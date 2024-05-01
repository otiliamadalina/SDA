#ifndef SDA_MODEL_H
#define SDA_MODEL_H

#include <stdbool.h>


typedef struct tree_element TreeElement;

struct tree_element {
    int element_id;

    TreeElement *left_element;
    TreeElement *right_element;
};

TreeElement *create_tree_element(int element_id);

bool is_tree_element_a_leaf(const TreeElement *tree_element);

int calculate_tree_element_height(const TreeElement *tree_element);

void delete_tree_element(TreeElement **element);

void clear_tree_element(TreeElement **element);

typedef struct tree Tree;

struct tree {
    TreeElement *tree_root;
};

Tree *create_tree();

int calculate_tree_element_depth(const Tree *tree, const TreeElement *tree_element);

Tree *create_tree_with_elements(int nr_of_elements);

TreeElement *add_element_to_tree(Tree *tree, TreeElement *tree_element);

void print_tree(const Tree *tree);

void print_tree_leafs(const Tree *tree);

int calculate_tree_depth(const Tree *tree);

const TreeElement *find_tree_element(const Tree *tree, int element_id);

void clear_tree(Tree *tree);

void delete_tree(Tree *tree);

const TreeElement *_find_tree_element(const TreeElement *current_element, int element_id);
void _print_tree_element_leaf_recursive(const TreeElement *tree_element);
void _print_tree_element_recursive(const TreeElement *tree_element);
TreeElement *_add_element_to_tree_to_left(TreeElement **current_element, TreeElement *tree_element);
int _calculate_tree_element_depth(const TreeElement *tree_element, int element_id);

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
#endif //SDA_MODEL_H
