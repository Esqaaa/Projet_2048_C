#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

int TAILLE = 4;

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

    // Initialisation du générateur de nombre aléatoire
    srand(time(NULL));

    // Pointeur vers le jeu
    Jeu *jeu = NULL;

    if (choix == 'C' || choix == 'c') {

        // Lire la taille dans le fichier avant de créer le jeu
        FILE *f = fopen("save.txt", "r");
        if (!f) {
            // Le fichier n'existe pas -> Pas de sauvegarde disponible
            printf("Aucune sauvegarde trouvee.\n");
            system("pause");
            return 0;
        }

        // On lit la première valeur du fichier qui contient la taille de la grille
        fscanf(f, "%d", &TAILLE);
        fclose(f);

        // Créer le jeu avec la bonne taille
        jeu = creer_jeu();

        // Charger la sauvegarde avec les valeurs sauvegardées
        charger(jeu);
    }
    else if (choix == 'N' || choix == 'n') {
    
        // Le joueur choisit sa taille de grille
        printf("Choisissez la taille de la grille (3, 4 ou 5) : ");
        scanf("%d", &TAILLE);

        // Vérification que la taille est valide, sinon 4x4 par défaut
        if (TAILLE < 3 || TAILLE > 5) {
            printf("Taille invalide ! Utilisation de 4x4.\n");
            TAILLE = 4;
        }

        // Création du jeu puis ajout de 2 tuiles pour débuter la partie
        jeu = creer_jeu();
        ajouter_tuile(jeu);
        ajouter_tuile(jeu);
    }
    else {
        // Touche inconnue ou "X" -> on quitte simplement le programme
        return 0;
    }

    char c;

    // Boucle de jeu principale
    while (1) {
        // Affichage de la grille et du score
        system("cls");
        afficher(jeu);

        // Vérification de la victoire ou de la défaite
        if (victoire(jeu)) {
            printf("\n BRAVO ! Vous avez atteint 2048 !\n");
            break;
        }

        // Vérification de la défaite
        if (defaite(jeu)) {
            printf("\n GAME OVER ! Aucun mouvement possible.\n");
            break;
        }

        // Lecture de l'entrée utilisateur
        c = getch();
        int mouvement_effectue = 1;

        // Traitement de l'entrée utilisateur
        switch (c) {

            // Cas de la touche "q" ou "Q" pour déplacer à gauche
            case 'q':
            case 'Q':
                deplacer_gauche(jeu);
                break;

            // Cas de la touche "d" ou "D" pour déplacer à droite
            case 'd':
            case 'D':
                deplacer_droite(jeu);
                break;

            // Cas de la touche "z" ou "Z" pour déplacer vers le haut
            case 'z':
            case 'Z':
                deplacer_haut(jeu);
                break;

            // Cas de la touche "s" ou "S" pour déplacer vers le bas
            case 's':
            case 'S':
                deplacer_bas(jeu);
                break;

            // Cas de la touche "x" ou "X" pour quitter le jeu
            case 'x':
            case 'X':
                printf("\nAu revoir !\n");
                detruire_jeu(jeu);
                return 0;

            // Cas de la touche "r" ou "R" pour recommencer une partie
            case 'r':
            case 'R':
                detruire_jeu(jeu);
                jeu = creer_jeu();
                ajouter_tuile(jeu);
                ajouter_tuile(jeu);
                mouvement_effectue = 0;
                break;

            // Cas de la touche "w" ou "W" pour sauvegarder une partie en cours
            case 'w':
            case 'W':
                sauvegarder(jeu);
                mouvement_effectue = 0;
                break;

            // Cas de la touche "c" ou "C" pour charger une sauvegarde
            case 'c':
            case 'C':
                {
                    FILE *f_load = fopen("save.txt", "r");
                    if (f_load) {
                        fscanf(f_load, "%d", &TAILLE);
                        fclose(f_load);
                        
                        detruire_jeu(jeu); // On détruit l'ancienne grille en cours
                        jeu = creer_jeu(); // On reconstruit à la bonne taille
                        charger(jeu);      // On applique les valeurs chargées
                    } else {
                        printf("\nErreur: Fichier de sauvegarde introuvable.\n");
                        system("pause");
                    }
                }
                mouvement_effectue = 0; // Pas de nouvelle tuile lors d'un chargement
                break;
            
            // Cas par défaut
            default:
                mouvement_effectue = 0;
                printf("\n\x1b[91mTouche invalide ! Utilise Z Q S D pour bouger, X, W, C ou R.\x1b[0m\n");
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
