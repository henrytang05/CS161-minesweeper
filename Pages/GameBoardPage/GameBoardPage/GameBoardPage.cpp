#include "GameBoardPage.h"
void GameBoardPage::setupGameBoardPage(int level) {
    QHBoxLayout* mainLayout = new ("layout") QHBoxLayout(this);
    Board = new ("Game Board") GameBoard(this, level);
    replayButton = new ("Replay Button") QPushButton("Replay", this);
    styleButton(replayButton, "12D9C4", true);

    announcementLabel = new ("Announcement Label") QLabel("Announcement", this);
    announcementLabel->setAlignment(Qt::AlignVCenter);
    styleLabel(announcementLabel, "DBD8AE", 20);
    announcementLabel->hide();

    QVBoxLayout* rightLayout = new ("rightLayout") QVBoxLayout(this);
    rightLayout->addWidget(announcementLabel);
    rightLayout->addSpacing(10);
    rightLayout->addWidget(replayButton);

    mainLayout->addWidget(Board);
    mainLayout->addStretch();
    mainLayout->addLayout(rightLayout);

    QObject::connect(replayButton, &QPushButton::clicked, this, &replayClicked);
    QObject::connect(Board, &GameBoard::result, this, &GameBoardPage::victoryAnnoucement);

    mainLayout->addStretch();
    setLayout(mainLayout);
}
void GameBoardPage::victoryAnnoucement(bool won) {
    if (won) {
        announcementLabel->setText("You won!");
    } else {
        announcementLabel->setText("You lost!");
    }

    announcementLabel->setStyleSheet("background-color: #12D9C4; border-radius: 15px ;");
    announcementLabel->setFixedHeight(50);
    announcementLabel->show();
    for (auto& squareRow : Board->grid) {
        for (auto& square : squareRow) {
            square->setEnabled(false);
        }
    }
}