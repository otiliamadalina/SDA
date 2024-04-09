#include "utils.h"


int generate_random_number() {
    return (rand() % 10);
}

char generate_random_character() {
    char letters[] = "abcdefghijklmnopqrstuvwxyz";
    int letters_size = (int) strlen(letters);
    int rand_pos = rand() % letters_size;
    return letters[rand_pos];
}

char* generate_random_string() {
    int random_length = generate_random_number();
    char* random_string = (char*) malloc(sizeof(char) * random_length);
    for(int iter = 0; iter < random_length - 1; ++iter) {
        random_string[iter] = generate_random_character();
    }
    random_string[random_length - 1] = '\0';

    return random_string;
}