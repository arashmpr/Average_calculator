#include "utils.hpp"

std::vector<std::string> get_subdirs_or_files(char* path) {
    struct dirent *d;
    DIR *dir = opendir(path);

    if(dir == NULL) {
        perror("opendir");
        exit(1);
    }

    std::vector<std::string> files;
    while((d = readdir(dir)) != NULL) {
        std::string dir_name(d -> d_name);
        if(dir_name.compare("..") != 0 && dir_name.compare(".") != 0 && dir_name.compare(".DS_Store") != 0)
            files.push_back(dir_name);
    }

    closedir(dir);

    return files;
}