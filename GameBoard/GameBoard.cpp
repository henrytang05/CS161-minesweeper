#include "GameBoard.h"

#include <random>

#define CELL_SIZE 60
constexpr int BOARD_SIZE = 8;
constexpr int MINE_NUMBER = 10;

void setIcon(
    QPushButton* button, const QIcon icon, int width = CELL_SIZE / 2,
    int length = CELL_SIZE / 2
) {
    QSize iconSize(width, length);
    QPixmap pixmap = icon.pixmap(iconSize);
    if (button) {
        button->setIcon(QIcon(pixmap));
        button->setIconSize(iconSize);
    }
}

void GameBoard::initializeGameBoard() {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(0, BOARD_SIZE - 1);

    int arraySize = MINE_NUMBER;

    for (int i = 0; i < arraySize; i++) {
        int rowRandomNumber = distribution(generator);
        int colRandomNumber = distribution(generator);
        mines.emplace_back(std::make_pair(rowRandomNumber, colRandomNumber));
    }
}

void GameBoard::setupGameBoard() {
    setFixedSize(900, 800);

    QWidget* gridWidget = new QWidget(this);
    gridWidget->setFixedSize(CELL_SIZE * BOARD_SIZE, CELL_SIZE * BOARD_SIZE);

    mainGridLayout = new QGridLayout(gridWidget);

    grid.resize(BOARD_SIZE, std::vector<QPushButton*>(BOARD_SIZE, nullptr));
    initializeGameBoard();

    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            QPushButton* square = new QPushButton(gridWidget);
            square->setFixedSize(CELL_SIZE, CELL_SIZE);

            connect(square, &QPushButton::clicked, this, [this, square, row, col]() {
                squareClicked(square, row, col);
            });

            mainGridLayout->addWidget(square, row, col);
        }
    }

    setCentralWidget(gridWidget);
}

void GameBoard::squareClicked(QPushButton* square, int row, int col) {
    if (std::find(mines.begin(), mines.end(), std::make_pair(row, col)) != mines.end()) {
        square->setStyleSheet("background-color: red");
        setIcon(square, QIcon("Pictures/bomb.png"));
        return;
    }
    square->setStyleSheet("background-color: green");
    square->setText("None");
}
