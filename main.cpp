#include "utils.hpp"

int main(int args, char* argv[]) {
    char* school_file_path = argv[1];
    char class_path[BUFFER_SIZE];
    sprintf(class_path, "%s/class", school_file_path);

    char send_buf[BUFFER_SIZE];

    char base_fifo_name[1024] = BASE_FIFO_PATH;

    int pipe_fd[2];
    std::vector<std::string> class_names;

    mkfifo(base_fifo_name, 0777);
    class_names = get_subdirs_or_files(school_file_path);

    for (int i=0 ; i < class_names.size() ; i++) {
        sprintf(send_buf, "$%d$%s$%s$", i+1, base_fifo_name, class_path);
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
            execl("./class.out", "./school/class", NULL);
        }

        //In Parent Process
        close(pipe_fd[0]);
        write(pipe_fd[1], send_buf, BUFFER_SIZE);
        close(pipe_fd[1]);

    }
}