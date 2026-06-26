#pragma once

#include <memory>

#include "ShapeData.h"

class ShapeItem;

class ShapeFactory {
  public:
    static std::unique_ptr<ShapeItem> createItem(const ShapeData& data);
    static ShapeData cloneWithOffset(const ShapeData& data, const QPointF& offset);
};
