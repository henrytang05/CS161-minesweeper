#include "GameboardPage.h"

#include "Session/Session.h"
#include "Square/Square.h"
#include "Style/Style.h"
#include "Timer/Timer.h"
GameboardPage::GameboardPage(QStackedWidget* parent) : QWidget(parent) {
    gameboard = new QWidget(this);
    replayButton = new QPushButton("Replay", this);
    announcementLabel = new QLabel(this);
    timer = new QLabel("00:00", this);
    QHBoxLayout* mainLayout = new QHBoxLayout(this);

    styleTimer(timer);
    styleButton(replayButton, "12D9C4", true);

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

    mainLayout->addWidget(gameboard);
    mainLayout->addStretch();
    mainLayout->addLayout(rightLayout);

    mainLayout->addStretch();
    setLayout(mainLayout);

    QObject::connect(
        &Session::GetInstance(), &Session::result, this, &victoryAnnoucement
    );
}
GameboardPage::~GameboardPage() {}

void GameboardPage::reavealAllBombs() {
    auto& board = Session::GetBoard();

    for (auto& squareRow : board) {
        for (auto& square : squareRow) {
            if (square->type == Square_Type::Mine) {
                square->changeState(Square::STATE::Revealed);
            }
        }
    }
}
void GameboardPage::victoryAnnoucement(Result won) {
    auto& board = Session::GetBoard();
    Session::GetInstance().stopTimer();
    if (won) {
        announcementLabel->setText("You won!");
    } else {
        this->reavealAllBombs();
        announcementLabel->setText("You lost!");
    }
    announcementLabel->show();
    for (auto& squareRow : board) {
        for (auto& square : squareRow) {
            square->setEnabled(false);
        }
    }
}
void GameboardPage::handleNewGameStart() {
    // TODO : Get Session and stuffs
    QGridLayout* mainGridLayout = new QGridLayout(this);
    auto& board = Session::GetBoard();
    gameboard->setFixedSize(
        Session::GetCellSize() * Session::GetColumn(),
        Session::GetCellSize() * Session::GetRow()
    );

    mainGridLayout = new QGridLayout(this);

    for (auto& row : board) {
        for (auto& square : row) {
            mainGridLayout->addWidget(square, square->row, square->col);
        }
    }
    gameboard->setLayout(mainGridLayout);
    connect(Session::GetTimer(), &Timer::timerUpdated, timer, [this]() {
        timer->setText(Session::GetTimer()->elapsedTime.toString("mm:ss"));
    });
}
