#include <iostream>
#include "Util/util.h"
#include "Util/File.h"
#include "Util/logger.h"

using namespace toolkit;

int main() {
    Logger::Instance().add(std::make_shared<ConsoleChannel>());
    Logger::Instance().setWriter(std::make_shared<AsyncLogWriter>());

    InfoL << "测试文件操作接口:\n";
    InfoL << "当前目录: " << exeDir() << std::endl;
    File::create_path("test/1/", 0755);
    auto p = File::parentDir(exeDir());
    p = File::parentDir(p);
    p = File::parentDir(p);
    auto file = p + "debug/test_File.cpp";
    auto content = File::loadFile(file.data());
    std::cout << content;
    File::create_file("test/1/test.cpp", "a+");
    File::saveFile(content, "test/1/test.cpp");
    auto absp = File::absolutePath(".", ".", true);
    std::cout << absp << std::endl;
    File::delete_file("test");
}