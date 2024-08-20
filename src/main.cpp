#include <iostream>
#include <filesystem>
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
            } else if (input.starts_with("ALL_IN")) {
                input = "";
                std::cin >> input;
                std::string dir = std::filesystem::current_path().generic_string() + "/" + input;
                for (const auto & entry : std::filesystem::directory_iterator(dir)) {
                    std::string fnameRelative = "./" + input + "/" + entry.path().filename().generic_string();
                    if (fnameRelative.length() > 63) {
                        std::cerr << "Couldn't include " << fnameRelative << ", path too long." << std::endl;
                        continue;
                    }
                    filesToBundle.push_back(fnameRelative);
                    std::cout << "(" << fnameRelative << ")" << std::endl;
                }
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