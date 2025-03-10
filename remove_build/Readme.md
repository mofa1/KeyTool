#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

// �ݹ麯��������Ŀ¼��ɾ����Ϊ "build" ��Ŀ¼
void removeBuildDirectories(const fs::path& directory) {
    try {
        for (const auto& entry : fs::directory_iterator(directory)) {
            if (entry.is_directory()) {
                const auto& path = entry.path();
                std::cout << "Checking directory: " << path << std::endl;

                // ���Ŀ¼��Ϊ "build"����ɾ����Ŀ¼
                if (path.filename() == "build") {
                    std::cout << "Removing directory: " << path << std::endl;
                    fs::remove_all(path);
                }
                else {
                    // �ݹ������Ŀ¼
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

    // ���õݹ麯�����ӵ�ǰĿ¼��ʼ
    removeBuildDirectories(currentDir);

    std::cout << "Finished checking directories." << std::endl;
    return 0;
}