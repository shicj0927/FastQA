#ifndef _EDIT_FILE_H_
#define _EDIT_FILE_H_

#include "include.h"

void editFileHelp() {
    io::cout << CYAN("编辑工具使用说明：") << io::endl;
    io::cout << RED("h") << "\t显示说明" << io::endl;
    io::cout << RED("+") << "\t在末尾添加问题" << io::endl;
    io::cout << RED("+i") << "\t在第i个问题后添加问题" << io::endl;
    io::cout << RED("-") << "\t删除最后一个问题" << io::endl;
    io::cout << RED("-i") << "\t删除第i个问题" << io::endl;
    io::cout << RED(">i") << "\t移动第i个问题" << io::endl;
    io::cout << RED("A") << "\t开启连续添加模式" << io::endl;
    io::cout << RED("q") << "\t退出编辑" << io::endl;
    io::cout << io::endl;
    io::cout << CYAN("指令也支持字母格式 l=: a=+ d=- m=>，如a10等价于+10") << io::endl;
    io::cout << io::endl;
    io::cout << CYAN("在空白文件中，使用+创建第一个问题") << io::endl;
}

void editFileMain(fileList list) {
    io::cout << MAGENTA("输入问题组序号> ") << _YELLOW;
    int id;
    io::cin >> id;
    io::cout << _RESET;
    if (id <= 0 || id > list.num) {
        io::pause(RED("错误：无效的序号，按任意键返回..."));
        return;
    }
    clearScreen();
    editFileHelp();
    io::cout << io::endl;
    while (true) {
        int breakFlag = 0;
        fileData data = readFileData(list.l[id - 1]);
        io::cout << CYAN("输入h查看说明，输入q退出") << io::endl << io::endl;
        io::cout << _GREEN << "从 " << data.name << " 中读取到 " << data.num << " 个问题："
                 << _RESET << io::endl;
        for (int i = 1; i <= data.num; i++) {
            io::cout << _RED << i << _RESET << "\t" << GREEN(data.l[i - 1].que) << " ("
                     << CYAN(data.l[i - 1].hint) << ") : " << RED(data.l[i - 1].ans) << io::endl;
        }
        io::cout << io::endl;
        io::cout << MAGENTA("> ") << _YELLOW;
        std::string ord;
        io::cin >> ord;
        io::cout << _RESET;
        io::cin.ignoreLine();
        if (ord[0] == '+' || ord[0] == 'a') {
            int i;
            if (ord == "+" || ord == "a") {
                i = data.num + 1;
            } else {
                i = stringToInt(removeFirstLetter(ord));
            }
            if (i == -1) {
                io::cout << RED("输入错误") << io::endl;
                continue;
            }
            if (i <= 0 || i > data.num + 1) {
                io::cout << RED("输入超出范围") << io::endl;
                continue;
            }
            lineData tmp;
            io::cout << MAGENTA("问题> ") << _YELLOW;
            getline(io::cin, tmp.que);
            // io::cin>>tmp.que;
            io::cout << MAGENTA("提示> ") << _YELLOW;
            getline(io::cin, tmp.hint);
            // io::cin>>tmp.hint;
            io::cout << MAGENTA("答案> ") << _YELLOW;
            getline(io::cin, tmp.ans);
            // io::cin>>tmp.ans;
            data.addLine(tmp);
            io::cout << _RESET;
            for (int j = data.num; j > i + 1; j--) {
                std::swap(data.l[j - 1], data.l[j - 2]);
            }
            writeFileData(data);
        } else if (ord[0] == '-' || ord[0] == 'd') {
            int i;
            if (ord == "-" || ord == "d") {
                i = data.num;
            } else {
                i = stringToInt(removeFirstLetter(ord));
            }
            if (i == -1) {
                clearScreen();
                continue;
            }
            if (i <= 0 || i > data.num) {
                clearScreen();
                continue;
            }
            data.l.erase(data.l.begin() + i - 1);
            data.num--;
            writeFileData(data);
        } else if (ord[0] == '>' || ord[0] == 'm') {
            int i = stringToInt(removeFirstLetter(ord));
            if (i == -1) {
                clearScreen();
                continue;
            }
            if (i <= 0 || i > data.num) {
                clearScreen();
                continue;
            }
            for (int j = 1; j <= data.num; j++) {
                io::cout << j << "\t" << data.l[j - 1].que << " (" << data.l[j - 1].hint
                         << ") : " << data.l[j - 1].ans << io::endl;
            }
            io::cout << _MAGENTA << "将第 " << i << " 个问题移到哪个后面> " << _YELLOW;
            int t;
            io::cin >> t;
            io::cout << _RESET;
            if (t < 0 || t > data.num) {
                clearScreen();
                continue;
            }
            lineData tmp = data.l[i - 1];
            data.l.erase(data.l.begin() + i - 1);
            data.num--;
            data.addLine(tmp);
            for (int j = data.num; j > t + 1; j--) {
                std::swap(data.l[j - 1], data.l[j - 2]);
            }
            writeFileData(data);
        } else if (ord == "A") {
            while (true) {
                clearScreen();
                io::cout << CYAN("连续添加模式") << io::endl;
                io::cout << io::endl;
                for (int i = std::max(1, data.num - 4); i <= data.num; i++) {
                    io::cout << _RED << i << "\t" << GREEN(data.l[i - 1].que) << " ("
                             << CYAN(data.l[i - 1].hint) << ") : " << RED(data.l[i - 1].ans)
                             << io::endl;
                }
                lineData tmp;
                io::cout << io::endl;
                io::cout << CYAN("在 问题 中输入q退出连续添加模式") << io::endl;
                io::cout << CYAN("在 问题 中输入-或d删除最后一个") << io::endl;
                io::cout << io::endl;
                io::cout << MAGENTA("问题> ") << _YELLOW;
                getline(io::cin, tmp.que);
                io::cout << _RESET;
                // io::cin>>tmp.que;
                if (tmp.que == "q") {
                    breakFlag = 1;
                    break;
                }
                if (tmp.que == "-" || tmp.que == "d") {
                    if (data.num != 0) {
                        data.l.pop_back();
                        data.num--;
                        writeFileData(data);
                    }
                    continue;
                }
                io::cout << MAGENTA("提示> ") << _YELLOW;
                getline(io::cin, tmp.hint);
                // io::cin>>tmp.hint;
                io::cout << MAGENTA("答案> ") << _YELLOW;
                getline(io::cin, tmp.ans);
                // io::cin>>tmp.ans;
                data.addLine(tmp);
                io::cout << _RESET;
                writeFileData(data);
            }
        } else if (ord == "h") {
            editFileHelp();
            io::cout << io::endl;
            io::pause(MAGENTA("按任意键继续..."));
        } else if (ord == "q") {
            return;
        }
        clearScreen();
    }
}

#endif