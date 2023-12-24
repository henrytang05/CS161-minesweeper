#include "Style/Style.h"

#include "Session/Session.h"
#include "Square/Square.h"
void styleButton(QPushButton* b, QString background_color, QString text_color) {
    if (b == nullptr) {
        throw std::invalid_argument("QPushButton* b is nullptr");
    }

    if (background_color[0] == '#') background_color.remove(0, 1);
    if (text_color[0] == '#') text_color.remove(0, 1);

    QString styleSheet = "background-color: #" + background_color +
                         "; border-radius: 15px; " + "font-size: 0px;" + "color: #" +
                         text_color + ";";

    b->setFixedSize(100, 50);
    b->setStyleSheet(styleSheet);
}
void styleLabel(QLabel* label, QString color, double size) {
    if (color[0] == '#') color.remove(0, 1);
    QFont font = label->font();
    font.setPointSize(size);
    font.setBold(true);
    font.setFamily("sans-serif");

    label->setFont(font);

    QString styleSheet = "color: #" + color + "; ";
    label->setStyleSheet(styleSheet);
    label->setAlignment(Qt::AlignCenter);
}

void styleWindow(QString title, QMainWindow* window) {
    window->setWindowTitle(title);
    // window->setStyleSheet(QString::fromStdString("background-color: #" + color + ";"));
    QLinearGradient gradient(0, 0, 0, window->height());
    gradient.setColorAt(0, QColor("#FFB88C"));
    gradient.setColorAt(1, QColor("#DE6262"));
    QPalette palette;
    palette.setBrush(QPalette::Window, gradient);
    window->setPalette(palette);
    window->setAutoFillBackground(true);
}
void styleSquare(Square* square, QString color) {
    square->setFixedSize(Session::GetCellSize(), Session::GetCellSize());
    QString str = "QPushButton { border: 1px solid black;  ";

    if (!color.isEmpty()) {
        if (color[1].isDigit()) {
            if (color[0] == '#') color.remove(0, 1);
            square->setStyleSheet(str + "background-color: #" + color + ";}");
        } else {
            square->setStyleSheet(str + "background-color: " + color + ";}");
        }
        return;
    }
    if (square->row % 2 == square->col % 2) {
        square->setStyleSheet(str + "background-color: #C7DCA7;}");
    } else {
        square->setStyleSheet(str + "background-color: #89B9AD;}");
    }
}
void styleTimer(QLabel* timer, QString color, double size) {
    if (color[0] == '#') color.remove(0, 1);
    QFont font = timer->font();
    font.setPointSize(size);
    font.setBold(true);
    font.setFamily("sans-serif");
    timer->resize(250, 50);

    timer->setFont(font);
    timer->setFont(font);
    timer->setStyleSheet(QString("color: #" + color + "; background-color: red;"));
    timer->setAlignment(Qt::AlignCenter);
}