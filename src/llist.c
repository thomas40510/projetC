#include "llist.h"

/* Utility functions
 * ================= */

struct lcell* in_lists(struct llist* lst, char letter) {
    struct lcell* cur = lst->head;
    while (cur != NULL) {
        if (strcmp(cur->letter, letter) == 0) {
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

void free_llist(struct llist* lst){
    struct lcell* cur;
    struct lcell* tmp;
    // Empty list
    if (lst == NULL){
        return;
    }
    // Free each cell one by one
    cur = lst->head;
    while (cur != NULL){
        tmp = cur;
        cur = cur->next;
        free_list(tmp->start);
        free(tmp);
    }
    lst->head = NULL;
}

void free_lcell(struct lcell* lc){
    free_list(lc->start);
    free(lc);
}

/* lcell addition
======================== */

struct lcell* make_lcell(char* letter, struct list* start){
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
    return strcmp(lc1->letter, lc2->letter);
}

void linsert(struct llist* lst, struct lcell* lc){
    struct lcell *cur, *prev;

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
    struct lcell* lc;
    struct llist* llst = new_llist();
    struct cell* cur = lst->head;
    char* letter = (char*) malloc(sizeof(char));
    struct list* start = new_list();

    while(cur != NULL){
        if (cur->fname[0] != letter[0]){
            letter[0] = cur->fname[0];
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
    while (fgets(line, 101, f) != NULL) {
        struct list *cur = new_list();
        c = make_cell_from_line(line);
        printf("/?/[Log/I]: %s\n", line);
        insert(cur, c);
        // letter in lists ?
        if (in_lists(llst, c->lname[0]) == 0){
            printf("/?/[Log/I]: New letter %c\n", c->lname[0]);
            struct lcell* lc = make_lcell(&c->lname[0], cur);
            linsert(llst, lc);

        } else {
            struct lcell* lc = in_lists(llst, c->lname[0]);
            insert(lc->start, c);

        }
        //free_list(cur);
        nb_elems++;
    }
//    free_list(cur);
//    free_list(tmp);
    fclose(f);
    printf("/?/[Log/I]: loaded %d elements from file %s\n", nb_elems, file_name);
    return llst;

}


/* Printing
 * ======== */

void print_lcell(struct lcell* lc){
    printf("Letter: %s", lc->letter);
    print_list(lc->start);
}

void print_lcells(struct llist* lst){
    struct lcell* cur = lst->head;
    while (cur != NULL){
        print_lcell(cur);
        cur = cur->next;
    }
}

void print_lists(struct llist* lst){
    struct lcell* cur = lst->head;
    while (cur != NULL){
        printf("Letter: %s\n", cur->letter);
        print_list(cur->start);
        cur = cur->next;
    }
}
