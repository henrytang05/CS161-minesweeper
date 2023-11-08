#include "HomeWindow.h"

// #include "../Button/Button.h"
void setButtonColor(
    QPushButton* b, const std::string& color = "FF00000", bool rounded = true
) {
    b->setFixedSize(100, 50);
    if (!rounded)
        b->setStyleSheet(QString(("background-color: #" + color + ";").c_str()));
    else
        b->setStyleSheet(
            QString(("background-color: #" + color + "; border-radius: 15px ;").c_str())
        );
}
void HomeWindow::setupHomeWindow() {
    this->setWindowTitle("Home Window");
    this->setFixedSize(500, 500);
    this->setStyleSheet("background-color: #CA907E;");
    QLabel* titleLabel = new QLabel("MineSweeper");
    QLabel* titleWelcome = new QLabel("Welcome to");
    titleLabel->setStyleSheet("color: #DBD8AE;");
    titleWelcome->setStyleSheet("color: #DBD8AE;");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleWelcome->setAlignment(Qt::AlignCenter);
    QFont font = titleLabel->font();
    font.setPointSize(30);
    font.setBold(true);
    titleLabel->setFont(font);
    titleWelcome->setFont(font);

    QPushButton* newGame = new QPushButton("New Game");
    QPushButton* Resume = new QPushButton("Resume Game");
    connect(newGame, &QPushButton::clicked, this, &HomeWindow::setupNewGame);
    connect(Resume, &QPushButton::clicked, this, &HomeWindow::resumeGame);

    setButtonColor(newGame, "EAF4D3");
    setButtonColor(Resume, "EAF4D3");

    // newGame->setupButton("FFF6F6");
    // Resume->setupButton("FFF6F6");

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addStretch();
    layout->addWidget(titleWelcome, 0, Qt::AlignCenter);
    layout->addSpacing(10);
    layout->addWidget(titleLabel, 0, Qt::AlignCenter);
    layout->addStretch();
    layout->addWidget(newGame, 0, Qt::AlignCenter);
    layout->addSpacing(20);
    layout->addWidget(Resume, 0, Qt::AlignCenter);
    layout->addStretch();

    QWidget* centralWidget = new QWidget;
    centralWidget->setLayout(layout);
    this->setCentralWidget(centralWidget);
}

void HomeWindow::setupNewGame() {
    QPushButton* easy = new QPushButton("Easy");
    QPushButton* medium = new QPushButton("Medium");
    QPushButton* hard = new QPushButton("Hard");

    setButtonColor(easy, "FFF6F6");
    setButtonColor(medium, "FFF6F6");
    setButtonColor(hard, "FFF6F6");

    QVBoxLayout* mainLayout = new QVBoxLayout();
    QVBoxLayout* buttonLayout = new QVBoxLayout();

    QLabel* label = new QLabel("Choose a level");
    QFont font = label->font();
    font.setPointSize(20);
    font.setFamily("Arial");
    label->setFont(font);
    label->setStyleSheet("color: #DBD8AE;");
    mainLayout->addWidget(label, 0, Qt::AlignCenter);
    mainLayout->addLayout(buttonLayout);

    buttonLayout->addWidget(easy, 0, Qt::AlignCenter);
    buttonLayout->addWidget(medium, 0, Qt::AlignCenter);
    buttonLayout->addWidget(hard, 0, Qt::AlignCenter);

    QWidget* levelSelectionWidget = new QWidget;
    levelSelectionWidget->setLayout(mainLayout);
    this->setCentralWidget(levelSelectionWidget);
}
void HomeWindow::resumeGame() {}
