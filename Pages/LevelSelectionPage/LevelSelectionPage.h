#ifndef LEVEL_SELECTION_PAGE_H
#define LEVEL_SELECTION_PAGE_H
#include <QBoxLayout>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QPushButton>
#include <QStackedWidget>

class LevelSelectionPage : public QWidget {
    Q_OBJECT
   public:
    LevelSelectionPage(QStackedWidget* parent = nullptr);
    ~LevelSelectionPage();
    void setupLevelSelectionPage();
   signals:
    void backClicked();
    void levelSelected(int difficulty);
   public slots:
    void customLevelSelection()
};
#endif