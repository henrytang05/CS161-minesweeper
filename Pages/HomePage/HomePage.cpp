#include "HomePage.h"
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
    QPushButton* Resume = new QPushButton("Resume Game");
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