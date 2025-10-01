#include <stdio.h>
#include <string.h>

struct Contact {
    char nom[100];
    char numero_de_telephone[100];
    char email[100];
};

void trier_par_nom(struct Contact *contacts, int n) {
    int i, j;
    struct Contact temp;

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            // Comparer les noms alphabétiquement
            if (strcmp(contacts[j].nom, contacts[j + 1].nom) > 0) {
                // Échanger les structures
                temp = contacts[j];
                contacts[j] = contacts[j + 1];
                contacts[j + 1] = temp;
            }
        }
    }
}

void afficher_contacts(struct Contact *contacts, int n) {
    for (int i = 0; i < n; i++) {
        printf("Contact %d: %s, %s, %s\n", i + 1, contacts[i].nom, contacts[i].numero_de_telephone, contacts[i].email);
    }
}

int main() {
    
    struct Contact contacts[3] = {
        {"Dupont", "0123456789", "dupont@example.com"},
        {"Alice", "0987654321", "alice@example.com"},
        {"Bernard", "0567891234", "bernard@example.com"}
    };

    int n = 3;

    printf("Contacts avant tri:\n");
    afficher_contacts(contacts, n);

    
    trier_par_nom(contacts, n);

    printf("\nContacts après tri alphabétique par nom:\n");
    afficher_contacts(contacts, n);

    return 0;
}