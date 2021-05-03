/**
 * Auteur : Nicolas Levasseur
 *
 * Ce programme trouve la/les racines d'une equation de deuxieme ou de premier
 * degre dont les coefficients ont ete donnes par l'utilisateur, s'occupe des
 * cas ou il y a une infinite de solutions ou aucune solution, et montre le
 * resultat a l'utilisateur, dans une boucle qui se repete jusqu'a ce que
 * l'utilisateur ne lui demande d'arreter.
 */

#include <math.h>
#include <stdio.h>

// On se cree une structure qui emmagasine les nombres complexes
struct complexes {
    float reel;
    float imaginaire;
};

/**
 * Cette fonction trouve la racine de l'equation entree et affiche le resultat
 * a l'utilisateur.
 *
 * b: Coefficient du terme en x.
 * c: Constante.
 */
void calcul_racine_premier_degre(int b, int c) {
    // On trouve la racine
    float racine = -c / b;
    printf("L'equation %dx%+d a une racine reelle: %.2f\n", b, c, racine);
}

/**
 * Cette fonction trouve la/les racines reelles de l'equation entree et affiche
 * le/les resultats a l'utilisateur.
 *
 * a: Coefficient du terme en x2.
 * b: Coefficient du terme en x.
 * c: Constante.
 * delta : Determinant de l'equation entree.
 */
void calcul_racine_reelle(int a, int b, int c, float delta) {
    // On declare notre tableau de stockage des racines
    float racines[2];

    // On trouve les racines
    racines[0] = (-b + sqrt(delta)) / (2.0f * a);
    racines[1] = (-b - sqrt(delta)) / (2.0f * a);

    // On teste le nombre de racines trouvees et on affiche le resultat
    if (racines[0] != racines[1]) {
        printf("L'equation %dx2%+dx%+d a deux racines reelles: %.2f et %.2f\n",
               a, b, c, racines[0], racines[1]);
    }

    else {
        printf("L'equation %dx2%+dx%+d a une racine reelle: %.2f\n", a, b, c,
               racines[0]);
    }
}

/**
 * Cette fonction trouve les racines complexes de l'equation entree et affiche
 * les resultats a l'utilisateur.
 *
 * a: Coefficient du terme en x2.
 * b: Coefficient du terme en x.
 * c: Constante.
 * delta : Determinant de l'equation entree.
 */
void calcul_racine_complexe(int a, int b, int c, float delta) {
    // On declare les racines
    struct complexes racines[2];

    // On trouve les parties reelles des racines
    racines[0].reel = -b / (2 * a);
    racines[1].reel = racines[0].reel;

    // On trouve les parties imaginaires
    racines[0].imaginaire = sqrt(-delta) / (2 * a);
    racines[1].imaginaire = -racines[0].imaginaire;

    // On affiche le resultat
    printf(
        "L'equation %dx2%+dx%+d a deux racines complexes: %.2f%+.2fi et "
        "%.2f%+.2fi\n",
        a, b, c, racines[0].reel, racines[0].imaginaire, racines[1].reel,
        racines[1].imaginaire);
}

/**
 * Cette fonction trouve quelle est la fonction appropriee a appeler pour
 * trouver la/les racines de l'expression. La fonction prends aussi en compte
 * les cas speciaux d'une infinite de solution/d'aucune solution.
 *
 * a: Coefficient du terme en x2.
 * b: Coefficient du terme en x.
 * c: Constante.
 */
void calcul_racine(int a, int b, int c) {
    // On teste si c'est une equation du deuxieme degre
    if (a) {
        // On trouve delta
        float delta = b * b - 4 * a * c;

        // On teste si les racines sont reelles ou complexes
        if (delta >= 0) {
            calcul_racine_reelle(a, b, c, delta);
        } else {
            calcul_racine_complexe(a, b, c, delta);
        }
    } else {
        // On teste si c'est une equation du premier degre
        if (b) {
            calcul_racine_premier_degre(b, c);
        } else {
            // On teste si on a une infinite ou aucune solution
            if (c) {
                printf("Infinite de solutions pour ces coefficients\n");
            } else {
                printf("Aucune solution pour ces coefficients\n");
            }
        }
    }
}

int main() {
    // On declare nos variables
    int a, b, c;
    char rep;

    // On effectue des iterations tant que l'utilisateur le demande
    do {
        // On affiche un message et on collecte les coefficients
        printf(
            "Entrez les coefficients ax2 + bx + c dont on cherche les "
            "0:\n");
        scanf("%d%d%d", &a, &b, &c);

        // On calcule les racines
        calcul_racine(a, b, c);

        // On verifie si on execute encore une iteration
        printf("Voulez-vous continuer?\n");
        scanf(" %c", &rep);
    } while (rep == 'o');

    return 0;
}

/*
Entrez les coefficients ax2 + bx + c dont on cherche les 0:
1 0 -121
L'equation 1x2+0x-121 a deux racines reelles: 11.00 et -11.00
Voulez-vous continuer?
o
Entrez les coefficients ax2 + bx + c dont on cherche les 0:
16 -24 9
L'equation 16x2-24x+9 a une racine reelle: 0.75
Voulez-vous continuer?
o
Entrez les coefficients ax2 + bx + c dont on cherche les 0:
1 0 9
L'equation 1x2+0x+9 a deux racines complexes: 0.00+3.00i et 0.00-3.00i
Voulez-vous continuer?
o
Entrez les coefficients ax2 + bx + c dont on cherche les 0:
4 6 17
L'equation 4x2+6x+17 a deux racines complexes: 0.00+1.92i et 0.00-1.92i
Voulez-vous continuer?
o
Entrez les coefficients ax2 + bx + c dont on cherche les 0:
12 -31 20
L'equation 12x2-31x+20 a deux racines reelles: 1.33 et 1.25
Voulez-vous continuer?
o
Entrez les coefficients ax2 + bx + c dont on cherche les 0:
1 -36 324
L'equation 1x2-36x+324 a une racine reelle: 18.00
Voulez-vous continuer?
o
Entrez les coefficients ax2 + bx + c dont on cherche les 0:
0 4 -3
L'equation 4x-3 a une racine reelle: 0.00
Voulez-vous continuer?
o
Entrez les coefficients ax2 + bx + c dont on cherche les 0:
0 23 -10
L'equation 23x-10 a une racine reelle: 0.00
Voulez-vous continuer?
o
Entrez les coefficients ax2 + bx + c dont on cherche les 0:
0 0 5
Infinite de solutions pour ces coefficients
Voulez-vous continuer?
o
Entrez les coefficients ax2 + bx + c dont on cherche les 0:
0 0 0
Aucune solution pour ces coefficients
Voulez-vous continuer?
n
*/
