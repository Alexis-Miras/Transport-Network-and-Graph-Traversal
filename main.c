#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 1024

struct SStation {
    int id;
    char *name;
};
typedef struct SStation* Station;

void afficher(Station s);
Station *init_station(char *file_name, int *nb_stations);

int main(int argc, char *argv[]) {

    if (argc != 2) {
        fprintf(stderr, "Fichier : %s \n", argv[0]);
        return 1;
    }

    int nb_stations = 0;
    Station *stations = init_station(argv[1], &nb_stations);

    for (int i = 0; i < nb_stations; i++) afficher(stations[i]);;
    

    for (int i = 0; i < nb_stations; i++) {
        free(stations[i]->name);
        free(stations[i]);
    }
    free(stations); 
}


void afficher(Station s) {
    printf("ID : %i, Nom : %s \n", s->id, s->name);
}

Station *init_station(char *file_name, int *nb_stations) {

    char line[BUF_SIZE];

    FILE *f = fopen(file_name, "r");
    if (!f) {
        perror("Erreur d'ouverture du fichier");
        return NULL;
    }

    /*
    allocation dynamique mémoire des lignes

    struct stat sb;
    fstat(fileno(f), &sb);

    char *line = malloc(sb.st_size + 1);
    */

    while (fgets(line, BUF_SIZE, f)) {
        if (strncmp(line, "STATION", 7) == 0) {
            char *token = strtok(line, ";");
            token = strtok(NULL, ";");
            if (token && strlen(token) > 0) (*nb_stations)++;
        }
    }

    Station *stations = malloc((*nb_stations)*sizeof(Station));

    rewind(f);

    int count = 0;
    while (fgets(line, BUF_SIZE, f)) {
        if (strncmp(line, "STATION", 7) == 0) {

            char *type = strtok(line, ";");
            char *id = strtok(NULL, ";");
            char *name = strtok(NULL, "\n");

            // if (count >= *nb_stations) break;
            stations[count] = malloc(sizeof(struct SStation));

            if (id && strlen(id) > 0) stations[count]->id = atoi(id);
            else continue;

            if (name) stations[count]->name = strdup(name);
            else stations[count]->name = strdup("");

            count++;
        }
    }

    fclose(f);
    return stations;
}