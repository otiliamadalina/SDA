#include <stdio.h>
#include "model.h"

int main() {

    Tree *test_tree = create_tree_with_elements(10);


    bool do_exit = false;
    while (!do_exit) {
        printf("Choose an option:");
        int choice;
        scanf("%d", &choice);
        switch (choice) {
            case (PRINT_ELEMENTS):
                print_tree(test_tree);
                break;

            case (DEPTH_TREE):
                printf("Tree depth: %d\n", calculate_tree_depth(test_tree));
                break;

            case (DEPTH_NODE):
                printf("Choose the node: ");
                int *node = NULL;
                scanf("%d", node);
                printf("Depth of element nr %d is: %d\n", node, calculate_tree_element_depth(test_tree,
                                                                                             find_tree_element(
                                                                                                     test_tree,
                                                                                                     (int) &node)));
                break;

            case (HEIGHT_NODE):
                printf("Choose the node: ");
                int *element = NULL;
                scanf("%d", element);
                printf("Height of element nr %d is: %d\n", element, calculate_tree_element_height(test_tree));
                break;

            case (PRINT_LEAFS):
                print_tree_leafs(test_tree);
                break;

            case (CLEAR_ELEMENTS):
                clear_tree(test_tree);
                break;

            case (FREE_TREE):
                delete_tree(test_tree);
                break;

            case (EXIT_PROGRAM):
                do_exit = true;
                break;

            default:
                printf("No valid choice\n");
                break;
        }
    }

    delete_tree(test_tree);

    return 0;
}