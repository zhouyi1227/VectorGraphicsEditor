#pragma once

#include <QDialog>

#include "AppLanguage.h"

class QPushButton;
class QTextBrowser;

class TutorialDialog : public QDialog {
    Q_OBJECT

  public:
    explicit TutorialDialog(QWidget* parent = nullptr);

    void setLanguage(AppLanguage language);

  private:
    void setupUi();
    void retranslateUi();
    QString buildManualHtml() const;

    QTextBrowser* m_browser = nullptr;
    QPushButton* m_closeButton = nullptr;
    AppLanguage m_language = AppLanguage::SimplifiedChinese;
};
