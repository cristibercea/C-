//
// Created by Cristian on 3/7/2024.
//
#include <string.h>
#include <ctype.h>
#include "validators.h"

int validId(char *id) {
    /**
     * verifica daca id-ul e un string de exact 3 cifre
     * return: 1-daca id este valid
     *         0-altfel
     * **/
    if (strlen(id) != 3) return 0;
    for (int i = 0; i < 3; i++) if (!isdigit(id[i])) return 0;
    return 1;
}

int validCuv(char *cuv) {
    /**
     * verifica daca cuv este un string format doar din litere si caracterul '-'
     * return: 1-daca cuv este valid
     *         0-altfel
     * **/
    if (strlen(cuv) < 3) return 0;
    for (long long unsigned int i = 0; i < strlen(cuv); i++) if (isalpha(cuv[i]) == 0 && cuv[i] != '-') return 0;
    return 1;
}

int validScor(char *scor) {
    /**
     * verifica daca scor este un string care se poate transpune intr-un nr de la 0 la 10 si returneaza numarul corespunzator
     * return: 1-daca cuv este valid
     *         0-altfel
     * **/
    if (strlen(scor) == 1 && isdigit(scor[0])) return scor[0] - '0';
    if (strlen(scor) == 2 && scor[0] == '1' && scor[1] == '0') return 10;
    return -1;
}

int validFiltr(char *fil, char tip) {
    /**
     * verifica daca fil este un string format doar din cifre (daca tip=='1')
     * verifica daca fil este un string format doar dintr-o litera (daca tip=='2')
     * return: 1-daca fil este valid
     *         0-altfel
     * **/
    if (tip == '1') {
        if (strlen(fil) > 3 || strlen(fil) < 1) return 0;
        if (strlen(fil) == 1 && !isdigit(fil[0])) return 0;
        if (strlen(fil) == 2 && (!isdigit(fil[0]) || !isdigit(fil[1]))) return 0;
        if (strlen(fil) == 3 && (fil[0] != '1' || fil[1] != '0' || fil[2] != '0')) return 0;
    } else if (tip == '2') {
        if (strlen(fil) != 1) return 0;
        if (!isalpha(fil[0])) return 0;
    }
    return 1;
}

int validSrt(char *sort) {
    /**
     * verifica daca sort este unul din stringurile: "0", "1c", "1d", "2c", "2d"
     * return: 1-daca fil este valid
     *         0-altfel
     * **/
    if (!strcmp(sort, "0") || !strcmp(sort, "1c") || !strcmp(sort, "1d") || !strcmp(sort, "2c") ||
        !strcmp(sort, "2d"))
        return 1;
    return 0;
}