#include "GameboardPage.h"

#include "Session/Session.h"
#include "Square/Square.h"
#include "Style/Color.h"
#include "Style/Style.h"
#include "Timer/Timer.h"
GameboardPage::GameboardPage(QWidget* parent) : QWidget(parent) {
    gameboard = new QWidget(this);
    newGameButton = new QPushButton("Another level", this);
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
    static QVBoxLayout* mainLayout = new QVBoxLayout(this);
    static QVBoxLayout* labelLayout = new QVBoxLayout(this);
    static QVBoxLayout* buttonLayout = new QVBoxLayout(this);

    sideBar->setLayout(mainLayout);
    mainLayout->addLayout(labelLayout);
    mainLayout->addLayout(buttonLayout);

    styleLabel(announcementLabel, "596FB7", 30);
    styleButton(newGameButton, BUTTON_COLOR, BUTTON_TEXT_COLOR);
    styleButton(replayButton, BUTTON_COLOR, BUTTON_TEXT_COLOR);
    styleButton(exitButton, BUTTON_COLOR, BUTTON_TEXT_COLOR);
    styleLabel(level, "756AB6", 20);
    styleLabel(highScore, "AC87C5", 15);
    styleTimer(timer, "4F6F52");

    level->adjustSize();
    highScore->adjustSize();
    newGameButton->adjustSize();
    replayButton->adjustSize();
    exitButton->adjustSize();
    timer->adjustSize();

    labelLayout->addWidget(level, 0, Qt::AlignCenter);
    labelLayout->addWidget(highScore, 0, Qt::AlignVCenter);
    labelLayout->addWidget(timer, 0, Qt::AlignVCenter);
    buttonLayout->addWidget(newGameButton, 0, Qt::AlignVCenter);
    buttonLayout->addWidget(replayButton, 0, Qt::AlignVCenter);
    buttonLayout->addWidget(exitButton, 0, Qt::AlignVCenter);

    QObject::connect(replayButton, &QPushButton::clicked, this, [this]() {
        Session::ResetForReplay();
        handleReplay();
        Session::GetInstance().startTimer();
    });
    QObject::connect(
        newGameButton, &QPushButton::clicked, this, &GameboardPage::newGameSignal
    );
    QObject::connect(exitButton, &QPushButton::clicked, this, &GameboardPage::exitSignal);
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
    announcementLabel->setGeometry(
        (this->parentWidget()->width() - announcementLabel->width()) / 2,
        (parentWidget()->height() - gameboard->height()) / 2 - 50, 200, 50
    );
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
void GameboardPage::resultAnnoucement(Result won) {
    auto& board = Session::GetBoard();

    announcementLabel->show();
    if (won == Result::Win) {
        announcementLabel->setText("You won!");
    } else {
        reavealAllBombs();
        announcementLabel->setText("You lost!");
        return;
    }
    announcementLabel->setGeometry(
        (this->parentWidget()->width() - announcementLabel->width()) / 2,
        (parentWidget()->height() - gameboard->height()) / 2 - 50, 200, 50
    );

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