#ifndef HOME_PAGE_H
#define HOME_PAGE_H
#include <QBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QStackedWidget>
#include <QWidget>

class HomePage : public QWidget {
    Q_OBJECT
   public:
    HomePage(QWidget* parent = nullptr);
    ~HomePage();
    void setupHomePage();

   signals:
    void newGameSignal();
    void resumeGameSignal();
    void exit();
};
#endif