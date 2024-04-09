#ifndef SDA_MODELS_H
#define SDA_MODELS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

typedef struct document Document;

struct document {
    int id;
    char *doc_name;
    int nr_of_lines;
    int remain_lines;
    Document *next_doc;
};

Document* create_document(int id, const char* doc_name, int nr_of_lines);

Document* create_list_of_random_documents(int nr_of_docs);

void delete_document(Document** document);

void delete_list_of_documents(Document** documents_head);

Document* pop_document(Document** documents_head);

void push_document(Document** documents_head, Document* new_document);

typedef struct printer Printer;

struct printer {
    int id;
    int time_to_process;
    Document *current_doc;
    Printer *next_printer;
};

Printer* create_printer(int id, int time_to_process);


void push_printer(Printer** printers_head, Printer* new_printer);

Printer* pop_printer(Printer** printers_head);

Printer* create_list_of_random_printers(int nr_of_printers);

void delete_printer(Printer** printer);

void delete_list_of_printers(Printer** printers_head);


#endif //SDA_MODELS_H
