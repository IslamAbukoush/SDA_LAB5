#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 256

// Function to read content from a file
char* read(const char* filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file %s\n", filename);
        return NULL;
    }

    // Find the size of the file
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    // Allocate memory for the content
    char *content = (char*)malloc((file_size + 1) * sizeof(char));
    if (content == NULL) {
        fprintf(stderr, "Error allocating memory\n");
        fclose(file);
        return NULL;
    }

    // Read the content of the file
    size_t result = fread(content, sizeof(char), file_size, file);
    if (result != file_size) {
        fprintf(stderr, "Error reading file\n");
        fclose(file);
        free(content);
        return NULL;
    }
    content[file_size] = '\0'; // Null-terminate the content

    fclose(file);
    return content;
}

// Function to write content to a file
void write(const char* filename, const char* content) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Error opening file %s\n", filename);
        return;
    }

    // Write content to the file
    if (fprintf(file, "%s", content) < 0) {
        fprintf(stderr, "Error writing to file\n");
    }

    fclose(file);
}

// Function to append content to a file
void append(const char* filename, const char* content) {
    FILE *file = fopen(filename, "a"); // "a" mode for appending
    if (file == NULL) {
        fprintf(stderr, "Error opening file %s\n", filename);
        return;
    }

    // Write content to the end of the file
    if (fprintf(file, "%s", content) < 0) {
        fprintf(stderr, "Error appending to file\n");
    }

    fclose(file);
}

void clearStr(char* str, int len) {
    for(int i = 0; i < len; i++) {
        str[i] = '\0';
    }
}

char* split(char* str, const char* flag) {
    int flagLen = strlen(flag);
    char* result = (char*)malloc(BUFFER_SIZE * sizeof(char));
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }
    result[0] = '\0'; // Initialize result string as empty
    char* token = strtok(str, flag);
    while (token != NULL) {
        strcat(result, token);
        strcat(result, "\n"); // Add newline after each token
        token = strtok(NULL, flag);
    }
    return result;
}

int l2(char* str) {
    int idx = -1;
    int len = 0;
    while(str[++idx] != '\0') {
        if(str[idx] == '\n') {
            idx++;
            while(str[idx] != '\0' && str[idx] != '\n') {
                idx++;
                len++;
            }
            return len;
        }
    }
    return 0;
}

int ns(char* str) {
    int idx = -1;
    int len = 0;
    int lastn = 0;
    while(str[++idx] != '\0') {
        if(str[idx] == '\n') {
            len++;
            lastn = idx;
        }
    }
    if(lastn == idx-1) {
        return len;
    } else {
        return len+1;
    }
}

int main(int argc, char *argv[]) {
    char* mode = argv[1];
    char* fileName = "input.txt";
    char* out = "output.txt";
    if(!strcmp(mode, "w")) {
        write(fileName, argv[2]);
        printf(argv[2]);
    } else if(!strcmp(mode, "s")) {
        char* content = read(fileName);
        printf("%s", split(content, "..."));
    } else if(!strcmp(mode, "l2")) {
        char* content = read(fileName);
        printf("%i", l2(split(content, "...")));
    } else if(!strcmp(mode, "ns")) {
        char* content = read(fileName);
        printf("%i", ns(split(content, "...")));
    } else if(!strcmp(mode, "out")) {
        write(out, "");
        char* content = read(fileName);
        char* splitted = split(content, "...");
        int sNum = ns(splitted);
        int len2 = l2(splitted);
        char str1[20];
        char str2[20];
        sprintf(str1, "%d", sNum);
        sprintf(str2, "%d", len2);
        append(out, "Sentences:\n");
        append(out, splitted);
        append(out, "\n\nNumber of sentences: ");
        append(out, str1);
        append(out, "\nLength of second sentence: ");
        append(out, str2);
    }
}
