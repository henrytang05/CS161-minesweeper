#ifndef MEMORY_H
#define MEMORY_H
/*
This is used to track memory usage.
*/

#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <iostream>
#include <string_view>
class Memory {
   public:
    friend void* operator new(size_t size);
    friend void operator delete(void* ptr, size_t size);
    friend void* operator new[](size_t size);
    friend void operator delete[](void* ptr, size_t size);
    friend void* operator new(size_t size, const char* name);
    static void PrintMemory();

   private:
    inline static long long memoryUsed = 0;
};
void customMessageHandler(
    QtMsgType type, const QMessageLogContext& context, const QString& msg
);
void* operator new(size_t size);
void operator delete(void* ptr, size_t size);
void* operator new[](size_t size);
void operator delete[](void* ptr, size_t size);
void* operator new(size_t size, const char* name);
#endif  // MEMORY_H