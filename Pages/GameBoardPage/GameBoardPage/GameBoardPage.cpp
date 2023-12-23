#include "GameboardPage.h"

#include "Session/Session.h"
#include "Square/Square.h"
#include "Style/Style.h"
#include "Timer/Timer.h"
GameboardPage::GameboardPage(QStackedWidget* parent) : QWidget(parent) {
    gameboard = new QWidget(this);
    newGameButton = new QPushButton("New Game", this);
    replayButton = new QPushButton("Replay", this);
    timer = new QLabel("00:00", this);
    mainGridLayout = new QGridLayout(this);
    announcementLabel = new QLabel(this);
    level = new QLabel(this);
    highScore = new QLabel(this);
}
GameboardPage::~GameboardPage() {}

void GameboardPage::setupGameboard() {
    QWidget* sideBar = new QWidget(this);
    QVBoxLayout* sideLayout = new QVBoxLayout(sideBar);
    sideBar->setLayout(sideLayout);
    announcementLabel->hide();

    double& cell = Session::GetCellSize();
    int row = Session::GetRow();
    int col = Session::GetColumn();
    gameboard->resize(cell * col, cell * row);
    int x = (parentWidget()->width() - gameboard->width()) / 2;
    int y = (parentWidget()->height() - gameboard->height()) / 2;
    gameboard->setGeometry(x, y, gameboard->width(), gameboard->height());

    styleLabel(announcementLabel, "DBD8AE", 20);
    styleButton(newGameButton, "12D9C4", true);
    styleButton(replayButton, "12D9C4", true);
    styleLabel(level, "DBD8AE", 10);
    styleTimer(timer);
    styleLabel(highScore, "DBD8AE", 10);

    level->adjustSize();
    level->setText("Level: " + QString::number(Session::GetDifficulty()));
    highScore->adjustSize();
    highScore->setText("High Score: " + Session::GetHighScoreAsString());
    newGameButton->adjustSize();
    replayButton->adjustSize();
    timer->adjustSize();

    sideLayout->addWidget(timer);
    sideLayout->addWidget(newGameButton);
    sideLayout->addWidget(replayButton);
    sideLayout->addWidget(level);
    sideLayout->addWidget(highScore);

    QObject::connect(replayButton, &QPushButton::clicked, this, [this]() {
        timer->setText("00:00");
        cleanBoard();
        Session::ResetForReplay();
        handleReplay();
        Session::GetInstance().startTimer();
    });

    newGameButton->show();
    timer->show();
    level->show();
    highScore->show();
    replayButton->show();
}
void GameboardPage::handleReplay() {
    auto& board = Session::GetBoard();
    int i = 0, j = 0;
    for (auto& row : board) {
        for (auto& square : row) {
            mainGridLayout->addWidget(square, square->row, square->col);
            mainGridLayout->setRowStretch(i, 1);
            mainGridLayout->setColumnStretch(j, 1);
            square->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        }
    }
    timer->setText("00:00");
    announcementLabel->hide();
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

    highScore->setText("High Score: " + Session::GetHighScoreAsString());
}
void GameboardPage::handleNewGameStart() {
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