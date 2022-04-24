#include "utils.hpp"

int main(int argc, char* argv[]) {
    char read_buf[BUFFER_SIZE];
    char send_buf[BUFFER_SIZE];

    char student_name[BUFFER_SIZE];
    char parent_fifo_path[FIFO_SIZE];

    int write_fifo;

    std::ifstream csv_out;
    char pipe_name[SIZE];
    char school_name[SIZE];
    char class_name[SIZE];
    char student_path[SIZE];
    std::string field;
    std::string grade_str;
    int grade;

    read(0, read_buf, BUFFER_SIZE);
    sscanf(read_buf, "$%[^$]$%[^$]$", parent_fifo_path, student_name);
    sscanf(parent_fifo_path, "%[^-]-%[^-]-%[^-]", pipe_name, school_name, class_name);
    strcat(student_path, "./school/");
    strcat(student_path, class_name);
    strcat(student_path, "/");
    strcat(student_path, student_name);
    
    csv_out.open(student_path);
    if (!csv_out.is_open()) {
        perror("open");
        exit(1);
    }
    while(std::getline(csv_out, field, ',')) {
        std::getline(csv_out, grade_str, '\n');
        if(strcmp(field.c_str(), "Physics") == 0) {
            grade = atoi(grade_str.c_str());
        }
    }
    write_fifo = open(parent_fifo_path, O_WRONLY);
    sprintf(send_buf, "%d", grade);
    write(write_fifo, send_buf, BUFFER_SIZE);

    close(write_fifo);
    exit(EXIT_SUCCESS);
}