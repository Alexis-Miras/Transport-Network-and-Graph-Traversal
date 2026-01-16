// Auteur : Adam Zekari - Alexis Miras

#ifndef TRI_H
#define TRI_H

#include "graphe.h"

struct SDegreDesStations { //structure pour stocker le couple (id_station, degre)
    int id_station;
    int degre;
};

typedef struct SDegreDesStations* DegreDesStations; 

void calcul_du_degre(Graphe g, DegreDesStations* tableau); //on calcule le degré sortant pour chaque station
void swap_deg(DegreDesStations *, DegreDesStations *, int *);

void tri_par_selection(int nb, DegreDesStations* tableau, int *comparaisons, int *permutations); 
void tri_par_insertion(int nb, DegreDesStations* tableau, int *comparaisons, int *permutations); 
void tri_rapide(int nb, DegreDesStations* tableau, int *comparaisons, int *permutations);
void tri_rapide_rec(DegreDesStations *, int, int, int *, int *);
int partition(DegreDesStations *, int, int, int *, int *);
void afficher_stats(int, int);

#endif