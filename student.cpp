#include "utils.hpp"

int main(int argc, char* argv[]) {
    char read_buf[BUFFER_SIZE];
    char send_buf[BUFFER_SIZE];

    char student_name[BUFFER_SIZE];
    char parent_fifo_path[FIFO_SIZE];
    char child_fifo_path[FIFO_SIZE];
    char field_fifo_path[FIFO_SIZE];

    int write_fifo;

    std::ifstream csv_out;
    char pipe_name[SIZE];
    char school_name[SIZE];
    char class_name[BUFFER_SIZE];
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
        strcpy(field_fifo_path,create_fifo_name(parent_fifo_path, student_name, field.c_str()));
        grade = atoi(grade_str.c_str());
        put_grade_on_field(field_fifo_path, grade);
    }

    char final_ans[BUFFER_SIZE];
    memset(final_ans, 0 , BUFFER_SIZE);
    strcat(final_ans, class_name);
    strcat(final_ans, "-");
    strcat(final_ans, student_name);

    write_fifo = open(parent_fifo_path, O_WRONLY);
    sprintf(send_buf, "%s", final_ans);
    write(write_fifo, send_buf, BUFFER_SIZE);

    close(write_fifo);
    exit(EXIT_SUCCESS);
}