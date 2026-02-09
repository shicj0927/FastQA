#ifndef _CHECK_FILES_H
#define _CHECK_FILES_H

bool checkFiles() {
    bool ok = true;
    io::ifstream ftest("list.qal");
    if (!ftest.is_open()) {
        ok = false;
        io::cout << RED("访问问题列表文件失败……") << io::endl;
        io::cout << RED("如果这是第一次运行，请初始化文件") << io::endl;
        io::cout << RED("如果list.qal存在，请检查文件占用并重试，一定不要初始化文件") << io::endl;
        io::cout << MAGENTA("是否初始化文件(y/n)> ") << _YELLOW;
        std::string op;
        io::cin >> op;
        io::cout << _RESET;
        if (op == "y") {
            system("echo 0 > list.qal");
            system("mkdir data");
        } else {
            io::pause(GREEN("确认无占用后按任意键继续..."));
        }
    } else {
        ftest.close();
    }
    ftest.open("rec.qar");
    if (!ftest.is_open()) {
        ok = false;
        io::cout << RED("访问记录列表文件失败……") << io::endl;
        io::cout << RED("如果这是第一次运行，请初始化文件") << io::endl;
        io::cout << RED("如果rec.qar存在，请检查文件占用并重试，一定不要初始化文件") << io::endl;
        io::cout << MAGENTA("是否初始化文件(y/n)> ") << _YELLOW;
        std::string op;
        io::cin >> op;
        io::cout << _RESET;
        if (op == "y") {
            system("echo 0 > rec.qar");
            system("mkdir record");
        } else {
            io::pause(GREEN("确认无占用后按任意键继续..."));
        }
    } else {
        ftest.close();
    }
    return ok;
}

#endif
