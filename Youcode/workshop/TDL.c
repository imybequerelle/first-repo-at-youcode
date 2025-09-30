#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

// Structure pour un collaborateur
struct Collaborator {
    char nom[50];
    char prenom[50];
    char email[100];
};

// Structure pour une tache de todo
struct Todo {
    int id;
    char title[100];
    char description[200];
    char deadline[20]; // JJ/MM/AAAA
    char creation_date[20];
    bool status; // true = complete, false = incomplete
    struct Collaborator collaborators[10]; // max 10
    int collab_count;
};

void get_current_date(char *date) {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    sprintf(date, "%02d/%02d/%04d", tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900);
}

int days_remaining(char *deadline) {
    struct tm tm = {0};
    sscanf(deadline, "%d/%d/%d", &tm.tm_mday, &tm.tm_mon, &tm.tm_year);
    tm.tm_mon--; tm.tm_year -= 1900;

    return (mktime(&tm) - time(NULL)) / 86400;
}

void bubbleSortByTitle(struct Todo arr[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (strcmp(arr[j].title, arr[j + 1].title) > 0) {
                struct Todo tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
}

void bubbleSortByTitle(struct Todo arr[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (strcmp(arr[j].title, arr[j + 1].title) > 0) {
                struct Todo t = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = t;
            }
}


// Fonction qui ajoute une nouvelle tache

void add_task(struct Todo *todos, int *count, int *id)
{
    struct Todo *t = &todos[(*count)++];
    t->id = (*id)++;
    get_current_date(t->creation_date);
    t->status = false;

    printf("Titre: ");           scanf(" %[^\n]", t->title);
    printf("Description: ");     scanf(" %[^\n]", t->description);
    printf("Deadline: ");        scanf("%s", t->deadline);
    printf("Collaborateurs: ");  scanf("%d", &t->collab_count);

    for (int i = 0; i < t->collab_count; i++) {
        scanf("%s %s %s", t->collaborators[i].prenom,t->collaborators[i].nom,t->collaborators[i].email);
    }
}

// Fonction pour afficher le menu
void display_menu() {
    printf("\n ******* Gestion des Taches ToDo ******* \n");
    printf("1. Ajouter une nouvelle tache \n");
    printf("2. Ajouter plusieurs nouvelles taches \n");
    printf("3. Afficher la liste de toutes les taches \n");
    printf("4. Trier les taches par ordre alphabetique \n");
    printf("5. Trier les taches par deadline\n");
    printf("6. Afficher les taches dont le deadline est dans 3 jours ou moins \n");
    printf("7. Modifier une tache \n");
    printf("8. Supprimer une tache par identifiant \n");
    printf("9. Rechercher une tache par identifiant \n");
    printf("10. Rechercher une tache par titre \n");
    printf("11. Statistiques \n");
    printf("12. Sauvegarder les taches \n");
    printf("13. Charger les taches \n");
    printf("0. Quitter \n");
    printf("Choix : \n");
}

void add_task(struct Todo **todos, int *count, int *next_id) {
    *todos = realloc(*todos, (*count + 1) * sizeof(struct Todo));
    struct Todo *t = &(*todos)[*count];

    t->id = (*next_id)++;
    printf("Titre: ");         scanf(" %[^\n]", t->title);
    printf("Description: ");   scanf(" %[^\n]", t->description);
    printf("Deadline (JJ/MM/AAAA): "); scanf("%s", t->deadline);

    get_current_date(t->creation_date);
    t->status = false;

    printf("Nombre de collaborateurs: ");
    scanf("%d", &t->collab_count);

    for (int i = 0; i < t->collab_count; i++) {
        printf("Collaborateur %d:\n", i + 1);
        printf("Prenom: "); scanf("%s", t->collaborators[i].prenom);
        printf("Nom: ");    scanf("%s", t->collaborators[i].nom);
        printf("Email: ");  scanf("%s", t->collaborators[i].email);
    }

    (*count)++;
    printf("Tache ajoutee avec ID %d\n", t->id);
}

void add_multiple_tasks(struct Todo **todos, int *count, int *next_id) {
    int n;
    printf("Combien de taches ? ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("\nTache %d:\n", i + 1);
        add_task(todos, count, next_id);
    }
}
