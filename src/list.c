#include "list.h"
#include <string.h>
#include <sys/time.h>

/* Utility functions
 * ================= */
int64_t currentTimeMillis() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    int64_t res = tv.tv_usec;
    /* Convert from micro seconds (10^-6) to milliseconds (10^-3) */
    res /= 1000;
    /* Adds the seconds (10^0) after converting them to milliseconds (10^-3) */
    res += (tv.tv_sec * 1000);
    return res;
}

/* Construction/Destruction
======================== */

struct list* new_list() {
    struct list* lst = (struct list*)malloc(sizeof(struct list));

    if (lst == NULL) {
        return NULL;
    }

    lst->head=NULL;
    return lst;
}

static void free_cells(struct list *lst) {
    struct cell *cur;
    struct cell *tmp;
    // Empty list
    if (lst == NULL) {
        return;
    }
    // Free each cell one by one
    cur = lst->head;
    while (cur != NULL) {
        tmp = cur;
        cur = cur->next;
         //If dynamically allocated!
         free(tmp->fname);
         //free(tmp->lname);
         //free(tmp->zip);
        free(tmp);
    }
    free(cur);
    lst->head = NULL;
}

void free_list(struct list* lst) {
    free_cells(lst);
    free(lst);
}


/* Printing
======== */

void print_cell(struct cell* c) {
    /*
     * Print the content of a cell as [fname, lname, zip]
     */
    if (c == NULL) {
        return;
    }
    printf("[%s, %s, %s]", c->fname, c->lname, c->zip);
}

void print_list(struct list *lst) {
    /*
     * Print the content of a list and its cells
     */
    struct cell *cur;
    if (lst == NULL) {
        return;
    }
    cur = lst->head;
    printf("{\n");
    while (cur != NULL) {
        print_cell(cur);
        printf(",\n");
        cur = cur->next;
    }
    printf("}\n");
}

/* Cell addition
============= */

struct cell* make_cell(char* fname, char* lname, char* zip) {
    /*
     * Creates a cell from the given values
     */
    struct cell* c = (struct cell*)malloc(sizeof(struct cell));

    if (c == NULL) {
        return NULL;
    }

    c->fname = fname;
    c->lname = lname;
    c->zip = zip;
    c->next = NULL;
    return c;
}

void push(struct list *lst, struct cell* c) {
    /*
     * //DEPRECATED//
     * Append a cell to the list
     */
    if (lst == NULL) {
        return;
    }
    c->next = lst->head;
    lst->head = c;
}

void pop(struct list* lst, struct cell* out) {
    /*
     * Pop the head of the list in the given out pointer
     */
    struct cell *tmp;
    if (lst == NULL) {
        return;
    }
    tmp = lst->head;
    lst->head = lst->head->next;
    out->fname = tmp->fname;
    out->lname = tmp->lname;
    out->zip = tmp->zip;
    out->next = NULL;
    free(tmp);
}

/* Read from file and create cells
============== */

struct cell *make_cell_from_line(char *line) {
    /*
     * Make a cell from an input text line
     */
    char *fname, *lname, *zip;

    line = strtok(line, ";");
    char *tmp = (char*)malloc(strlen(line)+1);
    strcpy(tmp, line);
    fname = strtok(tmp, ",");
    lname = strtok(NULL, ",");
    zip = strtok(NULL, ",");

    // Create the cell
    return make_cell(fname, lname, zip);
}

struct list *load_file(char *file_name) {
    /*
     * Loads the contents of a file in a sorted list
     */
    FILE *f;
    char line[100];
    struct cell *c;
    struct list *lst;
    int nb_elems = 0;
    f = fopen(file_name, "r");
    if (f == NULL) {
        printf("/!!/[Log/E]: cannot open file %s", file_name);
        fclose(f);
        return NULL;
    }
    lst = new_list();
    printf("/?/[Log/I]: Loading file...\n");
    int64_t t0 = currentTimeMillis();
    while (fgets(line, 101, f) != NULL) {
        c = make_cell_from_line(line);
        insert(lst, c);
        nb_elems++;
    }
    fclose(f);
    int64_t dt = currentTimeMillis() - t0;
    printf("/?/[Log/I]: loaded %d elements from file %s in %lld millis\n", nb_elems, file_name, dt);
    return lst;
}

/* Sorting list
=========== */

int compare_cells(struct cell *c1, struct cell *c2) {
    /*
     * Compare two cells by their last name
     * if last name is identical, compare by first name
     */
    if (c1 == NULL || c2 == NULL) {
        exit(1);
    }

    int cmp = strcmp(c1->lname, c2->lname);
    if (cmp == 0) {
        cmp = strcmp(c1->fname, c2->fname);
    }
    return cmp;
}

void insert(struct list *lst, struct cell *c) {
    /*
     * Insert a cell in a sorted list
     */
    struct cell *cur, *prev;
    if (lst == NULL || c == NULL) {
        return;
    }
    // Empty list
    if (lst->head == NULL) {
        lst->head = c;
        return;
    }
    // Insert at the beginning
    if (compare_cells(c, lst->head) < 0) {
        c->next = lst->head;
        lst->head = c;
        return;
    }
    // Insert in the middle
    cur = lst->head;
    prev = lst->head;
    while (cur != NULL) {
        if (compare_cells(c, cur) < 0) {
            c->next = cur;
            prev->next = c;
            return;
        }
        prev = cur;
        cur = cur->next;
    }
    // Insert at the end
    prev->next = c;
}
