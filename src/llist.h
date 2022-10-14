#include "list.h"

struct llist {
    struct lcell* head;
};

struct lcell {
    char letter;
    struct list* start;
    struct lcell* next;
};

void free_llist(struct llist* lst);

void free_lcell(struct lcell* lc);

struct llist* new_llist();

struct lcell* make_lcell(char letter, struct list* start);

int compare_lcells(struct lcell* lc1, struct lcell* lc2);

void linsert(struct llist* lst, struct lcell* lc);

struct llist* make_lists(struct list* lst);

struct llist* lists_from_file(char* file_name);

void print_lcell(struct lcell* lc);

void print_lcells(struct llist* lst);

void print_lists(struct llist* lst);

