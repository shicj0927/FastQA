#ifndef _START_TEST_H_
#define _START_TEST_H_

#include "include.h"

void startTest(fileList list) {
    io::cout << MAGENTA("输入问题组序号> ");
    int id;
    io::cin >> id;
    if (id <= 0 || id > list.num) {
        io::pause(RED("错误：无效的序号，按任意键返回..."));
        return;
    }
    clearScreen();
    fileData data = readFileData(list.l[id - 1]);
    if (data.num == 0) {
        io::pause(RED("错误：问题组不可为空，按任意键返回..."));
        return;
    }
    recInfo info = newRec();
    recData rdata;
    rdata.name = info.name;
    rdata.path = info.path;
    rdata.timeStamp = info.timeStamp;
    std::queue<lineData> q;
    int num = 0, tot = 0, ac = 0, wa = 0, tiTot = 0;
    while (!q.empty()) {
        q.pop();
    }
    for (int i = 1; i <= data.num; i++) {
        q.push(data.l[i - 1]);
        tot++;
    }
    int startTime = time(0);
    io::cin.ignoreLine();
    while (!q.empty()) {
        clearScreen();
        int timeTmp = time(0);
        num++;
        io::cout << CYAN("输入q结束测验") << io::endl << io::endl;
        if (num == 1) {
            io::cout << _YELLOW;
            printf("\n%02d:%02d  ", tiTot / 60, tiTot % 60);
            io::cout << _MAGENTA;
            printf("%03d/%03d  ", num, tot);
            io::cout << _GREEN;
            printf("%03d", ac);
            io::cout << MAGENTA("/");
            io::cout << _RED;
            printf("%03d  ", wa);
            io::cout << _GREEN;
            printf("??.??%%\n\n");
            io::cout << _RESET;
        } else {
            io::cout << _YELLOW;
            printf("\n%02d:%02d  ", tiTot / 60, tiTot % 60);
            io::cout << _MAGENTA;
            printf("%03d/%03d  ", num, tot);
            io::cout << _GREEN;
            printf("%03d", ac);
            io::cout << MAGENTA("/");
            io::cout << _RED;
            printf("%03d  ", wa);
            io::cout << _GREEN;
            printf("%.2lf%%\n\n", 100.0 * ac / (num - 1));
            io::cout << _RESET;
        }
        io::cout << "问题：" << GREEN(q.front().que) << io::endl;
        io::cout << "提示：" << GREEN(q.front().hint) << io::endl;
        io::cout << io::endl;
        io::cout << "答案：" << _YELLOW;
        std::string ipt;
        getline(io::cin, ipt);
        io::cout << _RESET;
        recLine line;
        line.ti = time(0) - timeTmp;
        // io::cin>>ipt;
        bool ok;
        if (checkAns(ipt, q.front().ans)) {
            ac++;
            ok = true;
        } else if (ipt == "q") {
            num--;
            break;
        } else {
            io::cout << io::endl;
            io::cout << _RED << "错误，答案是 " << q.front().ans << io::endl;
            io::cout << io::endl;
            io::pause(MAGENTA("按任意键继续..."));
            wa++;
            ok = false;
        }
        line.que = q.front().que;
        line.hint = q.front().hint;
        line.ans = q.front().ans;
        line.ipt = ipt;
        line.ac = ok;
        rdata.addLine(line);
        writeRecData(rdata);
        tiTot += line.ti;
        q.pop();
    }
    clearScreen();
    io::cout << CYAN("答题结束") << io::endl;
    io::cout << io::endl << _GREEN;
    io::cout << _YELLOW << "共 " << tot << " 题" << io::endl;
    io::cout << _YELLOW << "答 " << num << " 题" << io::endl;
    io::cout << _YELLOW << "耗时 " << tiTot << "s" << io::endl;
    io::cout << _GREEN << "正确 " << ac << " 题" << io::endl;
    io::cout << _RED << "错误 " << wa << " 题" << io::endl;
    io::cout << _GREEN << "正确率 ";
    printf("%.2lf%%\n", 100.0 * ac / num);
    io::cout << io::endl;
    io::cout << _CYAN << "数据已写入 " << rdata.path << io::endl << io::endl;
    io::pause(MAGENTA("按任意键继续..."));
}

#endif