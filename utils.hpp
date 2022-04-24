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
void create_fifo_name(char* fifo_name, char* parent_fifo_path, char* student_name, const char* field_name);
void put_grade_on_field(char* fifo_path, int grade);
std::vector<char*> split_fifo_names(char* result);

#endif