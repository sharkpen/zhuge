/*
 File Name: file_parser.h
 Author: lijinqi
 Email: lijinqi@croot.com
 Created: 2023-09-07
 Last Modified: 2023-09-07
*/
#include <filesystem>
#include <string>
#include <iostream>

void ListFilesInDirectory(const std::string& path) {
    try {
        for (const auto& entry : std::filesystem::directory_iterator(path)) {
            if (entry.is_directory()) {
                // 如果是子目录，递归遍历
                ListFilesInDirectory(entry.path().string());
            } else if (entry.is_regular_file()) {
                // 如果是文件，打印文件名
                //std::cout << entry.path().filename() << std::endl;
                //std::cout << entry.path().string() << std::endl;
            }
        }
    } catch (const std::exception& ex) {
        std::cerr << "遍历文件夹时出现错误：" << ex.what() << std::endl;
    }
}

int main() {
    std::string directoryPath = "/home/lijinqi/workspace/zhuge/proto"; // 替换为您要遍历的目录路径
    ListFilesInDirectory(directoryPath);
    return 0;

}



