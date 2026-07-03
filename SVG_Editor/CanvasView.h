#pragma once

#include <QGraphicsView>

#include <cstdint>
#include <memory>
#include <optional>

#include "AppLanguage.h"
#include "MultiShapeSession.h"
#include "SelectionTransformOverlayItem.h"
#include "ShapeData.h"
#include "ShapeItem.h"

class ICreationStrategy;
class QGraphicsScene;
struct DocumentData;

class CanvasView : public QGraphicsView {
    Q_OBJECT

  public:
    enum class Tool : std::uint8_t {
        Select,
        Point,
        Line,
        Polyline,
        Circle,
        Ellipse,
        Rectangle,
        Polygon,
    };

    explicit CanvasView(QWidget* parent = nullptr);
    ~CanvasView() override;

    void setLanguage(AppLanguage language);
    void setTool(Tool tool);
    Tool tool() const;

    void updateSelectedShape(const ShapeData& data);
    void deleteSelectedItem();
    void deleteSelectedItems();
    void copySelectedItem();
    void pasteCopiedItem();
    void clearCanvas();
    DocumentData documentData() const;
    void loadDocument(const DocumentData& document);
    bool exportImage(const QString& filePath, QString* errorMessage = nullptr);
    int selectedShapeCount() const;

  signals:
    void selectionStateChanged(ShapeItem* primaryItem, int selectedCount);
    void statusMessageChanged(const QString& message);
    void deleteSelectionRequested();

  protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseDoubleClickEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

  private:
    struct SelectionDragSession : MultiShapeSession {
        QPointF pressScenePoint;
    };

    struct TransformSession : MultiShapeSession {
        SelectionTransformOverlayItem::Handle handle = SelectionTransformOverlayItem::Handle::None;
    };

    ShapeItem* selectedShapeItem() const;
    QList<ShapeItem*> selectedShapeItems() const;
    void handleSelectionChanged();
    void addShape(const ShapeData& data, bool selectNewItem = true);

    ShapeStyle currentStyleFor(ShapeType type) const;
    QString generateShapeId() const;
    ICreationStrategy* activePathStrategy() const;
    void cancelAllStrategies();
    bool isPreviewItem(const ShapeItem* item) const;

    std::optional<SelectionFrame> buildSelectionFrameFromSelection() const;
    void normalizeSelectedShapeTransforms();
    void invalidateSelectionFrame();
    void refreshSelectionNotification();
    void updateSelectionOverlay();
    void updateSelectionDecorations();

    ShapeItem* shapeItemAtViewPosition(const QPoint& viewPosition) const;
    void armSelectionDrag(const QPoint& viewPosition, const QPointF& scenePoint);
    void beginSelectionDrag();
    void updateSelectionDrag(const QPointF& scenePoint);
    void finishSelectionDrag();
    void cancelSelectionDrag();

    void beginTransformSession(SelectionTransformOverlayItem::Handle handle, const QPointF& scenePoint);
    void updateTransformSession(const QPointF& scenePoint, Qt::KeyboardModifiers modifiers);
    void finishTransformSession();
    void cancelTransformSession();

    qreal nextZValue();

    QGraphicsScene* m_scene = nullptr;
    AppLanguage m_language = kDefaultLanguage;
    Tool m_tool = Tool::Select;
    ShapeStyle m_currentStyle;
    std::optional<ShapeData> m_clipboardShape;
    qreal m_zCounter = 0.0;
    int m_pasteCount = 0;
    SelectionTransformOverlayItem* m_selectionOverlay = nullptr;

    std::unique_ptr<ICreationStrategy> m_dragStrategy;
    std::unique_ptr<ICreationStrategy> m_polylineStrategy;
    std::unique_ptr<ICreationStrategy> m_polygonStrategy;

    std::optional<SelectionFrame> m_selectionFrame;
    TransformSession m_transformSession;
    SelectionDragSession m_selectionDragSession;
    bool m_selectionDragCandidate = false;
    QPoint m_selectionMovePressViewPos;
};
