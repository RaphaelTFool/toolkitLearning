#include <iostream>
#include "Util/util.h"
#include "Util/logger.h"

using namespace toolkit;
using namespace std;

class Obj {
public:
    Obj(int x, int y) : real(x), imag(y) {}
    ~Obj() {}
    friend ostream& operator<<(ostream& os, const Obj& obj) {
        os << obj.real << " + " << obj.imag << "i";
        return os;
    }
private:
    int real{0};
    int imag{0};
};

int main() {
    Logger::Instance().add(std::make_shared<ConsoleChannel>("console_channel", LDebug));
    Logger::Instance().add(std::make_shared<FileChannel>("file_channel", "log/", LDebug));
    Logger::Instance().setWriter(std::make_shared<AsyncLogWriter>());

    DebugL << "hello to a logger";
    InfoL << "a = " << 100;
    TraceL << "f = " << 3.14;
    WarnL << "obj = " << Obj(3, 4);
    ErrorL << "check error";
}