#ifndef MENU_H
#define MENU_H

#include <QBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QResizeEvent>
#include <QStackedWidget>
#include <QWidget>
#include <iostream>
#include <string>

#include "../Memory/Memory.h"
#include "../Pages/GameBoardPage/GameBoardPage/GameBoardPage.h"
#include "../Pages/HomePage/HomePage.h"
#include "../Pages/LevelSelectionPage/LevelSelectionPage.h"
#include "../Style/Style.h"
class Pages : public QStackedWidget {
    Q_OBJECT
   public:
    Pages(QWidget* parent = nullptr) : QStackedWidget(parent) {
        homePage = new ("HomePage") HomePage(this);
        levelSelectionPage = new ("Level Selection Page") LevelSelectionPage(this);
        connect(homePage, &HomePage::newGameClicked, this, [this]() {
            setCurrentWidget(levelSelectionPage);
        });

        connect(levelSelectionPage, &LevelSelectionPage::easyClicked, this, [this]() {
            gameBoardPage = new ("Game Board Page") GameBoardPage(this, 1);
            this->addWidget(gameBoardPage);
            setCurrentWidget(gameBoardPage);
        });
        connect(levelSelectionPage, &LevelSelectionPage::mediumClicked, this, [this]() {
            gameBoardPage = new ("Game Board Page") GameBoardPage(this, 2);
            this->addWidget(gameBoardPage);
            setCurrentWidget(gameBoardPage);
        });
        connect(levelSelectionPage, &LevelSelectionPage::hardClicked, this, [this]() {
            gameBoardPage = new ("Game Board Page") GameBoardPage(this, 3);
            this->addWidget(gameBoardPage);
            setCurrentWidget(gameBoardPage);
        });

        this->addWidget(homePage);
        this->addWidget(levelSelectionPage);
        // this->addWidget(gameBoardPage);
        this->setCurrentWidget(homePage);
    }
    //    public slots:
    //     void resumeGameSlot();

   private:
    HomePage* homePage;
    LevelSelectionPage* levelSelectionPage;
    GameBoardPage* gameBoardPage;
};

class HomeWindow : public QMainWindow {
    Q_OBJECT
   public:
    HomeWindow(QMainWindow* parent = nullptr) : QMainWindow(parent) {
        stackedPages = new Pages(this);
        styleWindow("Main Window", 800, 500, this, "245344");
        setCentralWidget(stackedPages);
    }
    ~HomeWindow() { delete stackedPages; }

    //     void setupLevelSelectionPage();
    //     void setupGameBoardPage();
    void resumeGame();
    //     void startGame(int level);
    //     void restartGame(GameBoard* gameBoard);
    //    protected:
    //     void resizeEvent(QResizeEvent* event) override {
    //         // Desired aspect ratio
    //         float aspectRatio = 4.0f / 3.0f;

    //         // Current size
    //         QSize size = event->size();

    //         // Adjust width or height to maintain the aspect ratio
    //         if (size.width() / (float)size.height() > aspectRatio) {
    //             size.setWidth(size.height() * aspectRatio);
    //         } else {
    //             size.setHeight(size.width() / aspectRatio);
    //         }

    //         // Set the adjusted size
    //         resize(size);
    //     }

   private:
    Pages* stackedPages;
};

#endif