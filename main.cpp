/*
 -----------------------------------------------------------------------------------
 Laboratoire : 03
 Fichier     : main.cpp
 Auteur(s)   : Thomas Ricci
 Date        : 26.09.2018

 But         : <TODO>

 Remarque(s) : <TODO>

 Compilateur : g++ (Ubuntu 5.4.0-6ubuntu1~16.04.10)
 -----------------------------------------------------------------------------------
 */

#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <climits>
#include <ctime> //Utilisé pour générer des nombres pseudo-aléatoires

using namespace std;

int main() {
   
   const unsigned int NBR_EXP_MIN = 1000;
   const unsigned int NBR_EXP_MAX = 100000;
   
   const unsigned int TAILLE_GRILLE_MAX = 10; //50
   const unsigned int TAILLE_GRILLE_MIN = 2;
   const unsigned int TAILLE_GRILLE_INCREMENT = 2;
   
   const unsigned short DIRECTION_DROITE = 1;
   const unsigned short DIRECTION_GAUCHE = 2;
   const unsigned short DIRECTION_HAUT = 3;
   const unsigned short DIRECTION_BAS = 4;
   const unsigned short DISTANCE_DEPLACEMENT = 1;
   
   unsigned nbrExperiences;
   
   nbrExperiences = 100000;
   //Demander à l'utilisateur d'entrer le nombre d'expériences à effectuer
   /*do{
      cout << "Veuillez entrer un nombre d'experience " 
           << "( entre " << NBR_EXP_MIN << " et " << NBR_EXP_MAX << "): ";
      if (not(cin >> nbrExperiences))
      {
         cin.clear();
         cin.ignore(INT_MAX,'\n');
      }
   }while(nbrExperiences <NBR_EXP_MIN || nbrExperiences > NBR_EXP_MAX); */
   
   int x,y;
   short direction; //1=gauche; 2=droite; 3=haut; 4=bas
   unsigned int longueur;
   double longueurMoyenne = 0;
   bool droiteTouch,
        gaucheTouch,
        hautTouch,
        basTouch;
   int nbDroiteTouch,
       nbGaucheTouch,
       nbHautTouch,
       nbBasTouch;
   
   srand((unsigned)time(0));
   
   //Effectuer les expériences
   for(unsigned tailleGrille = TAILLE_GRILLE_MIN; tailleGrille <= TAILLE_GRILLE_MAX; tailleGrille += TAILLE_GRILLE_INCREMENT){
      for(unsigned j = 0; j < nbrExperiences; ++j){
         longueur = 0;
         x = y = tailleGrille / 2;
         droiteTouch = gaucheTouch = hautTouch = basTouch = false;
         while(!(droiteTouch && gaucheTouch && hautTouch && basTouch)){
            // - cout << "pos (" << x << "," << y << ")" << endl;
            //Déterminer direction et effectuer le déplacement
            direction = short(rand() % 4 + 1);
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
            //Si nouvelle direction = bord, rebondir et incrémenter le compteur de bord
            if(x % tailleGrille == 0 ||  y % tailleGrille == 0){
               //Rebondir
               switch (direction){
                  case DIRECTION_GAUCHE:
                     x += DISTANCE_DEPLACEMENT; 
                     gaucheTouch=true;
                     nbGaucheTouch++;
                     break;
                  case DIRECTION_DROITE:
                     x -= DISTANCE_DEPLACEMENT; 
                     droiteTouch=true;
                     nbDroiteTouch++;
                     break;
                  case DIRECTION_HAUT:
                     y -= DISTANCE_DEPLACEMENT; 
                     hautTouch=true;
                     nbHautTouch++;
                     break;
                  case DIRECTION_BAS:
                     y += DISTANCE_DEPLACEMENT; 
                     basTouch=true;
                     nbBasTouch++;
                     break;
                     
               }
               // Incrément en cas de rebond
               ++longueur;
            }
            // Incrément de fonctionnement normal
            ++longueur;
            // - cout << "Direction: " << direction << endl;
            // - cout << "pos après(" << x << "," << y << ")" << endl;
         }
         // - cout << "Longeur total: " << longueur << endl;
         // - cout << "longueurMoyenne: " << longueurMoyenne << endl;
         longueurMoyenne += (double)longueur/nbrExperiences;
      //Ajouter les compteurs de cotés à la moyenne
      }
      cout << setprecision(2) << fixed << "Pour une grille de " << tailleGrille
           << " cases, " << "La longueur moyenne du parcours du robot est " 
           << longueurMoyenne << endl;
      longueurMoyenne = 0;
   }
   
   
   
   return EXIT_SUCCESS;
}
