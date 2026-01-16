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

// affichage du menu
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

// gestion des E/S et du menu
void gestion_menu(int choix, int nb_stations, Station *stations, Graphe graph) {
    char *input = malloc(sizeof(char)*256);
    int idx = -1;
    switch (choix) {
        case 0:
            break;
        case 1:
            printf("Entrez un nom ou un id de station :\n");

            idx = saisie_clavier(input);

            afficher_station(stations[idx]);
            affichage_deg_sortant(graph, idx);
            break;
        case 2:
            printf("Entrez un nom ou un id de station :\n");

            idx = saisie_clavier(input);

            affichage_nb_voisins(stations, graph, idx);
            break;
        case 3:
            printf("Station de départ (nom ou id) :\n");
            int depart = saisie_clavier(input);

            printf("Station d'arrivée (nom ou id) :\n");
            int arrivee = saisie_clavier(input);

            SDijkstra *resultat = malloc(nb_stations * sizeof(SDijkstra));
            if (!resultat) {
                printf("Erreur allocation mémoire\n");
                break;
            }

            dijkstra(graph, depart, resultat);

            afficher_chemin(depart, arrivee, resultat, stations);

            free(resultat);
            break;
        case 4: {
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
            // tri_par_selection(graph->nb_stations, tableau, &comparaisons, &permutations);
            // Nombre de comparaisons : 8001, Nombre de permutations : 119

            // tri_par_insertion(graph->nb_stations, tableau, &comparaisons, &permutations);
            // Nombre de comparaisons : 1838, Nombre de permutations : 1838

            tri_rapide(graph->nb_stations, tableau, &comparaisons, &permutations);
            // Nombre de comparaisons : 305, Nombre de permutations : 432

            affichage_deg_tri(stations, graph, tableau);
            afficher_stats(comparaisons, permutations);

            for (int i = 0; i < graph->nb_stations; i++) free(tableau[i]);
            free(tableau);
            break;
        }
        default:
            // cas non utilisé mais laissé par sécurité
            printf("Choix invalide, entrez une valeur comprise entre 0 et 4\n");
    }
    if (input) free(input);
}
