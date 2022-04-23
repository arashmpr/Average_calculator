#ifndef _UTILS_HPP_
#define _UTILS_HPP_

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <vector>

#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

#define BUFFER_SIZE 512
#define BASE_FIFO_PATH "./pipes/school/"

std::vector<std::string> get_subdirs_or_files(char* path);

#endif