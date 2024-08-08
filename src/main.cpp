#include <iostream>
#include "bundle.h"

int main() {
    std::cout << "JE ASSET BUNDLE TOOL" << std::endl;
    std::cout << "Type file names to bundle. Names (including paths) must not exceed 64 characters. If they do, they will be truncated and things will likely break. Write \"DONE\" when you have finished." << std::endl;

    std::vector<std::string> filesToBundle;
    std::string input;
    for (;;) {
        std::cin >> input;
        if (input.starts_with("DONE")) {
            break;
        } else {
            filesToBundle.push_back(input);
        }
    }

    if (filesToBundle.empty()) std::cout << "Can't form bundle with no files!" << std::endl;
    else createBundle(filesToBundle);

    return 0;
}