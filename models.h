#ifndef SDA_MODELS_H
#define SDA_MODELS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

typedef struct printer Printer;

struct printer {
    int id;
    int time_to_process;
    Document *current_doc;
    Printer *next_printer;
};

Printer* create_printer(int id, int time_to_process);

Printer* create_list_of_random_printers(int nr_of_printers);

void delete_printer(Printer** printer);

void delete_list_of_printers(Printer** printers_head);


#endif //SDA_MODELS_H
