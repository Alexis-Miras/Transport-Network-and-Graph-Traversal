#include <stdio.h>
#include <stdlib.h>
#include "../include/graphe.h"
#include "../include/dijkstra.h"

void dijkstra(Graphe g, int station_depart, SDijkstra* resultat){
    int n = g->nb_stations; 

    //on initialise le tableau pour marquer les stations déja visitées
    int *marque = malloc(n*sizeof(int)); 
    int i; 
    for (i=0; i<n; i++){ 
        marque[i] = 0;
    }

    for (i=0; i<n; i++){ //on initialise les résultats
        resultat[i] = malloc(sizeof(struct SSDijkstra));
        resultat[i]->distance = -1; 
        resultat[i]->id_station_precedente   = -1; 

    }
    resultat[station_depart]->distance = 0;

    int k; 
    for (k=0; k<n; k++){ //boucle for pour chercher une station non visité avec la distance la plus petite possible (algorithme de dijkstra)
        int station_courante = -1;
        int distance_minimale = -1;
        for (i=0; i<n; i++) {
            if (!marque[i] && resultat[i]->distance != -1 &&
                (distance_minimale == -1 || resultat[i]->distance < distance_minimale)) {
                distance_minimale = resultat[i]->distance;
                station_courante = i;
            }
        }
        if (station_courante == -1) { //si ya pas de station on arrete et on passe
            break;
        }


        marque[station_courante] = 1; //on le marque comme station visitée 

        // on parcourt tous les arcs sortants (avec graphe g)
        Arc arc_courant = g->list_adj[station_courante];
        while (arc_courant != NULL) {
            int voisin = arc_courant->destination;
            int distance_totale = resultat[station_courante]->distance + arc_courant->temps;

            if (resultat[voisin]->distance < 0 || distance_totale < resultat[voisin]->distance) {
                resultat[voisin]->distance = distance_totale;
                resultat[voisin]->id_station_precedente = station_courante;
            }

            arc_courant = arc_courant->next_destination;
        }
    }
    free(marque);
}   