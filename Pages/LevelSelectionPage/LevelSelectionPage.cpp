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
    QPushButton* custom = new QPushButton("Custom", this);
    QPushButton* back = new QPushButton("Back", this);

    styleButton(easy, "FFF6F6");
    styleButton(medium, "FFF6F6");
    styleButton(hard, "FFF6F6");
    styleButton(custom, "FFF6F6");
    styleButton(back, "FFF6F6");

    buttonLayout->addWidget(easy, 0, Qt::AlignCenter);
    buttonLayout->addWidget(medium, 0, Qt::AlignCenter);
    buttonLayout->addWidget(hard, 0, Qt::AlignCenter);
    buttonLayout->addWidget(custom, 0, Qt::AlignCenter);
    buttonLayout->addWidget(back, 0, Qt::AlignCenter);

    connect(easy, &QPushButton::clicked, this, [this]() {
        emit LevelSelectionPage::levelSelected(DIFFICULTY::Beginner);
    });
    connect(medium, &QPushButton::clicked, this, [this]() {
        emit LevelSelectionPage::levelSelected(DIFFICULTY::Intermediate);
    });
    connect(hard, &QPushButton::clicked, this, [this]() {
        emit LevelSelectionPage::levelSelected(DIFFICULTY::Expert);
    });
    connect(custom, &QPushButton::clicked, this, [this]() {
        emit LevelSelectionPage::levelSelected(DIFFICULTY::Custom);
    });
    connect(back, &QPushButton::clicked, this, [this]() {
        emit LevelSelectionPage::backClicked();
    });
}
void LevelSelectionPage::customLevelSelection() {
    QDialog dialog(this);
    QFormLayout form(&dialog);

    QList<QLineEdit*> fields;
    for (int i = 0; i < 3; ++i) {
        QLineEdit* lineEdit = new QLineEdit(&dialog);
        QString label;
        switch (i) {
            case 0:
                label = QString("Row: ");
                break;
            case 1:
                label = QString("Column: ");
                break;
            case 2:
                label = QString("Mine: ");
                break;
        }
        form.addRow(label, lineEdit);
        fields << lineEdit;
    }

    QDialogButtonBox buttonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &dialog
    );
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    QObject::connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted) {
        QList<int> dimensions;
        for (QLineEdit* lineEdit : fields) {
            dimensions << lineEdit->text().toInt();
        }
        // Use dimensions here
    }
}