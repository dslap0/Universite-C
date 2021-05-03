/**
 * Ce programme produit des configurations de bataille navale de manière
 * pseudo-aléatoire en respectant certaines règles.
 *
 * @author Nicolas Levasseur
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* Nom du fichier où on va écrire les positions de départ */
#define NOM_FICHIER "navale.txt"
/* Nombre de colonnes de la grille de jeu */
#define X_MAX 10
/* Nombre de rangées de la grille de jeu */
#define Y_MAX X_MAX
/* Nombre d'orientations possibles pour un navire */
#define NBR_ORIENTATIONS 4
/* Nombre de navires à afficher (aussi la taille du plus grand) */
#define NBR_NAVIRES 5

/**
 * Cette fonction initialise toutes les cases d'une représentation d'une
 * grille de jeu de bataille navale avant de placer les navires.
 *
 * @param grille: Matrice représentant une grille du jeu de bataille navale.
 */
void init_grille(char grille[][X_MAX]) {
    for (int i = 0; i < X_MAX; i++)
        for (int j = 0; j < Y_MAX; j++) grille[i][j] = '-';
}

/**
 * Fonction qui trouve le nom du navire en fonction de sa longueur.
 *
 * @param longueur: Longueur du navire dont on cherche le nom.
 *
 * @return La première lettre du nom du navire.
 */
char trouve_nom(int longueur) {
    switch (longueur) {
        case 5:
            return 'P';
        case 4:
            return 'C';
        case 3:
            return 'D';
        case 2:
            return 'V';
        case 1:
            return 'S';
        default:
            return '-';
    }
}

/**
 * Cette fonction valide l'orientation d'un navire et place celui-ci dans la
 * grille du jeu si ladite orientation est validée. Il faudrait probablement
 * trouver un moyen d'améliorer la lisibilité du corps de la fonction ici, à
 * considérer si cette fonction est réutilisée
 *
 * @param grille: Matrice représentant une grille du jeu de bataille navale.
 * @param posDebutX: Numéro de colonne du début du navire courant.
 * @param posDebutY: Numéro de rangée du début du navire courant.
 * @param orientation: Orientation du navire courant, 0 étant vers la droite, 1
 * étant vers le bas, 2 étant vers la gauche et 3 étant vers le haut.
 * @param longueur: Longueur du navire à placer.
 * @param nom: Lettre à écrire pour représenter le navire.
 * @param zoneSec: Zone de sécurité autour du navire.
 */
bool valide_orientation(char grille[][X_MAX], const int posDebutX,
                        const int posDebutY, const int orientation,
                        const int longueur, const char nom,
                        const int zoneSec) {
    /* On teste la longueur du navire pour savoir si c'est le premier qu'on
     * place */
    bool testLongueur = longueur == NBR_NAVIRES ? true : false;

    /* On teste si l'ensemble du navire reste sur la grille et si l'ensemble du
     * navire est sur une case libre */
    switch (orientation) {
        /* Instructions quand le navire est orienté vers la droite */
        case 0:
            if (posDebutX + longueur >= X_MAX) return false;
            if (!testLongueur)
                for (int i = 1; i < longueur; i++)
                    if (grille[posDebutY][posDebutX + i] != '-') return false;

            /* On place le navire et sa zone de sécurité */
            for (int i = 1; i <= zoneSec; i++) {
                if (posDebutX - i >= 0) grille[posDebutY][posDebutX - i] = 'z';
                if (posDebutX + i + longueur - 1 < Y_MAX)
                    grille[posDebutY][posDebutX + i + longueur - 1] = 'z';
            }

            for (int i = 0; i < longueur; i++) {
                /* Position en x de la section courante du navire */
                int posX = posDebutX + i;

                /* On place la zone de sécurtié */
                for (int posSec = posDebutY - zoneSec;
                     posSec <= posDebutY + zoneSec; posSec++)
                    /* On vérifie que la zone de sécurité est dans la grille */
                    if (posSec >= 0 && posSec < Y_MAX)
                        grille[posSec][posX] = 'z';

                /* On place le navire */
                grille[posDebutY][posX] = nom;
            }
            break;
        /* Instructions quand le navire est orienté vers le bas */
        case 1:
            if (posDebutY - longueur < -1) return false;
            if (!testLongueur)
                for (int i = 1; i < longueur; i++)
                    if (grille[posDebutY - i][posDebutX] != '-') return false;

            /* On place le navire et sa zone de sécurité */
            for (int i = 1; i <= zoneSec; i++) {
                if (posDebutY - i - longueur >= -1)
                    grille[posDebutY - i - longueur + 1][posDebutX] = 'z';
                if (posDebutY + i < Y_MAX)
                    grille[posDebutY + i][posDebutX] = 'z';
            }

            for (int i = 0; i < longueur; i++) {
                /* Position en y de la section courante du navire */
                int posY = posDebutY - i;

                /* On place la zone de sécurtié */
                for (int posSec = posDebutX - zoneSec;
                     posSec <= posDebutX + zoneSec; posSec++)
                    /* On vérifie que la zone de sécurité est dans la grille */
                    if (posSec >= 0 && posSec < X_MAX)
                        grille[posY][posSec] = 'z';

                /* On place le navire */
                grille[posY][posDebutX] = nom;
            }
            break;
        /* Instructions quand le navire est orienté vers la gauche */
        case 2:
            if (posDebutX - longueur < -1) return false;
            if (!testLongueur)
                for (int i = 1; i < longueur; i++)
                    if (grille[posDebutY][posDebutX - i] != '-') return false;

            /* On place le navire et sa zone de sécurité */
            for (int i = 1; i <= zoneSec; i++) {
                if (posDebutX - i - longueur >= -1)
                    grille[posDebutY][posDebutX - i - longueur + 1] = 'z';
                if (posDebutX + i < Y_MAX)
                    grille[posDebutY][posDebutX + i] = 'z';
            }

            for (int i = 0; i < longueur; i++) {
                /* Position en x de la section courante du navire */
                int posX = posDebutX - i;

                /* On place la zone de sécurtié */
                for (int posSec = posDebutY - zoneSec;
                     posSec <= posDebutY + zoneSec; posSec++)
                    /* On vérifie que la zone de sécurité est dans la grille */
                    if (posSec >= 0 && posSec < Y_MAX)
                        grille[posSec][posX] = 'z';

                /* On place le navire */
                grille[posDebutY][posX] = nom;
            }
            break;
        /* Instructions quand le navire est orienté vers le haut */
        case 3:
            if (posDebutY + longueur >= Y_MAX) return false;
            if (!testLongueur)
                for (int i = 1; i < longueur; i++)
                    if (grille[posDebutY + i][posDebutX] != '-') return false;

            /* On place le navire et sa zone de sécurité */
            for (int i = 1; i <= zoneSec; i++) {
                if (posDebutY - i >= 0) grille[posDebutY - i][posDebutX] = 'z';
                if (posDebutY + i + longueur - 1 < Y_MAX)
                    grille[posDebutY + i + longueur - 1][posDebutX] = 'z';
            }

            for (int i = 0; i < longueur; i++) {
                /* Position en y de la section courante du navire */
                int posY = posDebutY + i;

                /* On place la zone de sécurtié */
                for (int posSec = posDebutX - zoneSec;
                     posSec <= posDebutX + zoneSec; posSec++)
                    /* On vérifie que la zone de sécurité est dans la grille */
                    if (posSec >= 0 && posSec < X_MAX)
                        grille[posY][posSec] = 'z';

                /* On place le navire */
                grille[posY][posDebutX] = nom;
            }
            break;
    }

    /* Si après tous nos tests on arrive ici, alors on a une orientation valide
     * et on aura aussi placé le navire */
    return true;
}

/**
 * Cette fonction place tous les navires du jeu bataille navale sur la grille
 * passée en paramètre, en commençant par le plus gros. Ce placement est fait
 * de manière pseudo-aléatoire, tout en respectant certaines règles de
 * placement. Les navires sont représentés par la première lettre de leur nom,
 * et leurs longueurs respectives vont comme suit: porte-avion = 5, croiseur =
 * 4, destroyer = 3, vedette = 2, sous-marin = 1.
 *
 * @param grille: Matrice représentant une grille du jeu de bataille navale.
 * @param zoneSec: Zone de sécurité où les autres navires ne peuvent pas être
 * autour d'un navire.
 */
void place_navires(char grille[][X_MAX], int zoneSec) {
    /* Position du début du navire courant (en numéro de colonne et de rangée)
     */
    int posDebutX, posDebutY;

    /* Orientation du navire courant, 0 étant vers la droite, 1 étant vers le
     * bas, 2 étant vers la gauche et 3 étant vers le haut */
    int orientation;

    /* Valeur nous indiquant si la position actuelle a été confirmée comme
     * valide */
    bool posValide;

    /* Lettre utilisée pour désigner le navire dans la grille */
    char nom;

    /* On trouve une position et une orientation valide pour chaque navire et
     * on les mets à ces positions */
    for (int longueur = NBR_NAVIRES; longueur > 0; longueur--) {
        /* On détermine le nom du navire courant */
        nom = trouve_nom(longueur);

        /* On réinitialise les paramètres pour chaque navire */
        posValide = false;

        while (!posValide) {
            /* On cherche une position du début du navire valide */
            do {
                posDebutX = rand() % 10;
                posDebutY = rand() % 10;
            } while (grille[posDebutY][posDebutX] != '-');

            /* L'orientation du sous marin n'a pas besoin d'être déterminée */
            posValide = longueur < 1 ? true : false;

            /* On cherche l'orientation du navire */
            orientation = rand() % NBR_ORIENTATIONS;
            for (int i = 0; i < NBR_ORIENTATIONS; i++) {
                if (valide_orientation(grille, posDebutX, posDebutY,
                                       orientation, longueur, nom, zoneSec)) {
                    posValide = true;
                    break;
                } else
                    orientation = (orientation + 1) % NBR_ORIENTATIONS;
            }
            /* Si on arrive ici, on a pas trouvé d'orientation valide à cette
             * position et on recommence donc tout le processus */
        }
    }
}

/**
 * Fonction qui permet d'afficher une configuration de bataille navale dans un
 * fichier.
 *
 * @param fichier: Fichier dans lequel on va placer la configuration.
 * @param grille: Matrice représentant une configuration de bataille navale.
 */
void montre_grille(FILE* fichier, char grille[][X_MAX]) {
    /* On écrit la lettre de la colonne */
    fprintf(fichier, "    ");
    for (int i = 1; i <= Y_MAX; i++) fprintf(fichier, "  %2d", i);
    fprintf(fichier, "\n");

    for (int i = 0; i < X_MAX; i++) {
        /* On met le numéro de la rangée */
        fprintf(fichier, "  %c ", (char)(i + 'a'));

        /* On affiche la position des navires */
        for (int j = 0; j < Y_MAX; j++){
            grille[j][i] = grille[j][i] == 'z' ? '-' : grille[j][i];
            fprintf(fichier, "   %c", grille[j][i]);
        }

        fprintf(fichier, "\n");
    }

    fprintf(fichier, "\n");
}

int main() {
    /* Fichier dans lequel on va montrer le parcours du cavalier étudié */
    FILE* fichier = fopen(NOM_FICHIER, "w");
    /* Échec de l'ouverture */
    if (fichier == NULL) {
        printf("Incapable d'ouvrir le fichier %s!!!\n", NOM_FICHIER);
        return 1;
    }

    /* Matrice représentant une grille du jeu de bataille navale */
    char grille[Y_MAX][X_MAX];

    /* Initialisation du germe aléatoire du programme */
    srand(1969);

    /* On trouve les configurations demandées */
    for (int i = 0; i < 6; i++) {
        init_grille(grille);
        place_navires(grille, i / 2 + 1);
        montre_grille(fichier, grille);
    }

    fclose(fichier);

    return 0;
}
