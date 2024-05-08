#include "model.h"
#include <stdlib.h>
#include <stdio.h>

const char *error_on_print_message = "Error on printing";
const char *error_on_add_message = "Error on adding element";

Person* create_random_person() {
    int person_id = generate_random_number();
    int age = generate_random_number();
    char *name = generate_random_string();
    char *family_name = generate_random_string();

    Person* new_person = create_person(person_id, age, name, family_name);
    free(name);
    free(family_name);
    return new_person;
}

Person* create_person(int person_id, int age, const char* name, const char* family_name) {
    Person *new_person = (Person*)malloc(sizeof(Person));
    new_person->person_id = person_id;
    new_person->age = age;
    strcpy(new_person->name, name);
    strcpy(new_person->family_name, family_name);

    return new_person;
}

void clear_person(Person* person) {
    person->age = 0;
    free(person->family_name);
    free(person->name);
    person->family_name = NULL;
    person->name = NULL;
}

void delete_person(Person** person) {
    free(*person);
    *person = NULL;
}

bool compare_tree_element_id_in_mirrored_tree(const TreeElement *left_tree_element, const TreeElement *right_tree_element) {
    if(left_tree_element->element_id < right_tree_element->element_id) {
        return true;
    }
    return false;
}

bool compare_tree_element_id_in_not_mirrored_tree(const TreeElement *left_tree_element, const TreeElement *right_tree_element) {
    if(left_tree_element->element_id < right_tree_element->element_id) {
        return true;
    }
    return false;
}

TreeElement *create_tree_element(int element_id, Person* person) {
    TreeElement *new_tree_element = (TreeElement *) malloc(sizeof(TreeElement));
    new_tree_element->element_id = element_id;
    new_tree_element->left_element = NULL;
    new_tree_element->right_element = NULL;
    new_tree_element->person = person;
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

int calculate_tree_element_depth(const SearchTree *tree, const TreeElement *tree_element) {
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
    } else {
        return right_side + 1;
    }

    return -1;
}

void delete_tree_element_recursive(TreeElement **element) {
    if (*element == NULL) {
        return;
    }
    delete_person(&((*element)->person));
    delete_tree_element_recursive(&(*element)->left_element);
    delete_tree_element_recursive(&(*element)->right_element);
    free(*element);
    *element = NULL;
}

//TODO: adjust
void delete_tree_element(TreeElement **element, bool(*compare_function)(int, int)) {
    if (*element == NULL) {
        return;
    }
    delete_person(&((*element)->person));
    if(compare_function());
    delete_tree_element(&(*element)->left_element, compare_function);
    delete_tree_element(&(*element)->right_element, compare_function);
    free(*element);
    *element = NULL;
}

void clear_tree_element(TreeElement *element) {
    clear_person(element->person);
}

TreeElement *_add_element_to_not_mirrored_tree(TreeElement **current_element, TreeElement *tree_element) {
    if ((*current_element)->left_element == NULL) {
        (*current_element)->left_element = tree_element;
        return (*current_element)->left_element;
    }
    if ((*current_element)->right_element == NULL) {
        (*current_element)->right_element = tree_element;
        return (*current_element)->right_element;
    }

    if(tree_element->element_id < (*current_element)->element_id) {
        return _add_element_to_tree_to_left(&((*current_element)->left_element), tree_element);
    }

    return _add_element_to_tree_to_left(&((*current_element)->right_element), tree_element);
}

TreeElement *_add_element_to_mirrored_tree(TreeElement **current_element, TreeElement *tree_element) {
    if ((*current_element)->left_element == NULL) {
        (*current_element)->left_element = tree_element;
        return (*current_element)->left_element;
    }
    if ((*current_element)->right_element == NULL) {
        (*current_element)->right_element = tree_element;
        return (*current_element)->right_element;
    }

    if(tree_element->element_id > (*current_element)->element_id) {
        return _add_element_to_tree_to_left(&((*current_element)->left_element), tree_element);
    }

    return _add_element_to_tree_to_left(&((*current_element)->right_element), tree_element);
}

TreeElement *add_element_to_tree(SearchTree *tree, TreeElement *tree_element) {
    if (tree == NULL || tree_element == NULL) {
        printf("%s: Tree or tree_element is NULL\n", error_on_add_message);
        return NULL;
    }
    if (tree->tree_root == NULL) {
        tree->tree_root = tree_element;
        return tree_element;
    }
    if(tree->is_mirrored) {
        return _add_element_to_mirrored_tree(&(tree->tree_root), tree_element);
    }
    return _add_element_to_not_mirrored_tree(&(tree->tree_root), tree_element);
}

SearchTree *create_tree() {
    SearchTree *search_tree = (SearchTree *) malloc(sizeof(SearchTree));
    search_tree->tree_root = NULL;
    search_tree->is_mirrored = false;
    return search_tree;
}

SearchTree *create_tree_with_elements(int nr_of_elements) {
    SearchTree *search_tree = create_tree();

    for (int i = 0; i < nr_of_elements; i++) {
        TreeElement *new_tree_element = create_tree_element(i, create_random_person());
        add_element_to_tree(search_tree, new_tree_element);
    }

    return search_tree;
}

void _print_tree_element_recursive(const TreeElement *tree_element) {
    if (tree_element == NULL) return;
    printf("%d\n", tree_element->element_id);
    _print_tree_element_recursive(tree_element->left_element);
    _print_tree_element_recursive(tree_element->right_element);
}

void print_tree(const SearchTree *tree) {
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

void print_tree_leafs(const SearchTree *tree) {
    if (tree == NULL) {
        printf("%s: Tree is NULL\n", error_on_print_message);
        return;
    }
    if (tree->tree_root == NULL) {
        printf("%s: Tree root is NULL", error_on_print_message);
    }
    _print_tree_element_leaf_recursive(tree->tree_root);
}

int calculate_tree_depth(const SearchTree *tree) {
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

const TreeElement *_find_tree_element_in_not_mirrored_tree(const TreeElement* current_element, int element_id) {
    if(current_element == NULL) return NULL;
    if(current_element->element_id == element_id) {
        return current_element;
    }
    if(element_id < current_element->element_id) {
        const TreeElement* searched_element = _find_tree_element_in_not_mirrored_tree(current_element->left_element, element_id);
        if(searched_element != NULL) return searched_element;
    }
    return _find_tree_element_in_not_mirrored_tree(current_element->right_element, element_id);
}

const TreeElement *_find_tree_element_in_mirrored_tree(const TreeElement* current_element, int element_id) {
    if(current_element == NULL) return NULL;
    if(current_element->element_id == element_id) {
        return current_element;
    }
    if(element_id > current_element->element_id) {
        const TreeElement* searched_element = _find_tree_element_in_mirrored_tree(current_element->left_element, element_id);
        if(searched_element != NULL) return searched_element;
    }
    return _find_tree_element_in_mirrored_tree(current_element->right_element, element_id);
}

const TreeElement *find_tree_element(const SearchTree *tree, int element_id) {
    if (tree == NULL) {
        printf("%s: Tree is NULL\n", error_on_print_message);
        return NULL;
    }
    if(tree->is_mirrored) {
        return _find_tree_element_in_mirrored_tree(tree->tree_root, element_id);
    }
    return _find_tree_element_in_not_mirrored_tree(tree->tree_root, element_id);
}

//TODO: adjust
void clear_tree(SearchTree *tree) {
    if (tree == NULL) {
        return;
    }
    delete_tree_element(&tree->tree_root);
    free(tree);
}

void delete_tree(SearchTree *tree) {
    if (tree == NULL) {
        return;
    }
    delete_tree_element_recursive(&tree->tree_root);
    free(tree);
}