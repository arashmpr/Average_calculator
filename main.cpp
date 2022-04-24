#include "utils.hpp"

int main(int args, char* argv[]) {
    char* school_file_path = argv[1];

    char class_path[BUFFER_SIZE];
    sprintf(class_path, "%s/class", school_file_path);

    int read_fifo;
    char send_buf[BUFFER_SIZE];
    char read_buf[BUFFER_SIZE];

    char parent_fifo_path[FIFO_SIZE] = INITIAL_FIFO_PATH;

    int pipe_fd[2];
    std::vector<std::string> class_names;

    mkfifo(parent_fifo_path, 0777);
    class_names = get_subdirs_or_files(school_file_path);

    for (int i=0 ; i < class_names.size() ; i++) {
        sprintf(send_buf, "$%d$%s$%s$", i+1, parent_fifo_path, class_path);
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
            execv("./class.out", NULL);
        }

        //In Parent Process
        close(pipe_fd[0]);
        write(pipe_fd[1], send_buf, BUFFER_SIZE);
        close(pipe_fd[1]);

    }

    read_fifo = open(parent_fifo_path, O_RDWR);
    int id = class_names.size();

    char result[BUFFER_SIZE];
    char answer[BUFFER_SIZE];
    while(id != 0) {
        id--;
        read(read_fifo, read_buf, BUFFER_SIZE);
        sscanf(read_buf, "%s", answer);
        if(id != 0) {
            strcat(result, answer);
            strcat(result, "@");
        } else {
            strcat(result, answer);
        }
    }

    close(read_fifo);
    unlink(parent_fifo_path);

    int p[2];
    for (int field_id = 0; field_id < 5 ; field_id++) {
        memset(send_buf, 0, BUFFER_SIZE);
        sprintf(send_buf, "$%s$%d$", result, field_id);
        if(pipe(p) < 0) {
            perror("pipe");
            exit(1);
        }
        pid_t pid = fork();
        if(pid == 0) {
            //In Child Process
            close(p[1]);
            dup2(p[0], STDIN_FILENO);
            close(p[0]);
            execv("./read_and_calculate.out", NULL);
        }

        //In Parent Process
        close(p[0]);
        write(p[1], send_buf, BUFFER_SIZE);
        close(p[1]);
    }
    
    exit(EXIT_SUCCESS);
}