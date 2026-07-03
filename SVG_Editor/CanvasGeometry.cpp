// =====================================================================
// CanvasGeometry.cpp
// ---------------------------------------------------------------------
// @brief CanvasGeometry.h 的实现
// @details 这些函数原本在 CanvasView.cpp 的匿名 namespace 中；本文件保持原行为
//          不变，仅提升可见性以便 core 单元测试覆盖。
// @layer   core
// =====================================================================

#include "CanvasGeometry.h"

#include <algorithm>
#include <cmath>

namespace {

constexpr qreal kMinimumScaleFactor = 0.01;

QPointF localPointForHandleImpl(CanvasHandle handle) {
    switch (handle) {
    case CanvasHandle::TopLeft:
        return QPointF(0.0, 0.0);
    case CanvasHandle::TopRight:
        return QPointF(1.0, 0.0);
    case CanvasHandle::BottomLeft:
        return QPointF(0.0, 1.0);
    case CanvasHandle::BottomRight:
        return QPointF(1.0, 1.0);
    case CanvasHandle::None:
        return QPointF(0.5, 0.5);
    }
    return QPointF(0.5, 0.5);
}

CanvasHandle oppositeHandle(CanvasHandle handle) {
    switch (handle) {
    case CanvasHandle::TopLeft:
        return CanvasHandle::BottomRight;
    case CanvasHandle::TopRight:
        return CanvasHandle::BottomLeft;
    case CanvasHandle::BottomLeft:
        return CanvasHandle::TopRight;
    case CanvasHandle::BottomRight:
        return CanvasHandle::TopLeft;
    case CanvasHandle::None:
        return CanvasHandle::None;
    }
    return CanvasHandle::None;
}

qreal dotProduct(const QPointF& lhs, const QPointF& rhs) { return lhs.x() * rhs.x() + lhs.y() * rhs.y(); }

qreal vectorLength(const QPointF& vector) { return std::hypot(vector.x(), vector.y()); }

QPointF normalizedVector(const QPointF& vector) {
    const qreal length = vectorLength(vector);
    if (qFuzzyIsNull(length)) {
        return QPointF();
    }
    return QPointF(vector.x() / length, vector.y() / length);
}

} // namespace

namespace canvas_geometry {

QRectF circleRectFromPoints(const QPointF& start, const QPointF& end) {
    const qreal dx = end.x() - start.x();
    const qreal dy = end.y() - start.y();
    const qreal side = std::max(std::abs(dx), std::abs(dy));
    const qreal x = dx >= 0.0 ? start.x() : start.x() - side;
    const qreal y = dy >= 0.0 ? start.y() : start.y() - side;
    return QRectF(x, y, side, side);
}

SelectionFrame scaledFrameFromHandle(CanvasHandle handle, const SelectionFrame& frame, const QPointF& currentPoint,
                                     bool keepAspectRatio) {
    const SelectionFrame baseFrame = frame.isOrthogonal() ? frame : frame.orthonormalized();
    const qreal xLength = vectorLength(baseFrame.xAxis);
    const qreal yLength = vectorLength(baseFrame.yAxis);
    if (qFuzzyIsNull(xLength) || qFuzzyIsNull(yLength)) {
        return baseFrame;
    }

    const QPointF handleLocal = localPointForHandleImpl(handle);
    const QPointF pivotLocal = localPointForHandleImpl(oppositeHandle(handle));
    const qreal signX = handleLocal.x() - pivotLocal.x();
    const qreal signY = handleLocal.y() - pivotLocal.y();
    const QPointF xDirection = normalizedVector(baseFrame.xAxis);
    const QPointF yDirection = normalizedVector(baseFrame.yAxis);
    const QPointF pivotPoint = baseFrame.topLeft + baseFrame.xAxis * pivotLocal.x() + baseFrame.yAxis * pivotLocal.y();
    const QPointF pivotToCurrent = currentPoint - pivotPoint;
    qreal scaleX = std::max((signX * dotProduct(pivotToCurrent, xDirection)) / xLength, kMinimumScaleFactor);
    qreal scaleY = std::max((signY * dotProduct(pivotToCurrent, yDirection)) / yLength, kMinimumScaleFactor);

    if (keepAspectRatio) {
        const qreal magnitude = std::max(scaleX, scaleY);
        scaleX = magnitude;
        scaleY = magnitude;
    }

    SelectionFrame scaledFrame;
    scaledFrame.xAxis = xDirection * (xLength * scaleX);
    scaledFrame.yAxis = yDirection * (yLength * scaleY);
    scaledFrame.topLeft = pivotPoint - scaledFrame.xAxis * pivotLocal.x() - scaledFrame.yAxis * pivotLocal.y();
    return scaledFrame;
}

QTransform transformBetweenFrames(const SelectionFrame& source, const SelectionFrame& target) {
    bool invertible = false;
    const QTransform sourceToLocal = source.localToSceneTransform().inverted(&invertible);
    if (!invertible) {
        return QTransform();
    }

    return sourceToLocal * target.localToSceneTransform();
}

QTransform scaleTransformFromHandle(CanvasHandle handle, const SelectionFrame& frame, const QPointF& currentPoint,
                                    bool keepAspectRatio) {
    return transformBetweenFrames(frame, scaledFrameFromHandle(handle, frame, currentPoint, keepAspectRatio));
}

} // namespace canvas_geometry
