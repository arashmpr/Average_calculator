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

void create_fifo_name(char* fifo_name, char* parent_fifo_path, char* student_name, const char* field_name) {
    strcpy(fifo_name, parent_fifo_path);
    strcat(fifo_name, "-");
    strcat(fifo_name, student_name);
    strcat(fifo_name, "-");
    strcat(fifo_name, field_name);

    mkfifo(fifo_name, 0666);
}

void put_grade_on_field(char* fifo_path, int grade) {
    int write_fifo;
    char send_buf[BUFFER_SIZE];
    memset(send_buf, 0, BUFFER_SIZE);
    write_fifo = open(fifo_path, O_WRONLY | O_NONBLOCK);
    sprintf(send_buf, "$%d$", grade);
    write(write_fifo, send_buf, BUFFER_SIZE);

    close(write_fifo);
}

std::vector<char*> split_fifo_names(char* result) {
    char* fifo_name;
    std::vector<char*> fifo_names;
    fifo_name = strtok(result, "@");
    while(fifo_name != NULL) {
        fifo_names.push_back(fifo_name);
        fifo_name = strtok(NULL, "@");
    }

    return fifo_names;
}