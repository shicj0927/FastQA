#ifndef _VIEW_RECORD_H_
#define _VIEW_RECORD_H_

#include "include.h"

void viewRecord() {
    clearScreen();
    io::cout << CYAN("查看历史记录") << io::endl;
    io::cout << io::endl;
    recList list = readRecList();
    io::cout << _GREEN << "读取到 " << list.num << " 条记录" << _RESET << io::endl;
    for (int i = 1; i <= list.num; i++) {
        io::cout << _RED << i << "\t" << _RESET
                 << timeStampToString(list.l[i - 1].timeStamp, "%Y-%m-%d %H:%M:%S") << " ("
                 << subString(list.l[i - 1].name, 20, 30) << ")" << io::endl;
    }
    io::cout << io::endl;
    io::cout << MAGENTA("输入记录序号> ") << _YELLOW;
    int id;
    io::cin >> id;
    if (id <= 0 || id > list.num) {
        io::pause(RED("错误，无效的序号，按任意键返回..."));
        return;
    }
    recData data = readRecData(list.l[id - 1]);
    clearScreen();
    io::cout << _CYAN << "来自 " << timeStampToString(list.l[id - 1].timeStamp, "%Y-%m-%d %H:%M:%S")
             << " 的记录" << io::endl;
    io::cout << "区分编号：" << subString(list.l[id - 1].name, 20, 30) << io::endl;
    io::cout << io::endl;
    io::cout << _YELLOW << "答题数量：" << data.num << io::endl;
    if (data.num == 0) {
        io::cout << io::endl;
        io::pause(MAGENTA("按任意键返回..."));
        return;
    }
    io::cout << _YELLOW << "耗时：" << data.getTi() << "s" << io::endl;
    io::cout << _GREEN << "正确回答：" << data.getAc() << io::endl;
    io::cout << _RED << "错误回答：" << data.getWa() << io::endl;
    io::cout << _GREEN << "正确率：";
    printf("%.2lf%%", 100.0 * data.getAc() / data.num);
    io::cout << _RESET << io::endl << io::endl;
    for (int i = 1; i <= data.num; i++) {
        if (data.l[i - 1].ac) {
            io::cout << _GREEN;
        } else {
            io::cout << _RED;
        }
        io::cout << i << "\t" << (data.l[i - 1].ac ? "[正确]" : "[错误]") << "\t"
                 << "[" << data.l[i - 1].ti << "s]\t" << data.l[i - 1].que << " ("
                 << data.l[i - 1].hint << ") : " << data.l[i - 1].ans << " (" << data.l[i - 1].ipt
                 << ")" << io::endl;
        io::cout << _RESET;
    }
    io::cout << io::endl;
    io::pause(MAGENTA("按任意键返回..."));
}

#endif