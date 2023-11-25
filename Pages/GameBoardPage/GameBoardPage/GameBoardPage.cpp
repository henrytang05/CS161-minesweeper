#include "GameBoardPage.h"
void GameBoardPage::setupGameBoardPage() {
    QHBoxLayout* mainLayout = new ("layout") QHBoxLayout(this);
    mainLayout->addWidget(Board);
    mainLayout->addStretch();
    mainLayout->addWidget(replayButton);
    mainLayout->addStretch();
    setLayout(mainLayout);
}