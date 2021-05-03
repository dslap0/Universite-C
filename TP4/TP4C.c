/**
 * Auteur : Nicolas Levasseur
 *
 * Ce programme a ete concu pour tester 3 methodes d'integration numeriques
 * (methode du point milieu, de Simpson et de Newton-COtes a 10 points) sur un
 * ensemble de fonctions et de bornes.
 */
#include <math.h>
#include <stdio.h>

/**
 * Toutes les fonctions commencant par le suffixe "integrale_" ci-apres ont
 * pour but de donner la valeur exacte de l'integrale entre borneInf et
 * borneSup d'une certaine fonction. Ces fonctions sont donnees par le suffixe
 * dans le nom de la fonction: exp -> exponentielle, sin -> sinus, cos ->
 * cosinus, tan -> tangeante, asin -> arc sinus, acos -> arc cosinus, atan ->
 * arc tangeante, sinh -> sinus hyperbolique, cosh -> cosinus hyperbolique et
 * tanh -> tangeante hyperbolique.
 *
 * borneInf : Borne inferieure de l'integrale definie.
 * borneSup : Borne superieure de l'integrale definie.
 *
 * return : La valeur exacte de l'integrale d'une certaine fonction a
 * l'aide de sa definition mathematique.
 */

double integrale_exp(const double borneInf, const double borneSup) {
    return exp(borneSup) - exp(borneInf);
}

double integrale_sin(const double borneInf, const double borneSup) {
    return cos(borneInf) - cos(borneSup);
}

double integrale_cos(const double borneInf, const double borneSup) {
    return sin(borneSup) - sin(borneInf);
}

double integrale_tan(const double borneInf, const double borneSup) {
    return log(cos(borneInf)) - log(cos(borneSup));
}

double integrale_asin(const double borneInf, const double borneSup) {
    return borneSup * asin(borneSup) + sqrt(1 - borneSup * borneSup) -
           (borneInf * asin(borneInf) + sqrt(1 - borneInf * borneInf));
}

double integrale_acos(const double borneInf, const double borneSup) {
    return borneSup * acos(borneSup) - sqrt(1 - borneSup * borneSup) -
           (borneInf * acos(borneInf) - sqrt(1 - borneInf * borneInf));
}

double integrale_atan(const double borneInf, const double borneSup) {
    return borneSup * atan(borneSup) - 0.5 * log(1 + borneSup * borneSup) -
           (borneInf * atan(borneInf) - 0.5 * log(1 + borneInf * borneInf));
}

double integrale_sinh(const double borneInf, const double borneSup) {
    return cosh(borneSup) - cosh(borneInf);
}

double integrale_cosh(const double borneInf, const double borneSup) {
    return sinh(borneSup) - sinh(borneInf);
}

double integrale_tanh(const double borneInf, const double borneSup) {
    return log(cosh(borneSup)) - log(cosh(borneInf));
}

/**
 * On trouve la valeur de l'integrale par la methode du point milieu d'une
 * fonction entre borneInf et borneSup.
 *
 * nTermes : Nombre de termes a calculer.
 * borneInf : Borne inferieure d'integration.
 * borneSup : Borne superieure d'integration.
 * fonction : Fonction a integrer.
 *
 * return : Valeur de l'integrale approximee.
 */
double point_milieu(const int nTermes, const double borneInf,
                    const double borneSup, double (*fonction)(double)) {
    /* Pas d'integration (largeur dx) */
    const double pas = (borneSup - borneInf) / nTermes;

    /* Terme sous la forme d'une somme dans la formule du point milieu */
    double somme = 0;
    for (int i = 0; i <= nTermes - 1; i++) {
        somme += fonction(borneInf + pas * (i + 0.5));
    }
    return somme * pas;
}

/**
 * On trouve la valeur de l'integrale par la methode de Simpson d'une fonction
 * entre borneInf et borneSup. On prend des doubles pour les bornes parce que
 * sinon les resultats dependent de l'ordinateur (mon portable produit des
 * resultats differents de mon ordinateur de bureau avec des floats).
 *
 * nTermes : Nombre de termes a calculer pour la sommation, doit etre un
 * multiple de 2.
 * borneInf : Borne inferieure d'integration.
 * borneSup : Borne superieure d'integration.
 * fonction : Fonction a integrer.
 *
 * return : Valeur de l'integrale approximee
 */
double Simpson(const int nTermes, const double borneInf, const double borneSup,
               double (*fonction)(double)) {
    /* Pas d'integration (largeur dx) */
    const double pas = (borneSup - borneInf) / nTermes;

    /* Terme par lequel on va multiplier le pas / 3 pour obtenir l'integrale
     * finale */
    double integrale = fonction(borneInf) + fonction(borneSup);
    for (int i = 1; i < nTermes; i++) {
        if (i % 2)
            integrale += 4.0 * fonction(borneInf + i * pas);
        else
            integrale += 2.0 * fonction(borneInf + i * pas);
    }

    return pas / 3.0 * integrale;
}

/**
 * On trouve la valeur de l'integrale par une methode de Newton-Cotes a 10
 * points d'une fonction entre borneInf et borneSup.
 *
 * nTermes : Nombre de termes a calculer pour la sommation, doit etre un
 * multiple de 9.
 * borneInf : Borne inferieure d'integration
 * borneSup : Borne superieure d'integration
 * fonction : Fonction a integrer
 *
 * return : Valeur de l'integrale approximee
 */
double Newton_Cotes10(const int nTermes, const double borneInf,
                      const double borneSup, double (*fonction)(double)) {
    /* Pas d'integration (largeur dx) */
    const double pas = (borneSup - borneInf) / nTermes;

    double integrale = 2857 * (fonction(borneInf) + fonction(borneSup));
    for (int i = 1; i < nTermes; i++) {
        if (i % 9 == 1 || i % 9 == 8)
            integrale += 15741 * fonction(borneInf + pas * i);
        else if (i % 9 == 2 || i % 9 == 7)
            integrale += 1080 * fonction(borneInf + pas * i);
        else if (i % 9 == 3 || i % 9 == 6)
            integrale += 19344 * fonction(borneInf + pas * i);
        else if (i % 9 == 4 || i % 9 == 5)
            integrale += 5778 * fonction(borneInf + pas * i);
        else
            integrale += 5714 * fonction(borneInf + pas * i);
    }

    return 9 * pas / 89600 * integrale;
}

/**
 * Cette fonction montre le resultat d'une integrale numerique approximee selon
 * une certaine methode.
 *
 * nTermes: Nombre de termes a calculer pour l'approximation.
 * borneInf : Borne inferieure d'integration.
 * borneSup : Borne superieure d'integration.
 * methode : Fonction pour approximer l'integrale.
 * fonction : Fonction a integrer.
 * integraleExacte : Valeur de l'integrale exacte.
 * nom : Nom de la methode utilisee pour integrer.
 */
void approximer_integrale(const int nTermes, const double borneInf,
                          const double borneSup,
                          double (*methode)(int, double, double,
                                            double (*)(double)),
                          double (*fonction)(double),
                          const double integraleExacte, const char nom[]) {
    /* Integrale approximee et son erreur */
    double integraleApprox, erreur;

    integraleApprox = methode(nTermes, borneInf, borneSup, fonction);
    erreur = fabs(integraleApprox - integraleExacte) / integraleExacte * 100;
    printf("%-12s %8d %19.14f  %10.6lf%%\n", nom, nTermes, integraleApprox,
           erreur);
}

/**
 * Cette fonction montre le resultat d'une integration numerique a
 * l'utilisateur et divers parametres importants de cette integration.
 *
 * borneInf : Borne inferieure d'integration.
 * borneSup : Borne superieure d'integration.
 * integrale_exacte : Fonction pour calculer l'integrale exacte.
 * fonction : Fonction a integrer.
 * nom : Nom de la methode utilisee pour integrer.
 */
void integration(const double borneInf, const double borneSup,
                 double (*integrale_exacte)(double, double),
                 double (*fonction)(double), const char nom[]) {
    /* Valeur exacte de l'integrale */
    double integraleExacte = integrale_exacte(borneInf, borneSup);
    printf("Valeur exacte pour %s: %19.14lf\n", nom, integraleExacte);

    printf("Methode   Intervalles   Valeur approximee       Erreur\n\n");

    for (int i = 10; i <= 30; i += 10) {
        approximer_integrale(i, borneInf, borneSup, point_milieu, fonction,
                             integraleExacte, "Point milieu");
        approximer_integrale(i, borneInf, borneSup, Simpson, fonction,
                             integraleExacte, "Simpson");
    }
    approximer_integrale(9, borneInf, borneSup, Newton_Cotes10, fonction,
                         integraleExacte, "Secrete");
    printf("\n");
}

int main() {
    /* Numero de fonction */
    int nf;

    /* Bornes d'integrations */
    double binf, bsup;

    /* Reponse de l'utilisateur */
    char rep;

    /* On repete tant que l'utilisateur le desire */
    do {
        /* On recupere les bornes d'integrations */
        printf("Entrez le numero de fonction et les bornes: ");
        scanf("%d%lf%lf", &nf, &binf, &bsup);

        switch (nf) {
        case 1:
            integration(binf, bsup, integrale_exp, exp, "exp");
            break;
        case 2:
            integration(binf, bsup, integrale_sin, sin, "sin");
            break;
        case 3:
            integration(binf, bsup, integrale_cos, cos, "cos");
            break;
        case 4:
            integration(binf, bsup, integrale_tan, tan, "tan");
            break;
        case 5:
            integration(binf, bsup, integrale_asin, asin, "asin");
            break;
        case 6:
            integration(binf, bsup, integrale_acos, acos, "acos");
            break;
        case 7:
            integration(binf, bsup, integrale_atan, atan, "atan");
            break;
        case 8:
            integration(binf, bsup, integrale_sinh, sinh, "sinh");
            break;
        case 9:
            integration(binf, bsup, integrale_cosh, cosh, "cosh");
            break;
        case 10:
            integration(binf, bsup, integrale_tanh, tanh, "tanh");
            break;
        }
        printf(
            "Voulez-vous continuer? Taper 'o' si oui, n'importe quelle autre "
            "touche pour quitter.\n");
        scanf(" %c", &rep);
        printf("\n");
    } while (rep == 'o');

    return 0;
}

/*
Entrez le numero de fonction et les bornes: 1 0 1
Valeur exacte pour exp:    1.71828182845905
Methode   Intervalles   Valeur approximee       Erreur

Point milieu       10    1.71756608646113    0.041655%
Simpson            10    1.71828278192482    0.000055%
Point milieu       20    1.71810285381891    0.010416%
Simpson            20    1.71828188810386    0.000003%
Point milieu       30    1.71820228095233    0.004629%
Simpson            30    1.71828184024268    0.000001%
Secrete             9    1.71828182845967    0.000000%

Voulez-vous continuer? Taper 'o' si oui, n'importe quelle autre touche pour
quitter.
o

Entrez le numero de fonction et les bornes: 2 0 3
Valeur exacte pour sin:    1.98999249660045
Methode   Intervalles   Valeur approximee       Erreur

Point milieu       10    1.99747460403255    0.375987%
Simpson            10    1.99008301487454    0.004549%
Point milieu       20    1.99185933960437    0.093812%
Simpson            20    1.98999810848141    0.000282%
Point milieu       30    1.99082190204383    0.041679%
Simpson            30    1.98999360346935    0.000056%
Secrete             9    1.98999243312620    0.000003%

Voulez-vous continuer? Taper 'o' si oui, n'importe quelle autre touche pour
quitter.
o

Entrez le numero de fonction et les bornes: 3 0 3
Valeur exacte pour cos:    0.14112000805987
Methode   Intervalles   Valeur approximee       Erreur

Point milieu       10    0.14165060054347    0.375987%
Simpson            10    0.14112642714918    0.004549%
Point milieu       20    0.14125239494083    0.093812%
Simpson            20    0.14112040602553    0.000282%
Point milieu       30    0.14117882521775    0.041679%
Simpson            30    0.14112008655330    0.000056%
Secrete             9    0.14112000355860    0.000003%

Voulez-vous continuer? Taper 'o' si oui, n'importe quelle autre touche pour
quitter.
o

Entrez le numero de fonction et les bornes: 4 0 0.5
Valeur exacte pour tan:    0.13058424044372
Methode   Intervalles   Valeur approximee       Erreur

Point milieu       10    0.13055317443740    0.023790%
Simpson            10    0.13058434123558    0.000077%
Point milieu       20    0.13057646978840    0.005951%
Simpson            20    0.13058424677436    0.000005%
Point milieu       30    0.13058078647682    0.002645%
Simpson            30    0.13058424169537    0.000001%
Secrete             9    0.13058424047760    0.000000%

Voulez-vous continuer? Taper 'o' si oui, n'importe quelle autre touche pour
quitter.
o

Entrez le numero de fonction et les bornes: 5 0 0.5
Valeur exacte pour asin:    0.12782479158359
Methode   Intervalles   Valeur approximee       Erreur

Point milieu       10    0.12780869268948    0.012595%
Simpson            10    0.12782486282229    0.000056%
Point milieu       20    0.12782076391003    0.003151%
Simpson            20    0.12782479608051    0.000004%
Point milieu       30    0.12782300126300    0.001401%
Simpson            30    0.12782479247354    0.000001%
Secrete             9    0.12782479175483    0.000000%

Voulez-vous continuer? Taper 'o' si oui, n'importe quelle autre touche pour
quitter.
o

Entrez le numero de fonction et les bornes: 6 0 0.5
Valeur exacte pour acos:    0.65757337181386
Methode   Intervalles   Valeur approximee       Erreur

Point milieu       10    0.65758947070797    0.002448%
Simpson            10    0.65757330057516    0.000011%
Point milieu       20    0.65757739948742    0.000613%
Simpson            20    0.65757336731694    0.000001%
Point milieu       30    0.65757516213445    0.000272%
Simpson            30    0.65757337092391    0.000000%
Secrete             9    0.65757337164262    0.000000%

Voulez-vous continuer? Taper 'o' si oui, n'importe quelle autre touche pour
quitter.
o

Entrez le numero de fonction et les bornes: 7 0 1
Valeur exacte pour atan:    0.43882457311748
Methode   Intervalles   Valeur approximee       Erreur

Point milieu       10    0.43903321114083    0.047545%
Simpson            10    0.43882598036308    0.000321%
Point milieu       20    0.43887667545306    0.011873%
Simpson            20    0.43882466020391    0.000020%
Point milieu       30    0.43884772501767    0.005276%
Simpson            30    0.43882459028882    0.000004%
Secrete             9    0.43882460336896    0.000007%

Voulez-vous continuer? Taper 'o' si oui, n'importe quelle autre touche pour
quitter.
o

Entrez le numero de fonction et les bornes: 8 0 3
Valeur exacte pour sinh:    9.06766199577777
Methode   Intervalles   Valeur approximee       Erreur

Point milieu       10    9.03374731181394    0.374018%
Simpson            10    9.06806570959703    0.004452%
Point milieu       20    9.05916663808717    0.093689%
Simpson            20    9.06768743042707    0.000280%
Point milieu       30    9.06388490496193    0.041655%
Simpson            30    9.06766702737693    0.000055%
Secrete             9    9.06766214543104    0.000002%

Voulez-vous continuer? Taper 'o' si oui, n'importe quelle autre touche pour
quitter.
o

Entrez le numero de fonction et les bornes: 9 0 3
Valeur exacte pour cosh:   10.01787492740990
Methode   Intervalles   Valeur approximee       Erreur

Point milieu       10    9.98040627647094    0.374018%
Simpson            10   10.01832094696265    0.004452%
Point milieu       20   10.00848932935302    0.093689%
Simpson            20   10.01790302739154    0.000280%
Point milieu       30   10.01370202998605    0.041655%
Simpson            30   10.01788048627734    0.000055%
Secrete             9   10.01787509274555    0.000002%

Voulez-vous continuer? Taper 'o' si oui, n'importe quelle autre touche pour
quitter.
o

Entrez le numero de fonction et les bornes: 10 0 2
Valeur exacte pour tanh:    1.32500274735786
Methode   Intervalles   Valeur approximee       Erreur

Point milieu       10    1.32655607502048    0.117232%
Simpson            10    1.32502347899121    0.001565%
Point milieu       20    1.32539025043729    0.029245%
Simpson            20    1.32500400922744    0.000095%
Point milieu       30    1.32517490317650    0.012993%
Simpson            30    1.32500299546578    0.000019%
Secrete             9    1.32500544984948    0.000204%

Voulez-vous continuer? Taper 'o' si oui, n'importe quelle autre touche pour
quitter.
n
*/