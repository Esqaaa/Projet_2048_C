#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void afficher_case(int valeur);

// Couleurs ANSI pour les tuiles (venant de couleur.c)
const char* couleur(int valeur);

// Définition de la taille de la grille
#define TAILLE 4
#define RESET   "\x1b[0m"
#define ROSE    "\x1b[38;5;199m"
#define BLEU    "\x1b[38;5;51m"

// Structure du jeu
typedef struct {
    int **grille;
    int score;
} Jeu;


// Affichage de la grille + score
void afficher_case(int valeur) {
    // Si la case est vide, afficher un tiret
    if (valeur == 0) {
        printf(BLEU "|" RESET "  -   ");

        return;
    }

    // Convertit la valeur en chaîne de caractères pour l'affichage
    char buffer[16];
    sprintf(buffer, "%d", valeur);

    // Calcule l'espacement pour centrer la valeur dans la case
    int len = strlen(buffer);
    int total = 6; 
    int left = (total - len) / 2;
    int right = total - len - left;

    printf(BLEU "|" RESET);

    // Espaces à gauche
    for (int i = 0; i < left; i++) {
        printf(" ");
    }

    // Affiche la valeur avec la couleur correspondante
    printf("%s%s%s", couleur(valeur), buffer, "\x1b[0m");

    // Espaces à droite
    for (int i = 0; i < right; i++) {
        printf(" ");
    }

}


// Affichage de la grille + score
void afficher(Jeu *jeu) {
    // Efface la console
    system("cls");

    // Affichage du score
    printf("Score : %d\n\n", jeu->score);

    printf(BLEU "+------+------+------+------+" RESET "\n");

    // Affichage de chaque tuile avec sa couleur 
    for (int i = 0; i < TAILLE; i++) {
        for (int j = 0; j < TAILLE; j++) {

            int valeur = jeu->grille[i][j];

            afficher_case(valeur);
        }
        printf(BLEU "|\n" RESET);
        printf(BLEU "+------+------+------+------+" RESET "\n");
    }

    // Instructions pour le joueur
    printf("\nDeplacement (Z Q S D)\n");
    printf("Quitter (X)\n");
    printf("Rejouer (R)\n");
    printf("Votre choix : ");
}