#include "model.h"
#include <stdlib.h>
#include <stdio.h>

const char *error_on_print_message = "Error on printing";
const char *error_on_add_message = "Error on adding element";


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

int _calculate_tree_element_depth(const TreeElement *tree_element, int element_id) {
    if (tree_element == NULL) return 0;
    if (tree_element->element_id == element_id) {
        return 1;
    }
    int left = _calculate_tree_element_depth(tree_element->left_element, element_id);
    if (left > 0) {
        return left + 1;
    }
    int right = _calculate_tree_element_depth(tree_element->right_element, element_id);
    if (right > 0) {
        return right + 1;
    }
    return -1;
}

int calculate_tree_element_depth(const Tree *tree, const TreeElement *tree_element) {
    return _calculate_tree_element_depth(tree->tree_root, tree_element->element_id);
}

int calculate_tree_element_height(const TreeElement *tree_element) {
    if (tree_element == NULL) {
        return -1;
    }

    int left_side;
    int right_side;
    left_side = calculate_tree_element_height(tree_element->left_element);
    right_side = calculate_tree_element_height(tree_element->right_element);

    if (left_side > right_side) {
        return left_side + 1;
    } else
        return right_side + 1;

    return -1;
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

void clear_tree_element(TreeElement **element) {
    delete_tree_element(&(*element));
    free(*element);
    *element = NULL;
}

TreeElement *_add_element_to_tree_to_left(TreeElement **current_element, TreeElement *tree_element) {
    if ((*current_element)->left_element == NULL) {
        (*current_element)->left_element = tree_element;
        return (*current_element)->left_element;
    }
    if ((*current_element)->right_element == NULL) {
        (*current_element)->right_element = tree_element;
        return (*current_element)->right_element;
    }
    return _add_element_to_tree_to_left(&((*current_element)->left_element), tree_element);
}

TreeElement *add_element_to_tree(Tree *tree, TreeElement *tree_element) {
    if (tree == NULL || tree_element == NULL) {
        printf("%s: Tree or tree_element is NULL\n", error_on_add_message);
        return NULL;
    }
    if (tree->tree_root == NULL) {
        tree->tree_root = tree_element;
        return tree_element;
    }
    return _add_element_to_tree_to_left(&(tree->tree_root), tree_element);
}

Tree *create_tree() {
    Tree *tree = (Tree *) malloc(sizeof(Tree));
    tree->tree_root = NULL;
    return tree;
}

Tree *create_tree_with_elements(int nr_of_elements) {
    Tree *tree = create_tree();

    for (int i = 0; i < nr_of_elements; i++) {
        TreeElement *new_tree_element = create_tree_element(i);
        add_element_to_tree(tree, new_tree_element);
    }

    return tree;
}

void _print_tree_element_recursive(const TreeElement *tree_element) {
    if (tree_element == NULL) return;
    printf("%d\n", tree_element->element_id);
    _print_tree_element_recursive(tree_element->left_element);
    _print_tree_element_recursive(tree_element->right_element);
}

void print_tree(const Tree *tree) {
    if (tree == NULL) {
        printf("%s: Tree is NULL\n", error_on_print_message);
        return;
    }
    if (tree->tree_root == NULL) {
        printf("%s: Tree root is NULL", error_on_print_message);
    }
    _print_tree_element_recursive(tree->tree_root);
}

void _print_tree_element_leaf_recursive(const TreeElement *tree_element) {
    if (tree_element == NULL) return;
    if (is_tree_element_a_leaf(tree_element)) {
        printf("%d\n", tree_element->element_id);
    }
    _print_tree_element_leaf_recursive(tree_element->left_element);
    _print_tree_element_leaf_recursive(tree_element->right_element);
}

void print_tree_leafs(const Tree *tree) {
    if (tree == NULL) {
        printf("%s: Tree is NULL\n", error_on_print_message);
        return;
    }
    if (tree->tree_root == NULL) {
        printf("%s: Tree root is NULL", error_on_print_message);
    }
    _print_tree_element_leaf_recursive(tree->tree_root);
}

int calculate_tree_depth(const Tree *tree) {
    if (tree == NULL) {
        printf("%s: Tree is NULL\n", error_on_print_message);
        return -1;
    }
    if (tree->tree_root == NULL) {
        printf("%s: Tree root is NULL", error_on_print_message);
        return -1;
    }
    return calculate_tree_element_height(tree->tree_root);
}

const TreeElement *_find_tree_element(const TreeElement* current_element, int element_id) {
    if(current_element == NULL) return NULL;
    if(current_element->element_id == element_id) {
        return current_element;
    }
    const TreeElement* searched_element = _find_tree_element(current_element->left_element, element_id);
    if(searched_element != NULL) return searched_element;
    return _find_tree_element(current_element->right_element, element_id);
}

const TreeElement *find_tree_element(const Tree *tree, int element_id) {
    if (tree == NULL) {
        printf("%s: Tree is NULL\n", error_on_print_message);
        return NULL;
    }
    return _find_tree_element(tree->tree_root, element_id);
}

void clear_tree(Tree *tree) {
    if (tree == NULL) {
        return;
    }
    delete_tree_element(&tree->tree_root);
    free(tree);
}

void delete_tree(Tree *tree) {
    if (tree == NULL) {
        return;
    }
    delete_tree_element(&tree->tree_root);
    free(tree);
}