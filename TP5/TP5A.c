/**
 * Ce programme trouve les n-tuplets (n donn� par l'utilisateur) dont la somme
 * donne somme (somme aussi donn�e par l'utilisateur), en utilisant les entiers
 * de 1 � max (max donne par l'utilisateur), sans r�peter le m�me entier dans
 * le m�me tuplet et sans r�p�ter les tuplets en changeant seulement l'ordre
 * d'apparition des entiers � l'int�rieur.
 *
 * @author: Nicolas Levasseur
 */
#include <stdio.h>
#include <stdlib.h>

/* Nom du fichier contenant les param�tres pour trouver les tuplets */
#define NOM_FICHIER_LU "dontuplets.txt"
/* Nom du fichier o� on va �crire les r�sultats du programme */
#define NOM_FICHIER_ECRIT "restuplets.txt"

/**
 * Cette fonction lit des param�tres contenu dans un fichier et place les
 * nouvelles valeurs directement dans les variables gr�ce � un pointeur.
 *
 * @param fichier: Fichier dans lequel on doit aller lire la valeurs des
 * param�tres.
 * @param param1: Param�tre devant �tre lu en premier dans le fichier.
 * @param param2: Param�tre devant �tre lu en deuxi�me dans le fichier.
 * @param param3: Param�tre devant �tre lu en troisi�me dans le fichier.
 *
 * @return 0 si la lecture s'est effectu�e sans probl�me, 1 si on est arriv�
 * au bout du fichier, 2 si la lecture a �chou� pour une autre raison.
 */
int lire_parametres(FILE* fichier, const int* param1, const int* param2,
                    const int* param3) {
    const int valeurRetour = fscanf(fichier, "%d%d%d", param1, param2, param3);

    /* D�roulement normal */
    if (valeurRetour == 3) return 0;

    /* On d�termine l'erreur */
    if (valeurRetour == EOF) return 1;
    return 2;
}

/**
 * Fonction qui modifie un tableau pass� en param�tre pour y mettre les sommes
 * partielles maximales associ�e � un certain nombre d'�l�ments et � un certain
 * maximum parmis lesdits �l�ments.
 *
 * @param max: Entier maximum qui peut composer le tuplet.
 * @param n: Nombre d'entiers composant le tuplet.
 * @param sommePartielleMax: Tableau qui sera modifi� pour accueillir les
 * sommes partielles maximales.
 */
void calcul_sommes_partielles_max(const int max, const int n,
                                  int sommePartielleMax[]) {
    for (int i = 0; i < n; i++) {
        sommePartielleMax[i] = 0;
        for (int j = max - i; j <= max; j++) sommePartielleMax[i] += j;
    }
}

/**
 * Cette fonction permet de g�n�rer le prochain tuplet � analyser. Celui-ci est
 * plac� dans le tableau tupletCour directement.
 *
 * @param n: Nombre d'entiers composant le tuplet.
 * @param somme: Somme � obtenir en addition les �l�ments du tuplet ensembles.
 * @param tupletPrec: Tableau repr�sentant l'essai pr�c�dent d'un tuplet.
 * @param tupletCour: Tableau repr�sentant l'essai courant d'un tuplet.
 * @param posTransition: Position de transition dans le tuplet courant.
 */
void former_tuplet(const int n, const int somme, const int tupletPrec[],
                   int tupletCour[], const int posTransition) {
    /* Somme partielle des �l�ments plac�s dans le tuplet courant */
    int sommePartielle = 0;

    for (int i = 0; i < n - 1; i++) {
        /* On d�termine la valeur du i�me �l�ment dans le tuplet courant */
        if (i < posTransition)
            tupletCour[i] = tupletPrec[i];
        else if (i == posTransition)
            tupletCour[i] = tupletPrec[i] + 1;
        else
            tupletCour[i] = tupletCour[i - 1] + 1;

        sommePartielle += tupletCour[i];
    }

    tupletCour[n - 1] = somme - sommePartielle;
}

/**
 * Cette fonction vise � repr�senter un tuplet dans un fichier.
 *
 * @param fichier: Fichier dans lequel on va �crire notre r�pr�sentation de
 * tuplet.
 * @param nElement: Nombre d'�l�ments dans le tuplet � afficher.
 * @param tuplet: Tableau repr�sentant le tuplet � afficher.
 * @param numTuplet: Num�ro du tuplet � afficher.
 */
void montre_tuplet(FILE* fichier, const int nElement, const int tuplet[],
                   const int numTuplet) {
    fprintf(fichier, "Tuplet no. %2d: (%2d", numTuplet, tuplet[0]);
    for (int i = 1; i < nElement; i++) {
        fprintf(fichier, ",%2d", tuplet[i]);
    }
    fprintf(fichier, ")\n");
}

/**
 * Cette fonction cherche � trouver la nouvelle position de transition dans le
 * tuplet courant.
 *
 * @param nElement: Nombre d'entiers composant le tuplet.
 * @param sommePartielleMax: Tableau contenant les sommes partielles maximales.
 * @param tupletCour: Tableau repr�sentant le tuplet courant.
 *
 * @return La nouvelle valeur pour la position de transition.
 */
int calcul_pos_transition(const int nElement, const int sommePartielleMax[],
                          const int tupletCour[]) {
    /* Tableau des sommes partielles du tuplet courant */
    int* sommePartielle = (int*)malloc(sizeof(int) * nElement);
    for (int i = 0; i < nElement; i++) {
        sommePartielle[i] = 0;
        for (int j = nElement - i - 1; j < nElement; j++)
            sommePartielle[i] += tupletCour[j];
    }

    for (int i = nElement - 1; i >= 0; i--)
        if (sommePartielle[i] > sommePartielleMax[i]) {
            free(sommePartielle);
            return nElement - i - 2;
        }
}

/**
 * Fonction qui fait appel � d'autres fonctions pour trouver tous les tuplets
 * valides et les mettre dans un fichier.
 *
 * @param fichier: Fichier o� on va �crire nos r�sultats.
 * @param max: Entier maximum qui peut composer le tuplet.
 * @param nElement: Nombre d'entiers composant le tuplet.
 * @param somme: Somme � obtenir en addition les �l�ments du tuplet ensembles.
 */
void trouver_tuplets(FILE* fichier, const int max, const int nElement,
                     const int somme) {
    /* Numero du tuplet valide � mettre dans le fichier */
    int numTuplet = 1;

    /* Tableau contenant les sommes partielles maximales */
    int* sommePartielleMax = (int*)malloc(sizeof(int) * nElement);
    calcul_sommes_partielles_max(max, nElement, sommePartielleMax);

    /* Tableau repr�sentant l'essai pr�c�dent d'un tuplet */
    int* tupletPrec = (int*)malloc(sizeof(int) * nElement);
    for (int i = 0; i < nElement - 2;) tupletPrec[i++] = i;
    tupletPrec[nElement - 2] = nElement - 2;

    /* Tableau repr�sentant l'essai courant d'un tuplet */
    int* tupletCour = (int*)malloc(sizeof(int) * nElement);

    /* Position de transition dans le tuplet courant */
    int posTransition = nElement - 2;

    /* On g�n�re tous les tuplets possibles et on affiche ceux qui sont
     * valides */
    do {
        former_tuplet(nElement, somme, tupletPrec, tupletCour, posTransition);

        /* On met � jour le tuplet pr�c�dent */
        for (int i = 0; i < nElement; i++) tupletPrec[i] = tupletCour[i];

        /* On teste la position de transition et on change sa valeur */
        if (tupletCour[nElement - 1] <= tupletCour[nElement - 2])
            posTransition--;
        else if (tupletCour[nElement - 1] <= max) {
            /* On a un tuplet valide, alors on l'affiche */
            montre_tuplet(fichier, nElement, tupletCour, numTuplet);
            numTuplet++;
            posTransition = nElement - 2;
        } else
            posTransition =
                calcul_pos_transition(nElement, sommePartielleMax, tupletCour);
    } while (posTransition >= 0);

    free(sommePartielleMax);
    free(tupletPrec);
    free(tupletCour);
}

int main() {
    /* Fichier o� on va lire les param�tres */
    FILE* fichierLu = fopen(NOM_FICHIER_LU, "r");
    /* �chec de l'ouverture */
    if (fichierLu == NULL) {
        printf("Incapable d'ouvrir le fichier %s!!!\n", NOM_FICHIER_LU);
        return 1;
    }

    /* Fichier o� on va �crire les r�sultats */
    FILE* fichierEcrit = fopen(NOM_FICHIER_ECRIT, "w");
    /* �chec de l'ouverture */
    if (fichierEcrit == NULL) {
        printf("Incapable d'ouvrir le fichier %s!!!\n", NOM_FICHIER_LU);
        return 1;
    }

    /* Entier maximum qui peut composer le tuplet */
    int max;
    /* Nombre d'entier composant le tuplet */
    int nElement;
    /* Somme � atteindre par l'addition des membres d'un tuplet */
    int somme;

    /* Boucle principale du programme: on lit les param�tres, on trouve les
     * tuplets et on les �crit dans le fichier de resultats */
    while (!lire_parametres(fichierLu, &max, &nElement, &somme)) {
        fprintf(
            fichierEcrit,
            "Suite des tuplets formes de %d entiers dont la somme est %d \n"
            "et dont chaque entier est <= %d\n\n",
            nElement, somme, max);
        trouver_tuplets(fichierEcrit, max, nElement, somme);
        fprintf(fichierEcrit, "\n");
    }

    fclose(fichierLu);
    fclose(fichierEcrit);

    return 0;
}
