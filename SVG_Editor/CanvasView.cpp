#include "CanvasView.h"

#include <QApplication>
#include <QGraphicsScene>
#include <QImage>
#include <QKeyEvent>
#include <QKeySequence>
#include <QLineF>
#include <QMouseEvent>
#include <QPainter>
#include <QUuid>

#include <algorithm>
#include <limits>

#include "CanvasGeometry.h"
#include "CanvasViewConstants.h"
#include "CreationStrategy.h"
#include "DragCreationStrategy.h"
#include "FileManager.h"
#include "I18n.h"
#include "PathCreationStrategy.h"
#include "ShapeFactory.h"
#include "ShapeItem.h"

namespace {

bool isDragTool(CanvasView::Tool tool) {
    return tool == CanvasView::Tool::Line || tool == CanvasView::Tool::Rectangle || tool == CanvasView::Tool::Circle ||
           tool == CanvasView::Tool::Ellipse;
}

std::optional<ShapeType> toolToShapeType(CanvasView::Tool tool) {
    switch (tool) {
    case CanvasView::Tool::Point:
        return ShapeType::Point;
    case CanvasView::Tool::Line:
        return ShapeType::Line;
    case CanvasView::Tool::Polyline:
        return ShapeType::Polyline;
    case CanvasView::Tool::Circle:
        return ShapeType::Circle;
    case CanvasView::Tool::Ellipse:
        return ShapeType::Ellipse;
    case CanvasView::Tool::Rectangle:
        return ShapeType::Rectangle;
    case CanvasView::Tool::Polygon:
        return ShapeType::Polygon;
    case CanvasView::Tool::Select:
        return std::nullopt;
    }

    return std::nullopt;
}

QRectF sceneBoundsForItems(const QList<ShapeItem*>& items) {
    QRectF bounds;
    bool first = true;
    for (ShapeItem* item : items) {
        if (item == nullptr) {
            continue;
        }

        const QRectF itemBounds = item->sceneTransform().map(item->shape()).boundingRect();
        if (first) {
            bounds = itemBounds;
            first = false;
        } else {
            bounds = bounds.united(itemBounds);
        }
    }

    return bounds.normalized();
}

} // namespace

CanvasView::CanvasView(QWidget* parent) : QGraphicsView(parent), m_scene(new QGraphicsScene(this)) {
    m_currentStyle.strokeEnabled = true;
    m_currentStyle.strokeColor = Qt::black;
    m_currentStyle.strokeWidth = 2.0;
    m_currentStyle.strokeStyle = Qt::SolidLine;
    m_currentStyle.fillColor = QColor("#80c8ff");
    m_currentStyle.fillEnabled = true;

    m_scene->setSceneRect(0.0, 0.0, kDefaultCanvasWidth, kDefaultCanvasHeight);
    m_scene->setBackgroundBrush(Qt::white);

    setScene(m_scene);
    setRenderHint(QPainter::Antialiasing, true);
    setDragMode(QGraphicsView::RubberBandDrag);
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    connect(m_scene, &QGraphicsScene::selectionChanged, this, &CanvasView::handleSelectionChanged);

    m_selectionOverlay = new SelectionTransformOverlayItem();
    m_scene->addItem(m_selectionOverlay);

    CreationContext creationContext;
    creationContext.nextZValue = [this]() { return nextZValue(); };
    creationContext.currentStyleFor = [this](ShapeType type) { return currentStyleFor(type); };
    creationContext.addShape = [this](const ShapeData& data, bool selectNewItem) { addShape(data, selectNewItem); };
    creationContext.generateId = [this]() { return generateShapeId(); };
    creationContext.currentShapeType = [this]() { return toolToShapeType(m_tool); };
    creationContext.scene = m_scene;

    m_dragStrategy = std::make_unique<DragCreationStrategy>(creationContext);
    m_polylineStrategy = std::make_unique<PathCreationStrategy>(ShapeType::Polyline, creationContext);
    m_polygonStrategy = std::make_unique<PathCreationStrategy>(ShapeType::Polygon, creationContext);
}

CanvasView::~CanvasView() = default;

void CanvasView::setLanguage(AppLanguage language) { m_language = language; }

void CanvasView::setTool(Tool tool) {
    if (m_tool == tool) {
        return;
    }

    cancelSelectionDrag();
    cancelTransformSession();
    cancelAllStrategies();

    m_tool = tool;
    setDragMode(tool == Tool::Select ? QGraphicsView::RubberBandDrag : QGraphicsView::NoDrag);
    m_selectionDragCandidate = false;
    invalidateSelectionFrame();
    updateSelectionDecorations();
    updateSelectionOverlay();

    if (tool == Tool::Select) {
        emit statusMessageChanged(i18n::tr(m_language, "toolbar.current_select", "Current tool: Select", "当前工具：选择"));
        return;
    }

    emit statusMessageChanged(i18n::tr(m_language, "toolbar.current_other", "Current tool: %1", "当前工具：%1")
                                  .arg(shapeDisplayName(toolToShapeType(tool).value_or(ShapeType::Rectangle), m_language)));
}

CanvasView::Tool CanvasView::tool() const { return m_tool; }

void CanvasView::updateSelectedShape(const ShapeData& data) {
    if (selectedShapeCount() != 1) {
        return;
    }

    ShapeItem* item = selectedShapeItem();
    if (item == nullptr) {
        return;
    }

    item->setShapeData(data);
    m_currentStyle = data.style;
    invalidateSelectionFrame();
    refreshSelectionNotification();
}

void CanvasView::deleteSelectedItem() {
    ShapeItem* item = selectedShapeItem();
    if (item == nullptr) {
        return;
    }

    cancelSelectionDrag();
    cancelTransformSession();
    m_scene->removeItem(item);
    delete item;
    invalidateSelectionFrame();
    refreshSelectionNotification();
}

void CanvasView::deleteSelectedItems() {
    const QList<ShapeItem*> items = selectedShapeItems();
    if (items.isEmpty()) {
        return;
    }

    cancelSelectionDrag();
    cancelTransformSession();
    for (ShapeItem* item : items) {
        m_scene->removeItem(item);
        delete item;
    }
    invalidateSelectionFrame();
    refreshSelectionNotification();
}

void CanvasView::copySelectedItem() {
    ShapeItem* item = selectedShapeItem();
    if (item == nullptr) {
        return;
    }

    m_clipboardShape = item->shapeData();
    m_pasteCount = 0;
    emit statusMessageChanged(i18n::tr(m_language, "status.shape_copied", "Shape copied.", "图形已复制。"));
}

void CanvasView::pasteCopiedItem() {
    if (!m_clipboardShape.has_value()) {
        return;
    }

    ++m_pasteCount;
    ShapeData copy = ShapeFactory::cloneWithOffset(*m_clipboardShape,
                                                   QPointF(kPasteOffsetPx * m_pasteCount, kPasteOffsetPx * m_pasteCount));
    copy.zValue = nextZValue();
    addShape(copy, true);
    emit statusMessageChanged(i18n::tr(m_language, "status.shape_pasted", "Shape pasted.", "图形已粘贴。"));
}

void CanvasView::clearCanvas() {
    cancelSelectionDrag();
    cancelTransformSession();
    cancelAllStrategies();

    m_scene->clear();
    m_zCounter = 0.0;
    m_pasteCount = 0;
    m_selectionFrame.reset();
    m_selectionDragCandidate = false;
    m_selectionDragSession = {};
    m_transformSession = {};

    m_selectionOverlay = new SelectionTransformOverlayItem();
    m_scene->addItem(m_selectionOverlay);
    refreshSelectionNotification();
}

DocumentData CanvasView::documentData() const {
    QList<ShapeData> shapes;
    QList<ShapeItem*> items;

    for (QGraphicsItem* graphicsItem : m_scene->items(Qt::AscendingOrder)) {
        if (auto* shapeItem = qgraphicsitem_cast<ShapeItem*>(graphicsItem)) {
            if (isPreviewItem(shapeItem)) {
                continue;
            }
            items.append(shapeItem);
        }
    }

    std::sort(items.begin(), items.end(),
              [](const ShapeItem* lhs, const ShapeItem* rhs) { return lhs->shapeData().zValue < rhs->shapeData().zValue; });

    for (const ShapeItem* item : items) {
        shapes.append(item->shapeData());
    }

    return {m_scene->sceneRect().size(), shapes};
}

void CanvasView::loadDocument(const DocumentData& document) {
    clearCanvas();
    m_scene->setSceneRect(QRectF(QPointF(0.0, 0.0), document.canvasSize));
    for (const ShapeData& shape : document.shapes) {
        addShape(shape, false);
        m_zCounter = std::max(m_zCounter, shape.zValue);
    }
    m_pasteCount = 0;
    invalidateSelectionFrame();
    refreshSelectionNotification();
}

bool CanvasView::exportImage(const QString& filePath, QString* errorMessage) {
    QRectF bounds;
    bool first = true;
    for (QGraphicsItem* graphicsItem : m_scene->items(Qt::AscendingOrder)) {
        auto* shapeItem = qgraphicsitem_cast<ShapeItem*>(graphicsItem);
        if (shapeItem == nullptr || isPreviewItem(shapeItem)) {
            continue;
        }

        if (first) {
            bounds = shapeItem->shape().boundingRect();
            first = false;
        } else {
            bounds = bounds.united(shapeItem->shape().boundingRect());
        }
    }

    if (first || bounds.isNull()) {
        bounds = m_scene->sceneRect();
    }

    bounds = bounds.adjusted(-kExportMarginPx, -kExportMarginPx, kExportMarginPx, kExportMarginPx);
    const QSize imageSize = bounds.size().toSize().expandedTo(kExportMinSize);

    QImage image(imageSize, QImage::Format_ARGB32_Premultiplied);
    image.fill(Qt::white);

    const bool overlayWasVisible = m_selectionOverlay != nullptr && m_selectionOverlay->isVisible();
    if (overlayWasVisible) {
        m_selectionOverlay->hide();
    }

    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing, true);
    m_scene->render(&painter, QRectF(QPointF(0.0, 0.0), imageSize), bounds);
    painter.end();

    if (overlayWasVisible) {
        m_selectionOverlay->show();
    }

    if (!image.save(filePath)) {
        if (errorMessage != nullptr) {
            *errorMessage = i18n::tr(m_language, "error.export_image", "Failed to save image file.", "保存图片文件失败。");
        }
        return false;
    }

    return true;
}

int CanvasView::selectedShapeCount() const { return static_cast<int>(selectedShapeItems().size()); }

void CanvasView::mousePressEvent(QMouseEvent* event) {
    const QPointF scenePoint = mapToScene(event->pos());
    m_selectionDragCandidate = false;

    if (m_tool == Tool::Select && event->button() == Qt::LeftButton && m_selectionOverlay != nullptr &&
        m_selectionOverlay->isVisible()) {
        const SelectionTransformOverlayItem::Handle handle = m_selectionOverlay->handleAt(scenePoint);
        if (handle != SelectionTransformOverlayItem::Handle::None) {
            beginTransformSession(handle, scenePoint);
            return;
        }
    }

    if (event->button() == Qt::LeftButton) {
        if (m_tool == Tool::Point) {
            ShapeData data;
            data.id = generateShapeId();
            data.type = ShapeType::Point;
            data.points = {scenePoint};
            data.style = currentStyleFor(ShapeType::Point);
            data.zValue = nextZValue();
            addShape(data, true);
            return;
        }

        if (isDragTool(m_tool)) {
            m_dragStrategy->begin(scenePoint);
            return;
        }

        if (ICreationStrategy* strategy = activePathStrategy(); strategy != nullptr) {
            strategy->begin(scenePoint);
            return;
        }
    }

    QGraphicsView::mousePressEvent(event);

    if (m_tool == Tool::Select && event->button() == Qt::LeftButton) {
        if (ShapeItem* item = shapeItemAtViewPosition(event->pos()); item != nullptr && item->isSelected()) {
            armSelectionDrag(event->pos(), scenePoint);
        }
    }
}

void CanvasView::mouseMoveEvent(QMouseEvent* event) {
    const QPointF scenePoint = mapToScene(event->pos());

    if (m_transformSession.active) {
        updateTransformSession(scenePoint, event->modifiers());
        return;
    }

    if (m_selectionDragSession.active) {
        updateSelectionDrag(scenePoint);
        return;
    }

    if (m_dragStrategy->inProgress()) {
        m_dragStrategy->update(scenePoint);
        return;
    }

    if (ICreationStrategy* strategy = activePathStrategy(); strategy != nullptr && strategy->inProgress()) {
        strategy->update(scenePoint);
    }

    QGraphicsView::mouseMoveEvent(event);

    if (m_tool != Tool::Select || !event->buttons().testFlag(Qt::LeftButton)) {
        return;
    }

    if (m_selectionDragCandidate &&
        (event->pos() - m_selectionMovePressViewPos).manhattanLength() >= QApplication::startDragDistance()) {
        beginSelectionDrag();
    }

    if (m_selectionDragSession.active) {
        updateSelectionDrag(scenePoint);
    }
}

void CanvasView::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton && m_transformSession.active) {
        finishTransformSession();
        return;
    }

    if (event->button() == Qt::LeftButton && m_dragStrategy->inProgress()) {
        m_dragStrategy->finish(mapToScene(event->pos()));
        return;
    }

    if (event->button() == Qt::LeftButton && m_selectionDragSession.active) {
        finishSelectionDrag();
        return;
    }

    QGraphicsView::mouseReleaseEvent(event);

    if (m_tool == Tool::Select && event->button() == Qt::LeftButton) {
        m_selectionDragCandidate = false;
    }
}

void CanvasView::mouseDoubleClickEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        if (ICreationStrategy* strategy = activePathStrategy(); strategy != nullptr && strategy->inProgress()) {
            strategy->finish(mapToScene(event->pos()));
            return;
        }
    }

    QGraphicsView::mouseDoubleClickEvent(event);
}

void CanvasView::keyPressEvent(QKeyEvent* event) {
    if ((event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter)) {
        if (ICreationStrategy* strategy = activePathStrategy(); strategy != nullptr && strategy->inProgress()) {
            const qreal nan = std::numeric_limits<qreal>::quiet_NaN();
            strategy->finish(QPointF(nan, nan));
            return;
        }
    }

    if (event->key() == Qt::Key_Escape) {
        if (m_selectionDragSession.active) {
            cancelSelectionDrag();
            return;
        }
        if (m_transformSession.active) {
            cancelTransformSession();
            return;
        }
        cancelAllStrategies();
        return;
    }

    if (event->key() == Qt::Key_Delete || event->key() == Qt::Key_Backspace) {
        emit deleteSelectionRequested();
        return;
    }

    if (event->matches(QKeySequence::Copy)) {
        copySelectedItem();
        return;
    }

    if (event->matches(QKeySequence::Paste)) {
        pasteCopiedItem();
        return;
    }

    QGraphicsView::keyPressEvent(event);
}

ShapeItem* CanvasView::selectedShapeItem() const {
    const QList<ShapeItem*> items = selectedShapeItems();
    return items.size() == 1 ? items.first() : nullptr;
}

QList<ShapeItem*> CanvasView::selectedShapeItems() const {
    QList<ShapeItem*> items;
    for (QGraphicsItem* item : m_scene->selectedItems()) {
        if (auto* shapeItem = qgraphicsitem_cast<ShapeItem*>(item)) {
            items.append(shapeItem);
        }
    }
    return items;
}

void CanvasView::handleSelectionChanged() {
    m_selectionDragCandidate = false;
    m_selectionDragSession = {};
    normalizeSelectedShapeTransforms();
    invalidateSelectionFrame();
    refreshSelectionNotification();
}

void CanvasView::addShape(const ShapeData& data, bool selectNewItem) {
    std::unique_ptr<ShapeItem> item = ShapeFactory::createItem(data);
    ShapeItem* rawItem = item.release();
    rawItem->setSelectionDecorationVisible(m_tool != Tool::Select);
    m_scene->addItem(rawItem);
    m_zCounter = std::max(m_zCounter, data.zValue);

    if (selectNewItem) {
        m_scene->clearSelection();
        rawItem->setSelected(true);
    }
}

ShapeStyle CanvasView::currentStyleFor(ShapeType type) const {
    ShapeStyle style = m_currentStyle;
    if (!shapeSupportsFill(type)) {
        style.fillEnabled = false;
    }
    return style;
}

QString CanvasView::generateShapeId() const { return QUuid::createUuid().toString(QUuid::WithoutBraces); }

ICreationStrategy* CanvasView::activePathStrategy() const {
    if (m_tool == Tool::Polyline) {
        return m_polylineStrategy.get();
    }
    if (m_tool == Tool::Polygon) {
        return m_polygonStrategy.get();
    }
    return nullptr;
}

void CanvasView::cancelAllStrategies() {
    if (m_dragStrategy != nullptr) {
        m_dragStrategy->cancel();
    }
    if (m_polylineStrategy != nullptr) {
        m_polylineStrategy->cancel();
    }
    if (m_polygonStrategy != nullptr) {
        m_polygonStrategy->cancel();
    }
}

bool CanvasView::isPreviewItem(const ShapeItem* item) const {
    if (item == nullptr) {
        return false;
    }

    return (m_dragStrategy != nullptr && m_dragStrategy->isPreviewItem(item)) ||
           (m_polylineStrategy != nullptr && m_polylineStrategy->isPreviewItem(item)) ||
           (m_polygonStrategy != nullptr && m_polygonStrategy->isPreviewItem(item));
}

std::optional<SelectionFrame> CanvasView::buildSelectionFrameFromSelection() const {
    const QList<ShapeItem*> items = selectedShapeItems();
    if (items.isEmpty()) {
        return std::nullopt;
    }

    if (items.size() == 1) {
        const ShapeItem* item = items.first();
        const SelectionFrame frame = SelectionFrame::fromRect(item->localGeometryBounds());
        return frame.mapped(item->shapeData().transform).orthonormalized();
    }

    const QRectF bounds = sceneBoundsForItems(items);
    if (bounds.isNull() || bounds.isEmpty()) {
        return std::nullopt;
    }

    return SelectionFrame::fromRect(bounds);
}

void CanvasView::normalizeSelectedShapeTransforms() {
    const QList<ShapeItem*> items = selectedShapeItems();
    for (ShapeItem* item : items) {
        if (item == nullptr) {
            continue;
        }

        const SelectionFrame localFrame = SelectionFrame::fromRect(item->localGeometryBounds());
        const SelectionFrame mappedFrame = localFrame.mapped(item->shapeData().transform);
        if (mappedFrame.isOrthogonal()) {
            continue;
        }

        ShapeData data = item->shapeData();
        data.transform = canvas_geometry::transformBetweenFrames(localFrame, mappedFrame.orthonormalized());
        item->setShapeData(data);
    }
}

void CanvasView::invalidateSelectionFrame() { m_selectionFrame.reset(); }

void CanvasView::refreshSelectionNotification() {
    const QList<ShapeItem*> items = selectedShapeItems();
    updateSelectionDecorations();
    updateSelectionOverlay();
    emit selectionStateChanged(items.size() == 1 ? items.first() : nullptr, static_cast<int>(items.size()));
}

void CanvasView::updateSelectionOverlay() {
    if (m_selectionOverlay == nullptr) {
        return;
    }

    if (m_tool != Tool::Select) {
        m_selectionOverlay->clearSelectionFrame();
        return;
    }

    if (selectedShapeCount() == 1 && !m_selectionDragSession.active && !m_transformSession.active) {
        m_selectionFrame = buildSelectionFrameFromSelection();
    }

    if (!m_selectionFrame.has_value()) {
        m_selectionFrame = buildSelectionFrameFromSelection();
    }

    if (!m_selectionFrame.has_value()) {
        m_selectionOverlay->clearSelectionFrame();
        return;
    }

    m_selectionOverlay->setHandlesVisible(!m_selectionDragSession.active && !m_transformSession.active);
    m_selectionOverlay->setSelectionFrame(*m_selectionFrame);
}

void CanvasView::updateSelectionDecorations() {
    const bool showItemSelectionDecoration = m_tool != Tool::Select;
    for (QGraphicsItem* graphicsItem : m_scene->items()) {
        if (auto* shapeItem = qgraphicsitem_cast<ShapeItem*>(graphicsItem)) {
            shapeItem->setSelectionDecorationVisible(showItemSelectionDecoration);
        }
    }
}

ShapeItem* CanvasView::shapeItemAtViewPosition(const QPoint& viewPosition) const {
    if (QGraphicsItem* graphicsItem = itemAt(viewPosition)) {
        return qgraphicsitem_cast<ShapeItem*>(graphicsItem);
    }
    return nullptr;
}

void CanvasView::armSelectionDrag(const QPoint& viewPosition, const QPointF& scenePoint) {
    m_selectionDragCandidate = true;
    m_selectionMovePressViewPos = viewPosition;
    m_selectionDragSession = {};
    m_selectionDragSession.pressScenePoint = scenePoint;
}

void CanvasView::beginSelectionDrag() {
    if (!m_selectionDragCandidate) {
        return;
    }

    if (!m_selectionFrame.has_value()) {
        m_selectionFrame = buildSelectionFrameFromSelection();
    }
    if (!m_selectionFrame.has_value()) {
        return;
    }

    const QList<ShapeItem*> items = selectedShapeItems();
    if (items.isEmpty()) {
        return;
    }

    // 拖动基准必须保留“按下时”的场景坐标；否则一旦会话 begin() 清空字段，
    // 第一帧 delta 会错误地从 (0, 0) 起算，图形就会瞬间跳走。
    const QPointF pressScenePoint = m_selectionDragSession.pressScenePoint;
    m_selectionDragSession = {};
    m_selectionDragSession.begin(items, *m_selectionFrame);
    m_selectionDragSession.pressScenePoint = pressScenePoint;
    m_selectionDragCandidate = false;
    updateSelectionOverlay();
}

void CanvasView::updateSelectionDrag(const QPointF& scenePoint) {
    if (!m_selectionDragSession.active) {
        return;
    }

    const QPointF delta = scenePoint - m_selectionDragSession.pressScenePoint;
    QTransform translation;
    translation.translate(delta.x(), delta.y());

    for (const MultiShapeEntry& entry : m_selectionDragSession.entries) {
        if (entry.item == nullptr) {
            continue;
        }

        ShapeData data = entry.snapshot;
        data.transform = entry.snapshot.transform * translation;
        entry.item->setShapeData(data);
    }

    if (m_selectionDragSession.entries.size() == 1) {
        m_selectionFrame = buildSelectionFrameFromSelection();
    } else {
        m_selectionFrame = m_selectionDragSession.originalFrame.translated(delta);
    }
    updateSelectionOverlay();
}

void CanvasView::finishSelectionDrag() {
    if (!m_selectionDragSession.active) {
        return;
    }

    m_selectionDragCandidate = false;
    m_selectionDragSession = {};
    refreshSelectionNotification();
}

void CanvasView::cancelSelectionDrag() {
    if (!m_selectionDragSession.active) {
        m_selectionDragCandidate = false;
        return;
    }

    m_selectionDragSession.cancel();
    m_selectionFrame = m_selectionDragSession.originalFrame;
    m_selectionDragCandidate = false;
    m_selectionDragSession = {};
    refreshSelectionNotification();
}

void CanvasView::beginTransformSession(SelectionTransformOverlayItem::Handle handle, const QPointF& scenePoint) {
    const QList<ShapeItem*> items = selectedShapeItems();
    if (items.isEmpty()) {
        return;
    }

    if (!m_selectionFrame.has_value()) {
        m_selectionFrame = buildSelectionFrameFromSelection();
    }
    if (!m_selectionFrame.has_value()) {
        return;
    }

    m_transformSession = {};
    m_transformSession.begin(items, *m_selectionFrame);
    m_transformSession.handle = handle;
    m_transformSession.startPoint = scenePoint;
    m_transformSession.handlePressOffsetLocal = QPointF();

    if (handle != SelectionTransformOverlayItem::Handle::Rotate) {
        bool invertible = false;
        const QTransform sceneToLocal = m_transformSession.originalFrame.localToSceneTransform().inverted(&invertible);
        if (invertible) {
            m_transformSession.handlePressOffsetLocal = sceneToLocal.map(scenePoint) - localPointForHandle(handle);
        }
    }

    updateSelectionOverlay();
}

void CanvasView::updateTransformSession(const QPointF& scenePoint, Qt::KeyboardModifiers modifiers) {
    if (!m_transformSession.active) {
        return;
    }

    const bool shiftPressed = modifiers.testFlag(Qt::ShiftModifier);
    const bool rotate = m_transformSession.handle == SelectionTransformOverlayItem::Handle::Rotate;

    SelectionFrame targetFrame = m_transformSession.originalFrame;
    if (rotate) {
        targetFrame = canvas_geometry::rotatedFrameFromPoints(m_transformSession.originalFrame, m_transformSession.startPoint,
                                                              scenePoint, shiftPressed);
    } else {
        targetFrame = canvas_geometry::scaledFrameFromHandle(m_transformSession.handle, m_transformSession.originalFrame,
                                                             scenePoint, m_transformSession.handlePressOffsetLocal,
                                                             shiftPressed);
    }

    const QTransform deltaTransform = canvas_geometry::transformBetweenFrames(m_transformSession.originalFrame, targetFrame);

    if (m_transformSession.entries.size() == 1) {
        const MultiShapeEntry& entry = m_transformSession.entries.first();
        if (entry.item != nullptr) {
            ShapeData data = entry.snapshot;
            const SelectionFrame localFrame = SelectionFrame::fromRect(entry.item->localGeometryBounds());
            data.transform = canvas_geometry::transformBetweenFrames(localFrame, targetFrame);
            entry.item->setShapeData(data);
        }
        m_selectionFrame = targetFrame;
    } else {
        for (const MultiShapeEntry& entry : m_transformSession.entries) {
            if (entry.item == nullptr) {
                continue;
            }

            ShapeData data = entry.snapshot;
            data.transform = entry.snapshot.transform * deltaTransform;
            entry.item->setShapeData(data);
        }
        m_selectionFrame = targetFrame;
    }
    updateSelectionOverlay();
}

void CanvasView::finishTransformSession() {
    if (!m_transformSession.active) {
        return;
    }

    m_transformSession = {};
    if (selectedShapeCount() == 1) {
        invalidateSelectionFrame();
    }
    refreshSelectionNotification();
}

void CanvasView::cancelTransformSession() {
    if (!m_transformSession.active) {
        return;
    }

    m_transformSession.cancel();
    m_selectionFrame = m_transformSession.originalFrame;
    m_transformSession = {};
    refreshSelectionNotification();
}

qreal CanvasView::nextZValue() {
    m_zCounter += 1.0;
    return m_zCounter;
}
