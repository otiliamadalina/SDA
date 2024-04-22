#include <stdio.h>
#include "model.h"

int main() {

    Tree *test_tree = create_tree_with_elements(10);
    //print_tree(test_tree);
    print_tree_leafs(test_tree);
    printf("Tree depth: %d\n", calculate_tree_depth(test_tree));
    printf("Depth of element nr 5 is: %d\n", calculate_tree_element_depth(test_tree,
                                                                          find_tree_element(test_tree, 5)));
    printf("Height of element nr 5 is: %d\n", calculate_tree_element_height(find_tree_element(test_tree, 5)));

    delete_tree(test_tree);
    add_element_to_tree(test_tree, NULL);


    return 0;
}