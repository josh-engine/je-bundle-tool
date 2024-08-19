//
// Created by Ethan Lee on 8/7/24.
//

#ifndef JEASSETBUNDLE_BUNDLE_H
#define JEASSETBUNDLE_BUNDLE_H

#define BLAHAJ_NUMBER 0x0B1A11A7

#include <string>
#include <vector>

struct bundled_file_info {
    char path[64];
    u_int64_t file_start_offset;
    u_int64_t file_length;
} typedef bundled_file_info;

struct file_header {
    unsigned int magicNum = BLAHAJ_NUMBER; // Blahaj magic number, static
    unsigned int fileCount = 0;
} typedef file_header;

void createBundle(std::vector<std::string> names);

#endif //JEASSETBUNDLE_BUNDLE_H
