#ifndef _UTILS_HPP_
#define _UTILS_HPP_

#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include <vector>

#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

std::vector<std::string> get_subdirs_or_files(char* path);

#endif