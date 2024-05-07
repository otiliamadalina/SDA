#include <stdio.h>
#include "model.h"

int main() {

    Tree *test_tree = create_tree_with_elements(10);

    int choice;
    printf("MENU:\n(1)Print Elements\n(2)Depth of the tree\n(3)Search a node(4)Depth of the node\n(5)Height of the node\n(6)Print Leafs\n(7)Clear Elements\n(8)Free tree\nChoose: ");
    scanf("%d", choice);

    switch(choice) {

        case(PRINT_ELEMENTS):
            print_tree(test_tree);
            break;

        case(DEPTH_TREE):
            printf("Tree depth: %d\n", calculate_tree_depth(test_tree));
            break;

        case(SEARCH_NODE):

            break;

        case(DEPTH_NODE):
            printf("Choose a node: ");
            int node;
            scanf("%d", &node);
            printf("Depth of element nr %d is: %d\n", node, calculate_tree_element_depth(test_tree,
                                                                                  find_tree_element(test_tree, node)));
            break;

        case(HEIGHT_NODE):
            printf("Choose a node: ");
            int element;
            scanf("%d", &element);
            printf("Height of element nr %d is: %d\n", element, calculate_tree_element_height(find_tree_element(test_tree, element)));
            break;

        case(PRINT_LEAFS):
            print_tree_leafs(test_tree);
            break;

        case(CLEAR_ELEMENTS):
            clear_tree(test_tree);
            break;

        case(FREE_TREE):
            delete_tree(test_tree);
            break;

        default:
            printf("No valid choice!");
    }
    /*
    Tree *test_tree = create_tree_with_elements(10);
    //print_tree(test_tree);
    print_tree_leafs(test_tree);
    printf("Tree depth: %d\n", calculate_tree_depth(test_tree));
    printf("Depth of element nr 5 is: %d\n", calculate_tree_element_depth(test_tree,
                                                                          find_tree_element(test_tree, 5)));
    printf("Height of element nr 5 is: %d\n", calculate_tree_element_height(find_tree_element(test_tree, 5)));

    delete_tree(test_tree);
    add_element_to_tree(test_tree, NULL);

*/
    return 0;
}