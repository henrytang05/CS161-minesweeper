#ifndef TIMER_H
#define TIMER_H
#include <QLabel>
#include <QTime>
#include <QTimer>
class Timer : public QTimer {
    Q_OBJECT
   public:
    Timer(QWidget* parent = nullptr);
    ~Timer();
    void startTimer();
    void stopTimer();
    void resetTimer();
    void connectTimer(QLabel*);

   signals:
    void timerUpdated();
   public slots:
    void updateTimerSlot();

   public:
    // QTimer* timerObject;
    QTime elapsedTime;
};
#endif