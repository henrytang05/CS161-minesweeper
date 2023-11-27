#include "Timer.h"

#include "../../../Style/Style.h"
Timer::Timer(QWidget* parent) : QLabel(parent) {
    timerObject = new QTimer(this);
    elapsedTime = QTime(0, 0);
    // Change the interval to 500 milliseconds (half a second)
    this->startTimer();
    connect(timerObject, &QTimer::timeout, this, &Timer::updateTimerSlot);
    this->setText(QString("00:00"));
    styleTimer(this);
}
Timer::~Timer() {
    delete timerObject;
    timerObject = nullptr;
}
void Timer::startTimer() { timerObject->start(1000); }
void Timer::stopTimer() { timerObject->stop(); }
void Timer::updateTimerSlot() {
    elapsedTime = elapsedTime.addSecs(1);
    this->setText(elapsedTime.toString("mm:ss"));
}