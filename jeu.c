#include <stdio.h>
#include <stdlib.h>

int TAILLE = 4;

typedef struct {
    int **grille;
    int score;
} Jeu;

// Prototypes des fonctions du jeu
Jeu* creer_jeu() {
    Jeu *jeu = malloc(sizeof(Jeu));
    if (!jeu) return NULL;

    jeu->score = 0;

    jeu->grille = malloc(TAILLE * sizeof(int*));
    for (int i = 0; i < TAILLE; i++)
        jeu->grille[i] = calloc(TAILLE, sizeof(int));

    return jeu;
}

// Libère la mémoire allouée pour le jeu
void detruire_jeu(Jeu *jeu) {
    for (int i = 0; i < TAILLE; i++)
        free(jeu->grille[i]);
    free(jeu->grille);
    free(jeu);
}

// Prototypes des fonctions d'affichage et de logique du jeu
void ajouter_tuile(Jeu *jeu) {
    int libres[TAILLE * TAILLE][2];
    int n = 0;

    for (int i = 0; i < TAILLE; i++)
        for (int j = 0; j < TAILLE; j++)
            if (jeu->grille[i][j] == 0) {
                libres[n][0] = i;
                libres[n][1] = j;
                n++;
            }

    if (n > 0) {
        int r = rand() % n;
        jeu->grille[libres[r][0]][libres[r][1]] = 2;
    }
}

// Déplacement vers la gauche
void deplacer_gauche(Jeu *jeu) {
    for (int i = 0; i < TAILLE; i++) {

        for (int rep = 0; rep < TAILLE; rep++)
            for (int j = 1; j < TAILLE; j++)
                if (jeu->grille[i][j] != 0 && jeu->grille[i][j-1] == 0) {
                    jeu->grille[i][j-1] = jeu->grille[i][j];
                    jeu->grille[i][j] = 0;
                }

        for (int j = 0; j < TAILLE - 1; j++)
            if (jeu->grille[i][j] != 0 && jeu->grille[i][j] == jeu->grille[i][j+1]) {
                jeu->grille[i][j] *= 2;
                jeu->score += jeu->grille[i][j];
                jeu->grille[i][j+1] = 0;
            }

        for (int j = 1; j < TAILLE; j++)
            if (jeu->grille[i][j] != 0 && jeu->grille[i][j-1] == 0) {
                jeu->grille[i][j-1] = jeu->grille[i][j];
                jeu->grille[i][j] = 0;
            }
    }
}

// Rotation de la grille dans le sens horaire
void pivoter(Jeu *jeu) {
    int tmp[TAILLE][TAILLE];

    for (int i = 0; i < TAILLE; i++)
        for (int j = 0; j < TAILLE; j++)
            tmp[j][TAILLE - 1 - i] = jeu->grille[i][j];

    for (int i = 0; i < TAILLE; i++)
        for (int j = 0; j < TAILLE; j++)
            jeu->grille[i][j] = tmp[i][j];
}

// Vérifie s'il y'a des mouvements possibles (dans les 4 directions)
int mouvements_possibles(Jeu *jeu) {
    for (int i = 0; i < TAILLE; i++)
        for (int j = 0; j < TAILLE; j++) {

            if (jeu->grille[i][j] == 0)
                return 1;

            if (j < TAILLE - 1 && jeu->grille[i][j] == jeu->grille[i][j+1])
                return 1;

            if (i < TAILLE - 1 && jeu->grille[i][j] == jeu->grille[i+1][j])
                return 1;
        }
    return 0;
}

// Vérifie si le joueur a atteint 2048
int victoire(Jeu *jeu) {
    for (int i = 0; i < TAILLE; i++)
        for (int j = 0; j < TAILLE; j++)
            if (jeu->grille[i][j] == 2048)
                return 1;
    return 0;
}
