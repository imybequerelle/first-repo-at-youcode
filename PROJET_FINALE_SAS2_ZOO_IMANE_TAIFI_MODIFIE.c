#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ANIMAUX 200
#define NOM_LEN 50
#define ESPECE_LEN 30
#define HABITAT_LEN 30
#define DATE_LEN 20

typedef struct {
    int id;
    char nom[NOM_LEN];
    char espece[ESPECE_LEN];
    int age;
    char habitat[HABITAT_LEN];
    double poids; // -1 si inconnu
    char date_arrivee[DATE_LEN]; // format YYYY-MM-DD
    int actif; // 1 = enregistre, 0 = supprimé
} Animal;

Animal zoo[MAX_ANIMAUX];
int count_animaux = 0;
int next_id = 1; //incremente les id

void press_enter_to_continue() {
    printf("\n Appuyez sur Entrée pour revenir au menu ");
    while (getchar() != '\n');
}

/* Initialisation avec 20 animaux pour tests */
void init_sample_data() {

    // Valeurs simples et variées
    struct {  int id;char *nom; char *espece; int age; char *habitat; double poids; }
    sample[20] = {

        {1,"Simba","Lion",5,"Savane",190.5},
        {2,"Nala","Lion",4,"Savane",175.0},
        {3,"Sherekhan","Tigre",8,"Jungle",220.3},
        {4,"Baloo","Ours",12,"Foret",310},
        {5,"Raja","Elephant",15,"Savane",540.7},
        {6,"Marty","Zebre",6,"savane",300.2},
        {7,"Gloria","Hippopotame",10,"Riviere",450.0},
        {8,"Alex","Lion",7,"Savane",200.0},
        {9,"Julien","Lémurien",3,"Jungle",12.5},
        {10,"Melman","Girafe",9,"savane",390.8},
        {11,"Timon","suricate",2,"Desert",1.2},
        {12,"Pumbaa","Phacochère",5,"Savane",120.0},
        {13,"Scar","Lion",11,"Savane",210.4},
        {14,"Kaa","Serpent",6,"Jungle",45.0},
        {15,"Iko","Perroquet",4,"Jungle",2.1},
        {16,"Dumbo","Elephant",3,"Savane",320.0},
        {17,"Kiki","Chien sauvage",7,"Savane",25.0},
        {18,"Donatello","Tortue",40,"Riviere",90.5},
        {19,"Polly","Oiseau",5,"Jungle",1.5},
        {20,"Kong","Gorille",13,"Jungle",180.0}

    };

    for (int i = 0; i < 20; ++i) {
        if (count_animaux >= MAX_ANIMAUX) break;
        Animal a;
        a.id = next_id++;
        strncpy(a.nom, sample[i].nom, NOM_LEN);
        strncpy(a.espece, sample[i].espece, ESPECE_LEN);
        a.age = sample[i].age;
        strncpy(a.habitat, sample[i].habitat, HABITAT_LEN);
        a.poids = sample[i].poids;
        a.actif = 1;
        zoo[count_animaux++] = a;
    }
}

/* Fonctions et utilitaires */
void ajouter_un_animal() {
    if (count_animaux >= MAX_ANIMAUX) {
        printf("Capacite maximale atteinte.\n");
        return;
    }
    Animal a;
    a.id = next_id++;
    printf("Nom: ");
    fgets(a.nom, NOM_LEN, stdin);
    a.nom[strcspn(a.nom, "\n")] = '\0';
    printf("Espece: ");
    fgets(a.espece, ESPECE_LEN, stdin);
    a.espece[strcspn(a.espece, "\n")] = '\0';
    printf("Age (entier): ");
    scanf("%d", &a.age);
    getchar();
    printf("Habitat: ");
    fgets(a.habitat, HABITAT_LEN, stdin);
    a.habitat[strcspn(a.habitat, "\n")] = '\0';
    printf("Poids (entre 0 et pour inconnu mettre -1): ");
    scanf("%lf", &a.poids);
    getchar();
    a.actif = 1;
    zoo[count_animaux++] = a;
    printf("Animal ajoute avec id %d \n", a.id);
}

void ajouter_plusieurs_animaux() {
    int n;
    printf("Combien d'animaux à ajouter ? ");
    if (scanf("%d", &n) != 1) { getchar(); printf("Entree invalide.\n"); return; }
    getchar();
    for (int i = 0; i < n; ++i) {
        printf("\n--- Animal %d ---\n", i+1);
        ajouter_un_animal();
    }
}

//comparaison du nom et de l'age
int cmp_nom(const void *p1, const void *p2) {
    Animal *a = (Animal*)p1;
    Animal *b = (Animal*)p2;
    return strcasecmp(a->nom, b->nom);
}
int cmp_age(const void *p1, const void *p2) {
    Animal *a = (Animal*)p1;
    Animal *b = (Animal*)p2;
    return a->age - b->age;
}

void afficher_animal_line(const Animal *a) {
    printf("ID: %d\n", a->id);
    printf("Nom: %s\n", a->nom);
    printf("Espèce: %s\n", a->espece);
    printf("Âge: %d\n", a->age);
    printf("Habitat: %s\n", a->habitat);
    if (a->poids < 0)
        printf("Poids: Inconnu\n");
    else
        printf("Poids: %.1f kg\n", a->poids);
    printf("Date d'arrivée: %s\n", a->date_arrivee);
    printf("------------------------ \n");
}

void afficher_tous_les_animaux() {
    if (count_animaux == 0) { printf("Aucun animal.\n"); return; }
    for (int i = 0; i < count_animaux; ++i) {
        if (zoo[i].actif) afficher_animal_line(&zoo[i]);
    }
}

void afficher_trie_par_nom() {
    Animal copie[MAX_ANIMAUX];
    int n = 0;
    for (int i = 0; i < count_animaux; ++i) if (zoo[i].actif) copie[n++] = zoo[i];
    qsort(copie, n, sizeof(Animal), cmp_nom);
    for (int i = 0; i < n; ++i) afficher_animal_line(&copie[i]);
}

void afficher_trie_par_age() {
    Animal copie[MAX_ANIMAUX];
    int n = 0;
    for (int i = 0; i < count_animaux; ++i) if (zoo[i].actif) copie[n++] = zoo[i];
    qsort(copie, n, sizeof(Animal), cmp_age);
    for (int i = 0; i < n; ++i) afficher_animal_line(&copie[i]);
}

void afficher_par_habitat() {
    char habitat[HABITAT_LEN];
    printf("Entrer habitat recherche: ");
    fgets(habitat, HABITAT_LEN, stdin);
    habitat[strcspn(habitat, "\n")] = '\0';
    int found = 0;
    for (int i = 0; i < count_animaux; ++i) {
        if (zoo[i].actif && strcasecmp(zoo[i].habitat, habitat) == 0) {
            afficher_animal_line(&zoo[i]);
            found = 1;
        }
    }
    if (!found) printf("Aucun animal pour cet habitat.\n");
}

/* Modifier */
Animal* find_by_id(int id) {
    for (int i = 0; i < count_animaux; ++i) if (zoo[i].actif && zoo[i].id == id) return &zoo[i];
    return NULL;
}

void modifier_habitat() {
    int id;
    printf("ID de l'animal a modifier habitat: ");
    if (scanf("%d", &id) != 1) { getchar(); printf("Entree invalide.\n"); return; }
    getchar();
    Animal *a = find_by_id(id);
    if (!a) { printf("Animal introuvable.\n"); return; }
    printf("Habitat actuel: %s\n", a->habitat);
    printf("Nouveau habitat: ");
    char h[HABITAT_LEN];
    fgets(h, HABITAT_LEN, stdin);
    h[strcspn(h, "\n")] = '\0';
    strncpy(a->habitat, h, HABITAT_LEN);
    printf("Habitat mis a jour.\n");
}

void modifier_age() {
    int id;
    printf("ID de l'animal a modifier age: ");
    if (scanf("%d", &id) != 1) { getchar(); printf("Entree invalide.\n"); return; }
    getchar();
    Animal *a = find_by_id(id);
    if (!a) { printf("Animal introuvable.\n"); return; }
    printf("Age actuel: %d\n", a->age);
    int newage;
    printf("Nouvel age: ");
    if (scanf("%d", &newage) != 1) { getchar(); printf("Entree invalide.\n"); return; }
    getchar();
    a->age = newage;
    printf("Age mis a jour.\n");
}

/* Supprimer */
void supprimer_animal() {
    int id;
    printf("ID de l'animal a supprimer: ");
    if (scanf("%d", &id) != 1) { getchar(); printf("Entree invalide.\n"); return; }
    getchar();
    Animal *a = find_by_id(id);
    if (!a) { printf("Animal introuvable.\n"); return; }
    a->actif = 0;
    printf("Animal supprime.\n");
}

/* Rechercher */
void rechercher_par_id() {
    int id;
    printf("ID recherche: ");
    if (scanf("%d", &id) != 1) { getchar(); printf("Entree invalide.\n"); return; }
    getchar();
    Animal *a = find_by_id(id);
    if (a) afficher_animal_line(a); else printf("Introuvable.\n");
}

void rechercher_par_nom() {
    char nom[NOM_LEN];
    printf("Nom recherche: ");
    fgets(nom, NOM_LEN, stdin);
    nom[strcspn(nom, "\n")] = '\0';
    int found = 0;
    for (int i = 0; i < count_animaux; ++i) {
        if (zoo[i].actif && strcasecmp(zoo[i].nom, nom) == 0) { afficher_animal_line(&zoo[i]); found = 1; }
    }
    if (!found) printf("Introuvable.\n");
}

void rechercher_par_espece() {
    char espece[ESPECE_LEN];
    printf("Espece recherche: ");
    fgets(espece, ESPECE_LEN, stdin);
    espece[strcspn(espece, "\n")] = '\0';
    int found = 0;
    for (int i = 0; i < count_animaux; ++i) {
        if (zoo[i].actif && strcasecmp(zoo[i].espece, espece) == 0) { afficher_animal_line(&zoo[i]); found = 1; }
    }
    if (!found) printf("Introuvable.\n");
}

/* Statistiques */
void statistiques() {
    int total = 0;
    double somme_age = 0;
    int max_age = -1, min_age = 9999;
    Animal *plus_vieux = NULL, *plus_jeune = NULL;
    // Compter espèces
    typedef struct { char espece[ESPECE_LEN]; int cnt; } EspCount;
    EspCount freq[200];
    int freq_n = 0;

    for (int i = 0; i < count_animaux; ++i) {
        if (!zoo[i].actif) continue;
        total++;
        somme_age += zoo[i].age;
        if (zoo[i].age > max_age) { max_age = zoo[i].age; plus_vieux = &zoo[i]; }
        if (zoo[i].age < min_age) { min_age = zoo[i].age; plus_jeune = &zoo[i]; }
        int found = 0;
        for (int j = 0; j < freq_n; ++j) {
            if (strcasecmp(freq[j].espece, zoo[i].espece) == 0) { freq[j].cnt++; found = 1; break; }
        }
        if (!found) {
            strncpy(freq[freq_n].espece, zoo[i].espece, ESPECE_LEN);
            freq[freq_n].cnt = 1;
            freq_n++;
        }
    }

    printf("Nombre total d'animaux: %d\n", total);
    if (total > 0) {
        double age_moy = somme_age / total;
        printf("Age moyen: %.2f\n", age_moy);
        if (plus_vieux) { printf("Plus vieux: ID %d %s age %d\n", plus_vieux->id, plus_vieux->nom, plus_vieux->age); }
        if (plus_jeune) { printf("Plus jeune: ID %d %s age %d\n", plus_jeune->id, plus_jeune->nom, plus_jeune->age); }

        // Especes les plus representees
        // trier frequences par cnt decroissant simple selection
        for (int i = 0; i < freq_n - 1; ++i) {
            int sel = i;
            for (int j = i+1; j < freq_n; ++j) if (freq[j].cnt > freq[sel].cnt) sel = j;
            if (sel != i) { EspCount tmp = freq[i]; freq[i] = freq[sel]; freq[sel] = tmp; }
        }
        printf("Especes les plus representees:\n");
        for (int i = 0; i < freq_n && i < 5; ++i) {
            printf("  %s : %d\n", freq[i].espece, freq[i].cnt);
        }
    }
}

/* Menu principal et sous-menus */
void menu_afficher() {
    while (1) {
        printf("\n--- Afficher les animaux ---\n");
        printf("1. Liste complete\n2. Trier par nom\n3. Trier par age\n4. Afficher par habitat\n5. Retour\nChoix: ");
        int c; if (scanf("%d", &c) != 1) { getchar(); printf("Entree invalide.\n"); continue; }
        getchar();
        switch (c) {
            case 1: afficher_tous_les_animaux(); break;
            case 2: afficher_trie_par_nom(); break;
            case 3: afficher_trie_par_age(); break;
            case 4: afficher_par_habitat(); break;
            case 5: return;
            default: printf("Option invalide.\n"); break;
        }
    }
}

void menu_rechercher() {
    while (1) {
        printf("\n--- Rechercher ---\n1. Par ID\n2. Par nom\n3. Par espece\n4. Retour\nChoix: ");
        int c; if (scanf("%d", &c) != 1) { getchar(); printf("Entree invalide.\n"); continue; }
        getchar();
        switch (c) {
            case 1: rechercher_par_id(); break;
            case 2: rechercher_par_nom(); break;
            case 3: rechercher_par_espece(); break;
            case 4: return;
            default: printf("Option invalide.\n"); break;
        }
    }
}   

/************************************************************************** MAIN *************************************************************************************************/

int main() {

    init_sample_data();

    while (1) {
        printf("\n====== Gestion Zoo ======\n");
        printf("1. Ajouter un animal \n 2. Afficher les animaux \n 3. Modifier un animal \n 4. Supprimer un animal \n 5. Rechercher un animal \n 6. Statistiques \n 7. Quitter \n   Choix: ");
        int choix;
        if (scanf("%d", &choix) != 1) {
            getchar();
            printf(" Entree invalide \n");
            continue;
        }
        getchar(); // pour consommer le \n
        switch (choix) {
            case 1: {
                printf("1. Ajouter un seul\n2. Ajouter plusieurs\nChoix: ");
                int c;
                if (scanf("%d", &c) != 1) {
                    getchar();
                    printf(" Entree invalide \n");
                    break;
                }
                getchar();
                if (c == 1) ajouter_un_animal();
                else if (c == 2) ajouter_plusieurs_animaux();
                else printf(" Option invalide \n");
                break;
            }
            case 2: menu_afficher(); break;
            case 3: {
                printf("1. Modifier habitat\n2. Modifier age\nChoix: ");
                int c;
                if (scanf("%d", &c) != 1) {
                    getchar();
                    printf(" Entree invalide \n");
                    break;
                }
                getchar();
                if (c == 1) modifier_habitat();
                else if (c == 2) modifier_age();
                else printf(" Option invalide \n");
                break;
            }
            case 4: supprimer_animal(); break;
            case 5: menu_rechercher(); break;
            case 6: statistiques(); break;
            case 7:
                printf(" Au revoir \n");
                return 0;
            default:
                printf(" Option invalide! \n");
                break;
        }
        press_enter_to_continue();
    }
    return 0;
}