#include "utils.hpp"

int main(int argc, char* argv[]) {
    char read_buf[BUFFER_SIZE];

    int class_id;
    char fifo_path[BUFFER_SIZE];
    char student_path[BUFFER_SIZE];

    read(0, read_buf, BUFFER_SIZE);
    sscanf(read_buf, "$%d$%[^$]$%[^$]$", &class_id, fifo_path, student_path);
    
    sprintf(fifo_path, "%sclass%d", fifo_path, class_id);
    sprintf(student_path, "%s%d", student_path, class_id);

    std::vector<std::string> student_names = get_subdirs_or_files(student_path);
    for (int i=0 ; i<student_names.size() ; i++) {
        std::cout << student_names[i] << std::endl;
    }
}