#include "LevelSelectionPage.h"

#include "Session/Session.h"
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
    resume = new QPushButton("Resume", this);
    easy = new QPushButton("Easy", this);
    medium = new QPushButton("Medium", this);
    hard = new QPushButton("Hard", this);
    custom = new QPushButton("Custom", this);
    back = new QPushButton("Back", this);

    styleButton(resume, "FFF6F6", "C499F3");
    styleButton(easy, "FFF6F6", "C499F3");
    styleButton(medium, "FFF6F6", "C499F3");
    styleButton(hard, "FFF6F6", "C499F3");
    styleButton(custom, "FFF6F6", "C499F3");
    styleButton(back, "FFF6F6", "C499F3");

    buttonLayout->addWidget(resume, 0, Qt::AlignCenter);
    buttonLayout->addWidget(easy, 0, Qt::AlignCenter);
    buttonLayout->addWidget(medium, 0, Qt::AlignCenter);
    buttonLayout->addWidget(hard, 0, Qt::AlignCenter);
    buttonLayout->addWidget(custom, 0, Qt::AlignCenter);
    buttonLayout->addWidget(back, 0, Qt::AlignCenter);

    connect(resume, &QPushButton::clicked, this, &LevelSelectionPage::resumeClicked);
    connect(easy, &QPushButton::clicked, this, [this]() { setupNewGame(9, 9, 10); });
    connect(medium, &QPushButton::clicked, this, [this]() { setupNewGame(16, 16, 50); });
    connect(hard, &QPushButton::clicked, this, [this]() { setupNewGame(10, 30, 99); });
    connect(custom, &QPushButton::clicked, this, [this]() {
        int row = 0, col = 0, mine = 0;
        customLevelSelection(row, col, mine);
        if (row == 0 || col == 0) return;
        setupNewGame(row, col, mine);
    });
    connect(back, &QPushButton::clicked, this, [this]() {
        emit LevelSelectionPage::backClicked();
    });
}
void LevelSelectionPage::setupNewGame(int row, int col, int mine) {
    Session::SetBoardDimension(row, col);
    Session::SetMineNumber(mine);
    double maxBoardWidth = 0.7 * this->parentWidget()->width();
    double maxBoardHeight = 0.7 * this->parentWidget()->height();
    // TODO : add set function
    double cellSize = std::min(
        maxBoardWidth / Session::GetColumn(), maxBoardHeight / Session::GetRow()
    );
    Session::SetCellSize(cellSize);
    emit LevelSelectionPage::levelSelected();
}
void LevelSelectionPage::customLevelSelection(int& row, int& col, int& mine) {
    QList<int> dimensions;
    bool validInput = false;
    do {
    again:
        QDialog dialog(this);

        QFormLayout form(&dialog);
        dialog.resize(300, 100);
        QList<QLineEdit*> fields;
        QLineEdit* lineEdit1 = new QLineEdit(&dialog);
        QLineEdit* lineEdit2 = new QLineEdit(&dialog);
        QLineEdit* lineEdit3 = new QLineEdit(&dialog);
        form.addRow("Row", lineEdit1);
        form.addRow("Column", lineEdit2);
        form.addRow("Mine Number", lineEdit3);

        fields << lineEdit1 << lineEdit2 << lineEdit3;

        QDialogButtonBox buttonBox(
            QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog
        );
        form.addRow(&buttonBox);
        QObject::connect(
            &buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept
        );
        QObject::connect(
            &buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject
        );

        if (dialog.exec() != QDialog::Accepted) return;
        dimensions.clear();
        validInput = true;
        for (QLineEdit* lineEdit : fields) {
            bool ok;
            int value = lineEdit->text().toInt(&ok);
            if (!ok || value < 1) {
                QMessageBox::warning(
                    this, "Invalid input", "Please enter a valid integer greater than 0"
                );
                validInput = false;
                goto again;
            }
            dimensions << value;
        }
        if (dimensions[0] * dimensions[1] <= dimensions[2]) {
            QMessageBox::warning(
                this, "Invalid input", "Row * Column must be greater than Mine Number"
            );
            validInput = false;
        } else if (dimensions[0] > 50 || dimensions[1] > 50) {
            QMessageBox::warning(
                this, "Invalid input", "Row and Column must be less than 50"
            );
            validInput = false;
        }
    } while (!validInput);

    if (validInput) {
        row = dimensions[0];
        col = dimensions[1];
        mine = dimensions[2];
    }
    return;
}
