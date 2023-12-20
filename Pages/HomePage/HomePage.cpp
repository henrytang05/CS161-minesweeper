#include "HomePage.h"

#include "Style/Style.h"
HomePage::HomePage(QStackedWidget* parent) { setupHomePage(); }
HomePage::~HomePage() {}
void HomePage::setupHomePage() {
    QVBoxLayout* mainLayout = new QVBoxLayout;
    this->setLayout(mainLayout);

    QVBoxLayout* labelLayout = new QVBoxLayout;
    QLabel* titleLabel = new QLabel("MineSweeper");
    QLabel* welcomeLabel = new QLabel("Welcome to");
    styleLabel(titleLabel, "DBD8AE");
    styleLabel(welcomeLabel, "DBD8AE");
    labelLayout->addWidget(welcomeLabel, 0, Qt::AlignCenter);
    labelLayout->addWidget(titleLabel, 0, Qt::AlignCenter);

    QVBoxLayout* buttonLayout = new QVBoxLayout;
    QPushButton* newGame = new QPushButton("New Game");
    QPushButton* resume = new QPushButton("Resume Game");
    QPushButton* highScore = new QPushButton("High Scores");
    buttonLayout->setSpacing(20);
    buttonLayout->addWidget(newGame, 0, Qt::AlignCenter);
    buttonLayout->setSpacing(20);
    buttonLayout->addWidget(highScore, 0, Qt::AlignCenter);
    buttonLayout->setSpacing(20);

    buttonLayout->addWidget(resume, 0, Qt::AlignCenter);
    styleButton(newGame, "A6DCEF");
    styleButton(resume, "A6DCEF");
    styleButton(highScore, "A6DCEF");

    connect(newGame, &QPushButton::clicked, this, &HomePage::newGameButton);
    connect(resume, &QPushButton::clicked, this, &HomePage::resumeButton);
    connect(highScore, &QPushButton::clicked, this, &HomePage::highScoreButton);
    mainLayout->addStretch();
    mainLayout->addLayout(labelLayout);
    mainLayout->addStretch();
    mainLayout->addLayout(buttonLayout);
    mainLayout->addStretch();

    QPushButton* exit = new QPushButton("Exit");
    styleButton(exit, "A6DCEF");
    connect(exit, &QPushButton::clicked, this, &HomePage::exit);
    mainLayout->addWidget(exit, 0, Qt::AlignCenter);
}