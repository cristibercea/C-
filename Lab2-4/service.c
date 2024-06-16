//
// Created by Cristian on 3/7/2024.
//
#include "service.h"
#include "repository.h"
#include <stdlib.h>
#include <string.h>

service *creeazaService() {
    ///functia din service responsabila de creerea unui repo gol
    ///postconditii: se returneaza o lista de participanti vida
    service *serv = (service *) malloc(sizeof(service));
    serv->repo = creeazaListaVida();
    return serv;
}

void distrugeService(service *serv) {
    /**
     * functie care sterge repo-ul cand este apelata
     * params: serv - struct de tip service
     * postconditii: serv.repo este dealocat din heap
     * **/
    distrugeRepo(serv->repo);
    free(serv);
}

int adaugaServParticipant(service *serv, char *nume, char *prenume, char *id, int *scor) {
    /**
     * creeaza un nou participant si il adauga in lista, daca nu exista deja altul cu acelasi id
     * params: nume,prenume,id-siruri de char
     *         scor-sir de 10 int-uri
     * postconditii: returneaza 1 daca s-a putut salva participantul, 0 altfel
     * **/
    Participant *part = creeazaParticipant(nume, prenume, id, scor);
    int verif = store(serv->repo, part);
    if (verif == 0) distrugeParticipant(part);
    return verif;
}

int editeazaServParticipant(service *serv, char *nume, char *prenume, char *id, int *scor) {
    /**
     * editeaza un participant existent in repo
     * params: nume,prenume,id-siruri de char
     *         scor-sir de 10 int-uri
     * postconditii: returneaza 1 daca s-a putut edita participantul cu id-ul dat, 0 altfel
     * **/
    return edit(serv->repo, nume, prenume, id, scor);
}

int stergeServParticipant(service *serv, char *id) {
    /**
     * sterge un participant din repo
     * param: id-sir de char
     * postconditii: returneaza 1 daca s-a sters participantul cu id-ul dat, 0 altfel
     * **/
    return delete(serv->repo, id);
}

void filtreazaServParticipantiScor(service *serv, ListaParticipanti *lista, char *filtru) {
    /**
     * filtreaza participantii din repo dupa scorul total obtinut la cele 10 probleme
     * param: serv - service
     *        filtru - sir de char, care contine scorul pt filtrare
     *        lista - lista cu participanti filtrati
     * postconditii: lista - contine participantii filtrati corespunzator
     * **/
    int scor = utilCalcScor(filtru);
    for (int i = 0; i < dimensiune(serv->repo); i++)
        if (get_scor_total(get_participant(serv->repo, i)) < scor) {
            store(lista, get_participant(serv->repo, i));
        }
}

void filtreazaServParticipantiNume(service *serv, ListaParticipanti *lista, const char *filtru) {
    /**
     * filtreaza participantii din repo dupa prima litera din nume
     * param: serv - service
     *        filtru - sir de char, care contine litera pt filtrare
     *        lista - lista cu participanti filtrati
     * postconditii: lista - contine participanti filtrati corespunzator
     * **/
    for (int i = 0; i < dimensiune(serv->repo); i++)
        if (get_nume(get_participant(serv->repo, i))[0] == filtru[0]) {
            store(lista, get_participant(serv->repo, i));
        }
}

void sorteazaServTip(service *serv, char *tip) {
    /**
     * sorteaza participantii din repo, in functie de tipul de sortare
     * param: serv - service
     *        tip - sir de char, care sugereaza tipul de sortare folosit
     * postconditii: repo-ul este sortat corespunzator
     * **/
    if (!strcmp(tip, "1c")) sort(serv->repo, 1, 0);
    else if (!strcmp(tip, "1d")) sort(serv->repo, 1, 1);
    else if (!strcmp(tip, "2c")) sort(serv->repo, 2, 0);
    else sort(serv->repo, 2, 1);
}

void sort(ListaParticipanti *list, int key, int reversed) {
    /**
     * sorteaza participantii din repo dupa key si in functie de ordine(reversed = 0 sau 1)
     * param: list - lista de sortat
     *        key = 1 -> sortare dupa nume
     *            = 2 -> sortare dupa scor
     *        reversed = 0 -> sortare crescatoare
     *                 = 1 -> sortare descrescatoare
     * postconditii: lista este sortata corespunzator
     * **/
    int sorted, condition, conditionExtra;
    do {
        sorted = 1;
        for (int i = 0; i < dimensiune(list) - 1; i++)
            if (key == 1) {
                condition = strcmp(get_nume(get_participant(list, i)), get_nume(get_participant(list, i + 1)));
                conditionExtra = strcmp(get_prenume(get_participant(list, i)), get_prenume(get_participant(list, i + 1)));
                if ((reversed == 0 && (condition > 0 || (condition == 0 && conditionExtra > 0))) || (reversed == 1 && (condition < 0 || (condition == 0 && conditionExtra < 0)))) {
                    swap_participanti(get_participant(list, i),get_participant(list, i+1));
                    sorted = 0;
                }
            } else {
                if ((reversed == 0 && get_scor_total(get_participant(list, i)) > get_scor_total(get_participant(list, i + 1))) || (reversed == 1 && get_scor_total(get_participant(list, i)) < get_scor_total(get_participant(list, i + 1)))) {
                    swap_participanti(get_participant(list, i), get_participant(list, i+1));
                    sorted = 0;
                }
            }
    } while (!sorted);
}

int utilCalcScor(char *filtru) {
    /**
     * functie care transforma un sir de char intr-un int
     * params: filtru - sir de char
     * postconditii: numar - int
     * **/
    int numar = 0;
    long long unsigned int i = 0;
    while (i < strlen(filtru)) {
        numar = numar * 10 + filtru[i] - '0';
        i++;
    }
    return numar;
}