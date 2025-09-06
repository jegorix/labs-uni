#ifndef FILE_UTILS_H
#define FILE_UTILS_H

int choose_file_operation(char** file_name, int* number_count);
void open_existing_file(char** file_name, int* number_count);
void write_to_file_by_hand(char* file_name, int number_count);
void write_to_file_by_random(char* file_name, int number_count);
void file_data_output(char* file_name, int number_count);
void fill_file_menu(char** file_name, int* number_count);
void find_max_length_sequence(char* file_name, int number_count);
void zero_even_positions(char* file_name, int number_count);
void hybrid_sort(char* file_name, int number_count);

#endif