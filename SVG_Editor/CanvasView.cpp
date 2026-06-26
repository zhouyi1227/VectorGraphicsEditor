#include "CanvasView.h"

#include <QFile>
#include <QGraphicsScene>
#include <QImage>
#include <QKeyEvent>
#include <QKeySequence>
#include <QLineF>
#include <QMouseEvent>
#include <QPainter>
#include <QUuid>

#include <algorithm>

#include "ShapeFactory.h"
#include "ShapeItem.h"

namespace {

QString textForLanguage(AppLanguage language, const QString& english, const QString& chinese) {
    return language == AppLanguage::SimplifiedChinese ? chinese : english;
}

bool isPathTool(CanvasView::Tool tool) {
    return tool == CanvasView::Tool::Polyline || tool == CanvasView::Tool::Polygon;
}

bool isDragTool(CanvasView::Tool tool) {
    return tool == CanvasView::Tool::Line || tool == CanvasView::Tool::Rectangle || tool == CanvasView::Tool::Circle ||
           tool == CanvasView::Tool::Ellipse;
}

ShapeType toolToShapeType(CanvasView::Tool tool) {
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
        return ShapeType::Rectangle;
    }
    return ShapeType::Rectangle;
}

QRectF circleRectFromPoints(const QPointF& start, const QPointF& end) {
    const qreal dx = end.x() - start.x();
    const qreal dy = end.y() - start.y();
    const qreal side = std::max(std::abs(dx), std::abs(dy));
    const qreal x = dx >= 0.0 ? start.x() : start.x() - side;
    const qreal y = dy >= 0.0 ? start.y() : start.y() - side;
    return QRectF(x, y, side, side);
}

} // namespace

CanvasView::CanvasView(QWidget* parent) : QGraphicsView(parent), m_scene(new QGraphicsScene(this)) {
    m_currentStyle.strokeColor = Qt::black;
    m_currentStyle.strokeWidth = 2.0;
    m_currentStyle.strokeStyle = Qt::SolidLine;
    m_currentStyle.fillColor = QColor("#80c8ff");
    m_currentStyle.fillEnabled = true;

    m_scene->setSceneRect(0.0, 0.0, 1200.0, 800.0);
    m_scene->setBackgroundBrush(Qt::white);

    setScene(m_scene);
    setRenderHint(QPainter::Antialiasing, true);
    setDragMode(QGraphicsView::RubberBandDrag);
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);

    connect(m_scene, &QGraphicsScene::selectionChanged, this, &CanvasView::handleSelectionChanged);
}

void CanvasView::setLanguage(AppLanguage language) { m_language = language; }

void CanvasView::setTool(Tool tool) {
    if (m_tool == tool) {
        return;
    }

    cancelDrawing();
    m_tool = tool;
    setDragMode(tool == Tool::Select ? QGraphicsView::RubberBandDrag : QGraphicsView::NoDrag);
    emit statusMessageChanged(tool == Tool::Select
                                  ? textForLanguage(m_language, "Current tool: Select", "当前工具：选择")
                                  : textForLanguage(m_language, "Current tool: %1", "当前工具：%1")
                                        .arg(shapeDisplayName(toolToShapeType(tool), m_language)));
}

CanvasView::Tool CanvasView::tool() const { return m_tool; }

void CanvasView::updateSelectedShape(const ShapeData& data) {
    ShapeItem* item = selectedShapeItem();
    if (item == nullptr) {
        return;
    }

    item->setShapeData(data);
    m_currentStyle = data.style;
    refreshSelectionNotification();
}

void CanvasView::deleteSelectedItem() {
    ShapeItem* item = selectedShapeItem();
    if (item == nullptr) {
        return;
    }

    m_scene->removeItem(item);
    delete item;
    refreshSelectionNotification();
}

void CanvasView::copySelectedItem() {
    ShapeItem* item = selectedShapeItem();
    if (item == nullptr) {
        return;
    }

    m_clipboardShape = item->shapeData();
    m_pasteCount = 0;
    emit statusMessageChanged(textForLanguage(m_language, "Shape copied.", "图形已复制。"));
}

void CanvasView::pasteCopiedItem() {
    if (!m_clipboardShape.has_value()) {
        return;
    }

    ++m_pasteCount;
    ShapeData copy =
        ShapeFactory::cloneWithOffset(*m_clipboardShape, QPointF(16.0 * m_pasteCount, 16.0 * m_pasteCount));
    copy.zValue = nextZValue();
    addShape(copy, true);
    emit statusMessageChanged(textForLanguage(m_language, "Shape pasted.", "图形已粘贴。"));
}

void CanvasView::clearCanvas() {
    cancelDrawing();
    m_scene->clear();
    m_previewItem = nullptr;
    m_zCounter = 0.0;
    m_pasteCount = 0;
    refreshSelectionNotification();
}

DocumentData CanvasView::documentData() const {
    QList<ShapeData> shapes;
    QList<ShapeItem*> items;

    for (QGraphicsItem* graphicsItem : m_scene->items(Qt::AscendingOrder)) {
        if (auto* shapeItem = qgraphicsitem_cast<ShapeItem*>(graphicsItem)) {
            if (shapeItem == m_previewItem) {
                continue;
            }
            items.append(shapeItem);
        }
    }

    std::sort(items.begin(), items.end(), [](const ShapeItem* lhs, const ShapeItem* rhs) {
        return lhs->shapeData().zValue < rhs->shapeData().zValue;
    });

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
    refreshSelectionNotification();
}

bool CanvasView::exportImage(const QString& filePath, QString* errorMessage) const {
    QRectF bounds = m_scene->itemsBoundingRect();
    if (bounds.isNull()) {
        bounds = m_scene->sceneRect();
    }

    bounds = bounds.adjusted(-20.0, -20.0, 20.0, 20.0);
    const QSize imageSize = bounds.size().toSize().expandedTo(QSize(400, 300));

    QImage image(imageSize, QImage::Format_ARGB32_Premultiplied);
    image.fill(Qt::white);

    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing, true);
    m_scene->render(&painter, QRectF(QPointF(0.0, 0.0), imageSize), bounds);
    painter.end();

    if (!image.save(filePath)) {
        if (errorMessage != nullptr) {
            *errorMessage = textForLanguage(m_language, "Failed to save image file.", "保存图片文件失败。");
        }
        return false;
    }

    return true;
}

void CanvasView::mousePressEvent(QMouseEvent* event) {
    const QPointF scenePoint = mapToScene(event->pos());

    if (event->button() == Qt::LeftButton) {
        if (m_tool == Tool::Point) {
            ShapeData data;
            data.id = QUuid::createUuid().toString(QUuid::WithoutBraces);
            data.type = ShapeType::Point;
            data.points = {scenePoint};
            data.style = currentStyleFor(ShapeType::Point);
            data.zValue = nextZValue();
            addShape(data, true);
            return;
        }

        if (isDragTool(m_tool)) {
            beginDragShape(scenePoint);
            return;
        }

        if (isPathTool(m_tool)) {
            beginPathPoint(scenePoint);
            return;
        }
    }

    QGraphicsView::mousePressEvent(event);
}

void CanvasView::mouseMoveEvent(QMouseEvent* event) {
    const QPointF scenePoint = mapToScene(event->pos());

    if (m_dragDrawing) {
        updateDragPreview(scenePoint);
        return;
    }

    if (!m_pathPoints.isEmpty()) {
        updatePathPreview(scenePoint);
    }

    QGraphicsView::mouseMoveEvent(event);
}

void CanvasView::mouseReleaseEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton && m_dragDrawing) {
        finishDragShape(mapToScene(event->pos()));
        return;
    }

    QGraphicsView::mouseReleaseEvent(event);
}

void CanvasView::mouseDoubleClickEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton && isPathTool(m_tool) && !m_pathPoints.isEmpty()) {
        const QPointF scenePoint = mapToScene(event->pos());
        if ((m_pathPoints.last() - scenePoint).manhattanLength() > 1.0) {
            m_pathPoints.append(scenePoint);
        }
        finishPathShape(m_tool == Tool::Polygon);
        return;
    }

    QGraphicsView::mouseDoubleClickEvent(event);
}

void CanvasView::keyPressEvent(QKeyEvent* event) {
    if ((event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) && isPathTool(m_tool) &&
        !m_pathPoints.isEmpty()) {
        finishPathShape(m_tool == Tool::Polygon);
        return;
    }

    if (event->key() == Qt::Key_Escape) {
        cancelDrawing();
        return;
    }

    if (event->key() == Qt::Key_Delete || event->key() == Qt::Key_Backspace) {
        deleteSelectedItem();
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
    const QList<QGraphicsItem*> items = m_scene->selectedItems();
    for (QGraphicsItem* item : items) {
        if (auto* shapeItem = qgraphicsitem_cast<ShapeItem*>(item)) {
            return shapeItem;
        }
    }
    return nullptr;
}

void CanvasView::handleSelectionChanged() { refreshSelectionNotification(); }

void CanvasView::addShape(const ShapeData& data, bool selectNewItem) {
    std::unique_ptr<ShapeItem> item = ShapeFactory::createItem(data);
    connect(item.get(), &ShapeItem::shapeChanged, this, [this](ShapeItem* changedItem) {
        m_currentStyle = changedItem->shapeData().style;
        refreshSelectionNotification();
    });

    ShapeItem* rawItem = item.release();
    m_scene->addItem(rawItem);
    m_zCounter = std::max(m_zCounter, data.zValue);

    if (selectNewItem) {
        m_scene->clearSelection();
        rawItem->setSelected(true);
    }
}

void CanvasView::beginDragShape(const QPointF& scenePoint) {
    cancelDrawing();
    m_dragDrawing = true;
    m_dragStartPoint = scenePoint;

    ShapeData preview = buildDragShapeData(scenePoint);
    preview.zValue = nextZValue();
    std::unique_ptr<ShapeItem> item = ShapeFactory::createItem(preview);
    item->setPreviewMode(true);

    m_previewItem = item.release();
    m_scene->addItem(m_previewItem);
}

void CanvasView::updateDragPreview(const QPointF& scenePoint) {
    if (m_previewItem == nullptr) {
        return;
    }

    m_previewItem->setShapeData(buildDragShapeData(scenePoint));
}

void CanvasView::finishDragShape(const QPointF& scenePoint) {
    const ShapeData data = buildDragShapeData(scenePoint);

    m_dragDrawing = false;
    if (m_previewItem != nullptr) {
        m_scene->removeItem(m_previewItem);
        delete m_previewItem;
        m_previewItem = nullptr;
    }

    bool validShape = false;
    switch (data.type) {
    case ShapeType::Line:
        validShape = data.points.size() >= 2 && QLineF(data.points.at(0), data.points.at(1)).length() > 1.0;
        break;
    case ShapeType::Circle:
    case ShapeType::Ellipse:
    case ShapeType::Rectangle:
        validShape = data.rect.width() > 1.0 && data.rect.height() > 1.0;
        break;
    default:
        break;
    }

    if (validShape) {
        addShape(data, true);
    }
}

void CanvasView::beginPathPoint(const QPointF& scenePoint) {
    if (m_pathPoints.isEmpty()) {
        ShapeData preview;
        preview.id = QUuid::createUuid().toString(QUuid::WithoutBraces);
        preview.type = toolToShapeType(m_tool);
        preview.style = currentStyleFor(preview.type);
        preview.zValue = nextZValue();

        std::unique_ptr<ShapeItem> item = ShapeFactory::createItem(preview);
        item->setPreviewMode(true);
        m_previewItem = item.release();
        m_scene->addItem(m_previewItem);
    }

    m_pathPoints.append(scenePoint);
    updatePathPreview(scenePoint);
}

void CanvasView::updatePathPreview(const QPointF& scenePoint) {
    if (m_previewItem == nullptr || m_pathPoints.isEmpty()) {
        return;
    }

    m_previewItem->setShapeData(buildPathPreviewData(scenePoint));
}

void CanvasView::finishPathShape(bool closed) {
    if (m_pathPoints.isEmpty()) {
        cancelDrawing();
        return;
    }

    ShapeData data = buildPathPreviewData(m_pathPoints.last());
    data.points = m_pathPoints;
    data.type = closed ? ShapeType::Polygon : ShapeType::Polyline;

    if (m_previewItem != nullptr) {
        m_scene->removeItem(m_previewItem);
        delete m_previewItem;
        m_previewItem = nullptr;
    }

    const int minimumPoints = closed ? 3 : 2;
    if (data.points.size() >= minimumPoints) {
        addShape(data, true);
    }

    m_pathPoints.clear();
}

void CanvasView::cancelDrawing() {
    m_dragDrawing = false;
    m_pathPoints.clear();
    if (m_previewItem != nullptr) {
        m_scene->removeItem(m_previewItem);
        delete m_previewItem;
        m_previewItem = nullptr;
    }
}

ShapeData CanvasView::buildDragShapeData(const QPointF& endPoint) const {
    ShapeData data;
    data.id = QUuid::createUuid().toString(QUuid::WithoutBraces);
    data.type = toolToShapeType(m_tool);
    data.style = currentStyleFor(data.type);
    data.zValue = m_zCounter + 1.0;

    switch (data.type) {
    case ShapeType::Line:
        data.points = {m_dragStartPoint, endPoint};
        break;
    case ShapeType::Rectangle:
    case ShapeType::Ellipse:
        data.rect = QRectF(m_dragStartPoint, endPoint).normalized();
        break;
    case ShapeType::Circle:
        data.rect = circleRectFromPoints(m_dragStartPoint, endPoint);
        break;
    default:
        break;
    }

    return normalizedShapeData(data);
}

ShapeData CanvasView::buildPathPreviewData(const QPointF& cursorPoint) const {
    ShapeData data;
    data.id = QUuid::createUuid().toString(QUuid::WithoutBraces);
    data.type = toolToShapeType(m_tool);
    data.style = currentStyleFor(data.type);
    data.zValue = m_zCounter + 1.0;
    data.points = m_pathPoints;
    data.points.append(cursorPoint);
    return normalizedShapeData(data);
}

ShapeStyle CanvasView::currentStyleFor(ShapeType type) const {
    ShapeStyle style = m_currentStyle;
    if (!shapeSupportsFill(type)) {
        style.fillEnabled = false;
    }
    return style;
}

void CanvasView::refreshSelectionNotification() {
    if (ShapeItem* item = selectedShapeItem(); item != nullptr) {
        emit selectedShapeChanged(item);
    } else {
        emit selectedShapeChanged(nullptr);
    }
}

qreal CanvasView::nextZValue() {
    m_zCounter += 1.0;
    return m_zCounter;
}
