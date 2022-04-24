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
#include <cstring>
#include <fstream>
#include <cstdlib>

#define BUFFER_SIZE 512
#define FIFO_SIZE 64
#define SIZE 128
#define INITIAL_FIFO_PATH "pipes-school";

#define PHYSICS     0
#define ENGLISH     1
#define MATH        2
#define LITERATURE  3  
#define CHEMISTRY   4

std::vector<std::string> get_subdirs_or_files(char* path);

#endif