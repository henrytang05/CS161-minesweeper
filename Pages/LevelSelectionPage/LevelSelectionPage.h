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
class MainWindow;
class LevelSelectionPage : public QWidget {
    Q_OBJECT

   public:
    LevelSelectionPage(QStackedWidget* parent = nullptr);
    ~LevelSelectionPage();

   private:
    void setupLevelSelectionPage();
    void setupNewGame(int row, int col, int mine);

   private:
    QPushButton* resume;
    QPushButton* easy;
    QPushButton* medium;
    QPushButton* hard;
    QPushButton* custom;
    QPushButton* back;

   public slots:
    void customLevelSelection(int&, int&, int&);

   signals:
    void backClicked();
    void levelSelected();
    void resumeClicked();
};
#endif