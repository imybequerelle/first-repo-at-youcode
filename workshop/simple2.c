#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#define MAX 100

typedef struct {
    int id;
    char titre[100];
    char desc[200];
    char deadline[20]; // JJ/MM/AAAA
    char creation[20];
    bool status;
} Tache;

Tache liste[MAX];
int total = 0, next_id = 1;

void date_actuelle(char *str) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(str, "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

void ajouter() {
    if (total>= MAX) return;
    Tache *t = &liste[total];
    t->id = next_id++;
    printf("Titre: "); getchar(); fgets(t->titre, 100, stdin);
    t->titre[strcspn(t->titre, "\n")] = '\0';
    printf("Description: "); fgets(t->desc, 200, stdin);
    t->desc[strcspn(t->desc, "\n")] = '\0';
    printf("Deadline (JJ/MM/AAAA): "); scanf("%s", t->deadline);
    date_actuelle(t->creation);
    t->status = false;
    total++;
    printf(" Tâche ajoutée.\n");
}

void afficher() {
    if (total == 0) { printf("📭 Aucune tâche.\n"); return;}
    for (int i = 0; i < total; i++) {
        Tache t = liste[i];
        printf("\nID: %d\nTitre: %s\nDesc: %s\nDeadline: %s\nCréée: %s\nStatut: %s\n",
               t.id, t.titre, t.desc, t.deadline, t.creation, t.status? "Complète": "Incomplète");
}
}

void modifier() {
    int id, choix;
    printf("ID à modifier: "); scanf("%d", &id);
    for (int i = 0; i < total; i++) {
        if (liste[i].id == id) {
            printf("1. Description\n2. Statut\n3. Deadline\nChoix: ");
            scanf("%d", &choix); getchar();
            if (choix == 1) {
                printf("Nouvelle description: "); fgets(liste[i].desc, 200, stdin);
                liste[i].desc[strcspn(liste[i].desc, "\n")] = '\0';
} else if (choix == 2) {
                printf("Statut (0/1): "); scanf("%d", &liste[i].status);
} else if (choix == 3) {
                printf("Nouvelle deadline: "); scanf("%s", liste[i].deadline);
}
            return;
}
}
    printf(" Tâche non trouvée.\n");
}

void supprimer() {
    int id;
    printf("ID à supprimer: "); scanf("%d", &id);
    for (int i = 0; i < total; i++) {
        if (liste[i].id == id) {
            for (int j = i; j < total - 1; j++)
                liste[j] = liste[j + 1];
            total--;
            printf(" Tâche supprimée.\n");
            return;
}
}
    printf(" Tâche non trouvée.\n");
}

void trier() {
    for (int i = 0; i < total - 1; i++) {
        for (int j = 0; j < total - i - 1; j++) {
            if (strcmp(liste[j].titre, liste[j + 1].titre)> 0) {
                Tache tmp = liste[j];
                liste[j] = liste[j + 1];
                liste[j + 1] = tmp;
}
}
}
    printf(" Tâches triées par titre.\n");
}

void sauvegarder() {
    FILE *f = fopen("taches.dat", "wb");
    if (!f) { printf(" Erreur de sauvegarde.\n"); return;}
    fwrite(&total, sizeof(int), 1, f);
    fwrite(&next_id, sizeof(int), 1, f);
    fwrite(liste, sizeof(Tache), total, f);
    fclose(f);
    printf("💾 Tâches sauvegardées.\n");
}

void charger() {
    FILE *f = fopen("taches.dat", "rb");
    if (!f) { printf(" Aucun fichier trouvé.\n"); return;}
    fread(&total, sizeof(int), 1, f);
    fread(&next_id, sizeof(int), 1, f);
    fread(liste, sizeof(Tache), total, f);
    fclose(f);
    printf(" Tâches chargées.\n");
}

int main() {
    int choix;
    charger();
    do {
        printf("\n Menu:\n1. Ajouter\n2. Afficher\n3. Modifier\n4. Supprimer\n5. Trier\n6. Sauvegarder\n0. Quitter\nChoix: ");
        scanf("%d", &choix);
        switch (choix) {
            case 1: ajouter(); break;
            case 2: afficher(); break;
            case 3: modifier(); break;
            case 4: supprimer(); break;
            case 5: trier(); break;
            case 6: sauvegarder(); break;
            case 0: printf(" Au revoir!\n"); break;
            default: printf(" Choix invalide.\n");
}
} while (choix!= 0);
    return 0;
}