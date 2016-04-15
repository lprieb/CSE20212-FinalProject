#include<iostream>
#include<cstdlib>
#include"sdl_win_wrap.h"
#include"texture.h"
#include"Rivercrossing.h"

#define wolf 1
#define goat 2
#define cabbage 4

Rivercrossing::Rivercrossing(SDL_Window* ngWindow, SDL_Renderer* ngRenderer): 
   gBackgroundTexture(ngWindow, ngRenderer), \
   gSheep(ngWindow, ngRenderer), \
   gWolf(ngWindow, ngRenderer), \
   gCabbage(ngWindow, ngRenderer), \
   gBoat(ngWindow, ngRenderer), \
   gWindow(ngWindow), \
   gRenderer(ngRenderer)

{

   //window dimensions
   SDL_GetWindowSize(ngWindow, &SCREEN_WIDTH, &SCREEN_HEIGHT);

   end=0;
   start=7;
   onboat=0;
   //1=start position, -1=end position
   position=1;
   nummoves=0;
   numtries=1;

   loadMedia();

}

Rivercrossing::~Rivercrossing() {

   gBackgroundTexture.free();
   gSheep.free();
   gWolf.free();
   gCabbage.free();
   gBoat.free();

}

void Rivercrossing::reset() {   //reset all values to replay

   end=0;
   start=7;
   onboat=0;
   //1=start position, -1=end position
   position=1;

}

void Rivercrossing::play() {

   SDL_Event e;
   bool change;
   bool changeboat;
   int points;
   char choice;

   //initial display
   display();

   //not game over or success
   int game=finished();
   while (game==1) {
      display();
      change=false;
      //change is true when position of one of 3 items is changed
      manageEvents(e, change, changeboat);
      //if something changed position, render images again and display
      if(change) {
	 display();
      }
      //if boat changed, chek if game over
      if(changeboat) {
	 display();
	 switch (finished()) {
	    case 2:
	       display();
	       //wolf ate goat, game over! ask to try again(click y)
	       cout << "The wolf has ate the sheep! Game over!" << endl;
	       cout << "Would you like to try again? If you don't help this farmer, you get 0 points! Press y to continue, n to quit. " << endl;
	       cin >> choice;
	       if (choice=='y') {
		  reset();
		  numtries++;
		  game=1;
	       }
	       else if (choice=='n') {
		  cout << "You tried " << numtries << " times but couldn't help the farmer! You get no points. Sorry!" << endl;
		  game=0;
	       }
	       break;
	    case 3:
	       display();
	       //goat ate cabbage, game over! ask to try again(click y)
	       cout << "The sheep has ate the cabbage! Game over!" << endl;
	       cout << "Would you like to try again? If you don't help this farmer, you get 0 points! Press y to continue, n to quit. " << endl;
	       cin >> choice;
	       if (choice=='y') {
		  reset();
		  numtries++;
		  game=1;
	       }
	       else if (choice=='n') {
		  cout << "You tried " << numtries << " times but couldn't help the farmer! You get no points. Sorry!" << endl;
		  game=0;
	       }
	       break;
	    case 0:
	       display();
	       //success!
	       points=100/numtries;
	       cout << "The farmer is so thankful for your help! You finished in " << numtries << " tries, so you get " << points << " points!" << endl;
	       if (points<=40) {
		  cout << "The farmer thanks you with his cabbage!" << endl;
	       }
	       else if (points>40 && points <=60) {
		  cout << "The farmer thanks you with some expensive cheese from his goats on the farm!" << endl;
	       }
	       else if (points<=100 && points>61) {
		  cout << "The farmer thanks you with his cabbage, some really nice goat cheese, and a cute wool scarf made from real sheep wool!" << endl;
	       }
	       game=0;
	       break;
	 }

      }

   }

}

int Rivercrossing::finished() {

   //return 0 means finished successfully
   //return 1 means not yet finished but not game over
   //return 2 means wolf ate goat and game over
   //return 3 means goat ate cabbage and game over
   if (end==goat+cabbage+wolf) {
      return 0;
   }
   else if (position==1) {
      if (end==wolf+goat) {
	 return 2;
      }
      else if (end==goat+cabbage) {
	 return 3;
      }
   }
   else if (position==-1) {
      if (start==wolf+goat) {
	 return 2;	 
      }
      else if (start==goat+cabbage) {
	 return 3;
      }
   }

   return 1;
   

}

void Rivercrossing::display() {
   SDL_RenderClear(gRenderer);

   //Render background
   gBackgroundTexture.render(0, 0, NULL);

   //render boat
   if (position==1) {
      gBoat.render(190, 330, NULL);
      if (onboat==cabbage) {
	 gCabbage.render(50+190, 155+330, NULL);
      }
      else if (onboat==wolf) {
	 gWolf.render(105+190, 190+330, NULL);
      }
      else if (onboat==goat) {
	 gSheep.render(15+190, 60+550, NULL);
      }
   }
   else if (position==-1) {
      gBoat.render(285, 330, NULL);
      if (onboat==cabbage) {
	 gCabbage.render(50+285, 155+330, NULL);
      }
      else if (onboat==wolf) {
	 gWolf.render(105+285, 190+330, NULL);
      }
      else if (onboat==goat) {
	 gSheep.render(15+285, 60+550, NULL);
      }
   }
 
   //render items
   //at start
   if (start == goat + cabbage + wolf) {
      gSheep.render(110, 335, NULL);
      gWolf.render(85, 390, NULL);
      gCabbage.render(20, 345, NULL);
   }
   else if (start == goat + cabbage) {
      gCabbage.render(20, 345, NULL);
      gSheep.render(110, 335, NULL);
   }
   else if (start == goat + wolf) {
      gSheep.render(110, 335, NULL);
      gWolf.render(85, 390, NULL);
   }
   else if (start == wolf+cabbage) {
      gWolf.render(85, 390, NULL);
      gCabbage.render(20, 345, NULL);
   }
   else if (start == goat) {
      gSheep.render(110, 335, NULL);
   }
   else if (start == cabbage) {
      gCabbage.render(20, 345, NULL);
   }
   else if (start == wolf) {
      gWolf.render(85, 390, NULL);
   }

   //at end
   if (end == goat + cabbage + wolf) {
      gSheep.render(450, 340, NULL);
      gWolf.render(410, 385, NULL);
      gCabbage.render(380, 340, NULL);
   }
   else if (end == goat + cabbage) {
      gCabbage.render(380, 340, NULL);
      gSheep.render(450, 340, NULL);
   }
   else if (end == goat + wolf) {
      gSheep.render(450, 340, NULL);
      gWolf.render(410, 385, NULL);
   }
   else if (end == wolf+cabbage) {
      gWolf.render(410, 385, NULL);
      gCabbage.render(380, 340, NULL);     
   }
   else if (end == goat) {
       gSheep.render(450, 340, NULL);     
   }
   else if (end == cabbage) {
       gCabbage.render(380, 340, NULL);  
   }
   else if (end == wolf) {
      gWolf.render(410, 385, NULL);
   }

   //update screen
   SDL_RenderPresent(gRenderer);

}

void Rivercrossing::manageEvents(SDL_Event &e, bool &change, bool &changeboat) {

   bool toContinue = false;
   int pos;

   while(!toContinue) {

      SDL_WaitEvent(NULL);

      while(SDL_PollEvent(&e)) {

	 if(e.type == SDL_QUIT) {
	    toContinue = true;
	 }

	 //boat movement with arrow keys
	 //click down once, it will move to opp side
	 else if(e.type == SDL_KEYDOWN && e.key.repeat == 0) {
	    switch(e.key.keysym.sym) {
	       case SDLK_LEFT:
		  //only switch position if at start
		  if (position==1) {
		     position=position*(-1);
		  }
		  changeboat=true;
		  break;
	       case SDLK_RIGHT:
		  //only switch position if at end
		  if (position==-1) {
		     position=position*(-1);
		  }
		  changeboat=true;
		  break;
	    }
	 }
	 else if(e.type == SDL_MOUSEBUTTONDOWN) {
            //get mouse position
	    int x, y;
	    SDL_GetMouseState(&x, &y);
	    
	    //check where mouse is
	    pos=mousepos(x, y);
	    
	    switch (pos) {
	       case wolf: //move wolf to boat and move out whatever was in boat if there was anythong
		  drop();
		  pickup('w');
		  change=true;
		  break;
	       case goat: //move goat to boat and move out whatever was in boat if there was anything
		  drop();
		  pickup('g');
		  change=true;
		  break;
	       case cabbage: //move cabbage to boat and move out whatever was in boat if there was anything
		  drop();
		  pickup('c');
		  change=true;
		  break;
	       case 3: //boat, if boat empty, dont to anything, if not empty move whatever is on boat back to land
		  drop();
		  change=true;
		  break;
	       default:  //default case, dont do anything
		  break;
	    }
	 }
      }
   }
}
         

int Rivercrossing::mousepos(int x, int y) {

   int b=3;

   if (position==1) { //if at start, only need to check for clicks on start side
      //start side, return positive val
      if ((x>=50 || x<=100) && (y>=354 || y<=387)) {
	 return cabbage;
      }
      else if ((x>=85 || x<=150) && (y>=390 || y<=457)) {
	 return wolf;
      }
      else if ((x>=110 || x<=170) && (y>=335 || y<=376)) {
	 return goat;
      }
      else if ((x>=190 || x<=270) && (y>=330 || y<=242)) {
	 return b;
      }
   }
   else if (position==-1) {
      //end side, return neg val
      if ((x>=380 || x<=430) && (y>=340 || y<=382)) {
	 return cabbage*(-1);
      }
      else if ((x>=410 || x<=475) && (y>=385 || y<=452)) {
	 return wolf*(-1);
      }
      else if ((x>=450 || x<=510) && (y>=340 || y<=381)) {
	 return goat*(-1);
      }
      else if ((x>=285 || x<=365) && (y>=330 || y<=424)) {
	 return b*(-1);
      }
   }

   //all other clicks return 0
   return 0;

}

void Rivercrossing::drop() {

   char choice;

   if (position==1) {
      start=start+onboat;
      onboat=0;
   }
   else if (position==-1) {
      end=end+onboat;
      onboat=0;
   }
  
}

void Rivercrossing::pickup(char choice) {

   switch (choice) {
      case 'w':
	 //check if wolf on that side
	 if (position==1) {
	    if (start==wolf+goat || start==wolf+cabbage || start==wolf+goat+cabbage || start==wolf) {
	       onboat=wolf;
	       start=start-wolf;
	    }
	 }
	 else if (position==-1) {
	    if (end==wolf+goat || end==wolf+cabbage || end==wolf) {
	       onboat=wolf;
	       end=end-wolf;
	    }
	 }
	 break;
      case 'g':
	 //check if goat on that side
	 if (position==1) {
	    if (start==wolf+goat || start==goat+cabbage || start==wolf+goat+cabbage || start==goat) {
	       onboat=goat;
	       start=start-goat;
	    }
	 }
	 else if (position==-1) {
	    if (end==wolf+goat || end==goat+cabbage || end==goat) {
	       onboat=goat;
	       end=end-goat;
	    }
	 }
	 break;
      case 'c':
	 //check if cabbage on that side
	 if (position==1) {
	    if (start==cabbage+goat || start==cabbage+wolf || start==wolf+goat+cabbage || start==cabbage) {
	       onboat=cabbage;
	       start=start-cabbage;
	    }
	 }
	 else if (position==-1) {
	    if (end==cabbage+goat || end==cabbage+wolf || end==cabbage) {
	       onboat=cabbage;
	       end=end-cabbage;
	    }
	 }
	 break;
   }
   
}

bool Rivercrossing::loadMedia() {

   bool success = true;

   if (!gBackgroundTexture.loadFromFile("images/river.png")) {
      printf("failed to load background texture\n");
      success=false;
   }
   if (!gSheep.loadFromFile("images/sheep.png")) {
      printf("failed to load sheep texture\n");
      success=false;
   }
   if (!gWolf.loadFromFile("images/wolf.png")) {
      printf("failed to load wolf texture\n");
      success=false;
   }
   if (!gCabbage.loadFromFile("images/cabbage.png")) {
      printf("failed to load cabbage texture\n");
      success=false;
   }
   if (!gBoat.loadFromFile("images/farmerandboat1.png")) {
      printf("failed to load boat texture\n");
      success=false;
   }

   return success;

}

