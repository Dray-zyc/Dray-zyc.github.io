#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <iomanip>
#include <cstdio>

class TimeHashGenerator {
private:
    const std::string charset = "0123456789abcdefghijklmnopqrstuvwxyz";
    
    std::string generateRandomString(int length) {
        std::string result;
        for (int i = 0; i < length; ++i) {
            int index = rand() % charset.size();
            result += charset[index];
        }
        return result;
    }

public:
    TimeHashGenerator() {
        // 使用当前时间作为随机数种子
        srand(static_cast<unsigned int>(time(NULL)));
    }
    
    std::string generateTimeHash() {
        // 生成各个部分的哈希
        std::string part1 = generateRandomString(6);
        std::string part2 = generateRandomString(8);
        std::string part3 = generateRandomString(2);
        std::string part4 = generateRandomString(4);
        
        // 组合成最终格式：6-8-2-4
        return part1 + "-" + part2 + "-" + part3 + "-" + part4;
    }
    
    // 执行文件操作
    bool copyAndRenameTemplate(const std::string& hash) {
        std::string filename = hash + ".html";
        
        // 复制文件
        std::string copyCmd = "copy ..\\template.html .\\" + filename;
        std::cout << "执行命令: " << copyCmd << std::endl;
        int copyResult = system(copyCmd.c_str());
        
        if (copyResult != 0) {
            std::cerr << "复制文件失败!" << std::endl;
            return false;
        }
        
        // 移动文件到父目录
        std::string moveCmd = "move .\\" + filename + " ..\\";
        std::cout << "执行命令: " << moveCmd << std::endl;
        int moveResult = system(moveCmd.c_str());
        
        if (moveResult != 0) {
            std::cerr << "移动文件失败!" << std::endl;
            return false;
        }
        
        std::cout << "文件操作成功完成! 生成的文件: " << filename << std::endl;
        return true;
    }
};

int main() {
    TimeHashGenerator generator;
    
    // 生成哈希
    std::string hash = generator.generateTimeHash();
    std::cout << "生成的哈希: " << hash << std::endl;
    
    // 复制并重命名template.html文件
    bool success = generator.copyAndRenameTemplate(hash);
    
    if (success) {
        std::cout << "操作完成!" << std::endl;
    } else {
        std::cerr << "操作失败!" << std::endl;
        return 1;
    }
    
    return 0;
}
