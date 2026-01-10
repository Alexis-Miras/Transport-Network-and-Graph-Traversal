#include <stdio.h>
#include <stdlib.h>
#include "../include/station.h"
#include "../include/menu.h"
#include "../include/graphe.h"
#include "../include/hash.h"
#include "../include/hash.h"
#include <string.h>


int main(int argc, char *argv[]) {

    if (argc != 2) {
        fprintf(stderr, "Fichier : %s \n", argv[0]);
        return 1;
    }

    int nb_stations = 0;
    Station *stations = init_station(argv[1], &nb_stations);

    Graphe graph = init_graphe(stations, nb_stations);

    lire_edges(graph, argv[1]);

    // Initialiser la hash map
    init_hash();
    for (int i = 0; i < nb_stations; i++) {
        stations[i]->name[strcspn(stations[i]->name, "\n")] = 0;
        insert_hash(stations[i]->name, i);
    }
    // print_hash_table();

    
    // for (int i = 0; i < nb_stations; i++) afficher(stations[i]);;

    int choix = -1;
    while (choix != 0) {
        choix = menu();
        affichage_menu(choix, nb_stations, stations, graph);
    }

    for (int i = 0; i < nb_stations; i++) {
        free(stations[i]->name);
        free(stations[i]);
    }
    free(stations);

    return 0;
}
