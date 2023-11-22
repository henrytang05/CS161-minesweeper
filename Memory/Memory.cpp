#include "memory.h"

void customMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    Q_UNUSED(context);

    QString txt;
    switch (type) {
        case QtInfoMsg:
            txt = QString("Info: %1").arg(msg);
            break;
        // You can also handle other message types if needed
    }

    QFile outFile("output.txt");
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&outFile);
    ts << txt;
}

void* operator new(size_t size) {
    qInstallMessageHandler(customMessageHandler);
    Memory::memoryUsed += size;
    qInfo() << "Allocated " <<  size << " bytes\n";
    Memory::PrintMemory();
    return malloc(size);
}
void* operator new(size_t size, const char* name) {
    qInstallMessageHandler(customMessageHandler);
    Memory::memoryUsed += size;
    qInfo() << "Allocated " << size << " bytes for " << name << "\n";
    Memory::PrintMemory();
    return malloc(size);
}

void* operator new[](size_t size) {
    qInstallMessageHandler(customMessageHandler);
    Memory::memoryUsed += size;
    qInfo() << "Array: Allocated " <<  size << " bytes\n";
    Memory::PrintMemory();

    return malloc(size);
}
void operator delete(void* ptr, size_t size) {
    qInstallMessageHandler(customMessageHandler);
    Memory::memoryUsed -= size;
    qInfo() << "Freed " <<  size << " bytes\n";
    Memory::PrintMemory();

    free(ptr);
}


void operator delete[](void* ptr, size_t size) {
    qInstallMessageHandler(customMessageHandler);
    Memory::memoryUsed -= size;
    qInfo() << "Freed " <<  size << " bytes\n";
    Memory::PrintMemory();
    free(ptr);
}
void Memory::PrintMemory() { 
     qInstallMessageHandler(customMessageHandler);
     qInfo() << "Memory used: " << memoryUsed << '\n'; 
}

