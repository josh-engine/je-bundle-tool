//
// Created by Ethan Lee on 8/18/24.
//

#include "debundle.h"
#include <fstream>
#include <iostream>

std::vector<unsigned char> readCharvec(const std::string& filename) {
    std::vector<unsigned char> charsVec;
    std::ifstream file(filename, std::ios::binary);
    while (!file.eof()) {
        char c{};
        file.get(c);
        charsVec.push_back(c);
    }
    charsVec.resize(charsVec.size()-1); // Take off the extra zero, TODO this is bad
    return charsVec;
}

std::vector<bundled_file_info> getBfis(std::string filename) {
    std::vector<unsigned char> chars = readCharvec(filename);
    file_header head = *reinterpret_cast<file_header*>(&chars[0]); // get head TODO bad bad shouldn't work
    if (head.magicNum != BLAHAJ_NUMBER) {
        throw "balls in your face";
    }
    std::cout << "File count: " << std::to_string(head.fileCount) << std::endl;
    std::vector<bundled_file_info> bfis{};
    bfis.reserve(head.fileCount);
    for (int i = 0; i < head.fileCount; ++i) {
        bfis.push_back(*reinterpret_cast<bundled_file_info*>(&chars[sizeof(file_header)+i*sizeof(bundled_file_info)]));
    }
    for (auto const& bfi : bfis) {
        std::cout << bfi.path << " (" << std::to_string(bfi.file_length) << " bytes)" << std::endl;
    }
    return bfis;
}

void extractFile(bundled_file_info bfi, const std::string& compressedFile) {
    std::vector<unsigned char> chars = readCharvec(compressedFile);
    char outfilebytes[bfi.file_length];
    memcpy(&outfilebytes[0], &chars[bfi.file_start_offset], bfi.file_length);
    std::ofstream finalFile("./extracted_" + std::string(bfi.path), std::ios::binary);
    finalFile.write(reinterpret_cast<const char *>(&outfilebytes[0]), bfi.file_length);
    finalFile.close();
}