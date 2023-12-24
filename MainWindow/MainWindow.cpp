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

    styleWindow(this);

    setCentralWidget(Pages);
    Pages->setCurrentWidget(homePage);
    makeConnection();
}
MainWindow::~MainWindow() {
    Session::SaveHighScores();
    if (Session::GetState() == Session::State::Playing) Session::StopSession();
}
void MainWindow::makeConnection() {
    QObject::connect(homePage, &HomePage::newGameSignal, this, [this]() {
        Pages->setCurrentWidget(levelSelectionPage);
    });
    QObject::connect(
        homePage, &HomePage::resumeGameSignal, this, &MainWindow::resumeGameSlot
    );

    QObject::connect(homePage, &HomePage::exit, this, &QCoreApplication::quit);
    QObject::connect(
        gameboardPage, &GameboardPage::exitSignal, this, &QCoreApplication::quit
    );

    QObject::connect(
        levelSelectionPage, LevelSelectionPage::backClicked, Pages,
        [this]() { Pages->setCurrentWidget(homePage); }
    );
    QObject::connect(
        levelSelectionPage, LevelSelectionPage::levelSelected, this,
        &MainWindow::startNewGameSlot
    );
    // TODO : connect with a signal instead of the button
    QObject::connect(
        gameboardPage, &GameboardPage::newGameSignal, this, &MainWindow::endGameSlot
    );

    QObject::connect(
        levelSelectionPage, &LevelSelectionPage::resumeClicked, this,
        &MainWindow::resumeGameSlot
    );

    QObject::connect(
        &Session::GetInstance(), &Session::result, gameboardPage,
        &GameboardPage::victoryAnnoucement
    );
}
void MainWindow::startNewGameSlot() {
    Session::StartSession();
    gameboardPage->handleNewGameStart();
    Pages->setCurrentWidget(gameboardPage);
    Session::GetInstance().startTimer();
}
void MainWindow::endGameSlot() {
    Session::StopSession().ResetInstance();
    gameboardPage->cleanBoard();
    Pages->setCurrentWidget(levelSelectionPage);
}
void MainWindow::resumeGameSlot() {
    QFile file("Data/Session.dat");
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << file.errorString();
        return;
    }
    if (file.readAll().isEmpty()) {
        file.close();
        return;
    }
    file.seek(0);
    QDataStream in(&file);
    in >> Session::GetState();
    if (Session::GetState() != Session::State::Playing) {
        file.close();
        return;
    }
    Session::ResumeSession();
    gameboardPage->handleNewGameStart();
    gameboardPage->timer->setText(Session::GetElapsedTimeAsString());
    Pages->setCurrentWidget(gameboardPage);
    file.close();
}
