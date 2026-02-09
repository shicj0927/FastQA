# Compiler and flags
CXX = g++
WINCXX = x86_64-w64-mingw32-g++
CXXFLAGS = -Wall -std=gnu++17
WINCXXFLAGS = -static -static-libgcc -static-libstdc++ -Wall -std=gnu++17 -lole32 -lcomdlg32 -luser32 -lshell32


# Target executable
TARGET = FastQA
WINTARGET = FastQA.exe

# Source files
SRC = main.cpp thirdparty/tinyfiledialogs/tinyfiledialogs.c

all:
	$(CXX) $(SRC) $(CXXFLAGS) -o $(TARGET)
	./$(TARGET)

run:
	$(CXX) $(SRC) $(CXXFLAGS) -o $(TARGET)
	./$(TARGET)

win:
	$(WINCXX) $(SRC) $(WINCXXFLAGS) -o $(WINTARGET)

cnt:
	cloc . --exclude-list-file=.clocignore --include-lang=C++,"C/C++ Header","make"

clean:
	rm -f $(TARGET)

.PHONY: all clean
