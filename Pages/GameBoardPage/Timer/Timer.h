#ifndef TIMER_H
#define TIMER_H
#include <QLabel>
#include <QTime>
#include <QTimer>
class Timer : public QLabel {
    Q_OBJECT
   public:
    Timer(QWidget* parent = nullptr);
    ~Timer();
    void startTimer();
    void stopTimer();

   signals:
    void timerUpdated();
   public slots:
    void updateTimerSlot();

   private:
    QTimer* timerObject;
    QTime elapsedTime;
};
#endif