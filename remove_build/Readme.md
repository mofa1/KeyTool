#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

// 递归函数，遍历目录并删除名为 "build" 的目录
void removeBuildDirectories(const fs::path& directory) {
    try {
        for (const auto& entry : fs::directory_iterator(directory)) {
            if (entry.is_directory()) {
                const auto& path = entry.path();
                std::cout << "Checking directory: " << path << std::endl;

                // 如果目录名为 "build"，则删除该目录
                if (path.filename() == "build") {
                    std::cout << "Removing directory: " << path << std::endl;
                    fs::remove_all(path);
                }
                else {
                    // 递归进入子目录
                    removeBuildDirectories(path);
                }
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Error accessing directory " << directory << ": " << e.what() << std::endl;
    }
}

int main() {
    fs::path currentDir = fs::current_path();
    std::cout << "Starting directory: " << currentDir << std::endl;

    // 调用递归函数，从当前目录开始
    removeBuildDirectories(currentDir);

    std::cout << "Finished checking directories." << std::endl;
    return 0;
}