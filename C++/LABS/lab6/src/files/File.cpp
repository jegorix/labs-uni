#include "../../include/files/File.h"

File::~File() {
    if (iFile.is_open()) iFile.close();
    if (oFile.is_open()) oFile.close();
    if (fFile.is_open()) fFile.close();
}
