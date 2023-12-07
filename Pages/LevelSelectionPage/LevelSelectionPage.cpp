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
void LevelSelectionPage::customLevelSelection() {
    QList<int> dimensions;
    bool validInput = false;
    do {
        QDialog dialog(this);
        QFormLayout form(&dialog);

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
                break;
            }
            dimensions << value;
        }
        if (dimensions[0] * dimensions[1] <= dimensions[2]) {
            QMessageBox::warning(
                this, "Invalid input", "Row * Column must be greater than Mine Number"
            );
            validInput = false;
        }
    } while (!validInput);

    if (validInput) {
        Session::SetBoardDimension(dimensions[0], dimensions[1]);
        Session::SetMineNumber(dimensions[2]);
    }
    return;
}