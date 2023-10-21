#include "Square.h"
void Square::setMine() { this->isMine = true; }
bool Square::getIsMine() { return this->isMine; }
bool Square::getIsRevealed() { return this->isRevealed; }
void Square::setAsRevealed() {
    squareRevealed++;
    this->isRevealed = true;
}
void Square::setAsNotRevealed() {
    squareRevealed--;
    this->isRevealed = false;
}