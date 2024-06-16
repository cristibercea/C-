//
// Created by Cristian on 3/7/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ui.h"
#include "service.h"
#include "validators.h"

///functia din ui pt adaugare participanti
void adaugaParticipant(service *serv);

///functia din ui pt editare participant existent in lista
void editeazaParticipant(service *serv);

///functia din ui pt stergere participant din lista
void stergeParticipant(service *serv);

///functia din ui de filtrare a participantilor din lista in functie de un parametru
void filtreazaParticipanti(service *serv);

///functia din ui de sortare a concurentilor din lista (cresc/desc), dupa un criteriu
void sorteazaParticipanti(service *serv);

void print_successful_operation() { printf("Operatie realizata cu succes!\n"); }

void print_unsuccessful_operation() { printf("Operatia a esuat!\n"); }

void meniu() { ///meniul principal al aplicatiei
    printf("\n    Concurs de programare - Comenzi:\n");
    printf(" 0. Oprire aplicatie\n 1. Adauga participant\n 2. Editeaza participant\n 3. Sterge participant\n 4. Afisare participanti filtrati\n 5. Sortare participanti");
}

void meniuFiltre() { ///meniul pentru filtre
    printf("\n    Filtre:\n");
    printf(" 0. Anulare operatie\n 1. Participanti cu scor mai mic decat o valoare\n 2. Participanti al caror nume incepe cu o litera\n");
}

void meniuSortari(){ ///meniul pentru sortari
    printf("\n    Sortari:\n");
    printf(" -> 0 - Anulare operatie\n -> Sortare lexicografica dupa nume:\n   1c - crescator\n   1d - descrescator\n -> Sortare dupa scor\n   2c - crescator\n   2d - descrescator\n");
}

void citesteComanda(char *comm) {
    /**
     * functia de citire comenzi de la tast
     * ia drept comanda doar primul caracter introdus de user de la tast
     * daca s-au introdus mai mult de un singur caracter, comanda este invalida
     * postconditii: comm = (char) reprezinta un singur caracter (diferit de newline)
     * **/
    printf("\n>Introduceti comanda:");
    scanf_s("%s", comm, 10);
    fflush(stdin);
    while (strlen(comm)>1) {
        printf("[!] Comanda invalida!\n");
        meniu();
        printf("\n>Introduceti comanda:");
        strcpy(comm, "");
        scanf_s("%s", comm, 10);
        fflush(stdin);
    }
}

void citesteFiltru(char *comm) {
    /**
     * functia de citire comenzi de la tast
     * ia drept comanda doar primul caracter introdus de user de la tast
     * daca s-au introdus mai mult de un singur caracter, comanda este invalida
     * postconditii: comm = (char) reprezinta un singur caracter (diferit de newline)
     * **/
    strcpy(comm, "");
    printf("\n>Introduceti comanda de filtrare:");
    scanf_s("%s", comm, 10);
    fflush(stdin);
    while (strlen(comm) > 1) {
        printf("[!] Comanda de filtrare invalida!\n");
        meniuFiltre();
        printf("\n>Introduceti comanda de filtrare:");
        strcpy(comm, "");
        scanf_s("%s", comm, 10);
        fflush(stdin);
    }
}

void citesteId(char *id) {
    /**
     * citeste string-ul id de la tast
     * **/
    scanf_s("%s", id, 10);
    fflush(stdin);
    while (!validId(id)) {
        printf("[!] Id invalid. Mai incearca:");
        strcpy(id, "");
        scanf_s("%s", id, 10);
        fflush(stdin);
    }
}

void citesteNume(char *nume) {
    /**
     * citeste string-ul nume de la tast
     * postconditii: returneaza un nume valid
     * **/
    scanf_s("%s", nume, 41);
    fflush(stdin);
    while (!validCuv(nume)) {
        printf("[!] Nume invalid. Mai incearca:");
        strcpy(nume, "");
        scanf_s("%s", nume, 41);
        fflush(stdin);
    }
}

void citestePrenume(char *prenume) {
    /**
     * citeste string-ul prenume de la tast
     * postconditii: returneaza un prenume valid
     * **/
    scanf_s("%s", prenume, 41);
    fflush(stdin);
    while (!validCuv(prenume)) {
        printf("[!] Prenume invalid. Mai incearca:");
        strcpy(prenume, "");
        scanf_s("%s", prenume, 41);
        fflush(stdin);
    }
}

char *citesteValoareFiltru(char tip) {
    /**
     * citeste string-ul filtru de la tast
     * postconditii: returneaza un filtru valid
     * **/
    char *fil;
    if (tip == '1') printf(" >Introduceti scor (nr intre 0 si 100): ");
    else printf(" >Introduceti initiala numelui de familie: ");
    fil = (char *) malloc(sizeof(char) * 10);
    scanf_s("%s", fil, sizeof(fil));
    fflush(stdin);
    while (!validFiltr(fil, tip)) {
        printf("[!] Valoare invalida. Mai incearca:");
        strcpy(fil, "");
        scanf_s("%s", fil, sizeof(fil));
        fflush(stdin);
    }
    return fil;
}

int citesteScor() {
    /**
     * citeste scorul de la tast
     * postconditii: returneaza un scor valid
     * **/
    char scor[7];
    scanf_s("%s", scor, sizeof(scor));
    fflush(stdin);
    while (validScor(scor) == -1) {
        printf("[!] Scor invalid. Mai incearca:");
        strcpy(scor, "");
        scanf_s("%s", scor, sizeof(scor));
        fflush(stdin);
    }
    return validScor(scor);
}

void citesteSortare(char *sort){
    /**
     * citeste string-ul sort de la tast
     * postconditii: returneaza un tip de sortare valid
     * **/
    meniuSortari();
    printf(" >Introduceti comanda:");
    scanf_s("%s", sort, sizeof(sort));
    fflush(stdin);
    while (!validSrt(sort)) {
        meniuSortari();
        printf("[!] Comanda invalida. Mai incearca:");
        strcpy(sort, "");
        scanf_s("%s", sort, sizeof(sort));
        fflush(stdin);
    }
}

void runApp() {
    /**
     * functia care ruleaza app. creeaza lista de participanti si intra in ciclu infinit pana la introducerea
     * de catre utilizator a caracterului '0' de la tast, cand lista se sterge, iar rularea se opreste
     * **/
    service *serv = creeazaService();
    char* comm = malloc(sizeof(char) * 10);
    while (1) {
        meniu();
        strcpy(comm, "");
        citesteComanda(comm);
        if (comm[0] == '0') break;
        switch (comm[0]) {
            case '1':
                adaugaParticipant(serv);
                break;
            case '2':
                editeazaParticipant(serv);
                break;
            case '3':
                stergeParticipant(serv);
                break;
            case '4':
                filtreazaParticipanti(serv);
                break;
            case '5':
                sorteazaParticipanti(serv);
                break;
            default:
                printf("[!] Comanda invalida!\n");
        }
    }
    free(comm);
    distrugeService(serv);
    printf("\n ~Aplicatie oprita!");
}

void adaugaParticipant(service *serv) {
    /**
     * se citesc si se valideaza datele unui nou participant care se va adauga in repo daca nu exista deja
     * **/
    char *nume = malloc(sizeof(char) * 41), *prenume = malloc(sizeof(char) * 41), *id = malloc(sizeof(char) * 10);
    int scor[10];
    printf("Introduceti id-ul(3 cifre):");
    citesteId(id);
    printf("Introduceti numele(fara spatiu):");
    citesteNume(nume);
    printf("Introduceti prenumele(fara spatiu):");
    citestePrenume(prenume);
    printf("\nIntroduceti Punctajele (0->10):\n");
    for (int i = 0; i < 10; i++) {
        printf(">Punctaj Problema %d:", i + 1);
        scor[i] = citesteScor();
    }
    if (adaugaServParticipant(serv, nume, prenume, id, scor)) print_successful_operation();
    else print_unsuccessful_operation();
    free(nume);
    free(prenume);
    free(id);
}

void editeazaParticipant(service *serv) {
    /**
     * se citesc si se valideaza noile date ale unui participant existent in repo
     * **/
    char *nume = malloc(sizeof(char) * 41), *prenume = malloc(sizeof(char) * 41), *id = malloc(sizeof(char) * 10);
    int scor[10];
    printf("Introduceti id-ul unui participant existent(3 cifre):");
    citesteId(id);
    printf("Introduceti numele nou(fara spatiu):");
    citesteNume(nume);
    printf("Introduceti prenumele nou(fara spatiu):");
    citestePrenume(prenume);
    printf("Introduceti Punctajele actualizate (0->10):\n");
    for (int i = 0; i < 10; i++) {
        printf(">Punctaj nou Problema %d:", i + 1);
        scor[i] = citesteScor();
    }
    if (editeazaServParticipant(serv, nume, prenume, id, scor)) print_successful_operation();
    else print_unsuccessful_operation();
    free(nume);
    free(prenume);
    free(id);
}

void stergeParticipant(service *serv) {
    /**
     * se citeste si se valideaza id-ul unui participant de sters din repo
     * **/
    char *id = malloc(sizeof(char) * 10);
    printf("Introduceti id-ul unui participant existent(3 cifre):");
    citesteId(id);
    if (stergeServParticipant(serv, id)) print_successful_operation();
    else print_unsuccessful_operation();
    free(id);
}

void filtreazaParticipanti(service *serv) {
    /**
     * se citeste si se valideaza tipul-ul unui filtru iar apoi se afiseaza participantii filtrati
     * dupa acest fltru
     * **/
    meniuFiltre();
    char* tip = malloc(sizeof(char) * 10);
    citesteFiltru(tip);
    while (tip[0] != '0' && tip[0] != '1' && tip[0] != '2') {
        printf("[!] Comanda de filtrare necunoscuta!\n");
        meniuFiltre();
        citesteFiltru(tip);
    }
    if (tip[0] == '0') return;
    char *filtru;
    filtru = citesteValoareFiltru(tip[0]);
    ListaParticipanti *filtrat = creeazaListaVida();
    if (tip[0] == '1') {
        filtreazaServParticipantiScor(serv, filtrat, filtru);
        if (dimensiune(filtrat) != 0) printf("    Lista cu participantii cu scor total mai mic decat %s\n", filtru);
    } else {
        filtreazaServParticipantiNume(serv, filtrat, filtru);
        if (dimensiune(filtrat) != 0) printf("    Lista cu participantii cu prima litera a numelui \"%s\"\n", filtru);
    }
    free(tip);
    free(filtru);
    if (dimensiune(filtrat) != 0)
        for (int i = 0; i < dimensiune(filtrat); i++)
            printf(" %d. Id: %s - Nume: %s - Prenume: %s - Scor total: %d;\n", i + 1, get_id(get_participant(filtrat,i)),
                   get_nume(get_participant(filtrat,i)),
                   get_prenume(get_participant(filtrat,i)), get_scor_total(get_participant(filtrat,i)));
    else printf(" [!] Nu exista participanti cu propretatea data.\n");
    ///curatam doar referinta la participantii filtrati, nu si ceea ce se gaseste la acele adrese (de aceea nu se apeleaza distrugeRepo())
    free(filtrat->concurenti);
    free(filtrat);
}

void sorteazaParticipanti(service *serv) {
    /**
     * se citeste si se valideaza tipul-ul unei sortari iar apoi se afiseaza participantii sortati
     * in functie de acest tip
     * **/
    if (dimensiune(serv->repo) != 0) {
        char *tip = (char *) malloc(sizeof(char) * 5);
        citesteSortare(tip);
        if(!strcmp(tip,"0")) {
            free(tip);
            return;
        }
        sorteazaServTip(serv, tip);
        free(tip);
        printf("\n    Lista cu participantii sortati:\n");
        for (int i = 0; i < dimensiune(serv->repo); i++)
            printf(" %d. Id: %s - Nume: %s - Prenume: %s - Scor total: %d;\n", i + 1, get_id(get_participant(serv->repo,i)),
                   get_nume(get_participant(serv->repo,i)),
                   get_prenume(get_participant(serv->repo,i)), get_scor_total(get_participant(serv->repo,i)));
    } else printf(" [!] Nu s-a salvat niciun participant in aplicatie!\n");

}
