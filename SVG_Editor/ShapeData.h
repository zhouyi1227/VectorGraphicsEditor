#pragma once

#include <QColor>
#include <QJsonObject>
#include <QPointF>
#include <QRectF>
#include <QString>
#include <Qt>
#include <QVector>

#include <cstdint>
#include <optional>

#include "AppLanguage.h"

enum class ShapeType : std::uint8_t { Point, Line, Polyline, Circle, Ellipse, Rectangle, Polygon };

struct ShapeStyle {
    QColor strokeColor = Qt::black;
    qreal strokeWidth = 2.0;
    Qt::PenStyle strokeStyle = Qt::SolidLine;
    QColor fillColor = QColor("#80c8ff");
    bool fillEnabled = false;
};

struct ShapeData {
    QString id;
    ShapeType type = ShapeType::Rectangle;
    QVector<QPointF> points;
    QRectF rect;
    ShapeStyle style;
    qreal zValue = 0.0;
};

QString shapeTypeToString(ShapeType type);
std::optional<ShapeType> shapeTypeFromString(const QString& value);

QString penStyleToString(Qt::PenStyle style);
std::optional<Qt::PenStyle> penStyleFromString(const QString& value);

bool shapeSupportsFill(ShapeType type);
QString shapeDisplayName(ShapeType type, AppLanguage language = AppLanguage::English);
QString penStyleDisplayName(Qt::PenStyle style, AppLanguage language = AppLanguage::English);

ShapeData normalizedShapeData(const ShapeData& data);
QRectF pointsBoundingRect(const QVector<QPointF>& points);
void translateShapeData(ShapeData& data, const QPointF& delta);

QJsonObject shapeDataToJson(const ShapeData& data);
std::optional<ShapeData> shapeDataFromJson(const QJsonObject& object);
