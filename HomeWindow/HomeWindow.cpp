#include "HomeWindow.h"
// void Pages::newGameSlot() { emit newGameClicked(); }
// #include "../Button/Button.h"

// void HomeWindow::setupLevelSelectionPage() {}
// void HomeWindow::resumeGame() {}
// void HomeWindow::startGame(int level) {

//     QHBoxLayout* mainLayout = new ("layout") QHBoxLayout();
//     mainLayout->addWidget(gameBoard->mainGrid);

//     this->setFixedSize(
//         GameBoard::BOARD_SIZE * Square::CELL_SIZE + 200,
//         GameBoard::BOARD_SIZE * Square::CELL_SIZE + 100
//     );
//     gameBoard->replayButton = new ("replay button") QPushButton("Replay", gameBoard);
//     gameBoard->replayButton->setGeometry(
//         GameBoard::BOARD_SIZE * Square::CELL_SIZE + 50, 20, 100, 50
//     );

//     styleButton(gameBoard->replayButton, "FFF6F6");
//     connect(gameBoard->replayButton, &QPushButton::clicked, this, [this]() {
//         this->restartGame(gameBoard);
//     });
//     mainLayout->addWidget(gameBoard->replayButton);
//     gameBoard->setLayout(mainLayout);
//     stackedWidget->addWidget(gameBoard);
//     stackedWidget->setCurrentWidget(gameBoard);
// }
// void HomeWindow::restartGame(GameBoard* gameBoard) {
//     stackedWidget->setCurrentWidget(homePage);
//     delete gameBoard;
//     gameBoard = nullptr;
//     Memory::PrintMemory();
// }