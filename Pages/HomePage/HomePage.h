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
    HomePage(QStackedWidget* parent = nullptr) { setupHomePage(); }
    ~HomePage() {}
    void setupHomePage();

    //    public slots:
    //     void newGameSlot();
    // void resumeGameSlot();
   signals:
    void newGameClicked();
    void resumeGameClicked();
};
#endif