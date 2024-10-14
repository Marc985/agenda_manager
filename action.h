#ifndef ACTION_H
#define ACTION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LGNOM 20
#define LGPRENOM 15
#define LGTEL 11
#define LGFONCTION 20
#define LGFICHIER 21

typedef struct Client;
{
    char nom[LGNOM + 1];
    char prenom[LGPRENOM + 1];
    int age;
    char tel[LGTEL + 1];
    char fonction[LGFONCTION + 1]; // Champ fonction
};

void supprimer_nouvelle_ligne(char *chaine);
void afficher_agenda_actuel(const char *nomfich);
void creer_enregistrements(FILE *fichier);
void lire_par_nom(FILE *fichier);
void lire_par_numero(FILE *fichier);
void afficher_les_enregistrements(FILE *fichier);
FILE *ouvrir_agenda(char *nomfich, const char *mode);
FILE *creer_agenda(char *nomfich);
