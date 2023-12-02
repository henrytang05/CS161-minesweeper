#include "LevelSelectionPage.h"

#include "Style/Style.h"
LevelSelectionPage::LevelSelectionPage(QStackedWidget* parent) {
    setupLevelSelectionPage();
}
LevelSelectionPage::~LevelSelectionPage() {}
void LevelSelectionPage::setupLevelSelectionPage() {
    QVBoxLayout* mainLayout = new QVBoxLayout();
    this->setLayout(mainLayout);

    QLabel* label = new QLabel("Choose a level");
    styleLabel(label, "DBD8AE");
    mainLayout->addWidget(label, 0, Qt::AlignCenter);
    mainLayout->addSpacing(-50);
    QVBoxLayout* buttonLayout = new QVBoxLayout(this);
    mainLayout->addLayout(buttonLayout);
    QPushButton* easy = new QPushButton("Easy", this);
    QPushButton* medium = new QPushButton("Medium", this);
    QPushButton* hard = new QPushButton("Hard", this);
    QPushButton* back = new QPushButton("Back", this);

    styleButton(easy, "FFF6F6");
    styleButton(medium, "FFF6F6");
    styleButton(hard, "FFF6F6");
    styleButton(back, "FFF6F6");

    buttonLayout->addWidget(easy, 0, Qt::AlignCenter);
    buttonLayout->addWidget(medium, 0, Qt::AlignCenter);
    buttonLayout->addWidget(hard, 0, Qt::AlignCenter);
    buttonLayout->addWidget(back, 0, Qt::AlignCenter);

    connect(easy, &QPushButton::clicked, this, [this]() {
        emit LevelSelectionPage::levelSelected(1);
    });
    connect(medium, &QPushButton::clicked, this, [this]() {
        emit LevelSelectionPage::levelSelected(2);
    });
    connect(hard, &QPushButton::clicked, this, [this]() {
        emit LevelSelectionPage::levelSelected(3);
    });
    connect(back, &QPushButton::clicked, this, [this]() {
        emit LevelSelectionPage::backClicked();
    });
}