#pragma once

#include <array>
#include <functional>
#include <unordered_map>
#include <vector>

#include "ShapeData.h"

struct GeometryField {
    const char* label = "";
    double minimum = -100000.0;
    double maximum = 100000.0;
};

struct GeometryFieldSet {
    std::vector<GeometryField> fields;
    std::function<void(ShapeData&, const std::array<double, 6>&)> applyTo;
};

inline const GeometryFieldSet& geometryFieldsFor(ShapeType type) {
    static const std::unordered_map<ShapeType, GeometryFieldSet> kFields = {
        {ShapeType::Point,
         {{{"x"}, {"y"}},
          [](ShapeData& data, const std::array<double, 6>& values) {
              if (!data.points.isEmpty()) {
                  data.points[0] = QPointF(values[0], values[1]);
              }
          }}},
        {ShapeType::Line,
         {{{"x1"}, {"y1"}, {"x2"}, {"y2"}},
          [](ShapeData& data, const std::array<double, 6>& values) {
              if (data.points.size() >= 2) {
                  data.points[0] = QPointF(values[0], values[1]);
                  data.points[1] = QPointF(values[2], values[3]);
              }
          }}},
        {ShapeType::Polyline,
         {{{"x"}, {"y"}},
          [](ShapeData& data, const std::array<double, 6>& values) {
              const QRectF currentBounds = pointsBoundingRect(data.points);
              translateShapeData(data, QPointF(values[0] - currentBounds.x(), values[1] - currentBounds.y()));
          }}},
        {ShapeType::Polygon,
         {{{"x"}, {"y"}},
          [](ShapeData& data, const std::array<double, 6>& values) {
              const QRectF currentBounds = pointsBoundingRect(data.points);
              translateShapeData(data, QPointF(values[0] - currentBounds.x(), values[1] - currentBounds.y()));
          }}},
        {ShapeType::Circle,
         {{{"cx"}, {"cy"}, {"r", 0.0, 100000.0}},
          [](ShapeData& data, const std::array<double, 6>& values) {
              const qreal radius = values[2];
              const QPointF center(values[0], values[1]);
              data.rect = QRectF(center.x() - radius, center.y() - radius, radius * 2.0, radius * 2.0);
          }}},
        {ShapeType::Ellipse,
         {{{"cx"}, {"cy"}, {"rx", 0.0, 100000.0}, {"ry", 0.0, 100000.0}},
          [](ShapeData& data, const std::array<double, 6>& values) {
              const QPointF center(values[0], values[1]);
              data.rect = QRectF(center.x() - values[2], center.y() - values[3], values[2] * 2.0, values[3] * 2.0);
          }}},
        {ShapeType::Rectangle,
         {{{"x"}, {"y"}, {"width", 0.0, 100000.0}, {"height", 0.0, 100000.0}},
          [](ShapeData& data, const std::array<double, 6>& values) {
              data.rect = QRectF(values[0], values[1], values[2], values[3]);
          }}},
    };

    return kFields.at(type);
}
