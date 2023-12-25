#include "GameboardPage.h"

#include "Session/Session.h"
#include "Square/Square.h"
#include "Style/Color.h"
#include "Style/Style.h"
#include "Timer/Timer.h"
GameboardPage::GameboardPage(QStackedWidget* parent) : QWidget(parent) {
    gameboard = new QWidget(this);
    newGameButton = new QPushButton("New Game", this);
    replayButton = new QPushButton("Replay", this);
    exitButton = new QPushButton("Exit", this);
    timer = new QLabel("00:00", this);
    mainGridLayout = new QGridLayout(this);
    announcementLabel = new QLabel(this);
    announcementLabel->hide();
    level = new QLabel(this);
    highScore = new QLabel(this);
    setupGameboard();
}
GameboardPage::~GameboardPage() {}

void GameboardPage::setupGameboard() {
    static QWidget* sideBar = new QWidget(this);
    static QVBoxLayout* sideLayout = new QVBoxLayout(sideBar);
    sideBar->setLayout(sideLayout);

    styleLabel(announcementLabel, "DBD8AE", 20);
    styleButton(newGameButton, BUTTON_COLOR, BUTTON_TEXT_COLOR);
    styleButton(replayButton, BUTTON_COLOR, BUTTON_TEXT_COLOR);
    styleButton(exitButton, BUTTON_COLOR, BUTTON_TEXT_COLOR);
    styleLabel(level, "DBD8AE", 10);
    styleTimer(timer, "4F6F52");
    styleLabel(highScore, "DBD8AE", 10);

    level->adjustSize();
    highScore->adjustSize();
    newGameButton->adjustSize();
    replayButton->adjustSize();
    exitButton->adjustSize();
    timer->adjustSize();

    sideLayout->addWidget(timer);
    sideLayout->addWidget(newGameButton);
    sideLayout->addWidget(replayButton);
    sideLayout->addWidget(exitButton);
    sideLayout->addWidget(level);
    sideLayout->addWidget(highScore);
    sideLayout->setAlignment(Qt::AlignVCenter);
    sideLayout->setAlignment(Qt::AlignHCenter);

    QObject::connect(replayButton, &QPushButton::clicked, this, [this]() {
        Session::ResetForReplay();
        handleReplay();
        Session::GetInstance().startTimer();
    });
    QObject::connect(newGameButton, &QPushButton::clicked, this, &newGameSignal);
    QObject::connect(exitButton, &QPushButton::clicked, this, &exitSignal);
}
void GameboardPage::handleNewGameStart() {
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
    gameboard->setLayout(mainGridLayout);
    gameboard->resize(
        Session::GetCellSize() * Session::GetColumn(),
        Session::GetCellSize() * Session::GetRow()
    );
    int x = (parentWidget()->width() - gameboard->width()) / 2;
    int y = (parentWidget()->height() - gameboard->height()) / 2;
    gameboard->setGeometry(x, y, gameboard->width(), gameboard->height());
    announcementLabel->setGeometry(x + gameboard->width() / 2 - 200, y - 50, 200, 50);
    connect(Session::GetTimer(), &Timer::timerUpdated, timer, [this]() {
        timer->setText(Session::GetElapsedTimeAsString());
    });
    announcementLabel->hide();
    level->setText("Level: " + QString::number(Session::GetDifficulty()));
    highScore->setText("High Score: " + Session::GetHighScoreAsString());
}
void GameboardPage::handleReplay() {
    cleanBoard();

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
                square->state != Square::State::Flagged) {
                square->changeState(Square::State::Revealed);
            }
            square->setEnabled(false);
        }
    }
}
void GameboardPage::victoryAnnoucement(Result won) {
    auto& board = Session::GetBoard();

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
                square->changeState(Square::State::Flagged);
            square->setEnabled(false);
        }
    }

    highScore->setText("High Score: " + Session::GetHighScoreAsString());
}

void GameboardPage::cleanBoard() {
    announcementLabel->hide();
    QLayoutItem* item;
    while ((item = mainGridLayout->takeAt(0))) {
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }
    timer->setText("00:00");
}