#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

// Prototypes des fonctions externes
void afficher_ascii();

typedef struct {
    int **grille;
    int score;
} Jeu;

// Prototypes des fonctions du jeu
Jeu* creer_jeu();
void detruire_jeu(Jeu *jeu);
void afficher(Jeu *jeu);
void ajouter_tuile(Jeu *jeu);
void deplacer_gauche(Jeu *jeu);
void pivoter(Jeu *jeu);
int mouvements_possibles(Jeu *jeu);
int victoire(Jeu *jeu);

// Fonction principale
int main() {

    // Affichage du logo ASCII
    afficher_ascii();
    system("pause");

    // Initialisation du générateur de nombres aléatoires
    srand(time(NULL));

    // Création du jeu et ajout des 2 tuiles initiales
    Jeu *jeu = creer_jeu();
    ajouter_tuile(jeu);
    ajouter_tuile(jeu);

    char c;

    // Boucle de jeu principale
    while (1) {
        // Affichage de la grille et du score
        afficher(jeu);

        // Vérification de la victoire ou de la défaite
        if (victoire(jeu)) {
            printf("\n BRAVO ! Vous avez atteint 2048 !\n");
            break;
        }

        if (!mouvements_possibles(jeu)) {
            printf("\n GAME OVER ! Aucun mouvement possible.\n");
            break;
        }

        // Lecture de l'entrée utilisateur
        c = getch();
        int mouvement_effectue = 1;

        // Traitement de l'entrée utilisateur
        switch (c) {

            case 'q':
            case 'Q':
                deplacer_gauche(jeu);
                break;

            case 'd':
            case 'D':
                pivoter(jeu); pivoter(jeu);
                deplacer_gauche(jeu);
                pivoter(jeu); pivoter(jeu);
                break;

            case 'z':
            case 'Z':
                pivoter(jeu); pivoter(jeu); pivoter(jeu);
                deplacer_gauche(jeu);
                pivoter(jeu);
                break;

            case 's':
            case 'S':
                pivoter(jeu);
                deplacer_gauche(jeu);
                pivoter(jeu); pivoter(jeu); pivoter(jeu);
                break;

            case 'x':
            case 'X':
                printf("\nAu revoir !\n");
                detruire_jeu(jeu);
                return 0;

            case 'r':
            case 'R':
                detruire_jeu(jeu);
                jeu = creer_jeu();
                ajouter_tuile(jeu);
                ajouter_tuile(jeu);
                mouvement_effectue = 0;
                break;

            default:
                mouvement_effectue = 0;
                printf("\n\x1b[91mTouche invalide ! Utilise Z Q S D, X ou R.\x1b[0m\n");
                system("pause");
                break;
        }

        // Si un mouvement a été effectué, ajouter une nouvelle tuile
        if (mouvement_effectue)
            ajouter_tuile(jeu);
        }

    // Détruire le jeu
    detruire_jeu(jeu);
    return 0;
}
