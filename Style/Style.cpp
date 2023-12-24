#include "Style/Style.h"

#include "Session/Session.h"
#include "Square/Square.h"
void styleButton(
    QPushButton* b, std::string&& background_color, std::string&& text_color
) {
    if (b == nullptr) {
        throw std::invalid_argument("QPushButton* b is nullptr");
    }

    QString styleSheet = QString::fromStdString(
        "background-color: #" + background_color + "; border-radius: 15px; " +
        "font-size: 0px;" + "color: #" + text_color +
        "; font-family: 'Arial'; font-size: 14px; font-weight: bold; "
    );

    b->setFixedSize(100, 50);
    b->setStyleSheet(styleSheet);
}
void styleLabel(QLabel* label, std::string&& color, double size) {
    QFont font = label->font();
    font.setPointSize(size);
    font.setBold(true);
    font.setFamily("sans-serif");

    label->setFont(font);

    QString styleSheet = QString::fromStdString("color: #" + color + ";");
    label->setStyleSheet(styleSheet);
    label->setAlignment(Qt::AlignCenter);
}

void styleWindow(QMainWindow* window) {
    QLinearGradient gradient(0, 0, 0, window->height());
    gradient.setColorAt(0, QColor("#FFB88C"));
    gradient.setColorAt(1, QColor("#DE6262"));
    QPalette palette;
    palette.setBrush(QPalette::Window, gradient);
    window->setPalette(palette);
    window->setAutoFillBackground(true);
}
void styleSquare(Square* square, std::string&& color) {
    square->setFixedSize(Session::GetCellSize(), Session::GetCellSize());

    if (color != "") {
        if (!isdigit(color[1]))
            square->setStyleSheet(
                QString::fromStdString("background-color: " + color + ";")
            );
        return;
        square->setStyleSheet(QString::fromStdString("background-color: #" + color + ";")
        );
    }
    if (square->row % 2 == square->col % 2) {
        square->setStyleSheet(QString::fromStdString("background-color: #C7DCA7;"));
    } else {
        square->setStyleSheet(QString::fromStdString("background-color: #89B9AD;"));
    }
}
void styleTimer(QLabel* timer, std::string&& color, double size) {
    QFont font = timer->font();
    font.setPointSize(size);
    font.setBold(true);
    font.setFamily("sans-serif");
    timer->resize(250, 50);

    timer->setFont(font);
    timer->setStyleSheet(QString::fromStdString("color: #" + color + "; "));
    timer->setAlignment(Qt::AlignCenter);
}