#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/station.h"
#include "../include/graphe.h"

int menu() {
    int choice;

    while (1) {
        printf(
            "===== MENU RESEAU DE TRANSPORT ===== \n"
            "1 - Afficher les informations d'une station \n"
            "2 - Lister les voisins d'une station \n"
            "3 - Calculer un chemin minimal \n"
            "4 - Afficher les stations triées par degré \n"
            "0 - Quitter \n"
            "Votre choix : "
        );

        if (scanf("%i", &choice) != 1) {
            while (getchar() != '\n');
            continue;
        }

        while (getchar() != '\n');

        if (choice < 0 || choice > 4) {
            printf("Erreur : choix entre 0 et 4 uniquement.\n");
            continue;
        }

        // printf("%i", choice);

        return choice;
    }
}

void affichage_station(Station station, Station* stations, int nb_station, Graphe g) {
    int find = 0;
    if (station->id != -1) {
        for (int i = 0; i < nb_station; i++) {
            if (station->id == stations[i]->id) {
                station->name = malloc(strlen(stations[i]->name) + 1);
                strcpy(station->name, stations[i]->name);
                station->name = stations[i]->name;
                find = 1;
                break;
            }
        }
    } else if (station->name != NULL) {
        for (int i = 0; i < nb_station; i++) {
            if (!strcmp(station->name, stations[i]->name)) {
                station->id = stations[i]->id;
                find = 1;
                break;
            }
        }
    }
    if (!find) printf("Nom ou ID invalide \n");
    else {
        afficher(station);
        int deg = 0;
        Arc arc = g->list_adj[station->id];
        while (arc != NULL) {
            deg++;
            arc = arc->next_destination;
        }
        printf("Nombre de voisins sortants : %i \n", deg);
    }
    if (station->name != NULL) free(station->name);
    
}