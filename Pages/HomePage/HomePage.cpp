#include "HomePage.h"

#include "Style/Color.h"
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
    QPushButton* newGame = new QPushButton("New Game", this);
    QPushButton* resume = new QPushButton("Resume Game", this);
    QPushButton* exit = new QPushButton("Exit", this);
    styleButton(newGame, BUTTON_COLOR, BUTTON_TEXT_COLOR);
    styleButton(resume, BUTTON_COLOR, BUTTON_TEXT_COLOR);
    styleButton(exit, BUTTON_COLOR, BUTTON_TEXT_COLOR);

    buttonLayout->setSpacing(20);
    buttonLayout->addWidget(newGame, 0, Qt::AlignCenter);
    buttonLayout->setSpacing(20);
    buttonLayout->addWidget(resume, 0, Qt::AlignCenter);
    buttonLayout->setSpacing(20);
    buttonLayout->addWidget(exit, 0, Qt::AlignCenter);
    buttonLayout->setSpacing(20);

    connect(newGame, &QPushButton::clicked, this, &HomePage::newGameSignal);
    connect(resume, &QPushButton::clicked, this, &HomePage::resumeGameSignal);
    connect(exit, &QPushButton::clicked, this, &HomePage::exit);

    mainLayout->addStretch();
    mainLayout->addLayout(labelLayout);
    mainLayout->addStretch();
    mainLayout->addLayout(buttonLayout);
    mainLayout->addStretch();
}