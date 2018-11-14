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


#include <cmath>

using namespace std;


void expFit(int n, int x[], double y[]){
    int i,j,k;

    double lny[n],a,b,c;

    for (i=0;i<n;i++)                        //Calculate the values of ln(yi)
        lny[i]=log(y[i]);        
    double xsum=0,x2sum=0,ysum=0,xysum=0;                //variables for sums/sigma of xi,yi,xi^2,xiyi etc
    for (i=0;i<n;i++)
    {
        xsum=xsum+x[i];                        //calculate sigma(xi)
        ysum=ysum+lny[i];                        //calculate sigma(yi)
        x2sum=x2sum+pow(x[i],2);                //calculate sigma(x^2i)
        xysum=xysum+x[i]*lny[i];                    //calculate sigma(xi*yi)
    }
    a=(n*xysum-xsum*ysum)/(n*x2sum-xsum*xsum);            //calculate slope(or the the power of exp)
    b=(x2sum*ysum-xsum*xysum)/(x2sum*n-xsum*xsum);            //calculate intercept
    c=pow(2.71828,b);                        //since b=ln(c)
    double y_fit[n];                        //an array to store the new fitted values of y    
    for (i=0;i<n;i++)
        y_fit[i]=c*pow(2.71828,a*x[i]);                    //to calculate y(fitted) at given x points

    /*for (i=0;i<n;i++)
        cout<<i+1<<"."<<setw(8)<<x[i]<<setw(15)<<y[i]<<setw(18)<<y_fit[i]<<endl;//print a table of x,y(obs.) and y(fit.)    
    */
    cout<<"y = "<<c<<"e^"<<a<<"x" << endl;
}



int main() {
   
   const unsigned int NBR_EXP_MIN = 1000;
   const unsigned int NBR_EXP_MAX = 100000;
   
   const unsigned int TAILLE_GRILLE_MAX = 100; //50
   const unsigned int TAILLE_GRILLE_MIN = 2;
   const unsigned int TAILLE_GRILLE_INCREMENT = 2;
   
   const unsigned short DIRECTION_DROITE = 1;
   const unsigned short DIRECTION_GAUCHE = 2;
   const unsigned short DIRECTION_HAUT = 3;
   const unsigned short DIRECTION_BAS = 4;
   const unsigned short DISTANCE_DEPLACEMENT = 1;
   
   unsigned nbrExperiences;
   
   nbrExperiences = 100;
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
   
   double values[TAILLE_GRILLE_MAX / 2];
   int xValues[TAILLE_GRILLE_MAX/2];
   
   for(int i = 0; i < 10; ++i){
   //Effectuer les expériences
   for(unsigned tailleGrille = TAILLE_GRILLE_MIN; tailleGrille <= TAILLE_GRILLE_MAX; tailleGrille += TAILLE_GRILLE_INCREMENT){
      for(unsigned j = 0; j < nbrExperiences; ++j){
         longueur = 0;
         x = y = tailleGrille / 2;
         droiteTouch = gaucheTouch = hautTouch = basTouch = false;
         nbHautTouch = nbDroiteTouch = nbGaucheTouch = nbBasTouch = 0;
         while(!(droiteTouch && gaucheTouch && hautTouch && basTouch)){
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
            
         }
         
         longueurMoyenne += (double)(longueur)/nbrExperiences;
      //Ajouter les compteurs de cotés à la moyenne
      }
      /*cout << "{" << tailleGrille << "," << longueurMoyenne << "},";
      cout << setprecision(2) << fixed << "Pour une grille de " << tailleGrille
           << " cases, " << "La longueur moyenne du parcours du robot est " 
           << longueurMoyenne << endl;*/
      
      values[tailleGrille/2 - 1] = longueurMoyenne;
      xValues[tailleGrille/2 - 1] = tailleGrille;
      longueurMoyenne = 0;
   }
   // cout << "Nombres de touche unique sur";
   
   
   expFit(TAILLE_GRILLE_MAX/2, xValues, values);
   } 
   
   return EXIT_SUCCESS;
}

