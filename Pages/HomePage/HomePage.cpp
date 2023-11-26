#include "HomePage.h"
void HomePage::setupHomePage() {
    QVBoxLayout* mainLayout = new ("Layout") QVBoxLayout;
    this->setLayout(mainLayout);

    QVBoxLayout* labelLayout = new ("Layout") QVBoxLayout;
    QLabel* titleLabel = new ("Label") QLabel("MineSweeper");
    QLabel* titleWelcome = new ("Label") QLabel("Welcome to");
    styleLabel(titleLabel, "DBD8AE");
    styleLabel(titleWelcome, "DBD8AE");
    labelLayout->addWidget(titleWelcome, 0, Qt::AlignCenter);
    labelLayout->addWidget(titleLabel, 0, Qt::AlignCenter);

    QVBoxLayout* buttonLayout = new ("Layout") QVBoxLayout;
    QPushButton* newGame = new ("New Game Button") QPushButton("New Game");
    buttonLayout->setSpacing(20);
    QPushButton* Resume = new ("Resume Button") QPushButton("Resume Game");
    buttonLayout->addWidget(newGame, 0, Qt::AlignCenter);
    buttonLayout->addWidget(Resume, 0, Qt::AlignCenter);
    styleButton(newGame, "A6DCEF");
    styleButton(Resume, "A6DCEF");

    connect(newGame, &QPushButton::clicked, this, &HomePage::newGameClicked);
    // connect(Resume, &QPushButton::clicked, this, &HomePage::resumeGameClicked);

    mainLayout->addStretch();
    mainLayout->addLayout(labelLayout);
    mainLayout->addStretch();
    mainLayout->addLayout(buttonLayout);
    mainLayout->addStretch();
}