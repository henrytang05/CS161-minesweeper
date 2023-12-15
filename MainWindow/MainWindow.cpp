#include "MainWindow.h"

#include "GameboardPage/GameboardPage.h"
#include "HomePage/HomePage.h"
#include "LevelSelectionPage/LevelSelectionPage.h"
#include "Session/Session.h"
#include "Square/Square.h"
#include "Style/Style.h"

MainWindow::MainWindow(QMainWindow* parent) : QMainWindow(parent) {
    Session::GetInstance();
    Pages = new QStackedWidget(this);
    homePage = new HomePage(Pages);
    levelSelectionPage = new LevelSelectionPage(Pages);
    gameboardPage = new GameboardPage(Pages);

    Pages->addWidget(homePage);
    Pages->addWidget(levelSelectionPage);
    Pages->addWidget(gameboardPage);

    styleWindow("Main Window", this, "E36387");
    setCentralWidget(Pages);
    Pages->setCurrentWidget(homePage);
    makeConnection();
}
MainWindow::~MainWindow() {}
void MainWindow::makeConnection() {
    QObject::connect(homePage, HomePage::newGameButton, this, [this]() {
        Pages->setCurrentWidget(levelSelectionPage);
    });
    QObject::connect(
        levelSelectionPage, LevelSelectionPage::backClicked, Pages,
        [this]() { Pages->setCurrentWidget(homePage); }
    );
    QObject::connect(
        levelSelectionPage, LevelSelectionPage::levelSelected, this,
        &MainWindow::startNewGameSlot
    );

    QObject::connect(
        levelSelectionPage, LevelSelectionPage::levelSelected, gameboardPage,
        &GameboardPage::handleNewGameStart
    );
    QObject::connect(gameboardPage->replayButton, &QPushButton::clicked, this, [this]() {
        Pages->setCurrentWidget(levelSelectionPage);
        });
    // TODO : change resume to high score
    // TODO : move resume to level selection page
}
void MainWindow::startNewGameSlot() {
    // Session already prepared
    Pages->setCurrentWidget(gameboardPage);
    connect(
        gameboardPage, &GameboardPage::replayClicked, this, &MainWindow::replayGameSlot
    );
    Session::GetInstance().startTimer();
}
void MainWindow::replayGameSlot() {}
void MainWindow::resumeGameSlot() {}
