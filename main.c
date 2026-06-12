#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

extern int TAILLE;

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
void deplacer_droite(Jeu *jeu);
void deplacer_haut(Jeu *jeu);
void deplacer_bas(Jeu *jeu);

void sauvegarder(Jeu *jeu);
void charger(Jeu *jeu);

// Fonctions de logique du jeu
int mouvements_possibles(Jeu *jeu);
int victoire(Jeu *jeu);
int defaite(Jeu *jeu);

// Fonction principale
int main() {

    afficher_ascii();
    system("pause");

    char choix;

    printf("(C) Charger la sauvegarde\n");
    printf("(N) Nouvelle partie\n");
    printf("(X) Quitter\n");
    printf("Votre choix : ");
    choix = getch();

    // Initialisation RNG
    srand(time(NULL));

    Jeu *jeu = NULL;

    if (choix == 'C' || choix == 'c') {

        // Lire la taille dans le fichier AVANT de créer le jeu
        FILE *f = fopen("save.txt", "r");
        if (!f) {
            printf("Aucune sauvegarde trouvée.\n");
            system("pause");
            return 0;
        }

        fscanf(f, "%d", &TAILLE);
        fclose(f);

        // Créer le jeu avec la bonne taille
        jeu = creer_jeu();

        // Charger la sauvegarde
        charger(jeu);
    }
    else if (choix == 'N' || choix == 'n') {

        printf("Choisissez la taille de la grille (3, 4 ou 5) : ");
        scanf("%d", &TAILLE);
        if (TAILLE < 3 || TAILLE > 5) {
            printf("Taille invalide ! Utilisation de 4x4.\n");
            TAILLE = 4;
        }

        jeu = creer_jeu();
        ajouter_tuile(jeu);
        ajouter_tuile(jeu);
    }
    else {
        return 0;
    }

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

        if (defaite(jeu)) {
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
                deplacer_droite(jeu);
                break;

            case 'z':
            case 'Z':
                deplacer_haut(jeu);
                break;

            case 's':
            case 'S':
                deplacer_bas(jeu);
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
                printf("\n\x1b[91mTouche invalide ! Utilise Z Q S D pour bouger, X, W, C ou R.\x1b[0m\n");
                system("pause");
                break;

            case 'w':
            case 'W':
                sauvegarder(jeu);
                break;
            
            case 'c':
            case 'C':
                charger(jeu);
                mouvement_effectue = 0;
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
