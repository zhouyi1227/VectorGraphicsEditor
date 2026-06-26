#include "MainWindow.h"

#include <QAction>
#include <QActionGroup>
#include <QDockWidget>
#include <QFileDialog>
#include <QFileInfo>
#include <QSettings>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QStatusBar>
#include <QToolBar>

#include "FileManager.h"
#include "PropertyPanel.h"
#include "ShapeItem.h"
#include "TutorialDialog.h"

namespace {

QString textForLanguage(AppLanguage language, const QString& english, const QString& chinese) {
    return language == AppLanguage::SimplifiedChinese ? chinese : english;
}

QString toolLabel(CanvasView::Tool tool, AppLanguage language) {
    switch (tool) {
    case CanvasView::Tool::Select:
        return textForLanguage(language, "Select", "选择");
    case CanvasView::Tool::Point:
        return textForLanguage(language, "Point", "点");
    case CanvasView::Tool::Line:
        return textForLanguage(language, "Line", "直线");
    case CanvasView::Tool::Polyline:
        return textForLanguage(language, "Polyline", "折线");
    case CanvasView::Tool::Circle:
        return textForLanguage(language, "Circle", "圆");
    case CanvasView::Tool::Ellipse:
        return textForLanguage(language, "Ellipse", "椭圆");
    case CanvasView::Tool::Rectangle:
        return textForLanguage(language, "Rectangle", "矩形");
    case CanvasView::Tool::Polygon:
        return textForLanguage(language, "Polygon", "多边形");
    }
    return textForLanguage(language, "Unknown", "未知");
}

} // namespace

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    m_language = loadLanguage();
    setupUi();
    setupActions();
    setupToolbar();
    setupMenus();
    connectSignals();
    setLanguage(m_language);
    statusBar()->showMessage(textForLanguage(m_language, "Ready", "就绪"));
}

AppLanguage MainWindow::loadLanguage() const {
    const QSettings settings;
    const QString value = settings.value("ui/language", "zh-CN").toString();
    return value == "en" ? AppLanguage::English : AppLanguage::SimplifiedChinese;
}

void MainWindow::saveLanguage() const {
    QSettings settings;
    settings.setValue("ui/language", m_language == AppLanguage::English ? "en" : "zh-CN");
}

void MainWindow::setLanguage(AppLanguage language) {
    m_language = language;
    saveLanguage();

    m_canvasView->setLanguage(language);
    m_propertyPanel->setLanguage(language);
    m_tutorialDialog->setLanguage(language);

    if (m_englishAction != nullptr) {
        m_englishAction->setChecked(language == AppLanguage::English);
    }
    if (m_simplifiedChineseAction != nullptr) {
        m_simplifiedChineseAction->setChecked(language == AppLanguage::SimplifiedChinese);
    }

    retranslateUi();
    statusBar()->showMessage(textForLanguage(m_language, "Language updated.", "界面语言已更新。"), 2500);
}

void MainWindow::setupUi() {
    resize(1400, 900);
    setMinimumSize(1100, 720);

    m_canvasView = new CanvasView(this);
    setCentralWidget(m_canvasView);

    m_propertyPanel = new PropertyPanel(this);
    m_propertyDock = new QDockWidget(this);
    m_propertyDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    m_propertyDock->setWidget(m_propertyPanel);
    addDockWidget(Qt::RightDockWidgetArea, m_propertyDock);

    m_tutorialDialog = new TutorialDialog(this);
}

void MainWindow::setupActions() {
    m_openAction = new QAction(this);
    m_saveAction = new QAction(this);
    m_saveAsAction = new QAction(this);
    m_exportAction = new QAction(this);
    m_exitAction = new QAction(this);
    m_deleteAction = new QAction(this);
    m_copyAction = new QAction(this);
    m_pasteAction = new QAction(this);
    m_clearAction = new QAction(this);
    m_showTutorialAction = new QAction(this);
    m_englishAction = new QAction(this);
    m_simplifiedChineseAction = new QAction(this);

    m_openAction->setShortcut(QKeySequence::Open);
    m_saveAction->setShortcut(QKeySequence::Save);
    m_saveAsAction->setShortcut(QKeySequence::SaveAs);
    m_deleteAction->setShortcut(QKeySequence::Delete);
    m_copyAction->setShortcut(QKeySequence::Copy);
    m_pasteAction->setShortcut(QKeySequence::Paste);
    m_exitAction->setShortcut(QKeySequence::Quit);

    m_toolActionGroup = new QActionGroup(this);
    m_toolActionGroup->setExclusive(true);

    m_languageActionGroup = new QActionGroup(this);
    m_languageActionGroup->setExclusive(true);
    m_englishAction->setCheckable(true);
    m_simplifiedChineseAction->setCheckable(true);
    m_languageActionGroup->addAction(m_englishAction);
    m_languageActionGroup->addAction(m_simplifiedChineseAction);
}

void MainWindow::setupMenus() {
    m_fileMenu = menuBar()->addMenu(QString());
    m_fileMenu->addAction(m_openAction);
    m_fileMenu->addAction(m_saveAction);
    m_fileMenu->addAction(m_saveAsAction);
    m_fileMenu->addAction(m_exportAction);
    m_fileMenu->addSeparator();
    m_fileMenu->addAction(m_exitAction);

    m_editMenu = menuBar()->addMenu(QString());
    m_editMenu->addAction(m_copyAction);
    m_editMenu->addAction(m_pasteAction);
    m_editMenu->addAction(m_deleteAction);
    m_editMenu->addAction(m_clearAction);

    m_toolMenu = menuBar()->addMenu(QString());
    for (QAction* action : m_toolActionGroup->actions()) {
        m_toolMenu->addAction(action);
    }

    m_tutorialMenu = menuBar()->addMenu("Tutorial");
    m_tutorialMenu->addAction(m_showTutorialAction);
    m_tutorialMenu->addSeparator();
    m_languageMenu = m_tutorialMenu->addMenu(QString());
    m_languageMenu->addAction(m_englishAction);
    m_languageMenu->addAction(m_simplifiedChineseAction);
}

void MainWindow::setupToolbar() {
    m_toolBar = addToolBar(QString());
    m_toolBar->setMovable(false);

    m_toolBar->addAction(createToolAction(CanvasView::Tool::Select));
    m_toolBar->addAction(createToolAction(CanvasView::Tool::Point));
    m_toolBar->addAction(createToolAction(CanvasView::Tool::Line));
    m_toolBar->addAction(createToolAction(CanvasView::Tool::Polyline));
    m_toolBar->addAction(createToolAction(CanvasView::Tool::Circle));
    m_toolBar->addAction(createToolAction(CanvasView::Tool::Ellipse));
    m_toolBar->addAction(createToolAction(CanvasView::Tool::Rectangle));
    m_toolBar->addAction(createToolAction(CanvasView::Tool::Polygon));
    m_toolBar->addSeparator();
    m_toolBar->addAction(m_deleteAction);
    m_toolBar->addAction(m_copyAction);
    m_toolBar->addAction(m_pasteAction);
    m_toolBar->addAction(m_openAction);
    m_toolBar->addAction(m_saveAction);
    m_toolBar->addAction(m_clearAction);

    if (!m_toolActionGroup->actions().isEmpty()) {
        m_toolActionGroup->actions().first()->setChecked(true);
    }
}

void MainWindow::connectSignals() {
    connect(m_openAction, &QAction::triggered, this, &MainWindow::openDocument);
    connect(m_saveAction, &QAction::triggered, this, [this]() { saveDocument(); });
    connect(m_saveAsAction, &QAction::triggered, this, [this]() { saveDocumentAs(); });
    connect(m_exportAction, &QAction::triggered, this, &MainWindow::exportImage);
    connect(m_exitAction, &QAction::triggered, this, &QWidget::close);
    connect(m_showTutorialAction, &QAction::triggered, this, &MainWindow::showTutorial);
    connect(m_deleteAction, &QAction::triggered, m_canvasView, &CanvasView::deleteSelectedItem);
    connect(m_copyAction, &QAction::triggered, m_canvasView, &CanvasView::copySelectedItem);
    connect(m_pasteAction, &QAction::triggered, m_canvasView, &CanvasView::pasteCopiedItem);
    connect(m_clearAction, &QAction::triggered, this, [this]() {
        m_canvasView->clearCanvas();
        m_currentFilePath.clear();
        updateWindowTitle();
    });

    connect(m_canvasView, &CanvasView::selectedShapeChanged, this, [this](ShapeItem* item) {
        if (item != nullptr) {
            m_propertyPanel->setShapeData(item->shapeData());
        } else {
            m_propertyPanel->clearSelection();
        }
    });

    connect(m_canvasView, &CanvasView::statusMessageChanged, this,
            [this](const QString& message) { statusBar()->showMessage(message, 2500); });

    connect(m_propertyPanel, &PropertyPanel::shapeEdited, m_canvasView, &CanvasView::updateSelectedShape);
    connect(m_englishAction, &QAction::triggered, this, [this]() { setLanguage(AppLanguage::English); });
    connect(m_simplifiedChineseAction, &QAction::triggered, this,
            [this]() { setLanguage(AppLanguage::SimplifiedChinese); });
}

void MainWindow::retranslateUi() {
    m_fileMenu->setTitle(textForLanguage(m_language, "File", "文件"));
    m_editMenu->setTitle(textForLanguage(m_language, "Edit", "编辑"));
    m_toolMenu->setTitle(textForLanguage(m_language, "Tools", "工具"));
    m_tutorialMenu->setTitle("Tutorial");
    m_languageMenu->setTitle(textForLanguage(m_language, "Language", "语言"));

    m_openAction->setText(textForLanguage(m_language, "Open", "打开"));
    m_saveAction->setText(textForLanguage(m_language, "Save", "保存"));
    m_saveAsAction->setText(textForLanguage(m_language, "Save As", "另存为"));
    m_exportAction->setText(textForLanguage(m_language, "Export Image", "导出图片"));
    m_exitAction->setText(textForLanguage(m_language, "Exit", "退出"));
    m_deleteAction->setText(textForLanguage(m_language, "Delete", "删除"));
    m_copyAction->setText(textForLanguage(m_language, "Copy", "复制"));
    m_pasteAction->setText(textForLanguage(m_language, "Paste", "粘贴"));
    m_clearAction->setText(textForLanguage(m_language, "Clear Canvas", "清空画布"));
    m_showTutorialAction->setText(textForLanguage(m_language, "Operation Manual", "操作手册"));
    m_englishAction->setText("English");
    m_simplifiedChineseAction->setText(QString::fromUtf8("简体中文"));

    for (QAction* action : m_toolActionGroup->actions()) {
        const QVariant data = action->data();
        if (data.isValid()) {
            action->setText(toolLabel(static_cast<CanvasView::Tool>(data.toInt()), m_language));
        }
    }

    m_propertyDock->setWindowTitle(textForLanguage(m_language, "Properties", "属性"));
    m_toolBar->setWindowTitle(textForLanguage(m_language, "Tools", "工具"));
    updateWindowTitle();
}

void MainWindow::updateWindowTitle() {
    const QString fileName = m_currentFilePath.isEmpty() ? textForLanguage(m_language, "Untitled", "未命名")
                                                         : QFileInfo(m_currentFilePath).fileName();
    setWindowTitle(QString("%1 - %2").arg(fileName, textForLanguage(m_language, "SVG Editor", "SVG 编辑器")));
}

void MainWindow::showTutorial() {
    m_tutorialDialog->setLanguage(m_language);
    m_tutorialDialog->exec();
}

QAction* MainWindow::createToolAction(CanvasView::Tool tool) {
    QAction* action = new QAction(this);
    action->setCheckable(true);
    action->setData(static_cast<int>(tool));
    m_toolActionGroup->addAction(action);

    connect(action, &QAction::triggered, this, [this, tool]() { m_canvasView->setTool(tool); });

    return action;
}

bool MainWindow::saveToPath(const QString& filePath) {
    QString errorMessage;
    if (!FileManager::saveToFile(filePath, m_canvasView->documentData(), &errorMessage)) {
        QMessageBox::warning(this, textForLanguage(m_language, "Save Failed", "保存失败"), errorMessage);
        return false;
    }

    m_currentFilePath = filePath;
    updateWindowTitle();
    statusBar()->showMessage(textForLanguage(m_language, "File saved.", "文件已保存。"), 2500);
    return true;
}

bool MainWindow::saveDocument() {
    if (m_currentFilePath.isEmpty()) {
        return saveDocumentAs();
    }

    return saveToPath(m_currentFilePath);
}

bool MainWindow::saveDocumentAs() {
    const QString filePath = QFileDialog::getSaveFileName(
        this, textForLanguage(m_language, "Save Vector Document", "保存矢量图文件"),
        m_currentFilePath.isEmpty() ? "drawing.vgjson" : m_currentFilePath,
        textForLanguage(m_language, "Vector JSON (*.vgjson *.json)", "矢量 JSON 文件 (*.vgjson *.json)"));

    if (filePath.isEmpty()) {
        return false;
    }

    return saveToPath(filePath);
}

void MainWindow::openDocument() {
    const QString filePath = QFileDialog::getOpenFileName(
        this, textForLanguage(m_language, "Open Vector Document", "打开矢量图文件"), QString(),
        textForLanguage(m_language, "Vector JSON (*.vgjson *.json)", "矢量 JSON 文件 (*.vgjson *.json)"));
    if (filePath.isEmpty()) {
        return;
    }

    QString errorMessage;
    const std::optional<DocumentData> document = FileManager::loadFromFile(filePath, &errorMessage);
    if (!document.has_value()) {
        QMessageBox::warning(this, textForLanguage(m_language, "Open Failed", "打开失败"), errorMessage);
        return;
    }

    m_canvasView->loadDocument(*document);
    m_currentFilePath = filePath;
    updateWindowTitle();
    statusBar()->showMessage(textForLanguage(m_language, "File loaded.", "文件已加载。"), 2500);
}

void MainWindow::exportImage() {
    const QString filePath =
        QFileDialog::getSaveFileName(this, textForLanguage(m_language, "Export Image", "导出图片"), "canvas.png",
                                     textForLanguage(m_language, "PNG Image (*.png)", "PNG 图片 (*.png)"));
    if (filePath.isEmpty()) {
        return;
    }

    QString errorMessage;
    if (!m_canvasView->exportImage(filePath, &errorMessage)) {
        QMessageBox::warning(this, textForLanguage(m_language, "Export Failed", "导出失败"), errorMessage);
        return;
    }

    statusBar()->showMessage(textForLanguage(m_language, "Image exported.", "图片已导出。"), 2500);
}
