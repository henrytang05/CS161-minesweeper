#include "GameboardPage.h"

#include "Session/Session.h"
#include "Square/Square.h"
#include "Style/Style.h"
#include "Timer/Timer.h"
GameboardPage::GameboardPage(QStackedWidget* parent) : QWidget(parent) {
    gameboard = new QWidget(this);
    replayButton = new QPushButton("Replay", this);
    timer = new QLabel("00:00", this);
    mainGridLayout = new QGridLayout(this);
    announcementLabel = new QLabel(this);
}
GameboardPage::~GameboardPage() {}

void GameboardPage::setupGameboard() {
    // layoutCollection.clear();
    double& cell = Session::GetCellSize();

    int row = Session::GetRow();
    int col = Session::GetColumn();
    announcementLabel->hide();

    gameboard->resize(cell * col, cell * row);
    int x = (parentWidget()->width() - gameboard->width()) / 2;
    int y = (parentWidget()->height() - gameboard->height()) / 2;
    styleTimer(timer);

    styleButton(replayButton, "12D9C4", true);
    gameboard->setGeometry(x, y, gameboard->width(), gameboard->height());

    timer->setGeometry(x - 50, y - 200, timer->width(), timer->height());
    styleLabel(announcementLabel, "DBD8AE", 20);
}

void GameboardPage::reavealAllBombs() {
    auto& board = Session::GetBoard();

    for (auto& squareRow : board) {
        for (auto& square : squareRow) {
            if (square->type == Square_Type::Mine &&
                square->state != Square::STATE::Flagged) {
                square->changeState(Square::STATE::Revealed);
            }
            square->setEnabled(false);
        }
    }
}
void GameboardPage::victoryAnnoucement(Result won) {
    auto& board = Session::GetBoard();
    Session::GetInstance().stopTimer();
    announcementLabel->setGeometry(
        (parentWidget()->width() + gameboard->width()) / 2 + 50,
        parentWidget()->height() / 2, announcementLabel->width() + 20,
        announcementLabel->height() + 30
    );
    announcementLabel->show();
    if (won == Result::Win) {
        announcementLabel->setText("You won!");
    } else {
        reavealAllBombs();
        announcementLabel->setText("You lost!");
        return;
    }

    for (auto& squareRow : board) {
        for (auto& square : squareRow) {
            if (square->type == Square_Type::Mine)
                square->changeState(Square::STATE::Flagged);
            square->setEnabled(false);
        }
    }
}
void GameboardPage::handleNewGameStart() {
    // TODO : Get Session and stuffs

    auto& board = Session::GetBoard();

    setupGameboard();
    int i = 0, j = 0;
    for (auto& row : board) {
        for (auto& square : row) {
            mainGridLayout->addWidget(square, square->row, square->col);
            mainGridLayout->setRowStretch(i, 1);
            mainGridLayout->setColumnStretch(j, 1);
            square->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        }
    }
    gameboard->setLayout(mainGridLayout);
    connect(Session::GetTimer(), &Timer::timerUpdated, timer, [this]() {
        timer->setText(Session::GetTimer()->elapsedTime.toString("mm:ss"));
    });
}
void GameboardPage::cleanBoard() {
    QLayoutItem* item;
    while ((item = mainGridLayout->takeAt(0))) {
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }
    timer->setText("00:00");
}