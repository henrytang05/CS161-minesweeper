#include "Style/Style.h"

#include "Session/Session.h"
#include "Square/Square.h"
void styleButton(
    QPushButton* b, std::string&& background_color, bool rounded, int width, int height,
    std::string&& text_color
) {
    if (b == nullptr) {
        throw std::invalid_argument("QPushButton* b is nullptr");
    }

    std::string styleSheet = "background-color: #" + background_color + "; " +
                             (rounded ? "border-radius: 15px; " : "") +
                             "font-size: 0px;" + "color: #" + text_color + ";";

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
    label->setStyleSheet(QString::fromStdString("color: #" + color + ";"));
    label->setAlignment(Qt::AlignCenter);
}

void styleWindow(std::string&& title, QMainWindow* window, std::string&& color) {
    window->setWindowTitle(QString::fromStdString(title));
    window->setStyleSheet(QString::fromStdString("background-color: #" + color + ";"));
}
void styleSquare(Square* square, std::string&& color) {
    square->setFixedSize(Session::GetCellSize(), Session::GetCellSize());
    QString str = std::move(QString("QPushButton { border: 0px solid black;  "));
    if (!color.empty()) {
        if (std::isdigit(color[1])) {
            if (color[0] == '#') color.erase(0, 1);
            square->setStyleSheet(
                str + QString::fromStdString("background-color: #" + color + ";}")
            );
        } else {
            square->setStyleSheet(
                str + QString::fromStdString("background-color: " + color + ";}")
            );
        }
        return;
    }
    if (square->row % 2 == square->col % 2) {
        square->setStyleSheet(str + QString("background-color: #C7DCA7;}"));
    } else {
        square->setStyleSheet(str + QString("background-color: #89B9AD;}"));
    }
}
void styleTimer(QLabel* timer, std::string&& color, double size) {
    if (color[0] == '#') color.erase(0, 1);
    QFont font = timer->font();
    font.setPointSize(size);
    font.setBold(true);
    font.setFamily("sans-serif");
    timer->resize(250, 50);

    timer->setFont(font);
    timer->setFont(font);
    timer->setStyleSheet(
        QString::fromStdString("color: #" + color + "; background-color: red;")
    );
    timer->setAlignment(Qt::AlignCenter);
}