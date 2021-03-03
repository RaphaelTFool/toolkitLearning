#include <iostream>
#include <memory>
#include <string>
#include <signal.h>
#include "Util/util.h"
#include "Util/logger.h"
#include "Util/NoticeCenter.h"

using namespace std;
using namespace toolkit;

bool g_isExit = false;

int main() {
    Logger::Instance().add(make_shared<ConsoleChannel>("console_channel", LDebug));
    Logger::Instance().setWriter(make_shared<AsyncLogWriter>());
    signal(SIGINT, [](int){ g_isExit = true; });

    //注册在同一个名字上的函数类型必须一致，否则会产生未知错误
    //参数类型不一致导致的内存越界
    NoticeCenter::Instance().addListener(0, "test1", [](char &a, int &b, const char* &c, const string& d) {
        DebugL << "a = " << a << ", b = " << b << ", c = " << c << ", d = " << d;
        NoticeCenter::Instance().delListener(0, "test1");
        NoticeCenter::Instance().addListener(0, "test1", [](char &a, int &b, const char* &c, const string& d) {
            InfoL << "a = " << a << ", b = " << b << ", c = " << c << ", d = " << d;
        });
    });

    NoticeCenter::Instance().addListener(0, "test2", [](const string& a, const char* &b, int &c, char &d) {
        TraceL << "a = " << a << ", b = " << b << ", c = " << c << ", d = " << d;
        NoticeCenter::Instance().delListener(0, "test2");
        NoticeCenter::Instance().addListener(0, "test2", [](const string& a, const char* &b, int &c, char &d){
            ErrorL << "a = " << a << ", b = " << b << ", c = " << c << ", d = " << d;
        });
    });

    int a = 0;
    while (!g_isExit) {
        const char* b = "what's UP";
        char c = '@';
        string d("shit");
        NoticeCenter::Instance().emitEvent("test1", c, ++a, (const char *)"b", d);
        NoticeCenter::Instance().emitEvent("test2", d, b, a, c);
        sleep(1);
    }
}