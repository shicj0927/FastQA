#ifndef _FILE_H_
#define _FILE_H_

#include "include.h"

struct fileInfo {
    std::string name;
    std::string path;
    int wordNum;
};

struct fileList {
    int num;
    std::vector<fileInfo> l;
    fileList() {
        num = 0;
        l.clear();
    }
    bool include(std::string name) {
        for (auto i : l) {
            if (i.name == name) {
                return true;
            }
        }
        return false;
    }
};

struct lineData {
    std::string que;
    std::string hint;
    std::string ans;
};

struct fileData {
    std::string name;
    std::string path;
    int num;
    std::vector<lineData> l;
    fileData() {
        num = 0;
        l.clear();
    }
    fileInfo getInfo() { return {name, path, num}; }
    void addLine(lineData line) {
        l.push_back(line);
        num++;
    }
};

struct recInfo {
    std::string name;
    std::string path;
    int timeStamp;
    int recNum;
};

struct recList {
    int num;
    std::vector<recInfo> l;
    recList() {
        num = 0;
        l.clear();
    }
    bool include(std::string name) {
        for (auto i : l) {
            if (i.name == name) {
                return true;
            }
        }
        return false;
    }
};

struct recLine {
    std::string que;
    std::string hint;
    std::string ans;
    std::string ipt;
    bool ac;
    int ti;
};

struct recData {
    std::string name;
    std::string path;
    int num;
    int timeStamp;
    std::vector<recLine> l;
    recData() {
        num = 0;
        l.clear();
    }
    recInfo getInfo() { return {name, path, num}; }
    void addLine(recLine line) {
        l.push_back(line);
        num++;
    }
    int getAc() {
        int tot = 0;
        for (auto i : l) {
            if (i.ac) {
                tot++;
            }
        }
        return tot;
    }
    int getWa() { return num - getAc(); }
    int getTi() {
        int tot = 0;
        for (auto i : l) {
            tot += i.ti;
        }
        return tot;
    }
};

fileList readFileList() {
    fileList list;
    io::ifstream fin("list.qal");
    fin >> list.num;
    for (int i = 1; i <= list.num; i++) {
        std::string name, path;
        int wordNum;
        fin >> name;
        path = "./data/" + name + ".qa";
        // std::cerr << path << std::endl;
        io::ifstream finf(path.c_str());
        finf >> wordNum;
        finf.close();
        list.l.push_back({name, path, wordNum});
    }
    fin.close();
    return list;
}

void writeFileList(fileList list) {
    io::ofstream fout("list.qal");
    fout << list.num << io::endl;
    for (int i = 1; i <= list.num; i++) {
        fout << list.l[i - 1].name << io::endl;
    }
    fout.close();
}

std::string newFile(std::string name) {
    std::string path = "./data/" + name + ".qa";
    io::ofstream fout(path.c_str());
    fout << 0 << io::endl;
    fout.close();
    return path;
}

fileData readFileData(fileInfo info) {
    fileData data;
    data.name = info.name;
    data.path = info.path;
    io::ifstream fin(data.path.c_str());
    fin >> data.num;
    fin.ignoreLine();
    for (int i = 1; i <= data.num; i++) {
        lineData tmp;
        getline(fin, tmp.que);
        getline(fin, tmp.hint);
        getline(fin, tmp.ans);
        tmp.que = removeFirstLetter(tmp.que);
        tmp.hint = removeFirstLetter(tmp.hint);
        tmp.ans = removeFirstLetter(tmp.ans);
        data.l.push_back(tmp);
    }
    fin.close();
    return data;
}

void writeFileData(fileData data) {
    io::ofstream fout(data.path.c_str());
    fout << data.num << io::endl;
    for (auto i : data.l) {
        fout << "Q" << i.que << io::endl;
        fout << "H" << i.hint << io::endl;
        fout << "A" << i.ans << io::endl;
    }
    fout.close();
}

void writeRecList(recList rec) {
    io::ofstream fout("rec.qar");
    fout << rec.num << io::endl;
    for (int i = 1; i <= rec.num; i++) {
        fout << rec.l[i - 1].name << io::endl;
    }
    fout.close();
}

recList readRecList() {
    recList rec;
    io::ifstream fin("rec.qar");
    fin >> rec.num;
    for (int i = 1; i <= rec.num; i++) {
        std::string name, path;
        int recNum;
        int timeStamp;
        fin >> name;
        path = "./record/" + name + ".rec";
        io::ifstream finf(path.c_str());
        finf >> recNum >> timeStamp;
        finf.close();
        rec.l.push_back({name, path, timeStamp, recNum});
    }
    fin.close();
    return rec;
}

recData readRecData(recInfo info) {
    recData data;
    data.name = info.name;
    data.path = info.path;
    io::ifstream fin(data.path.c_str());
    fin >> data.num >> data.timeStamp;
    fin.ignoreLine();
    for (int i = 1; i <= data.num; i++) {
        recLine tmp;
        getline(fin, tmp.que);
        getline(fin, tmp.hint);
        getline(fin, tmp.ans);
        getline(fin, tmp.ipt);
        std::string _ac, _ti;
        getline(fin, _ac);
        getline(fin, _ti);
        tmp.que = removeFirstLetter(tmp.que);
        tmp.hint = removeFirstLetter(tmp.hint);
        tmp.ans = removeFirstLetter(tmp.ans);
        tmp.ipt = removeFirstLetter(tmp.ipt);
        tmp.ac = removeUnimportantChar(_ac) == "C1";
        tmp.ti = stringToInt(removeFirstLetter(_ti));
        data.l.push_back(tmp);
    }
    fin.close();
    return data;
}

void writeRecData(recData data) {
    io::ofstream fout(data.path.c_str());
    fout << data.num << " " << data.timeStamp << io::endl;
    for (auto i : data.l) {
        fout << "Q" << i.que << io::endl;
        fout << "H" << i.hint << io::endl;
        fout << "A" << i.ans << io::endl;
        fout << "I" << i.ipt << io::endl;
        fout << "C" << (i.ac ? "1" : "0") << io::endl;
        fout << "T" << i.ti << io::endl;
    }
    fout.close();
}

recInfo newRec() {
    int ti = getTimeStamp();
    std::string name = timeStampToString(ti) + "-" + randString(10);
    std::string path = "./record/" + name + ".rec";
    recInfo info = {name, path, ti, 0};
    io::ofstream fout(path.c_str());
    fout << 0 << " " << ti << io::endl;
    fout.close();
    recList list = readRecList();
    list.num++;
    list.l.push_back(info);
    writeRecList(list);
    return info;
}

#endif