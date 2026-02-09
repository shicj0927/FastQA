#ifndef _NEW_FILE_H_
#define _NEW_FILE_H_

#include "include.h"

fileList newFileMain(fileList &list) {
    std::string name;
    io::cout << MAGENTA("问题组名称> ") << _YELLOW;
    io::cin >> name;
    io::cout << _RESET;
    if (list.include(name)) {
        io::pause(RED("错误：该问题组已经存在，按任意键返回..."));
        return list;
    }
    list.num++;
    list.l.push_back({name, newFile(name), 0});
    writeFileList(list);
    io::cout << _GREEN << "成功：空的问题组已写入到" << list.l[list.l.size() - 1].path
             << "，按任意键返回 " << _RESET;
    io::pause("");
    return list;
}

#endif