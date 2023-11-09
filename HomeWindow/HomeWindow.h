#ifndef MENU_H
#define MENU_H

#include <QBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QStackedWidget>
#include <QWidget>
#include <string>

#include "../GameBoard/GameBoard.h"
#include "../Style/Style.h"

class HomeWindow : public QMainWindow {
   public:
    HomeWindow(QMainWindow* parent = nullptr) : QMainWindow(parent) {
        stackedWidget = new QStackedWidget(this);
        setupWindowTitle("Main Window", 500, 500, this, "245344");
        setupHomeWindow();
        setCentralWidget(stackedWidget);

        setupLevelSelection();
        stackedWidget->addWidget(homePage);
        stackedWidget->addWidget(levelSelectionPage);
        stackedWidget->setCurrentWidget(homePage);
    }
    ~HomeWindow() {
        delete homePage;
        delete levelSelectionPage;
        delete stackedWidget;
    }
    void setupHomeWindow();
    void setLevel(int level);

   private slots:
    void setupLevelSelection();
    void resumeGame();
    void startGame(int level);
    void restartGame(GameBoard* gameBoard);

   private:
    QStackedWidget* stackedWidget;
    QWidget* homePage;
    QWidget* levelSelectionPage;
    GameBoard* gameBoard;
    QPushButton* replayButton;
};

#endif