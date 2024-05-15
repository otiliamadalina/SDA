#include <stdio.h>
#include "model.h"
#include <math.h>

enum MENU {
    PRINT_ELEMENTS = 1,
    DEPTH_TREE,
    SEARCH_NODE,
    DEPTH_NODE,
    HEIGHT_NODE,
    PRINT_LEAFS,
    CLEAR_ELEMENTS,
    FREE_TREE
};

void print_menu_list() {
    printf("MENU:\n"
           "(%d)Print Elements\n"
           "(%d)Depth of the tree\n"
           "(%d)Search a node"
           "(%d)Depth of the node\n"
           "(%d)Height of the node\n"
           "(%d)Print Leafs\n"
           "(%d)Clear Elements\n"
           "(%d)Free tree\nChoose: ",
           PRINT_ELEMENTS, DEPTH_TREE, SEARCH_NODE, DEPTH_NODE, HEIGHT_NODE, PRINT_LEAFS, CLEAR_ELEMENTS, FREE_TREE);
}

int main() {

//    Tree *test_tree = create_tree_with_elements(10);
//
//    int choice;
//    scanf("%d", choice);
//
//    switch (choice) {
//
//        case (PRINT_ELEMENTS):
//            print_tree(test_tree);
//            break;
//
//        case (DEPTH_TREE):
//            printf("Tree depth: %d\n", calculate_tree_depth(test_tree));
//            break;
//
//        case (SEARCH_NODE):
//
//            break;
//
//        case (DEPTH_NODE):
//            printf("Choose a node: ");
//            int node;
//            scanf("%d", &node);
//            printf("Depth of element nr %d is: %d\n", node, calculate_tree_element_depth(test_tree,
//                                                                                         find_tree_element(test_tree,
//                                                                                                           node)));
//            break;
//
//        case (HEIGHT_NODE):
//            printf("Choose a node: ");
//            int element;
//            scanf("%d", &element);
//            printf("Height of element nr %d is: %d\n", element,
//                   calculate_tree_element_height(find_tree_element(test_tree, element)));
//            break;
//
//        case (PRINT_LEAFS):
//            print_tree_leafs(test_tree);
//            break;
//
//        case (CLEAR_ELEMENTS):
//            clear_tree(test_tree);
//            break;
//
//        case (FREE_TREE):
//            delete_tree(test_tree);
//            break;
//
//        default:
//            printf("No valid choice!\n");
//    }


    SearchTree* tree = create_tree_with_elements(10);
    pretty_printf_search_tree(tree);
    balance_tree(tree);
    pretty_printf_search_tree(tree);
    delete_tree(tree);
    return 0;
}