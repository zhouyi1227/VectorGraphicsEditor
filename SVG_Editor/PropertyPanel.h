#pragma once

#include <QFormLayout>
#include <QWidget>

#include "AppLanguage.h"
#include "ShapeData.h"

class QCheckBox;
class QComboBox;
class QDoubleSpinBox;
class QLabel;
class QPushButton;

class PropertyPanel : public QWidget {
    Q_OBJECT

  public:
    explicit PropertyPanel(QWidget* parent = nullptr);

    void setLanguage(AppLanguage language);
    void clearSelection();
    void setShapeData(const ShapeData& data);

  signals:
    void shapeEdited(const ShapeData& data);

  private:
    void setupUi();
    void retranslateUi();
    void updateButtons();
    void updateGeometryControls();
    void updateSelectionTexts();
    void emitEditedShape();
    void rebuildLineStyleCombo();

    QLabel* m_titleLabel = nullptr;
    QLabel* m_hintLabel = nullptr;
    QLabel* m_geometryLabels[6] = {};
    QDoubleSpinBox* m_geometryEdits[6] = {};
    QPushButton* m_strokeColorButton = nullptr;
    QPushButton* m_fillColorButton = nullptr;
    QDoubleSpinBox* m_lineWidthSpin = nullptr;
    QComboBox* m_lineStyleCombo = nullptr;
    QCheckBox* m_fillEnabledCheck = nullptr;
    QFormLayout* m_formLayout = nullptr;

    ShapeData m_currentData;
    AppLanguage m_language = AppLanguage::SimplifiedChinese;
    bool m_hasSelection = false;
    bool m_updatingWidgets = false;
};
