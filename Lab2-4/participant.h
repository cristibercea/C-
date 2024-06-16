//
// Created by Cristian on 3/9/2024.
//

#ifndef LAB2_4_PARTICIPANT_H
#define LAB2_4_PARTICIPANT_H

typedef struct {
    char *nume, *prenume, *id;
    int *scor;
} Participant;

///functie care creeaza un participant nou si il returneaza
Participant *creeazaParticipant(char *nume, char *prenume, char *id, const int *scor);

///functie care dealoca memoria pt un participant
void distrugeParticipant(Participant *p);

///returneaza id-ul participantului
char *get_id(Participant *p);

///returneaza numele participantului
char *get_nume(Participant *p);

///returneaza prenumele participantului
char *get_prenume(Participant *p);

///returneaza scorul final al participantului
int get_scor_total(Participant *p);

///returneaza scorul participantului pentru problema n
int get_scor(Participant *p, int n);

///seteaza id-ul participantului cu o valoare noua
void set_id(Participant *p, char *new);

///seteaza numele participantului cu o valoare noua
void set_nume(Participant *p, char *new);

///seteaza prenumele participantului cu o valoare noua
void set_prenume(Participant *p, char *new);

///seteaza scorul participantului, la problema n, cu o valoare noua
void set_scor(Participant *p, int new, int n);

///interschimba 2 participanti
void swap_participanti(Participant *a, Participant *b);

#endif //LAB2_4_PARTICIPANT_H