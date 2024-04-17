#include "model.h"
#include <stdlib.h>

TreeElement *create_tree_element(int element_id) {
    TreeElement *new_tree_element = (TreeElement *) malloc(sizeof(TreeElement));
    new_tree_element->element_id = element_id;
    new_tree_element->left_element = NULL;
    new_tree_element->right_element = NULL;
    return new_tree_element;
}

bool is_tree_element_a_leaf(const TreeElement *tree_element) {
    return ((tree_element->left_element == NULL) && (tree_element->right_element == NULL)) ? true : false;
}

int calculate_tree_element_depth(const TreeElement *) {
    //TODO
}

int calculate_tree_element_height(const TreeElement *) {
    //TODO
}

void delete_tree_element(TreeElement **element) {
    if (*element == NULL) {
        return;
    }
    delete_tree_element(&(*element)->left_element);
    delete_tree_element(&(*element)->right_element);
    free(*element);
    *element = NULL;
}

Tree *create_tree_with_random_elements(int nr_of_elements) {
    //TODO
}

void print_tree(const Tree *tree) {
    //TODO
}

void print_tree_leafs(const Tree *tree) {
    //TODO
}

int calculate_tree_depth(const Tree *tree) {
    //TODO
}

const TreeElement *find_tree_element(const Tree *tree, int element_id) {
    //TODO
}

void clear_tree(Tree *tree) {
    //TODO
}

void delete_tree(Tree *tree) {
    //TODO
}