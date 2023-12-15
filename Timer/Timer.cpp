#include "Timer.h"

Timer::Timer(QWidget* parent) : QTimer(parent) {
    elapsedTime = QTime(0, 0);

    connect(this, &QTimer::timeout, this, &Timer::updateTimerSlot);
    // this->setText(QString("00:00"));
    // styleTimer(this);
}
Timer::~Timer() {}
void Timer::startTimer() { this->start(1000); }
void Timer::stopTimer() { this->stop(); }
void Timer::resetTimer() { this->elapsedTime.setHMS(0, 0, 0); }
void Timer::updateTimerSlot() {
    elapsedTime = elapsedTime.addSecs(1);
    emit timerUpdated();
    // this->setText(elapsedTime.toString("mm:ss"));
}
void Timer::connectTimer(QLabel* label) {
    QObject::connect(this, &QTimer::timeout, label, [this, label]() {
        label->setText(elapsedTime.toString("mm:ss"));
    });
}