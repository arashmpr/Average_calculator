#include "utils.hpp"

int main(int argc, char* argv[]) {
    char read_buf[BUFFER_SIZE];
    char send_buf[BUFFER_SIZE];
    int pipe_fd[2], read_fifo, write_fifo;

    int class_id;
    char parent_fifo_path[FIFO_SIZE];
    char child_fifo_path[FIFO_SIZE];

    char class_dir_path[BUFFER_SIZE];

    read(0, read_buf, BUFFER_SIZE);
    sscanf(read_buf, "$%d$%[^$]$%[^$]$", &class_id, parent_fifo_path, class_dir_path);
    
    sprintf(child_fifo_path, "%s-class%d", parent_fifo_path, class_id);
    sprintf(class_dir_path, "%s%d", class_dir_path, class_id);

    std::vector<std::string> student_names = get_subdirs_or_files(class_dir_path);
    mkfifo(child_fifo_path, 0777);

    for (int i=0 ; i < student_names.size() ; i++) {
        sprintf(send_buf, "$%s$%s$", child_fifo_path, student_names[i].c_str());
        if(pipe(pipe_fd) < 0) {
            std::cout << "Could not create pipe!" << std::endl;
            exit(1);
        }

        pid_t pid = fork();
        if(pid == 0) {
            //In Child Process
            close(pipe_fd[1]);
            dup2(pipe_fd[0], STDIN_FILENO);
            close(pipe_fd[0]);
            execv("./student.out", NULL);
        }

        //In Parent Process
        close(pipe_fd[0]);
        write(pipe_fd[1], send_buf, BUFFER_SIZE);
        close(pipe_fd[1]);
    }
    

    // Parent Process
    read_fifo = open(child_fifo_path, O_RDWR);
    write_fifo = open(parent_fifo_path, O_WRONLY);

    int id = student_names.size();
    char result[BUFFER_SIZE];
    char student_ans[BUFFER_SIZE];

    while(id != 0) {
        id--;
        read(read_fifo, read_buf, BUFFER_SIZE);
        sscanf(read_buf, "%s", student_ans);
        if (id != 0) {
            strcat(result, student_ans);
            strcat(result, "@");
        } else {
            strcat(result, student_ans);
        }
    }
    sprintf(send_buf, "%s", result);
    write(write_fifo, send_buf, BUFFER_SIZE);

    close(read_fifo);
    close(write_fifo);
    unlink(child_fifo_path);
    exit(EXIT_SUCCESS);
}