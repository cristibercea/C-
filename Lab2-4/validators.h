//
// Created by Cristian on 3/7/2024.
//

#ifndef LAB2_4_VALIDATORS_H
#define LAB2_4_VALIDATORS_H

///verifica daca id-ul e un string de exact 3 cifre
int validId(char *id);

///verifica daca cuv este un string format doar din litere si caracterul '-'
int validCuv(char *cuv);

///verifica daca scor este un string care se poate transpune intr-un nr de la 0 la 10 si returneaza numarul corespunzator

int validScor(char *scor);

///verifica daca fil este un string format doar din cifre (daca tip=='1')
///verifica daca fil este un string format doar dintr-o litera (daca tip=='2')
int validFiltr(char *fil, char tip);

///verifica daca sort este unul din stringurile: "0", "1c", "1d", "2c", "2d"
int validSrt(char *sort);

#endif //LAB2_4_VALIDATORS_H