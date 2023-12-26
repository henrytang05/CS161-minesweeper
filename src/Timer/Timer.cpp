#include "Timer.h"

Timer::Timer(QObject* parent) : QTimer(parent) {
    elapsedTime = QTime(0, 0);

    connect(this, &QTimer::timeout, this, &Timer::updateTimerSlot);
}
Timer::~Timer() {}
void Timer::startTimer() { this->start(1000); }
void Timer::stopTimer() { this->stop(); }
void Timer::resetTimer() { this->elapsedTime.setHMS(0, 0, 0); }
void Timer::updateTimerSlot() {
    elapsedTime = elapsedTime.addSecs(1);
    emit timerUpdated();
}
void Timer::connectTimer(QLabel* label) {
    QObject::connect(this, &QTimer::timeout, label, [this, label]() {
        label->setText(QString::fromStdString(elapsedTime.toString("mm:ss").toStdString())
        );
    });
}