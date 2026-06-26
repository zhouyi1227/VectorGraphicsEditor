// =====================================================================
// CanvasGeometry.cpp
// ---------------------------------------------------------------------
// @brief CanvasGeometry.h 的实现
// @details 这些函数原本在 CanvasView.cpp 的匿名 namespace 中；本文件保持原行为
//          不变，仅提升可见性以便 core 单元测试覆盖。
// @layer   core
// =====================================================================

#include "CanvasGeometry.h"

#include <QtMath>

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
    case CanvasHandle::Rotate:
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
    case CanvasHandle::Rotate:
    case CanvasHandle::None:
        return CanvasHandle::None;
    }
    return CanvasHandle::None;
}

qreal angleFromCenter(const QPointF& center, const QPointF& point) {
    return std::atan2(point.y() - center.y(), point.x() - center.x());
}

} // namespace

QPointF localPointForHandle(CanvasHandle handle) { return localPointForHandleImpl(handle); }

namespace canvas_geometry {

QRectF circleRectFromPoints(const QPointF& start, const QPointF& end) {
    const qreal dx = end.x() - start.x();
    const qreal dy = end.y() - start.y();
    const qreal side = std::max(std::abs(dx), std::abs(dy));
    const qreal x = dx >= 0.0 ? start.x() : start.x() - side;
    const qreal y = dy >= 0.0 ? start.y() : start.y() - side;
    return QRectF(x, y, side, side);
}

qreal snapAngleDegrees(qreal degrees) { return std::round(degrees / 15.0) * 15.0; }

SelectionFrame scaledFrameFromHandle(CanvasHandle handle, const SelectionFrame& frame, const QPointF& currentPoint,
                                     const QPointF& handlePressOffsetLocal, bool keepAspectRatio) {
    const QTransform localToScene = frame.localToSceneTransform();
    bool invertible = false;
    const QTransform sceneToLocal = localToScene.inverted(&invertible);
    if (!invertible) {
        return frame.orthonormalized();
    }

    const QPointF handleLocal = localPointForHandleImpl(handle);
    const QPointF pivotLocal = localPointForHandleImpl(oppositeHandle(handle));
    const QPointF currentLocal = sceneToLocal.map(currentPoint) - handlePressOffsetLocal;
    const qreal startDx = handleLocal.x() - pivotLocal.x();
    const qreal startDy = handleLocal.y() - pivotLocal.y();
    qreal scaleX = qFuzzyIsNull(startDx) ? 1.0 : (currentLocal.x() - pivotLocal.x()) / startDx;
    qreal scaleY = qFuzzyIsNull(startDy) ? 1.0 : (currentLocal.y() - pivotLocal.y()) / startDy;
    scaleX = std::max(scaleX, kMinimumScaleFactor);
    scaleY = std::max(scaleY, kMinimumScaleFactor);

    if (keepAspectRatio) {
        const qreal magnitude = std::max(scaleX, scaleY);
        scaleX = magnitude;
        scaleY = magnitude;
    }

    QTransform localScale;
    localScale.translate(pivotLocal.x(), pivotLocal.y());
    localScale.scale(scaleX, scaleY);
    localScale.translate(-pivotLocal.x(), -pivotLocal.y());
    return frame.mapped(localToScene * localScale * sceneToLocal).orthonormalized();
}

SelectionFrame rotatedFrameFromPoints(const SelectionFrame& frame, const QPointF& startPoint, const QPointF& currentPoint,
                                      bool snapToFifteenDegrees) {
    const QPointF center = frame.center();
    qreal rotationDegrees =
        qRadiansToDegrees(angleFromCenter(center, currentPoint) - angleFromCenter(center, startPoint));
    if (snapToFifteenDegrees) {
        rotationDegrees = snapAngleDegrees(rotationDegrees);
    }

    QTransform transform;
    transform.translate(center.x(), center.y());
    transform.rotate(rotationDegrees);
    transform.translate(-center.x(), -center.y());
    return frame.mapped(transform).orthonormalized();
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
                                    const QPointF& handlePressOffsetLocal, bool keepAspectRatio) {
    return transformBetweenFrames(frame,
                                  scaledFrameFromHandle(handle, frame, currentPoint, handlePressOffsetLocal,
                                                       keepAspectRatio));
}

QTransform rotationTransformFromPoints(const SelectionFrame& frame, const QPointF& startPoint,
                                       const QPointF& currentPoint, bool snapToFifteenDegrees) {
    return transformBetweenFrames(frame, rotatedFrameFromPoints(frame, startPoint, currentPoint, snapToFifteenDegrees));
}

} // namespace canvas_geometry
