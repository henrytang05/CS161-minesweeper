#ifndef HOME_PAGE_H
#define HOME_PAGE_H
#include <QBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QPushButton>
#include <QStackedWidget>
#include <QWidget>
#include <iostream>
#include <string>

#include "../../Memory/Memory.h"
#include "../../Style/Style.h"
class HomePage : public QWidget {
    Q_OBJECT
   public:
    HomePage(QWidget* parent = nullptr) { setupHomePage(); }
    ~HomePage() {}

    void setupHomePage();
};
#endif