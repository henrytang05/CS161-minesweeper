#ifndef LEVEL_SELECTION_PAGE_H
#define LEVEL_SELECTION_PAGE_H
#include <QBoxLayout>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QGuiApplication>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QScreen>
#include <QStackedWidget>
class LevelSelectionPage : public QWidget {
    Q_OBJECT
   public:
    LevelSelectionPage(QStackedWidget* parent = nullptr);
    ~LevelSelectionPage();
    void setupLevelSelectionPage();
   signals:
    void backClicked();
    void levelSelected();
   public slots:
    void customLevelSelection(int&, int&, int&);
};
#endif