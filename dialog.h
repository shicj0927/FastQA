#pragma once

#include <string>
#include <vector>
#include <filesystem>
#include "thirdparty/tinyfiledialogs/tinyfiledialogs.h"

#ifdef _WIN32
#include <windows.h>
#endif

namespace dialog {

// ======================
// 内部编码转换
// ======================

#ifdef _WIN32

inline std::string acpToUtf8(const char *str) {
    if (!str)
        return {};

    // ACP -> UTF16
    int wideLen = MultiByteToWideChar(CP_ACP, 0, str, -1, nullptr, 0);
    if (wideLen <= 0)
        return {};

    std::wstring wide(wideLen, 0);
    MultiByteToWideChar(CP_ACP, 0, str, -1, wide.data(), wideLen);

    // UTF16 -> UTF8
    int utf8Len = WideCharToMultiByte(CP_UTF8, 0, wide.c_str(), -1, nullptr, 0, nullptr, nullptr);
    if (utf8Len <= 0)
        return {};

    std::string utf8(utf8Len - 1, 0);
    WideCharToMultiByte(CP_UTF8, 0, wide.c_str(), -1, utf8.data(), utf8Len, nullptr, nullptr);

    return utf8;
}

inline std::filesystem::path convertPath(const char *path) {
    return std::filesystem::u8path(acpToUtf8(path));
}

#else

inline std::filesystem::path convertPath(const char *path) {
    return std::filesystem::path(path ? path : "");
}

#endif

// ======================
// API
// ======================

inline std::filesystem::path openFile(const std::string &title = "Open File",
                                      const std::vector<const char *> &filters = {}) {
    const char *file = tinyfd_openFileDialog(
        title.c_str(), "", filters.empty() ? 0 : static_cast<int>(filters.size()),
        filters.empty() ? nullptr : filters.data(), nullptr, 0);

    return file ? convertPath(file) : std::filesystem::path{};
}

inline std::filesystem::path saveFile(const std::string &title = "Save File",
                                      const std::string &defaultName = "") {
    const char *file =
        tinyfd_saveFileDialog(title.c_str(), defaultName.c_str(), 0, nullptr, nullptr);

    return file ? convertPath(file) : std::filesystem::path{};
}

inline std::filesystem::path selectFolder(const std::string &title = "Select Folder") {
    const char *folder = tinyfd_selectFolderDialog(title.c_str(), "");

    return folder ? convertPath(folder) : std::filesystem::path{};
}

} // namespace dialog
