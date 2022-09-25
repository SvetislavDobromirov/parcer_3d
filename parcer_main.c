#include "parcer.h"

int main() {
    struct_data data_file = {}; 
    char* filename = "./cube.obj";
    start_parcer(&data_file, filename);
    
    return 0;
}