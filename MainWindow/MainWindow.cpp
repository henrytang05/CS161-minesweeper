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
        levelSelectionPage, LevelSelectionPage::levelSelected, gameboardPage,
        &GameboardPage::handleNewGameStart
    );
    QObject::connect(
        levelSelectionPage, LevelSelectionPage::levelSelected, this,
        &MainWindow::startNewGameSlot
    );

    QObject::connect(
        gameboardPage->replayButton, &QPushButton::clicked, this,
        &MainWindow::replayGameSlot
    );
    QObject::connect(
        levelSelectionPage->resume, &QPushButton::clicked, this,
        &MainWindow::resumeGameSlot
    );
    // TODO : change resume to high score
}
void MainWindow::startNewGameSlot() {
    // Session already prepared
    Pages->setCurrentWidget(gameboardPage);
    Session::GetInstance().startTimer();
}
void MainWindow::replayGameSlot() {
    Session::StopSession();
    Session::ResetInstance();
    delete gameboardPage;
    gameboardPage = new GameboardPage(Pages);
    Pages->setCurrentWidget(levelSelectionPage);
}
void MainWindow::resumeGameSlot() {
    QFile file("save.dat");
    if (file.readAll().isEmpty()) {
        return;
    }
    Session::ResumeSession();
    gameboardPage = new GameboardPage(Pages);
    Pages->setCurrentWidget(gameboardPage);
}
