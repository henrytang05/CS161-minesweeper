#include "GameBoardPage.h"

#include "GameBoard/GameBoard.h"
#include "Session/Session.h"
#include "Square/Square.h"
#include "Style/Style.h"
#include "Timer/Timer.h"
GameBoardPage::GameBoardPage(QStackedWidget* parent, int level) : QWidget(parent) {
    setupGameBoardPage(level);
}
GameBoardPage::~GameBoardPage() {}
void GameBoardPage::setupGameBoardPage(int level) {
    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    Board = new GameBoard(this, level);
    replayButton = new QPushButton("Replay", this);
    timer = new Timer(this);
    styleButton(replayButton, "12D9C4", true);

    announcementLabel = new QLabel("Announcement", this);
    announcementLabel->setAlignment(Qt::AlignVCenter);
    styleLabel(announcementLabel, "DBD8AE", 20);
    announcementLabel->hide();

    QVBoxLayout* rightLayout = new QVBoxLayout(this);
    rightLayout->addWidget(announcementLabel);
    rightLayout->addStretch();
    rightLayout->addWidget(timer);
    rightLayout->addStretch();
    rightLayout->addWidget(replayButton);

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
void GameBoardPage::reavealAllBombs() {
    auto& board = Session::GetBoard();

    for (auto& squareRow : board) {
        for (auto& square : squareRow) {
            if (dynamic_cast<Mine_Square*>(square) != nullptr) {
                square->changeState(Square::STATE::Revealed);
            }
        }
    }
}
void GameBoardPage::victoryAnnoucement(bool won) {
    timer->stopTimer();
    this->reavealAllBombs();
    auto& board = Session::GetBoard();

    if (won) {
        announcementLabel->setText("You won!");
    } else {
        announcementLabel->setText("You lost!");
    }
    announcementLabel->show();
    for (auto& squareRow : board) {
        for (auto& square : squareRow) {
            square->setEnabled(false);
        }
    }
}
