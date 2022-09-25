
#include "struct_action.h"

int init_matrix_data(struct_data *data_struct) {
    // требуется доработка согласно расширению структуры
    int ret = 0;
    // выделяем память под массив точек
    // Сначала под количество рядов
    data_struct->matrix_3d.rows = data_struct->count_of_v; // Количество рядов в струкуре соотвествует количеству строчек   
    data_struct->matrix_3d.cols = 3;
    data_struct->matrix_3d.matrix = (double**) malloc(sizeof(double*) * data_struct->count_of_v);
    if (data_struct->matrix_3d.matrix == NULL) return 3;
    for (int i = 0; i < data_struct->matrix_3d.rows; i++) {
        data_struct->matrix_3d.matrix[i] = (double*) malloc(sizeof(double) * 3);
        if (data_struct->matrix_3d.matrix[i] == NULL) return 4;
    }        
    return ret;
}

int show_data_stuct(struct_data data) {
    int ret = 0;
    printf("Кол-во точек: %ld\n", data.count_of_v);
    printf("Кол-во полигонов: %ld\n", data.count_of_f);

    for (unsigned long i = 0; i < data.matrix_3d.rows; i++) {
        printf("%ld: ", i);
        for (int k = 0; k < 3; k++) {
            printf("%f ", data.matrix_3d.matrix[i][k]);
        }
        printf("\n");
    }
    fflush(stdout);  
  
    for (unsigned long i = 0; i < data.count_of_f; i++) {
        printf("%ld: ", i);
        for (int k = 0; k < data.polygons[i].numbers_of_vertexes_in_facets; k++) {
            printf("%d ", data.polygons[i].vertexes[k]);
        }
    printf("\n");
    }
    return ret;
}


int clean_data_struct(struct_data *data) {
  int ret = 0;
    for (unsigned long i = 0; i < data->matrix_3d.rows; i++)
        free(data->matrix_3d.matrix[i]);
    free(data->matrix_3d.matrix);
    for (unsigned long i = 0; i < data->count_of_f; i++)
           free(data->polygons[i].vertexes);
    free((data->polygons));
    return ret;
}


////asdas///