/**
 * Programme qui tente de trouver des parcours de cavalier � partir d'une
 * position de d�part quelconque sur un �chiquier.
 *
 * @author Nicolas Levasseur
 */
#include <stdbool.h>
#include <stdio.h>

/* Nom du fichier contenant les positions de d�part du cavalier */
#define NOM_FICHIER_LU "positions.txt"
/* Nom du fichier o� on va �crire le parcours du cavalier */
#define NOM_FICHIER_ECRIT "parcours.txt"
/* Nombre de colonnes de l'�chiquier */
#define X_MAX 6
/* Nombre de rang�es de l'�chiquier */
#define Y_MAX X_MAX

/**
 * Cette fonction lit des param�tres (une position sur un �chiquier) contenu
 * dans un fichier et place les nouvelles valeurs directement dans les
 * variables gr�ce � un pointeur. Ces param�tres sont ensuite convertis pour
 * �tre des indices valides pour un tableau stockant les positions sur un
 * �chiquier.
 *
 * @param fichier: Fichier dans lequel on doit aller lire la valeurs des
 * param�tres.
 * @param xInit: Param�tre devant �tre lu en premier dans le fichier, devrait
 * �tre le num�ro de la colonne de d�part (commence � 0).
 * @param yInit: Param�tre devant �tre lu en deuxi�me dans le fichier, devrait
 * �tre le num�ro de la rang�e de d�part (commence � 0).
 *
 * @return 0 si la lecture s'est effectu�e sans probl�me, 1 si on est arriv�
 * au bout du fichier, 2 si la lecture a �chou� pour une autre raison.
 */
int trouve_pos_init(FILE* fichier, int* xInit, int* yInit) {
    /* Variables temporaires pour assigner les vrais pram�tres � des valeurs
     * valides */
    const char temp1, temp2;
    const int valeurRetour = fscanf(fichier, " %c%c", &temp1, &temp2);

    *xInit = temp1 - 'a';
    *yInit = temp2 - '1';

    /* D�roulement normal */
    if (valeurRetour == 2) return 0;

    /* On d�termine l'erreur */
    if (valeurRetour == EOF) return 1;
    return 2;
}

/**
 * Cette fonction initialise toutes les cases d'une repr�sentation d'un
 * �chiquier � 0, sauf pour la position initiale du cavalier qui est
 * initialis�e � 1.
 *
 * @param echiquier: Matrice repr�sentant un �chiquier.
 * @param xInit: Num�ro de colonne au d�part du cavalier.
 * @param yInit: Num�ro de rang�e au d�part du cavalier.
 */
void init_echiquier(int echiquier[][X_MAX], const int xInit, const int yInit) {
    for (int i = 0; i < X_MAX; i++)
        for (int j = 0; j < Y_MAX; j++) echiquier[i][j] = 0;

    echiquier[yInit][xInit] = 1;
}

/**
 * Fonction r�cursive qui teste le parcours du cavalier par une m�thode de
 * force brute accompagn�e de backtracking. Cette fonction modifie
 * l'�chiquier directement en m�moire afin de noter l'ordre des d�placements du
 * cavalier.
 *
 * @param echiquier: Matrice repr�sentant l'�chiquer.
 * @param x: Num�ro de colonne de la case courante.
 * @param y: Num�ro de rang�e de la case courante.
 * @param dx: D�placement en nombre de colonnes du cavalier.
 * @param dy: D�placement en nombre de rang�es du cavalier.
 * @param numCoup: Num�ro du coup courant.
 *
 * @return true si on peut poursuivre le parcours, false sinon.
 */
bool essai(int echiquier[][X_MAX], const int x, const int y, const int dx[],
           const int dy[], const int numCoup) {
    /* Indice du prochain coup */
    int iProchainCoup = 0;
    /* Indique si on a r�ussi � trouver comment poursuivre le parcours. */
    bool succes = false;
    /* Num�ro de colonne d'une case candidate */
    int xCandidat;
    /* Num�ro de rang�e d'une case candidate */
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
 * directement l'�chiquier afin d'y mettre l'ordre des coups.
 *
 * @param echiquier: Matrice repr�sentant l'�chiquer qui garde en m�moire
 * l'ordre de visite de chaque case par le cavalier.
 * @param xInit: Num�ro de colonne de d�part du cavalier (on commence � 0).
 * @param yInit: Num�ro de rang�e de d�part du cavalier (on commence � 0).
 */
void trouve_parcours(int echiquier[][X_MAX], const int xInit,
                     const int yInit) {
    /* D�placement en nombre de colonnes du cavalier */
    const int dx[] = {-2, -2, -1, -1, 1, 1, 2, 2};
    /* D�placement en nombre de rang�es du cavalier */
    const int dy[] = {-1, 1, -2, 2, -2, 2, -1, 1};

    essai(echiquier, xInit, yInit, dx, dy, 2);
}

/**
 * Cette fonction �crit le parcours d'un cavalier sur un �chiquier dans un
 * fichier donn� en param�tre.
 *
 * @param fichier: Fichier dans lequel on va �crire le parcours
 * @param echiquier: Matrice repr�sentant l'ordre d'arriv�e du cavalier sur
 * chaque case d'un �chiquier.
 * @param xInit: Num�ro de colonne du cavalier au d�but (on commence � 0).
 * @param yInit: Num�ro de rang�e du cavalier au d�but (on commence � 0).
 */
void ecrit_parcours(FILE* fichier, const int echiquier[][X_MAX],
                    const int xInit, const int yInit) {
    fprintf(fichier, "Solution pour la position initiale: %c%d\n\n",
            (char)((char)xInit + 'a'), yInit + 1);

    for (int i = Y_MAX - 1; i >= 0; i--) {
        /* On met le num�ro de la rang�e */
        fprintf(fichier, "%d   ", i + 1);

        /* On affiche les d�placements du cavalier */
        for (int j = 0; j < X_MAX; j++)
            fprintf(fichier, " %2d", echiquier[i][j]);

        fprintf(fichier, "\n");
    }

    /* On �crit la lettre de la colonne */
    fprintf(fichier, "    ");
    for (int i = 0; i < X_MAX; i++) fprintf(fichier, "  %c", 'a' + i);

    fprintf(fichier, "\n\n");
}

int main() {
    /* Fichier dans lequel on a stock� les positions initiales du cavalier �
     * �tudier */
    FILE* fichierLu = fopen(NOM_FICHIER_LU, "r");
    /* �chec de l'ouverture */
    if (fichierLu == NULL) {
        printf("Incapable d'ouvrir le fichier %s!!!\n", NOM_FICHIER_LU);
        return 1;
    }

    /* Fichier dans lequel on va montrer le parcours du cavalier �tudi� */
    FILE* fichierEcrit = fopen(NOM_FICHIER_ECRIT, "w");
    /* �chec de l'ouverture */
    if (fichierEcrit == NULL) {
        printf("Incapable d'ouvrir le fichier %s!!!\n", NOM_FICHIER_ECRIT);
        return 1;
    }

    /* Matrice repr�sentant l'�chiquer */
    int echiquier[Y_MAX][X_MAX];

    /* Num�ro de la colonne o� commence le cavalier */
    int xInit;
    /* Num�ro de la rang�e o� commence le cavalier */
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
