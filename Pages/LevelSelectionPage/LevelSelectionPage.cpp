#include "LevelSelectionPage.h"
void LevelSelectionPage::setupLevelSelectionPage() {
    // Create the layout button and label of the level selection page
    // connect the button to the game board
    QVBoxLayout* mainLayout = new ("Layout") QVBoxLayout();
    this->setLayout(mainLayout);

    QLabel* label = new ("Label") QLabel("Choose a level");
    styleLabel(label, "DBD8AE");
    mainLayout->addWidget(label, 0, Qt::AlignCenter);

    QVBoxLayout* buttonLayout = new ("Layout") QVBoxLayout();
    mainLayout->addLayout(buttonLayout);
    QPushButton* easy = new ("easy button") QPushButton("Easy");
    QPushButton* medium = new ("medium button") QPushButton("Medium");
    QPushButton* hard = new ("hard button") QPushButton("Hard");
    QPushButton* back = new ("Back Button") QPushButton("Back");

    styleButton(easy, "FFF6F6");
    styleButton(medium, "FFF6F6");
    styleButton(hard, "FFF6F6");
    styleButton(back, "FFF6F6");

    buttonLayout->addWidget(easy, 0, Qt::AlignCenter);
    buttonLayout->addWidget(medium, 0, Qt::AlignCenter);
    buttonLayout->addWidget(hard, 0, Qt::AlignCenter);
    buttonLayout->addWidget(back, 0, Qt::AlignCenter);
    // connect(back, &QPushButton::clicked, this, [this]() {
    //     stackedWidget->setCurrentWidget(homePage);
    // });
    // connect(easy, &QPushButton::clicked, this, [this]() { startGame(1); });
    // connect(medium, &QPushButton::clicked, this, [this]() { startGame(2); });
    // connect(hard, &QPushButton::clicked, this, [this]() { startGame(3); });
}