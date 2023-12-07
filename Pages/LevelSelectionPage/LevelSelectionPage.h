#ifndef LEVEL_SELECTION_PAGE_H
#define LEVEL_SELECTION_PAGE_H
#include <QBoxLayout>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QInputDialog>
#include <QLabel>
#include <QPushButton>
#include <QStackedWidget>

class LevelSelectionPage : public QWidget {
   public:
    enum class DIFFICULTY : char { Beginner, Intermediate, Expert, Custom };
    Q_OBJECT
   public:
    LevelSelectionPage(QStackedWidget* parent = nullptr);
    ~LevelSelectionPage();
    void setupLevelSelectionPage();
   signals:
    void backClicked();
    void levelSelected(DIFFICULTY);
   public slots:
    void customLevelSelection();
};
#endif