#include <stdbool.h>
#include "models.h"
#include "tests.c"

#define DEFAULT_NR_OF_PRINTERS 1000

bool iterate_session_optimized(Printer **printers_head, Document **documents_head);

bool iterate_session(Printer **printers_head, Document **documents_head, time_t* iter_time) {
    time_t start_time = time(0), end_time ;
    Printer *printer_iter = *printers_head;
    bool finish_flag = true;
    for (; printer_iter != NULL; printer_iter = printer_iter->next_printer) {
        if (printer_iter->current_doc == NULL) {
            Document *new_doc = pop_document(documents_head);
            printer_iter->current_doc = new_doc;
            if(new_doc == NULL) continue;
        }
        if (printer_iter->current_doc->remain_lines > 0) {
            printer_iter->current_doc->remain_lines -= printer_iter->time_to_process;
            finish_flag = false;
        } else {
            delete_document(&printer_iter->current_doc);
        }
    }
    end_time = time(0);
    *iter_time += end_time - start_time;
    return finish_flag;
}

int main() {
    srand(time(NULL));
    Printer *printers_head = create_list_of_random_printers(DEFAULT_NR_OF_PRINTERS);
    Document *documents_head = create_list_of_random_documents(DEFAULT_NR_OF_PRINTERS);
    time_t total_iterated_time = 0;

    do {
        print_list_of_printers(&printers_head);
        print_list_of_documents(&documents_head);
        printf("---------------------------------------------------------------------------------------------------\n");
    } while (iterate_session(&printers_head, &documents_head, &total_iterated_time));

    print_list_of_printers(&printers_head);

    printf("Time to process in seconds:\n%lf", ((double)total_iterated_time / CLOCKS_PER_SEC));

    delete_list_of_printers(&printers_head);
    delete_list_of_documents(&documents_head);
    return 0;
}
