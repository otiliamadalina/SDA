#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct book {
    char *name;
    char *author;
    int pages;
    int price;
} Book;

typedef struct library {
    Book *books;
    unsigned int nr_of_books;
} Library;

int get_number_of_lines_from_file(FILE *file) {
    const int buffer_size = 500;
    char buffer[500];
    int lines = 0;
    while (fgets(buffer, buffer_size, file)) {
        lines++;
    }
    rewind(file);
    return lines ? lines : 0;
}

void read_book_from_file(FILE *file, Book *target_book) {
    if ((target_book->name != NULL) || (target_book->author != NULL)) {
        free(target_book->name);
        free(target_book->author);
    }
    target_book->name = malloc(sizeof(char) * 100);
    target_book->author = malloc(sizeof(char) * 100);
    if (feof(file)) {
        printf("This is end of file error!");
        return;
    }
    fscanf(file,
           "%s %s %d %d",
           target_book->name,
           target_book->author,
           &target_book->pages,
           &target_book->price);
}


Library *read_books_from_file_by_path(const char *file_path) {
    if (file_path == NULL) {
        printf("File path should be setted!");
        return NULL;
    }
    Library *result_library = NULL;
    FILE *file = fopen(file_path, "r+");
    if(file == NULL) {
        printf("Cannot open the file");
        return NULL;
    }
    size_t number_of_books = get_number_of_lines_from_file(file);
    result_library = malloc(sizeof(Library));
    result_library->books = calloc(number_of_books, sizeof(Book));
    result_library->nr_of_books = number_of_books;
    for (int i = 0; i < number_of_books; i++) {
        read_book_from_file(file, result_library->books + i);
    }
    fclose(file);
    return result_library;
}

void print_book_data(Book *book) {
    printf("Nume: %s\nAutor: %s\nPagini: %d\nPret: %d\n\n",
           book->name,
           book->author,
           book->pages,
           book->price);
}

void print_library(Library *library) {

    if (library == NULL) {
        printf("Library is NULL!\n");
        return;
    }

    printf("\nBooks are:\n");
    for (int i = 0; i < library->nr_of_books; i++) {
        print_book_data((library->books) + i);
    }
}

void delete_books(Library * library) {
    for (int i = 0; i < library->nr_of_books; i++) {
        free(library->books[i].name);
        free(library->books[i].author);
    }
    free(library->books);
}

void delete_library(Library *library) {
    if (!library) {
        return;
    }
    if(!(library->books)) {
        return;
    }

    delete_books(library);
    free(library);
}

int search_book_by_name(const Library *library, const char *name) {

    for(int i = 0; i < library->nr_of_books; i++) {
        if(strcmp(name, library->books[i].name) == 0) {
            print_book_data(&library->books[i]);
            return i;
        }
    }
    return -1;
}

int search_book_by_author(const Library *library, const char *author) {

    for(int i = 0; i < library->nr_of_books; i++) {
        if(strcmp(author, library->books[i].author) == 0) {
            print_book_data(&library->books[i]);
            return i;
        }
    }
    return -1;
}

int search_book_by_pages(const Library *library, const int pages) {

    for(int i = 0; i < library->nr_of_books; i++) {
        if(pages == library->books[i].pages) {
            print_book_data(&library->books[i]);
            return i;
        }
    }
    return -1;
}

int search_book_by_price(const Library *library, const int price) {

    for(int i = 0; i < library->nr_of_books; i++) {
        if(price == library->books[i].price) {
            print_book_data(&library->books[i]);
            return i;
        }
    }
    return -1;
}

/*
 *
 * void sort_list_elements_generic(List *list, PersonComparatorPointer comparator) {
    for (Node *first_node = list->head; first_node; first_node = first_node->next) {
        for (Node *second_node = first_node; second_node; second_node = second_node->next) {
            if (comparator(first_node->person, second_node->person) > 0) {
                _swap_persons(first_node->person, second_node->person);
            }
        }
    }
}
 */

void sort_library_by_price(Library *library) {

    for(int i = 0; i < library->nr_of_books; i++) {
        for(int j = i; j < library->nr_of_books; j++) {
            if(library->books[i].price < library->books[j].price) {
                Book temp;
                memcpy(&temp, &library->books[i], sizeof(Book));
                memcpy(&library->books[i], &library->books[j], sizeof(Book));
                memcpy(&library->books[j], &temp, sizeof(Book));
            }
        }
    }
}

void sort_library_by_pages(Library *library) {

    for(int i = 0; i < library->nr_of_books; i++) {
        for(int j = i; j < library->nr_of_books; j++) {
            if(library->books[i].pages < library->books[j].pages) {
                Book temp;
                memcpy(&temp, &library->books[i], sizeof(Book));
                memcpy(&library->books[i], &library->books[j], sizeof(Book));
                memcpy(&library->books[j], &temp, sizeof(Book));
            }
        }
    }
}

Book* alloc_book() {
    Book *book = malloc(sizeof(Book));
    book->name = malloc(sizeof(char) * 100);
    book->author = malloc(sizeof(char) * 100);
    return book;
}

Book* alloc_books(unsigned int size) {
    Book* books = malloc(sizeof(Book) * size);
    for(int i = 0; i < size; i++) {
        books[i].name = malloc(sizeof(char) * 100);
        books[i].author = malloc(sizeof(char) * 100);
    }
    return books;
}

Book *read_book_from_console() {

    Book *book = alloc_book();
    printf("Dati denumirea cartii:");
    scanf("%s", book->name);
    printf("Autor:");
    scanf("%s", book->author);
    printf("Pagini:");
    scanf("%d", &book->pages);
    printf("Pret:");
    scanf("%d", &book->price);
    return book;
}

void copy_book(Book* dest, const Book* source) {
    strcpy(dest->name, source->name);
    strcpy(dest->author, source->author);
    dest->price = source->price;
    dest->pages = source->pages;
}

void insert_book_at_the_end(Library *library, const Book *new_book) {

    Book* new_books = alloc_books(library->nr_of_books+1);
    for(int i = 0; i < library->nr_of_books; i++) {
        copy_book(&new_books[i], &library->books[i]);
    }
    copy_book(&new_books[library->nr_of_books], new_book);

    delete_books(library);
    library->books = new_books;
    library->nr_of_books++;

}

void insert_book_at_position(Library *library, const Book *new_book, const int position) {

    if(position >= library->nr_of_books) {
        printf("Position is bigger than nr of books\n");
        return;
    }

    Book* new_books = alloc_books(library->nr_of_books+1);
    for(int i = 0; i < position; i++) {
        copy_book(&new_books[i], &library->books[i]);
    }

    for(int i = library->nr_of_books - 1; i >= position; i--) {
        copy_book(&new_books[i+1], &library->books[i]);
    }

    copy_book(&new_books[position], new_book);
    delete_books(library);
    library->books = new_books;
    library->nr_of_books++;
}


/*

void search(Book *books, int nr_of_books) {

    int search_pages;
    int search_price;
    char *search_name = malloc(sizeof(char) * 100);
    char *search_author = malloc(sizeof(char) * 100);

    int option;
    printf("Search by\n");
    printf("(1) search by name\n");
    printf("(2) search by author\n");
    printf("(3) search by pages\n");
    printf("(4) search by price\n");
    scanf("%d", &option);

    if (option == 1) {
        printf("Introduceti numele pentru cautare: ");
        scanf("%s", search_name);

        for (int i = 0; i < nr_of_books; i++) {
            if (strcmp(books[i].name, search_name) == 0) {
                printf("Autor: %s\nPagini: %d\nPret: %d\n", books[i].author, books[i].pages, books[i].price);
            }
        }
    } else if (option == 2) {
        printf("Introduceti autorul pentru cautare: ");
        scanf("%s", search_author);

        for (int i = 0; i < nr_of_books; i++) {
            if (strcmp((const char *) books[i].author, search_author) == 0) {
                printf("Nume: %s\nPagini: %d\nPret: %d\n", books[i].name, books[i].pages, books[i].price);
            }
        }
    } else if (option == 3) {

        printf("Introduceti pagina pentru cautare: ");
        scanf("%d", &search_pages);

        for (int i = 0; i < nr_of_books; i++) {
            if (books[i].pages == search_pages) {
                printf("Nume: %s\nAutor: %s\nPret: %d\n", books[i].name, books[i].author, books[i].price);
            }
        }
    } else if (option == 4) {

        printf("Introduceti pretul pentru cautare: ");
        scanf("%d", &search_price);

        for (int i = 0; i < nr_of_books; i++) {
            if (books[i].price == search_price) {
                printf("Nume: %s\nAutor: %s\nPagini: %d\n", books[i].name, books[i].author, books[i].pages);
            }
        }
    }
    free(search_name);
    free(search_author);
}

void swap(struct book *a, struct book *b) {
    struct book temp = *a;
    *a = *b;
    *b = temp;
}

void sort_elements_by_name(Book *books, int nr_of_books) {

    for (int i = 0; i < nr_of_books - 1; i++) {
        for (int j = 0; j < nr_of_books - i - 1; j++) { //penultimul elem nesortat
            if (books[j].name[0] > books[j + 1].name[0]) {
                swap(&books[j], &books[j + 1]);
            }
        }
    }
}

void sort_elements_by_author(Book *books, int nr_of_books) {

    for (int i = 0; i < nr_of_books - 1; i++) {
        for (int j = 0; j < nr_of_books - i - 1; j++) {
            if (books[j].author[0] > books[j + 1].author[0]) {
                swap(&books[j], &books[j + 1]);
            }
        }
    }
}

void sort_elements_by_pages(Book *books, int nr_of_books) {

    for (int i = 0; i < nr_of_books - 1; i++) {
        for (int j = 0; j < nr_of_books - i - 1; j++) {
            if (books[j].pages > books[j + 1].pages) {
                swap(&books[j], &books[j + 1]);
            }
        }
    }
}

void sort_elements_by_price(Book *books, int nr_of_books) {

    for (int i = 0; i < nr_of_books - 1; i++) {
        for (int j = 0; j < nr_of_books - i - 1; j++) {
            if (books[j].price > books[j + 1].price) {
                swap(&books[j], &books[j + 1]);
            }
        }
    }

}

struct book create_book() {

    struct book Book;

    printf("add an interesting book:\n");
    printf("Name:");
    Book.name = malloc(sizeof(char) * 100);
    scanf("%s", Book.name);
    printf("Author:");
    Book.author = malloc(sizeof(char) * 100);
    scanf("%s", Book.author);
    printf("Pages:");
    scanf("%d", &Book.pages);
    printf("Price:");
    scanf("%d", &Book.price);

    return Book;
}

void print_books(struct book *vect, int nr_of_books) {
    printf("\nlist of books:\n");

    for (int i = 0; i < nr_of_books; ++i) {
        printf("Book %d:\n", i + 1);
        printf("Name: %s\n", vect[i].name);
        printf("Author: %s\n", vect[i].author);
        printf("Pages: %d\n", vect[i].pages);
        printf("Price: %d\n", vect[i].price);
        printf("\n");
    }
}

struct book *add_elem_start(Book *books, int nr_of_books) {

    (*nr_of_books)++;

    vect = realloc(vect, (*nr_of_books) * sizeof(struct book));

    for (int i = (*nr_of_books) - 1; i > 0; --i) { // -1 la ultim elem
        vect[i] = vect[i - 1];
    }

    vect[0] = create_book();
    print_books(vect, (int) nr_of_books);
    return vect;
}

struct book *add_elem_end(struct book *vect, int *nr_of_books) {

    (*nr_of_books)++;
    vect = realloc(vect, (*nr_of_books) * sizeof(struct book));

    vect[*nr_of_books - 1] = create_book();

    return &(vect[*nr_of_books - 1]); //& adresa memoriei unde e stocat ultimul elem
}

void insert_element(struct book **vect, int *nr_of_books) {

    int option;
    printf("Choose an option:\nwhere?\n");
    printf("`1` 0\n");
    printf("`2` last\n");
    printf("`3` x\n");
    scanf("%d", &option);

    int position = 0;

    if (option == 1) {

        printf("\naaaaaaaam intrat in optiunea 1\n");

        *vect = add_elem_start(*vect, nr_of_books);

        printf("\ntotul merge bine\n");

    } else if (option == 2) {

        printf("Am intrat in optiunea 2. TEST\n");

        *vect = add_elem_end(*vect, nr_of_books);

    } else if (option == 3) {

        printf("input positionnnnnnnn:");
        scanf("%d", &position);

        if (position >= 0 && position <= *nr_of_books) {
            (*nr_of_books)++;
            *vect = realloc(*vect, (*nr_of_books) * sizeof(struct book));

            for (int i = *nr_of_books - 1; i > position; --i) {
                *(vect + i) = *(vect + i - 1);
                vect[i] = vect[i - 1];
            }
            (*vect)[position] = create_book();
        } else {
            printf("INTRODU CORECT!!!!!!!!!!!1");
        }
    }
}

void delete_element(void **vect, int *nr_of_books) {

    int position;
    printf("input positionnnnnnnn:");
    scanf("%d", &position);

    if (position >= 0 && position < *nr_of_books) {
        for (int i = position; i < *nr_of_books - 1; i++) {
            vect[i] = vect[i + 1];
        }
        (*nr_of_books)--;
        *vect = realloc(*vect, (*nr_of_books) * sizeof(struct book));
    } else {
        printf("doesnt exist");
    }
}

*/

int main() {

    Library* library = read_books_from_file_by_path("file.txt");
    print_library(library);

    Book* new_book = read_book_from_console();
    //print_book_data(new_book);


    //insert_book_at_the_end(library, new_book);
    insert_book_at_position(library, new_book, 3);

    //free(new_book);
    print_library(library);
    delete_library(library);

    /*
    int nr;
    while (1) {
        printf("\n");
        printf("-1-  Display books\n");
        printf("-2-  Search books\n");
        printf("-3-  Sort books\n");
        printf("-4-  Input\n");
        printf("-5-  Delete\n");
        printf("-0-  Exit\n");
        scanf("%d", &nr);

        if (nr == 1) {
            Book *book;
            print_array_of_books(book, nr_of_books);
        } else if (nr == 2) {
            search(vect, nr_of_books);
        } else if (nr == 3) {
            sort_elements(vect, nr_of_books);
        } else if (nr == 4) {

            int option;
            printf("Choose an option:\n~~Sort by~~:\n");
            printf("(1) Name\n");
            printf("(2) Author\n");
            printf("(3) Pages\n");
            printf("(4) Price\n");
            scanf("%d", &option);

            Book *books;
            if (option == 1) {
                sort_elements_by_name(books, nr_of_books);
            } else if (option == 2) {
                sort_elements_by_author(books, nr_of_books);
            } else if (option == 3) {
                sort_elements_by_pages(books, nr_of_books);
            } else if (option == 4) {
                sort_elements_by_price(books, nr_of_books);
            }
            insert_element(vect, &nr_of_books);

        } else if (nr == 5) {
            delete_element((void **) vect, &nr_of_books);
        } else if (nr == 0) {
            break;
        }
    }

    Book *books = NULL;
    delete_array_of_books(books, nr_of_books);

     */
    return 0;
}

