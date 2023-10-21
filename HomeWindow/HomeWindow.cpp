#include "HomeWindow.h"

void HomeWindow::setupHomeWindow() {
    this->setWindowTitle("Home Window");
    this->setFixedSize(400, 400);
    this->setStyleSheet("background-color: #FFDFDF;");
    QLabel* label = new QLabel("Choose a level", this);
    QPushButton* easy = new QPushButton("Easy", this);
    QPushButton* medium = new QPushButton("Medium", this);
    QPushButton* hard = new QPushButton("Hard", this);
    easy->setBaseSize(1000, 100);
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    QVBoxLayout* buttonLayout = new QVBoxLayout();
    mainLayout->addWidget(label, 0, Qt::AlignCenter);
    mainLayout->addLayout(buttonLayout);

    buttonLayout->addWidget(easy, 0, Qt::AlignCenter);
    buttonLayout->addWidget(medium, 0, Qt::AlignCenter);
    buttonLayout->addWidget(hard, 0, Qt::AlignCenter);

    connect(easy, &QPushButton::clicked, nullptr, [this]() { setLevel(1); });
    connect(medium, &QPushButton::clicked, nullptr, [this]() { setLevel(2); });
    connect(hard, &QPushButton::clicked, nullptr, [this]() { setLevel(3); });
}
void HomeWindow::setLevel(int level) {
    this->close();
    GameBoard* game = new GameBoard(nullptr, level);
}
