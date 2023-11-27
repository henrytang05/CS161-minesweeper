#include "GameBoardPage.h"

#include "../GameBoard/GameBoard.h"
#include "../Square/Square.h"
GameBoardPage::GameBoardPage(QStackedWidget* parent, int level) : QWidget(parent) {
    setupGameBoardPage(level);
}
GameBoardPage::~GameBoardPage() {}
void GameBoardPage::setupGameBoardPage(int level) {
    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    Board = new GameBoard(this, level);
    replayButton = new QPushButton("Replay", this);
    styleButton(replayButton, "12D9C4", true);

    announcementLabel = new QLabel("Announcement", this);
    announcementLabel->setAlignment(Qt::AlignVCenter);
    styleLabel(announcementLabel, "DBD8AE", 20);
    announcementLabel->hide();

    QVBoxLayout* rightLayout = new QVBoxLayout(this);
    QHBoxLayout* labelButtonLayout = new QHBoxLayout(this);
    labelButtonLayout->addWidget(announcementLabel);
    labelButtonLayout->addWidget(replayButton);
    rightLayout->addLayout(labelButtonLayout);
    rightLayout->addSpacing(10);

    mainLayout->addWidget(Board);
    mainLayout->addStretch();
    mainLayout->addLayout(rightLayout);

    QObject::connect(
        replayButton, &QPushButton::clicked, this, &GameBoardPage::replayClicked
    );
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

    // announcementLabel->setStyleSheet("background-color: #12D9C4; border-radius: 15px
    // ;"); announcementLabel->setFixedHeight(50);
    announcementLabel->show();
    for (auto& squareRow : Board->grid) {
        for (auto& square : squareRow) {
            square->setEnabled(false);
        }
    }
}