#pragma once

#include <QGraphicsView>

#include <cstdint>
#include <optional>

#include "AppLanguage.h"
#include "FileManager.h"
#include "ShapeData.h"
#include "ShapeItem.h"

class CanvasView : public QGraphicsView {
    Q_OBJECT

  public:
    enum class Tool : std::uint8_t { Select, Point, Line, Polyline, Circle, Ellipse, Rectangle, Polygon };

    explicit CanvasView(QWidget* parent = nullptr);

    void setLanguage(AppLanguage language);
    void setTool(Tool tool);
    Tool tool() const;

    void updateSelectedShape(const ShapeData& data);
    void deleteSelectedItem();
    void copySelectedItem();
    void pasteCopiedItem();
    void clearCanvas();

    DocumentData documentData() const;
    void loadDocument(const DocumentData& document);
    bool exportImage(const QString& filePath, QString* errorMessage = nullptr) const;

  signals:
    void selectedShapeChanged(ShapeItem* item);
    void statusMessageChanged(const QString& message);

  protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseDoubleClickEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

  private:
    ShapeItem* selectedShapeItem() const;
    void handleSelectionChanged();
    void addShape(const ShapeData& data, bool selectNewItem = true);
    void beginDragShape(const QPointF& scenePoint);
    void updateDragPreview(const QPointF& scenePoint);
    void finishDragShape(const QPointF& scenePoint);
    void beginPathPoint(const QPointF& scenePoint);
    void updatePathPreview(const QPointF& scenePoint);
    void finishPathShape(bool closed);
    void cancelDrawing();
    ShapeData buildDragShapeData(const QPointF& endPoint) const;
    ShapeData buildPathPreviewData(const QPointF& cursorPoint) const;
    ShapeStyle currentStyleFor(ShapeType type) const;
    void refreshSelectionNotification();
    qreal nextZValue();

    QGraphicsScene* m_scene = nullptr;
    AppLanguage m_language = AppLanguage::SimplifiedChinese;
    Tool m_tool = Tool::Select;
    ShapeStyle m_currentStyle;
    QPointF m_dragStartPoint;
    bool m_dragDrawing = false;
    QVector<QPointF> m_pathPoints;
    ShapeItem* m_previewItem = nullptr;
    std::optional<ShapeData> m_clipboardShape;
    qreal m_zCounter = 0.0;
    int m_pasteCount = 0;
};
