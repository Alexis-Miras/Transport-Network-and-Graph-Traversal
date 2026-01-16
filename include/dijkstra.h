// Auteur : Adam Zekari - Alexis Miras

#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "graphe.h"

struct SSDijkstra { //on fait une structure pour stocker les résultats de Dijkstra
    int distance; //distance minimale (depuis le depart de la sation id sinon -1)
    int id_station_precedente; //prédecesseurs
};

typedef struct SSDijkstra* SDijkstra; 

//on initialise la fonction dijkstra qui va permettre de calculer les chemins
void dijkstra(Graphe g, int station_depart, SDijkstra* resultat);
void afficher_chemin(int, int, SDijkstra *, Station *);

#endif