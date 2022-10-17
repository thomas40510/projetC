/*
 * File llist.h
 * ------------
 * Author: Thomas Prévost (CSN 2024) [github.com/thomas40510]
 *
 * Liste chaînée de listes chaînées
 */

#include "list.h"

struct llist {
    struct lcell* head;
};

struct lcell {
    char letter;
    struct list* start;
    struct lcell* next;
};

/* Frees the input list and its cells */
void free_llist(struct llist* lst);

/* Frees the input lcell and its list */
void free_lcell(struct lcell* lc);

/* Creates a new llist */
struct llist* new_llist();

/* Creates a new lcell */
struct lcell* make_lcell(char letter, struct list* start);

/* Compares lcells by their letter */
int compare_lcells(struct lcell* lc1, struct lcell* lc2);

/* Inserts a lcell in the llist */
void linsert(struct llist* lst, struct lcell* lc);

/* Splits a list into lists by first letter of lname and adds them to a llist */
struct llist* make_lists(struct list* lst);

/* Creates a llist from content of given file */
struct llist* lists_from_file(char* file_name);

/* Prints a single lcell */
void print_lcell(struct lcell* lc);

/* prints lcells of a llist */
void print_lcells(struct llist* lst);

/* Prints lists of a llist */
void print_lists(struct llist* lst);

