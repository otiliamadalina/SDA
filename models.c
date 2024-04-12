#include "models.h"


Document *create_document(int id, const char *doc_name, int nr_of_lines) {

    Document *document = malloc(sizeof(Document));

    document->id = id;
    document->doc_name = malloc(sizeof(strlen(doc_name)));
    strcpy(document->doc_name, doc_name);
    document->nr_of_lines = nr_of_lines;
    document->remain_lines = nr_of_lines;
    document->next_doc = NULL;

    return document;

}

Document *create_list_of_random_documents(int nr_of_docs) {
    Document *head = NULL;

    for (int iter = 0; iter < nr_of_docs; ++iter) {
        Document *new_document = create_document(generate_random_number(),
                                                 generate_random_string(),
                                                 generate_random_number());
        push_document(&head, new_document);
    }

    return head;
}

void delete_document(Document **document) {
    if(*document == NULL) return;
    free((*document)->doc_name);
    free(*document);
    (*document) = NULL;
}

void delete_list_of_documents(Document **documents_head) {
    Document *previous_doc = NULL;

    while (*documents_head != NULL) {
        previous_doc = *documents_head;
        (*documents_head) = (*documents_head)->next_doc;
        delete_document(&previous_doc);
    }

    (*documents_head) = NULL;
}

Document *pop_document(Document **documents_head) {
    if (*documents_head == NULL) return NULL;
    Document *first_document = *documents_head;
    (*documents_head) = (*documents_head)->next_doc;
    return first_document;
}

void push_document(Document **documents_head, Document *new_document) {
    if (new_document == NULL) return;

    if (*documents_head == NULL) {
        (*documents_head) = new_document;
    } else {
        Document *doc_iter = *documents_head;
        while (doc_iter->next_doc != NULL) doc_iter = doc_iter->next_doc;
        doc_iter->next_doc = new_document;
    }
}

Printer *create_printer(int id, int time_to_process) {

    Printer *printer = (Printer *) malloc(sizeof(Printer));

    printer->id = id;
    printer->time_to_process = time_to_process;
    printer->current_doc = NULL;
    printer->next_printer = NULL;

    return printer;
}

void push_printer(Printer **printers_head, Printer *new_printer) {
    if (*printers_head == NULL) {
        *printers_head = new_printer;
        return;
    }
    new_printer->next_printer = *printers_head;
    *printers_head = new_printer;
}

Printer *pop_printer(Printer **printers_head) {
    if (*printers_head == NULL) return NULL;
    Printer *tmp_printer = (*printers_head);
    (*printers_head) = (*printers_head)->next_printer;
    tmp_printer->next_printer = NULL;
    return tmp_printer;
}

Printer *create_list_of_random_printers(int nr_of_printers) {
    Printer *printers_head = NULL;
    for (int iter = 0; iter < nr_of_printers; ++iter) {
        Printer *new_printer = create_printer(generate_random_number(), generate_random_number());
        push_printer(&printers_head, new_printer);
    }
    return printers_head;
}

void delete_printer(Printer **printer) {
    free(*printer);
    (*printer) = NULL;
}

void delete_list_of_printers(Printer **printers_head) {
    Printer *previous_printer = NULL;

    while (*printers_head != NULL) {
        previous_printer = *printers_head;
        (*printers_head) = (*printers_head)->next_printer;
        delete_printer(&previous_printer);
    }

    (*printers_head) = NULL;
}

void print_list_of_printers(Printer **printers_head) {
    Printer *list_iter = *printers_head;
    printf("---Showing printers---\n");
    for (; list_iter != NULL; list_iter = list_iter->next_printer) {
        printf("ID: %d | Time to pricess: %d | Current doc: ", list_iter->id, list_iter->time_to_process);
        if (list_iter->current_doc == NULL) {
            printf("NULL");
        } else {
            printf("%d | Remain Time %d/%d",
                   list_iter->current_doc->id,
                   list_iter->current_doc->remain_lines,
                   list_iter->current_doc->nr_of_lines);
        }
        printf("\n");
    }
}

void print_list_of_documents(Document **documents_head) {
    Document *list_iter = *documents_head;
    printf("---Showing Documents---\n");
    for (; list_iter != NULL; list_iter = list_iter->next_doc) {
        printf("ID: %d | Doc: %s | Lines: %d | Remain lines: %d\n", list_iter->id, list_iter->doc_name,
               list_iter->nr_of_lines, list_iter->remain_lines);
    }
}