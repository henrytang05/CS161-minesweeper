#include "MainWindow.h"

#include "GameBoard/GameBoard.h"
#include "GameBoardPage/GameBoardPage.h"
#include "HomePage/HomePage.h"
#include "LevelSelectionPage/LevelSelectionPage.h"
#include "Session/Session.h"
#include "Square/Square.h"
#include "Style/Style.h"
MainWindow::MainWindow(double width, double height, QMainWindow* parent)
    : QMainWindow(parent) {
    stackedPages = new Pages(this);
    this->windowWidth = width;
    this->windowHeight = height;
    styleWindow("Main Window", windowWidth, windowHeight, this, "E36387");
    setCentralWidget(stackedPages);
    makeconnection();
}
MainWindow::~MainWindow() {
    delete stackedPages;
    stackedPages = nullptr;
}
Pages::Pages(QWidget* parent) : QStackedWidget(parent) { setupPages(); }
Pages::~Pages() {
    delete homePage;
    delete levelSelectionPage;
    delete gameBoardPage;
    homePage = nullptr;
    levelSelectionPage = nullptr;
    gameBoardPage = nullptr;
}

void MainWindow::makeconnection() {
    // QObject::connect(stackedPages, Pages::newGameSignal, this, [this]() {
    //     double windowWidth = Square::CELL_SIZE * GameBoard::BOARD_SIZE + 300;
    //     double windowHeight = Square::CELL_SIZE * GameBoard::BOARD_SIZE + 100;
    //     // this->setFixedSize(windowWidth, windowHeight);
    // });
    // QObject::connect(stackedPages, Pages::replaySignal, this, [this]() {
    //     this->setFixedSize(520, 420);
    // });
}
void Pages::makeconnection() {
    // QObject::connect(homePage, HomePage::newGameClicked, this, &Pages::newGameSignal);
    QObject::connect(homePage, HomePage::newGameClicked, this, [this]() {
        setCurrentWidget(levelSelectionPage);
    });
    QObject::connect(homePage, HomePage::resumeGameClicked, this, &Pages::resumeGameSlot);
    QObject::connect(
        levelSelectionPage, LevelSelectionPage::levelSelected, this,
        &Pages::startNewGameSlot
    );
    QObject::connect(levelSelectionPage, LevelSelectionPage::backClicked, this, [this]() {
        setCurrentWidget(homePage);
        emit replaySignal();
    });
}

void Pages::startNewGameSlot() {
    gameBoardPage = new GameBoardPage(this);
    this->addWidget(gameBoardPage);
    setCurrentWidget(gameBoardPage);
    connect(gameBoardPage, &GameBoardPage::replayClicked, this, &Pages::replayGameSlot);
    emit newGameSignal();
}
void Pages::replayGameSlot() {
    delete gameBoardPage;
    gameBoardPage = nullptr;
    Session::ResetInstance().serialize();
    this->setCurrentWidget(levelSelectionPage);
}
void Pages::resumeGameSlot() {
    Session::GetInstance().deserialize();
    startNewGameSlot();
}
void Pages::setupPages() {
    homePage = new HomePage(this);
    levelSelectionPage = new LevelSelectionPage(this);
    makeconnection();
    this->addWidget(homePage);
    this->addWidget(levelSelectionPage);
    this->setCurrentWidget(homePage);
}