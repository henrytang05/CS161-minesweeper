#ifndef HOME_PAGE_H
#define HOME_PAGE_H
#include <QBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QStackedWidget>
#include <QWidget>

// #include "../../Memory/Memory.h"
#include "../../Style/Style.h"
class HomePage : public QWidget {
    Q_OBJECT
   public:
    HomePage(QStackedWidget* parent = nullptr) { setupHomePage(); }
    ~HomePage() {}
    void setupHomePage();

   signals:
    void newGameClicked();
    void resumeGameClicked();
};
#endif