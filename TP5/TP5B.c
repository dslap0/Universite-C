/**
 * Programme qui tente de trouver des parcours de cavalier à partir d'une
 * position de départ quelconque sur un échiquier.
 *
 * @author Nicolas Levasseur
 */
#include <stdbool.h>
#include <stdio.h>

/* Nom du fichier contenant les positions de départ du cavalier */
#define NOM_FICHIER_LU "positions.txt"
/* Nom du fichier où on va écrire le parcours du cavalier */
#define NOM_FICHIER_ECRIT "parcours.txt"
/* Nombre de colonnes de l'échiquier */
#define X_MAX 6
/* Nombre de rangées de l'échiquier */
#define Y_MAX X_MAX

/**
 * Cette fonction lit des paramètres (une position sur un échiquier) contenu
 * dans un fichier et place les nouvelles valeurs directement dans les
 * variables grâce à un pointeur. Ces paramètres sont ensuite convertis pour
 * être des indices valides pour un tableau stockant les positions sur un
 * échiquier.
 *
 * @param fichier: Fichier dans lequel on doit aller lire la valeurs des
 * paramètres.
 * @param xInit: Paramètre devant être lu en premier dans le fichier, devrait
 * être le numéro de la colonne de départ (commence à 0).
 * @param yInit: Paramètre devant être lu en deuxième dans le fichier, devrait
 * être le numéro de la rangée de départ (commence à 0).
 *
 * @return 0 si la lecture s'est effectuée sans problème, 1 si on est arrivé
 * au bout du fichier, 2 si la lecture a échoué pour une autre raison.
 */
int trouve_pos_init(FILE* fichier, int* xInit, int* yInit) {
    /* Variables temporaires pour assigner les vrais pramètres à des valeurs
     * valides */
    const char temp1, temp2;
    const int valeurRetour = fscanf(fichier, " %c%c", &temp1, &temp2);

    *xInit = temp1 - 'a';
    *yInit = temp2 - '1';

    /* Déroulement normal */
    if (valeurRetour == 2) return 0;

    /* On détermine l'erreur */
    if (valeurRetour == EOF) return 1;
    return 2;
}

/**
 * Cette fonction initialise toutes les cases d'une représentation d'un
 * échiquier à 0, sauf pour la position initiale du cavalier qui est
 * initialisée à 1.
 *
 * @param echiquier: Matrice représentant un échiquier.
 * @param xInit: Numéro de colonne au départ du cavalier.
 * @param yInit: Numéro de rangée au départ du cavalier.
 */
void init_echiquier(int echiquier[][X_MAX], const int xInit, const int yInit) {
    for (int i = 0; i < X_MAX; i++)
        for (int j = 0; j < Y_MAX; j++) echiquier[i][j] = 0;

    echiquier[yInit][xInit] = 1;
}

/**
 * Fonction récursive qui teste le parcours du cavalier par une méthode de
 * force brute accompagnée de backtracking. Cette fonction modifie
 * l'échiquier directement en mémoire afin de noter l'ordre des déplacements du
 * cavalier.
 *
 * @param echiquier: Matrice représentant l'échiquer.
 * @param x: Numéro de colonne de la case courante.
 * @param y: Numéro de rangée de la case courante.
 * @param dx: Déplacement en nombre de colonnes du cavalier.
 * @param dy: Déplacement en nombre de rangées du cavalier.
 * @param numCoup: Numéro du coup courant.
 *
 * @return true si on peut poursuivre le parcours, false sinon.
 */
bool essai(int echiquier[][X_MAX], const int x, const int y, const int dx[],
           const int dy[], const int numCoup) {
    /* Indice du prochain coup */
    int iProchainCoup = 0;
    /* Indique si on a réussi à trouver comment poursuivre le parcours. */
    bool succes = false;
    /* Numéro de colonne d'une case candidate */
    int xCandidat;
    /* Numéro de rangée d'une case candidate */
    int yCandidat;

    do {
        /* Calcul de la position de la case candidate */
        xCandidat = x + dx[iProchainCoup];
        yCandidat = y + dy[iProchainCoup];

        /* On teste la position candidate */
        if (xCandidat >= 0 && xCandidat < X_MAX && yCandidat >= 0 &&
            yCandidat < Y_MAX && !echiquier[yCandidat][xCandidat]) {
            echiquier[yCandidat][xCandidat] = numCoup;
            if (numCoup < X_MAX * Y_MAX) {
                succes = essai(echiquier, xCandidat, yCandidat, dx, dy,
                               numCoup + 1);
                if (!succes) echiquier[yCandidat][xCandidat] = 0;
            } else
                succes = true;
        }

        iProchainCoup++;
    } while (!succes && iProchainCoup < 8);

    return succes;
}

/**
 * Fonction qui cherche une solution au parcours du cavalier en sachant sa
 * position initiale. Cette fonction en appelle une autre pour modifier
 * directement l'échiquier afin d'y mettre l'ordre des coups.
 *
 * @param echiquier: Matrice représentant l'échiquer qui garde en mémoire
 * l'ordre de visite de chaque case par le cavalier.
 * @param xInit: Numéro de colonne de départ du cavalier (on commence à 0).
 * @param yInit: Numéro de rangée de départ du cavalier (on commence à 0).
 */
void trouve_parcours(int echiquier[][X_MAX], const int xInit,
                     const int yInit) {
    /* Déplacement en nombre de colonnes du cavalier */
    const int dx[] = {-2, -2, -1, -1, 1, 1, 2, 2};
    /* Déplacement en nombre de rangées du cavalier */
    const int dy[] = {-1, 1, -2, 2, -2, 2, -1, 1};

    essai(echiquier, xInit, yInit, dx, dy, 2);
}

/**
 * Cette fonction écrit le parcours d'un cavalier sur un échiquier dans un
 * fichier donné en paramètre.
 *
 * @param fichier: Fichier dans lequel on va écrire le parcours
 * @param echiquier: Matrice représentant l'ordre d'arrivée du cavalier sur
 * chaque case d'un échiquier.
 * @param xInit: Numéro de colonne du cavalier au début (on commence à 0).
 * @param yInit: Numéro de rangée du cavalier au début (on commence à 0).
 */
void ecrit_parcours(FILE* fichier, const int echiquier[][X_MAX],
                    const int xInit, const int yInit) {
    fprintf(fichier, "Solution pour la position initiale: %c%d\n\n",
            (char)((char)xInit + 'a'), yInit + 1);

    for (int i = Y_MAX - 1; i >= 0; i--) {
        /* On met le numéro de la rangée */
        fprintf(fichier, "%d   ", i + 1);

        /* On affiche les déplacements du cavalier */
        for (int j = 0; j < X_MAX; j++)
            fprintf(fichier, " %2d", echiquier[i][j]);

        fprintf(fichier, "\n");
    }

    /* On écrit la lettre de la colonne */
    fprintf(fichier, "    ");
    for (int i = 0; i < X_MAX; i++) fprintf(fichier, "  %c", 'a' + i);

    fprintf(fichier, "\n\n");
}

int main() {
    /* Fichier dans lequel on a stocké les positions initiales du cavalier à
     * étudier */
    FILE* fichierLu = fopen(NOM_FICHIER_LU, "r");
    /* Échec de l'ouverture */
    if (fichierLu == NULL) {
        printf("Incapable d'ouvrir le fichier %s!!!\n", NOM_FICHIER_LU);
        return 1;
    }

    /* Fichier dans lequel on va montrer le parcours du cavalier étudié */
    FILE* fichierEcrit = fopen(NOM_FICHIER_ECRIT, "w");
    /* Échec de l'ouverture */
    if (fichierEcrit == NULL) {
        printf("Incapable d'ouvrir le fichier %s!!!\n", NOM_FICHIER_ECRIT);
        return 1;
    }

    /* Matrice représentant l'échiquer */
    int echiquier[Y_MAX][X_MAX];

    /* Numéro de la colonne où commence le cavalier */
    int xInit;
    /* Numéro de la rangée où commence le cavalier */
    int yInit;

    while (!trouve_pos_init(fichierLu, &xInit, &yInit)) {
        init_echiquier(echiquier, xInit, yInit);
        trouve_parcours(echiquier, xInit, yInit);
        ecrit_parcours(fichierEcrit, echiquier, xInit, yInit);
    }

    fclose(fichierLu);
    fclose(fichierEcrit);

    return 0;
}
