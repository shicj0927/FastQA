#ifndef _COLOR_H_
#define _COLOR_H_

#include "include.h"

// #ifdef _WIN32
// 	#include <windows.h>
// 	void enableANSI(){
// 	    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
// 	    if (hOut == INVALID_HANDLE_VALUE) return;

// 	    DWORD dwMode = 0;
// 	    if (!GetConsoleMode(hOut, &dwMode)) return;

// 	    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
// 	    SetConsoleMode(hOut, dwMode);
// 	}
// #else
// 	void enableANSI(){}
// #endif

// void enableANSI(){
// 	#ifdef _WIN32
// 		#define NOMINMAX
// 		#define WIN32_LEAN_AND_MEAN
// 		#include <windows.h>

// 		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
// 		if (hOut == INVALID_HANDLE_VALUE) return;

// 		DWORD dwMode = 0;
// 		if (!GetConsoleMode(hOut, &dwMode)) return;

// 		dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
// 		SetConsoleMode(hOut, dwMode);
// 	#endif
// }

void initColor() {
#ifdef _WIN32
    // #define NO_COLOR
    // enableANSI();
#endif
}

#ifndef NO_COLOR
std::string BLACK(std::string x) { return "\e[30m" + x + "\e[0m"; }
std::string RED(std::string x) { return "\e[31m" + x + "\e[0m"; }
std::string GREEN(std::string x) { return "\e[32m" + x + "\e[0m"; }
std::string YELLOW(std::string x) { return "\e[33m" + x + "\e[0m"; }
std::string BLUE(std::string x) { return "\e[34m" + x + "\e[0m"; }
std::string MAGENTA(std::string x) { return "\e[35m" + x + "\e[0m"; }
std::string CYAN(std::string x) { return "\e[36m" + x + "\e[0m"; }
std::string WHITE(std::string x) { return "\e[37m" + x + "\e[0m"; }
std::string DEFAULT(std::string x) { return "\e[0m" + x + "\e[0m"; }

const std::string _BLACK = "\e[30m";
const std::string _RED = "\e[31m";
const std::string _GREEN = "\e[32m";
const std::string _YELLOW = "\e[33m";
const std::string _BLUE = "\e[34m";
const std::string _MAGENTA = "\e[35m";
const std::string _CYAN = "\e[36m";
const std::string _WHITE = "\e[37m";
const std::string _RESET = "\e[0m";
#else
std::string BLACK(std::string x) { return x; }
std::string RED(std::string x) { return x; }
std::string GREEN(std::string x) { return x; }
std::string YELLOW(std::string x) { return x; }
std::string BLUE(std::string x) { return x; }
std::string MAGENTA(std::string x) { return x; }
std::string CYAN(std::string x) { return x; }
std::string WHITE(std::string x) { return x; }
std::string DEFAULT(std::string x) { return x; }

const std::string _BLACK = "";
const std::string _RED = "";
const std::string _GREEN = "";
const std::string _YELLOW = "";
const std::string _BLUE = "";
const std::string _MAGENTA = "";
const std::string _CYAN = "";
const std::string _WHITE = "";
const std::string _RESET = "";
#endif

void debugTestColor() {
    io::cout << BLACK("BLACK") << io::endl;
    io::cout << RED("RED") << io::endl;
    io::cout << GREEN("GREEN") << io::endl;
    io::cout << YELLOW("YELLOW") << io::endl;
    io::cout << BLUE("BLUE") << io::endl;
    io::cout << MAGENTA("MAGENTA") << io::endl;
    io::cout << CYAN("CYAN") << io::endl;
    io::cout << WHITE("WHITE") << io::endl;
    io::cout << DEFAULT("DEFAULT") << io::endl;
}

#endif