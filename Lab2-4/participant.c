//
// Created by Cristian on 3/9/2024.
//
#include "participant.h"
#include <stdlib.h>
#include <string.h>

Participant *creeazaParticipant(char *nume, char *prenume, char *id, const int *scor) {
    /**
     * functie care creeaza un participant nou si il returneaza
     * return: part, rtype:Participant
     * **/
    Participant *part = malloc(sizeof(Participant));
    part->id = malloc(sizeof(char) * 4);
    strcpy(part->id, id);

    part->nume = malloc(sizeof(char) * (strlen(nume) + 1));
    strcpy(part->nume, nume);

    part->prenume = malloc(sizeof(char) * (strlen(prenume) + 1));
    strcpy(part->prenume, prenume);

    part->scor = malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++) part->scor[i] = scor[i];
    return part;
}

void distrugeParticipant(Participant *p) {
    /**
     * functie care dealoca memoria pt un participant
     * param: p - participantul
     * **/
    free(p->id);
    free(p->nume);
    free(p->prenume);
    free(p->scor);
    free(p);
}

char *get_id(Participant *p) {
    /**
     * param: p - participantul
     * return: idul participantului p (char*)
     * **/
    return p->id;
}

char *get_nume(Participant *p) {
    /**
     * param: p - participantul
     * return: numele participantului p (char*)
     * **/
    return p->nume;
}

char *get_prenume(Participant *p) {
    /**
     * param: p - participantul
     * return: prenumele participantului p (char*)
     * **/
    return p->prenume;
}

int get_scor(Participant *p, int n) {
    /**
     * param: p - participantul
     * param: n - indexul scorului
     * return: scorul participantului p (float)
     * **/
    return p->scor[n];
}

int get_scor_total(Participant *p) {
    /**
     * param: p - participantul
     * return: media scorurilor participantului p (float)
     * **/
    int scorTotal = 0;
    for (int i = 0; i < 10; i++) scorTotal += p->scor[i];
    return scorTotal;
}

void set_id(Participant *p, char *new) {
    /**
     * seteaza id-ul participantului
     * param: p - participantul
     * **/
    strcpy(p->id, new);
}

void set_nume(Participant *p, char *new) {
    /**
     * seteaza numele-ul participantului
     * param: p - participantul
     * **/
    free(p->nume);
    p->nume = malloc(sizeof(char) * (strlen(new) + 1));
    strcpy(p->nume, new);
}

void set_prenume(Participant *p, char *new) {
    /**
     * seteaza prenumele-ul participantului
     * param: p - participantul
     * **/
    free(p->prenume);
    p->prenume = malloc(sizeof(char) * (strlen(new) + 1));
    strcpy(p->prenume, new);
}

void set_scor(Participant *p, int new, int n) {
    /**
     * seteaza id-ul participantului
     * param: p - participantul
     * **/
    p->scor[n] = new;
}

void swap_participanti(Participant *a, Participant *b) {
    /**
     * interschimba participantii a si b
     * param: a,b - participanti
     * **/
    Participant *aux = malloc(sizeof(Participant));
    *aux = *a;
    *a = *b;
    *b = *aux;
    free(aux);
}
