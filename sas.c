#include <stdio.h>                                  
#include <stdlib.h>
#include <string.h>

 #define MAX_ANIMAUX 200
 #define NOM_LEN 50
 #define ESPECE_LEN 30
 #define HABITAT_LEN 30
 
typedef struct {
    int id;
    char nom[NOM_LEN];
    char espece[ESPECE_LEN];
    int age;
    char habitat[HABITAT_LEN];
    double poids;
    int actif;
} Animal;

Animal zoo[MAX_ANIMAUX];
int count_animaux = 0;
int next_id = 1;

void pause() {
    printf("\n Appuyez sur Entrée pour continuer...");
    while (getchar() != '\n');
}

void init_sample_data() {
    char *noms[] = {"Simba","Nala","Sherekhan","Baloo","Raja","Marty","Gloria","Alex","Julien","Melman",
                    "Timon","Pumbaa","Scar","Kaa","Iko","Dumbo","Kiki","Donatello","Polly","Kong"};
    char *especes[] = {"Lion","Lion","Tigre","Ours","Elephant","Zebre","Hippopotame","Lion","Lémurien","Girafe",
                       "Suricate","Phacochère","Lion","Serpent","Perroquet","Elephant","Chien sauvage","Tortue","Oiseau","Gorille"};
    int ages[] = {5,4,8,12,15,6,10,7,3,9,2,5,11,6,4,3,7,40,5,13};
    char *habitats[] = {"Savane","Savane","Jungle","Foret","Savane","Savane","Riviere","Savane","Jungle","Savane",
                        "Desert","Savane","Savane","Jungle","Jungle","Savane","Savane","Riviere","Jungle","Jungle"};
    double poids[] = {190.5,175.0,220.3,310,540.7,300.2,450.0,200.0,12.5,390.8,
                      1.2,120.0,210.4,45.0,2.1,320.0,25.0,90.5,1.5,180.0};

    for (int i = 0; i < 20; i++) {
        Animal a;
        a.id = next_id++;
        strncpy(a.nom, noms[i], NOM_LEN);
        strncpy(a.espece, especes[i], ESPECE_LEN);
        a.age = ages[i];
        strncpy(a.habitat, habitats[i], HABITAT_LEN);
        a.poids = poids[i];
        a.actif = 1;
        zoo[count_animaux++] = a;
    }
}

void afficher_animal(const Animal *a) {
    printf("ID: %d | Nom: %s | Espece: %s | Age: %d | Habitat: %s | Poids: %.1f\n",
           a->id, a->nom, a->espece, a->age, a->habitat, a->poids < 0 ? 0 : a->poids);
}

void afficher_tous() {
    for (int i = 0; i < count_animaux; i++)
        if (zoo[i].actif) afficher_animal(&zoo[i]);
}

int cmp_nom(const void *a, const void *b) {
    return strcasecmp(((Animal*)a)->nom, ((Animal*)b)->nom);
}
int cmp_age(const void *a, const void *b) {
    return ((Animal*)a)->age - ((Animal*)b)->age;
}

void afficher_trie(int (*cmp)(const void*, const void*)) {
    Animal temp[MAX_ANIMAUX];
    int n = 0;
    for (int i = 0; i < count_animaux; i++)
        if (zoo[i].actif) temp[n++] = zoo[i];
    qsort(temp, n, sizeof(Animal), cmp);
    for (int i = 0; i < n; i++) afficher_animal(&temp[i]);
}

void ajouter_animal() {
    if (count_animaux >= MAX_ANIMAUX) { printf("Zoo plein.\n"); return; }
    Animal a;
    a.id = next_id++;
    printf("Nom: "); fgets(a.nom, NOM_LEN, stdin); a.nom[strcspn(a.nom, "\n")] = 0;
    printf("Espece: "); fgets(a.espece, ESPECE_LEN, stdin); a.espece[strcspn(a.espece, "\n")] = 0;
    printf("Age: "); scanf("%d", &a.age); getchar();
    printf("Habitat: "); fgets(a.habitat, HABITAT_LEN, stdin); a.habitat[strcspn(a.habitat, "\n")] = 0;
    printf("Poids: "); scanf("%lf", &a.poids); getchar();
    a.actif = 1;
    zoo[count_animaux++] = a;
    printf("Ajouté avec ID %d\n", a.id);
}

Animal* trouver_par_id(int id) {
    for (int i = 0; i < count_animaux; i++)
        if (zoo[i].actif && zoo[i].id == id) return &zoo[i];
    return NULL;
}

void modifier_animal() {
    int id;
    printf("ID à modifier: "); scanf("%d", &id); getchar();
    Animal *a = trouver_par_id(id);
    if (!a) { printf("Introuvable.\n"); return; }
    printf("1. Habitat\n2. Age\nChoix: ");
    int c; scanf("%d", &c); getchar();
    if (c == 1) {
        printf("Nouveau habitat: "); fgets(a->habitat, HABITAT_LEN, stdin); a->habitat[strcspn(a->habitat, "\n")] = 0;
    } else if (c == 2) {
        printf("Nouvel age: "); scanf("%d", &a->age); getchar();
    } else printf("Option invalide.\n");
}

void supprimer_animal() {
    int id;
    printf("ID à supprimer: "); scanf("%d", &id); getchar();
    Animal *a = trouver_par_id(id);
    if (a) { a->actif = 0; printf("Supprimé.\n"); }
    else printf("Introuvable.\n");
}

void rechercher() {
    printf("1. Par ID\n2. Par nom\n3. Par espece\nChoix: ");
    int c; scanf("%d", &c); getchar();
    if (c == 1) {
        int id; printf("ID: "); scanf("%d", &id); getchar();
        Animal *a = trouver_par_id(id);
        if (a) afficher_animal(a); else printf("Introuvable.\n");
    } else if (c == 2) {
        char nom[NOM_LEN]; printf("Nom: "); fgets(nom, NOM_LEN, stdin); nom[strcspn(nom, "\n")] = 0;
        int found = 0;
        for (int i = 0; i < count_animaux; i++)
            if (zoo[i].actif && strcasecmp(zoo[i].nom, nom) == 0) { afficher_animal(&zoo[i]); found = 1; }
        if (!found) printf("Introuvable.\n");
    } else if (c == 3) {
        char espece[ESPECE_LEN]; printf("Espece: "); fgets(espece, ESPECE_LEN, stdin); espece[strcspn(espece, "\n")] = 0;
        int found = 0;
        for (int i = 0; i < count_animaux; i++)
            if (zoo[i].actif && strcasecmp(zoo[i].espece, espece) == 0) { afficher_animal(&zoo[i]); found = 1; }
        if (!found) printf("Introuvable.\n");
    } else printf("Option invalide.\n");
}

void statistiques() {
    int total = 0, max_age = -1, min_age = 9999;
    double somme_age = 0;
    Animal *plus_vieux = NULL, *plus_jeune = NULL;
    for (int i = 0; i < count_animaux; i++) {
        if (!zoo[i].actif) continue;
        total++;
        somme_age += zoo[i].age;
        if (zoo[i].age > max_age) { max_age = zoo[i].age; plus_vieux = &zoo[i]; }
        if (zoo[i].age < min_age) { min_age = zoo[i].age; plus_jeune = &zoo[i]; }
    }
    printf("Total: %d\n", total);
    if (total) {
        printf("Age moyen: %.2f\n", somme_age / total);
        if (plus_vieux) printf("Plus vieux: %s (%d ans)\n", plus_vieux->nom, plus_vieux->age);
        if (plus_jeune) printf("Plus jeune: %s (%d ans)\n", plus_jeune->nom, plus_jeune->age);
    }
}

int main() {
    init_sample_data();
    while (1) {
        printf("\n=== MENU ZOO ===\n");
        printf("1. Ajouter un animal \n 2. Afficher un animal \n 3. Modifier un animal \n 4. Supprimer un animal \n 5. Rechercher un animal \n 6. Statistiques\n 7. Quitter \n Choix: ");
        int choix; scanf("%d", &choix); getchar();
        switch (choix) {
            case 1: ajouter_animal(); break;
            case 2: {
                printf("1. Tous\n2. Par nom\n3. Par age\nChoix: ");
                int c; scanf("%d", &c); getchar();
                if (c == 1) afficher_tous();
                else if (c == 2) afficher_trie(cmp_nom);
                else if (c == 3) afficher_trie(cmp_age);
                else printf("Option invalide.\n");
                break;
            }
            case 3: modifier_animal(); break;
            case 4: supprimer_animal(); break;
            case 5: rechercher(); break;
            case 6: statistiques(); break;
            case 7: printf("Au revoir!\n"); return 0;
            default: printf("Option invalide.\n"); break;
        }
        pause();
    }
    return 0;
}