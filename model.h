#ifndef SDA_MODEL_H
#define SDA_MODEL_H

#include <stdbool.h>
#include "utils.h"

typedef struct tree_element TreeElement;

typedef struct person Person;

struct person {
    int person_id;
    int age;
    char* name;
    char* family_name;
};

Person* create_random_person();

Person* create_person(int person_id, int age, const char* name, const char* family_name);

void clear_person(Person* person);

void delete_person(Person** person);

struct tree_element {
    int element_id;
    Person *person;
    TreeElement *left_element;
    TreeElement *right_element;
};

TreeElement *create_tree_element(int element_id, Person* person);

bool is_tree_element_a_leaf(const TreeElement *tree_element);

int calculate_tree_element_height(const TreeElement *tree_element);

void delete_tree_element(TreeElement **element, bool(*compare_function)(int, int));

void clear_tree_element(TreeElement *element);





typedef struct search_tree SearchTree;

struct search_tree {
    TreeElement *tree_root;
    bool is_mirrored;
};

SearchTree *create_tree();

int calculate_tree_element_depth(const SearchTree *tree, const TreeElement *tree_element);

SearchTree *create_tree_with_elements(int nr_of_elements);

TreeElement* _add_element_to_tree(TreeElement* current_tree_element, TreeElement* tree_element_to_insert, bool (*compare_function)(int, int));
TreeElement *add_element_to_tree(SearchTree *tree, TreeElement *tree_element);

void print_tree(const SearchTree *tree);
void pretty_printf_search_tree(SearchTree* tree);
void print_tree_leafs(const SearchTree *tree);

int calculate_tree_depth(const SearchTree *tree);

const TreeElement *find_tree_element(const SearchTree *tree, int element_id);

void clear_tree(SearchTree *tree);

void delete_tree(SearchTree *tree);

void balance_tree(SearchTree* tree);

void mirror_tree(SearchTree* tree);

TreeElement* search_element_int_search_tree(SearchTree* tree,  int element_id);
int count_nr_of_elements_in_search_tree(SearchTree* tree);
bool is_search_tree_balanced(SearchTree* tree);


const TreeElement *_find_tree_element(const TreeElement *current_element, int element_id);
void _print_tree_element_leaf_recursive(const TreeElement *tree_element);
void _print_tree_element_recursive(const TreeElement *tree_element);
int _calculate_tree_element_depth(const TreeElement *tree_element, int element_id);

void print_tree_depth(TreeElement *tree_element);
void print_tree_vsd(TreeElement *tree_element);
void print_tree_svd(TreeElement *tree_element);
void print_tree_sdv(TreeElement *tree_element);


#endif //SDA_MODEL_H
