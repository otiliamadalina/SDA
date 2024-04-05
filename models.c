#include "models.h"


Document* create_document(int id, const char* doc_name, int nr_of_lines) {

    Document* document = malloc(sizeof(Document));

    document->id = id;
    document->doc_name = malloc(sizeof(strlen(doc_name)));
    strcpy(document->doc_name, doc_name);
    document->nr_of_lines = nr_of_lines;
    document->remain_lines = nr_of_lines;
    document->next_doc = NULL;

    return document;

}

Document* create_list_of_random_documents(int nr_of_docs) {

}

void delete_document(Document **document) {

    free((*document)->doc_name);
    free(*document);
    (*document) = NULL;
}

void delete_list_of_documents(Document **documents_head) {

}

Document* pop_document(Document** documents_head) {

}

Printer* create_printer(int id, int time_to_process) {

    Printer *printer = malloc(sizeof(Printer));

    printer->id = id;
    printer->time_to_process = time_to_process;
    printer->current_doc = NULL;
    printer->next_printer = NULL;

    return printer;
}

Printer* create_list_of_random_printers(int nr_of_printers) {

}

void delete_printer(Printer** printer) {

    free(*printer);
    (*printer) = NULL;
}

void delete_list_of_printers(Printer** printers_head) {

}