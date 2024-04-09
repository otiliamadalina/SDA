#include "models.h"
#include "utils.h"

void test_documents() {
    Document* documents_head = create_list_of_random_documents(10);
    push_document(documents_head, NULL);

}