#pragma once

#include <QMenu>
#include <QMainWindow>
#include <QToolBar>

#include "AppLanguage.h"
#include "CanvasView.h"

class PropertyPanel;
class QAction;
class QActionGroup;
class QDockWidget;
class TutorialDialog;

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    explicit MainWindow(QWidget* parent = nullptr);

  private:
    AppLanguage loadLanguage() const;
    void saveLanguage() const;
    void setLanguage(AppLanguage language);
    void setupUi();
    void setupActions();
    void setupMenus();
    void setupToolbar();
    void connectSignals();
    void retranslateUi();
    void updateWindowTitle();
    void showTutorial();
    QAction* createToolAction(CanvasView::Tool tool);

    bool saveToPath(const QString& filePath);
    bool saveDocument();
    bool saveDocumentAs();
    void openDocument();
    void exportImage();

    CanvasView* m_canvasView = nullptr;
    PropertyPanel* m_propertyPanel = nullptr;
    QDockWidget* m_propertyDock = nullptr;
    TutorialDialog* m_tutorialDialog = nullptr;
    QToolBar* m_toolBar = nullptr;
    QMenu* m_fileMenu = nullptr;
    QMenu* m_editMenu = nullptr;
    QMenu* m_toolMenu = nullptr;
    QMenu* m_tutorialMenu = nullptr;
    QMenu* m_languageMenu = nullptr;

    QAction* m_openAction = nullptr;
    QAction* m_saveAction = nullptr;
    QAction* m_saveAsAction = nullptr;
    QAction* m_exportAction = nullptr;
    QAction* m_exitAction = nullptr;
    QAction* m_deleteAction = nullptr;
    QAction* m_copyAction = nullptr;
    QAction* m_pasteAction = nullptr;
    QAction* m_clearAction = nullptr;
    QAction* m_showTutorialAction = nullptr;
    QAction* m_englishAction = nullptr;
    QAction* m_simplifiedChineseAction = nullptr;

    QActionGroup* m_toolActionGroup = nullptr;
    QActionGroup* m_languageActionGroup = nullptr;
    AppLanguage m_language = AppLanguage::SimplifiedChinese;
    QString m_currentFilePath;
};
