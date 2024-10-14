#include "action.h"
int main(int argc, char const *argv[])
{
    int choix;
    char nomfich[LGFICHIER] = ""; // Initialisé à une chaîne vide
    FILE *fichier = NULL;

    do
    {
        printf("\n--- Menu ---\n");
        printf("1. Ouvrir un agenda existant\n");
        printf("2. Créer un nouvel agenda\n");
        printf("3. Créer des enregistrements\n");
        printf("4. Lire un enregistrement par nom\n");
        printf("5. Lire un enregistrement par numéro\n");
        printf("6. Afficher tous les enregistrements\n");
        printf("7. Fermer l'agenda\n");
        printf("8. Quitter\n");
        printf("Votre choix : ");
        scanf("%d", &choix);
        getchar(); // Consommer le caractère de nouvelle ligne après scanf

        switch (choix)
        {
        case 1:
            if (fichier != NULL)
            {
                fclose(fichier); // Fermer l'agenda actuel s'il est déjà ouvert
            }
            printf("Donnez le nom du fichier de l'agenda à ouvrir : ");
            fgets(nomfich, LGFICHIER, stdin);
            supprimer_nouvelle_ligne(nomfich);
            fichier = ouvrir_agenda(nomfich, "rb+");
            afficher_agenda_actuel(nomfich);
            break;

        case 2:
            if (fichier != NULL)
            {
                fclose(fichier); // Fermer l'agenda actuel s'il est déjà ouvert
            }
            printf("Donnez le nom du nouvel agenda à créer : ");
            fgets(nomfich, LGFICHIER, stdin);
            supprimer_nouvelle_ligne(nomfich);
            fichier = creer_agenda(nomfich);
            afficher_agenda_actuel(nomfich);
            break;

        case 3:
            if (fichier == NULL)
            {
                printf("Erreur : aucun agenda n'est ouvert.\n");
            }
            else
            {
                creer_enregistrements(fichier);
                afficher_agenda_actuel(nomfich);
            }
            break;

        case 4:
            if (fichier == NULL)
            {
                printf("Erreur : aucun agenda n'est ouvert.\n");
            }
            else
            {
                lire_par_nom(fichier);
                afficher_agenda_actuel(nomfich);
            }
            break;

        case 5:
            if (fichier == NULL)
            {
                printf("Erreur : aucun agenda n'est ouvert.\n");
            }
            else
            {
                lire_par_numero(fichier);
                afficher_agenda_actuel(nomfich);
            }
            break;

        case 6:
            if (fichier == NULL)
            {
                printf("Erreur : aucun agenda n'est ouvert.\n");
            }
            else
            {
                afficher_les_enregistrements(fichier);
                afficher_agenda_actuel(nomfich);
            }
            break;

        case 7:
            if (fichier != NULL)
            {
                fclose(fichier);
                fichier = NULL;
                printf("Agenda fermé.\n");
            }
            else
            {
                printf("Erreur : aucun agenda n'est ouvert.\n");
            }
            break;

        case 8:
            if (fichier != NULL)
            {
                fclose(fichier);
            }
            printf("Au revoir !\n");
            break;

        default:
            printf("Choix invalide. Veuillez réessayer.\n");
            break;
        }

    } while (choix != 8);

    return 0;
}
