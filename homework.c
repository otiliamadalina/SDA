#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linear_regression.h"

#define BUFFER_SIZE 10
#define MONTHS_PER_YEAR 12

struct date {
    unsigned int day;
    unsigned int month;
    unsigned int year;
};

typedef struct date Date;

typedef struct product {
    Date date;
    unsigned int id;
    char *name;
    char *category;
    char *subcategory;
    double price;
    unsigned int amount;
    char *country;
    char *city;
} Product;

typedef struct db {
    Product *products;
    unsigned int nr_of_rows;
} Database;

//int get_number_of_lines_from_file(FILE *file) {
//    char buffer[BUFFER_SIZE];
//    int lines = 0;
//    while (fgets(buffer, BUFFER_SIZE, file)) {
//        lines++;
//    }
//    rewind(file);
//    return lines;
//}

int get_number_of_lines_from_file(FILE *fp) {
    int lines = 0;
    int ch;
    while (!feof(fp)) {
        ch = fgetc(fp);
        if (ch == '\n') {
            lines++;
        }
    }
    rewind(fp);
    return lines;
}


Database *alloc_db(const unsigned int nr_of_rows) {

    Database *db = malloc(sizeof(Database));
    db->products = malloc(sizeof(Product) * nr_of_rows);

    db->products->name = NULL;
    db->products->category = NULL;
    db->products->subcategory = NULL;
    db->products->country = NULL;
    db->products->city = NULL;

    db->nr_of_rows = nr_of_rows;

    return db;
}

Product *alloc_product() {
    Product *product = malloc(sizeof(Product));
    product->name = NULL;
    product->category = NULL;
    product->subcategory = NULL;
    product->country = NULL;
    product->city = NULL;
    return product;
}

Date str_to_date(const char *str) {
    Date date;
    sscanf(str, "%d-%d-%d",
           &date.year,
           &date.month,
           &date.day);
    return date;
}

char *tmp_str_to_str(const char *tmp_str) {
    unsigned int tmp_str_size = strlen(tmp_str);
    char *str = malloc(sizeof(char *) * tmp_str_size);
    strcpy(str, tmp_str);
    return str;
}

void read_product_from_file(FILE *file, Product *product) {
    char tmp_date[BUFFER_SIZE];
    char tmp_id[BUFFER_SIZE];
    char tmp_name[BUFFER_SIZE];
    char tmp_category[BUFFER_SIZE];
    char tmp_subcategory[BUFFER_SIZE];
    char tmp_price[BUFFER_SIZE];
    char tmp_amount[BUFFER_SIZE];
    char tmp_country[BUFFER_SIZE];
    char tmp_city[BUFFER_SIZE];
    fscanf(file, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,\n]",
           tmp_date,
           tmp_id,
           tmp_name,
           tmp_category,
           tmp_subcategory,
           tmp_price,
           tmp_amount,
           tmp_country,
           tmp_city);

    product->date = str_to_date(tmp_date);
    product->id = atoi(tmp_id);
    product->name = tmp_str_to_str(tmp_name);
    product->category = tmp_str_to_str(tmp_category);
    product->subcategory = tmp_str_to_str(tmp_subcategory);
    product->price = atof(tmp_price);
    product->amount = atoi(tmp_amount);
    product->country = tmp_str_to_str(tmp_country);
    product->city = tmp_str_to_str(tmp_city);
}


Database *read_db_from_file(const char *file_name) {

    FILE *file = fopen("db.txt", "r");
    if (file == NULL) {
        return 0;
    }

    int nr_of_rows = get_number_of_lines_from_file(file);
    Database *db = alloc_db(nr_of_rows);

    for (int i = 0; i < db->nr_of_rows; i++) {
        read_product_from_file(file, &db->products[i]);
    }
    fclose(file);
    return db;
}

void print_db(const Database *db, const unsigned int *limit) {
    unsigned int nr_of_rows = limit != NULL ? *limit : db->nr_of_rows;
    printf("\tData\tID\tName\tCategory\tSubcat\tPrice\tAmount\n");

    for (int i = 0; i < nr_of_rows; i++) {
        printf("|%d-%d-%d\t|\t%d\t|\t%s\t|\t%s\t|\t%s\t|\t%.1lf\t|\t%d\n",
               db->products[i].date.year,
               db->products[i].date.month,
               db->products[i].date.day,
               db->products[i].id,
               db->products[i].name,
               db->products[i].category,
               db->products[i].subcategory,
               db->products[i].price,
               db->products[i].amount
                //db->products[i].country,
                //db->products[i].city
        );
    }
}

void free_database(Database **db) {
    for (int i = 0; i < (*db)->nr_of_rows; i++) {
        free((*db)->products[i].name);
        free((*db)->products[i].category);
        free((*db)->products[i].country);
        free((*db)->products[i].city);
        free((*db)->products[i].subcategory);
    }
    free((*db)->products);
    free(*db);
    *db = NULL;
}

void count_revenue_per_month_of_year(const Database *db, int year) {
    double revenue[12] = {0};
    for (int i = 0; i < db->nr_of_rows; i++) {
        if (db->products[i].date.year == year) {
            revenue[db->products[i].date.month - 1] += (db->products[i].price * db->products[i].amount);
        }
    }
    printf("For %d we have:\n", year);
    for (int i = 0; i < 12; i++) {
        printf("For month nr. %d: %.2lf\n", i, revenue[i]);
    }

}

typedef struct {
    char name[BUFFER_SIZE];
    double revenue;
} product_rev;

int search_product_name_in_array(const product_rev *products, const char *name, int size) {
    for (int i = 0; i < size; i++) {
        if (strcmp(products[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

int cmp_products_revenue(const void *a, const void *b)   //ex 1
{
    return (int) ((*(product_rev *) b).revenue - (*(product_rev *) a).revenue);
}

void print_top_5_products(const Database *db)   //ex 2
{
    product_rev *products = malloc(0);
    int array_size = 0;
    for (int i = 0; i < db->nr_of_rows; i++) {
        int position = search_product_name_in_array(products, db->products[i].name, array_size);
        if (position == -1) {
            realloc(products, sizeof(product_rev) * (array_size + 1));
            strcpy(products[array_size].name, db->products[i].name);
            products[array_size].revenue = db->products[i].price * db->products[i].amount;
            array_size++;
        } else {
            products[position].revenue += db->products[i].price * db->products[i].amount;
        }
    }
    qsort(products, array_size, sizeof(product_rev), cmp_products_revenue);
    printf("Top 5 products by revenue:\n");
    for (int i = 0; i < 5; i++) {
        printf("%s: %.2lf\n", products[i].name, products[i].revenue);
    }
}

typedef struct {
    char category[BUFFER_SIZE];
    unsigned int revenue;
} category_rev;

int search_category_in_array(const category_rev *categories, const char *category, int size) {
    for (int i = 0; i < size; i++) {
        if (strcmp(categories[i].category, category) == 0) {
            return i;
        }
    }
    return -1;
}

void q3(const Database *db) {

    category_rev *categories = malloc(0);
    int array_size = 0;
    for (int i = 0; i < db->nr_of_rows; i++) {
        int position = search_category_in_array(categories, db->products[i].category, array_size);
        if (position == -1) {
            realloc(categories, sizeof(category_rev) * (array_size + 1));
            strcpy(categories[array_size].category, db->products[i].category);
            categories[array_size].revenue = db->products[i].amount;
            array_size++;
        } else {
            categories[position].revenue += db->products[i].amount;
        }
    }

    for (int i = 0; i < array_size; i++) {
        printf("%s: %d\n", categories[i].category, categories[i].revenue);
    }
}

typedef struct {
    char *city_name;
    double revenue;
} city_rev;

typedef struct {
    char *country_name;
    int nr_of_cities;
    city_rev *cities;
} country_rev;

int search_country_in_array(const country_rev *countries, const char *country_name, int size) {
    for (int i = 0; i < size; i++) {
        if (strcmp(countries[i].country_name, country_name) == 0) {
            return i;
        }
    }
    return -1;
}

int search_city_in_array(const city_rev *cities, const char *city_name, int size) {
    for (int i = 0; i < size; i++) {
        if (strcmp(cities[i].city_name, city_name) == 0) {
            return i;
        }
    }
    return -1;
}

int cmp_cities_revenue(const void *a, const void *b) {
    return (int) ((*(city_rev *) b).revenue - (*(city_rev *) a).revenue);
}

void q4(const Database *db) {
    country_rev *countries = malloc(sizeof(country_rev) * 10000);
    int nr_of_countries = 0;
    for (int i = 0; i < db->nr_of_rows; i++) {
        int country_position = search_country_in_array(countries, db->products[i].country, nr_of_countries);
        if (country_position == -1) {
            countries[nr_of_countries].country_name = tmp_str_to_str(db->products[i].country);
            countries[nr_of_countries].cities = malloc(sizeof(city_rev) * 10000);
            countries[nr_of_countries].nr_of_cities = 0;
            country_position = nr_of_countries;
            nr_of_countries++;
        }

        int city_position = search_city_in_array(countries[country_position].cities,
                                                 db->products[i].city,
                                                 countries[country_position].nr_of_cities);

        if (city_position == -1) {
            int last_city = countries[country_position].nr_of_cities;
            countries[country_position].cities[last_city].city_name = tmp_str_to_str(db->products[i].city);
            countries[country_position].cities[last_city].revenue = 0;
            city_position = last_city;
            countries[country_position].nr_of_cities++;

        }

        countries[country_position].cities[city_position].revenue += db->products[i].price * db->products[i].amount;

    }

    for (int i = 0; i < nr_of_countries; i++) {
        qsort(countries[i].cities, countries[i].nr_of_cities, sizeof(city_rev), cmp_cities_revenue);
    }

    int top_number = 1;
    for (int i = 0; i < nr_of_countries; i++) {
        printf("%s:\n", countries[i].country_name);
        if (countries[i].nr_of_cities >= top_number) {
            for (int j = 0; j < top_number; j++) {
                printf("\t%s: %.2f\n", countries[i].cities[j].city_name, countries[i].cities[j].revenue);
            }
        }
    }

    for (int i = 0; i < nr_of_countries; i++) {
        for (int j = 0; j < countries[i].nr_of_cities; j++) {
            free(countries[i].cities[j].city_name);
        }
        free(countries[i].cities);
        free(countries[i].country_name);
    }
    free(countries);

}

void q5(const Database *db, int year, const char* subcategory) {
    int next_prediction = 13;
    double months[MONTHS_PER_YEAR] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
    double revenue[MONTHS_PER_YEAR] = {0};
    for (int i = 0; i < db->nr_of_rows; i++) {
        if ((db->products[i].date.year == year) && (strcmp(db->products[i].subcategory, subcategory) == 0))
        {
            revenue[db->products[i].date.month - 1] += (db->products[i].price * db->products[i].amount);
        }
    }
    printf("For %d and subcategory: %s we have:\n", year, subcategory);
    for (int i = 0; i < 12; i++) {
        printf("For month nr. %d: %.2lf\n", i, revenue[i]);
    }

    double next_revenue_prediction = predict_next_value(months, revenue, MONTHS_PER_YEAR, next_prediction);
    printf("Next prediction for %d: %.2lf\n", next_prediction, next_revenue_prediction);
}


int main() {
    Database *db = read_db_from_file("db.txt");
    //unsigned int limit = 10;
    //print_db(db, &limit);
    //count_revenue_per_month_of_year(db, 2001);
    //print_top_5_products(db);

    //q3(db);
    //q4(db);

    q5(db, 2022, "meeting");

    free_database(&db);

    return 0;
}
