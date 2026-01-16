// Auteur : Adam Zekari - Alexis Miras

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/station.h"
#include "../include/hash.h"


void afficher(Station s) {
    printf("ID : %i, Nom : %s \n", s->id, s->name);
}

// initialiser un tableau de station
Station *init_station(char *file_name, int *nb_stations) {

    char line[BUF_SIZE];

    FILE *f = fopen(file_name, "r");
    if (!f) {
        printf("Erreur d'ouverture du fichier");
        return NULL;
    }

    // boucle pour la gestion d'erreur dans le fichier et comptage du nombre de station
    while (fgets(line, BUF_SIZE, f)) {
        if (strncmp(line, "STATION", 7) == 0) {

            strtok(line, ";");
            char *id = strtok(NULL, ";");
            char *name = strtok(NULL, "\n");

            if (!id || strlen(id) == 0 || !name || strlen(name) == 0) {
                fprintf(stderr, "Erreur format STATION ligne %i\n", (*nb_stations)+1);
                continue; // ignorer
            }
            (*nb_stations)++;
        }
    }

    Station *stations = malloc((*nb_stations)*sizeof(Station));
    if (!stations) {
        fclose(f);
        return NULL;
    }

    // retour au début du fichier
    rewind(f);

    int index = 0;
    while (fgets(line, BUF_SIZE, f)) {
        if (line[0] == '#' || strlen(line) <= 1) continue;
        if (strncmp(line, "STATION", 7) == 0) {
            strtok(line, ";");
            char *id = strtok(NULL, ";");
            char *name = strtok(NULL, "\n");


            if (!id || strlen(id) == 0 || !name || strlen(name) == 0) {
                printf("Erreur format STATION ligne %i\n", index+1);
                continue;
            }

            int existing_index = search_hash(id);
            if (existing_index != -1) {
                printf("Doublon ID station %i à la ligne %i, nom remplacé\n", atoi(id), index+1);
                free(stations[existing_index]->name);
                stations[existing_index]->name = strdup(name);
                continue;
            }

            stations[index] = malloc(sizeof(struct SStation));
            stations[index]->id = atoi(id);
            stations[index]->name = strdup(name);

            insert_hash(id, index);
            index++;
        }
    }

    fclose(f);
    return stations;
}