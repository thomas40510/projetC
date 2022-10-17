#include <time.h>

#include "llist.h"

int main(int argc, char *argv[]) {
//    struct list* l;
//    l = new_list();
//    print_list(l);
//
//    struct cell* c ;
//    c = make_cell("Annie", "ERNAUX", "76170");
//
//    push(l, c);
//
//    print_list(l);
//
//    struct cell* c2;
//    c2 = make_cell("Michel", "LAPICHE", "85100");
//    push(l, c2);
//    print_list(l);
//
//    pop(l, c2);
//
//    //free_list(l);
//
//    l = load_file("../data/medium.txt");
//    //print_list(l);
//    free_list(l);

    int disp = 0;
    if (argc > 1 && argv[2] != NULL) {
        if (strcmp(argv[2], "--display") == 0) {
            disp = 1;
        }
    }

    char* filename = argv[1];
    printf("///// Méthode 1 /////\n");
    struct list* l;
    l = load_file(filename);
    if (disp) {
        print_list(l);
    }
    free_list(l);

    printf("\n");

    printf("///// Méthode 2 /////\n");
    struct llist* ll;
    ll = lists_from_file(filename);
    if (disp) {
        print_lists(ll);
    }
    free_llist(ll);
    return 0;
}
