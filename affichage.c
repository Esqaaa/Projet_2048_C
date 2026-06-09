#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Association des valeurs de tuiles à des couleurs ANSI
#define RESET "\x1b[0m"
#define ROSE  "\x1b[38;5;199m"
#define BLEU  "\x1b[38;5;51m"

// Fonctions externes
extern int TAILLE;

// Structure du jeu
typedef struct {
    int **grille;
    int score;
} Jeu;

// Affiche une case
void afficher_case(int valeur) {
    if (valeur == 0) {
        printf(BLEU "|" RESET "  .   ");
        return;
    }

    // Centrage du nombre dans la case
    char buffer[16];
    sprintf(buffer, "%d", valeur);

    // Calcul des espaces à gauche et à droite pour centrer le nombre
    int len = strlen(buffer);
    int total = 6;
    int left = (total - len) / 2;
    int right = total - len - left;

    printf(BLEU "|" RESET);

    // Espaces à gauche
    for (int i = 0; i < left; i++) {
        printf(" ");
    }

    printf("%s%s%s", BLEU, buffer, RESET);

    // Espaces à droite
    for (int i = 0; i < right; i++) {
        printf(" ");
    }

    printf(RESET);
}

void afficher(Jeu *jeu) {
    // Effacer l'écran
    system("cls");

    // Affichage du score
    printf("Score : %d\n\n", jeu->score);

    printf(BLEU);
    
    // Affichage de la ligne
    for (int i = 0; i < TAILLE; i++)
        printf("+------");
    printf("+\n" RESET);

    // Affichage de la grille
    for (int i = 0; i < TAILLE; i++) {

        // Affichage des cases
        for (int j = 0; j < TAILLE; j++)
            afficher_case(jeu->grille[i][j]);

        printf("|\n");

        printf(BLEU);

        // Affichage de la ligne de séparation
        for (int j = 0; j < TAILLE; j++)
            printf("+------");
        printf("+\n" RESET);
    }

    // Affichage des commandes
    printf("\nDeplacement (Z Q S D)\n");
    printf("Quitter (X)\n");
    printf("Rejouer (R)\n");
    printf("Votre choix : ");
}
