#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <string>

#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

int get_size_of_classes(char* path_file);
std::string* get_class_names(char* path_file);

int get_size_of_students(char* path_file);
std::string* get_students_names(char* path_file);



int main(int args, char* argv[]) {
    char* path_file = argv[1];
    int pids[100];
    int i = 0;

    int class_num;
    std::string* class_names;

    class_num = get_size_of_classes(path_file);
    class_names = get_class_names(path_file);

    for (i ; i < class_num ; i++) {
        pids[i] = fork();
        if (pids[i] == 0) {
            break;
        }
    }

    std::string class_path_file = std::string(path_file) + "/" + class_names[i+3];
    int sss = get_size_of_students(class_path_file);
    std::cout << "student: "<<sss<<std::endl;

    
    

    for (int j = 0 ; j < class_num+1 ; j++) {
        wait(NULL);
    }
}

int get_size_of_classes(char* path_file) {
    DIR *dp;
    struct dirent *ep;     
    dp = opendir (path_file);

    int size = 0;

    if (dp != NULL)
    {
        while (ep = readdir (dp))
            size++;
        (void) closedir (dp);
    } 
    else
        perror ("Couldn't open the directory");
    
    return size - 3;
}

std::string* get_class_names(char* path_file) {
    DIR *dp;
    struct dirent *ep;     
    dp = opendir (path_file);
    std::string class_name[1000];

    int i = 0;

    if (dp != NULL)
    {
        while (ep = readdir (dp)) {
            class_name[i] = ep -> d_name;
            i++;
        }
        (void) closedir (dp);
    } 
    else
        perror ("Couldn't open the directory");
    
    return class_name;
}

int get_size_of_students(char* path_file) {
    DIR *dp;
    struct dirent *ep;     
    dp = opendir (path_file);

    int size = 0;

    if (dp != NULL)
    {
        while (ep = readdir (dp)) 
            size++;
        
        (void) closedir (dp);
    } 
    else
        perror ("Couldn't open the directory");
    
    return size;
}