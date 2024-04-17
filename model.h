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

int calculate_tree_element_depth(const TreeElement *);

int calculate_tree_element_height(const TreeElement *);

void delete_tree_element(TreeElement **element);

typedef struct tree Tree;

struct tree {
    TreeElement *tree_root;
};

Tree *create_tree_with_random_elements(int nr_of_elements);

void print_tree(const Tree *tree);

void print_tree_leafs(const Tree *tree);

int calculate_tree_depth(const Tree *tree);

const TreeElement *find_tree_element(const Tree *tree, int element_id);

void clear_tree(Tree *tree);

void delete_tree(Tree *tree);

#endif //SDA_MODEL_H
