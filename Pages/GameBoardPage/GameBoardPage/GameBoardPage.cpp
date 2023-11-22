#include "GameBoardPage.h"
void GameBoardPage::setupGameBoardPage() {
    Board = new ("Game Board") GameBoard();
    replayButton = new ("Replay Button") QPushButton("Replay");
    QHBoxLayout* mainLayout = new ("layout") QHBoxLayout();
    mainLayout->addWidget(Board);
    mainLayout->addWidget(replayButton);
    setLayout(mainLayout);
}