#include <stdio.h>
#include <stdlib.h>
#include "../include/station.h"
#include "../include/menu.h"
#include "../include/graphe.h"
#include <string.h>


int main(int argc, char *argv[]) {

    if (argc != 2) {
        fprintf(stderr, "Fichier : %s \n", argv[0]);
        return 1;
    }

    int nb_stations = 0;
    Station *stations = init_station(argv[1], &nb_stations);

    Graphe graph = init_graphe(stations, nb_stations);

    // for (int i = 0; i < nb_stations; i++) afficher(stations[i]);;

    int choice = -1;
    while (choice != 0) {
        choice = menu();
        char input[100];
        switch (choice) {
            case 0:
                break;
            case 1:
                printf("Entrez un nom ou un id de station :\n");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = 0; // enlever le '\n'
                Station search = (Station) malloc(sizeof(struct SStation));
                search->id = -1; search->name = NULL;
                int id;
                if (sscanf(input, "%d", &id) == 1) search->id = id;
                else {
                    search->name = (char *) malloc(strlen(input) + 1);
                    strcpy(search->name, input);
                }
                affichage_station(search, stations, nb_stations, graph);
                // free(search->name); // free dans affichage station;
                free(search);
                break;
            case 2:
                printf("Lister voisins station\n");
                break;
            case 3:
                printf("Chemin minimal\n");
                break;
            case 4:
                printf("Stations triées par degré\n");
                break;
            default:
                printf("Choix invalide\n");
        }
    }

    for (int i = 0; i < nb_stations; i++) {
        free(stations[i]->name);
        free(stations[i]);
    }
    free(stations);

    return 0;
}
