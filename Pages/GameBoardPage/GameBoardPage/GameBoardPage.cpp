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
}
GameboardPage::~GameboardPage() {}

void GameboardPage::setupGameboard() {
    // layoutCollection.clear();
    int cell = Session::GetCellSize();
    int row = Session::GetRow();
    int col = Session::GetColumn();

    int x = (parentWidget()->width() - gameboard->width()) / 2;
    int y = (parentWidget()->height() - gameboard->height()) / 2;
    styleTimer(timer);

    timer->setGeometry(x - 50, y - 200, timer->width(), timer->height());
    styleButton(replayButton, "12D9C4", true);

    gameboard->resize(cell * col, cell * row);

    gameboard->setGeometry(
        x - gameboard->width() / 2, y - gameboard->height() / 2, gameboard->width(),
        gameboard->height()
    );

    connect(this, &GameboardPage::result, this, &GameboardPage::victoryAnnoucement);
}

void GameboardPage::reavealAllBombs() {
    auto& board = Session::GetBoard();

    for (auto& squareRow : board) {
        for (auto& square : squareRow) {
            if (square->type == Square_Type::Mine) {
                square->render_square();
            }
        }
    }
}
void GameboardPage::victoryAnnoucement(Result won) {
    auto& board = Session::GetBoard();
    Session::GetInstance().stopTimer();
    QLabel* announcementLabel = new QLabel(this);
    announcementLabel->setGeometry(QRect(QPoint(500, 20), QPoint(500 + 200, 20 + 200)));

    styleLabel(announcementLabel, "DBD8AE", 20);
    if (won == Result::Win) {
        announcementLabel->setText("You won!");
    } else {
        reavealAllBombs();
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
void GameboardPage::cleanBoard() {
    QLayoutItem* item;
    while ((item = mainGridLayout->takeAt(0))) {
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }
}