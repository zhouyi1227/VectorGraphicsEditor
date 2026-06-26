// =====================================================================
// CanvasGeometry.h
// ---------------------------------------------------------------------
// @brief   CanvasView 内部几何 helper 的 core 层版本（无 QGraphicsView 依赖）
// @details CanvasView 的匿名 namespace 里有一批"纯函数"helper（不依赖
//          QGraphicsItem / QGraphicsScene 状态），本文件把它们提升到 core 静态库，
//          便于编写单元测试与在其它视图（如缩略图、工具栏图标）复用。
// @layer   core
// @warning 内部签名 / 行为变更须同步更新 CanvasView.cpp 的调用点。
// =====================================================================

#pragma once

#include <QPointF>
#include <QRectF>
#include <QTransform>

#include <cstdint>

#include "SelectionFrame.h"

/// @brief 选中手柄位置（core 层定义；QGraphicsView 层通过 SelectionTransformOverlayItem 暴露同名列）
enum class CanvasHandle : std::uint8_t {
    None,        ///< 无命中
    TopLeft,     ///< 左上角缩放手柄
    TopRight,    ///< 右上角缩放手柄
    BottomLeft,  ///< 左下角缩放手柄
    BottomRight, ///< 右下角缩放手柄
    Rotate,      ///< 上方圆旋转手柄
};

/// @brief 给定手柄位置，返回 frame 局部单位矩形中的对应点。
QPointF localPointForHandle(CanvasHandle handle);

namespace canvas_geometry {

/// @brief 从拖拽的起、终点构造圆的外接正方形。
QRectF circleRectFromPoints(const QPointF& start, const QPointF& end);

/// @brief 构造"沿 frame 局部轴缩放"的场景空间变换。
QTransform scaleTransformFromHandle(CanvasHandle handle, const SelectionFrame& frame, const QPointF& currentPoint,
                                    const QPointF& handlePressOffsetLocal, bool keepAspectRatio);

/// @brief 根据当前拖拽位置直接计算目标正交 frame。
SelectionFrame scaledFrameFromHandle(CanvasHandle handle, const SelectionFrame& frame, const QPointF& currentPoint,
                                     const QPointF& handlePressOffsetLocal, bool keepAspectRatio);

/// @brief 构造"以 frame 中心为旋转中心"的场景空间变换。
QTransform rotationTransformFromPoints(const SelectionFrame& frame, const QPointF& startPoint,
                                       const QPointF& currentPoint, bool snapToFifteenDegrees);

/// @brief 根据当前拖拽位置直接计算旋转后的目标正交 frame。
SelectionFrame rotatedFrameFromPoints(const SelectionFrame& frame, const QPointF& startPoint, const QPointF& currentPoint,
                                      bool snapToFifteenDegrees);

/// @brief 计算两个 frame 之间的场景空间增量变换。
QTransform transformBetweenFrames(const SelectionFrame& source, const SelectionFrame& target);

/// @brief 把角度吸附到 15° 的整数倍。
qreal snapAngleDegrees(qreal degrees);

} // namespace canvas_geometry
