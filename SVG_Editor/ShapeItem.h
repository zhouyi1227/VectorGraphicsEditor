#pragma once

#include <QGraphicsObject>
#include <QPainterPath>
#include <QPen>

#include "ShapeData.h"

class ShapeItem : public QGraphicsObject {
    Q_OBJECT

  public:
    enum { Type = QGraphicsItem::UserType + 1 };

    explicit ShapeItem(const ShapeData& data, QGraphicsItem* parent = nullptr);

    int type() const override { return Type; }
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

    ShapeData shapeData() const;
    void setShapeData(const ShapeData& data);
    void setPreviewMode(bool enabled);

  signals:
    void shapeChanged(ShapeItem* item);

  protected:
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

  private:
    QPainterPath buildPath() const;
    QPen buildPen() const;
    void commitMoveOffset(const QPointF& delta);

    ShapeData m_data;
    bool m_previewMode = false;
    bool m_committingMove = false;
};
