#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ANIMAUX 200
#define TAILLE_NOM 50
#define TAILLE_ESPECE 30
#define TAILLE_HABITAT 30
#define TAILLE_DATE 20

// Structure de données de la catégorisation (carnivore/herbivore/omnivore)
typedef enum {
    CARNIVORE,HERBIVORE,OMNIVORE,INCONNU
} RegimeAlimentaire;

// Bloc du code qui Convertit une énumération de régime alimentaire en chaîne de caractères
char* regime_to_string(RegimeAlimentaire regime) {
    switch (regime) {
        case CARNIVORE: return "Carnivore";
        case HERBIVORE: return "Herbivore";
        case OMNIVORE: return "Omnivore";
        default: return "Inconnu";
    }
}

//Bloc du code qui Convertit une chaîne de caractères en énumération de régime alimentaire
 
RegimeAlimentaire string_to_regime(const char* s) {
    if (strcmp(s, "Carnivore") == 0) return CARNIVORE;
    if (strcmp(s, "Herbivore") == 0) return HERBIVORE;
    if (strcmp(s, "Omnivore") == 0) return OMNIVORE;
    return INCONNU;
}

// Structure de l'Animal
typedef struct {
    int id;
    char nom[TAILLE_NOM];
    char espece[TAILLE_ESPECE];
    int age;
    char habitat[TAILLE_HABITAT];
    float poids;   // Poids (réel, optionnel)
    char date_arrivee[TAILLE_DATE];
    RegimeAlimentaire regime; 
} Animal;

// Bloc du code qui incrémente les id
Animal zoo[MAX_ANIMAUX];
int nb_animaux = 0;
int next_id = 1; // Prochain ID unique à attribuer

//Bloc du code qui Génère un ID unique et incrémental.
 
int generer_id() {
    return next_id++;
}

// Déclarations des Fonctions utilisées :

void initialiser_zoo();
int generer_id();
void ajouter_animal_interactif();
void ajouter_animal_donnees(const char* nom, const char* espece, int age, const char* habitat, float poids, RegimeAlimentaire regime);
void afficher_menu_affichage();
void afficher_animaux(const Animal animaux[], int taille);
void trier_animaux_par_nom();
void trier_animaux_par_age();
void afficher_animaux_par_habitat();
void modifier_animal_menu();
void supprimer_animal();
void rechercher_animal_menu();
void afficher_statistiques();
void verifier_age_critique(const Animal* a); 
char* regime_to_string(RegimeAlimentaire regime);
RegimeAlimentaire string_to_regime(const char* s);
int comparer_noms(const void *a, const void *b);
int comparer_ages(const void *a, const void *b);
int trouver_index_par_id(int id);

//***Fonction qui Trouve l'index d'un animal dans le tableau par son ID. L'index de l'animal ou -1 si non trouvé
 
int trouver_index_par_id(int id) {
    for (int i = 0; i < nb_animaux; i++) {
        if (zoo[i].id == id) {
            return i;
        }
    }
    return -1;
}

//***Fonctions de Tri (tri rapide)
//***Fonction de comparaison pour trier par nom

int comparer_noms(const void *a, const void *b) {
    return strcmp(((Animal*)a)->nom, ((Animal*)b)->nom);
}

//***Fonction de comparaison pour trier par âge
 
int comparer_ages(const void *a, const void *b) {
    return ((Animal*)a)->age - ((Animal*)b)->age;
}

//Initialisation du Zoo
//Initialise le tableau du zoo (au moins 20 animaux)
 
void initialiser_zoo() {
    // Utilisation d'un tableau statique rempli pour simuler l'initialisation à partir de animaux.csv
    ajouter_animal_donnees("1","Simba","Lion",5,"Savane",190.5);
    ajouter_animal_donnees("2","Nala","Lion",4,"Savane",175.0);
    ajouter_animal_donnees("3","ShereKhan","Tigre",8,"Jungle",220.3);
    ajouter_animal_donnees("4","Baloo","Ours",12,"Forêt",310.0);
    ajouter_animal_donnees("5","Raja","Éléphant",15,"Savane",540.7);
    ajouter_animal_donnees("6","Marty","Zèbre",6,"Savane",300.2);
    ajouter_animal_donnees("7","Gloria","Hippopotame",10,"Rivière",450.0);
    ajouter_animal_donnees("8","Alex","Lion",7,"Savane",200.0);
    ajouter_animal_donnees("9","Julien","Lémurien",3,"Jungle",12.5);
    ajouter_animal_donnees("10","Melman","Girafe",9,"Savane",390.8);
    ajouter_animal_donnees("11","Timon","Suricate",2,"Désert",1.2);
    ajouter_animal_donnees("12","Pumbaa","Phacochère",5,"Savane",120.0);
    ajouter_animal_donnees("13","Scar","Lion",11,"Savane",210.4);
    ajouter_animal_donnees("14","Kaa","Serpent",6,"Jungle",45.0);
    ajouter_animal_donnees("15","Iko","Perroquet",4,"Jungle",2.1);
    ajouter_animal_donnees("16","Dumbo","Éléphant",3,"Savane",320.0);
    ajouter_animal_donnees("17","Kiki","Chien sauvage",7,"Savane",25.0);
    ajouter_animal_donnees("18","Donatello","Tortue",40,"Rivière",90.5);
    ajouter_animal_donnees("19","Polly","Oiseau",5,"Jungle",1.5);
    ajouter_animal_donnees("20","Kong","Gorille",13,"Jungle",180.0);
}

/****************************************Fonctions de Gestion***************************************************************************/

//***Fonction Ajoute un animal au tableau du zoo
 
void ajouter_animal_donnees(const char* nom, const char* espece, int age, const char* habitat, float poids, RegimeAlimentaire regime) {
    if (nb_animaux < MAX_ANIMAUX) {
        Animal a;
        a.id = generer_id();
        strncpy(a.nom, nom, TAILLE_NOM - 1); a.nom[TAILLE_NOM - 1] = '\0';
        strncpy(a.espece, espece, TAILLE_ESPECE - 1); a.espece[TAILLE_ESPECE - 1] = '\0';
        a.age = age;
        strncpy(a.habitat, habitat, TAILLE_HABITAT - 1); a.habitat[TAILLE_HABITAT - 1] = '\0';
        a.poids = poids;
        a.regime = regime;

        // Date d'arrivée automatique
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        strftime(a.date_arrivee, sizeof(a.date_arrivee), "%d/%m/%Y", &tm);

        zoo[nb_animaux++] = a;
        // La vérification d'âge critique se fait à l'ajout
        verifier_age_critique(&a);
    } else {
        printf(" Erreur: Limite maximale de %d animaux atteinte.\n", MAX_ANIMAUX);
    }
}

//***Fonction Ajoute un ou plusieurs animaux en demandant les informations à l'utilisateur
 
void ajouter_animal_interactif() {
    int nb_a_ajouter = 1;
    char choix_multi;

    printf("\n Ajout d'Animal \n");
    printf("Voulez-vous ajouter plusieurs animaux (O/N) ? ");
    scanf(" %c", &choix_multi);
    if (choix_multi == 'O' || choix_multi == 'o') {
        printf("Combien d'animaux voulez-vous ajouter ? ");
        scanf("%d", &nb_a_ajouter);
        while (getchar() != '\n'); // Nettoyer le buffer
    } else {
        while (getchar() != '\n'); // Nettoyer le buffer
    }

    for (int i = 0; i < nb_a_ajouter; i++) {
        if (nb_animaux >= MAX_ANIMAUX) {
            printf("Limite maximale de %d animaux atteinte. Arrêt de l'ajout.\n", MAX_ANIMAUX);
            break;
        }
        Animal a;
        char regime_str[30];
        char poids_str[10];
        a.id = generer_id();
        printf("\nAjout de l'animal #%d:\n", i + 1);
        printf("Nom: ");
        fgets(a.nom, TAILLE_NOM, stdin);
        a.nom[strcspn(a.nom, "\n")] = 0; // Supprimer le newline
        printf("Espèce (ex: Lion, Tigre, Girafe...): ");
        fgets(a.espece, TAILLE_ESPECE, stdin);
        a.espece[strcspn(a.espece, "\n")] = 0;
        printf("Âge (entier): ");
        if (scanf("%d", &a.age) != 1) {
            printf("Entrée invalide pour l'âge. Annulation de l'ajout.\n");
            while (getchar() != '\n');
            next_id--; // Annuler l'ID généré
            return;
        }
        while (getchar() != '\n');
        printf("Habitat (ex: Savane, Jungle, Désert, Aquatique...): ");
        fgets(a.habitat, TAILLE_HABITAT, stdin);
        a.habitat[strcspn(a.habitat, "\n")] = 0;
        printf("Poids (réel, laisser vide pour ignorer): ");
        fgets(poids_str, sizeof(poids_str), stdin);
        poids_str[strcspn(poids_str, "\n")] = 0;
        if (strlen(poids_str) > 0) {
            if (sscanf(poids_str, "%f", &a.poids) != 1) {
                printf(" Poids invalide. Poids fixé à 0.0.\n");
                a.poids = 0.0;
            }
        } else {
            a.poids = 0.0;
        }

        printf("Régime Alimentaire (Carnivore, Herbivore, Omnivore) : ");
        fgets(regime_str, 30, stdin);
        regime_str[strcspn(regime_str, "\n")] = 0;
        a.regime = string_to_regime(regime_str);

        // Date d'arrivée automatique
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        strftime(a.date_arrivee, sizeof(a.date_arrivee), "%d/%m/%Y", &tm);
        zoo[nb_animaux++] = a;
        printf("✅ Animal '%s' (ID: %d) ajouté au zoo. Date d'arrivée: %s\n", a.nom, a.id, a.date_arrivee);
        verifier_age_critique(&a);
    }
}

//***Fonction qui Affiche la liste des animaux dans un tableau structuré.

void afficher_animaux(const Animal animaux[], int taille) {
    if (taille == 0) {
        printf("Aucune animal à afficher.\n");
        return;
    }

    printf("\n+-----+-------------------------------------------------------+-----------------------------+\n");
    printf("| ID  | Nom (Espèce) - Âge (Ans) | Habitat | Poids (Kg) | Régime | Arrivée |\n");
    printf("+-----+--------------------------+-----------------+------------+--------+---------+\n");

    for (int i = 0; i < taille; i++) {
        const Animal* a = &animaux[i];
        printf("| %-3d | %-12s (%-10s) - %-3d | %-15s | %-10.1f | %-6s | %-7s |\n",
               a->id, a->nom, a->espece, a->age, a->habitat, a->poids, regime_to_string(a->regime), a->date_arrivee);
    }

    printf("+-----+-------------------------------------------------------+-----------------------------+\n");
    printf("Total: %d animal(aux).\n", taille);
}

//***Fonction qui Affiche le sous-menu d'affichage
 
void afficher_menu_affichage() {
    int choix;
    do {
        printf("\n--- Menu Affichage ---\n");
        printf("1. Afficher la liste complète\n");
        printf("2. Trier par nom\n");
        printf("3. Trier par âge\n");
        printf("4. Afficher par habitat spécifique\n");
        printf("0. Retour au Menu Principal\n");
        printf("Votre choix : ");

        if (scanf("%d", &choix) != 1) {
            printf("Choix invalide.\n");
            while (getchar() != '\n');
            continue;
        }
        while (getchar() != '\n');

        switch (choix) {
            case 1:
                printf("\n--- Liste Complète ---\n");
                afficher_animaux(zoo, nb_animaux);
                break;
            case 2:
                trier_animaux_par_nom();
                break;
            case 3:
                trier_animaux_par_age();
                break;
            case 4:
                afficher_animaux_par_habitat();
                break;
            case 0:
                return;
            default:
                printf("Option non reconnue.\n");
        }
    } while (choix != 0);
}

//***Fonction qui Trie et affiche les animaux par nom.
 
void trier_animaux_par_nom() {
    // Crée une copie temporaire pour ne pas altérer l'ordre principal du zoo
    Animal zoo_trie[MAX_ANIMAUX];
    memcpy(zoo_trie, zoo, nb_animaux * sizeof(Animal));

    // Utilisation de qsort avec la fonction de comparaison comparer_noms
    qsort(zoo_trie, nb_animaux, sizeof(Animal), comparer_noms);

    printf("\n--- Animaux triés par Nom ---\n");
    afficher_animaux(zoo_trie, nb_animaux);
}

//***Fonction qui Trie et affiche les animaux par âge.

void trier_animaux_par_age() {
    // Crée une copie temporaire
    Animal zoo_trie[MAX_ANIMAUX];
    memcpy(zoo_trie, zoo, nb_animaux * sizeof(Animal));

    // Utilisation de qsort avec la fonction de comparaison comparer_ages
    qsort(zoo_trie, nb_animaux, sizeof(Animal), comparer_ages);

    printf("\n--- Animaux triés par Âge ---\n");
    afficher_animaux(zoo_trie, nb_animaux);
}

//***Affiche les animaux d'un habitat spécifique.

void afficher_animaux_par_habitat() {
    char habitat_recherche[TAILLE_HABITAT];
    Animal resultats[MAX_ANIMAUX];
    int count = 0;

    printf("\n--- Afficher par Habitat ---\n");
    printf("Entrez l'habitat à rechercher : ");
    fgets(habitat_recherche, TAILLE_HABITAT, stdin);
    habitat_recherche[strcspn(habitat_recherche, "\n")] = 0;

    // Filtrage
    for (int i = 0; i < nb_animaux; i++) {
        if (strcmp(zoo[i].habitat, habitat_recherche) == 0) {
            resultats[count++] = zoo[i];
        }
    }

    printf("\n Animaux de l'habitat '%s' \n", habitat_recherche);
    afficher_animaux(resultats, count);
}

//***Fonction qui Modifier l'habitat ou l'âge d'un animal
 
void modifier_animal_menu() {
    int id;
    int index;
    int choix;

    printf("\n Modification d'Animal \n");
    printf("Entrez l'ID de l'animal à modifier : ");
    if (scanf("%d", &id) != 1) {
        printf("Entrée invalide pour l'ID.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    index = trouver_index_par_id(id);

    if (index == -1) {
        printf("Animal avec l'ID %d non trouvé.\n", id);
        return;
    }

    printf("Animal sélectionné: %s (ID: %d, Habitat: %s, Âge: %d)\n",
           zoo[index].nom, zoo[index].id, zoo[index].habitat, zoo[index].age);

    printf("Que voulez-vous modifier ?\n");
    printf("1. Habitat\n");
    printf("2. Âge\n");
    printf("Votre choix : ");

    if (scanf("%d", &choix) != 1) {
        printf("Choix invalide.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    switch (choix) {
        case 1: {
            char nouvel_habitat[TAILLE_HABITAT];
            printf("Nouvel habitat : ");
            fgets(nouvel_habitat, TAILLE_HABITAT, stdin);
            nouvel_habitat[strcspn(nouvel_habitat, "\n")] = 0;
            // Bonus: Ajouter la possibilité de déplacer un animal d'un habitat à un autre
            printf(" Animal déplacé de %s à %s.\n", zoo[index].habitat, nouvel_habitat);
            strncpy(zoo[index].habitat, nouvel_habitat, TAILLE_HABITAT - 1);
            zoo[index].habitat[TAILLE_HABITAT - 1] = '\0';
            break;
        }
        case 2: {
            int nouvel_age;
            printf("Nouvel âge : ");
            if (scanf("%d", &nouvel_age) != 1) {
                printf(" Entrée invalide pour l'âge.\n");
                while (getchar() != '\n');
                return;
            }
            if (nouvel_age < 0) {
                printf(" L'âge ne peut pas être négatif.\n");
                return;
            }
            zoo[index].age = nouvel_age;
            printf(" Âge de %s mis à jour à %d ans.\n", zoo[index].nom, nouvel_age);
            verifier_age_critique(&zoo[index]);  // Vérifier l'âge critique après modification
            break;
        }
        default:
            printf(" Option de modification non reconnue.\n");
            break;
    }
}

//***Fonction qui Supprime un animal par son ID.
 
void supprimer_animal() {
    int id;
    int index;

    printf("\n--- Suppression d'Animal ---\n");
    printf("Entrez l'ID de l'animal à supprimer : ");
    if (scanf("%d", &id) != 1) {
        printf(" Entrée invalide pour l'ID.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    index = trouver_index_par_id(id);

    if (index == -1) {
        printf(" Animal avec l'ID %d non trouvé.\n", id);
        return;
    }

    printf("Confirmez-vous la suppression de %s (ID: %d) ? (O/N) : ", zoo[index].nom, id);
    char confirmation;
    scanf(" %c", &confirmation);
    while (getchar() != '\n');

    if (confirmation == 'O' || confirmation == 'o') {
        // Décalage des éléments suivants pour "fermer le trou"
        for (int i = index; i < nb_animaux - 1; i++) {
            zoo[i] = zoo[i + 1];
        }
        nb_animaux--;
        printf(" Animal avec l'ID %d a été supprimé.\n", id);
    } else {
        printf(" Suppression annulée.\n");
    }
}

// Fonction qui Affiche le menu de recherche
 
void rechercher_animal_menu() {
    int choix;
    printf("\n--- Menu Recherche ---\n");
    printf("1. Rechercher par ID\n");
    printf("2. Rechercher par Nom\n");
    printf("3. Rechercher par Espèce\n");
    printf("0. Retour au Menu Principal\n");
    printf("Votre choix : ");

    if (scanf("%d", &choix) != 1) {
        printf(" Choix invalide.\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');

    Animal resultats[MAX_ANIMAUX];
    int count = 0;

    switch (choix) {
        case 1: {     // Recherche par ID
            int id_recherche;
            printf("Entrez l'ID à rechercher : ");
            if (scanf("%d", &id_recherche) != 1) {
                printf(" Entrée invalide pour l'ID.\n");
                while (getchar() != '\n');
                return;
            }
            while (getchar() != '\n');
            int index = trouver_index_par_id(id_recherche);
            if (index != -1) {
                resultats[count++] = zoo[index];
            }
            printf("\n--- Résultat de la Recherche par ID %d ---\n", id_recherche);
            break;
        }
        case 2: {    // Recherche par Nom
            char nom_recherche[TAILLE_NOM];
            printf("Entrez le Nom à rechercher : ");
            fgets(nom_recherche, TAILLE_NOM, stdin);
            nom_recherche[strcspn(nom_recherche, "\n")] = 0;

            for (int i = 0; i < nb_animaux; i++) {
                if (strcasecmp(zoo[i].nom, nom_recherche) == 0) { // strcasecmp pour une recherche insensible à la casse
                    resultats[count++] = zoo[i];
                }
            }
            printf("\n--- Résultat de la Recherche par Nom '%s' ---\n", nom_recherche);
            break;
        }
        case 3: {   // Recherche par Espèce
            char espece_recherche[TAILLE_ESPECE];
            printf("Entrez l'Espèce à rechercher : ");
            fgets(espece_recherche, TAILLE_ESPECE, stdin);
            espece_recherche[strcspn(espece_recherche, "\n")] = 0;

            for (int i = 0; i < nb_animaux; i++) {
                if (strcasecmp(zoo[i].espece, espece_recherche) == 0) {
                    resultats[count++] = zoo[i];
                }
            }
            printf("\n Résultat de la Recherche par Espèce '%s' \n", espece_recherche);
            break;
        }
        case 0:
            return;
        default:
            printf(" Option non reconnue.\n");
            return;
    }

    afficher_animaux(resultats, count);
}

/*******************************************************Statistiques**********************************************************/
// Fonction qui Affiche les statistiques du zoo
 
void afficher_statistiques() {
    printf("\n--- Statistiques du Zoo ---\n");

    if (nb_animaux == 0) {
        printf(" Le zoo est vide. Aucune statistique à afficher.\n");
        return;
    }

    // 1. Nombre total d’animaux
    printf("1. Nombre total d’animaux : **%d**\n", nb_animaux);

    // 2. Âge moyen, Plus vieux et Plus jeune animal
    float total_age = 0.0;
    int plus_vieux_age = -1;
    int plus_jeune_age = 9999;
    const Animal *plus_vieux = NULL;
    const Animal *plus_jeune = NULL;

    for (int i = 0; i < nb_animaux; i++) {
        total_age += zoo[i].age;

        if (zoo[i].age > plus_vieux_age) {
            plus_vieux_age = zoo[i].age;
            plus_vieux = &zoo[i];
        }
        if (zoo[i].age < plus_jeune_age) {
            plus_jeune_age = zoo[i].age;
            plus_jeune = &zoo[i];
        }
    }

    float age_moyen = total_age / nb_animaux;
    printf("2. Âge moyen des animaux : **%.2f ans**\n", age_moyen);

    if (plus_vieux) {
        printf("3. Plus vieux animal : **%s** (%d ans, ID: %d)\n", plus_vieux->nom, plus_vieux->age, plus_vieux->id);
    }
    if (plus_jeune) {
        printf("4. Plus jeune animal : **%s** (%d ans, ID: %d)\n", plus_jeune->nom, plus_jeune->age, plus_jeune->id);
    }

    // 5. Espèces les plus représentées (Simple : Top 3 ou toutes).Nécessite une structure pour compter les espèces
    struct {
        char espece[TAILLE_ESPECE];
        int count;
    } espece_counts[MAX_ANIMAUX]; // Max possible
    int nb_especes_uniques = 0;

    for (int i = 0; i < nb_animaux; i++) {
        int trouve = 0;
        for (int j = 0; j < nb_especes_uniques; j++) {
            if (strcmp(zoo[i].espece, espece_counts[j].espece) == 0) {
                espece_counts[j].count++;
                trouve = 1;
                break;
            }
        }
        if (!trouve) {
            if (nb_especes_uniques < MAX_ANIMAUX) {
                strncpy(espece_counts[nb_especes_uniques].espece, zoo[i].espece, TAILLE_ESPECE - 1);
                espece_counts[nb_especes_uniques].count = 1;
                nb_especes_uniques++;
            }
        }
    }

    printf("5. Espèces représentées : (%d espèces uniques)\n", nb_especes_uniques);

    // Tri (bulle ou qsort) pour afficher les plus représentées en premier
    for (int i = 0; i < nb_especes_uniques - 1; i++) {
        for (int j = 0; j < nb_especes_uniques - 1 - i; j++) {
            if (espece_counts[j].count < espece_counts[j + 1].count) {
                // Échange
                typeof(espece_counts[0]) temp = espece_counts[j];
                espece_counts[j] = espece_counts[j + 1];
                espece_counts[j + 1] = temp;
            }
        }
    }

    int limit = (nb_especes_uniques > 5) ? 5 : nb_especes_uniques; // Afficher max Top 5
    for (int i = 0; i < limit; i++) {
        printf("   - %s : %d\n", espece_counts[i].espece, espece_counts[i].count);
    }
    if (nb_especes_uniques > limit) {
        printf("   - ... et %d autres espèces.\n", nb_especes_uniques - limit);
    }
}

/************************************************Bonus Fonction *****************************************************************/
// La fonction qui Vérifie et affiche un message si l'animal atteint un âge critique (ex. > 20 ans pour un lion)

void verifier_age_critique(const Animal* a) {
    int age_critique = -1;

    // Quelques exemples d'âges critiques
    if (strcasecmp(a->espece, "Lion") == 0 || strcasecmp(a->espece, "Tigre") == 0) {
        age_critique = 20;
    } else if (strcasecmp(a->espece, "Girafe") == 0) {
        age_critique = 25;
    } else if (strcasecmp(a->espece, "Elephant") == 0) {
        age_critique = 60;
    } else if (strcasecmp(a->espece, "Tortue") == 0) {
        age_critique = 100; // Juste pour l'exemple
    }

    if (age_critique > 0 && a->age >= age_critique) {
        printf("\n🚨 ALERTE ÂGE CRITIQUE : L'animal %s (%s, ID: %d) a %d ans, atteignant ou dépassant l'âge critique estimé de %d ans.\n",
               a->nom, a->espece, a->id, a->age, age_critique);
    }
}


/******************************************************* MAIN ********************************************************************************/
// Fonction Principale (Main) 
int main() {
    int choix;

    // 1. Initialisation des données
    initialiser_zoo();

    do {
        // Affichage du menu principal
        printf("\n============================================\n");
        printf(" Bienvenue dans l'Application Zoo Manager  \n");
        printf("============================================\n");
        printf("1. Ajouter un animal\n");
        printf("2. Afficher les animaux (Tri/Filtre)\n");
        printf("3. Modifier un animal (Habitat/Âge)\n");
        printf("4. Supprimer un animal\n");
        printf("5. Rechercher un animal\n");
        printf("6. Statistiques\n");
        printf("0. Quitter\n");
        printf("--------------------------------------------\n");
        printf("Entrez votre choix : ");

        // Lecture du choix (gestion simple d'erreur)
        if (scanf("%d", &choix) != 1) {
            printf(" Choix invalide. Veuillez entrer un nombre.\n");
            // Nettoyer le buffer d'entrée
            while (getchar() != '\n');
            choix = -1; // Force la boucle à continuer
            continue;
        }
        while (getchar() != '\n'); // Nettoyer le buffer après le scanf

        // Traitement du choix
        switch (choix) {
            case 1:
                ajouter_animal_interactif();
                break;
            case 2:
                afficher_menu_affichage();
                break;
            case 3:
                modifier_animal_menu();
                break;
            case 4:
                supprimer_animal();
                break;
            case 5:
                rechercher_animal_menu();
                break;
            case 6:
                afficher_statistiques();
                break;
            case 0:
                printf("\n Fermeture de l'application. Au revoir !\n");
                break;
            default:
                printf(" Option non valide. Veuillez réessayer.\n");
        }
        
    } while (choix != 0);
    return 0;
}