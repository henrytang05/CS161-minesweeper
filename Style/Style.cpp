#include "../Style/Style.h"

void styleButton(
    QPushButton* b, std::string&& background_color, bool rounded, int width, int height,
    std::string&& text_color
) {
    if (background_color[0] == '#') background_color.erase(0, 1);
    if (text_color[0] == '#') text_color.erase(0, 1);
    b->setFixedSize(width, height);
    b->setStyleSheet(QString::fromStdString(
        "background-color: #" + background_color + "; " +
        (rounded ? "border-radius: 15px; " : "") + "font-size: 0px;" + "color: #" +
        text_color + ";"
    ));
}
void styleLabel(QLabel* label, std::string&& color, double size) {
    if (color[0] == '#') color.erase(0, 1);
    QFont font = label->font();
    font.setPointSize(size);
    font.setBold(true);
    font.setFamily("sans-serif");

    label->setFont(font);
    label->setFont(font);
    label->setStyleSheet(QString::fromStdString("color: #" + color + ";"));
    label->setAlignment(Qt::AlignCenter);
}

void styleWindow(
    std::string&& title, int width, int height, QMainWindow* window, std::string&& color
) {
    window->setWindowTitle(QString::fromStdString(title));
    window->setFixedSize(width, height);
    // window->setMinimumWidth(width);
    window->setStyleSheet(QString::fromStdString("background-color: #" + color + ";"));
}
void styleSquare(QPushButton* square, int row, int col) {
    if (row % 2 == col % 2) {
        square->setStyleSheet("background-color: #C7DCA7");
    } else {
        square->setStyleSheet("background-color: #89B9AD");
    }
}