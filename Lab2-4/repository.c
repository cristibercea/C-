//
// Created by Cristian on 3/7/2024.
//
#include "repository.h"
#include <stdlib.h>
#include <string.h>

ListaParticipanti *creeazaListaVida() {
    /**
     * functia care creeaza o lista vida de concurenti la rularea programului
     * postconditii: se returneaza o structura care contine:
     *               - concurenti = un vector alocat dinamic de structuri de tip Participant
     *               - lungime = 0 (int) lungimea vectorului de concurenti
     * **/
    ListaParticipanti *Lista = (ListaParticipanti *) malloc(sizeof(ListaParticipanti));
    Lista->lungime = 0;
    Lista->capacitate = 20;
    Lista->concurenti = (Participant **) malloc((Lista->capacitate) * sizeof(Participant *));
    return Lista;
}

void distrugeRepo(ListaParticipanti *list) {
    /**
     * functie care distruge repo-ul (lista cu participanti)
     * params: list - de tipul ListaParticipanti
     * postconditii: list.lungime - devine 0 (lista vida)
     *               list.capacitate - devine 0 (lista vida)
     *               list.concurenti - este dealocat din heap
     * **/
    for (int i = 0; i < dimensiune(list); i++) distrugeParticipant(get_participant(list, i));
    free(list->concurenti);
    list->lungime = 0;
    list->capacitate = 0;
    free(list);
}

void resizeRepo(ListaParticipanti *repo) {
    /**
     * functie care realoca un spatiu mai mare pentru vectorul dinamic de participanti
     * params: repo - pointer catre repo
     * postconditii: se dubleaza capacitatea repo-ului si se aloca spatiul de memorie
     *               corespunzator petru vectorul dinamic 'concurenti'
     * **/
    ListaParticipanti* r_cpy = (ListaParticipanti*)malloc(sizeof(ListaParticipanti));
    r_cpy->lungime = 0;
    r_cpy->capacitate = repo->capacitate * 2;
    r_cpy->concurenti = (Participant**)malloc(sizeof(Participant*) * repo->capacitate);
    for (int i = 0; i < dimensiune(repo); i++){
        (r_cpy->concurenti)[dimensiune(r_cpy)] = get_participant(repo, i);
        r_cpy->lungime++;
    }

    free(repo->concurenti);

    repo->capacitate = r_cpy->capacitate;
    repo->lungime = 0;
    repo->concurenti = (Participant**)malloc(sizeof(Participant*) * (repo->capacitate));
    for (int i = 0; i < dimensiune(r_cpy); i++){
        (repo->concurenti)[dimensiune(repo)] = get_participant(r_cpy, i);
        repo->lungime++;
    }
    free(r_cpy->concurenti);
    free(r_cpy);
}

Participant *get_participant(ListaParticipanti *lista, int index) {
    /**
     * functie care returneaza participantul din repo cu indexul dat ca parametru
     * params: lista - repo-ul de tip ListaParticipanti
     *         index - int
     * postconditii: se returneaza: participantul din repo cu indexul cautat
     * **/
    return lista->concurenti[index];
}

int dimensiune(ListaParticipanti *lista) {
    /**
     * functie care returneaza numarul de elemente din repo
     * params: lista - repo-ul de tip ListaParticipanti
     * postconditii: se returneaza: nr de elem din repo
     * **/
    return lista->lungime;
}

int find_by_id(ListaParticipanti *repo, char *id) {
    /**
     * functie care cauta un participant in repo cu un anume id
     * params: repo - tip ListaParticipanti
     *         id - tip sir de char (id-ul dupa care se face cautarea)
     * postconditii: se returneaza: participantul cu id-ul cautat, daca acesta exista, NULL, altfel
     * **/
    for (int i = 0; i < dimensiune(repo); i++) if (strcmp(get_id(get_participant(repo, i)), id) == 0) return i;
    return -1;
}

int store(ListaParticipanti *repo, Participant *part) {
    /**
     * functie care salveaza in repo un participant
     * params: repo
     * **/
    if (find_by_id(repo, get_id(part)) != -1) return 0; ///duplicat, id deja existent in repo
    if (dimensiune(repo) >= repo->capacitate) resizeRepo(repo);
    (repo->concurenti)[dimensiune(repo)] = part;
    repo->lungime++;
    return 1; ///salvat
}

int edit(ListaParticipanti *repo, char *nume, char *prenume, char *id, int *scor) {
    /**
     * functie care editeaza un participant din repo
     * params: repo
     *         nume,prenume,id-siruri de char
     *         scor-sir de inturi
     * **/
    int index = find_by_id(repo, id);
    if (index == -1) return 0; ///id inexistent in repo
    set_nume(get_participant(repo, index), nume);
    set_prenume(get_participant(repo, index), prenume);
    for (int i = 0; i < 10; i++) set_scor(get_participant(repo, index), scor[i], i);
    return 1; ///editat
}

int delete(ListaParticipanti *repo, char *id) {
    /**
     * functie care sterge un participant din repo
     * params: repo
     *         id-sir de char
     * **/
    int index = find_by_id(repo, id);
    if (index == -1) return 0; ///id inexistent in repo
    distrugeParticipant(get_participant(repo, index));
    for (int i = index; i < dimensiune(repo); i++) repo->concurenti[i] = get_participant(repo, i + 1);
    repo->lungime--;
    return 1; ///sters
}