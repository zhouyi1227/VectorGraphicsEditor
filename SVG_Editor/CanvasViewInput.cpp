#include "CanvasView.h"

#include <QApplication>
#include <QKeyEvent>
#include <QKeySequence>
#include <QMouseEvent>

#include <limits>

#include "CreationStrategy.h"

namespace {

bool isDragTool(CanvasView::Tool tool) {
    return tool == CanvasView::Tool::Line || tool == CanvasView::Tool::Rectangle || tool == CanvasView::Tool::Circle ||
           tool == CanvasView::Tool::Ellipse;
}

} // namespace

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

ShapeItem* CanvasView::shapeItemAtViewPosition(const QPoint& viewPosition) const {
    if (QGraphicsItem* graphicsItem = itemAt(viewPosition)) {
        return qgraphicsitem_cast<ShapeItem*>(graphicsItem);
    }
    return nullptr;
}
