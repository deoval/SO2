#define MODO_CRIACAO S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH

// used by cp
void copy_file(char *source_file_name, char *dest_file_name);
int isnot_dir(char *path);