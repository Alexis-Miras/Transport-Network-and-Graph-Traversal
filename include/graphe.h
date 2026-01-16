// Auteur : Adam Zekari - Alexis Miras

#ifndef GRAPHE_H
#define GRAPHE_H

#include "station.h"

struct SArc {
    int destination; 
    int temps; 
    struct SArc* next_destination;
}; 
typedef struct SArc* Arc;
 
struct SGraphe {
    Station *stations;
    Arc *list_adj; // Arc **list_adj;
    int nb_stations; 
};
typedef struct SGraphe* Graphe;

Graphe init_graphe(Station *stations, int nb_stations); //initialisation du graphe
void graphe_add_arc(Graphe g, int source, int destination, int temps); //On va ajouter un arc dans le graphe
void free_graphe(Graphe g); //On va libérer la mémoire allouée au graphe avec free

void lire_edges(Graphe g, char *file_name);
void affichage_deg_sortant(Graphe, int);
void affichage_nb_voisins(Station *, Graphe, int);

#endif 