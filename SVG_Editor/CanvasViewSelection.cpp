#include "CanvasView.h"

#include <QGraphicsScene>

#include "CanvasGeometry.h"

namespace {

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

void CanvasView::beginTransformSession(SelectionTransformOverlayItem::Handle handle, const QPointF&) {
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

    updateSelectionOverlay();
}

void CanvasView::updateTransformSession(const QPointF& scenePoint, Qt::KeyboardModifiers modifiers) {
    if (!m_transformSession.active) {
        return;
    }

    const bool keepAspectRatio = modifiers.testFlag(Qt::ShiftModifier);
    const SelectionFrame targetFrame =
        canvas_geometry::scaledFrameFromHandle(m_transformSession.handle, m_transformSession.originalFrame, scenePoint,
                                               keepAspectRatio);
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
