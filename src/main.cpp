#include <iostream>
#include "bundle.h"
#include "debundle.h"

int main() {
    std::cout << "JE ASSET BUNDLE TOOL" << std::endl;
    std::cout << "Bundle (b) or Debundle (d)?" << std::endl;
    std::string input;
    std::cin >> input;
    if (input[0] == 'b') {
        std::cout
                << "Type file names to bundle. \nNames (including paths) must not exceed 64 characters. \nIf they do, they will be truncated and things will likely break on debundle. \nWrite \"DONE\" when you have finished."
                << std::endl;

        std::vector<std::string> filesToBundle;
        for (;;) {
            input = "";
            std::cin >> input;
            if (input.starts_with("DONE")) {
                break;
            } else {
                filesToBundle.push_back(input);
            }
        }

        if (filesToBundle.empty()) std::cerr << "Can't form bundle with no files!" << std::endl;
        else createBundle(filesToBundle);
    } else {
        std::cout << "Bundle file name > ";
        std::string fname;
        std::cin >> fname;
        std::vector<bundled_file_info> fileInfos = getBfis(fname);
        std::cout << "File to extract? > ";
        input = "";
        std::cin >> input;
        bundled_file_info selected;
        for (auto const& bfi : fileInfos) {
            if (input.starts_with(bfi.path)) {
                selected = bfi;
                break;
            }
        }
        extractFile(selected, fname);
    }
    return 0;
}