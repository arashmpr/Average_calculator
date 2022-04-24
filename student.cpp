#include "utils.hpp"

int main(int argc, char* argv[]) {
    char read_buf[BUFFER_SIZE];
    char send_buf[BUFFER_SIZE];

    char student_name[BUFFER_SIZE];
    char parent_fifo_path[FIFO_SIZE];

    int write_fifo;

    read(0, read_buf, BUFFER_SIZE);
    sscanf(read_buf, "$%[^$]$%[^$]$", parent_fifo_path, student_name);
    

    write_fifo = open(parent_fifo_path, O_WRONLY);
    sprintf(send_buf, "%d", 3);
    write(write_fifo, send_buf, BUFFER_SIZE);

    close(write_fifo);
    exit(EXIT_SUCCESS);
}