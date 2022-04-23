#include "utils.hpp"

int main(int argc, char* argv[]) {
    char read_buf[BUFFER_SIZE];

    char fifo_path[BUFFER_SIZE];
    char new_fifo_path[BUFFER_SIZE];
    int class_id;

    read(0, read_buf, BUFFER_SIZE);
    sscanf(read_buf, "$%d$%[^$]$", &class_id, fifo_path);
    
    sprintf(new_fifo_path, "%sclass%d", fifo_path, class_id);

    std::cout<<new_fifo_path<<std::endl;
}