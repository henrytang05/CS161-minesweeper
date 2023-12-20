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
    QObject::connect(homePage, HomePage::resumeButton, this, &MainWindow::resumeGameSlot);
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
        gameboardPage->replayButton, &QPushButton::clicked, this, &MainWindow::endGameSlot
    );
    QObject::connect(
        levelSelectionPage->resume, &QPushButton::clicked, this,
        &MainWindow::resumeGameSlot
    );
    QObject::connect(
        &Session::GetInstance(), &Session::result, gameboardPage, &GameboardPage::result
    );

    // TODO : change resume to high score
}
void MainWindow::startNewGameSlot() {
    // Session already prepared
    Pages->setCurrentWidget(gameboardPage);
    Session::GetInstance().startTimer();
}
void MainWindow::endGameSlot() {
    Session::StopSession().serialize();
    Session::ResetInstance();
    gameboardPage->cleanBoard();
    Pages->setCurrentWidget(levelSelectionPage);
}
void MainWindow::resumeGameSlot() {
    QFile file("save.dat");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << file.errorString();
        return;
    }
    if (file.readAll().isEmpty()) {
        file.close();
        return;
    }
    Session::ResumeSession();
    gameboardPage->handleNewGameStart();
    Pages->setCurrentWidget(gameboardPage);
}
