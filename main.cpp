#include <QApplication>
#include <QDebug>
#include <QFile>
#include "HomeWindow/HomeWindow.h"
#include "Memory/Memory.h"

int main(int argc, char** argv) {   
    QFile outFile("output.txt");
    outFile.open(QIODevice::WriteOnly);
    outFile.close();
    QApplication app(argc, argv);
    
    HomeWindow* Game = new ("Homewindow") HomeWindow;

    Game->show();
    Memory::PrintMemory();
    return app.exec();
}