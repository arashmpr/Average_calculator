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

char* create_fifo_name(char* parent_fifo_path, char* student_name, const char* field_name) {
    char fifo_name[BUFFER_SIZE];
    strcpy(fifo_name, parent_fifo_path);
    strcat(fifo_name, "-");
    strcat(fifo_name, student_name);
    strcat(fifo_name, "-");
    strcat(fifo_name, field_name);

    mkfifo(fifo_name, 0777);
    return fifo_name;
}

void put_grade_on_field(char* fifo_path, int grade) {
    int write_fifo;
    char send_buf[BUFFER_SIZE];

    write_fifo = open(fifo_path, O_WRONLY);

    sprintf(send_buf, "%d", grade);
    write(write_fifo, send_buf, BUFFER_SIZE);

    close(write_fifo);
    exit(EXIT_SUCCESS);
}