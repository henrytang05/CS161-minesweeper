#include "HomePage.h"
void HomePage::setupHomePage() {
    // Create the layout button and label of the home page
    // connect the button to the level selection page
    // this = new ("Home Page") QWidget;
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
    styleButton(newGame, "FFF6F6");
    styleButton(Resume, "EAF4D3");

    // connect(newGame, &QPushButton::clicked, this, [this]() {
    //     stackedWidget->setCurrentWidget(levelSelectionPage);
    // });
    // connect(Resume, &QPushButton::clicked, this, &HomeWindow::resumeGame);

    mainLayout->addStretch();
    mainLayout->addLayout(labelLayout);
    mainLayout->addStretch();
    mainLayout->addLayout(buttonLayout);
    mainLayout->addStretch();
}