# 2048 en C

Implémentation du jeu 2048 en console, développée en langage C dans le cadre du module **Langages compilés** à Strasbourg Ynov Campus.

## Fonctionnalités

- Grille de taille variable (3x3, 4x4 ou 5x5)
- Déplacements avec les touches Z Q S D
- Fusion des tuiles et calcul du score
- Affichage coloré en console (couleurs ANSI)
- Sauvegarde et chargement de partie
- Conditions de victoire (2048) et de défaite

## Installation et lancement

> Requiert un compilateur GCC

```bash
git clone https://github.com/Esqaaa/Projet_2048_C.git
cd Projet_2048_C
gcc main.c jeu.c affichage.c couleur.c ascii.c sauvegarde.c -o Jeu2048
./Jeu2048
```

## Utilisation

Au lancement, un menu s'affiche :

```
(C) Charger la sauvegarde
(N) Nouvelle partie
(X) Quitter
```

En jeu :

| Touche | Action      |
|--------|-------------|
| Z      | Haut        |
| Q      | Gauche      |
| S      | Bas         |
| D      | Droite      |
| W      | Sauvegarder |
| R      | Recommencer |
| C      | Charger     |
| X      | Quitter     |

## Structure du projet

```
├── main.c          # Boucle principale et gestion des entrées
├── jeu.c           # Logique du jeu (déplacements, fusions, victoire)
├── affichage.c     # Rendu de la grille en console
├── couleur.c       # Couleurs ANSI selon la valeur des tuiles
├── ascii.c         # Titre ASCII art au lancement
└── sauvegarde.c    # Lecture et écriture de la sauvegarde
```

> Le fichier `save.txt` est généré automatiquement à la première sauvegarde.

## Concepts C utilisés

- Allocation dynamique (`malloc`, `calloc`, `free`)
- Pointeurs et tableaux 2D dynamiques
- Gestion d'erreurs (vérification des retours de `malloc`)
- Découpage en plusieurs fichiers `.c`
- Variable globale `extern`

## Auteur

Hugo — Strasboueg Ynov Campus - B1 Cyber — Juin 2026
