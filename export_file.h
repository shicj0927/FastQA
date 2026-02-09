#ifndef _EXPORT_FILE_H_
#define _EXPORT_FILE_H_

#include "include.h"

void exportQaFile(fileList list) {
    io::cout << io::endl;
    io::cout << CYAN("导出问题组") << io::endl;
    io::cout << MAGENTA("问题组序号> ") << _YELLOW;
    int id;
    io::cin >> id;
    if (id <= 0 || id > list.num) {
        io::pause(RED("输入错误，按任意键返回..."));
        return;
    }
    std::string name = list.l[id - 1].name;
    std::string path = list.l[id - 1].path;
    io::cout << CYAN("选择保存位置") << io::endl;
    auto file = dialog::saveFile("FastQA 导出问题组", path);
    std::filesystem::copy_file(path, file, std::filesystem::copy_options::overwrite_existing);
    io::pause(GREEN("文件导出成功，按任意键返回..."));
}

#endif