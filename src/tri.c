#include <stdio.h>
#include "../include/graphe.h"
#include "../include/tri.h"
#include <stdlib.h>

//on calcule le degré sortant pour chaque station
void calcul_du_degre(Graphe g, DegreDesStations* tableau){  
    for (int i=0; i<g->nb_stations; i++){
        // tableau = malloc(sizeof(struct SDegreDesStations));
        tableau[i]->id_station = i; 

        int deg = 0; 
        Arc arc = g->list_adj[i]; 
        while (arc){ //on parcourt la liste d'adjacence
            deg++; 
            arc = arc->next_destination;
        }
        tableau[i]->degre = deg; //pour stocker
    }
} 

void swap_deg(DegreDesStations *a, DegreDesStations *b, int *permutations) {
    DegreDesStations c = *a;
    *a = *b;
    *b = c;
    (*permutations)++;
}


void tri_par_selection(int nb, DegreDesStations* tableau, int *comparaisons, int *permutations){
    (void)comparaisons; // warning

    for (int i = 0; i < nb-1; i++) {
        int min = i;
        for (int j = i + 1; j < nb; j++) {
            if (tableau[j]->degre < tableau[min]->degre) {
                min = j;
            }
            if (min != i) swap_deg(&tableau[i], &tableau[min], permutations);
        }
    }
}

void tri_par_insertion(int nb, DegreDesStations* tableau, int *comparaisons, int *permutations){
    for (int i = 1; i < nb-1; i++) {
        DegreDesStations clef = tableau[i];
        int j = i - 1;
        while (j >= 0 && tableau[j] > clef) { 
            (*comparaisons)++;
            tableau[j+1] = tableau[j];
            (*permutations)++;
            j--;
        }
        tableau[j + 1] = clef;
    }
}

int partition(DegreDesStations *tableau, int l, int r, int *comparaisons, int *permutations) {
    int pivot = tableau[r]->degre;
    int idx = l;
    for (int i = l; i < r; i++) {
        if (tableau[i]->degre < pivot) {
            (*comparaisons)++;
            swap_deg(&tableau[i], &tableau[idx], permutations);
            idx++;
        }
    }
    swap_deg(&tableau[idx], &tableau[r], permutations);
    return idx;
}

void tri_rapide_rec(DegreDesStations *tableau, int l, int r, int *comparaisons, int *permutations) {
    int pivot;
    if (l <= r) {
        pivot = partition(tableau, l, r, comparaisons, permutations);
        tri_rapide_rec(tableau, l, pivot-1, comparaisons, permutations);
        tri_rapide_rec(tableau, pivot+1, r, comparaisons, permutations);
    }
}

void tri_rapide(int nb, DegreDesStations* tableau, int *comparaisons, int *permutations){
    if (!tableau || nb <= 1) return;
    tri_rapide_rec(tableau, 0, nb - 1, comparaisons, permutations);
}

void afficher_stats(int comparaisons, int permutations) {
    printf("Nombre de comparaisons : %i\n", comparaisons);
    printf("Nombre de permutations : %i\n", permutations);
}
