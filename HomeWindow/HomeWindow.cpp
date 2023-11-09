#include "HomeWindow.h"

#include "../Style/Style.h"
// #include "../Button/Button.h"

void HomeWindow::setupHomeWindow() {
    homePage = new QWidget;
    QVBoxLayout* layout = new QVBoxLayout;
    homePage->setLayout(layout);
    this->setCentralWidget(homePage);
    stackedWidget->addWidget(homePage);
    stackedWidget->setCurrentWidget(homePage);

    QLabel* titleLabel = new QLabel("MineSweeper");
    QLabel* titleWelcome = new QLabel("Welcome to");
    QPushButton* newGame = new QPushButton("New Game");
    QPushButton* Resume = new QPushButton("Resume Game");

    setupLabel(titleLabel, "DBD8AE");
    setupLabel(titleWelcome, "DBD8AE");

    setupButton(newGame, "FFF6F6");
    setupButton(Resume, "EAF4D3");
    connect(newGame, &QPushButton::clicked, this, [this]() {
        stackedWidget->setCurrentWidget(levelSelectionPage);
    });
    connect(Resume, &QPushButton::clicked, this, &HomeWindow::resumeGame);

    layout->addStretch();
    layout->addWidget(titleWelcome, 0, Qt::AlignCenter);
    layout->addSpacing(10);
    layout->addWidget(titleLabel, 0, Qt::AlignCenter);
    layout->addStretch();
    layout->addWidget(newGame, 0, Qt::AlignCenter);
    layout->addSpacing(20);
    layout->addWidget(Resume, 0, Qt::AlignCenter);
    layout->addStretch();
}

void HomeWindow::setupLevelSelection() {
    levelSelectionPage = new QWidget;
    QVBoxLayout* mainLayout = new QVBoxLayout();
    levelSelectionPage->setLayout(mainLayout);
    QLabel* label = new QLabel("Choose a level");
    QVBoxLayout* buttonLayout = new QVBoxLayout();

    mainLayout->addWidget(label, 0, Qt::AlignCenter);
    mainLayout->addLayout(buttonLayout);

    QPushButton* easy = new QPushButton("Easy");
    QPushButton* medium = new QPushButton("Medium");
    QPushButton* hard = new QPushButton("Hard");
    QPushButton* back = new QPushButton("Back");

    setupButton(easy, "FFF6F6");
    setupButton(medium, "FFF6F6");
    setupButton(hard, "FFF6F6");
    setupButton(back, "FFF6F6");

    setupLabel(label, "DBD8AE");
    buttonLayout->addWidget(easy, 0, Qt::AlignCenter);
    buttonLayout->addWidget(medium, 0, Qt::AlignCenter);
    buttonLayout->addWidget(hard, 0, Qt::AlignCenter);
    buttonLayout->addWidget(back, 0, Qt::AlignCenter);
    connect(back, &QPushButton::clicked, this, [this]() {
        stackedWidget->setCurrentWidget(homePage);
    });
    connect(easy, &QPushButton::clicked, this, [this]() { startGame(1); });
    connect(medium, &QPushButton::clicked, this, [this]() { startGame(2); });
    connect(hard, &QPushButton::clicked, this, [this]() { startGame(3); });
}
void HomeWindow::resumeGame() {}
void HomeWindow::startGame(int level) {
    gameBoard = new GameBoard(this, level);
    gameBoard->setupGameBoard();

    this->setFixedSize(
        GameBoard::BOARD_SIZE * GameBoard::CELL_SIZE + 200,
        GameBoard::BOARD_SIZE * GameBoard::CELL_SIZE + 100
    );
    replayButton = new QPushButton("Replay");
    replayButton->setGeometry(
        GameBoard::BOARD_SIZE * GameBoard::CELL_SIZE + 50, 20, 100, 50
    );

    setupButton(replayButton, "FFF6F6");
    connect(replayButton, &QPushButton::clicked, this, [this]() {
        this->restartGame(gameBoard);
    });
    QVBoxLayout* mainLayout = new QVBoxLayout(gameBoard);
    // QHBoxLayout* layout = new QHBoxLayout();
    mainLayout->addWidget(replayButton);
    mainLayout->addLayout(GameBoard::mainGrid);

    stackedWidget->addWidget(gameBoard);
    stackedWidget->setCurrentWidget(gameBoard);
}
void HomeWindow::restartGame(GameBoard* gameBoard) {
    stackedWidget->setCurrentWidget(homePage);
    delete gameBoard;
    gameBoard = nullptr;
}