// Auteur : Adam Zekari - Alexis Miras

#include <stdio.h>
#include <stdlib.h>
#include "../include/graphe.h"
#include "../include/dijkstra.h"

#define INF 1000000000

void dijkstra(Graphe g, int station_depart, SDijkstra* resultat){
    int n = g->nb_stations; 

    //on initialise le tableau pour marquer les stations déja visitées
    int *marque = malloc(n*sizeof(int));
    if (!marque) return;
    
    int i; 
    for (i=0; i<n; i++){ 
        marque[i] = 0;

        //on initialise les résultats
        resultat[i] = malloc(sizeof(struct SSDijkstra));
        resultat[i]->distance = INF; 
        resultat[i]->id_station_precedente   = -1; 

    }

    resultat[station_depart]->distance = 0;

    for (int k=0; k<n; k++){ //boucle for pour chercher une station non visité avec la distance la plus petite possible (algorithme de dijkstra)
        int station_courante = -1;
        int distance_minimale = INF;
        for (i=0; i<n; i++) {
            if (!marque[i] && resultat[i]->distance < distance_minimale) {
                distance_minimale = resultat[i]->distance;
                station_courante = i;
            }
        }
        //si pas de station on arrete et on passe
        if (station_courante == -1) break;


        marque[station_courante] = 1; //on le marque comme station visitée 

        // on parcourt tous les arcs sortants (avec graphe g)
        Arc arc_courant = g->list_adj[station_courante];
        while (arc_courant != NULL) {
            int voisin = arc_courant->destination;
            int distance_totale = resultat[station_courante]->distance + arc_courant->temps;

            if (distance_totale < resultat[voisin]->distance) {
                resultat[voisin]->distance = distance_totale;
                resultat[voisin]->id_station_precedente = station_courante;
            }

            arc_courant = arc_courant->next_destination;
        }
    }
    free(marque);
} 

void afficher_chemin(int depart, int arrivee, SDijkstra *res, Station *stations) {
    (void)depart; // warning

    if (res[arrivee]->distance == INF) {
        printf("Aucun chemin trouvé.\n");
        return;
    }

    printf("Temps minimal : %d\n", res[arrivee]->distance);
    printf("Chemin : ");

    int *chemin = malloc(sizeof(int)*1000);
    int len = 0;

    for (int v = arrivee; v != -1; v = res[v]->id_station_precedente) chemin[len++] = v;

    for (int i = len - 1; i >= 0; i--) {
        printf("%s", stations[chemin[i]]->name);
        if (i > 0) printf(" -> ");
    }
    printf("\n");
    free(chemin);
}
