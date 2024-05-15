#include "model.h"
#include <stdlib.h>
#include <stdio.h>

const char *error_on_print_message = "Error on printing";
const char *error_on_add_message = "Error on adding element";

Person *create_random_person() {

    int person_id = generate_random_number();
    int age = generate_random_number();
    char *name = generate_random_string();
    char *family_name = generate_random_string();

    Person *new_person = create_person(person_id, age, name, family_name);

    free(name);
    free(family_name);
    return new_person;
}

Person *create_person(int person_id, int age, const char *name, const char *family_name) {
    Person *new_person = (Person *) malloc(sizeof(Person));
    new_person->person_id = person_id;
    new_person->age = age;
    new_person->name = malloc(sizeof(char) * strlen(name));
    strcpy(new_person->name, name);
    new_person->family_name = malloc(sizeof(char) * strlen(family_name));
    strcpy(new_person->family_name, family_name);

    return new_person;
}

void clear_person(Person *person) {
    person->age = 0;
    free(person->family_name);
    free(person->name);
    person->family_name = NULL;
    person->name = NULL;
}

void delete_person(Person **person) {
    free(*person);
    *person = NULL;
}

bool compare_tree_element_id_in_mirrored_tree(int left_element_id, int right_element_id) {
    if (left_element_id < right_element_id) {
        return true;
    }
    return false;
}

bool compare_tree_element_id_in_not_mirrored_tree(int left_element_id, int right_element_id) {
    if (left_element_id > right_element_id) {
        return true;
    }
    return false;
}

TreeElement *create_tree_element(int element_id, Person *person) {
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
    delete_tree_element_recursive(&(*element)->left_element);
    delete_tree_element_recursive(&(*element)->right_element);
    delete_person(&((*element)->person));
    free(*element);
    *element = NULL;
}

//TODO: adjust
//void delete_tree_element(TreeElement **element, bool(*compare_function)(int, int)) {
//    if (*element == NULL) {
//        return;
//    }
//    delete_person(&((*element)->person));
//    if(compare_function());
//    delete_tree_element(&(*element)->left_element, compare_function);
//    delete_tree_element(&(*element)->right_element, compare_function);
//    free(*element);
//    *element = NULL;
//}

void clear_tree_element(TreeElement *element) {
    clear_person(element->person);
}

TreeElement *_add_element_to_tree(TreeElement *current_tree_element, TreeElement *tree_element_to_insert,
                                  bool (*compare_function)(int, int)) {
    if (current_tree_element == NULL) return NULL;

    if (compare_function(current_tree_element->element_id, tree_element_to_insert->element_id) == true) {
        if (current_tree_element->left_element == NULL) {
            current_tree_element->left_element = tree_element_to_insert;
        } else {
            _add_element_to_tree(current_tree_element->left_element, tree_element_to_insert, compare_function);
        }
    } else {
        if (current_tree_element->right_element == NULL) {
            current_tree_element->right_element = tree_element_to_insert;
        } else {
            _add_element_to_tree(current_tree_element->right_element, tree_element_to_insert, compare_function);
        }
    }

    return tree_element_to_insert;
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

    if (tree->is_mirrored) {
        return _add_element_to_tree(tree->tree_root, tree_element, compare_tree_element_id_in_mirrored_tree);
    }
    return _add_element_to_tree(tree->tree_root, tree_element, compare_tree_element_id_in_not_mirrored_tree);
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

void _pretty_printf_postorder_recursive(TreeElement* p, int indent)
{
    if(p != NULL) {
        //TODO: chech mirroring
        if(p->left_element) _pretty_printf_postorder_recursive(p->left_element, indent+4);
        if(p->right_element) _pretty_printf_postorder_recursive(p->right_element, indent+4);
        if (indent) {
            //std::cout << std::setw(indent) << ' ';
            for(int i = 0; i < indent; i++) printf(" ");
        }
        //cout<< p->data << "\n ";
        printf("%d\n ", p->element_id);
    }
}

void pretty_printf_search_tree(SearchTree* tree) {
    if(tree == NULL) {
        printf("Search tree is NULL\n");
        return;
    }
    _pretty_printf_postorder_recursive(tree->tree_root, 0);
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

const TreeElement *_find_tree_element_in_not_mirrored_tree(const TreeElement *current_element, int element_id) {
    if (current_element == NULL) return NULL;
    if (current_element->element_id == element_id) {
        return current_element;
    }
    if (element_id < current_element->element_id) {
        const TreeElement *searched_element = _find_tree_element_in_not_mirrored_tree(current_element->left_element,
                                                                                      element_id);
        if (searched_element != NULL) return searched_element;
    }
    return _find_tree_element_in_not_mirrored_tree(current_element->right_element, element_id);
}

const TreeElement *_find_tree_element_in_mirrored_tree(const TreeElement *current_element, int element_id) {
    if (current_element == NULL) return NULL;
    if (current_element->element_id == element_id) {
        return current_element;
    }
    if (element_id > current_element->element_id) {
        const TreeElement *searched_element = _find_tree_element_in_mirrored_tree(current_element->left_element,
                                                                                  element_id);
        if (searched_element != NULL) return searched_element;
    }
    return _find_tree_element_in_mirrored_tree(current_element->right_element, element_id);
}

const TreeElement *find_tree_element(const SearchTree *tree, int element_id) {
    if (tree == NULL) {
        printf("%s: Tree is NULL\n", error_on_print_message);
        return NULL;
    }
    if (tree->is_mirrored) {
        return _find_tree_element_in_mirrored_tree(tree->tree_root, element_id);
    }
    return _find_tree_element_in_not_mirrored_tree(tree->tree_root, element_id);
}

void _clear_tree_element_recursive(TreeElement *element) {
    if (element == NULL) return;
    _clear_tree_element_recursive(element->left_element);
    _clear_tree_element_recursive(element->right_element);
    clear_tree_element(element);
}

void clear_tree(SearchTree *tree) {
    if (tree == NULL) {
        return;
    }
    _clear_tree_element_recursive(tree->tree_root);
    free(tree);
}

void delete_tree(SearchTree *tree) {
    if (tree == NULL) {
        return;
    }
    delete_tree_element_recursive(&tree->tree_root);
    free(tree);
}

TreeElement *
_search_element_int_search_tree(TreeElement *tree_element, int element_id, bool (*compare_function)(int, int)) {
    if (tree_element == NULL) return NULL;

    if (tree_element->element_id == element_id) {
        return tree_element;
    }

    if (compare_function(tree_element->element_id, element_id) == true) {
        return _search_element_int_search_tree(tree_element->left_element, element_id, compare_function);
    }
    return _search_element_int_search_tree(tree_element->right_element, element_id, compare_function);

}

TreeElement *search_element_int_search_tree(SearchTree *tree, int element_id) {
    if (tree == NULL) {
        printf("Search tree is NULL!\n");
        return NULL;
    }
    if (tree->is_mirrored) {
        _search_element_int_search_tree(tree->tree_root, element_id, compare_tree_element_id_in_mirrored_tree);
    } else {
        _search_element_int_search_tree(tree->tree_root, element_id, compare_tree_element_id_in_not_mirrored_tree);
    }
}

void _mirror_tree(TreeElement *tree_element) {
    if (tree_element == NULL) return;

    _mirror_tree(tree_element->left_element);
    _mirror_tree(tree_element->right_element);

    TreeElement *temp = tree_element->left_element;
    tree_element->left_element = tree_element->right_element;
    tree_element->right_element = temp;
}

void mirror_tree(SearchTree *tree) {
    _mirror_tree(tree->tree_root);
    if (tree->is_mirrored) {
        tree->is_mirrored = false;
    } else {
        tree->is_mirrored = true;
    }
}

int _count_nr_of_elements_in_search_tree(TreeElement *tree) {
    if (tree == NULL) return 0;

    return _count_nr_of_elements_in_search_tree(tree->right_element) +
           _count_nr_of_elements_in_search_tree(tree->left_element) + 1;
}

int count_nr_of_elements_in_search_tree(SearchTree *tree) {
    if (tree == NULL) {
        printf("Search tree is NULL!\n");
        return 0;
    }
    return _count_nr_of_elements_in_search_tree(tree->tree_root);
}

bool is_search_tree_balanced(SearchTree *tree) {
    if (tree == NULL) {
        printf("Search tree is NULL!\n");
        return false;
    }

    int left_element_height = calculate_tree_element_height(tree->tree_root->left_element);
    int right_element_height = calculate_tree_element_height(tree->tree_root->right_element);
    int abs_value = abs(left_element_height - right_element_height);
    if (abs_value > 1) {
        return false;
    }
    return true;
}

int
_insert_tree_elements_in_array_svd(TreeElement *tree_element, TreeElement **tree_element_array, int current_position) {
    if (tree_element == NULL) return 0;
    int result_position = _insert_tree_elements_in_array_svd(tree_element->left_element, tree_element_array,
                                                             current_position + 1);
    tree_element_array[result_position] = tree_element;
    result_position++;
    return _insert_tree_elements_in_array_svd(tree_element->right_element, tree_element_array, result_position);
}

TreeElement *_balance_tree_from_array(TreeElement **tree_element_array, int start, int end) {
    if (start > end) return NULL;

    int mid = ((start + end) / 2);

    TreeElement *new_root = tree_element_array[mid];

    new_root->left_element = _balance_tree_from_array(tree_element_array, start, mid - 1);
    new_root->right_element = _balance_tree_from_array(tree_element_array, mid + 1, end);

    return new_root;
}

void _balance_tree(SearchTree *tree) {
    int nr_of_tree_elements = count_nr_of_elements_in_search_tree(tree);
    TreeElement *tree_element_array[nr_of_tree_elements];
    _insert_tree_elements_in_array_svd(tree->tree_root, tree_element_array, 0);
    tree->tree_root = _balance_tree_from_array(tree_element_array, 0, nr_of_tree_elements - 1);
}

void balance_tree(SearchTree *tree) {
    if (tree == NULL) {
        printf("Search tree is NULL!\n");
        return;
    }

    if (is_search_tree_balanced(tree) == true) {
        printf("Search tree is already balanced!\n");
        return;
    }
    _balance_tree(tree);
}

void print_tree_depth(TreeElement *tree_element) {
    if (tree_element == NULL) return;

    printf("%d", tree_element->element_id);
    print_tree_depth(tree_element->left_element);
    print_tree_depth(tree_element->right_element);
}

void print_tree_vsd(TreeElement *tree_element) { // preordine
    if (tree_element == NULL) return;

    printf("%d", tree_element->element_id);
    print_tree_depth(tree_element->left_element);
    print_tree_depth(tree_element->right_element);
}

void print_tree_svd(TreeElement *tree_element) { // inorder
    if (tree_element == NULL) return;

    print_tree_depth(tree_element->left_element);
    printf("%d", tree_element->element_id);
    print_tree_depth(tree_element->right_element);

}

void print_tree_sdv(TreeElement *tree_element) { // postordine
    if (tree_element == NULL) return;

    print_tree_depth(tree_element->left_element);
    print_tree_depth(tree_element->right_element);
    printf("%d", tree_element->element_id);

}
