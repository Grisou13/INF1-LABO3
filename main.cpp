/*
 -----------------------------------------------------------------------------------
 Laboratoire : 03
 Fichier     : main.cpp
 Auteur(s)   : Thomas Ricci, Noah Fusi, Gildas Houlmann
 Date        : 20.11.2018

 But         : Déterminer la longueur moyenne du chemin d'un robot dans une grille
 *             avant d'avoir touché les 4 bords de la grille.
 *             Le robot est placé au milieu de la grille, et se déplace aléatoirement
 *             dans 4 directions. Lorsque le robot touche un bord, il rebondit et 
 *             revient sur sa position précédente.
 *             On mesure aussi combien de fois chaque mur est touché répétitivement.
 *             Finalement, on affiche la moyenne de la longueur parcourue et des
 *             Répétitions d'impacts sur chaque mur, le tout pour des tailles de 
 *             grilles différentes.
 *             

 Remarque(s) : Le programme doit donner les mêmes résultats peu importe la machine.
 *             C'est pourquoi les nombres pseudo-aléatoires ne sont pas seedés, 
 *             c'est-à-dire que la suite de nombres générés sera toujours la même.

 Compilateur : g++ 6.3.0 Windows
 *             
 -----------------------------------------------------------------------------------
 */

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <limits>
#include <cmath>

using namespace std;

int main() {
   
   const unsigned int NBR_EXP_MIN = 1000;
   const unsigned int NBR_EXP_MAX = 100000;
   
   const unsigned int TAILLE_GRILLE_MAX = 50;
   const unsigned int TAILLE_GRILLE_MIN = 50;
   const unsigned int TAILLE_GRILLE_INCREMENT = 2;
   
   const unsigned short DIRECTION_DROITE = 1;
   const unsigned short DIRECTION_GAUCHE = 2;
   const unsigned short DIRECTION_HAUT = 3;
   const unsigned short DIRECTION_BAS = 4;
   const unsigned short DISTANCE_DEPLACEMENT = 1;
   
   unsigned nbrExperiences;
   
   nbrExperiences = 1000;
   //Demander à l'utilisateur d'entrer le nombre d'expériences à effectuer
   do{
      cout << "Veuillez entrer un nombre d'experiences " 
           << "(entre " << NBR_EXP_MIN << " et " << NBR_EXP_MAX << "): ";
      if (not(cin >> nbrExperiences))
      {
         cin.clear();
         cin.ignore(numeric_limits<streamsize>::max(),'\n');
      }
   }while(nbrExperiences <NBR_EXP_MIN || nbrExperiences > NBR_EXP_MAX);
   
   int x,y;
   short direction; //1=gauche; 2=droite; 3=haut; 4=bas
   unsigned int longueur;
   double longueurMoyenne;
   
   //Indique si un mur a déjà été touché
   bool droiteTouch,
        gaucheTouch,
        hautTouch,
        basTouch;
   
   //Nombres de fois que chaque mur a été touché répétitivement
   int nbDroiteTouch,
       nbGaucheTouch,
       nbHautTouch,
       nbBasTouch;
   
   double moyenneNbDroiteTouch,
          moyenneNbGaucheTouch,
          moyenneNbHautTouch,
          moyenneNbBasTouch;
   
   int prevBord;
   for(int i = 0; i < 1000; ++i){ //ENLEVER CETTE BOUCLE
   //Effectuer les expériences
   for(unsigned tailleGrille = TAILLE_GRILLE_MIN; tailleGrille <= TAILLE_GRILLE_MAX;
           tailleGrille += TAILLE_GRILLE_INCREMENT){
      longueurMoyenne = 0;
      moyenneNbDroiteTouch = moyenneNbGaucheTouch = moyenneNbHautTouch 
       = moyenneNbBasTouch = 0;
      
      for(unsigned j = 0; j < nbrExperiences; ++j){
         x = y = tailleGrille / 2; //Positionner le robot au milieu de la grille
         longueur = 0;
         droiteTouch = gaucheTouch = hautTouch = basTouch = false;
         nbHautTouch = nbDroiteTouch = nbGaucheTouch = nbBasTouch = 0;
         prevBord=0;
         
         //Continuer l'expérience tant que les 4 murs n'ont pas été touchés
         while(!(droiteTouch && gaucheTouch && hautTouch && basTouch)){
            
            //Déterminer la direction et effectuer le déplacement
            direction = short(rand() % 4 + 1);//Nombre pseudo-aléatoire entre 1 et 4
            switch(direction){
               case DIRECTION_GAUCHE: 
                  x -= DISTANCE_DEPLACEMENT; break;
               case DIRECTION_DROITE: 
                  x += DISTANCE_DEPLACEMENT; break;
               case DIRECTION_HAUT: 
                  y += DISTANCE_DEPLACEMENT; break;
               case DIRECTION_BAS: 
                  y -= DISTANCE_DEPLACEMENT; break;
               default:
                  continue;
            }     

            //Si le robot atteint un mur, il rebondit et la longueur est incrémentée
            if(x % tailleGrille == 0 ||  y % tailleGrille == 0){
               //Rebondir. Si le mur touché est le même que le dernier mur touché,
               //son compteur respectif est incrémenté.
               switch (direction){
                  case DIRECTION_GAUCHE:
                     x += DISTANCE_DEPLACEMENT; 
                     gaucheTouch=true;
                     if(prevBord == direction)
                        nbGaucheTouch++;
                     break;
                  case DIRECTION_DROITE:
                     x -= DISTANCE_DEPLACEMENT; 
                     droiteTouch=true;
                     if(prevBord == direction)
                        nbDroiteTouch++;
                     break;
                  case DIRECTION_HAUT:
                     y -= DISTANCE_DEPLACEMENT; 
                     hautTouch=true;
                     if(prevBord == direction)
                        nbHautTouch++;
                     break;
                  case DIRECTION_BAS:
                     y += DISTANCE_DEPLACEMENT; 
                     basTouch=true;
                     if(prevBord == direction)
                        nbBasTouch++;
                     break;                
               }
               prevBord = direction;
               
               // Incrémentation de la longueur en cas de rebond
               longueur += DISTANCE_DEPLACEMENT;               
            }
            // Incrémentation de la longueur de fonctionnement normal
            longueur += DISTANCE_DEPLACEMENT;
         }
         
         //Calcul des moyennes
         moyenneNbGaucheTouch += (double)(nbGaucheTouch) / nbrExperiences;
         moyenneNbDroiteTouch += (double)(nbDroiteTouch)/ nbrExperiences;
         moyenneNbHautTouch += (double)(nbHautTouch) / nbrExperiences;
         moyenneNbBasTouch += (double)(nbBasTouch)/ nbrExperiences; 
         longueurMoyenne += (double)longueur/nbrExperiences;
           
      } //Fin de l'expérience 

      cout << setprecision(2) << fixed << "Pour une grille de " << tailleGrille
           << " cases, " << "La longueur moyenne du parcours du robot est " 
           << longueurMoyenne << endl;
      cout << "Le bord gauche a été heurté répétitivement en moyenne " 
           << moyenneNbGaucheTouch << " fois" << endl;
      cout << "Le bord droite a été heurté répétitivement en moyenne " 
           << moyenneNbDroiteTouch << " fois" << endl;
      cout << "Le bord haut a été heurté répétitivement en moyenne " 
           << moyenneNbHautTouch << " fois" << endl;
      cout << "Le bord bas a été heurté répétitivement en moyenne "
           << moyenneNbBasTouch << " fois" << endl << endl;
   }
   }
   
   
   return EXIT_SUCCESS;
}