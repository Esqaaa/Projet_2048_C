#include <stdlib.h>

extern int TAILLE;

typedef struct {
    int **grille;
    int score;
} Jeu;

// Création d'un nouveau jeu
Jeu* creer_jeu() {
    // Allocation mémoire de la structure principale
    Jeu *jeu = malloc(sizeof(Jeu));
    if (!jeu) return NULL;
    jeu->score = 0;

    // Allocation du tableau de pointeurs (donc les lignes de la grille)
    jeu->grille = malloc(TAILLE * sizeof(int*));
    if (!jeu->grille) { 
        free(jeu); // On libère ce qui a déjà été alloué avant de quitter
        return NULL; 
    }

    // Allocation de chaque ligne, initialisée à 0 grâce à calloc
    for (int i = 0; i < TAILLE; i++) {
        jeu->grille[i] = calloc(TAILLE, sizeof(int));
        if (!jeu->grille[i]) {

            // En cas d'échec, on libère toutes les lignes déjà allouées
            for (int j = 0; j < i; j++) free(jeu->grille[j]);
            free(jeu->grille);
            free(jeu);
            return NULL;
        }
    }
    return jeu;
}

// Libère la mémoire allouée pour le jeu
void detruire_jeu(Jeu *jeu) {
    if (!jeu) return;
    if (jeu->grille) {
        for (int i = 0; i < TAILLE; i++) {
            free(jeu->grille[i]);
        }
        free(jeu->grille);
    }
    free(jeu);
}

// Ajoute une tuile "2" dans une case vide aléatoire
void ajouter_tuile(Jeu *jeu) {
    int libres[25][2]; // Tableau des coordonnées des cases vides (max 5x5 = 25)
    int n = 0; // Nombre de cases vides trouvées

    // Parcours de la grille + stockage des coordonnées de cases vides
    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            if (jeu->grille[i][j] == 0) {
                libres[n][0] = i; // Ligne
                libres[n][1] = j; // Colonne
                n++;
            }
        }
    }
    if (n > 0) {

        // On tire une case vide au hasard parmi toutes celles disponibles
        int r = rand() % n;
        jeu->grille[libres[r][0]][libres[r][1]] = 2;
    }
}

// Déplacement gauche
void deplacer_gauche(Jeu *jeu) {
    for (int i = 0; i < TAILLE; i++) {
        // Tasser vers la gauche (enlever les zéros)
        for (int passage = 0; passage < TAILLE; passage++) {
            for (int j = 1; j < TAILLE; j++) {
                if (jeu->grille[i][j] != 0 && jeu->grille[i][j - 1] == 0) {
                    jeu->grille[i][j - 1] = jeu->grille[i][j];
                    jeu->grille[i][j] = 0;
                }
            }
        }
        // Fusionner les tuiles identiques de gauche à droite
        for (int j = 0; j < TAILLE - 1; j++) {
            if (jeu->grille[i][j] != 0 && jeu->grille[i][j] == jeu->grille[i][j + 1]) {
                jeu->grille[i][j] *= 2;
                jeu->score += jeu->grille[i][j]; // Ajout au score du jeu
                jeu->grille[i][j + 1] = 0;
                j++; // Empêche la tuile suivante de re-fusionner immédiatement
            }
        }
        // Retasser vers la gauche après les fusions
        for (int j = 1; j < TAILLE; j++) {
            if (jeu->grille[i][j] != 0 && jeu->grille[i][j - 1] == 0) {
                jeu->grille[i][j - 1] = jeu->grille[i][j];
                jeu->grille[i][j] = 0;
            }
        }
    }
}

// Déplacement droite
void deplacer_droite(Jeu *jeu) {
    for (int i = 0; i < TAILLE; i++) {
        // Tasser vers la droite
        for (int passage = 0; passage < TAILLE; passage++) {
            for (int j = TAILLE - 2; j >= 0; j--) {
                if (jeu->grille[i][j] != 0 && jeu->grille[i][j + 1] == 0) {
                    jeu->grille[i][j + 1] = jeu->grille[i][j];
                    jeu->grille[i][j] = 0;
                }
            }
        }
        // Fusionner les tuiles de droite à gauche
        for (int j = TAILLE - 1; j > 0; j--) {
            if (jeu->grille[i][j] != 0 && jeu->grille[i][j] == jeu->grille[i][j - 1]) {
                jeu->grille[i][j] *= 2;
                jeu->score += jeu->grille[i][j];
                jeu->grille[i][j - 1] = 0;
                j--; // Empêche la double fusion
            }
        }
        // Retasser vers la droite après les fusions
        for (int j = TAILLE - 2; j >= 0; j--) {
            if (jeu->grille[i][j] != 0 && jeu->grille[i][j + 1] == 0) {
                jeu->grille[i][j + 1] = jeu->grille[i][j];
                jeu->grille[i][j] = 0;
            }
        }
    }
}

// Déplacement haut
void deplacer_haut(Jeu *jeu) {
    for (int j = 0; j < TAILLE; j++) {
        // Tasser vers le haut
        for (int passage = 0; passage < TAILLE; passage++) {
            for (int i = 1; i < TAILLE; i++) {
                if (jeu->grille[i][j] != 0 && jeu->grille[i - 1][j] == 0) {
                    jeu->grille[i - 1][j] = jeu->grille[i][j];
                    jeu->grille[i][j] = 0;
                }
            }
        }
        // Fusionner les tuiles du haut vers le bas
        for (int i = 0; i < TAILLE - 1; i++) {
            if (jeu->grille[i][j] != 0 && jeu->grille[i][j] == jeu->grille[i + 1][j]) {
                jeu->grille[i][j] *= 2;
                jeu->score += jeu->grille[i][j];
                jeu->grille[i + 1][j] = 0;
                i++; // Empêche la double fusion
            }
        }
        // Retasser vers le haut après les fusions
        for (int i = 1; i < TAILLE; i++) {
            if (jeu->grille[i][j] != 0 && jeu->grille[i - 1][j] == 0) {
                jeu->grille[i - 1][j] = jeu->grille[i][j];
                jeu->grille[i][j] = 0;
            }
        }
    }
}

// Déplacement bas
void deplacer_bas(Jeu *jeu) {
    for (int j = 0; j < TAILLE; j++) {
        // Tasser vers le bas
        for (int passage = 0; passage < TAILLE; passage++) {
            for (int i = TAILLE - 2; i >= 0; i--) {
                if (jeu->grille[i][j] != 0 && jeu->grille[i + 1][j] == 0) {
                    jeu->grille[i + 1][j] = jeu->grille[i][j];
                    jeu->grille[i][j] = 0;
                }
            }
        }
        // Fusionner les tuiles du bas vers le haut
        for (int i = TAILLE - 1; i > 0; i--) {
            if (jeu->grille[i][j] != 0 && jeu->grille[i][j] == jeu->grille[i - 1][j]) {
                jeu->grille[i][j] *= 2;
                jeu->score += jeu->grille[i][j];
                jeu->grille[i - 1][j] = 0;
                i--; // Empêche la double fusion
            }
        }
        // Retasser vers le bas après les fusions
        for (int i = TAILLE - 2; i >= 0; i--) {
            if (jeu->grille[i][j] != 0 && jeu->grille[i + 1][j] == 0) {
                jeu->grille[i + 1][j] = jeu->grille[i][j];
                jeu->grille[i][j] = 0;
            }
        }
    }
}

// Fonction de vérification des mouvements
int mouvements_possibles(Jeu *jeu) {
    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {
            if (jeu->grille[i][j] == 0) return 1;
            if (j < TAILLE - 1 && jeu->grille[i][j] == jeu->grille[i][j+1]) return 1;
            if (i < TAILLE - 1 && jeu->grille[i][j] == jeu->grille[i+1][j]) return 1;
        }
    }
    return 0;
}

// Vérification de la victoire 
int victoire(Jeu *jeu) {
    for (int i = 0; i < TAILLE; i++)
        for (int j = 0; j < TAILLE; j++)
            if (jeu->grille[i][j] == 2048) return 1;
    return 0;
}

// Vérification de la défaite
int defaite(Jeu *jeu) {
    return !mouvements_possibles(jeu);
}