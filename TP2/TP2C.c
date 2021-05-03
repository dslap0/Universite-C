/**
 * Auteur : Nicolas Levasseur
 *
 * Ce programme calcule la suite de collatz d'un premier terme donne par
 * l'utilsateur et affiche certains parametres tels que le terme maximum de la
 * suite ou le nombre de terme avant sa convergence. Le programme calcule des
 * suites de Collatz jusqu'a un arret de l'utilisateur.
 */

#include <stdio.h>

/**
 * Cette fonction trouve la suite de collatz selon un premier terme donne et
 * tiens compte du maximum et du nombre de termes avant la convergence de
 * celle-ci.
 *
 * premierTerme: premier terme de la suite de Collatz recherchee
 */
void suite_de_Collatz(int premierTerme) {
    // On declare ici le terme courant, le terme maximum et le nombre de
    // termes de la suite jusqu'a present
    int terme = premierTerme, nTermes = 0, max = premierTerme;

    // On affiche un message de base pour l'utilisateur
    printf("Les termes de la suite avec a = %d sont: ", premierTerme);

    // On fait une boucle jusqu'a la convergence (on sait qu'elle se produit
    // toujours a 1)
    while (terme != 1) {
        // On ecrit le dernier terme de la suite
        printf("%d, ", terme);

        // On ajuste les valeurs du terme, du max et du nombre de terme avant
        // la convergence
        terme = terme % 2 ? 3 * terme + 1 : terme / 2;
        max = terme > max ? terme : max;
        nTermes++;
    }

    // On finit ici d'indiquer certaines informations a l'utlisateur (dernier
    // terme + nombre de terme + terme maximum)
    printf("1\n");
    printf("Nombre total pour la convergence: %d\n", nTermes);
    printf("Terme maximum de la suite: %d\n", max);
}

int main() {
    // On declare nos variables contenant les reponses de l'utilisateur
    int a;
    char rep;

    // On effectue des iterations tant que l'utilisateur le demande
    do {
        // On demande a l'utilisateur d'entrer le premier terme de la suite de
        // Collatz
        printf("Entrez le premier terme de la suite de Collatz:\n");
        scanf("%d", &a);

        // On calcule la suite de Collatz et on montre divers analyses de
        // celle-ci
        suite_de_Collatz(a);

        // On verifie si on execute encore une iteration
        printf("Voulez-vous continuer?\n");
        scanf(" %c", &rep);
    } while (rep == 'o');

    return 0;
}

/*
Entrez le premier terme de la suite de Collatz:
10
Les termes de la suite avec a = 10 sont: 10, 5, 16, 8, 4, 2, 1
Nombre total pour la convergence: 6
Terme maximum de la suite: 16
Voulez-vous continuer?
o
Entrez le premier terme de la suite de Collatz:
11
Les termes de la suite avec a = 11 sont: 11, 34, 17, 52, 26, 13, 40, 20, 10, 5,
16, 8, 4, 2, 1
Nombre total pour la convergence: 14
Terme maximum de la suite: 52
Voulez-vous continuer?
o
Entrez le premier terme de la suite de Collatz:
12
Les termes de la suite avec a = 12 sont: 12, 6, 3, 10, 5, 16, 8, 4, 2, 1
Nombre total pour la convergence: 9
Terme maximum de la suite: 16
Voulez-vous continuer?
o
Entrez le premier terme de la suite de Collatz:
13
Les termes de la suite avec a = 13 sont: 13, 40, 20, 10, 5, 16, 8, 4, 2, 1
Nombre total pour la convergence: 9
Terme maximum de la suite: 40
Voulez-vous continuer?
o
Entrez le premier terme de la suite de Collatz:
14
Les termes de la suite avec a = 14 sont: 14, 7, 22, 11, 34, 17, 52, 26, 13, 40,
20, 10, 5, 16, 8, 4, 2, 1
Nombre total pour la convergence: 17
Terme maximum de la suite: 52
Voulez-vous continuer?
o
Entrez le premier terme de la suite de Collatz:
25
Les termes de la suite avec a = 25 sont: 25, 76, 38, 19, 58, 29, 88, 44, 22,
11, 34, 17, 52, 26, 13, 40, 20, 10, 5, 16, 8, 4, 2, 1
Nombre total pour la convergence: 23
Terme maximum de la suite: 88
Voulez-vous continuer?
o
Entrez le premier terme de la suite de Collatz:
26
Les termes de la suite avec a = 26 sont: 26, 13, 40, 20, 10, 5, 16, 8, 4, 2, 1
Nombre total pour la convergence: 10
Terme maximum de la suite: 40
Voulez-vous continuer?
o
Entrez le premier terme de la suite de Collatz:
37
Les termes de la suite avec a = 37 sont: 37, 112, 56, 28, 14, 7, 22, 11, 34,
17, 52, 26, 13, 40, 20, 10, 5, 16, 8, 4, 2, 1
Nombre total pour la convergence: 21
Terme maximum de la suite: 112
Voulez-vous continuer?
o
Entrez le premier terme de la suite de Collatz:
38
Les termes de la suite avec a = 38 sont: 38, 19, 58, 29, 88, 44, 22, 11, 34,
17, 52, 26, 13, 40, 20, 10, 5, 16, 8, 4, 2, 1
Nombre total pour la convergence: 21
Terme maximum de la suite: 88
Voulez-vous continuer?
o
Entrez le premier terme de la suite de Collatz:
49
Les termes de la suite avec a = 49 sont: 49, 148, 74, 37, 112, 56, 28, 14, 7,
22, 11, 34, 17, 52, 26, 13, 40, 20, 10, 5, 16, 8, 4, 2, 1
Nombre total pour la
convergence: 24
Terme maximum de la suite: 148
Voulez-vous continuer?
n
*/
