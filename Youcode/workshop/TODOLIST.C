#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

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

// Fonction pour obtenir la date actuelle
void get_current_date(char *date_str) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(date_str, "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

// Fonction pour calculer les jours restants jusqu'à la deadline
int days_remaining(char *deadline) {
    struct tm tm_dead = {0};
    sscanf(deadline, "%d/%d/%d", &tm_dead.tm_mday, &tm_dead.tm_mon, &tm_dead.tm_year);
    tm_dead.tm_mon -= 1;
    tm_dead.tm_year -= 1900;
    time_t t_dead = mktime(&tm_dead);
    time_t t_now = time(NULL);
    double diff = difftime(t_dead, t_now);
    return diff / (60 * 60 * 24);
}

// Fonction pour trier par bulle selon le titre
void bubbleSortByTitle(struct Todo arr[], int n) {
    int i, j;
    struct Todo temp;
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (strcmp(arr[j].title, arr[j+1].title) > 0) {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

// Fonction pour trier par deadline
void bubbleSortByDeadline(struct Todo arr[], int n) {
    int i, j;
    struct Todo temp;
    for (i = 0; i < n-1; i++) {
        for (j = 0; j < n-i-1; j++) {
            if (strcmp(arr[j].deadline, arr[j+1].deadline) > 0) {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

// Fonction pour afficher le menu
void display_menu() {
    printf("\n=== Gestion de Taches ToDo ===\n");
    printf("1. Ajouter une nouvelle tache\n");
    printf("2. Ajouter plusieurs nouvelles taches\n");
    printf("3. Afficher la liste de toutes les taches\n");
    printf("4. Trier les taches par ordre alphabetique\n");
    printf("5. Trier les taches par deadline\n");
    printf("6. Afficher les taches dont le deadline est dans 3 jours ou moins\n");
    printf("7. Modifier une tache\n");
    printf("8. Supprimer une tache par identifiant\n");
    printf("9. Rechercher une tache par identifiant\n");
    printf("10. Rechercher une tache par titre\n");
    printf("11. Statistiques\n");
    printf("12. Sauvegarder les taches\n");
    printf("13. Charger les taches\n");
    printf("0. Quitter\n");
    printf("Choix: ");
}

// Fonction pour ajouter une tache
void add_task(struct Todo **todos, int *count, int *next_id) {
    *todos = (struct Todo*) realloc(*todos, (*count + 1) * sizeof(struct Todo));
    struct Todo *new_task = &(*todos)[*count];
    new_task->id = *next_id;
    (*next_id)++;
    printf("Titre: ");
    scanf(" %[^\n]", new_task->title);
    printf("Description: ");
    scanf(" %[^\n]", new_task->description);
    printf("Deadline (JJ/MM/AAAA): ");
    scanf("%s", new_task->deadline);
    get_current_date(new_task->creation_date);
    new_task->status = false;
    printf("Nombre de collaborateurs: ");
    scanf("%d", &new_task->collab_count);
    for (int i = 0; i < new_task->collab_count; i++) {
        printf("Collaborateur %d:\n", i+1);
        printf("Prenom: ");
        scanf("%s", new_task->collaborators[i].prenom);
        printf("Nom: ");
        scanf("%s", new_task->collaborators[i].nom);
        printf("Email: ");
        scanf("%s", new_task->collaborators[i].email);
    }
    (*count)++;
    printf("Tache ajoutee avec ID %d\n", new_task->id);
}

// Fonction pour ajouter plusieurs taches
void add_multiple_tasks(struct Todo **todos, int *count, int *next_id) {
    int num;
    printf("Nombre de taches a ajouter: ");
    scanf("%d", &num);
    for (int i = 0; i < num; i++) {
        printf("\nTache %d:\n", i+1);
        add_task(todos, count, next_id);
    }
}

// Fonction pour afficher toutes les taches
void display_tasks(struct Todo *todos, int count) {
    if (count == 0) {
        printf("Aucune tache.\n");
        return;
    }
    printf("\nListe des taches:\n");
    for (int i = 0; i < count; i++) {
        printf("ID: %d\nTitre: %s\nDescription: %s\nDeadline: %s\nCreation: %s\nStatut: %s\nCollaborateurs: %d\n\n",
               todos[i].id, todos[i].title, todos[i].description, todos[i].deadline,
               todos[i].creation_date, todos[i].status ? "Complete" : "Incomplete", todos[i].collab_count);
    }
}

// Fonction pour afficher taches dues dans 3 jours
void display_due_soon(struct Todo *todos, int count) {
    printf("\nTaches dues dans 3 jours ou moins:\n");
    bool found = false;
    for (int i = 0; i < count; i++) {
        int days = days_remaining(todos[i].deadline);
        if (days <= 3 && days >= 0) {
            printf("ID: %d, Titre: %s, Deadline: %s, Jours restants: %d\n",
                   todos[i].id, todos[i].title, todos[i].deadline, days);
            found = true;
        }
    }
    if (!found) printf("Aucune tache trouvee.\n");
}

// Fonction pour modifier une tache
void modify_task(struct Todo *todos, int count) {
    int id;
    printf("ID de la tache a modifier: ");
    scanf("%d", &id);
    for (int i = 0; i < count; i++) {
        if (todos[i].id == id) {
            printf("1. Modifier description\n2. Modifier statut\n3. Modifier deadline\nChoix: ");
            int choice;
            scanf("%d", &choice);
            if (choice == 1) {
                printf("Nouvelle description: ");
                scanf(" %[^\n]", todos[i].description);
            } else if (choice == 2) {
                printf("Statut (0=Incomplete, 1=Complete): ");
                scanf("%d", &todos[i].status);
                if (todos[i].status && todos[i].collab_count > 0) {
                    printf("Collaborateur qui a effectue la tache (index 0-%d): ", todos[i].collab_count - 1);
                    int idx;
                    scanf("%d", &idx);
                    if (idx >= 0 && idx < todos[i].collab_count) {
                        printf("Tache finalisee par %s %s (%s)\n",
                               todos[i].collaborators[idx].prenom, todos[i].collaborators[idx].nom, todos[i].collaborators[idx].email);
                    }
                }
            } else if (choice == 3) {
                printf("Nouvelle deadline: ");
                scanf("%s", todos[i].deadline);
            }
            return;
        }
    }
    printf("Tache non trouvee.\n");
}

// Fonction pour supprimer une tache
void delete_task(struct Todo **todos, int *count) {
    int id;
    printf("ID de la tache a supprimer: ");
    scanf("%d", &id);
    for (int i = 0; i < *count; i++) {
        if ((*todos)[i].id == id) {
            for (int j = i; j < *count - 1; j++) {
                (*todos)[j] = (*todos)[j+1];
            }
    *todos = (struct Todo*) realloc(*todos, (*count - 1) * sizeof(struct Todo));
            (*count)--;
            printf("Tache supprimee.\n");
            return;
        }
    }
    printf("Tache non trouvee.\n");
}

// Fonction pour rechercher par ID
void search_by_id(struct Todo *todos, int count) {
    int id;
    printf("ID: ");
    scanf("%d", &id);
    for (int i = 0; i < count; i++) {
        if (todos[i].id == id) {
            printf("Titre: %s\nDescription: %s\nDeadline: %s\nStatut: %s\n", 
                   todos[i].title, todos[i].description, todos[i].deadline, todos[i].status ? "Complete" : "Incomplete");
            return;
        }
    }
    printf("Tache non trouvee.\n");
}

// Fonction pour rechercher par titre
void search_by_title(struct Todo *todos, int count) {
    char title[100];
    printf("Titre: ");
    scanf(" %[^\n]", title);
    bool found = false;
    for (int i = 0; i < count; i++) {
        if (strstr(todos[i].title, title) != NULL) {
            printf("ID: %d, Titre: %s, Description: %s, Deadline: %s, Statut: %s\n",
                   todos[i].id, todos[i].title, todos[i].description, todos[i].deadline, todos[i].status ? "Complete" : "Incomplete");
            found = true;
        }
    }
    if (!found) printf("Aucune tache trouvee.\n");
}

// Fonction pour statistiques
void statistics(struct Todo *todos, int count) {
    int total = count;
    int complete = 0, incomplete = 0;
    for (int i = 0; i < count; i++) {
        if (todos[i].status) complete++;
        else incomplete++;
        int days = days_remaining(todos[i].deadline);
        printf("Tache %d: %d jours restants\n", todos[i].id, days);
    }
    printf("Total taches: %d\nCompletes: %d\nIncompletes: %d\n", total, complete, incomplete);
}

// Fonction pour sauvegarder
void save_tasks(struct Todo *todos, int count) {
    FILE *f = fopen("tasks.dat", "wb");
    if (f == NULL) {
        printf("Erreur sauvegarde.\n");
        return;
    }
    fwrite(&count, sizeof(int), 1, f);
    fwrite(todos, sizeof(struct Todo), count, f);
    fclose(f);
    printf("Taches sauvegardees.\n");
}

// Fonction pour charger
void load_tasks(struct Todo **todos, int *count, int *next_id) {
    FILE *f = fopen("tasks.dat", "rb");
    if (f == NULL) {
        printf("Aucun fichier de sauvegarde.\n");
        return;
    }
    fread(count, sizeof(int), 1, f);
    *todos = (struct Todo*) realloc(*todos, *count * sizeof(struct Todo));
    fread(*todos, sizeof(struct Todo), *count, f);
    fclose(f);
    *next_id = (*count > 0) ? (*todos)[*count - 1].id + 1 : 1;
    printf("Taches chargees.\n");
}

int main() {
    struct Todo *todos = NULL;
    int count = 0;
    int next_id = 1;
    int choice;

    // Charger les taches au demarrage
    load_tasks(&todos, &count, &next_id);

    do {
        display_menu();
        scanf("%d", &choice);
        switch (choice) {
            case 1: add_task(&todos, &count, &next_id); break;
            case 2: add_multiple_tasks(&todos, &count, &next_id); break;
            case 3: display_tasks(todos, count); break;
            case 4: bubbleSortByTitle(todos, count); display_tasks(todos, count); break;
            case 5: bubbleSortByDeadline(todos, count); display_tasks(todos, count); break;
            case 6: display_due_soon(todos, count); break;
            case 7: modify_task(todos, count); break;
            case 8: delete_task(&todos, &count); break;
            case 9: search_by_id(todos, count); break;
            case 10: search_by_title(todos, count); break;
            case 11: statistics(todos, count); break;
            case 12: save_tasks(todos, count); break;
            case 13: load_tasks(&todos, &count, &next_id); break;
            case 0: printf("Au revoir!\n"); break;
            default: printf("Choix invalide.\n");
        }
    } while (choice != 0);

    free(todos);
    return 0;
}