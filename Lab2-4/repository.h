//
// Created by Cristian on 3/7/2024.
//

#ifndef LAB2_4_REPOSITORY_H
#define LAB2_4_REPOSITORY_H

#include "participant.h"

typedef struct {
    Participant **concurenti;
    int lungime, capacitate;
} ListaParticipanti;

///functia care creeaza o lista vida de concurenti
ListaParticipanti *creeazaListaVida();

///functie care distruge repo-ul (lista cu participanti)
void distrugeRepo(ListaParticipanti *list);

///functie care realoca un spatiu mai mare pentru repo
void resizeRepo(ListaParticipanti *repo);

///functie care returneaza numarul de elemente din repo
int dimensiune(ListaParticipanti *lista);

///functie care returneaza participantul din repo cu indexul dat ca parametru
Participant *get_participant(ListaParticipanti *lista, int index);

///functie care salveaza in repo un participant
int store(ListaParticipanti *repo, Participant *part);

///functie care editeaza un participant din repo
int edit(ListaParticipanti *repo, char *nume, char *prenume, char *id, int *scor);

///functie care sterge un participant din repo
int delete(ListaParticipanti *repo, char *id);

///functie care cauta un participant in repo cu un anume id
int find_by_id(ListaParticipanti *repo, char *id);

#endif //LAB2_4_REPOSITORY_H