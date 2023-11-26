#ifndef LEVEL_SELECTION_PAGE_H
#define LEVEL_SELECTION_PAGE_H
#include <QBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QStackedWidget>
#include <QWidget>
#include <iostream>
#include <string>

#include "../../Memory/Memory.h"
#include "../../Style/Style.h"
class LevelSelectionPage : public QWidget {
    Q_OBJECT
   public:
    LevelSelectionPage(QStackedWidget* parent = nullptr) { setupLevelSelectionPage(); }
    ~LevelSelectionPage() {}
    void setupLevelSelectionPage();
   signals:
    void backClicked();
    void levelSelected(int difficulty);
};
#endif