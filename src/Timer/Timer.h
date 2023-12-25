#ifndef TIMER_H
#define TIMER_H
#include <QLabel>
#include <QObject>
#include <QTime>
#include <QTimer>
class Timer : public QTimer {
    Q_OBJECT
   public:
    Timer(QObject* parent = nullptr);
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
    QTime elapsedTime;
};
#endif