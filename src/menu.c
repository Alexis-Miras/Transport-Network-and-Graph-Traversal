// Auteur : Adam Zekari - Alexis Miras

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/station.h"
#include "../include/graphe.h"
#include "../include/hash.h"
#include "../include/tri.h"
#include "../include/dijkstra.h"
#include "../include/menu.h"

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

// gestion de la saisi clavier, transformation de char * en int (nom --> id)
int saisie_clavier(char *input) {
    int idx = -1, id;
    fgets(input, 256, stdin);
    input[strcspn(input, "\n")] = 0; // retirer \n et \r

    if (sscanf(input, "%i", &id) == 1) {
        idx = id;
    } else {
        idx = search_hash(input);
    }

    if (idx == -1) {
        printf("Nom ou ID invalide\n");
        return -1;
    }
    return idx;
}

void affichage_menu(int choix, int nb_stations, Station *stations, Graphe graph) {
    char *input = malloc(sizeof(char)*256);
    int idx = -1;
    switch (choix) {
        case 0:
            break;
        case 1:
            printf("Entrez un nom ou un id de station :\n");

            idx = saisie_clavier(input);

            affichage_station(stations[idx], graph, idx);
            break;
        case 2:
            printf("Lister voisins station\n");
            printf("Entrez un nom ou un id de station :\n");

            idx = saisie_clavier(input);

            if (idx != -1) {
                Arc a = graph->list_adj[idx];
                printf("Voisins de %s :\n", stations[idx]->name);
                while (a) {
                    printf("  %i - %s (temps: %i)\n", a->destination,
                    stations[a->destination]->name, a->temps);
                a = a->next_destination;
                }
            }
            break;
        case 3:
            printf("Chemin minimal\n");
            int depart, arrivee;
            SDijkstra *resultat = malloc(nb_stations * sizeof(SDijkstra));
            if (!resultat) {
                printf("Erreur allocation mémoire\n");
                break;
            }

            printf("Station de départ (nom ou id) :\n");
            depart = saisie_clavier(input);

            printf("Station d'arrivée (nom ou id) :\n");
            arrivee = saisie_clavier(input);

            dijkstra(graph, depart, resultat);

            afficher_chemin(depart, arrivee, resultat, stations);

            free(resultat);
            break;
        case 4: 
            printf("Stations triées par degré\n");
            DegreDesStations *tableau = malloc(graph->nb_stations * sizeof(DegreDesStations));
            if (!tableau) {
                printf("Erreur allocation mémoire\n");
                break;
            }

            for (int i = 0; i < graph->nb_stations; i++) {
                tableau[i] = malloc(sizeof(struct SDegreDesStations));
                if (!tableau[i]) {
                    printf("Erreur allocation mémoire\n");
                    break;
                }
            }

            calcul_du_degre(graph, tableau);


            int comparaisons = 0, permutations = 0;
            tri_par_selection(graph->nb_stations, tableau, &comparaisons, &permutations);

            for (int i = 0; i < graph->nb_stations; i++) {
                int idx = tableau[i]->id_station;
                if (stations[idx]) printf("%s (degré = %i)\n", 
                                    stations[idx]->name, tableau[i]->degre);
            }

            afficher_stats(comparaisons, permutations);

            for (int i = 0; i < graph->nb_stations; i++) free(tableau[i]);
            free(tableau);
            break;
        default:
            // cas non utilisé mais laissé par sécurité
            printf("Choix invalide, entrez une valeur comprise entre 0 et 4\n");
    }
    if (input) free(input);
}

void affichage_station(Station station, Graphe g, int idx) {
    if (!station) return;

    afficher(station);

    int deg = 0;
    Arc arc = g->list_adj[idx];
    while (arc != NULL) {
        deg++;
        arc = arc->next_destination;
    }
    printf("Nombre de voisins sortants : %i \n", deg);
}
