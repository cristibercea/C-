//
// Created by Cristian on 3/7/2024.
//

#ifndef LAB2_4_SERVICE_H
#define LAB2_4_SERVICE_H

#include "repository.h"

typedef struct {
    ListaParticipanti *repo;
} service;

///functia care creeaza un service
service *creeazaService();

///functie care distruge service-ul
void distrugeService(service *serv);

///creeaza un nou participant si il adauga in lista, daca nu exista deja altul cu acelasi id
int adaugaServParticipant(service *serv, char *nume, char *prenume, char *id, int *scor);

///editeaza un participant existent in repo
int editeazaServParticipant(service *serv, char *nume, char *prenume, char *id, int *scor);

///sterge un participant din repo
int stergeServParticipant(service *serv, char *id);

///filtreaza participantii din repo dupa scorul total obtinut la cele 10 probleme
void filtreazaServParticipantiScor(service *serv, ListaParticipanti *lista, char *filtru);

///filtreaza participantii din repo dupa prima litera din nume
void filtreazaServParticipantiNume(service *serv, ListaParticipanti *lista, const char *filtru);

///sorteaza participantii din repo, in functie de tipul de sortare
void sorteazaServTip(service *serv, char *tip);

///sorteaza participantii din repo dupa key si in functie de ordine(reversed = 0 sau 1)
void sort(ListaParticipanti *list, int key, int reversed);

///functie care transforma un sir de char intr-un int
int utilCalcScor(char *filtru);

#endif //LAB2_4_SERVICE_H