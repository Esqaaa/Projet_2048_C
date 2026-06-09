#include <stdio.h>

// Association des valeurs de tuiles à des couleurs ANSI
#define RESET   "\x1b[0m"
#define GRIS    "\x1b[90m"
#define JAUNE   "\x1b[93m"
#define ORANGE  "\x1b[38;5;208m"
#define ROUGE   "\x1b[91m"
#define VERT    "\x1b[92m"
#define BLEU    "\x1b[94m"
#define VIOLET  "\x1b[95m"

// Retourne la couleur ANSI pour une valeur de tuile donnée
const char* couleur(int valeur) {
    switch (valeur) {
        case 2:   return GRIS;
        case 4:   return JAUNE;
        case 8:   return ORANGE;
        case 16:  return ROUGE;
        case 32:  return VERT;
        case 64:  return BLEU;
        case 128: return VIOLET;
        case 256: return JAUNE;
        case 512: return ORANGE;
        case 1024:return ROUGE;
        case 2048:return VERT;
        default:  return RESET;
    }
}
