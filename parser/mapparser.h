
/***************************************************
 * ---- mapparser.h ----
 * Fonctions gerant le parsage des donnees GPS de la
 * carte du campus
 *
 * Auteur(s) : Team Mobley
 * Date : 16/01/2018
****************************************************/


#ifndef MAPPARSER_H
#define MAPPARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE 40



// ---------------------------------------------------------------------------
// ----------------------------- STRUCTURES ----------------------------------
// ---------------------------------------------------------------------------

/*********************** str_point (point) ************************ 
 * Point de reperes appartenant a la carte (Map)
 * id : identifiant du point
 * name : nom du batiment
 * x : longitude
 * y : latitude
 ***************************************************************/

typedef struct str_point {
  int id;
  char name[MAXSIZE];
  double x; //longitude
  double y; //latitude
} point;

/*********************** str_step (step) ************************ 
 * Chemin entre deux points
 * id : identifiant du chemin
 * src : nom du batiment de depart
 * dest : nom du batiment d'arrivee
 * nbPoints : nombre de points appartenant au chemin
 * points : tableau contenant les points du chemin
 ***************************************************************/
typedef struct str_step {
  int id;
  char src[MAXSIZE];
  char dest[MAXSIZE];
  int nbPoints;
  point* points;
} step;

/*********************** str_map (map) ************************ 
 * Carte (du campus ou autre)
 * sizePoints : nombre de bâtiments appartenant a la carte
 * sizeSteps : nombre de chemins appartenant a la carte
 * tabPoints : tableau contenant les batiments (points) de la carte
 * tabSteps : tableau contenant les chemins appartenant a la carte
 ***************************************************************/
typedef struct str_map {
  int sizePoints;
  int sizeSteps;
  point* tabPoints;
  step* tabSteps;

} map;


/*********************** str_tab (tab) ************************ 
 * Tableau
 * data : tableau
 * size : taille du tableau
 ***************************************************************/
typedef struct str_tab {
  int * data;
  int size;
  int inverse;
} tab;





// ---------------------------------------------------------------------------
// ------------------------- VARIABLES GLOBALES ------------------------------
// ---------------------------------------------------------------------------

/* Tableau contenant le nombre de chemins "directs" (size) et identifiants des
 *  chemins "directs" (data)  pour aller du point de depart au point d'arrivee */
tab resuFinal; 

// Map contenant la carte du monde (ici campus)
map world;

// ---------------------------------------------------------------------------
// ----------------------- CREATION DE LA MAP --------------------------------
// ---------------------------------------------------------------------------

/********************** parsePoints ************************
 * Recupere les coordonnees GPS de points de reperes sur le
 * campus et les place dans le tableau de map
 * INPUTS : fpoints : fichier contenant 
 *          world : structure contenant la carte du campus
 * OUTPUT : --
 *********************************************************/
void parsePoints(FILE *fpoints, map* world);

/********************** parseSteps ******************************
 * Recupere les identifiants des reperes des etapes appartenant
 * a un chemin donne et les place dans le tableau tabSteps 
 * de world
 * INPUTS : fsteps : fichier contenant les etapes d'un chemin
 *          world : structure contenant la carte du campus
 * OUTPUT : --
 ***************************************************************/
void parseSteps(FILE *fsteps, map* world);


/********************** printPoints ******************************
 * Affiche les coordonnees GPS des points de reperes appartenant
 * a la carte du campus 
 * INPUTS : world : structure contenant la carte du campus
 * OUTPUT : --
 ***************************************************************/
void printPoints(map world);

/********************** printPoint ******************************
 * Affiche les coordonnees GPS d'UN point de reperes appartenant
 * a la carte du campus 
 * INPUTS : pt : le point à afficher
 * OUTPUT : --
 ***************************************************************/
void printPoint(point pnt);

/********************** getPoint ******************************
 * Renvoie la structure point du point dont l'id est donne en
 *  entree
 * INPUTS : world : structure contenant la carte du campus
 *          id : identifiant du point concerne
 * OUTPUT : point : structure point correspondant a l'id
 ***************************************************************/
point getPoint(map world, int id);

/********************** getStep ******************************
 * Renvoie la structure Step du chemin dont l'id est donne en
 *  entree
 * INPUTS : world : structure contenant la carte du campus
 *          id : identifiant du step concerne
 * OUTPUT : structure Step correspondant a l'id
 ***************************************************************/
step getStep(map world, int id);

/************************** findSeqStep *********************************
 * Renvoie le nombre de chemins "directs" (size) et identifiants des chemins
 * "directs" (data)  pour aller du point de depart au point
 * d'arrivee
 * INPUTS : world : structure contenant la carte du campus
 *          src : nom du point de depart
 *          dest : nom de la destination
 * OUTPUT : tableau contenant "size" et "data"
 *************************************************************************/
tab findSeqStep (map world, char * src, char *dest, int nbRec);

#endif
