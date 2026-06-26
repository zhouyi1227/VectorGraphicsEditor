#include <QtTest>

#include <cmath>

#include "CanvasGeometry.h"
#include "SelectionFrame.h"

namespace {
constexpr qreal kTolerance = 0.0001;

bool pointsNear(const QPointF& lhs, const QPointF& rhs) {
    return std::abs(lhs.x() - rhs.x()) < kTolerance && std::abs(lhs.y() - rhs.y()) < kTolerance;
}

qreal dotProduct(const QPointF& lhs, const QPointF& rhs) { return lhs.x() * rhs.x() + lhs.y() * rhs.y(); }
} // namespace

class CanvasGeometryTests : public QObject {
    Q_OBJECT

  private slots:
    void circleRectFromDiagonalDrag();
    void circleRectFromAntiDiagonalDrag();
    void snapAngleQuantizesTo15Degrees();
    void orthonormalizedFrameKeepsCenterAndRemovesShear();
    void scaleTransformDoublesFrameSizeFromTopLeft();
    void scaledRotatedFrameKeepsAxesPerpendicular();
    void scaleClampPreventsFlipAcrossPivot();
    void transformBetweenFramesMapsCornersExactly();
    void rotationTransformAroundCenterIsCorrect();
    void rotationTransformWithShiftSnapsTo15Degrees();
};

void CanvasGeometryTests::circleRectFromDiagonalDrag() {
    const QRectF rect = canvas_geometry::circleRectFromPoints(QPointF(10.0, 20.0), QPointF(50.0, 80.0));
    // dx=40, dy=60, side=60, 起点在左上角
    QCOMPARE(rect.x(), 10.0);
    QCOMPARE(rect.y(), 20.0);
    QCOMPARE(rect.width(), 60.0);
    QCOMPARE(rect.height(), 60.0);
}

void CanvasGeometryTests::circleRectFromAntiDiagonalDrag() {
    const QRectF rect = canvas_geometry::circleRectFromPoints(QPointF(50.0, 80.0), QPointF(10.0, 20.0));
    // dx=-40, dy=-60, side=60, 起点在右下角 → 反推左上角
    QCOMPARE(rect.x(), -10.0);
    QCOMPARE(rect.y(), 20.0);
    QCOMPARE(rect.width(), 60.0);
    QCOMPARE(rect.height(), 60.0);
}

void CanvasGeometryTests::snapAngleQuantizesTo15Degrees() {
    QCOMPARE(canvas_geometry::snapAngleDegrees(0.0), 0.0);
    QCOMPARE(canvas_geometry::snapAngleDegrees(7.0), 0.0);
    QCOMPARE(canvas_geometry::snapAngleDegrees(8.0), 15.0);
    QCOMPARE(canvas_geometry::snapAngleDegrees(22.0), 15.0);
    QCOMPARE(canvas_geometry::snapAngleDegrees(23.0), 30.0);
    QCOMPARE(canvas_geometry::snapAngleDegrees(-7.0), 0.0);
    QCOMPARE(canvas_geometry::snapAngleDegrees(-8.0), -15.0);
}

void CanvasGeometryTests::orthonormalizedFrameKeepsCenterAndRemovesShear() {
    SelectionFrame frame;
    frame.topLeft = QPointF(0.0, 0.0);
    frame.xAxis = QPointF(10.0, 0.0);
    frame.yAxis = QPointF(3.0, 8.0);

    const QPointF center = frame.center();
    const SelectionFrame normalized = frame.orthonormalized();

    QVERIFY(pointsNear(normalized.center(), center));
    QVERIFY(std::abs(dotProduct(normalized.xAxis, normalized.yAxis)) < kTolerance);
}

void CanvasGeometryTests::scaleTransformDoublesFrameSizeFromTopLeft() {
    const SelectionFrame frame = SelectionFrame::fromRect(QRectF(0.0, 0.0, 100.0, 50.0));

    // 从 BottomRight 拖到 (200,100) = 局部 (2,2)，pivot=TopLeft=(0,0)
    // scaleX = 2/1 = 2, scaleY = 2/1 = 2 → frame 在两个轴都翻倍
    const QTransform transform = canvas_geometry::scaleTransformFromHandle(CanvasHandle::BottomRight, frame,
                                                                           QPointF(200.0, 100.0), QPointF(), false);

    const QPointF tl = transform.map(QPointF(0.0, 0.0));
    const QPointF br = transform.map(QPointF(100.0, 50.0));
    QVERIFY(pointsNear(tl, QPointF(0.0, 0.0)));
    QVERIFY(pointsNear(br, QPointF(200.0, 100.0)));
}

void CanvasGeometryTests::scaledRotatedFrameKeepsAxesPerpendicular() {
    const SelectionFrame frame = SelectionFrame::fromRect(QRectF(-50.0, -50.0, 100.0, 100.0));
    const QPointF center = frame.center();
    const SelectionFrame rotated = canvas_geometry::rotatedFrameFromPoints(
        frame, QPointF(center.x() + 10.0, center.y()), QPointF(center.x(), center.y() - 10.0), false);
    const SelectionFrame scaled = canvas_geometry::scaledFrameFromHandle(
        CanvasHandle::BottomRight, rotated, rotated.bottomRight() + QPointF(60.0, 20.0), QPointF(), false);

    QVERIFY(rotated.isOrthogonal());
    QVERIFY(scaled.isOrthogonal());
}

void CanvasGeometryTests::scaleClampPreventsFlipAcrossPivot() {
    const SelectionFrame frame = SelectionFrame::fromRect(QRectF(0.0, 0.0, 100.0, 100.0));
    const SelectionFrame scaled = canvas_geometry::scaledFrameFromHandle(CanvasHandle::BottomRight, frame,
                                                                         QPointF(-20.0, -10.0), QPointF(), false);

    QVERIFY(scaled.isOrthogonal());
    QVERIFY(std::hypot(scaled.xAxis.x(), scaled.xAxis.y()) > 0.0);
    QVERIFY(std::hypot(scaled.yAxis.x(), scaled.yAxis.y()) > 0.0);
    QVERIFY(std::abs(dotProduct(scaled.xAxis, scaled.yAxis)) < kTolerance);
}

void CanvasGeometryTests::transformBetweenFramesMapsCornersExactly() {
    const SelectionFrame source = SelectionFrame::fromRect(QRectF(0.0, 0.0, 100.0, 80.0));
    SelectionFrame target = SelectionFrame::fromRect(QRectF(0.0, 0.0, 160.0, 120.0));
    target = canvas_geometry::rotatedFrameFromPoints(target, target.center() + QPointF(10.0, 0.0),
                                                     target.center() + QPointF(0.0, -10.0), false);

    const QTransform delta = canvas_geometry::transformBetweenFrames(source, target);
    QVERIFY2(pointsNear(delta.map(source.topLeft), target.topLeft),
             qPrintable(QString("topLeft mismatch: actual=(%1,%2) expected=(%3,%4)")
                            .arg(delta.map(source.topLeft).x())
                            .arg(delta.map(source.topLeft).y())
                            .arg(target.topLeft.x())
                            .arg(target.topLeft.y())));
    QVERIFY2(pointsNear(delta.map(source.topRight()), target.topRight()),
             qPrintable(QString("topRight mismatch: actual=(%1,%2) expected=(%3,%4)")
                            .arg(delta.map(source.topRight()).x())
                            .arg(delta.map(source.topRight()).y())
                            .arg(target.topRight().x())
                            .arg(target.topRight().y())));
    QVERIFY2(pointsNear(delta.map(source.bottomLeft()), target.bottomLeft()),
             qPrintable(QString("bottomLeft mismatch: actual=(%1,%2) expected=(%3,%4)")
                            .arg(delta.map(source.bottomLeft()).x())
                            .arg(delta.map(source.bottomLeft()).y())
                            .arg(target.bottomLeft().x())
                            .arg(target.bottomLeft().y())));
    QVERIFY2(pointsNear(delta.map(source.bottomRight()), target.bottomRight()),
             qPrintable(QString("bottomRight mismatch: actual=(%1,%2) expected=(%3,%4)")
                            .arg(delta.map(source.bottomRight()).x())
                            .arg(delta.map(source.bottomRight()).y())
                            .arg(target.bottomRight().x())
                            .arg(target.bottomRight().y())));
}

void CanvasGeometryTests::rotationTransformAroundCenterIsCorrect() {
    const SelectionFrame frame = SelectionFrame::fromRect(QRectF(-50.0, -25.0, 100.0, 50.0));
    const QPointF center = frame.center();

    // start 在 center 正右方，current 在 center 正上方 → 累计旋转 -90°
    const QTransform transform = canvas_geometry::rotationTransformFromPoints(
        frame, QPointF(center.x() + 10.0, center.y()), QPointF(center.x(), center.y() - 10.0), false);

    // frame 的 right-center 点 (-50+100, -25+25) = (50, 0)，旋转 -90° 应到 (0, -50)
    const QPointF rotated = transform.map(QPointF(50.0, 0.0));
    QVERIFY2(pointsNear(rotated, QPointF(0.0, -50.0)),
             qPrintable(QString("actual rotated point=(%1,%2)").arg(rotated.x()).arg(rotated.y())));
}

void CanvasGeometryTests::rotationTransformWithShiftSnapsTo15Degrees() {
    const SelectionFrame frame = SelectionFrame::fromRect(QRectF(0.0, 0.0, 100.0, 50.0));
    const QPointF center = frame.center();

    // 真实累计角度约 7°（不到 15° 阈值）；Shift 打开后应被吸附到 0°
    const QTransform transform = canvas_geometry::rotationTransformFromPoints(
        frame, QPointF(center.x() + 10.0, center.y()), QPointF(center.x() + 10.0, center.y() - 1.23), true);

    // 0° 旋转 = 恒等变换
    const QPointF sample = QPointF(20.0, 10.0);
    QVERIFY(pointsNear(transform.map(sample), sample));
}

QTEST_APPLESS_MAIN(CanvasGeometryTests)

#include "CanvasGeometryTests.moc"
