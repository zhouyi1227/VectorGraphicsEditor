#include "ShapeItem.h"

#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QPainterPathStroker>

#include <algorithm>

ShapeItem::ShapeItem(const ShapeData& data, QGraphicsItem* parent)
    : QGraphicsObject(parent), m_data(normalizedShapeData(data)) {
    setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
    setZValue(m_data.zValue);
}

QRectF ShapeItem::boundingRect() const { return shape().boundingRect().adjusted(-4.0, -4.0, 4.0, 4.0); }

QPainterPath ShapeItem::shape() const {
    QPainterPath path = buildPath();
    if (path.isEmpty()) {
        return path;
    }

    const qreal strokerWidth = std::max<qreal>(8.0, m_data.style.strokeWidth + 6.0);
    QPainterPathStroker stroker;
    stroker.setWidth(strokerWidth);
    stroker.setCapStyle(Qt::RoundCap);
    stroker.setJoinStyle(Qt::RoundJoin);

    if (shapeSupportsFill(m_data.type) && m_data.style.fillEnabled) {
        return stroker.createStroke(path).united(path);
    }

    return stroker.createStroke(path);
}

void ShapeItem::paint(QPainter* painter, const QStyleOptionGraphicsItem*, QWidget*) {
    painter->setRenderHint(QPainter::Antialiasing, true);

    QPen pen = buildPen();
    painter->setPen(pen);

    const bool fillEnabled = shapeSupportsFill(m_data.type) && m_data.style.fillEnabled;
    painter->setBrush(fillEnabled ? QBrush(m_data.style.fillColor) : Qt::NoBrush);

    switch (m_data.type) {
    case ShapeType::Point: {
        if (m_data.points.isEmpty()) {
            break;
        }
        const QPointF point = m_data.points.first();
        const qreal radius = std::max<qreal>(3.0, m_data.style.strokeWidth * 1.5);
        painter->drawEllipse(point, radius, radius);
        break;
    }
    case ShapeType::Line:
        if (m_data.points.size() >= 2) {
            painter->drawLine(m_data.points.at(0), m_data.points.at(1));
        }
        break;
    case ShapeType::Polyline:
        if (m_data.points.size() >= 2) {
            painter->drawPolyline(m_data.points.constData(), static_cast<int>(m_data.points.size()));
        }
        break;
    case ShapeType::Circle:
    case ShapeType::Ellipse:
        painter->drawEllipse(m_data.rect);
        break;
    case ShapeType::Rectangle:
        painter->drawRect(m_data.rect);
        break;
    case ShapeType::Polygon:
        if (m_previewMode && m_data.points.size() >= 2) {
            painter->drawPolyline(m_data.points.constData(), static_cast<int>(m_data.points.size()));
        } else if (m_data.points.size() >= 3) {
            painter->drawPolygon(m_data.points.constData(), static_cast<int>(m_data.points.size()));
        }
        break;
    }

    if (isSelected() && !m_previewMode) {
        QPen selectionPen(QColor("#2d7ff9"));
        selectionPen.setStyle(Qt::DashLine);
        selectionPen.setCosmetic(true);
        selectionPen.setWidthF(1.0);
        painter->setPen(selectionPen);
        painter->setBrush(Qt::NoBrush);
        painter->drawRect(buildPath().boundingRect().adjusted(-6.0, -6.0, 6.0, 6.0));
    }
}

ShapeData ShapeItem::shapeData() const { return m_data; }

void ShapeItem::setShapeData(const ShapeData& data) {
    prepareGeometryChange();
    m_data = normalizedShapeData(data);
    setZValue(m_data.zValue);
    update();
}

void ShapeItem::setPreviewMode(bool enabled) {
    m_previewMode = enabled;
    setFlag(QGraphicsItem::ItemIsSelectable, !enabled);
    setFlag(QGraphicsItem::ItemIsMovable, !enabled);
    update();
}

void ShapeItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
    QGraphicsObject::mouseReleaseEvent(event);

    if (m_previewMode || m_committingMove) {
        return;
    }

    const QPointF delta = pos();
    if (!qFuzzyIsNull(delta.x()) || !qFuzzyIsNull(delta.y())) {
        commitMoveOffset(delta);
        emit shapeChanged(this);
    }
}

QPainterPath ShapeItem::buildPath() const {
    QPainterPath path;

    switch (m_data.type) {
    case ShapeType::Point:
        if (!m_data.points.isEmpty()) {
            const QPointF point = m_data.points.first();
            const qreal radius = std::max<qreal>(3.0, m_data.style.strokeWidth * 1.5);
            path.addEllipse(point, radius, radius);
        }
        break;
    case ShapeType::Line:
        if (m_data.points.size() >= 2) {
            path.moveTo(m_data.points.at(0));
            path.lineTo(m_data.points.at(1));
        }
        break;
    case ShapeType::Polyline:
        if (!m_data.points.isEmpty()) {
            path.moveTo(m_data.points.first());
            for (int index = 1; index < m_data.points.size(); ++index) {
                path.lineTo(m_data.points.at(index));
            }
        }
        break;
    case ShapeType::Circle:
    case ShapeType::Ellipse:
        path.addEllipse(m_data.rect);
        break;
    case ShapeType::Rectangle:
        path.addRect(m_data.rect);
        break;
    case ShapeType::Polygon:
        if (m_previewMode && !m_data.points.isEmpty()) {
            path.moveTo(m_data.points.first());
            for (int index = 1; index < m_data.points.size(); ++index) {
                path.lineTo(m_data.points.at(index));
            }
        } else if (m_data.points.size() >= 3) {
            path.addPolygon(QPolygonF(m_data.points));
        }
        break;
    }

    return path;
}

QPen ShapeItem::buildPen() const {
    QPen pen(m_data.style.strokeColor, m_data.style.strokeWidth, m_data.style.strokeStyle, Qt::RoundCap, Qt::RoundJoin);
    if (m_previewMode) {
        pen.setColor(m_data.style.strokeColor.lighter(115));
        pen.setStyle(Qt::DashLine);
    }
    return pen;
}

void ShapeItem::commitMoveOffset(const QPointF& delta) {
    if (qFuzzyIsNull(delta.x()) && qFuzzyIsNull(delta.y())) {
        return;
    }

    prepareGeometryChange();
    translateShapeData(m_data, delta);
    m_committingMove = true;
    setPos(QPointF());
    m_committingMove = false;
    update();
}
