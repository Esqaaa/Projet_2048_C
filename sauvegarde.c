#include <stdio.h>
#include <stdlib.h>

extern int TAILLE;

typedef struct {
    int **grille;
    int score;
} Jeu;

// Sauvegarde la partie dans save.txt
void sauvegarder(Jeu *jeu) {
    FILE *f = fopen("save.txt", "w");
    if (!f) {
        perror("Erreur : impossible d'ouvrir save.txt\n");
        return;
    }

    // Sauvegarde de la taille
    fprintf(f, "%d\n", TAILLE);

    // Sauvegarde du score
    fprintf(f, "%d\n", jeu->score);

    // Sauvegarde de la grille
    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            fprintf(f, "%d ", jeu->grille[i][j]);
        }
        fprintf(f, "\n");
    }

    fclose(f);
    printf("Partie sauvegardee.\n");
    printf("Appuyez sur Entree pour continuer...");
    getchar();
    getchar();

}

// Charge la partie depuis save.txt
void charger(Jeu *jeu) {
    FILE *f = fopen("save.txt", "r");
    if (!f) {
        perror("Aucune sauvegarde trouvee.\n");
        return NULL;
    }

    int taille_fichier;
    fscanf(f, "%d", &taille_fichier);

    // Vérifie que la taille correspond
    if (taille_fichier != TAILLE) {
        perror("Sauvegarde incompatible avec la taille actuelle.\n");
        fclose(f);
        return NULL;
    }

    // Charger le score
    fscanf(f, "%d", &jeu->score);

    // Charger la grille
    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            fscanf(f, "%d", &jeu->grille[i][j]);
        }
    }

    fclose(f);
    printf("Sauvegarde chargee.\n");
    printf("Appuyez sur Entrée pour continuer...");
    getchar(); 
    getchar();
}
