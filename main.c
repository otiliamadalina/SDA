#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_SIZE 50

// TODO: rename MAX -> MAX_STR_SIZE
// TODO: function documentation according to doxygen standard
// TODO: typedef for struct Book

struct book {
    char name[MAX_STR_SIZE];
    char author[MAX_STR_SIZE];
    char genre[MAX_STR_SIZE];
    int pages;
    double price;
    struct book *next;
};

typedef struct book Book;

/**
 * Alloc memory for a Book structure
 * @result pointer to Book structure
 */

Book *create_book() {
    Book *new_book = (Book *)malloc(sizeof(Book));
    new_book->next = NULL;
    return new_book;
}

/**
 * Read list
 * @param head pointer to list
 * @return void
 */

void read_list(Book **head) {
    int n;
    printf("cate carti?\n");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        Book *new_book = create_book();

        printf("Nume: ");
        scanf("%s", new_book->name);

        printf("Autor: ");
        scanf("%s", new_book->author);

        printf("Gen: ");
        scanf("%s", new_book->genre);

        printf("Pagini: ");
        scanf("%d", &new_book->pages);

        printf("Pret: ");
        scanf("%lf", &new_book->price);

        printf("\n");

        new_book->next = *head;
        *head = new_book;
    }
}

/**
 * Display list
 * @param head pointer to list
 * @return void
 */

void display_list(Book *head) {
    Book *current = head;

    printf("\n\tbook list:\n");
    while (current != NULL) {
        printf("Nume: %s\n Autor: %s\n Gen: %s\n Pagini: %d\n Pret: %.2lf\n\n",
               current->name, current->author, current->genre, current->pages,
               current->price);
        current = current->next;
    }
    printf("\n");
}

/**
 * Read list of books
 * @param head pointer to list
 * @param name_searched pointer to the name to search for in the list
 * @return position of the book or "-1" if the position doesnt exist
 */

int search_book_by_name(Book *head, const char *name_searched) {
    int position = 1;
    Book *current = head;

    while (current != NULL) {
        if (strcmp(current->name, name_searched) == 0) {
            return position;
        }
        current = current->next;
        position++;
    }
    return -1;
}

/**
 * Free memory for book structure
 * @param head pointer to list
 * @return void
 */

void free_memory(Book **head) {
    while (*head != NULL) {
        Book *temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

/**
 * Sort list of books by price
 * @param head pointer to list
 * @return void
 */

void sort_list_by_price(Book **head) {

    Book *current, *next, *prev = NULL;
    int swapped;

    do {
        swapped = 0;
        current = *head;

        while (current->next != NULL) {
            next = current->next;

            if (current->price > next->price) {

                float temp = current->price;
                current->price = next->price;
                next->price = temp;
                swapped = 1;
            }

            prev = current;
            current = current->next;
        }
    } while (swapped);
}

/**
 * Insert a book at the end of the list
 * @param head pointer to list
 * @return void
 */

void insert_at_end(Book **head) {
    Book *new_book = create_book();
    new_book->next = NULL;

    printf("Nume:");
    scanf("%s", new_book->name);

    printf("Autor:");
    scanf("%s", new_book->author);

    printf("Gen:");
    scanf("%s", new_book->genre);

    printf("Pagini:");
    scanf("%d", &new_book->pages);

    printf("Pret:");
    scanf("%lf", &new_book->price);

    if (*head == NULL) {
        *head = new_book;
    } else {
        Book *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_book;
    }
}

/**
 * Insert a book at the start of the list
 * @param head pointer to list
 * @return void
 */

void insert_at_start(Book **head) {
    Book *new_book = create_book();

    printf("Nume:");
    scanf("%s", new_book->name);

    printf("Autor:");
    scanf("%s", new_book->author);

    printf("Gen:");
    scanf("%s", new_book->genre);

    printf("Pagini:");
    scanf("%d", &new_book->pages);

    printf("Pret:");
    scanf("%lf", &new_book->price);

    new_book->next = *head;
    *head = new_book;
}

/**
 * Insert a book at a specified position of the list
 * @param head pointer to list
 * @param position a variabile to the position to insert in the list
 * @return void
 */

void insert_at_position(Book **head, int position) {

    Book *new_book = create_book();

    printf("Nume:");
    scanf("%s", new_book->name);

    printf("Autor:");
    scanf("%s", new_book->author);

    printf("Gen:");
    scanf("%s", new_book->genre);

    printf("Pagini:");
    scanf("%d", &new_book->pages);

    printf("Pret:");
    scanf("%lf", &new_book->price);

    if (position == 1) {
        new_book->next = *head;
        *head = new_book;
    } else {
        Book *current = *head;
        for (int i = 1; i < position - 1 && current != NULL; i++) {
            current = current->next;
        }
        new_book->next = current->next;
        current->next = new_book;
    }
}

/**
 * Delete a book at a specified position of the list
 * @param head pointer to list
 * @param position a variabile to the position to insert in the list
 * @return void
 */

void delete_at_position(Book **head, int position) {

    Book *temp;

    if (position == 1) {
        temp = *head;
        *head = (*head)->next;
    } else {
        Book *current = *head;
        for (int i = 1; i < position - 1 && current != NULL; i++) {
            current = current->next;
        }
        temp = current->next;
        current->next = temp->next;
    }
    free(temp);
}

/**
 * Reverse the whole list
 * @param head pointer to list
 * @return void
 */

void reverse_list(Book **head) {

    Book *prev = NULL, *current = *head, *next;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head = prev;
}

/**
 * Clear the list
 * @param head pointer to list
 * @return void
 */

void clear_list(Book **head) { free_memory(head); }

int main() {

    Book *book_list = NULL;
    int choice;

    do {
        printf("\n1. citeste\n");
        printf("2. afiseaza\n");
        printf("3. cauta\n");
        printf("4. sorteaza\n");
        printf("5. insert end\n");
        printf("6. insert start\n");
        printf("7. insert X\n");
        printf("8. delete X\n");
        printf("9. inverseaza\n");
        printf("10. curata\n");
        printf("11. exit\n");

        printf("\nalege: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                read_list(&book_list);
                break;
            case 2:
                display_list(book_list);
                break;
            case 3: {
                char search_name[MAX_STR_SIZE];
                printf("scrie denumirea cartii pentru cautare: ");
                scanf("%s", search_name);
                int position = search_book_by_name(book_list, search_name);
                if (position != -1) {
                    printf("cartea %s este pe pozitia %d.\n", search_name, position);
                } else {
                    printf("cartea nu a fost gasita.\n", search_name);
                }
                break;
            }
            case 4:
                sort_list_by_price(&book_list);
                break;
            case 5:
                insert_at_end(&book_list);
                break;
            case 6:
                insert_at_start(&book_list);
                break;
            case 7: {
                int position;
                printf("care pozitie? ");
                scanf("%d", &position);
                insert_at_position(&book_list, position);
                break;
            }
            case 8: {
                int position;
                printf("care pozitie? ");
                scanf("%d", &position);
                delete_at_position(&book_list, position);
                break;
            }
            case 9:
                reverse_list(&book_list);
                break;
            case 10:
                clear_list(&book_list);
                break;
            case 11:
                break;
            default:
                printf("nu i asa optiune.\n");
        }
    } while (choice != 11);

    return 0;
}
