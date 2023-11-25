#include "../Style/Style.h"

void styleButton(QPushButton* b, std::string&& color, bool rounded) {
    if (color[0] == '#') color.erase(0, 1);
    b->setFixedSize(100, 50);
    if (!rounded)
        b->setStyleSheet(QString::fromStdString("background-color: #" + color + ";"));
    else
        b->setStyleSheet(
            QString(("background-color: #" + color + "; border-radius: 15px ;").c_str())
        );
}
void styleLabel(QLabel* label, std::string&& color) {
    if (color[0] == '#') color.erase(0, 1);
    QFont font = label->font();
    font.setPointSize(30);
    font.setBold(true);
    font.setFamily("Arial");

    label->setFont(font);
    label->setFont(font);
    label->setStyleSheet(QString::fromStdString("color: #" + color + ";"));
    label->setAlignment(Qt::AlignCenter);
}

void styleWindow(
    std::string&& title, int width, int height, QMainWindow* window, std::string&& color
) {
    window->setWindowTitle(QString::fromStdString(title));
    window->setBaseSize(4, 3);
    window->setMinimumWidth(width);
    window->setStyleSheet(QString::fromStdString("background-color: #" + color + ";"));
}