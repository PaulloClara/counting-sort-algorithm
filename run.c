#include "stdio.h"
#include "stdlib.h"

#define TRUE 1
#define FALSE 0

int show_error(char *error_msg) {
  printf("\n\t\033[1;93m%s\033[0;0m\n", error_msg);
  return 1;
}

size_t end_array(char *array, size_t index) {
  return array[index] == '\0' || array[index] == '\n' ? TRUE : FALSE;
}

void load_array(char *input_array[], int *array, size_t array_size) {
  array[array_size-1] = atoi(input_array[array_size]);

  if (array_size == 1) return;
  load_array(input_array, array, --array_size);
}

size_t get_higher_value(int *array, size_t array_size, size_t higher_value) {
  if (array[--array_size] > higher_value) higher_value = array[array_size];

  if (array_size == 0) return higher_value;
  get_higher_value(array, array_size, higher_value);
}

void initialize_index_array(size_t *array, size_t array_size) {
  array[--array_size] = 0;

  if (array_size == 0) return;
  initialize_index_array(array, array_size);
}

void load_index_array(size_t *index_array, int *array, size_t array_size) {
  index_array[array[--array_size]]++;

  if (array_size == 0) return;
  load_index_array(index_array, array, array_size);
}

void map_index_array(size_t *index_array, size_t index_array_size, size_t i) {
  index_array[i] += index_array[i-1];

  if (i >= index_array_size) return;
  map_index_array(index_array, index_array_size, ++i);
};

void load_new_array(int *new_array, int *array, size_t *index_array, size_t size) {
  size--;
  new_array[--index_array[array[size]]] = array[size];

  if (size == 0) return;
  load_new_array(new_array, array, index_array, size);
}

void show_array(int *array, size_t array_size, size_t i) {
  printf("%d, ", array[i++]);

  if (i >= array_size) return;
  show_array(array, array_size, i);
}

int main(int argc, char *argv[]) {
  if (argc < 3) return show_error("Array not found!");

  size_t array_size = argc - 1;
  int array[array_size];

  load_array(argv, array, array_size);

  size_t index_array_size = get_higher_value(array, array_size, array[0]);
  size_t index_array[++index_array_size];

  initialize_index_array(index_array, index_array_size);
  load_index_array(index_array, array, array_size);
  map_index_array(index_array, index_array_size, 1);

  int new_array[array_size];

  load_new_array(new_array, array, index_array, array_size);

  printf("\n\n\t[");
  show_array(new_array, array_size, 0);
  printf("\b\b]\n\n\n");

  return 0;
}
