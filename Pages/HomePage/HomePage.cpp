#include "HomePage.h"

#include "Style/Style.h"
HomePage::HomePage(QStackedWidget* parent) { setupHomePage(); }
HomePage::~HomePage() {}
void HomePage::setupHomePage() {
    QVBoxLayout* mainLayout = new QVBoxLayout;
    this->setLayout(mainLayout);

    QVBoxLayout* labelLayout = new QVBoxLayout;
    QLabel* titleLabel = new QLabel("MineSweeper");
    QLabel* titleWelcome = new QLabel("Welcome to");
    styleLabel(titleLabel, "DBD8AE");
    styleLabel(titleWelcome, "DBD8AE");
    labelLayout->addWidget(titleWelcome, 0, Qt::AlignCenter);
    labelLayout->addWidget(titleLabel, 0, Qt::AlignCenter);

    QVBoxLayout* buttonLayout = new QVBoxLayout;
    QPushButton* newGame = new QPushButton("New Game");
    buttonLayout->setSpacing(20);
    QPushButton* highScore = new QPushButton("High Scores");
    buttonLayout->addWidget(newGame, 0, Qt::AlignCenter);
    buttonLayout->addWidget(highScore, 0, Qt::AlignCenter);
    styleButton(newGame, "A6DCEF");
    styleButton(highScore, "A6DCEF");

    connect(newGame, &QPushButton::clicked, this, &HomePage::newGameButton);
    connect(highScore, &QPushButton::clicked, this, &HomePage::highScoreButton);

    mainLayout->addStretch();
    mainLayout->addLayout(labelLayout);
    mainLayout->addStretch();
    mainLayout->addLayout(buttonLayout);
    mainLayout->addStretch();
}