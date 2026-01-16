// Auteur : Adam Zekari - Alexis Miras

#include <stdio.h>
#include <stdlib.h>
#include "../include/station.h"
#include "../include/menu.h"
#include "../include/graphe.h"
#include "../include/hash.h"
#include <string.h>


int main(int argc, char *argv[]) {

    if (argc != 2) {
        printf("Erreur : impossible d'ouvrir le fichier : %s \n", argv[0]);
        return -1;
    }

    // Initialisation de la table de hachage
    init_hash();

    int nb_stations = 0;
    // initialisation du tableau de station
    Station *stations = init_station(argv[1], &nb_stations);

    // initialisation du graphe
    Graphe graph = init_graphe(stations, nb_stations);

    lire_edges(graph, argv[1]);
    
    // print_hash();

    // Boucle infini sur le menu jusqu'au choix 0 (quitter)
    int choix = -1;
    while (choix != 0) {
        choix = menu();
        gestion_menu(choix, nb_stations, stations, graph);
    }

    // liberation de memoire du tableau de station
    for (int i = 0; i < nb_stations; i++) {
        if (stations[i]) {
            if (stations[i]->name) free(stations[i]->name);
            free(stations[i]);
        }
    }
    free(stations);

    return 0;
}
