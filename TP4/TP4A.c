/**
 * Auteur: Nicolas Levasseur
 *
 * Ce programme sert calculer la suite des nombres de Motzkin selon une methode
 * recursive et une methode iterative. On comapre ensuite diverses donnes pour
 * chaque methode d'execution afin de les comparer.
 */

#include <stdio.h>
#include <time.h>

/* Afin de fonctionner correctement sur Linux ou Unix */
#ifndef CLK_TCK
#define CLK_TCK CLOCKS_PER_SEC
#endif

#define NTERMEMAX 28 /* Nombre maximum de termes calcules par la suite */

/**
 * Fonction qui cherche a calculer la suite de Motzkin de maniere recursive, 
 * grace a la formule M_n = M_(n-1) + Somme(M_i * M_(n-2-i)), avec i allant de 
 * 0 a n-2.
 *
 * nTerme: Numero du terme a calculer.
 * 
 * return: Nombre de Motzkin d'indice nTerme.
 */
double Motzkin_recursif1(const int nTerme) {
    /* Definitions des deux premiers termes */
    if (!nTerme || nTerme == 1)
        return 1;

    /* Terme sous la forme d'une sommation dans la definition de la suite */
    double somme = 0;
    /* Limite de la sommation */
    const int limiteSomme = nTerme - 2;
    for (int i = 0; i <= limiteSomme; i++)
        somme += Motzkin_recursif1(i) * Motzkin_recursif1(limiteSomme - i);

    return Motzkin_recursif1(nTerme - 1) + somme;
}

/**
 * Fonction qui cherche a calculer la suite de Motzkin de maniere iterative, 
 * grace a la formule M_n = (2n + 1) / (n + 2) * M_(n-1) + (3n - 3) / (n + 2) 
 * * M_(n-2).
 *
 * nTerme: Numero du terme a calculer.
 * 
 * return: Nombre de Motzkin d'indice nTerme.
 */
double Motzkin_iteratif1(const int nTerme) {
    /* Definitions des deux premiers termes */
    if (!nTerme || nTerme == 1)
        return 1;

    /* Le dernier terme calcule et l'avant-dernier terme calcule par la suite,
     * dans cet ordre */
    double dernier = 1, avantDernier = 1;

    /* On calcule les termes de la suite iterativement, jusqu'a ce qu'on arrive
     * au terme voulu */
    for (int i = 2; i <= nTerme; i++){
        double courant = (2 * i + 1) / (i + 2.0) * dernier +
                  (3 * i - 3) / (i + 2.0) * avantDernier;
        avantDernier = dernier;
        dernier = courant;
    }

    return dernier;
}

/**
 * Fonction qui sert a afficher les temps d'executions et les resultats d'une 
 * fonction qui calcule la suite de Motzkin.
 * 
 * nom: Nom de la nom utilisee pour calculer la suite de Motzkin.
 * Motzkin1: Fonction qui calcule les termes de la suite de Motzkin.
 */
void afficher_temps(const char nom[], double (*Motzkin1)(const int)){
    printf("Suite de Motzkin calculee %s...", nom);

    /* Temps au debut */
    const clock_t tempsDeb = clock();

    /* On affiche les resultats de la fonction ici */
    for(int i = 0; i < NTERMEMAX; i++){
        /* Test pour formatter */ 
        if (!(i % 4))
            printf("\n");

        printf("M%-2d = %-11.0lf ", i, Motzkin1(i));
    }
    /* Temps a la fin. */
    const clock_t tempsFin = clock();
    printf("\nTemps de calcul: %6.2f secondes\n\n",
           ((float)tempsFin - tempsDeb) / CLK_TCK);
}

/**
 * Fonction qui cherche a calculer la suite de Motzkin de maniere recursive,
 * grace a la formule M_n = M_(n-1) + Somme(M_i * M_(n-2-i)), avec i allant de
 * 0 a n-2. Elle tient aussi compte du nombre d'operation de chaque type
 * effectuees durant son executition.
 *
 * nTerme: Numero du terme a calculer.
 * nAffectations: Nombre d'affectations effectuées par la fonction de base.
 * nAdditions: Nombre d'additions effectuées par la fonction de base.
 * nMultiplications: Nombre de multîplications effectuées par la fonction de
 * base. 
 * nComparaisons: Nombre de comparaisons effectuées par la fonction de
 * base.
 * 
 * return: Nombre de Motzkin d'indice nTerme.
 */
double Motzkin_recursif2(const int nTerme, double* nAffectations, double* nAdditions,
                        double* nMultiplications, double* nComparaisons) {
    /* 1 affectation pour la copie de nTerme */
    ++*nAffectations;
    /* 2 comparaisons pour ! et == (je n'ai pas compte || comme une
     * comparaison) */
    *nComparaisons += 2;
    if (!nTerme || nTerme == 1) {
        /* Si nTerme est 0 alors on n'a pas effectue la comparaison pour le ==
         * puisqu'on a un vrai du cote gauche du || */
        if (!nTerme)
            --*nComparaisons;
        /* 1 affectation pour return */
        ++*nAffectations;
        return 1;
    }

    /* 3 affectations pour somme =, pour limiteSomme = et pour i = (dans le
     * for) */
    *nAffectations += 3;
    /* 1 comparaison pour <= dans le for */
    ++*nComparaisons;
    /* 1 addition pour le - dans limiteSomme */
    ++*nAdditions;
    /* Terme sous la forme d'une sommation dans la definition de la suite */
    double somme = 0;
    /* Limite de la sommation */
    const int limiteSomme = nTerme - 2;
    for (int i = 0; i <= limiteSomme; i++) {
        /* 3 additions pour i++, somme += et le - dans les arguments de
         * Motzkin_recursif2 */
        *nAdditions += 3;
        /* 2 affectation pour i++ et somme += */
        *nAffectations += 2;
        /* 1 multiplication pour * entre les termes de la somme */
        ++*nMultiplications;
        somme += Motzkin_recursif2(i, nAffectations, nAdditions,
                                   nMultiplications, nComparaisons) *
                 Motzkin_recursif2(limiteSomme - i, nAffectations, nAdditions,
                                   nMultiplications, nComparaisons);
        /* 1 comparaison pour <= dans le for */
        ++*nComparaisons;
    }

    /* 1 affection pour return */
    ++*nAffectations;
    /* 2 additions pour - et + */
    *nAdditions += 2;
    return Motzkin_recursif2(nTerme - 1, nAffectations, nAdditions,
                             nMultiplications, nComparaisons) +
           somme;
}

/**
 * Fonction qui cherche a calculer la suite de Motzkin de maniere iterative, 
 * grace a la formule M_n = (2n + 1) / (n + 2) * M_(n-1) + (3n - 3) / (n + 2) 
 * * M_(n-2). Elle tient aussi compte du nombre d'operation de chaque type 
 * effectuees durant son executition.
 *
 * nTerme: Numero du terme a calculer.
 * nAffectations: Nombre d'affectations effectuées par la fonction de base.
 * nAdditions: Nombre d'additions effectuées par la fonction de base.
 * nMultiplications: Nombre de multîplications effectuées par la fonction de
 * base. 
 * nComparaisons: Nombre de comparaisons effectuées par la fonction de
 * base.
 * 
 * return: Nombre de Motzkin d'indice nTerme.
 */
double Motzkin_iteratif2(const int nTerme, double* nAffectations, double* nAdditions,
                         double* nMultiplications, double* nComparaisons) {
    /* 1 affectation pour la copie de nTerme */
    ++*nAffectations;
    /* 2 comparaisons pour ! et == (je n'ai pas compte || comme une
     * comparaison) */
    *nComparaisons += 2;
    if (!nTerme || nTerme == 1) {
        /* Si nTerme est 0 alors on n'a pas effectue la comparaison pour le ==
         * puisqu'on a un vrai du cote gauche du || */
        if (!nTerme)
            --*nComparaisons;
        /* 1 affectation pour return */
        ++*nAffectations;
        return 1;
    }

    /* 3 affectations pour dernier =, pour avantDernier = et pour i = (dans le
     * for) */
    *nAffectations += 3;

    /* Le dernier terme calcule et l'avant-dernier terme calcule par la suite,
     * dans cet ordre */
    double dernier = 1, avantDernier = 1;

    /* 1 comparaison pour i <= (dans le for) */
    ++*nComparaisons;
    /* On calcule les termes de la suite iterativement, jusqu'a ce qu'on arrive
     * au terme voulu */
    for (int i = 2; i <= nTerme; i++){
        /* 4 affectations pour i++, courant =, pour avantDernier = et pour
         * dernier = */
        *nAffectations += 4;
        /* 6 multiplications pour les 2 * dans les numerateurs, les 2 / entre
         * les numerateurs et les denominateurs et les * entre les termes et
         * leurs coefficients */
        *nMultiplications += 6;
        /* 6 additions pour le i++, les 2 + dans les numerateurs, pour les 2 -
         * dans les denominateurs et pour le + entre les deux termes */
        *nAdditions += 6;
        double courant = (2 * i + 1) / (i + 2.0) * dernier +
                  (3 * i - 3) / (i + 2.0) * avantDernier;
        avantDernier = dernier;
        dernier = courant;
        /* 1 comparaison pour le i <= (dans le for) */
        ++*nComparaisons;
    }

    /* 1 affectation pour le return */
    ++*nAffectations;
    return dernier;
}

/**
 * Fonction qui sert a afficher le nombre d'operations de chaque type et les
 * resultats d'une fonction qui calcule la suite de Motzkin.
 *
 * nom: Nom de la nom utilisee pour calculer la suite de Motzkin.
 * Motzkin2: Fonction qui calcule les termes de la suite de Motzkin en tenant
 * compte du nombre d'operations de chaque type effectuees.
 */
void afficher_mesures(const char nom[],
                      double (*Motzkin2)(const int, double*, double*, double*, double*)) {
    printf("Suite de Motzkin calculee %s...", nom);

    /* Compteur d'affectations, compteur d'additions, compteur de
     * multiplications et compteur de comparaisons, dans cet ordre */
    double nAffectations = 0;
    double nAdditions = 0;
    double nMultiplications = 0;
    double nComparaisons = 0;

    /* On affiche les resultats de la fonction ici */
    for(int i = 0; i < NTERMEMAX; i++){
        /* Test pour formatter */ 
        if (!(i % 4))
            printf("\n");

        printf("M%-2d = %-11.0lf ", i,
               Motzkin2(i, &nAffectations, &nAdditions, &nMultiplications,
                        &nComparaisons));
    }

    printf("\n");

    /* On affiche les metriques mesurees au long des executions */
    printf("Nombre d'affectations    : %-.0lf\n", nAffectations);
    printf("Nombre d'additions       : %-.0lf\n", nAdditions);
    printf("Nombre de multiplications: %-.0lf\n", nMultiplications);
    printf("Nombre de comparaisons   : %-.0lf\n\n", nComparaisons);
}

int main() {
    afficher_temps("recursivement", Motzkin_recursif1);
    afficher_temps("iterativement", Motzkin_iteratif1);

    printf("\n");

    afficher_mesures("recursivement", Motzkin_recursif2);
    afficher_mesures("iterativement", Motzkin_iteratif2);

    return 0;
}

/*
Suite de Motzkin calculee recursivement...
M0  = 1           M1  = 1           M2  = 2           M3  = 4
M4  = 9           M5  = 21          M6  = 51          M7  = 127
M8  = 323         M9  = 835         M10 = 2188        M11 = 5798
M12 = 15511       M13 = 41835       M14 = 113634      M15 = 310572
M16 = 853467      M17 = 2356779     M18 = 6536382     M19 = 18199284    
M20 = 50852019    M21 = 142547559   M22 = 400763223   M23 = 1129760415  
M24 = 3192727797  M25 = 9043402501  M26 = 25669818476 M27 = 73007772802 
Temps de calcul: 136.29 secondes

Suite de Motzkin calculee iterativement...
M0  = 1           M1  = 1           M2  = 2           M3  = 4
M4  = 9           M5  = 21          M6  = 51          M7  = 127
M8  = 323         M9  = 835         M10 = 2188        M11 = 5798
M12 = 15511       M13 = 41835       M14 = 113634      M15 = 310572
M16 = 853467      M17 = 2356779     M18 = 6536382     M19 = 18199284
M20 = 50852019    M21 = 142547559   M22 = 400763223   M23 = 1129760415
M24 = 3192727797  M25 = 9043402501  M26 = 25669818476 M27 = 73007772802
Temps de calcul:   0.01 secondes


Suite de Motzkin calculee recursivement...
M0  = 1           M1  = 1           M2  = 2           M3  = 4
M4  = 9           M5  = 21          M6  = 51          M7  = 127
M8  = 323         M9  = 835         M10 = 2188        M11 = 5798
M12 = 15511       M13 = 41835       M14 = 113634      M15 = 310572      
M16 = 853467      M17 = 2356779     M18 = 6536382     M19 = 18199284    
M20 = 50852019    M21 = 142547559   M22 = 400763223   M23 = 1129760415  
M24 = 3192727797  M25 = 9043402501  M26 = 25669818476 M27 = 73007772802 
Nombre d'affectations    : 82403133143
Nombre d'additions       : 43904613045
Nombre de multiplications: 9228778012
Nombre de comparaisons   : 51549983118

Suite de Motzkin calculee iterativement...
M0  = 1           M1  = 1           M2  = 2           M3  = 4
M4  = 9           M5  = 21          M6  = 51          M7  = 127
M8  = 323         M9  = 835         M10 = 2188        M11 = 5798
M12 = 15511       M13 = 41835       M14 = 113634      M15 = 310572
M16 = 853467      M17 = 2356779     M18 = 6536382     M19 = 18199284
M20 = 50852019    M21 = 142547559   M22 = 400763223   M23 = 1129760415
M24 = 3192727797  M25 = 9043402501  M26 = 25669818476 M27 = 73007772802
Nombre d'affectations    : 1538
Nombre d'additions       : 2106
Nombre de multiplications: 2106
Nombre de comparaisons   : 432

*/