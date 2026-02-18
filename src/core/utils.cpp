#include <core/utils.h>
#include <cstdio>
#include <core/debug.h>

bool Lux::Utils::read_file(const char* path, char buffer_str[1024]){
    FILE* file = fopen(path, "rb");

    LUX_VERIFY(file, "failed to open file");

    fseek(file, 0, SEEK_END);

    size_t file_size = ftell(file);

    fseek(file, 0, SEEK_SET);

    buffer_str[file_size + 1] = '\0';

    fread(buffer_str, sizeof(char), file_size, file);

    return true;
}