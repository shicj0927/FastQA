/*******************************************
                   io.h
         By shicj0927 with ChatGPT
   自动处理windows终端编码问题和文件名乱码
                 2026.2.7
 ******************************************
    io::cin
    io::cout
    io::endl
    io::cin.ignoreLine()
    io::ifstream
    io::ofstream
    io::pause()
    io::pause("msg")
    注意：程序内部要求使用utf8编码
          代码应使用utf8编码保存
 ******************************************/

#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <limits>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

namespace io {

#ifdef _WIN32

// ================= 编码转换 =================

inline std::string UTF8ToGBK(const std::string &utf8) {
    if (utf8.empty())
        return {};
    int wideLen = MultiByteToWideChar(CP_UTF8, 0, utf8.data(), (int)utf8.size(), nullptr, 0);
    if (wideLen <= 0)
        return {};
    std::wstring wideStr(wideLen, 0);
    MultiByteToWideChar(CP_UTF8, 0, utf8.data(), (int)utf8.size(), wideStr.data(), wideLen);

    int len = WideCharToMultiByte(936, 0, wideStr.data(), wideLen, nullptr, 0, nullptr, nullptr);
    if (len <= 0)
        return {};
    std::string gbk(len, 0);
    WideCharToMultiByte(936, 0, wideStr.data(), wideLen, gbk.data(), len, nullptr, nullptr);
    return gbk;
}

inline std::string GBKToUTF8(const std::string &gbk) {
    if (gbk.empty())
        return {};
    int wideLen = MultiByteToWideChar(936, 0, gbk.data(), (int)gbk.size(), nullptr, 0);
    if (wideLen <= 0)
        return {};
    std::wstring wideStr(wideLen, 0);
    MultiByteToWideChar(936, 0, gbk.data(), (int)gbk.size(), wideStr.data(), wideLen);

    int len =
        WideCharToMultiByte(CP_UTF8, 0, wideStr.data(), wideLen, nullptr, 0, nullptr, nullptr);
    if (len <= 0)
        return {};
    std::string utf8(len, 0);
    WideCharToMultiByte(CP_UTF8, 0, wideStr.data(), wideLen, utf8.data(), len, nullptr, nullptr);
    return utf8;
}

inline void EnableANSI() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE)
        return;
    DWORD mode = 0;
    if (!GetConsoleMode(hOut, &mode))
        return;
    mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, mode);
    SetConsoleOutputCP(936);
    SetConsoleCP(936);
}

struct ConsoleInit {
    ConsoleInit() { EnableANSI(); }
};
static ConsoleInit __console_init;

#endif

// ================= 基类输入流 =================

class BaseIn {
  public:
    virtual std::istream &stream() = 0;
    virtual bool needConvert() const = 0;
    virtual ~BaseIn() = default;
};

// ================= 彩色控制符 =================

namespace color {
constexpr const char *reset = "\033[0m";
constexpr const char *red = "\033[31m";
constexpr const char *green = "\033[32m";
constexpr const char *yellow = "\033[33m";
constexpr const char *blue = "\033[34m";
constexpr const char *magenta = "\033[35m";
constexpr const char *cyan = "\033[36m";
} // namespace color

struct Endl {};
inline Endl endl;

// ================= Cout =================

class Cout {
  public:
    template <typename T> Cout &operator<<(const T &val) {
#ifdef _WIN32
        std::ostringstream oss;
        oss << val;
        std::cout << UTF8ToGBK(oss.str());
#else
        std::cout << val;
#endif
        return *this;
    }

    Cout &operator<<(std::ostream &(*pf)(std::ostream &)) {
        std::cout << pf;
        return *this;
    }

    Cout &operator<<(Endl) {
        std::cout << "\n";
        return *this;
    }
};

inline Cout cout;

// ================= Cin =================

class Cin : public BaseIn {
  public:
    std::istream &stream() override { return std::cin; }

    bool needConvert() const override { return true; }

    Cin &operator>>(std::string &s) {
#ifdef _WIN32
        std::string tmp;
        std::cin >> tmp;
        s = GBKToUTF8(tmp);
#else
        std::cin >> s;
#endif
        return *this;
    }

    template <typename T> Cin &operator>>(T &val) {
        std::cin >> val;
        return *this;
    }

    void ignoreLine() { std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); }
};

inline Cin cin;

// ================= ofstream =================

class ofstream {
    std::ofstream fs;

  public:
    ofstream() = default;

    ofstream(const std::string &filename, std::ios::openmode mode = std::ios::out) {
        open(filename, mode);
    }

    bool open(const std::string &filename, std::ios::openmode mode = std::ios::out) {
#ifdef _WIN32
        std::string gbkName = UTF8ToGBK(filename);
        fs.open(gbkName, mode);
#else
        fs.open(filename, mode);
#endif
        return fs.is_open();
    }

    void close() { fs.close(); }

    bool is_open() const { return fs.is_open(); }

    template <typename T> ofstream &operator<<(const T &val) {
        std::ostringstream oss;
        oss << val;
        fs << oss.str(); // 文件内容始终 UTF8
        return *this;
    }

    ofstream &operator<<(std::ostream &(*pf)(std::ostream &)) {
        fs << pf;
        return *this;
    }

    ofstream &operator<<(Endl) {
        fs << "\n";
        return *this;
    }
};

// ================= ifstream =================

class ifstream : public BaseIn {
    std::ifstream fs;

  public:
    ifstream() = default;

    ifstream(const std::string &filename, std::ios::openmode mode = std::ios::in) {
        open(filename, mode);
    }

    bool open(const std::string &filename, std::ios::openmode mode = std::ios::in) {
#ifdef _WIN32
        std::string gbkName = UTF8ToGBK(filename);
        fs.open(gbkName, mode);
#else
        fs.open(filename, mode);
#endif
        return fs.is_open();
    }

    std::istream &stream() override { return fs; }

    bool needConvert() const override { return false; }

    bool is_open() const { return fs.is_open(); }

    void close() { fs.close(); }

    template <typename T> ifstream &operator>>(T &val) {
        fs >> val;
        return *this;
    }

    void ignoreLine() { fs.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); }
};

// ================= 统一 getline =================

inline void getline(BaseIn &in, std::string &s) {
#ifdef _WIN32
    std::string tmp;
    std::getline(in.stream(), tmp);
    if (in.needConvert())
        s = GBKToUTF8(tmp);
    else
        s = tmp;
#else
    std::getline(in.stream(), s);
#endif
}

// ================= pause =================

inline void pause(const std::string &msg = "Press any key to continue...") {
    cout << msg;
    std::cout.flush();

#ifdef _WIN32
    _getch();
#else
    termios oldt{}, newt{};
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    char c;
    read(STDIN_FILENO, &c, 1);
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
#endif

    cout << endl;
}

} // namespace io
