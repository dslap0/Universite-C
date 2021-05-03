/**
 * Auteur: Nicolas Levasseur
 *
 * Ce programme permet de calculer et d'afficher la probabilite que deux
 * personnes aillent le meme anniversaire dans un groupe d'une grosseur donne.
 * On affiche ces probabilites pour une serie de groupe dont les grosseurs sont
 * separees par un certain pas jusqu'a ce qu'on arrive au groupe de grosseur
 * maximale.
 */

#include <stdio.h>

#define N_PERSONNES_MAX 40  // Nombre de personnes maximal
#define PAS 4               // Pas de l'affichage des probabilites

int main() {
    // On definit nos variables qui vont stocker la probabilite (en pourcentage)
    // que, dans un groupe d'un nombre de personnes donne, deux d'entre eux
    // partagent la meme fete et le produit de tout les termes sur 365 utilises
    // pour calculer la probabilite recherchee
    double probabiliteFete, produitDesTermesSur365 = 1;

    // On fait une boucle a chaque fois qu'on ajoute une personne au groupe
    for (int nPersonnes = 1; nPersonnes <= N_PERSONNES_MAX; nPersonnes++) {
        produitDesTermesSur365 *= (365.0 - nPersonnes) / 365.0;

        // On verifie si on veut connaitre la probabilite au nombre de personne
        // ou on est rendu
        if (!(nPersonnes % PAS)) {
            // On calcule la probabilite en pourcentage et on l'affiche a
            // l'utilisateur
            probabiliteFete = (1 - produitDesTermesSur365) * 100;
            printf(
                "Probabilite de 2 anniversaires identiques dans un groupe "
                "de %d personnes: %5.2lf\%\n",
                nPersonnes, probabiliteFete);
        }  // end if
    }      // end for

    return 0;
}

/*
Probabilite de 2 anniversaires identiques dans un groupe de 4 personnes:  2.71
Probabilite de 2 anniversaires identiques dans un groupe de 8 personnes:  9.46
Probabilite de 2 anniversaires identiques dans un groupe de 12 personnes: 19.44
Probabilite de 2 anniversaires identiques dans un groupe de 16 personnes: 31.50
Probabilite de 2 anniversaires identiques dans un groupe de 20 personnes: 44.37
Probabilite de 2 anniversaires identiques dans un groupe de 24 personnes: 56.87
Probabilite de 2 anniversaires identiques dans un groupe de 28 personnes: 68.10
Probabilite de 2 anniversaires identiques dans un groupe de 32 personnes: 77.50
Probabilite de 2 anniversaires identiques dans un groupe de 36 personnes: 84.87
Probabilite de 2 anniversaires identiques dans un groupe de 40 personnes: 90.32
*/
