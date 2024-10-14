#include "action.h"

void supprimer_nouvelle_ligne(char *chaine)
{
    size_t longueur = strlen(chaine);
    if (chaine[longueur - 1] == '\n')
    {
        chaine[longueur - 1] = '\0';
    }
}

void afficher_agenda_actuel(const char *nomfich)
{
    if (nomfich[0] != '\0')
    {
        printf("Agenda ouvert : %s\n", nomfich);
    }
}

void creer_enregistrements(FILE *fichier)
{
    Client client;
    char continuer;

    do
    {
        printf("\nNom : ");
        fgets(client.nom, LGNOM + 1, stdin);
        supprimer_nouvelle_ligne(client.nom);

        if (strlen(client.nom) == 0)
        {
            break; // Si le nom est vide, on arrête la saisie
        }

        printf("Prénom : ");
        fgets(client.prenom, LGPRENOM + 1, stdin);
        supprimer_nouvelle_ligne(client.prenom);

        printf("Âge : ");
        scanf("%d", &client.age);
        getchar(); // Consommer le caractère de nouvelle ligne après scanf

        printf("Téléphone : ");
        fgets(client.tel, LGTEL + 1, stdin);
        supprimer_nouvelle_ligne(client.tel);

        printf("Fonction : ");
        fgets(client.fonction, LGFONCTION + 1, stdin);
        supprimer_nouvelle_ligne(client.fonction);

        fwrite(&client, sizeof(Client), 1, fichier);
        memset(&client, 0, sizeof(Client));

        // Demander à l'utilisateur s'il veut continuer
        printf("Voulez-vous ajouter un autre enregistrement ? (o/n) : ");
        scanf("%c", &continuer);
        getchar(); // Consommer le caractère de nouvelle ligne après scanf

    } while (continuer == 'o' || continuer == 'O');
}

void lire_par_nom(FILE *fichier)
{
    Client client;
    char nomcher[LGNOM + 1];
    int trouve = 0;

    printf("Quel nom recherchez-vous : ");
    fgets(nomcher, LGNOM + 1, stdin);
    supprimer_nouvelle_ligne(nomcher);

    while (fread(&client, sizeof(Client), 1, fichier))
    {
        if (strcmp(nomcher, client.nom) == 0)
        {
            trouve = 1;
            printf("\nNom : %s\n", client.nom);
            printf("Prénom : %s\n", client.prenom);
            printf("Âge : %d\n", client.age);
            printf("Téléphone : %s\n", client.tel);
            printf("Fonction : %s\n", client.fonction);
            break;
        }
    }

    if (!trouve)
    {
        printf("-- Ce nom ne figure pas dans le fichier --\n");
    }
}

void lire_par_numero(FILE *fichier)
{
    Client client;
    int num;
    long taille;
    long pos;

    fseek(fichier, 0, SEEK_END);
    taille = ftell(fichier);
    rewind(fichier);

    // Calculer le nombre d'enregistrements
    long nb_enregistrements = taille / sizeof(Client);

    printf("Quel numéro recherchez-vous (1 à %ld) : ", nb_enregistrements);
    scanf("%d", &num);
    getchar(); // Consommer le caractère de nouvelle ligne après scanf

    // Ajuster la position en soustrayant 1 pour correspondre à l'index de tableau
    pos = (num - 1) * sizeof(Client);

    if (num < 1 || num > nb_enregistrements)
    {
        printf("-- Ce numéro ne figure pas dans le fichier --\n");
    }
    else
    {
        fseek(fichier, pos, SEEK_SET);
        fread(&client, sizeof(Client), 1, fichier);
        printf("\nNom : %s\n", client.nom);
        printf("Prénom : %s\n", client.prenom);
        printf("Âge : %d\n", client.age);
        printf("Téléphone : %s\n", client.tel);
        printf("Fonction : %s\n", client.fonction);
    }
}

void afficher_les_enregistrements(FILE *fichier)
{
    Client client;
    int compteur = 0;

    printf("\n--- Liste des enregistrements ---\n");

    while (fread(&client, sizeof(Client), 1, fichier))
    {
        compteur++;
        printf("\nEnregistrement %d :\n", compteur);
        printf("Nom : %s\n", client.nom);
        printf("Prénom : %s\n", client.prenom);
        printf("Âge : %d\n", client.age);
        printf("Téléphone : %s\n", client.tel);
        printf("Fonction : %s\n", client.fonction);
    }

    if (compteur == 0)
    {
        printf("-- Aucun enregistrement trouvé --\n");
    }
}

FILE *ouvrir_agenda(char *nomfich, const char *mode)
{
    FILE *fichier = fopen(nomfich, mode);
    if (fichier == NULL)
    {
        printf("Erreur : impossible d'ouvrir le fichier %s.\n", nomfich);
    }
    return fichier;
}

FILE *creer_agenda(char *nomfich)
{
    FILE *fichier = fopen(nomfich, "wb+");
    if (fichier == NULL)
    {
        printf("Erreur : impossible d'ouvrir le fichier %s.\n", nomfich);
    }
    return fichier;
}