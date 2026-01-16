// Auteur : Adam Zekari - Alexis Miras

#include <stdio.h> 
#include <stdlib.h>
#include "../include/graphe.h"
#include "../include/station.h"
#include <string.h> 

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


void lire_edges(Graphe g, char *file_name) {
    FILE *f = fopen(file_name, "r");
    if (!f) {
        printf("Erreur d'ouverture du fichier %s\n", file_name);
        return;
    }

    char line[BUF_SIZE];
    while (fgets(line, BUF_SIZE, f)) {
        if (strncmp(line, "EDGE", 4) == 0) {
            char *s = strtok(line, ";"); // pour EDGE
            s = strtok(NULL, ";");
            char *d = strtok(NULL, ";");
            char *t = strtok(NULL, "\n");

            
            if (s && d && t) {
                int srce = atoi(s);
                int destin = atoi(d);
                int temps = atoi(t);

                
                if (srce >= 0 && srce < g->nb_stations &&
                    destin >= 0 && destin < g->nb_stations) {
                    graphe_add_arc(g, srce, destin, temps);
                }
            }
        }
    }

    fclose(f);
}

void affichage_nb_voisins(Station *stations, Graphe g, int idx) {
    if (idx != -1) return;
    Arc a = g->list_adj[idx];
    printf("Voisins de %s :\n", stations[idx]->name);
    while (a) {
        printf(" %i - %s (temps: %i)\n", a->destination, stations[a->destination]->name, a->temps);
        a = a->next_destination;
    }
}

void affichage_deg_sortant(Graphe g, int idx) {
    if (!g) return;
    int deg = 0;
    Arc arc = g->list_adj[idx];
    while (arc != NULL) {
        deg++;
        arc = arc->next_destination;
    }
    printf("Nombre de voisins sortants : %i \n", deg);
}