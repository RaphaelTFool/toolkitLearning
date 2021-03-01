#include <iostream>
#include "Util/util.h"
#include "Util/logger.h"
#include "Util/List.h"

using namespace toolkit;

int main() {
    Logger::Instance().add(std::make_shared<ConsoleChannel>());
    Logger::Instance().setWriter(std::make_shared<AsyncLogWriter>());
    List<int> li;
    li.emplace_back(1);
    li.emplace_front(2);
    li.for_each([](int i) {
        InfoL << i << ", ";
    });
    li.clear();
    InfoL << std::endl;
}