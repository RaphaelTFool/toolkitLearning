
#include <signal.h>
#include <iostream>
#include "Util/CMD.h"
#include "Util/util.h"
#include "Util/logger.h"

using namespace std;
using namespace toolkit;

class CMD_main : public CMD {
public:
    CMD_main() {
        _parser.reset(new OptionParser(nullptr));

#if !defined(_WIN32)
        (*_parser) << Option('d',/*该选项简称，如果是\x00则说明无简称*/
                             "daemon",/*该选项全称,每个选项必须有全称；不得为null或空字符串*/
                             Option::ArgNone,/*该选项后面必须跟值*/
                             nullptr,/*该选项默认值*/
                             false,/*该选项是否必须赋值，如果没有默认值且为ArgRequired时用户必须提供该参数否则将抛异常*/
                             "是否以Daemon方式启动",/*该选项说明文字*/
                             nullptr);
#endif//!defined(_WIN32)

        (*_parser) << Option('l',/*该选项简称，如果是\x00则说明无简称*/
                             "level",/*该选项全称,每个选项必须有全称；不得为null或空字符串*/
                             Option::ArgRequired,/*该选项后面必须跟值*/
                             to_string(LTrace).data(),/*该选项默认值*/
                             false,/*该选项是否必须赋值，如果没有默认值且为ArgRequired时用户必须提供该参数否则将抛异常*/
                             "日志等级,LTrace~LError(0~4)",/*该选项说明文字*/
                             nullptr);

        (*_parser) << Option('m',/*该选项简称，如果是\x00则说明无简称*/
                             "max_day",/*该选项全称,每个选项必须有全称；不得为null或空字符串*/
                             Option::ArgRequired,/*该选项后面必须跟值*/
                             "7",/*该选项默认值*/
                             false,/*该选项是否必须赋值，如果没有默认值且为ArgRequired时用户必须提供该参数否则将抛异常*/
                             "日志最多保存天数",/*该选项说明文字*/
                             nullptr);

        (*_parser) << Option('c',/*该选项简称，如果是\x00则说明无简称*/
                             "config",/*该选项全称,每个选项必须有全称；不得为null或空字符串*/
                             Option::ArgRequired,/*该选项后面必须跟值*/
                             (exeDir() + "config.ini").data(),/*该选项默认值*/
                             false,/*该选项是否必须赋值，如果没有默认值且为ArgRequired时用户必须提供该参数否则将抛异常*/
                             "配置文件路径",/*该选项说明文字*/
                             nullptr);

        (*_parser) << Option('a',/*该选项简称，如果是\x00则说明无简称*/
                             "an-example",/*该选项全称,每个选项必须有全称；不得为null或空字符串*/
                             Option::ArgNone,/*该选项后面不需跟值*/
                             nullptr,/*该选项默认值*/
                             false,/*该选项是否必须赋值，如果没有默认值且为ArgRequired时用户必须提供该参数否则将抛异常*/
                             "测试用例无参数",/*该选项说明文字*/
                             nullptr);

        (*_parser) << Option('b',/*该选项简称，如果是\x00则说明无简称*/
                             "argRequired",/*该选项全称,每个选项必须有全称；不得为null或空字符串*/
                             Option::ArgRequired,/*该选项后面必须跟值*/
                             "b parameter required",/*该选项默认值*/
                             true,/*该选项是否必须赋值，如果没有默认值且为ArgRequired时用户必须提供该参数否则将抛异常*/
                             "测试用例必带参数",/*该选项说明文字*/
                             nullptr);

        (*_parser) << Option('o',/*该选项简称，如果是\x00则说明无简称*/
                             "argOptional",/*该选项全称,每个选项必须有全称；不得为null或空字符串*/
                             Option::ArgOptional,/*该选项后面必须跟值*/
                             "o parameter optional",/*该选项默认值*/
                             true,/*该选项是否必须赋值，如果没有默认值且为ArgRequired时用户必须提供该参数否则将抛异常*/
                             "测试用例选参数",/*该选项说明文字*/
                             nullptr);

#if defined(ENABLE_VERSION)
        (*_parser) << Option('v', "version", Option::ArgNone, nullptr, false, "显示版本号",
                             [](const std::shared_ptr<ostream> &stream, const string &arg) -> bool {
                                 //版本信息
                                 *stream << "编译日期: " << build_time << std::endl;
                                 *stream << "当前git分支: " << branch_name << std::endl;
                                 *stream << "当前git hash值: " << commit_hash << std::endl;
                                 throw ExitException();
                             });
#endif
    }

    ~CMD_main() override{}
    const char *description() const override {
        return "主程序命令参数";
    }
};

int main(int argc, char* argv[]) {
    //设置日志
    Logger::Instance().add(std::make_shared<ConsoleChannel>());
    Logger::Instance().setWriter(std::make_shared<AsyncLogWriter>());
    //InfoL << "测试CMD接口:\n";
    //CMD cmd;
    //try {
    //    cmd(argc, argv);
    //} catch (std::excetpion& ex) {
    //    InfoL << ex.what();
    //    return 0;
    //}

    CMD_main cmd_main;
    InfoL << "测试CMD_main接口:\n";
    try {
        cmd_main.operator()(argc, argv);
    } catch (ExitException&) {
        return 0;
    } catch (std::exception &ex) {
        cout << ex.what() << endl;
        return -1;
    }

    auto a = cmd_main["an-example"];
    auto b = cmd_main["argRequired"];
    auto o = cmd_main["argOptional"];

    InfoL << "a = " << a << ", b = " << b << endl;
    InfoL << "o = " << o << endl;

    return 0;
}
