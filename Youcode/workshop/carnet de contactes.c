#include<stdio.h>
#include<string.h>

//structure affichant un contact
struct contact 
{
    char nom[100];
    char numero_de_telephone[100];
    char email[100];
};

//tableau de contacts
struct contact contacts[100];
int nombre_de_contacts = 0;
void afficher_contacts() {
    int i;
    for(i = 0; i < nombre_de_contacts; i++) 
    {
        printf("Contact %d: %s, %s, %s\n", i + 1, contacts[i].nom, contacts[i].numero_de_telephone, contacts[i].email);
    }
}

//modifier contact
void modifier_contact(char nom[]) {
    int i;

    for(i = 0; i < nombre_de_contacts; i++) {
        if(strcmp(contacts[i].nom, nom) == 0) {
            printf("Entrer le nouveau numero de telephone : ");
            fgets(contacts[i].numero_de_telephone, sizeof(contacts[i].numero_de_telephone), stdin);
            printf("Entrer le nouvel email : ");
            fgets(contacts[i].email, sizeof(contacts[i].email), stdin);
            printf("Contact modifié avec succes!\n");
            return;
        }
    }
    printf("Contact non trouvé!\n");
}

//supprimer contact
void supprimer_contact(char nom[]) {
    int i, j;

    for(i = 0; i < nombre_de_contacts; i++) {
        if(strcmp(contacts[i].nom, nom) == 0) {
            for(j = i; j < nombre_de_contacts - 1; j++) {
                contacts[j] = contacts[j + 1];
            }
            nombre_de_contacts--;
            printf("Contact supprimé avec succes!\n");
            return;
        }
    }
    printf("Contact non trouvé!\n");
}

//affiche tous les contacts
void afficher_tous_les_contacts() {
    int i;
    for(i = 0; i < nombre_de_contacts; i++) {
        printf("Contact %d: %s, %s, %s\n", i + 1, contacts[i].nom, contacts[i].numero_de_telephone, contacts[i].email);
    }
}

//recherche un contact
void recherche_contact(char nom[]) {
    int i, trouve = 0;

    for(i = 0; i < nombre_de_contacts; i++) {
        if(strcmp(contacts[i].nom, nom) == 0) {
            printf("Contact trouvé: %s, %s, %s\n", contacts[i].nom, contacts[i].numero_de_telephone, contacts[i].email);
            trouve = 1;
            break;
        }
    }
    if(!trouve) {
        printf("Contact non trouvé!\n");
    }
}
/*************************************************************************************************************************/
int main()
{
    int choix;
    struct contact c;

    do {
        printf("entrer votre choix :\n");
        printf("1. ajouter un contact\n");
        printf("2. modifier un contact\n");
        printf("3. supprimer un contact\n");
        printf("4. afficher tous les contacts\n");  
        printf("5. rechercher un contact\n");
        printf("6. quitter\n");
        scanf("%d", &choix);
        getchar();

        switch (choix)
        {
            case 1: //ajouter un contact
                printf("entrer le nom :");
                fgets(c.nom, sizeof(c.nom), stdin);
                printf("entrer le numero de telephone :");
                fgets(c.numero_de_telephone, sizeof(c.numero_de_telephone), stdin);
                printf("entrer l'email :");
                fgets(c.email, sizeof(c.email), stdin);
                printf("le contact est : %s %s %s",c.nom,c.numero_de_telephone,c.email);
                // Ajouter le contact au tableau
                contacts[nombre_de_contacts++] = c;
                break;

            case 2: //modifier un contact
                {
                    char nom[100];
                    printf("Entrer le nom du contact a modifier : ");
                    fgets(nom, sizeof(nom), stdin);
                    nom[strcspn(nom, "\n")] = 0; // enlever le saut de ligne
                    modifier_contact(nom);
                }
                break;

            case 3:
                // supprimer un contact
                {
                    char nom[100];
                    printf("Entrer le nom du contact a supprimer : ");
                    fgets(nom, sizeof(nom), stdin);
                    nom[strcspn(nom, "\n")] = 0; // enlever le saut de ligne
                    supprimer_contact(nom);
                }
                break;

            case 4:
                // afficher tous les contacts
                afficher_contacts();
                break;

            case 5:
                // rechercher un contact
                {
                    char nom[100];
                    int i, trouve = 0;
                    printf("Entrer le nom du contact a rechercher : ");
                    fgets(nom, sizeof(nom), stdin);
                    nom[strcspn(nom, "\n")] = 0; // enlever le saut de ligne

                    for(i = 0; i < nombre_de_contacts; i++) {
                        if(strcmp(contacts[i].nom, nom) == 0) {
                            printf("Contact trouvé: %s, %s, %s\n", contacts[i].nom, contacts[i].numero_de_telephone, contacts[i].email);
                            trouve = 1;
                            break;
                        }
                    }
                    if(!trouve) {
                        printf("Contact non trouvé!\n");
                    }
                }
                break;

            case 6:
                printf("Au revoir!\n");
                break;

            default:
                printf("Choix invalide! \n");
                break;
        }
    } 
    while (choix != 6);
    return 0;
}