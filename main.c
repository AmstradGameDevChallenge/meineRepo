//-----------------------------LICENSE NOTICE------------------------------------
//  This file is part of CPCtelera: An Amstrad CPC Game Engine
//  Copyright (C) 2018 ronaldo / Fremos / Cheesetea / ByteRealms (@FranGallegoBR)
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.
//------------------------------------------------------------------------------

#include <cpctelera.h>
#include <math.h>
struct tValue{
   u8 energy;
   u8 defense;
   u8 attack;
}myPlayer,myEnemy;

struct tScreenPositions{
   u8 posX;
   u8 posY;
}myPlayerPos,myEnemyPos;

void initPlayerValues(){
   myPlayer.energy  =15;
   myPlayer.defense =15;
   myPlayer.attack  =15;
   myPlayerPos.posX =0; 
   myPlayerPos.posY =10; 
}

void initEnemyValues(){
   myEnemy.energy   =15;
   myEnemy.defense  =15;
   myEnemy.attack   =15;
   myEnemyPos.posX  =0; 
   myEnemyPos.posY  =40; 
}

u8 valueEnergy=0;


void paintPlayerValuesInScreen()
{
   u8* textPlayerPosition;
   u8* textPlayerEnergyPosition;
   u8* textPlayerDefensePosition;
   u8* textPlayerAttackPosition;
   u8  offsetTextX = 10;

   textPlayerPosition            = cpct_getScreenPtr(CPCT_VMEM_START, myPlayerPos.posX,myPlayerPos.posY+4);
   textPlayerEnergyPosition      = cpct_getScreenPtr(CPCT_VMEM_START, myPlayerPos.posX+(offsetTextX*2),myPlayerPos.posY);
   textPlayerDefensePosition     = cpct_getScreenPtr(CPCT_VMEM_START, myPlayerPos.posX+(offsetTextX*4),myPlayerPos.posY);
   textPlayerAttackPosition      = cpct_getScreenPtr(CPCT_VMEM_START, myPlayerPos.posX+(offsetTextX*6),myPlayerPos.posY);
   
   cpct_setDrawCharM1(1, 0);
   cpct_drawStringM1("Player: "  , textPlayerPosition);
   cpct_drawStringM1("Energy: "  , textPlayerEnergyPosition);
   cpct_drawStringM1("Defense: " , textPlayerDefensePosition);
   cpct_drawStringM1("Attack: "  , textPlayerAttackPosition);

}

void paintPlayerBoxesInScreen(){
   u8  offsetTextX = 10;
   u8  offsetTextY = 10;

   u8* drawBoxPlayerPosition;
   u8* drawBoxPlayerEnergyPosition;
   u8* drawBoxPlayerDefensePosition;
   u8* drawBoxPlayerAttackPosition;


   drawBoxPlayerPosition            = cpct_getScreenPtr(CPCT_VMEM_START, myPlayerPos.posX,myPlayerPos.posY);
   drawBoxPlayerEnergyPosition      = cpct_getScreenPtr(CPCT_VMEM_START, myPlayerPos.posX+(offsetTextX*2),myPlayerPos.posY+10);
   drawBoxPlayerDefensePosition     = cpct_getScreenPtr(CPCT_VMEM_START, myPlayerPos.posX+(offsetTextX*4),myPlayerPos.posY+10);
   drawBoxPlayerAttackPosition      = cpct_getScreenPtr(CPCT_VMEM_START, myPlayerPos.posX+(offsetTextX*6),myPlayerPos.posY+10);
   
    
    

    cpct_drawSolidBox(drawBoxPlayerEnergyPosition, cpct_px2byteM1(3, 3, 3, 3), myPlayer.energy , 10); // 0xFF 
    cpct_drawSolidBox(drawBoxPlayerDefensePosition, cpct_px2byteM1(3, 3, 3, 3), myPlayer.defense, 10); // 0xFF 
    cpct_drawSolidBox(drawBoxPlayerAttackPosition, cpct_px2byteM1(3, 3, 3, 3), myPlayer.attack , 10);
     // 0xFF 


}

void paintEnemyValuesInScreen()
{
   u8* textEnemyPosition;
   u8* textEnemyEnergyPosition;
   u8* textEnemyDefensePosition;
   u8* textEnemyAttackPosition;
   u8  offsetTextX = 10;

   textEnemyPosition            = cpct_getScreenPtr(CPCT_VMEM_START, myEnemyPos.posX,myEnemyPos.posY+4);
   textEnemyEnergyPosition      = cpct_getScreenPtr(CPCT_VMEM_START, myEnemyPos.posX+(offsetTextX*2),myEnemyPos.posY);
   textEnemyDefensePosition     = cpct_getScreenPtr(CPCT_VMEM_START, myEnemyPos.posX+(offsetTextX*4),myEnemyPos.posY);
   textEnemyAttackPosition      = cpct_getScreenPtr(CPCT_VMEM_START, myEnemyPos.posX+(offsetTextX*6),myEnemyPos.posY);
   
   cpct_setDrawCharM1(1, 0);
   cpct_drawStringM1("Enemy: "  , textEnemyPosition);
   cpct_drawStringM1("Energy: "  , textEnemyEnergyPosition);
   cpct_drawStringM1("Defense: " , textEnemyDefensePosition);
   cpct_drawStringM1("Attack: "  , textEnemyAttackPosition);

}
void paintEnemyBoxesInScreen(){

   u8  offsetTextX = 10;
   u8  offsetTextY = 10;
  

   u8* drawBoxEnemyPosition;
   u8* drawBoxEnemyEnergyPosition;
   u8* drawBoxEnemyDefensePosition;
   u8* drawBoxEnemyAttackPosition;


   drawBoxEnemyPosition            = cpct_getScreenPtr(CPCT_VMEM_START, myEnemyPos.posX,myEnemyPos.posY);
   drawBoxEnemyEnergyPosition      = cpct_getScreenPtr(CPCT_VMEM_START, myEnemyPos.posX+(offsetTextX*2),myEnemyPos.posY+10);
   drawBoxEnemyDefensePosition     = cpct_getScreenPtr(CPCT_VMEM_START, myEnemyPos.posX+(offsetTextX*4),myEnemyPos.posY+10);
   drawBoxEnemyAttackPosition      = cpct_getScreenPtr(CPCT_VMEM_START, myEnemyPos.posX+(offsetTextX*6),myEnemyPos.posY+10);


 cpct_scanKeyboard_f();

      // Check if user has pressed a Cursor Key and, if so, move the sprite if
      // it will still be inside screen boundaries

  
      if      (cpct_isKeyPressed(Key_CursorRight) ){
         if (valueEnergy<14){
            valueEnergy= valueEnergy + 1;  cpct_waitVSYNC();
         }
         cpct_clearScreen_f64(0x00);

         
      }
   
   //cpct_drawSolidBox(drawBoxEnemyEnergyPosition, cpct_px2byteM1(3, 3, 3, 3), myEnemy.energy , 10); // 0xFF
   cpct_drawSolidBox(drawBoxEnemyEnergyPosition, cpct_px2byteM1(3, 3, 3, 3), myEnemy.energy-valueEnergy , 10); // 0xFF

   cpct_drawSolidBox(drawBoxEnemyDefensePosition, cpct_px2byteM1(3, 3, 3, 3), myEnemy.defense, 10); // 0xFF 
   cpct_drawSolidBox(drawBoxEnemyAttackPosition, cpct_px2byteM1(3, 3, 3, 3), myEnemy.attack , 10); // 0xFF 
   

}





void main(){
    
   initPlayerValues();
   initEnemyValues();
   
 

   while(1){

     
   //Press key Action
    

    paintPlayerBoxesInScreen();
    paintEnemyBoxesInScreen();

   

    paintPlayerValuesInScreen();
    paintEnemyValuesInScreen();

   
  
        
     
   }

}
