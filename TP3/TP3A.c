/**
 * Auteur : Nicolas Levasseur
 *
 * Ce programme trouve la vitesse de convergence de 3 formules pour calculer pi
 * (fractions infinies, somme infinie et multiplication infinie) et montre les
 * resultats de chaque iteration a l'utilisateur. L'utilisateur peut ensuite
 * comprendre visuellement la vitesse de convergence de chaque formule. Le
 * programme a ete elabore afin de favoriser la modularite du code, par exemple
 * il est tres facile d'ajouter une nouvelle fonction convergent vers une
 * constante connue (qui peut etre pi ou une autre).
 */
#include <math.h>
#include <stdio.h>

/* Constante mathematique pi */
#define PI 3.14159265358979
/* Precision sur les formules de Brouncker et de Leibniz */
#define EPSILON1 1e-7
/* Precision sur la formule de Vieta */
#define EPSILON2 1e-14

/**
 * Cette fonction trouve une approximation de pi obtenue par les fractions
 * infinies de Brouncker.
 *
 * iTerme : Numero du terme recherche pour calculer pi
 *
 * return : Retourne le terme de la fraction de Brouncker
 */
double Brouncker(unsigned int iTerme) {
    /* Terme a calculer, initialise a 2 puisque le terme divise le prochain et
     * tout les termes sont divises par 2 au depart */
    double terme = 0;

    /* On trouve la fraction partielle */
    for (; iTerme; iTerme--)
        /* On a besoin que le terme mis au carre soit un double avant sa mise au
         * carre, d'ou le 2.0 au premier terme */
        terme = (2.0 * iTerme - 1) * (2 * iTerme - 1) / (2.0 + terme);

    return 4 / (1 + terme);
}

/**
 * Cette fonction trouve une approximation de pi obtenue par la sommation
 * infinie de Leibniz.
 *
 * nTermes : Nombre de termes a sommer pour calculer pi
 *
 * return : Retourne l'approximation de pi recherche
 */
double Leibniz(unsigned int nTermes) {
    /* Somme a calculer, initialise au terme k = 0 de la serie de Leibniz */
    double somme = 1;

    /* On trouve la somme partielle */
    for (int i = 1; i < nTermes; i++) {
        int signe = i % 2 ? -1 : 1;
        somme += signe / (i * 2.0 + 1);
    }

    return 4 * somme;
}

/**
 * Cette fonction trouve une approximation de pi obtenue par les produits
 * infinis de Vieta.
 *
 * nTermes : Nombre de termes a multiplier pour calculer pi
 *
 * return : Retourne l'approximation de pi recherche
 */
double Vieta(unsigned int nTermes) {
    /* Produit a calculer, initialise au terme k = 0 du produit de Veita */
    double produit = 2;

    /* On trouve le produit partiel */
    for (int i = 1; i < nTermes; i++) {
        /* Diviseur du terme courant dans le produit de Vieta */
        double diviseur = sqrt(2);

        /* On trouve le diviseur */
        for (int j = 1; j < i; j++) diviseur = sqrt(2 + diviseur);

        produit *= 2 / diviseur;
    }

    return produit;
}

/**
 * Cette fonction trouve la convergence vers une constante d'une formule a une
 * certaine erreur pres.
 *
 * nom : Message a afficher, nom de l'inventeur de la formule utilisee.
 * valeurConv : Valeur de convergence de la formule
 * errDemandee : Erreur apres laquelle on considere que la fonction a converge
 * longueurInt : Nombre de caracteres attribues au nombre de termes lors du
 * printf
 * precisionDouble : Nombre de chiffre apres la virgule qu'on veut
 * afficher pour la valeur de pi approximee et son erreur
 * formule : Fonction qui converge vers la constante
 */
void Converge(const char nom[], double valeurConv, double errDemandee,
              int longueurInt, int precisionDouble, double (*formule)(unsigned int)) {
    /* Variable representant le nombre de termes qu'on va ajouter a la suite a
     * la prochaine iteration */
    int increment = 1;
    /* Nombre de termes a calculer */
    unsigned int nTermes = 1;

    /* Erreur de l'iteration precedente, initialisee a l'erreur maximale */
    double errPrec = PI;

    printf("\nConvergence du calcul de PI avec la formule %s\n", nom);

    /* On calcule les termes de la fonction et on les affiche */
    while (errPrec > EPSILON1) {
        /* Terme recherche */
        double terme = (*formule)(nTermes);

        /* Erreur de l'iteration courante */
        double errCour = valeurConv - terme;
        errCour = errCour >= 0 ? errCour : -errCour;

        /* Modification ici, je me suis permis de ne pas mettre de s a terme
         * lorsque le nombre de terme n'est pas plus grand que 0 */
        printf("Valeur avec %*d terme%c = %.*lf, erreur = %.*lf\n", longueurInt,
               nTermes, nTermes > 1 ? 's' : ' ', precisionDouble, terme,
               precisionDouble, errCour);

        /* On teste si on augmente l'incrementation de iTerme */
        increment *= (int)log10(errPrec) == (int)log10(errCour) ? 2 : 1;

        /* Assignations pour l'iteration suivante */
        errPrec = errCour;
        nTermes = nTermes + increment;
    }
}

int main() {
    /* Je sais que le main n'est pas exactement pareil a ce qui est demande,
     * mais ma version est plus modulable donc je la garde */
    Converge("de Brouncker", PI, EPSILON1, 9, 7, Brouncker);
    Converge("de Leibniz", PI, EPSILON1, 9, 7, Leibniz);
    Converge("de Vieta", PI, EPSILON2, 2, 14, Vieta);
    return 0;
}

/*
Convergence du calcul de PI avec la formule de Brouncker
Valeur avec         1 terme  = 2.6666667, erreur = 0.4749260
Valeur avec         3 termes = 2.8952381, erreur = 0.2463546
Valeur avec         7 termes = 3.0170718, erreur = 0.1245208
Valeur avec        15 termes = 3.0791534, erreur = 0.0624393
Valeur avec        23 termes = 3.0999440, erreur = 0.0416486
Valeur avec        39 termes = 3.1165966, erreur = 0.0249961
Valeur avec        71 termes = 3.1277044, erreur = 0.0138882
Valeur avec       135 termes = 3.1342398, erreur = 0.0073528
Valeur avec       199 termes = 3.1365927, erreur = 0.0050000
Valeur avec       327 termes = 3.1385439, erreur = 0.0030488
Valeur avec       583 termes = 3.1398803, erreur = 0.0017123
Valeur avec      1095 termes = 3.1406802, erreur = 0.0009124
Valeur avec      1607 termes = 3.1409708, erreur = 0.0006219
Valeur avec      2631 termes = 3.1412127, erreur = 0.0003799
Valeur avec      4679 termes = 3.1413790, erreur = 0.0002137
Valeur avec      8775 termes = 3.1414787, erreur = 0.0001139
Valeur avec     16967 termes = 3.1415337, erreur = 0.0000589
Valeur avec     25159 termes = 3.1415529, erreur = 0.0000397
Valeur avec     41543 termes = 3.1415686, erreur = 0.0000241
Valeur avec     74311 termes = 3.1415792, erreur = 0.0000135
Valeur avec    139847 termes = 3.1415855, erreur = 0.0000072
Valeur avec    205383 termes = 3.1415878, erreur = 0.0000049
Valeur avec    336455 termes = 3.1415897, erreur = 0.0000030
Valeur avec    598599 termes = 3.1415910, erreur = 0.0000017
Valeur avec   1122887 termes = 3.1415918, erreur = 0.0000009
Valeur avec   1647175 termes = 3.1415920, erreur = 0.0000006
Valeur avec   2695751 termes = 3.1415923, erreur = 0.0000004
Valeur avec   4792903 termes = 3.1415924, erreur = 0.0000002
Valeur avec   8987207 termes = 3.1415925, erreur = 0.0000001
Valeur avec  17375815 termes = 3.1415926, erreur = 0.0000001

Convergence du calcul de PI avec la formule de Leibniz
Valeur avec         1 terme  = 4.0000000, erreur = 0.8584073
Valeur avec         3 termes = 3.4666667, erreur = 0.3250740
Valeur avec         7 termes = 3.2837385, erreur = 0.1421458
Valeur avec        15 termes = 3.2081857, erreur = 0.0665930
Valeur avec        23 termes = 3.1850504, erreur = 0.0434578
Valeur avec        39 termes = 3.1672295, erreur = 0.0256368
Valeur avec        71 termes = 3.1556765, erreur = 0.0140838
Valeur avec       135 termes = 3.1490000, erreur = 0.0074073
Valeur avec       199 termes = 3.1466177, erreur = 0.0050251
Valeur avec       327 termes = 3.1446508, erreur = 0.0030581
Valeur avec       583 termes = 3.1433079, erreur = 0.0017153
Valeur avec      1095 termes = 3.1425059, erreur = 0.0009132
Valeur avec      1607 termes = 3.1422149, erreur = 0.0006223
Valeur avec      2631 termes = 3.1419727, erreur = 0.0003801
Valeur avec      4679 termes = 3.1418064, erreur = 0.0002137
Valeur avec      8775 termes = 3.1417066, erreur = 0.0001140
Valeur avec     16967 termes = 3.1416516, erreur = 0.0000589
Valeur avec     25159 termes = 3.1416324, erreur = 0.0000397
Valeur avec     41543 termes = 3.1416167, erreur = 0.0000241
Valeur avec     74311 termes = 3.1416061, erreur = 0.0000135
Valeur avec    139847 termes = 3.1415998, erreur = 0.0000072
Valeur avec    205383 termes = 3.1415975, erreur = 0.0000049
Valeur avec    336455 termes = 3.1415956, erreur = 0.0000030
Valeur avec    598599 termes = 3.1415943, erreur = 0.0000017
Valeur avec   1122887 termes = 3.1415935, erreur = 0.0000009
Valeur avec   1647175 termes = 3.1415933, erreur = 0.0000006
Valeur avec   2695751 termes = 3.1415930, erreur = 0.0000004
Valeur avec   4792903 termes = 3.1415929, erreur = 0.0000002
Valeur avec   8987207 termes = 3.1415928, erreur = 0.0000001
Valeur avec  17375815 termes = 3.1415927, erreur = 0.0000001

Convergence du calcul de PI avec la formule de Vieta
Valeur avec  1 terme  = 2.00000000000000, erreur = 1.14159265358979
Valeur avec  3 termes = 3.06146745892072, erreur = 0.08012519466907
Valeur avec  5 termes = 3.13654849054594, erreur = 0.00504416304385
Valeur avec  7 termes = 3.14127725093277, erreur = 0.00031540265702
Valeur avec  9 termes = 3.14157294036709, erreur = 0.00001971322270
Valeur avec 11 termes = 3.14159142151120, erreur = 0.00000123207859
Valeur avec 13 termes = 3.14159257658487, erreur = 0.00000007700492
*/
