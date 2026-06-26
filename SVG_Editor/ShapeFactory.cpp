#include "ShapeFactory.h"

#include <QUuid>

#include "ShapeItem.h"

std::unique_ptr<ShapeItem> ShapeFactory::createItem(const ShapeData& data) {
    return std::make_unique<ShapeItem>(normalizedShapeData(data));
}

ShapeData ShapeFactory::cloneWithOffset(const ShapeData& source, const QPointF& offset) {
    ShapeData copy = source;
    copy.id = QUuid::createUuid().toString(QUuid::WithoutBraces);
    copy.zValue += 1.0;
    translateShapeData(copy, offset);
    return normalizedShapeData(copy);
}
