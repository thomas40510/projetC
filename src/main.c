#include <time.h>

#include "llist.h"

int main(int argc, char *argv[]) {
    /*
     * ===============================
     * Système d'annuaire alphabétique
     * ===============================
     * Projet C 2022
     *
     * Auteur: Thomas Prévost (CSN 2024) [github.com/thomas40510]
     *
     * Modules:
     * - list.c > création d'un annuaire par liste chaînée
     * - llist.c > création d'un annuaire par liste chaînée de listes chaînées (structure optimisée)
     */

    /* Exemples d'usages (décommenter pour tester) */
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

    /*
     * Partie principale : fonctionnement en ligne de commande
     */

    int disp = 0;
    if (argc > 1 && argv[2] != NULL) {
        /* Présence d'un 2nd argument */
        if (strcmp(argv[2], "--display") == 0) { /* Affichage des données */
            disp = 1;
        }
    }

    char* filename = argv[1];
    printf("///// Méthode 1 /////\n"); // méthode non optimisée
    struct list* l;
    l = load_file(filename);
    if (disp) {
        print_list(l);
    }
    free_list(l);

    printf("\n");

    printf("///// Méthode 2 /////\n"); // méthode optimisée
    struct llist* ll;
    ll = lists_from_file(filename);
    if (disp) {
        print_lists(ll);
    }
    free_llist(ll);
    return 0;
}
