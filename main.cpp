#include "utils.hpp"

int main(int args, char* argv[]) {
    char* path_file = argv[1];
    std::vector<std::string> class_names;

    class_names = get_subdirs_or_files(path_file);
    for (int i=0 ; i < class_names.size() ; i++) {
        std::cout<< class_names[i] << std::endl;
    }
}