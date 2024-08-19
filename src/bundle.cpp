//
// Created by Ethan Lee on 8/7/24.
//

#include "bundle.h"
#include <fstream>
#include <iostream>

void createBundle(std::vector<std::string> names) {
    std::cout << "Starting bundle creation." << std::endl;
    std::vector<std::vector<char>> fileByteArrays{};
    for (const auto& name : names) {
        std::ifstream file;
        file.open(name, std::ios::binary);
        fileByteArrays.emplace_back();
        unsigned int currentFBA = fileByteArrays.size()-1;
        if (!file.eof() && !file.fail()) {
            file.seekg(0, std::ios_base::end);
            std::streampos fileSize = file.tellg();
            fileByteArrays[currentFBA].resize(fileSize);

            file.seekg(0, std::ios_base::beg);
            file.read(&fileByteArrays[currentFBA][0], fileSize);
        } else if (file.fail()) {
            std::cout << "Failed to open \"" << name << "\"! Are you sure it exists? Proceeding bundle compilation, leaving blank." << std::endl;
        }
    }
    std::cout << "Names parsed and files loaded, Building file infos..." << std::endl;
    std::vector<bundled_file_info> bundledFileInfos;
    unsigned int file_len_counter = 0;
    // TODO just do it in one loop you don't need to debug this later
    for (int i = 0; i < names.size(); i++) {
        bundledFileInfos.emplace_back();
        memcpy(&bundledFileInfos[i].path, names[i].c_str(), names[i].length() > 64 ? 64 : names[i].length());
        bundledFileInfos[i].file_start_offset = sizeof(file_header) + names.size()*sizeof(bundled_file_info) + file_len_counter;
        bundledFileInfos[i].file_length = fileByteArrays[i].capacity();
        file_len_counter += fileByteArrays[i].capacity();
    }
    std::cout << "File infos built, creating final array..." << std::endl;
    unsigned char finalArray[sizeof(file_header) + names.size()*sizeof(bundled_file_info) + file_len_counter];
    file_header finalHeader;
    finalHeader.fileCount = bundledFileInfos.size();
    memcpy(finalArray, &finalHeader, sizeof(file_header)); // Copy header
    for (int i = 0; i < bundledFileInfos.size(); i++) {
        memcpy(&finalArray[sizeof(file_header) + i*sizeof(bundled_file_info)], &bundledFileInfos[i], sizeof(bundled_file_info));
    }
    int i = 0;
    // Bad, but i don't care.
    for (const auto& fba : fileByteArrays) {
        for (const auto& byte : fba) {
            finalArray[sizeof(file_header) + bundledFileInfos.size()*sizeof(bundled_file_info) + i++] = byte;
        }
    }
    std::cout << "Bundle successfully built." << std::endl;

    std::cout << "Bundle file name? (.jbd will be appended) > ";
    std::string finalFilename;
    std::cin >> finalFilename;

    std::ofstream finalFile(finalFilename + ".jbd", std::ios::binary);
    finalFile.write(reinterpret_cast<const char *>(&finalArray[0]), sizeof(file_header) + names.size() * sizeof(bundled_file_info) + file_len_counter);
    finalFile.close();
}