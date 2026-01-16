// Auteur : Adam Zekari - Alexis Miras

#ifndef STATION_H
#define STATION_H

#define BUF_SIZE 1024

struct SStation {
    int id;
    char *name;
};
typedef struct SStation* Station;

void afficher_station(Station s);
Station *init_station(char *file_name, int *nb_stations);

#endif 