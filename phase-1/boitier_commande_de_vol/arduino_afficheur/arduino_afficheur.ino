#include <SPI.h>
#include <Ucglib.h>
int buttonPins[2] = {8,9};
boolean buttonEtat[2] = {false, false};
int pressBouton = 0;
int flag = 0;
int oldX = 0;
int oldCol = 0;
int oldY = 0;
int oldPal = 0 ;
int flagD = 1;
Ucglib_ILI9341_18x240x320_SWSPI ucg(/*sclk=*/ 7, /*data=*/ 6, /*cd=*/ 5 , /*cs=*/ 3, /*reset=*/ 4);
const int boutonSuiv = 8 ;
const int boutonPrec = 9 ;

  
void setup(void){
   Serial.begin(9600);
   delay(1000);
   ucg.begin(UCG_FONT_MODE_TRANSPARENT);
   ucg.clearScreen();
 
  //afficheCollectif();
   // affichePallonier();
  afficheCyclique();
   ucg.setRotate180();
   pinMode(boutonSuiv,INPUT_PULLUP);
   pinMode(boutonPrec,INPUT_PULLUP);
   }

void loop(void){
 
   long int potardX = analogRead(0);
   long int potardY = analogRead(1);
   int potardCol = analogRead(2);
   int potardPal = analogRead(3);
    Serial.println(potardX);
   int newX = map(potardX,30,1000,0,230);
   int newY = map(potardY,30,1000,0,230);
   int newCol = map(potardCol,100,1024,0,238);
   int newPal = map(potardPal,512,1024,0,235);

     
 etatBouton();
     deplacement();
   afficheD(newY, newX,newCol,newPal);
 
  //jaugeCollectif();
   
   //if(digitalRead(boutonSuiv)==1{
  // ucg.clearScreen ;}
   
}

void affichePallonier(void){
  ucg.clearScreen();
  ucg.setColor(255,255,255);
  ucg.drawFrame(40,60,121,122);
  ucg.drawFrame(40,180,121,122);
  }

void afficheCyclique(void){
  ucg.clearScreen();
  ucg.setColor(255,255,255);
  ucg.drawFrame(10,50,220,220);   //largeur de l'écran = 240x320 pixels 
  }
  
void afficheCollectif(void){
  ucg.clearScreen();
  ucg.setColor(255,255,255);
  ucg.drawFrame(40,60,120,240);
  }




void positionCyclique(int newY , int newX){
  
  if(oldY != newY || oldX != newX){
    ucg.setColor(0,0,0);
    ucg.drawDisc(oldY-20,oldX+20,5,15);
    ucg.setColor(255,255,255);
    ucg.drawDisc(newY-20,newX+20,5,15);
    
    oldX=newX;
    oldY=newY;
     
 
  }
}
  
//void positionCyclique(int newY , int newX){
  // int potardX = analogRead(0);
  // int potardY = analogRead(1);

  // int newX = map(potardX,0,1024,0,200);
   //int newY = map(potardY,0,1024,0,200);

//   if(oldY != newY || oldX != newX){
  //    if(newY > oldY + 1 || newX > oldX + 1){
 //        ucg.setColor(255,255,255);
 //        ucg.drawDisc(newX+20,newY+60,5,15);
         // ucg.drawLine(newX+10,100,newX+30,100);
   //      ucg.setColor(0,0,0);
   //      ucg.drawDisc(oldX+20,oldY+60,5,15);
         // ucg.drawLine(oldX+10,100,oldX+30,100);
  //       oldX=newX;
 //        oldY=newY;
         //Serial.println(potardX);
 //        }
 //     else if(newY < oldY - 1 || newX < oldY - 1){
  //       ucg.setColor(255,255,255);
//         ucg.drawDisc(newX+20,newY+60,5,15);
         //ucg.drawLine(newX+10,100,newX+30,100);
//         ucg.setColor(0,0,0);
//         ucg.drawDisc(oldX+20,oldY+60,5,15);
         //ucg.drawLine(oldX+10,100,oldX+30,100);
  //      oldX=newX;
 //        oldY=newY;
       //  Serial.println(potardX);
//         }
//      }
//   }



void jaugeCollectif(int newCol){
  
 //  int potard = analogRead(0);
   //int newX = map(potard,0,1024,0,238);

 
   if(oldCol != newCol ){
      if(newCol > oldCol +1){
         ucg.setColor(255,255,255);
         ucg.drawBox(41,oldCol+61,118,newCol-oldCol);
         // ucg.setColor(0,0,0);
         // ucg.drawBox(41,oldX+61,119,newX-oldX);
         oldCol = newCol;
       //  Serial.println(potard);
         }
         
      else if(newCol < oldCol - 1){
         ucg.setColor(0,0,0);
         //ucg.drawBox(41,newX+61,119,-newX);
         ucg.drawBox(41, newCol+61,118, oldCol-newCol);
         oldCol = newCol;
     //    Serial.println(potard);
         }
      }
   }


/*void jaugePallonier(){
   int potard = analogRead(0) ;
   int newX = map(potard,0,1024,0,240);

   Serial.println(newX);

   //newX -= 120;
   ucg.setColor(255,255,255);
   ucg.drawBox(41, newX+61,119, oldX-newX);
   oldX = newX;
   if (newX < (newX - 120)){
     ucg.setColor(0,0,255);
   ucg.drawBox(41, newX+61,119, oldX-newX);
   } 
   else if (newX > (newX - 120)){
      ucg.setColor(255,0,0);
   ucg.drawBox(41, newX+61,119, oldX-newX);
   } 
   
}*/

void jaugePallonier(int newPal){
  
  // int potard = analogRead(0) ;
  // int newX = map(potard,0,1024,0,238);

  // potardPal -= 512;
 
   if(newPal<115){
      if(oldPal != newPal ) {
         if(newPal > oldPal +1 ){
            ucg.setColor(0,0,0);
            ucg.drawBox(41,oldPal +66,119,newPal-oldPal);
            oldPal = newPal;
           // Serial.println(potard);   
            } 
            
         else if(newPal < oldPal - 1){
            ucg.setColor(255,255,255);
            ucg.drawBox(41, newPal +66,119, oldPal-newPal);
            oldPal = newPal;
          //  Serial.println(potard);
            }
         }
   }
   else{
      if(oldPal != newPal ){
         if(newPal > oldPal +1){
            ucg.setColor(255,255,255);
            ucg.drawBox(41,oldPal +65,119,newPal-oldPal);
            oldPal = newPal;
           // Serial.println(potard);   
            } 
         else if(newPal < oldPal - 1){
            ucg.setColor(0,0,0);
            ucg.drawBox(41, newPal +65,119, oldPal-newPal);
            oldPal = newPal;
           // Serial.println(potard);
            }
         }  
      }
   }


void etatBouton(){
  if (!digitalRead(boutonSuiv)==1 ){
  //  buttonEtat[0] = true ;
  //  buttonEtat[1] = false ;
    pressBouton = 1 ;
  }

  if (!digitalRead(boutonPrec)==1){
  //  buttonEtat[0] = false ;
  //  buttonEtat[1] = true ;
    pressBouton = 2 ;
  }
}


void deplacement(){
  if((pressBouton==1) && (flagD < 3)){
    flagD++;
    pressBouton = 0;
    affiche1();}
  if((pressBouton==2) && (flagD > 1)){
    flagD--;
    pressBouton= 0;
    affiche1();}
}


void affiche1(){
  if (flagD == 1)
    afficheCyclique();
  if (flagD == 2)
    afficheCollectif();
  if (flagD == 3)
    affichePallonier();
}

void afficheD(int newY , int newX, int newCol, int newPal){
    if (flagD == 1)
    positionCyclique(newY, newX);
  if (flagD == 2)
    jaugeCollectif(newCol);
  if (flagD == 3)
    jaugePallonier(newPal);
}
