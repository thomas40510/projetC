#include "llist.h"
#include <sys/time.h>

/* Utility functions
 * ================= */

struct lcell* in_lists(struct llist* lst, char letter) {
/*
     * Return the lcell in lst with letter as first letter
     * Return 0 if not found
     */
    struct lcell* cur = lst->head;
    if (lst == NULL) {
        exit(1);
    }
    while (cur != NULL) {
        if (cur->letter == letter) {
            return cur;
        }
        cur = cur->next;
    }
    return 0;
}

/* Construction/Destruction
======================== */

struct llist* new_llist(){
    struct llist* llst = (struct llist*) malloc(sizeof(struct llist));

    if (llst == NULL){
        return NULL;
    }

    llst->head = NULL;
    return llst;
}


void free_lcell(struct lcell* lc){
    /*
     * Free a lcell
     */
    if (lc == NULL){
        return;
    }
    free_list(lc->start);
    free(lc);
}

void free_llist(struct llist* lst) {
    /*
     * free lcells content and lcells themselves
     * then free the llist
     */
    struct lcell* cur;
    struct lcell* tmp;
    // Empty list
    if (lst == NULL) {
        return;
    }
    // Free each lcell one by one
    cur = lst->head;
    while (cur != NULL) {
        tmp = cur;
        cur = cur->next;
        free_lcell(tmp);
    }
    lst->head = NULL;
    free(lst);
}

/* lcell addition
======================== */

struct lcell* make_lcell(char letter, struct list* start){
    struct lcell* lc = (struct lcell*) malloc(sizeof(struct lcell));

    if (lc == NULL){
        return NULL;
    }

    lc->letter = letter;
    lc->start = start;
    lc->next = NULL;

    return lc;
}

/* Inserting lcells in llist
======================== */

int compare_lcell(struct lcell* lc1, struct lcell* lc2){
    return strcmp(&lc1->letter, &lc2->letter);
}

void linsert(struct llist* lst, struct lcell* lc){
    struct lcell *cur, *prev;
    if (lst == NULL){
        printf("/?/Log[i] : Inserting in empty list");
        return;
    }
    if (lc == NULL){
        printf("/?/Log[i] : Inserting empty cell");
        return;
    }

    //empty llist
    if (lst->head == NULL){
        lst->head = lc;
        return;
    }

    //insert at the beginning
    if (compare_lcell(lc, lst->head) < 0){
        lc->next  = lst->head;
        lst->head = lc;
        return;
    }

    //insert in the middle`
    cur = lst->head;
    prev = lst->head;
    while(cur != NULL){
        if (compare_lcell(lc, cur) < 0){
            lc->next = cur;
            prev->next = lc;
            return;
        }
        prev = cur;
        cur = cur->next;
    }
    //insert at the end
    prev->next = lc;
}

/* Creating llist from sorted list
======================== */

struct llist* make_lists(struct list* lst){
    if (lst == NULL){
        exit(1);
    }
    struct lcell* lc;
    struct llist* llst = new_llist();
    struct cell* cur = lst->head;
    char letter;
    struct list* start = new_list();

    while(cur != NULL){
        if (cur->fname[0] != letter){
            letter = cur->fname[0];
            lc = make_lcell(letter, start);
            linsert(llst, lc);
        }
        push(start, cur);
        cur = cur->next;
    }
    return llst;
}

struct llist* lists_from_file(char* file_name){
    struct llist* llst = new_llist();
    if (file_name == NULL){
        printf("/?/Log[i] : Attempting to read from empty file");
        return NULL;
    }

    FILE *f;
    char line[100];
    struct cell *c;
    int nb_elems = 0;
    f = fopen(file_name, "r");
    if (f == NULL) {
        printf("/!!/[Log/E]: cannot open file %s", file_name);
        fclose(f);
        exit(1);
    }
    printf("/?/[Log/I]: Loading file...\n");
    int64_t t0 = currentTimeMillis();
    while (fgets(line, 101, f) != NULL) {
        struct list *cur = new_list();
        c = make_cell_from_line(line);
        insert(cur, c);
        // letter in lists ?
        if (in_lists(llst, c->lname[0]) == 0){
            char letter = c->lname[0];
            struct lcell* lc = make_lcell(letter, cur);
            linsert(llst, lc);

        } else {
            struct lcell* lc = in_lists(llst, c->lname[0]);
            struct list* lst = lc->start;
            insert(lst, c);
            lc -> start = lst;

        }
        nb_elems++;
    }
    fclose(f);
    int64_t dt = currentTimeMillis() - t0;
    printf("/?/[Log/I]: loaded %d elements from file %s in %lld millis\n", nb_elems, file_name, dt);
    return llst;

}


/* Printing
 * ======== */

void print_lcell(struct lcell* lc){
    if (lc == NULL){
        printf("/?/Log[i] : Printing empty cell");
        return;
    }
    printf("Letter: %c", lc->letter);
    print_list(lc->start);
}

void print_lcells(struct llist* lst){
    if (lst == NULL){
        printf("/?/Log[i] : Printing empty list");
        return;
    }
    struct lcell* cur = lst->head;
    while (cur != NULL){
        print_lcell(cur);
        cur = cur->next;
    }
}

void print_lists(struct llist* lst){
    if (lst == NULL){
        printf("/?/Log[i] : Attempting to print an empty list");
        return;
    }
    struct lcell* cur = lst->head;
    while (cur != NULL){
        print_list(cur->start);
        cur = cur->next;
    }
}
