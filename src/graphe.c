#include <stdio.h> 
#include <stdlib.h>
#include "../include/graphe.h"
#include "../include/station.h"

Graphe init_graphe(Station *stations, int nb_stations){ 
    Graphe g = malloc(sizeof(struct SGraphe)); 
    g->stations = stations; 
    g->nb_stations = nb_stations; 
    g->list_adj = malloc(sizeof(Arc*)*nb_stations);
    for (int i = 0; i < nb_stations; i++){ //On initialise chaque liste d'adjacence (chaque indice du tablea) à null 
        g->list_adj[i] = NULL; 
    }
    return g;
}

void graphe_add_arc(Graphe g, int source, int destination, int temps){
    Arc arc = malloc(sizeof(struct SArc)); 
    arc->destination = destination; 
    arc->temps = temps; 
    arc->next_destination = g->list_adj[source];  //On ajoute l'arc au début de la liste d'adjacence 
    g->list_adj[source] = arc; //après on met à jour la liste d'adjacence 
} 

void free_graphe(Graphe g){
    for (int i = 0; i < g->nb_stations; i++){ 
        Arc arc = g->list_adj[i]; 
        while (arc != NULL){ //on va parcourir toute la liste d'adjacence 
            Arc t = arc; 
            arc = arc->next_destination; 
            free(t); 
        }
    }
    free(g->list_adj); 
    free(g); //on libère le graphe
} 
