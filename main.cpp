#include <iostream>
#include "include.h"

#include "include.h"
int main() {
#ifdef _WIN32
    system("chcp 936");
#endif
    clearScreen();
    while (!checkFiles()) {
        clearScreen();
    }
    while (true) {
        // debugTestColor();
        io::cout << _RESET;
        io::cout << CYAN("FastQA V1.1 on " + getSystem()) << io::endl;
        io::cout << io::endl;
        io::cout << _YELLOW << "[system time : " << getTimeStamp() << "("
                 << timeStampToString(getTimeStamp(), "%Y-%m-%d %H:%M:%S") << ")]" << _RESET
                 << io::endl;
        io::cout << io::endl;
        io::cout << GREEN("读取到的问题组：") << io::endl;
        fileList list = readFileList();
        for (int i = 1; i <= list.num; i++) {
            io::cout << _RED << i << _RESET << "\t";
            io::cout << list.l[i - 1].name << " (" << list.l[i - 1].wordNum << ")" << io::endl;
        }
        io::cout << io::endl;
        io::cout << CYAN("选项：") << io::endl;
        io::cout << RED("a") << "\t进行测验" << io::endl;
        io::cout << RED("b") << "\t查看测验记录" << io::endl;
        io::cout << RED("c") << "\t编辑问题组" << io::endl;
        io::cout << RED("d") << "\t新建问题组" << io::endl;
        io::cout << RED("e") << "\t导入问题组" << io::endl;
        io::cout << RED("f") << "\t导出问题组" << io::endl;
        io::cout << RED("q") << "\t退出程序" << io::endl;
        io::cout << io::endl;
        io::cout << MAGENTA("输入选项> ") << _YELLOW;
        std::string ch;
        io::cin >> ch;
        io::cout << _RESET;
        if (ch == "q") {
            return 0;
        }
        switch (ch[0]) {
        case 'a':
            startTest(list);
            break;
        case 'b':
            viewRecord();
            break;
        case 'c':
            editFileMain(list);
            break;
        case 'd':
            newFileMain(list);
            break;
        case 'e':
            loadQaFile(list);
            break;
        case 'f':
            exportQaFile(list);
            break;
        }
        clearScreen();
    }
    return 0;
}