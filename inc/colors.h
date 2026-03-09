/**
 * @file colors.h
 * @brief Utilitaires pour la manipulation des couleurs et styles du terminal ANSI.
 * @details Permet de changer la couleur du texte, de l'arrière-plan et la graisse.
 * Valable en CPP et C
 */

#ifndef COLORS_H
#define COLORS_H

#include <stdio.h>

/** @brief Réinitialise tous les attributs (couleurs et styles). */
#define RESET       "\033[0m"

/** @brief Active le texte en gras. */
#define BOLD        "\033[1m"

/** @defgroup Foreground Couleurs de texte */
/*@{*/
#define F_BLACK     "\033[30m" /**< Texte Noir */
#define F_RED       "\033[31m" /**< Texte Rouge */
#define F_GREEN     "\033[32m" /**< Texte Vert */
#define F_YELLOW    "\033[33m" /**< Texte Jaune */
#define F_BLUE      "\033[34m" /**< Texte Bleu */
#define F_PURPLE    "\033[35m" /**< Texte Violet */
#define F_CYAN      "\033[36m" /**< Texte Cyan */
#define F_WHITE     "\033[37m" /**< Texte Blanc */
/*@}*/

/** @defgroup Background Couleurs d'arrière-plan */
/*@{*/
#define B_BLACK     "\033[40m" /**< Fond Noir */
#define B_RED       "\033[41m" /**< Fond Rouge */
#define B_GREEN     "\033[42m" /**< Fond Vert */
#define B_YELLOW    "\033[43m" /**< Fond Jaune */
#define B_BLUE      "\033[44m" /**< Fond Bleu */
#define B_PURPLE    "\033[45m" /**< Fond Violet */
#define B_CYAN      "\033[46m" /**< Fond Cyan */
#define B_WHITE     "\033[47m" /**< Fond Blanc */
/*@}*/

/**
 * @brief Change la couleur du texte dans le terminal.
 * @details Réinitialise le style avant d'appliquer la nouvelle couleur.
 * @param code La chaîne de caractères contenant le code ANSI (F_BLACK, F_RED, F_GREEN, F_YELLOW, F_BLUE, F_PURPLE, F_CYAN, F_WHITE) ou RESET pour defaut.
 */
inline void colors(const char *code) {
    if (code) printf("%s", code);
}

/**
 * @brief Configure le style complet du terminal en une seule commande.
 * @details Réinitialise le style avant d'appliquer les nouveaux paramètres.
 *
 * @param text Code couleur du texte (F_BLACK, F_RED, F_GREEN, F_YELLOW, F_BLUE, F_PURPLE, F_CYAN, F_WHITE) ou RESET pour defaut.
 * @param bg Code couleur de fond (B_BLACK, B_RED, B_GREEN, B_YELLOW, B_BLUE, B_PURPLE, B_CYAN, B_WHITE) ou RESET pour defaut.
 * @param bold 1 pour activer le gras, 0 pour le style normal.
 */
inline void set_style(const char *text, const char *bg, int bold) {
    printf("%s", RESET);
    if (bold) printf("%s", BOLD);
    if (text) printf("%s", text);
    if (bg)   printf("%s", bg);
}

#endif /* COLORS_H */