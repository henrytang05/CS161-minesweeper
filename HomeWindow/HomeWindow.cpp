#include "HomeWindow.h"

void HomeWindow::makeconnection() {
    QObject::connect(stackedPages, Pages::newGameSignal, this, [this]() {
        double windowWidth = Square::CELL_SIZE * GameBoard::BOARD_SIZE + 300;
        double windowHeight = Square::CELL_SIZE * GameBoard::BOARD_SIZE + 100;
        this->setFixedSize(windowWidth, windowHeight);
    });
    QObject::connect(stackedPages, Pages::replaySignal, this, [this]() {
        this->setFixedSize(520, 420);
    });
}
void Pages::makeconnection() {
    // QObject::connect(homePage, HomePage::newGameClicked, this, &Pages::newGameSignal);
    QObject::connect(homePage, HomePage::newGameClicked, this, [this]() {
        setCurrentWidget(levelSelectionPage);
    });
    QObject::connect(
        levelSelectionPage, LevelSelectionPage::levelSelected, this,
        &Pages::startNewGameSlot
    );
    QObject::connect(levelSelectionPage, LevelSelectionPage::backClicked, this, [this]() {
        setCurrentWidget(homePage);
        emit replaySignal();
    });
}

void Pages::startNewGameSlot(int difficulty) {
    createGameBoardPage(difficulty);
    this->addWidget(gameBoardPage);
    emit newGameSignal();
    QObject::connect(gameBoardPage, GameBoardPage::replayClicked, this, &replayGameSlot);
    this->setCurrentWidget(gameBoardPage);
}
void Pages::replayGameSlot() {
    delete gameBoardPage;
    emit replaySignal();
    this->setCurrentWidget(levelSelectionPage);
}
void Pages::createGameBoardPage(int difficulty) {
    gameBoardPage = new GameBoardPage(this, difficulty);
    this->addWidget(gameBoardPage);
    setCurrentWidget(gameBoardPage);
    connect(gameBoardPage, &GameBoardPage::replayClicked, this, &Pages::replayGameSlot);
}
void Pages::setupPages() {
    homePage = new HomePage(this);
    levelSelectionPage = new LevelSelectionPage(this);
    makeconnection();
    this->addWidget(homePage);
    this->addWidget(levelSelectionPage);
    this->setCurrentWidget(homePage);
}