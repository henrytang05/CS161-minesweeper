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
    mainGridLayout = new QGridLayout(this);
}
GameboardPage::~GameboardPage() {}

void GameboardPage::setupGameboard() {
    // layoutCollection.clear();
    int cell = Session::GetCellSize();
    int row = Session::GetRow();
    int col = Session::GetColumn();
    gameboard->setGeometry(QRect(QPoint(50, 50), QPoint(50 + cell * col, 50 + cell * row))
    );
    styleTimer(timer);
    timer->setGeometry(cell * row + 100, cell * col + 100, 200, 200);
    styleButton(replayButton, "12D9C4", true);

    announcementLabel->setAlignment(Qt::AlignVCenter);
    styleLabel(announcementLabel, "DBD8AE", 20);
    announcementLabel->hide();

    gameboard->resize(cell * row, cell * col);

    QObject::connect(
        &Session::GetInstance(), &Session::result, this, &victoryAnnoucement
    );
}

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

    auto& board = Session::GetBoard();

    setupGameboard();

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
