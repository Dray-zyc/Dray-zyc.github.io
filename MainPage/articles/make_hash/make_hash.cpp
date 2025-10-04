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
        // ʹ�õ�ǰʱ����Ϊ���������
        srand(static_cast<unsigned int>(time(NULL)));
    }
    
    std::string generateTimeHash() {
        // ���ɸ������ֵĹ�ϣ
        std::string part1 = generateRandomString(6);
        std::string part2 = generateRandomString(8);
        std::string part3 = generateRandomString(2);
        std::string part4 = generateRandomString(4);
        
        // ��ϳ����ո�ʽ��6-8-2-4
        return part1 + "-" + part2 + "-" + part3 + "-" + part4;
    }
    
    // ִ���ļ�����
    bool copyAndRenameTemplate(const std::string& hash) {
        std::string filename = hash + ".html";
        
        // �����ļ�
        std::string copyCmd = "copy ..\\template.html .\\" + filename;
        std::cout << "ִ������: " << copyCmd << std::endl;
        int copyResult = system(copyCmd.c_str());
        
        if (copyResult != 0) {
            std::cerr << "�����ļ�ʧ��!" << std::endl;
            return false;
        }
        
        // �ƶ��ļ�����Ŀ¼
        std::string moveCmd = "move .\\" + filename + " ..\\";
        std::cout << "ִ������: " << moveCmd << std::endl;
        int moveResult = system(moveCmd.c_str());
        
        if (moveResult != 0) {
            std::cerr << "�ƶ��ļ�ʧ��!" << std::endl;
            return false;
        }
        
        std::cout << "�ļ������ɹ����! ���ɵ��ļ�: " << filename << std::endl;
        return true;
    }
};

int main() {
    TimeHashGenerator generator;
    
    // ���ɹ�ϣ
    std::string hash = generator.generateTimeHash();
    std::cout << "���ɵĹ�ϣ: " << hash << std::endl;
    
    // ���Ʋ�������template.html�ļ�
    bool success = generator.copyAndRenameTemplate(hash);
    
    if (success) {
        std::cout << "�������!" << std::endl;
    } else {
        std::cerr << "����ʧ��!" << std::endl;
        return 1;
    }
    
    return 0;
}
