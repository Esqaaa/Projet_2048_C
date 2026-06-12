#include <stdio.h>
#include <stdlib.h>

int TAILLE = 4;

typedef struct {
    int **grille;
    int score;
} Jeu;

// Création d'un nouveau jeu
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

// Ajoute une tuile "2" dans une case vide aléatoire
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

// Fusionne une ligne vers la gauche (utilisée pour tous les déplacements)
void fusionnerLigne(int *ligne) {

    // Compression vers la gauche
    for (int rep = 0; rep < TAILLE; rep++)
        for (int j = 1; j < TAILLE; j++)
            if (ligne[j] != 0 && ligne[j-1] == 0) {
                ligne[j-1] = ligne[j];
                ligne[j] = 0;
            }

    // Fusion
    for (int j = 0; j < TAILLE - 1; j++)
        if (ligne[j] != 0 && ligne[j] == ligne[j+1]) {
            ligne[j] *= 2;
            ligne[j+1] = 0;
        }

    // Recompression
    for (int j = 1; j < TAILLE; j++)
        if (ligne[j] != 0 && ligne[j-1] == 0) {
            ligne[j-1] = ligne[j];
            ligne[j] = 0;
        }
}

// Déplacement GAUCHE
void deplacer_gauche(Jeu *jeu) {
    for (int i = 0; i < TAILLE; i++)
        fusionnerLigne(jeu->grille[i]);
}

// Déplacement DROITE
void deplacer_droite(Jeu *jeu) {
    for (int i = 0; i < TAILLE; i++) {

        int temp[TAILLE];

        // Inverser la ligne
        for (int j = 0; j < TAILLE; j++)
            temp[j] = jeu->grille[i][TAILLE - 1 - j];

        fusionnerLigne(temp);

        // Ré-inverser
        for (int j = 0; j < TAILLE; j++)
            jeu->grille[i][TAILLE - 1 - j] = temp[j];
    }
}

// Déplacement HAUT
void deplacer_haut(Jeu *jeu) {
    for (int col = 0; col < TAILLE; col++) {

        int temp[TAILLE];

        // Extraire la colonne
        for (int i = 0; i < TAILLE; i++)
            temp[i] = jeu->grille[i][col];

        fusionnerLigne(temp);

        // Remettre dans la grille
        for (int i = 0; i < TAILLE; i++)
            jeu->grille[i][col] = temp[i];
    }
}

// Déplacement BAS
void deplacer_bas(Jeu *jeu) {
    for (int col = 0; col < TAILLE; col++) {

        int temp[TAILLE];

        // Extraire colonne inversée
        for (int i = 0; i < TAILLE; i++)
            temp[i] = jeu->grille[TAILLE - 1 - i][col];

        fusionnerLigne(temp);

        // Ré-inverser dans la grille
        for (int i = 0; i < TAILLE; i++)
            jeu->grille[TAILLE - 1 - i][col] = temp[i];
    }
}

// Mouvements possibles (s'il y en a)
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

// Vérification de la victoire (2048 atteint)
int victoire(Jeu *jeu) {
    for (int i = 0; i < TAILLE; i++)
        for (int j = 0; j < TAILLE; j++)
            if (jeu->grille[i][j] == 2048)
                return 1;
    return 0;
}

// Vérification de la défaite
int defaite(Jeu *jeu) {
    return !mouvements_possibles(jeu);
}