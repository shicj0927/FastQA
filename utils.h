#ifndef _UTILS_H_
#define _UTILS_H_

#include "include.h"

std::string getSystem() {
#if defined(_WIN32) || defined(_WIN64)
    return "Windows";
#elif defined(__APPLE__) && defined(__MACH__)
    return "MacOS";
#elif defined(__linux__)
    return "Linux";
#else
    return "Unknown";
#endif
}

std::string removeFirstLetter(std::string s) {
    std::string t = "";
    for (int i = 1; i < s.size(); i++) {
        t += s[i];
    }
    return t;
}

std::string subString(std::string s, int l, int r) {
    std::string t = "";
    for (int i = l; i < r; i++) {
        t += s[i];
    }
    return t;
}

std::string removeUnimportantChar(std::string s) {
    std::string t = "";
    for (int i = 0; i < s.size(); i++) {
        if (s[i] != ' ' && s[i] != '\n') {
            t += s[i];
        }
    }
    return t;
}

int stringToInt(std::string s) {
    int x = 0;
    for (int i = 0; i < s.size(); i++) {
        if ('0' <= s[i] && s[i] <= '9') {
            x = x * 10 + s[i] - '0';
        } else {
            return -1;
        }
    }
    return x;
}

std::string intToString(int x) {
    std::string s = "";
    while (x) {
        s = char(x % 10 + '0') + s;
        x /= 10;
    }
    if (s == "") {
        s = "0";
    }
    return s;
}

int getTimeStamp() { return time(0); }

std::string timeStampToString(int ti, std::string ord = "%Y-%m-%d-%H-%M-%S") {
    time_t t = static_cast<time_t>(ti);
    tm tm_time;
    //  localtime_r(&t,&tm_time);
#if defined(_WIN32) || defined(_WIN64)
    // Windows
    localtime_s(&tm_time, &t);
    // localtime_r(&t, &tm_time);
#else
    // Linux / macOS
    localtime_r(&t, &tm_time);
#endif
    char buf[64];
    strftime(buf, sizeof(buf), ord.c_str(), &tm_time);
    return std::string(buf);
}

std::string randString(int len) {
    static const char charset[] = "0123456789"
                                  "abcdefghijklmnopqrstuvwxyz";
    static thread_local std::mt19937 rng{std::random_device{}()};
    std::uniform_int_distribution<> dist(0, sizeof(charset) - 2);
    std::string s;
    s.reserve(len);
    for (int i = 0; i < len; ++i) {
        s.push_back(charset[dist(rng)]);
    }
    return s;
}

void clearScreen() {
    io::cout << _RESET << io::endl;
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

bool checkAns(std::string ipt, std::string ans) {
    return removeUnimportantChar(ipt) == removeUnimportantChar(ans);
}

#endif
