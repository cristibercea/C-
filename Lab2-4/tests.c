//
// Created by Cristian on 3/7/2024.
//
#include <stdlib.h>
#include "participant.h"
#include "tests.h"
#include "repository.h"
#include "service.h"
#include "validators.h"
#include <assert.h>
#include <string.h>

///testele pentru functiile din repo
void testRepo();

///testele pentru functiile din serv
void testService();

///testele pentru functiile validator
void testValidators();

///testele pentru o entitate Participant
void testParticipant();

void runAllTests() {
    testValidators();
    testParticipant();
    testRepo();
    testService();
}

void test_Creeaza_Resize_Distruge_Repo() {
    ///CREEAZA
    ListaParticipanti *lista = NULL;
    assert(lista == NULL);
    lista = creeazaListaVida();
    assert(lista->concurenti != NULL);
    assert(lista != NULL);
    assert(lista->capacitate == 20);
    assert(dimensiune(lista) == 0);
    assert(sizeof(lista->concurenti) == sizeof(Participant *));

    ///RESIZE
    resizeRepo(lista);
    assert(lista->capacitate == 40);
    assert(dimensiune(lista) == 0);
    assert(sizeof(lista->concurenti) == sizeof(Participant *));

    ///DISTRUGE
    distrugeRepo(lista);
}

void testStoreFindEditDelete() {
    ListaParticipanti *lista = creeazaListaVida();

    ///STORE
    int s[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Participant *part = creeazaParticipant("nume", "prenume", "000", s);
    assert(store(lista, part) == 1);
    assert(store(lista, part) == 0);
    assert(dimensiune(lista) == 1);
    assert(get_participant(lista, 0) == part);
    for (int i = 0; i < 10; i++) assert(get_scor(get_participant(lista, 0), i) == i + 1);
    char nine = '9', four = '4';
    for (char i = '1'; i <= four; i++)
        for (char j = '0'; j <= nine; j++) {
            char id[4] = {'0', i, j, '\0'};
            Participant *p = creeazaParticipant("nume", "prenume", id, s);
            assert(store(lista, p) == 1);
        }
    assert(dimensiune(lista) == 41);

    ///FIND
    assert(find_by_id(lista, "001") == -1);
    assert(find_by_id(lista, "000") == 0);

    ///EDIT
    int s2[10];
    for (int i = 0; i < 10; i++) s2[i] = s[i] - 1;
    assert(edit(lista, "numenou", "prenumenou", "000", s2) == 1);
    assert(strcmp(get_id(get_participant(lista, 0)), "000") == 0);
    assert(strcmp(get_nume(get_participant(lista, 0)), "numenou") == 0);
    assert(strcmp(get_prenume(get_participant(lista, 0)), "prenumenou") == 0);
    for (int i = 0; i < 10; i++) assert(get_scor(get_participant(lista, 0), i) == i);
    assert(edit(lista, "", "", "111", s) == 0);
    assert(edit(lista, "nume", "prenume", "000", s) == 1);

    ///DELETE
    assert(delete(lista, "100") == 0);
    assert(get_participant(lista, 0) == part);
    for (int i = 0; i < 10; i++) assert(get_scor(get_participant(lista, 0), i) == i + 1);
    assert(delete(lista, "000") == 1);
    assert(delete(lista, "032") == 1);
    assert(delete(lista, "132") == 0);
    assert(dimensiune(lista) == 39);
    assert(delete(lista, "048") == 1);
    assert(dimensiune(lista) == 38);

    distrugeRepo(lista);
}

void testRepo() {
    test_Creeaza_Resize_Distruge_Repo();
    testStoreFindEditDelete();
}

void testSortari() {
    int s[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    service *serv;
    serv = creeazaService();

    assert(adaugaServParticipant(serv, "dnume", "prenume", "000", s) == 1);//55
    assert(adaugaServParticipant(serv, "dnume", "prenume", "001", s) == 1);//55
    s[3] += 4;
    assert(adaugaServParticipant(serv, "bnume", "aprenume", "002", s) == 1);//59
    s[9] = 1, s[0] = 7;
    assert(adaugaServParticipant(serv, "bnume", "grenume", "003", s) == 1);//56
    s[1] += 7, s[5] += 4;
    assert(adaugaServParticipant(serv, "anume", "tprenume", "004", s) == 1);//67

    ///sortare dupa nume si prenume, crescator
    sorteazaServTip(serv, "1c");
    assert(strcmp(get_id(get_participant(serv->repo, 0)), "004") == 0);
    assert(strcmp(get_id(get_participant(serv->repo, 1)), "002") == 0);
    assert(strcmp(get_id(get_participant(serv->repo, 2)), "003") == 0);
    assert(strcmp(get_id(get_participant(serv->repo, 3)), "000") == 0);
    assert(strcmp(get_id(get_participant(serv->repo, 4)), "001") == 0);

    ///sortare dupa nume si prenume, descrescator
    sorteazaServTip(serv, "1d");
    assert(strcmp(get_id(get_participant(serv->repo, 0)), "000") == 0);
    assert(strcmp(get_id(get_participant(serv->repo, 1)), "001") == 0);
    assert(strcmp(get_id(get_participant(serv->repo, 2)), "003") == 0);
    assert(strcmp(get_id(get_participant(serv->repo, 3)), "002") == 0);
    assert(strcmp(get_id(get_participant(serv->repo, 4)), "004") == 0);

    ///sortare dupa scor, crescator
    sorteazaServTip(serv, "2d");
    assert(strcmp(get_id(get_participant(serv->repo, 0)), "004") == 0);
    assert(strcmp(get_id(get_participant(serv->repo, 1)), "002") == 0);
    assert(strcmp(get_id(get_participant(serv->repo, 2)), "003") == 0);
    assert(strcmp(get_id(get_participant(serv->repo, 3)), "000") == 0);
    assert(strcmp(get_id(get_participant(serv->repo, 4)), "001") == 0);

    ///sortare dupa scor, descrescator
    sorteazaServTip(serv, "2c");
    assert(strcmp(get_id(get_participant(serv->repo, 0)), "000") == 0);
    assert(strcmp(get_id(get_participant(serv->repo, 1)), "001") == 0);
    assert(strcmp(get_id(get_participant(serv->repo, 2)), "003") == 0);
    assert(strcmp(get_id(get_participant(serv->repo, 3)), "002") == 0);
    assert(strcmp(get_id(get_participant(serv->repo, 4)), "004") == 0);

    distrugeService(serv);
}

void testFiltru1(int s[]) {
    service* serv;
    serv = creeazaService();
    char nine = '9', four = '4';
    for (char i = '1'; i <= four; i++)
        for (char j = '0'; j <= nine; j++) {
            char id[4] = { '0', i, j, '\0' };
            Participant* p = creeazaParticipant("nume", "prenume", id, s);
            store(serv->repo, p);
        }

    ListaParticipanti* filtrat1 = creeazaListaVida();
    filtreazaServParticipantiScor(serv, filtrat1, "10");
    assert(dimensiune(filtrat1) == 0);
    distrugeRepo(filtrat1);
    distrugeService(serv);
}

void testFiltru2(int s[]) {
    service* serv;
    serv = creeazaService();
    char nine = '9', four = '4';
    for (char i = '1'; i <= four; i++)
        for (char j = '0'; j <= nine; j++) {
            char id[4] = { '0', i, j, '\0' };
            Participant* p = creeazaParticipant("nume", "prenume", id, s);
            store(serv->repo, p);
        }

    ListaParticipanti* filtrat2 = creeazaListaVida();
    filtreazaServParticipantiScor(serv, filtrat2, "56");
    assert(dimensiune(filtrat2) == dimensiune(serv->repo));

    distrugeService(serv);
    free(filtrat2->concurenti);
    free(filtrat2);
}

void testFiltru3(int s[]) {
    service* serv;
    serv = creeazaService();
    char nine = '9', four = '4';
    for (char i = '1'; i <= four; i++)
        for (char j = '0'; j <= nine; j++) {
            char id[4] = { '0', i, j, '\0' };
            Participant* p = creeazaParticipant("nume", "prenume", id, s);
            store(serv->repo, p);
        }

    ListaParticipanti* filtrat3 = creeazaListaVida();
    filtreazaServParticipantiScor(serv, filtrat3, "100");
    assert(dimensiune(filtrat3) == dimensiune(serv->repo));
    free(filtrat3->concurenti);
    free(filtrat3);

    distrugeService(serv);
}

void testFiltru4(int s[]) {
    service* serv;
    serv = creeazaService();
    char nine = '9', four = '4';
    for (char i = '1'; i <= four; i++)
        for (char j = '0'; j <= nine; j++) {
            char id[4] = { '0', i, j, '\0' };
            Participant* p = creeazaParticipant("nume", "prenume", id, s);
            store(serv->repo, p);
        }

    ListaParticipanti* filtrat4 = creeazaListaVida();
    filtreazaServParticipantiNume(serv, filtrat4, "a");
    assert(dimensiune(filtrat4) == 0);
    free(filtrat4->concurenti);
    free(filtrat4);

    distrugeService(serv);
}

void testFiltru5(int s[]) {
    service* serv;
    serv = creeazaService();
    char nine = '9', four = '4';
    for (char i = '1'; i <= four; i++)
        for (char j = '0'; j <= nine; j++) {
            char id[4] = { '0', i, j, '\0' };
            Participant* p = creeazaParticipant("nume", "prenume", id, s);
            store(serv->repo, p);
        }

    ListaParticipanti* filtrat5 = creeazaListaVida();
    filtreazaServParticipantiNume(serv, filtrat5, "n");
    assert(dimensiune(filtrat5) == dimensiune(serv->repo));
    free(filtrat5->concurenti);
    free(filtrat5);

    distrugeService(serv);
}

void testService() {
    ///CREEAZA
    int s[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    service *serv1;
    serv1 = creeazaService();
    assert(serv1 != NULL);

    ///ADAUGA
    assert(adaugaServParticipant(serv1, "nume", "prenume", "123", s) == 1);
    assert(adaugaServParticipant(serv1, "nume", "prenume", "123", s) == 0);
    assert(adaugaServParticipant(serv1, "asasdg", "sdgre", "123", s) == 0);

    ///EDITEAZA
    assert(editeazaServParticipant(serv1, "aesfh", "pesyfdshertu", "123", s) == 1);
    assert(editeazaServParticipant(serv1, "numenou", "prenumenou", "123", s) == 1);
    assert(editeazaServParticipant(serv1, "numenou", "prenumenou", "121", s) == 0);

    ///STERGE
    assert(stergeServParticipant(serv1, "111") == 0);
    assert(stergeServParticipant(serv1, "123") == 1);
    assert(stergeServParticipant(serv1, "123") == 0);

    ///DISTRUGE
    distrugeService(serv1);

    ///UTILITAR
    assert(utilCalcScor("123") == 123);
    assert(utilCalcScor("13") == 13);
    assert(utilCalcScor("1") == 1);

    ///FILTRARE
    testFiltru1(s);
    testFiltru2(s);
    testFiltru3(s);
    testFiltru4(s);
    testFiltru5(s);
    
    ///SORTARE
    testSortari();
}

void testValidators() {
    ///validId(char * id)
    assert(validId("420") == 1);
    assert(validId("000") == 1);
    assert(validId("111111") == 0);
    assert(validId("11") == 0);
    assert(validId("1as") == 0);
    assert(validId("ohp") == 0);

    ///validCuv(char * cuv)
    assert(validCuv("cuvant") == 1);
    assert(validCuv("cu-vant") == 1);
    assert(validCuv("cu") == 0);
    assert(validCuv("cu vant") == 0);
    assert(validCuv("cuv1nt") == 0);
    assert(validCuv("1234") == 0);

    ///validScor(char * scor)
    assert(validScor("10") == 10);
    assert(validScor("5") == 5);
    assert(validScor("a") == -1);
    assert(validScor("aa") == -1);
    assert(validScor("11") == -1);
    assert(validScor("103") == -1);
    assert(validScor("") == -1);

    ///validFiltr(char *fil, '1')
    assert(validFiltr("", '1') == 0);
    assert(validFiltr("101", '1') == 0);
    assert(validFiltr("1a1", '1') == 0);
    assert(validFiltr("10a", '1') == 0);
    assert(validFiltr("a01", '1') == 0);
    assert(validFiltr("100", '1') == 1);
    assert(validFiltr("srjuf", '1') == 0);
    assert(validFiltr("a", '1') == 0);
    assert(validFiltr("12", '1') == 1);
    assert(validFiltr("q2", '1') == 0);
    assert(validFiltr("2q", '1') == 0);
    assert(validFiltr("tq", '1') == 0);
    assert(validFiltr("1", '1') == 1);

    ///validFiltr(char *fil, '2')
    assert(validFiltr("", '2') == 0);
    assert(validFiltr("a", '2') == 1);
    assert(validFiltr("dgjk", '2') == 0);
    assert(validFiltr("S", '2') == 1);
    assert(validFiltr("1", '2') == 0);
    assert(validFiltr("-", '2') == 0);
    assert(validFiltr("q1", '2') == 0);
    assert(validFiltr("seghj", '3') == 1); ///caz absurd, deoarece tip nu poate fi 3

    ///int validSrt(char *sort)
    assert(validSrt("0") == 1);
    assert(validSrt("1c") == 1);
    assert(validSrt("1d") == 1);
    assert(validSrt("2c") == 1);
    assert(validSrt("2d") == 1);
    assert(validSrt("12c") == 0);
    assert(validSrt("0adsv") == 0);
}

///--TESTE ENITIATE--///
void testCreeaza() {
    int s[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Participant *p = creeazaParticipant("nume", "prenume", "id", s);

    assert(strcmp(get_id(p), "id") == 0);
    assert(strcmp(get_nume(p), "nume") == 0);
    assert(strcmp(get_prenume(p), "prenume") == 0);
    for (int i = 0; i < 10; i++) assert(get_scor(p, i) == i + 1);

    distrugeParticipant(p);
}

void testSeteaza() {
    int s[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Participant *p = creeazaParticipant("", "", "", s);

    set_id(p, "idk");
    assert(strcmp(get_id(p), "idk") == 0);
    set_nume(p, "Cineva");
    assert(strcmp(get_nume(p), "Cineva") == 0);
    set_prenume(p, "Altcineva");
    assert(strcmp(get_prenume(p), "Altcineva") == 0);
    set_scor(p, 50, 3);
    assert(get_scor(p, 3) == 50);
    set_scor(p, 3, 0);
    assert(get_scor(p, 0) == 3);
    set_scor(p, 111, 9);
    assert(get_scor(p, 9) == 111);

    distrugeParticipant(p);
}

void testGetScorTotal() {
    int s[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Participant *p = creeazaParticipant("nume", "prenume", "id", s);
    assert(get_scor_total(p) == 55);
    distrugeParticipant(p);
}

void testSwap() {
    int s[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Participant *a = creeazaParticipant("nume", "prenume", "ida", s);
    Participant *b = creeazaParticipant("nume", "prenume", "idb", s);

    swap_participanti(a, b);
    assert(!strcmp(get_id(a), "idb"));
    assert(!strcmp(get_id(b), "ida"));

    distrugeParticipant(a);
    distrugeParticipant(b);
}

void testParticipant() {
    testCreeaza();
    testSeteaza();
    testGetScorTotal();
    testSwap();
}