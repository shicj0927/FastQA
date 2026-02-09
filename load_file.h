#ifndef _LOAD_FILE_H_
#define _LOAD_FILE_H_

#include "include.h"

void loadQaFile(fileList list) {
    clearScreen();
    io::cout << CYAN("导入问题组") << io::endl;
    io::cout << io::endl;
    io::cout << CYAN("选择有效的.qa文件") << io::endl;
    auto file = dialog::openFile("FastQA 导入问题组", {"*.qa"});
    io::cout << file << io::endl;
    if (file.empty()) {
        io::pause("未选择，按任意键返回...");
        return;
    }
    std::string name = file.filename().string();
    for (auto i : list.l) {
        if (i.name == name) {
            io::pause(RED("文件已经存在，请不要重复操作，按任意键返回..."));
            return;
        }
    }
    std::filesystem::path path = "./data";
    path = path / file.filename();
    std::filesystem::copy_file(file, path, std::filesystem::copy_options::overwrite_existing);
    list.num++;
    list.l.push_back({file.filename().stem().string(), path.string(), 0});
    writeFileList(list);
    io::pause(GREEN("文件导入成功，按任意键返回..."));
}

#endif