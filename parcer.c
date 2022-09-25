#include "parcer.h"
#include <stdlib.h>
#include "struct_action.h"
#include <errno.h>



int start_parcer(struct_data* data, char* filename) {
    int ret = 0;
    ret = counter_f_v (data, filename);
    if (ret != 0) return ret;

    printf("f = %ld\n", data->count_of_f);

    //data->matrix_3d.matrix = (double*) malloc(sizeof(double) * (int)data->count_of_f);
    if (init_matrix_data(data) !=0) return 2;  // Выдение памяти под матрицы
    // Память на массивы выделяем по ходу парсинга
    parcer_main(data, filename);
    show_data_stuct(*data);

    //
    clean_data_struct(data);
    return ret;
}

int counter_f_v (struct_data* data, char* filename) {
    FILE* file;
    file = fopen(filename, "r");
    if (file == NULL) return 2;
    char str[129] = {0};
    while (1) {
        if (fgets(str, 128, file) != NULL) {
            if (str[0] == 'f') {
                data->count_of_f++;
            } else if (str[0] == 'v'){
                data->count_of_v++;
            }
        } else {
            break;
        }
    }

    fseek(file, 0, 0);

  data->polygons  = (polygon_t*) malloc(sizeof(polygon_t) * (int) data->count_of_f);  // Выделение памяти под массив полигонов
  unsigned long poly_counter = 0;
  while (1) {
        if (fgets(str, 128, file) != NULL) {
            if (str[0] == 'f') {
                int numbers_of_vertexes_in_facets = count_num_in_poly(str);
                data->polygons[poly_counter].numbers_of_vertexes_in_facets = numbers_of_vertexes_in_facets;
                data->polygons[poly_counter].vertexes = (int*)malloc(sizeof(int)*numbers_of_vertexes_in_facets);
                poly_counter++;
            }
        } else {
            break;
        }
    }
    return 0;
}

int parcer_main(struct_data* data, char* filename) {
    int ret = 0;
    
    FILE* file;
    file = fopen(filename, "r");
    if (file == NULL) return 2;
    char str[256] = {0};
    int counter_v = 0;
    long counter_f = 0;
    
    while (1) {
        if (fgets(str, 128, file) != NULL) {
            
            if (str[0] == 'f') {
                int counter_lenght_poly = 0;
                int i = 0;
                while (str[i] != '\n' && str[i] != '\0') {
                    if (str[i] >= '0' && str[i] <= '9') {
                        
                        char number[30] = {0};
                        int k = 0;
                        while (str[i] != '\n' && str[i] != '\0' 
                                && str[i] != ' ') {
                            number[k] = str[i];
                            k++; i++;
                            if (str[i] == '/') {
                                while (str[i] != '\n' && 
                                    str[i] != '\0' && 
                                    str[i] != ' ') {
                                    i++;
                                }
                            }
                            number[k] = '\0';
                            printf("%s %ld:%d\n", number,counter_f, counter_lenght_poly);
                            /// заполняем массив на итерациях
                            data->polygons[counter_f].vertexes[counter_lenght_poly] = (int)atof(number);
                            counter_lenght_poly++;
                        }
                        i--;
                    }
                    i++;
                }
            counter_f++;
            
            } else if (str[0] == 'v') {
                int i = 0;
                while (str[i] != '\n' && str[i] != '\0') {
                    if (str[i] >= '0' && str[i] <= '9') {
                        char number[30] = {0};
                        int k = 0;
                        while (str[i] != '\n' && str[i] != '\0' && str[i] != ' ') {
                            //printf("%c", str[i]);
                            number[k] = str[i];
                            k++; i++;
                        }
                        counter_v++; i--;
                        number[k] = '\0';
                        double num = atof(number);
                        if (errno == ERANGE) return 3;
                        else data->matrix_3d.matrix[(int)((counter_v-1)/3)][((counter_v-1)%3)] = num;
                    }
                    i++;
                }
            }
              
        } else {
            break;
        }
    }
    
    return ret;
}

int count_num_in_poly(char* str) {
    int i = 0, counter = 0;
    while (str[i] != '\n' && str[i] != '\0') {
        if (str[i] >= '0' && str[i] <= '9') {
            counter++;
            int k = 0;
            while (str[i] != '\n' && str[i] != '\0' 
                    && str[i] != ' ') {
                i++;
                if (str[i] == '/') {
                    while (str[i] != '\n' && 
                        str[i] != '\0' && 
                        str[i] != ' ') {
                        i++;
                    }
                }
            }
        i--;
        }
        i++;
    }
    return counter;
}