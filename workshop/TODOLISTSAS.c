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

    // Fonction pour ajouter une tache
void add_task(struct Todo **todos, int *count, int *next_id) 
{
    *todos = realloc(*todos, (*count + 1) * sizeof(struct Todo));
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
    (*count)++;
    printf("Tache ajoutee avec ID %d\n", new_task->id);
}

// Ajouter plusieurs nouvelles taches
void display_tasks(struct Todo *todos, int count) {
    if (count == 0) {
        printf("Aucune tache.\n");
        return;
    }
    printf("\n Liste des taches:\n ");
    for (int i = 0; i < count; i++) {
        printf("ID: %d\nTitre: %s\nDescription: %s\nDeadline: %s\nCreation: %s\nStatut: %s\n\n",
               todos[i].id, todos[i].title, todos[i].description, todos[i].deadline,
               todos[i].creation_date, todos[i].status ? "Complete" : "Incomplete");
    }
}







// Fonction pour afficher le menu
void display_menu() {
    printf("\n=== Gestion de Taches ToDo ===\n");
    printf("1. Ajouter une tache\n");
    printf("2. Afficher toutes les taches\n");
    printf("3. Trier par titre\n");
    printf("4. Trier par deadline\n");
    printf("5. Taches dues bientot\n");
    printf("6. Modifier une tache\n");
    printf("7. Supprimer une tache\n");
    printf("8. Rechercher par ID\n");
    printf("9. Rechercher par titre\n");
    printf("10. Statistiques\n");
    printf("11. Sauvegarder\n");
    printf("12. Charger\n");
    printf("0. Quitter\n");
    printf("Choix: ");
}

/************************************************* Main : ****************************************************/
int main() {
    struct Todo *todos = NULL;            int next_id = 1;
    int count = 0;                        int choice;
   
    load_tasks(&todos, &count, &next_id);

    do {
        display_menu();
        scanf("%d", &choice);
        switch (choice) {
            case 1: add_task(&todos, &count, &next_id); break;
            case 2: display_tasks(todos, count); break;
            case 3: sort_by_title(todos, count); display_tasks(todos, count); break;
            case 4: sort_by_deadline(todos, count); display_tasks(todos, count); break;
            case 5: display_due_soon(todos, count); break;
            case 6: modify_task(todos, count); break;
            case 7: delete_task(&todos, &count); break;
            case 8: search_by_id(todos, count); break;
            case 9: search_by_title(todos, count); break;
            case 10: statistics(todos, count); break;
            case 11: save_tasks(todos, count); break;
            case 12: load_tasks(&todos, &count, &next_id); break;
            case 0: printf(" Au revoir ! \n"); break;
            default: printf(" Choix invalide! \n ");
        }
    } 
    while (choice != 0);
    free(todos);
    return 0;
}