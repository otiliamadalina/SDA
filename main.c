#include <stdio.h>
#include "model.h"

enum MENU {
    PRINT_ELEMENTS = 1,
    SEARCH_NODE,
    VSD,
    SVD,
    SDV,
    DFS,
    BFS,
    BALANCE_TREE,
    MIRROR_TREE,
    CLEAR_ELEMENTS,
    FREE_TREE,
    EXIT_PROGRAM
};

void print_menu_list() {
    printf("MENU:\n"
           "(%d)Print Elements\n"
           "(%d)Search a node\n"
           "(%d)VSD\n"
           "(%d)SVD\n"
           "(%d)SDV\n"
           "(%d)DFS\n"
           "(%d)BFS\n"
           "(%d)Balance tree\n"
           "(%d)Mirror tree\n"
           "(%d)Clear tree\n"
           "(%d)Free tree\n"
           "(%d)EXIT\nChoose: ",
           PRINT_ELEMENTS, SEARCH_NODE, VSD, SVD, SDV,
           DFS, BFS, BALANCE_TREE, MIRROR_TREE, CLEAR_ELEMENTS, FREE_TREE, EXIT_PROGRAM);
}

int main() {

    SearchTree *tree = create_tree_with_elements(10);
    print_menu_list();
    
    int choice;
    scanf("%d", &choice);

    switch (choice) {

        case (PRINT_ELEMENTS):
            pretty_printf_search_tree(tree);
            break;

        case (SEARCH_NODE):
            find_tree_element(tree, 1);
            break;

        case (VSD):
            print_tree_vsd((TreeElement *) tree);
            break;

        case (SVD):
            print_tree_svd((TreeElement *) tree);
            break;

        case (SDV):
            print_tree_sdv((TreeElement *) tree);
            break;

        case (DFS):
            print_tree_depth((TreeElement *) tree);
            break;

        case (BFS):
            print_tree_vsd((TreeElement *) tree);
            break;

        case (BALANCE_TREE):
            balance_tree(tree);
            break;

        case (MIRROR_TREE):
            mirror_tree(tree);
            break;

        case (CLEAR_ELEMENTS):
            clear_tree(tree);
            break;

        case (FREE_TREE):
            delete_tree(tree);
            break;

        default:
            printf("No valid choice!\n");
    }

    return 0;
}