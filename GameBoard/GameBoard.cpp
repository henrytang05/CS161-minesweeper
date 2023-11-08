#include "GameBoard.h"

#include <random>

void GameBoard::initializeGameBoard() {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(0, GameBoard::BOARD_SIZE - 1);

    for (int i = 0; i < GameBoard::MINE_NUMBER; i++) {
        int rowRandomNumber = distribution(generator);
        int colRandomNumber = distribution(generator);
        if (isValidBombPosition(rowRandomNumber, colRandomNumber)) {
            grid[rowRandomNumber][colRandomNumber]->setMine();
            updateSurroundingCells(rowRandomNumber, colRandomNumber);
        } else
            --i;
    }
}

void GameBoard::setupGameBoard() {
    this->setFixedSize(
        GameBoard::CELL_SIZE * GameBoard::BOARD_SIZE,
        GameBoard::CELL_SIZE * GameBoard::BOARD_SIZE
    );
    mainGridLayout = new QGridLayout(this);
    grid.resize(
        GameBoard::BOARD_SIZE, std::vector<Square*>(GameBoard::BOARD_SIZE, nullptr)
    );

    for (int row = 0; row < GameBoard::BOARD_SIZE; row++) {
        for (int col = 0; col < GameBoard::BOARD_SIZE; col++) {
            Square* square = new Square(this);
            square->setFixedSize(GameBoard::CELL_SIZE, GameBoard::CELL_SIZE);

            connect(square, &Square::clicked, this, [this, square, row, col]() {
                squareClicked(square, row, col);
            });
            grid[row][col] = square;
            mainGridLayout->addWidget(square, row, col);
        }
    }
    initializeGameBoard();

    // replayButton = new QPushButton("Replay", this);
    // replayButton->setGeometry(GameBoard::BOARD_SIZE * GameBoard::CELL_SIZE + 50, 20,
    // 100, 50); connect(replayButton, &QPushButton::clicked, this, [this]() {
    //     restartClicked(this);
    // });
}
void setIcon(
    QPushButton* button, const QIcon icon, int width = GameBoard::CELL_SIZE / 2,
    int length = GameBoard::CELL_SIZE / 2
) {
    QSize iconSize(width, length);
    QPixmap pixmap = icon.pixmap(iconSize);
    if (button) {
        button->setIcon(QIcon(pixmap));
        button->setIconSize(iconSize);
    }
}
bool GameBoard::isValidBombPosition(int row, int col) {
    if (!grid[row][col]->getIsMine()) {
        return true;
    } else {
        return false;
    }
}
void GameBoard::updateSurroundingCells(int row, int col) {
    int direction[8][2] = {
        {-1, -1},  // Up-Left
        {-1, 0},   // Up
        {-1, 1},   // Up-Right
        {0, -1},   // Left
        {0, 1},    // Right
        {1, -1},   // Down-Left
        {1, 0},    // Down
        {1, 1}     // Down-Right
    };
    for (auto& move : direction) {
        int newRow = row + move[0];
        int newCol = col + move[1];
        if (newRow < 0 || newRow >= GameBoard::BOARD_SIZE || newCol < 0 ||
            newCol >= GameBoard::BOARD_SIZE || grid[newRow][newCol]->getIsMine())
            continue;
        grid[newRow][newCol]->bombCount++;
    }
}
void GameBoard::breakSurroundingCells(int row, int col) {
    if (row < 0 || row >= GameBoard::BOARD_SIZE || col < 0 ||
        col >= GameBoard::BOARD_SIZE || grid[row][col]->getIsRevealed()) {
        return;
    }
    Square* square = grid[row][col];
    square->setAsRevealed();
    if (grid[row][col]->bombCount != 0) {
        render_square(grid[row][col], row, col);
        return;
    }
    square->setStyleSheet("background-color: green");

    int direction[8][2] = {
        {-1, -1},  // Up-Left
        {-1, 0},   // Up
        {-1, 1},   // Up-Right
        {0, -1},   // Left
        {0, 1},    // Right
        {1, -1},   // Down-Left
        {1, 0},    // Down
        {1, 1}     // Down-Right
    };
    for (auto& move : direction) {
        int newRow = row + move[0];
        int newCol = col + move[1];
        breakSurroundingCells(newRow, newCol);
    }
}
void GameBoard::render_square(Square* square, int row, int col) {
    switch (square->bombCount) {
        case 1:
            setIcon(square, QIcon("Pictures/number-1.png"));
            break;
        case 2:
            setIcon(square, QIcon("Pictures/number-2.png"));
            break;
        case 3:
            setIcon(square, QIcon("Pictures/number-3.png"));
            break;
        case 4:
            setIcon(square, QIcon("Pictures/number-4.png"));
            break;
        case 5:
            setIcon(square, QIcon("Pictures/number-5.png"));
            break;
        case 6:
            setIcon(square, QIcon("Pictures/number-6.png"));
            break;
        case 7:
            setIcon(square, QIcon("Pictures/number-7.png"));
            break;
        case 8:
            setIcon(square, QIcon("Pictures/number-8.png"));
            break;
        default:
            square->setAsNotRevealed();
            breakSurroundingCells(row, col);
    }
}

void GameBoard::announcement(std::string message) {
    QLabel* annoucement = new QLabel(this);

    annoucement->setAlignment(Qt::AlignCenter);
    annoucement->setGeometry(
        GameBoard::BOARD_SIZE * GameBoard::CELL_SIZE + 5, 10, 200, 200
    );
    QString qMessage = QString::fromStdString(message);
    annoucement->setText(qMessage);
    std::string styleSheet =
        "font-size: 30px; font-family: Sans-serif; font-style: normal; color: ";
    styleSheet += (message == "You Win") ? "green;" : "red;";
    annoucement->setStyleSheet(QString::fromStdString(styleSheet));
    annoucement->show();
}
void GameBoard::revealAllBombs() {
    for (auto row : grid) {
        for (Square* square : row) {
            if (square->getIsMine() && !square->getIsRevealed()) {
                square->setStyleSheet("background-color: red");
                setIcon(square, QIcon("Pictures/bomb.png"));
            }
            disconnect(square, &Square::clicked, nullptr, nullptr);
        }
    }
    announcement("Game Over");
}
void newGame() {
    GameBoard* gameBoard = new GameBoard();
    gameBoard->show();
}
void GameBoard::squareClicked(Square* square, int row, int col) {
    if (square->getIsMine()) {
        revealAllBombs();
        return;
    }
    square->setAsRevealed();
    render_square(square, row, col);
    if (Square::squareRevealed ==
        GameBoard::BOARD_SIZE * GameBoard::BOARD_SIZE - GameBoard::MINE_NUMBER) {
        announcement("You Win!");
    }
}
void GameBoard::restartClicked(GameBoard* gameboard) {
    gameboard->close();
    delete gameboard;
    GameBoard* newGameBoard = new GameBoard();
    newGameBoard->show();
}
