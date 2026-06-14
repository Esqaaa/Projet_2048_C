#include <stdio.h>

#define RESET   "\x1b[0m"
#define NEON    "\x1b[38;5;199m"   // rose néon
#define NEON2   "\x1b[38;5;51m"    // bleu néon

// Affiche le titre du jeu en ASCII art avec des couleurs néon
void afficher_ascii() {
    printf(NEON"  ____   ___  _  _   ___  \n"RESET);
    printf(NEON" |___ \\ / _ \\| || | / _ \\ \n"RESET);
    printf(NEON"   __) | | | | || || (_) |\n"RESET);
    printf(NEON"  / __/| | | |__   _> _ < \n"RESET);
    printf(NEON" |_____|_| |_|  |_|/_/ \\_\\\n"RESET);
    printf(NEON2"           2048\n\n"RESET);
}
