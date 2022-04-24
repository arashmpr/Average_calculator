#include "utils.hpp"

int main(int argc, char* argv[]) {
    char read_buf[BUFFER_SIZE];
    char send_buf[BUFFER_SIZE];
    int pipe_fd[2], read_fifo;

    char fifo_name_cstr[BUFFER_SIZE];
    int field_id;
    char field_name[BUFFER_SIZE];

    read(0, read_buf, BUFFER_SIZE);
    sscanf(read_buf, "$%[^$]$%d$", fifo_name_cstr, &field_id);

    std::vector<char*> fifo_names = split_fifo_names(fifo_name_cstr);
    
    if (field_id == PHYSICS) {
        strcpy(field_name, "Physics");
    } else if (field_id == ENGLISH) {
        strcpy(field_name, "English");
    } else if (field_id == MATH) {
        strcpy(field_name, "Math");
    } else if (field_id == LITERATURE) {
        strcpy(field_name, "Literature");
    } else if (field_id == CHEMISTRY) {
        strcpy(field_name, "Chemistry"); 
    }
    int grade;
    int grade_sum = 0;
    for (int i=0 ; i < fifo_names.size() ; i++) {
        char path[FIFO_SIZE];
        memset(path, 0, FIFO_SIZE);
        memset(read_buf, 0, BUFFER_SIZE);
        strcat(path, "pipes-school-");
        strcat(path, fifo_names[i]);
        strcat(path, "-");
        strcat(path, field_name);
        
        read_fifo = open(path, O_RDWR);
        read(read_fifo, read_buf, BUFFER_SIZE);
        sscanf(read_buf, "$%d$", &grade);
        grade_sum += grade;
        close(read_fifo);
        unlink(path);
    }
    int average_grade = grade_sum / fifo_names.size();
    std::cout << field_name << " average is: " << average_grade << std::endl;
    exit(EXIT_SUCCESS);
}