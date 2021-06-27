#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <filesystem>
#include <Windows.h>

#include <direct.h>

int green = 10;
int white = 15;
int red = 12;
int yellow = 14;

template<typename T>
std::string retVal(T val, HANDLE& hConsole, int change);

int main()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, white);
    SetConsoleTitle(L"CLEARY | MADE BY LegendsZ#1526 @ DISCORD");
    std::cout << "["<< retVal("CONSOLE", hConsole, yellow) << "]: BE AWARE THAT ADMIN PRIVILEGES ARE IDEAL!\n\n";

    std::vector<std::string> folders;
    std::ifstream file;

    while (true) {
        std::cout << "[" << retVal("CONSOLE", hConsole, yellow) << "]: LOOKING FOR DATA.TXT...";
        file.open("DATA.txt");
        if (file.is_open()) {
            retVal("OK!\n", hConsole, green);
            break;
        }
        else {
            std::cout << retVal("FAILED!", hConsole, red) << "!\n";
        }
        system("PAUSE");
    }

	std::string line;
	std::cout << "[" << retVal("CONSOLE", hConsole, yellow) << "]: RETRIEVING DATA...";
	while (std::getline(file, line)) {

		folders.push_back(line);
	}
    retVal("OK!\n\n", hConsole, green);
    file.close();
    
    int totalFiles = 0;
    int totalFolders = 0;
    for (int i = 0; i < folders.size(); i ++) {
        int nFiles_Deleted = 0;
        int nFiles = 0;

        DWORD attribs = GetFileAttributesA(folders.at(i).c_str());
        if (attribs == INVALID_FILE_ATTRIBUTES) {
            std::cout << "[" << retVal("CONSOLE", hConsole, yellow) << "]: INVALID FILE PATH - [" << retVal(folders.at(i).c_str(), hConsole, red) << "]!\n\n";
            continue;
        }

        for (const std::filesystem::path dirEntry : std::filesystem::recursive_directory_iterator(folders.at(i))) {
            if (std::filesystem::is_regular_file(dirEntry)) {
                nFiles++;
                try {
                    if (std::filesystem::remove(dirEntry)) {
                        nFiles_Deleted++;
                        totalFiles++;
                    }
                }
                catch (const std::filesystem::filesystem_error err) {
                    //std::cout << "filesystem error: " << err.what() << '\n';
                    continue;
                }
            }
        }
        for (const std::filesystem::path dirEntry : std::filesystem::directory_iterator(folders.at(i))) {
                try {
                    if (_rmdir(dirEntry.generic_string().c_str())) {
                        totalFolders++;
                    }
                }
                catch (const std::filesystem::filesystem_error err) {
                    continue;
                }
        }

        std::cout << "[" << retVal("CONSOLE", hConsole, yellow) << "]: DELETED [" << retVal(nFiles_Deleted, hConsole, green) <<"] OUT OF [" << retVal(nFiles, hConsole, green) << "] FILES IN DIRECTORY: [" << retVal(folders.at(i).c_str(),hConsole, green) << "]!\n" << std::endl;
    }
    std::cout << "[" << retVal("CONSOLE", hConsole, yellow) << "]: TOTAL AMOUNT OF FILES DELETED: [" << retVal(totalFiles, hConsole, green) << "]!\n";
    std::cout << "[" << retVal("CONSOLE", hConsole, yellow) << "]: TOTAL AMOUNT OF FOLDERS DELETED: [" << retVal(totalFolders, hConsole, green) << "]!\n\n";
    system("PAUSE");
}

template<typename T>
std::string retVal(T val , HANDLE& hConsole, int change) {
    SetConsoleTextAttribute(hConsole, change);
    std::cout << val;
    SetConsoleTextAttribute(hConsole, white);
    return "";
}