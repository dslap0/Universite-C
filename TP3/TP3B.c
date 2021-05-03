/**
 * Auteur : Nicolas Levasseur
 *
 * Ce programme a ete concu pour tester trois methodes d'integration numeriques
 * (methode des trapezes, de Simpson et de Simpson 3/8). On a pense a la
 * modularite du code, donc on utilise pas la fonction exponentielle directement
 * mais elle est passee en argument aux diverses methodes. On execute le code
 * tant que l'utilisateur le demande.
 */
#include <stdio.h>
#include <math.h>

/**
 * Cette fonction trouve la valeur exacte (si on ne prend pas en compte l'erreur
 * introduite sur les doubles par C) de l'integrale entre borneInf et borneSup
 * de la fonction exponentielle.
 *
 * borneInf : Borne inferieure de l'integrale definie
 * borneSup : Borne superieure de l'integrale definie
 * 
 * return : La fonction exponentielle evaluee a la borne supperieure moins la
 * fonction exponentielle a la borne inferieure
 */
double integrale_exacte(float borneInf, float borneSup){
    return exp(borneSup) - exp(borneInf);
}

/**
 * On trouve la valeur de l'integrale par la methode des trapezes de la
 * fonction exponentielle entre borneInf et borneSup.
 * 
 * nTermes : Nombre de termes a calculer pour la sommation
 * borneInf : Borne inferieure d'integration
 * borneSup : Borne superieure d'integration
 * fonction : Fonction a integrer
 * 
 * return : Valeur de l'integrale approximee
 */
double Trapeze(int nTermes, float borneInf, float borneSup,
                         double (*fonction)(double)) {
    /* Hauteur d'un trapeze (largeur dx) */
    const double hauteur = (borneSup - borneInf) / nTermes;

    /* Terme par lequel on va multiplier la hauteur des trapezes pour obtenir
     * l'integrale finale */
    double integrale = (fonction(borneInf) + fonction(borneSup)) / 2;
    for (int i = 1; i < nTermes; i++)
        integrale += fonction(borneInf + i * hauteur);
    
    return hauteur * integrale;
}

/**
 * On trouve la valeur de l'integrale par la methode de Simpson d'une fonction
 * entre borneInf et borneSup.
 * 
 * nTermes : Nombre de termes a calculer pour la sommation
 * borneInf : Borne inferieure d'integration
 * borneSup : Borne superieure d'integration
 * fonction : Fonction a integrer
 * 
 * return : Valeur de l'integrale approximee
 */
double Simpson(int nTermes, float borneInf, float borneSup,
                         double (*fonction)(double)) {
    /* Pas d'integration (largeur dx) */
    const double pas = (borneSup - borneInf) / nTermes;

    /* Terme par lequel on va multiplier le pas / 3 pour obtenir l'integrale
     * finale */
    double integrale = fonction(borneInf) + fonction(borneSup);
    for (int i = 1; i < nTermes; i++) {
        if (i % 2)
            integrale += 4 * fonction(borneInf + i * pas);
        else
            integrale += 2 * fonction(borneInf + i * pas);
    }

    return pas / 3 * integrale;
}

/**
 * On trouve la valeur de l'integrale par la methode de Simpson 3/8 d'une
 * fonction entre borneInf et borneSup.
 *
 * nTermes : Nombre de termes a calculer pour la sommation
 * borneInf : Borne inferieure d'integration
 * borneSup : Borne superieure d'integration
 * fonction : Fonction a integrer
 *
 * return : Valeur de l'integrale approximee
 */
double Simpson3Sur8(int nTermes, float borneInf, float borneSup,
                              double (*fonction)(double)) {
    /* Pas d'integration (largeur dx) */
    const double pas = (borneSup - borneInf) / nTermes;

    /* Terme par lequel on va multiplier 3 * pas / 8 pour obtenir l'integrale
     * finale */
    double integrale = fonction(borneInf) + fonction(borneSup);
    for(int i = 1; i < nTermes; i++) {
        if(i % 3)
            integrale += 3 * fonction(borneInf + i * pas);
        else
            integrale += 2 * fonction(borneInf + i * pas);
    }

    return 3 * pas / 8 * integrale;
}

/**
 * Cette fonction montre le resultat d'une integration numerique a l'utilisateur
 * et divers parametres importants de cette integration.
 * 
 * nom : Nom de la methode utilisee pour integrer
 * nTermes : nombre de termes necessaires a l'integration
 * borneInf : Borne inferieure d'integration
 * borneSup : Borne superieure d'integration
 * integraleExacte : Valeur veritable de l'integrale
 * fonction : Fonction a integrer
 * methode : Methode d'integration utilisee
 */
void montre_resultats(const char nom[], int nTermes, float borneInf,
                      float borneSup, double integraleExacte,
                      double (*fonction)(double),
                      double (*methode)(int, float, float,
                                        double (*f)(double))) {
    double integraleApprox = methode(nTermes, borneInf, borneSup, fonction);
    double erreur =
        fabs(integraleApprox - integraleExacte) / integraleExacte * 100;

    printf("%-12s %8d %19.14f  %10.6lf%%\n", nom, nTermes,
            integraleApprox, erreur);
}

int main(){
    /* Bornes d'integrations */
    float borneInf, borneSup;

    /* Reponse de l'utilisateur */
    char rep;

    do {
        /* On recupere les bornes d'integrations */
        printf("Entrez les bornes: ");
        scanf("%f%f", &borneInf, &borneSup);

        /* On trouve la valeur exacte de l'integrale */
        double integraleExacte = integrale_exacte(borneInf, borneSup);
        printf("Valeur exacte: %19.14f\n", integraleExacte);

        printf("Methode   Intervalles   Valeur approximee       Erreur\n\n");

        /* Boucle sur le nombre de termes utilises pour calculer l'integrale */
        for(int nTermes = 6; nTermes <= 30; nTermes += 6){
            montre_resultats("Trapeze", nTermes, borneInf, borneSup, integraleExacte, exp,
                            Trapeze);
            montre_resultats("Simpson", nTermes, borneInf, borneSup, integraleExacte, exp,
                            Simpson);
            montre_resultats("Simpson 3/8", nTermes, borneInf, borneSup, integraleExacte, exp,
                            Simpson3Sur8);
            printf("\n");
        }

        printf(
            "Voulez-vous continuer? Taper 'o' si oui, n'importe quelle autre "
            "touche pour quitter.\n");
        scanf(" %c", &rep);
        printf("\n");
    } while(rep == 'o');

    return 0;
}
/*
Entrez les bornes: 0 1
Valeur exacte:    1.71828182845905
Methode   Intervalles   Valeur approximee       Erreur

Trapeze             6    1.72225749247148    0.231374%
Simpson             6    1.71828916992083    0.000427%
Simpson 3/8         6    1.71829829247231    0.000958%

Trapeze            12    1.71927608944639    0.057864%
Simpson            12    1.71828228843802    0.000027%
Simpson 3/8        12    1.71828286255749    0.000060%

Trapeze            18    1.71872375064165    0.025719%
Simpson            18    1.71828191936081    0.000005%
Simpson 3/8        18    1.71828203291292    0.000012%

Trapeze            24    1.71853041528076    0.014467%
Simpson            24    1.71828185722555    0.000002%
Simpson 3/8        24    1.71828189317032    0.000004%

Trapeze            30    1.71844092568213    0.009259%
Simpson            30    1.71828184024268    0.000001%
Simpson 3/8        30    1.71828185496873    0.000002%

Voulez-vous continuer? Taper 'o' si oui, n'importe quelle autre touche pour quitter.
o

Entrez les bornes: -1 0
Valeur exacte:    0.63212055882856
Methode   Intervalles   Valeur approximee       Erreur

Trapeze             6    0.63358312388374    0.231374%
Simpson             6    0.63212325960142    0.000427%
Simpson 3/8         6    0.63212661560056    0.000958%

Trapeze            12    0.63248632700496    0.057864%
Simpson            12    0.63212072804537    0.000027%
Simpson 3/8        12    0.63212093925212    0.000060%

Trapeze            18    0.63228313291414    0.025719%
Simpson            18    0.63212059226945    0.000005%
Simpson 3/8        18    0.63212063404294    0.000012%

Trapeze            24    0.63221200880961    0.014467%
Simpson            24    0.63212056941117    0.000002%
Simpson 3/8        24    0.63212058263451    0.000004%

Trapeze            30    0.63217908742608    0.009259%
Simpson            30    0.63212056316352    0.000001%
Simpson 3/8        30    0.63212056858092    0.000002%

Voulez-vous continuer? Taper 'o' si oui, n'importe quelle autre touche pour quitter.
o

Entrez les bornes: -1 1
Valeur exacte:    2.35040238728760
Methode   Intervalles   Valeur approximee       Erreur

Trapeze             6    2.37212517685413    0.924216%
Simpson             6    2.35056148681103    0.006769%
Simpson 3/8         6    2.35075574460899    0.015034%

Trapeze            12    2.35584061635522    0.231374%
Simpson            12    2.35041242952225    0.000427%
Simpson 3/8        12    2.35042490807287    0.000958%

Trapeze            18    2.35281999933237    0.102859%
Simpson            18    2.35040437457987    0.000085%
Simpson 3/8        18    2.35040685214215    0.000190%

Trapeze            24    2.35176241645134    0.057864%
Simpson            24    2.35040301648339    0.000027%
Simpson 3/8        24    2.35040380180961    0.000060%

Trapeze            30    2.35127284221421    0.037034%
Simpson            30    2.35040264508287    0.000011%
Simpson 3/8        30    2.35040296702037    0.000025%

Voulez-vous continuer? Taper 'o' si oui, n'importe quelle autre touche pour quitter.
o

Entrez les bornes: -1.5 1.5
Valeur exacte:    4.25855891018963
Methode   Intervalles   Valeur approximee       Erreur

Trapeze             6    4.34691140764325    2.074704%
Simpson             6    4.25999469497233    0.033715%
Simpson 3/8         6    4.26169853074054    0.073725%

Trapeze            12    4.28071583468034    0.520292%
Simpson            12    4.25865064369270    0.002154%
Simpson 3/8        12    4.25876379670942    0.004811%

Trapeze            18    4.26841212467614    0.231374%
Simpson            18    4.25857710513704    0.000427%
Simpson 3/8        18    4.25859971430526    0.000958%

Trapeze            24    4.26410246529756    0.130174%
Simpson            24    4.25856467550330    0.000135%
Simpson 3/8        24    4.25857185810276    0.000304%

Trapeze            30    4.26210711795574    0.083319%
Simpson            30    4.25856127324214    0.000055%
Simpson 3/8        30    4.25856422074276    0.000125%

Voulez-vous continuer? Taper 'o' si oui, n'importe quelle autre touche pour quitter.
n


*/
