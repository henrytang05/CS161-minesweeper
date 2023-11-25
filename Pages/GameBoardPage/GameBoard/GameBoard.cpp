#include "GameBoard.h"
void GameBoard::setupGameBoard() {
    this->setFixedSize(
        Square::CELL_SIZE * GameBoard::BOARD_SIZE,
        Square::CELL_SIZE * GameBoard::BOARD_SIZE
    );
    grid.resize(
        GameBoard::BOARD_SIZE, std::vector<Square*>(GameBoard::BOARD_SIZE, nullptr)
    );
    QGridLayout* mainGridLayout = new ("mainGridLayout") QGridLayout(this);

    for (int row = 0; row < GameBoard::BOARD_SIZE; row++) {
        for (int col = 0; col < GameBoard::BOARD_SIZE; col++) {
            Square* square = new ("Square in grid") Square(this);
            square->setFixedSize(Square::CELL_SIZE, Square::CELL_SIZE);
            QObject::connect(square, &QPushButton::clicked, square, [square, row, col]() {
                square->squareClicked(row, col);
            });
            styleButton(square, "#EEA6B9", false);
            grid[row][col] = square;
            mainGridLayout->addWidget(square, row, col);
        }
    }
    this->setLayout(mainGridLayout);
    initializeGameBoard();
    this->show();
}
void GameBoard::initializeGameBoard() {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(0, GameBoard::BOARD_SIZE - 1);

    for (int i = 0; i < GameBoard::MINE_NUMBER; i++) {
        int rowRandomNumber = distribution(generator);
        int colRandomNumber = distribution(generator);
        if (isValidBombPosition(rowRandomNumber, colRandomNumber)) {
            grid[rowRandomNumber][colRandomNumber]->setMine();
            updateSurroundingSquares(rowRandomNumber, colRandomNumber);
        } else
            --i;
    }
}
bool GameBoard::isValidBombPosition(int row, int col) {
    if (!grid[row][col]->getIsMine()) {
        return true;
    } else {
        return false;
    }
}
void GameBoard::updateSurroundingSquares(int row, int col) {
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
        grid[newRow][newCol]->surroundingMineCount++;
    }
}

void GameBoard::breakSurroundingCells(int row, int col) {
    if (row < 0 || row >= GameBoard::BOARD_SIZE || col < 0 ||
        col >= GameBoard::BOARD_SIZE || GameBoard::grid[row][col]->getIsRevealed()) {
        return;
    }
    Square* square = GameBoard::grid[row][col];
    square->setAsRevealed();
    if (GameBoard::grid[row][col]->surroundingMineCount != 0) {
        GameBoard::grid[row][col]->render_square(row, col);
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

void GameBoard::announcement(std::string message) {
    QLabel* annoucement = new ("Label") QLabel;

    annoucement->setAlignment(Qt::AlignCenter);
    annoucement->setGeometry(GameBoard::BOARD_SIZE * Square::CELL_SIZE + 5, 10, 200, 200);
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
                square->setIcon(QIcon("Pictures/bomb.png"));
            }
            // disconnect(square, &Square::clicked, nullptr, nullptr);
        }
    }
    announcement("Game Over");
}
void newGame() {
    GameBoard* gameBoard = new ("GameBoard") GameBoard();
    gameBoard->show();
}
