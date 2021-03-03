#include <iostream>
#include "Util/util.h"
#include "Util/logger.h"
#include "Util/MD5.h"

using namespace toolkit;

int main() {
    Logger::Instance().add(std::make_shared<ConsoleChannel>("console_channel", LDebug));
    Logger::Instance().setWriter(std::make_shared<AsyncLogWriter>());

    auto mm = MD5("raphael");
    DebugL << "origin << " << mm;
    DebugL << "rawdigest: " << mm.rawdigest();
    DebugL << "hexdigest: " << mm.hexdigest();
    auto mm2 = MD5(mm.hexdigest());
    InfoL << "mm2 = " << mm2.rawdigest();
}