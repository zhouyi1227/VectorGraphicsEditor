#include "ShapeData.h"

#include <QJsonArray>

#include <algorithm>
#include <cmath>

namespace {

QString textForLanguage(AppLanguage language, const char* english, const char* chinese) {
    return language == AppLanguage::SimplifiedChinese ? QString::fromUtf8(chinese) : QString::fromUtf8(english);
}

QJsonObject pointToJson(const QPointF& point) {
    return {
        {"x", point.x()},
        {"y", point.y()},
    };
}

QPointF pointFromJson(const QJsonObject& object) {
    return QPointF(object.value("x").toDouble(), object.value("y").toDouble());
}

QJsonArray pointsToJson(const QVector<QPointF>& points) {
    QJsonArray array;
    for (const QPointF& point : points) {
        array.append(pointToJson(point));
    }
    return array;
}

QVector<QPointF> pointsFromJson(const QJsonArray& array) {
    QVector<QPointF> points;
    points.reserve(array.size());
    for (const auto& value : array) {
        points.append(pointFromJson(value.toObject()));
    }
    return points;
}

QRectF normalizedRect(const QRectF& rect) {
    QRectF result = rect.normalized();
    if (result.width() < 0.0) {
        result.setWidth(0.0);
    }
    if (result.height() < 0.0) {
        result.setHeight(0.0);
    }
    return result;
}

} // namespace

QString shapeTypeToString(ShapeType type) {
    switch (type) {
    case ShapeType::Point:
        return "point";
    case ShapeType::Line:
        return "line";
    case ShapeType::Polyline:
        return "polyline";
    case ShapeType::Circle:
        return "circle";
    case ShapeType::Ellipse:
        return "ellipse";
    case ShapeType::Rectangle:
        return "rectangle";
    case ShapeType::Polygon:
        return "polygon";
    }
    return "unknown";
}

std::optional<ShapeType> shapeTypeFromString(const QString& value) {
    if (value == "point") {
        return ShapeType::Point;
    }
    if (value == "line") {
        return ShapeType::Line;
    }
    if (value == "polyline") {
        return ShapeType::Polyline;
    }
    if (value == "circle") {
        return ShapeType::Circle;
    }
    if (value == "ellipse") {
        return ShapeType::Ellipse;
    }
    if (value == "rectangle") {
        return ShapeType::Rectangle;
    }
    if (value == "polygon") {
        return ShapeType::Polygon;
    }
    return std::nullopt;
}

QString penStyleToString(Qt::PenStyle style) {
    switch (style) {
    case Qt::SolidLine:
        return "solid";
    case Qt::DashLine:
        return "dash";
    case Qt::DotLine:
        return "dot";
    case Qt::DashDotLine:
        return "dashdot";
    default:
        return "solid";
    }
}

std::optional<Qt::PenStyle> penStyleFromString(const QString& value) {
    if (value == "solid") {
        return Qt::SolidLine;
    }
    if (value == "dash") {
        return Qt::DashLine;
    }
    if (value == "dot") {
        return Qt::DotLine;
    }
    if (value == "dashdot") {
        return Qt::DashDotLine;
    }
    return std::nullopt;
}

bool shapeSupportsFill(ShapeType type) {
    return type == ShapeType::Circle || type == ShapeType::Ellipse || type == ShapeType::Rectangle ||
           type == ShapeType::Polygon;
}

QString shapeDisplayName(ShapeType type, AppLanguage language) {
    switch (type) {
    case ShapeType::Point:
        return textForLanguage(language, "Point", "点");
    case ShapeType::Line:
        return textForLanguage(language, "Line", "直线");
    case ShapeType::Polyline:
        return textForLanguage(language, "Polyline", "折线");
    case ShapeType::Circle:
        return textForLanguage(language, "Circle", "圆");
    case ShapeType::Ellipse:
        return textForLanguage(language, "Ellipse", "椭圆");
    case ShapeType::Rectangle:
        return textForLanguage(language, "Rectangle", "矩形");
    case ShapeType::Polygon:
        return textForLanguage(language, "Polygon", "多边形");
    }
    return textForLanguage(language, "Unknown", "未知图形");
}

QString penStyleDisplayName(Qt::PenStyle style, AppLanguage language) {
    switch (style) {
    case Qt::SolidLine:
        return textForLanguage(language, "Solid", "实线");
    case Qt::DashLine:
        return textForLanguage(language, "Dash", "虚线");
    case Qt::DotLine:
        return textForLanguage(language, "Dot", "点线");
    case Qt::DashDotLine:
        return textForLanguage(language, "Dash Dot", "点划线");
    default:
        return textForLanguage(language, "Solid", "实线");
    }
}

ShapeData normalizedShapeData(const ShapeData& source) {
    ShapeData data = source;
    data.rect = normalizedRect(data.rect);

    if (data.type == ShapeType::Rectangle || data.type == ShapeType::Ellipse) {
        return data;
    }

    if (data.type == ShapeType::Circle) {
        QRectF rect = normalizedRect(data.rect);
        const qreal side = std::max(rect.width(), rect.height());
        data.rect = QRectF(rect.topLeft(), QSizeF(side, side));
        return data;
    }

    return data;
}

QRectF pointsBoundingRect(const QVector<QPointF>& points) {
    if (points.isEmpty()) {
        return QRectF();
    }

    qreal minX = points.first().x();
    qreal minY = points.first().y();
    qreal maxX = points.first().x();
    qreal maxY = points.first().y();

    for (const QPointF& point : points) {
        minX = std::min(minX, point.x());
        minY = std::min(minY, point.y());
        maxX = std::max(maxX, point.x());
        maxY = std::max(maxY, point.y());
    }

    return QRectF(QPointF(minX, minY), QPointF(maxX, maxY)).normalized();
}

void translateShapeData(ShapeData& data, const QPointF& delta) {
    switch (data.type) {
    case ShapeType::Point:
    case ShapeType::Line:
    case ShapeType::Polyline:
    case ShapeType::Polygon:
        for (QPointF& point : data.points) {
            point += delta;
        }
        break;
    case ShapeType::Circle:
    case ShapeType::Ellipse:
    case ShapeType::Rectangle:
        data.rect.translate(delta);
        break;
    }
}

QJsonObject shapeDataToJson(const ShapeData& source) {
    ShapeData data = normalizedShapeData(source);

    QJsonObject geometry;
    switch (data.type) {
    case ShapeType::Point:
        if (!data.points.isEmpty()) {
            geometry = pointToJson(data.points.first());
        }
        break;
    case ShapeType::Line:
        if (data.points.size() >= 2) {
            geometry = {
                {"x1", data.points.at(0).x()},
                {"y1", data.points.at(0).y()},
                {"x2", data.points.at(1).x()},
                {"y2", data.points.at(1).y()},
            };
        }
        break;
    case ShapeType::Polyline:
    case ShapeType::Polygon:
        geometry = {
            {"points", pointsToJson(data.points)},
        };
        break;
    case ShapeType::Circle: {
        const QPointF center = data.rect.center();
        geometry = {
            {"cx", center.x()},
            {"cy", center.y()},
            {"r", data.rect.width() / 2.0},
        };
        break;
    }
    case ShapeType::Ellipse: {
        const QPointF center = data.rect.center();
        geometry = {
            {"cx", center.x()},
            {"cy", center.y()},
            {"rx", data.rect.width() / 2.0},
            {"ry", data.rect.height() / 2.0},
        };
        break;
    }
    case ShapeType::Rectangle:
        geometry = {
            {"x", data.rect.x()},
            {"y", data.rect.y()},
            {"width", data.rect.width()},
            {"height", data.rect.height()},
        };
        break;
    }

    return {
        {"id", data.id},
        {"type", shapeTypeToString(data.type)},
        {"geometry", geometry},
        {"strokeColor", data.style.strokeColor.name(QColor::HexArgb)},
        {"strokeWidth", data.style.strokeWidth},
        {"strokeStyle", penStyleToString(data.style.strokeStyle)},
        {"fillColor", data.style.fillColor.name(QColor::HexArgb)},
        {"fillEnabled", data.style.fillEnabled},
        {"zValue", data.zValue},
    };
}

std::optional<ShapeData> shapeDataFromJson(const QJsonObject& object) {
    const std::optional<ShapeType> type = shapeTypeFromString(object.value("type").toString());
    if (!type.has_value()) {
        return std::nullopt;
    }

    ShapeData data;
    data.id = object.value("id").toString();
    data.type = *type;
    data.style.strokeColor = QColor(object.value("strokeColor").toString("#ff000000"));
    data.style.strokeWidth = std::max(0.5, object.value("strokeWidth").toDouble(2.0));
    data.style.fillColor = QColor(object.value("fillColor").toString("#00000000"));
    data.style.fillEnabled = object.value("fillEnabled").toBool(false) && shapeSupportsFill(data.type);
    data.zValue = object.value("zValue").toDouble(0.0);

    const std::optional<Qt::PenStyle> penStyle = penStyleFromString(object.value("strokeStyle").toString("solid"));
    data.style.strokeStyle = penStyle.value_or(Qt::SolidLine);

    const QJsonObject geometry = object.value("geometry").toObject();
    switch (data.type) {
    case ShapeType::Point:
        data.points = {pointFromJson(geometry)};
        break;
    case ShapeType::Line:
        data.points = {
            QPointF(geometry.value("x1").toDouble(), geometry.value("y1").toDouble()),
            QPointF(geometry.value("x2").toDouble(), geometry.value("y2").toDouble()),
        };
        break;
    case ShapeType::Polyline:
    case ShapeType::Polygon:
        data.points = pointsFromJson(geometry.value("points").toArray());
        break;
    case ShapeType::Circle: {
        const qreal r = std::max(0.0, geometry.value("r").toDouble());
        const qreal cx = geometry.value("cx").toDouble();
        const qreal cy = geometry.value("cy").toDouble();
        data.rect = QRectF(cx - r, cy - r, r * 2.0, r * 2.0);
        break;
    }
    case ShapeType::Ellipse: {
        const qreal rx = std::max(0.0, geometry.value("rx").toDouble());
        const qreal ry = std::max(0.0, geometry.value("ry").toDouble());
        const qreal cx = geometry.value("cx").toDouble();
        const qreal cy = geometry.value("cy").toDouble();
        data.rect = QRectF(cx - rx, cy - ry, rx * 2.0, ry * 2.0);
        break;
    }
    case ShapeType::Rectangle:
        data.rect = QRectF(geometry.value("x").toDouble(), geometry.value("y").toDouble(),
                           std::max(0.0, geometry.value("width").toDouble()),
                           std::max(0.0, geometry.value("height").toDouble()));
        break;
    }

    return normalizedShapeData(data);
}
