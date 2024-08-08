//
// Created by Ethan Lee on 8/7/24.
//

#ifndef JEASSETBUNDLE_BUNDLE_H
#define JEASSETBUNDLE_BUNDLE_H

#include <string>
#include <vector>

struct bundled_file_info {
    char path[64];
    u_int64_t file_start_offset;
    u_int64_t file_length;
} typedef bundled_file_info;

struct file_header {
    unsigned int magicNum = 0x0B1A11A7;
    unsigned int fileCount = 0;
} typedef file_header;

void createBundle(std::vector<std::string> names);

#endif //JEASSETBUNDLE_BUNDLE_H
