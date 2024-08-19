//
// Created by Ethan Lee on 8/18/24.
//

#ifndef JEASSETBUNDLE_DEBUNDLE_H
#define JEASSETBUNDLE_DEBUNDLE_H

#include "bundle.h"

// We are loading this file twice inevitably, because I do not want to pass around a huge ass vec<char>
// Evil to avoid greater crimes
std::vector<bundled_file_info> getBfis(std::string filename);
void extractFile(bundled_file_info bfi, const std::string& compressedFile);

#endif //JEASSETBUNDLE_DEBUNDLE_H
