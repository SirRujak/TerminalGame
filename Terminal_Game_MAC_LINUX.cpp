// TerminalGame.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <string>
using namespace std;

#define ScreenWidth 700
#define ScreenHeight 400

void endGame();
void initGame();
void gameLoop();
void staticChars();
void printImportant();
int xcoord;
int ycoord;
#define NUMOTRIES 4
#define textHeight 16
#define textWidth 9
#define textSize 16
long long triesLeft;
int attemptNumber;
float mouseCordX;
float mouseCordY;
int gameWon = 0;
int chosenHelpers[14] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
long long numCharSame = 0;

string characters1[][12] = {  //	0	1	2	3	4	5	6	7	8	9  10	11
						/*0, 6*/  {"*","#","(","*","/","!","#","^","&","$",")","K"},
					    /*1, 7*/  {"N","/","H","@","P","I","C","K","A","X","E","S"},
					    /*2, 8*/  {"Y","#","#","E","#","5","K","N","D","K","8","6"},//Random
					    /*3, 9*/  {"/","4","A","L","L","I","A","N","C","E","A","*"},
					    /*4, 10*/ {"F","2","R","A","C","X","?","X","$","#","W","I"},
					    /*5, 11*/ {"L","D","C","A","R","D","#","Q","Y","C","B","D"},
					    /*6, 12*/ {"E","V","Y","L","I","&","N","V","4","F","C","C"},//Random
						/*7, 13*/ {"/","[","%","#","@","&","!","]","8","X","U","I"},//Random
					    /*8, 14*/ {"D","N","1","J","T","G","U","N","F","I","G","H"},
					    /*9, 15*/ {"T","K","V","4","^","<","*","&",">","5","A","Q"},
					    /*10, 16*/{"T","T","Z","M","1","/","L","S","G","R","E","C"},
					    /*11, 17*/{"O","R","D","I","N","G","P","O","<","^",":","^"},
					    /*12, 18*/{"$","?",">","H","3","N","K","#","H","A","R","6"},
					    /*13, 19*/{"S","3","M","T","A","W","A","R","C","R","A","F"},
					    /*14, 20*/{"T","D","M","D","D","^","9","9","S","@","K","@"},
					    /*15, 21*/{"Y","/","7","R","9","2","H","6","#","J","3","9"},//Random
					    /*16, 22*/{"Z","Y","L","!","Z","0","1","2","P","O","W","R"}//Random
};

string characters2[][12] = {  //	0	1	2	3	4	5	6	7	8	9  10	11
						/*0, 6*/  {"2","J","M","&","N","S","&","B","3","L","#","*"},//Random
		 			    /*1, 7*/  {"5","A","P","A","N","G","O","L","I","N","6","5"},
					    /*2, 8*/  {"3","B","S","[","^","*","@","$","]","@","9","H"},//Random
					    /*3, 9*/  {"$","2","?","/","W","Q","0","Z","3","9","R","K"},//Random
					    /*4, 10*/ {"Z","L","F","F","T","7","H","E","L","E","C","T"},
					    /*5, 11*/ {"R","O","N","T","G","I","*","1","8","S","E","2"},
					    /*6, 12*/ {"V","Y","R","W","R","?","I","E","R","*","C","O"},//Random
					    /*7, 13*/ {"D","L","*","X","6","9","A","B","R","A","S","I"},
					    /*8, 14*/ {"V","E","I","S","E","A","S","H","E","L","L","Z"},
						/*9, 15*/{"#","!","#","S","L","1","Q","<","*","#",";","~"},//Random
					    /*10, 16*/{"+","*",">","U","5","R","F","^","2","^","U","N"},//Random
						/*11, 17*/{"O","C","H","R","&","#",">","6","G","I","N","8"},
					    /*12, 18*/{"1","5","L","S","A","#","1","D","1","I","F","{"},//Random
					    /*13, 19*/{"&","@","%","}","N","A","M","D","I","S","P","A"},
					    /*14, 20*/{"T","C","H","D","6","!","$","J","!","4","*","3"},
					    /*15, 21*/{"E","&","*","6","$","V","J","6","X","S","E","2"},//Random
					    /*16, 22*/{"P","A","M","U","S","I","C","I","A","N","W","9"}
};

int main()
{
	initGame();
	endGame();
}


void initGame()
{
	triesLeft = NUMOTRIES;
	bool subtractTry = false;
	if(!al_init())
	{
		al_show_native_message_box(NULL,NULL,NULL,"Could not initialize Allegro 5",NULL,NULL);
	}

	al_set_new_display_flags(ALLEGRO_WINDOWED);
	ALLEGRO_DISPLAY *display = al_create_display(ScreenWidth, ScreenHeight);
	al_set_window_position(display, 200, 100);
	al_set_window_title(display, "TITLE");

	ALLEGRO_COLOR green = al_map_rgb(0, 128, 0);
	ALLEGRO_COLOR blue = al_map_rgb(0,0,255);
	ALLEGRO_COLOR black = al_map_rgb(0, 0, 0);


	al_init_font_addon();
	al_init_ttf_addon();
	al_init_primitives_addon();
	al_install_mouse();

	// Printing Header
	ALLEGRO_FONT *font = al_load_font("ConsolaMono-Bold.ttf", textSize, NULL);
	al_draw_text(font, green, 0, textHeight*1, ALLEGRO_ALIGN_LEFT,"ROBCO INDUSTRIES (TM) TERMLINK PROTOCOL");
	al_draw_text(font, green, 0, textHeight*2, ALLEGRO_ALIGN_LEFT,"ENTER PASSWORD NOW");
	al_draw_text(font, green, 0, textHeight*4, ALLEGRO_ALIGN_LEFT,"4 ATTEMPT(S) LEFT:");
	al_draw_text(font, green, textWidth*20, textHeight*4, ALLEGRO_ALIGN_LEFT,"[] [] [] []");


	// Printing Hex Values
	al_draw_text(font, green, textWidth*0,textHeight*6, ALLEGRO_ALIGN_LEFT, "0x87FA");
	al_draw_text(font, green,textWidth*0,textHeight*7,ALLEGRO_ALIGN_LEFT, "0x39E7");
	al_draw_text(font, green,textWidth*0,textHeight*8,ALLEGRO_ALIGN_LEFT, "0x7A78");
	al_draw_text(font, green,textWidth*0,textHeight*9,ALLEGRO_ALIGN_LEFT, "0x721B");
	al_draw_text(font, green,textWidth*0,textHeight*10,ALLEGRO_ALIGN_LEFT, "0x45EB");
	al_draw_text(font, green,textWidth*0,textHeight*11,ALLEGRO_ALIGN_LEFT, "0x4E73");
	al_draw_text(font, green,textWidth*0,textHeight*12,ALLEGRO_ALIGN_LEFT, "0x6D61");
	al_draw_text(font, green,textWidth*0,textHeight*13,ALLEGRO_ALIGN_LEFT, "0x31DF");
	al_draw_text(font, green,textWidth*0,textHeight*14,ALLEGRO_ALIGN_LEFT, "0x5CC2");
	al_draw_text(font, green,textWidth*0,textHeight*15,ALLEGRO_ALIGN_LEFT, "0x4FE2");
	al_draw_text(font, green,textWidth*0,textHeight*16,ALLEGRO_ALIGN_LEFT, "0x52F5");
	al_draw_text(font, green,textWidth*0,textHeight*17,ALLEGRO_ALIGN_LEFT, "0x64E8");
	al_draw_text(font, green,textWidth*0,textHeight*18,ALLEGRO_ALIGN_LEFT, "0x7D94");
	al_draw_text(font, green,textWidth*0,textHeight*19,ALLEGRO_ALIGN_LEFT, "0x2879");
	al_draw_text(font, green,textWidth*0,textHeight*20,ALLEGRO_ALIGN_LEFT, "0x26F0");
	al_draw_text(font, green,textWidth*0,textHeight*21,ALLEGRO_ALIGN_LEFT, "0x7BE5");
	al_draw_text(font, green,textWidth*0,textHeight*22,ALLEGRO_ALIGN_LEFT, "0x3259");



	al_draw_text(font, green,textWidth*22,textHeight*6,ALLEGRO_ALIGN_LEFT, "0x1F0A");
	al_draw_text(font, green,textWidth*22,textHeight*7,ALLEGRO_ALIGN_LEFT, "0x6BD1");
	al_draw_text(font, green,textWidth*22,textHeight*8,ALLEGRO_ALIGN_LEFT, "0x6154");
	al_draw_text(font, green,textWidth*22,textHeight*9,ALLEGRO_ALIGN_LEFT, "0x4A03");
	al_draw_text(font, green,textWidth*22,textHeight*10,ALLEGRO_ALIGN_LEFT, "0x3B72");
	al_draw_text(font, green,textWidth*22,textHeight*11,ALLEGRO_ALIGN_LEFT, "0x2988");
	al_draw_text(font, green,textWidth*22,textHeight*12,ALLEGRO_ALIGN_LEFT, "0x1045");
	al_draw_text(font, green,textWidth*22,textHeight*13,ALLEGRO_ALIGN_LEFT, "0x789A");
	al_draw_text(font, green,textWidth*22,textHeight*14,ALLEGRO_ALIGN_LEFT, "0x6437");
	al_draw_text(font, green,textWidth*22,textHeight*15,ALLEGRO_ALIGN_LEFT, "0x8315");
	al_draw_text(font, green,textWidth*22,textHeight*16,ALLEGRO_ALIGN_LEFT, "0x53F4");
	al_draw_text(font, green,textWidth*22,textHeight*17,ALLEGRO_ALIGN_LEFT, "0x4602");
	al_draw_text(font, green,textWidth*22,textHeight*18,ALLEGRO_ALIGN_LEFT, "0x278E");
	al_draw_text(font, green,textWidth*22,textHeight*19,ALLEGRO_ALIGN_LEFT, "0x7A39");
	al_draw_text(font, green,textWidth*22,textHeight*20,ALLEGRO_ALIGN_LEFT, "0x2047");
	al_draw_text(font, green,textWidth*22,textHeight*21,ALLEGRO_ALIGN_LEFT, "0x3851");
	al_draw_text(font, green,textWidth*22,textHeight*22,ALLEGRO_ALIGN_LEFT, "0x367D");

	al_flip_display();
	al_clear_to_color(black);

	// LOOP LOCATION
	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
	al_register_event_source(event_queue,al_get_display_event_source(display));
	al_register_event_source(event_queue,al_get_mouse_event_source());
	
	ALLEGRO_EVENT events;
	bool gameFinished = false;
	subtractTry = false;
	triesLeft = 4;

	while(gameFinished != true)
	{
		
		al_wait_for_event(event_queue, &events);
		// EVENT TO CLOSE
		if(events.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			gameFinished = true;
		}

		else if(events.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if(events.mouse.button & 1)
			// FIRST WORD
			if(mouseCordX >=textWidth*12 && mouseCordX < textWidth*20 && mouseCordY >= textHeight*7 &&  mouseCordY < textHeight*8)
			{
				triesLeft--;
				numCharSame = 1;
				
			}
			// SECOND WORD
			else if(mouseCordX >=textWidth*10 && mouseCordX < textWidth*18 && mouseCordY >= textHeight*9 &&  mouseCordY < textHeight*10)
			{
				triesLeft--;
				numCharSame = 0;
			}			
			// THIRD WORD
			else if(mouseCordX >=textWidth*18 && mouseCordX < textWidth*20 && mouseCordY >= textHeight*10 &&  mouseCordY < textHeight*11 || mouseCordX >=textWidth*8 && mouseCordX < textWidth*14 && mouseCordY >= textHeight*11 &&  mouseCordY < textHeight*12)
			{
				triesLeft--;
				numCharSame =0;
			}
			// FOURTH WORD
			else if(mouseCordX >=textWidth*13 && mouseCordX < textWidth*20 && mouseCordY >= textHeight*14 &&  mouseCordY < textHeight*15 || mouseCordX >=textWidth*8 && mouseCordX < textWidth*9 && mouseCordY >= textHeight*15 &&  mouseCordY < textHeight*16)
			{
				triesLeft--;
				numCharSame = 1;
			}		
			// FIFTH WORD
			else if(mouseCordX >=textWidth*17 && mouseCordX < textWidth*20 && mouseCordY >= textHeight*16 &&  mouseCordY < textHeight*17 || mouseCordX >=textWidth*8 && mouseCordX < textWidth*14 && mouseCordY >= textHeight*17 &&  mouseCordY < textHeight*18)
			{
				triesLeft--;
				numCharSame = 0;
			}
			// SIXTH WORD
			/*else if(mouseCordX >=textWidth*16 && mouseCordX < textWidth*20 && mouseCordY >= textHeight*18 &&  mouseCordY < textHeight*19 || mouseCordX >=textWidth*8 && mouseCordX < textWidth*12 && mouseCordY >= textHeight*19 &&  mouseCordY < textHeight*20)
			{
				
			}		*/
			// SEVENTH WORD
			else if(mouseCordX >=textWidth*13 && mouseCordX < textWidth*20 && mouseCordY >= textHeight*19 &&  mouseCordY < textHeight*20 || mouseCordX >=textWidth*8 && mouseCordX < textWidth*9 && mouseCordY >= textHeight*20 &&  mouseCordY < textHeight*21)
			{
				triesLeft--;
				numCharSame = 1;
			}
			// EIGHTH WORD
			else if(mouseCordX >=textWidth*32 && mouseCordX < textWidth*40 && mouseCordY >= textHeight*7 &&  mouseCordY < textHeight*8)
			{
				gameWon = 1;
				gameFinished = 1;
			}			
			// NINTH WORD
			else if(mouseCordX >=textWidth*37 && mouseCordX < textWidth*42 && mouseCordY >= textHeight*10 &&  mouseCordY < textHeight*11 || mouseCordX >=textWidth*30 && mouseCordX < textWidth*33 && mouseCordY >= textHeight*11 &&  mouseCordY < textHeight*12)
			{
				triesLeft--;
				numCharSame = 1;
			}
			// TENTH WORD
			else if(mouseCordX >=textWidth*36 && mouseCordX < textWidth*42 && mouseCordY >= textHeight*13 &&  mouseCordY < textHeight*14 || mouseCordX >=textWidth*30 && mouseCordX < textWidth*32 && mouseCordY >= textHeight*14 &&  mouseCordY < textHeight*15)
			{
				triesLeft--;
				numCharSame = 0;
			}		
			// ELEVENTH WORD
			else if(mouseCordX >=textWidth*33 && mouseCordX < textWidth*41 && mouseCordY >= textHeight*14 &&  mouseCordY < textHeight*15)
			{
				triesLeft--;
				numCharSame = 0;
			}
			// TWELTH WORD
			/*else if(mouseCordX >=textWidth*31 && mouseCordX < textWidth*39 && mouseCordY >= textHeight*17 &&  mouseCordY < textHeight*18)
			{
				
			}		*/	
			// THIRTEENTH WORD
			else if(mouseCordX >=textWidth*37 && mouseCordX < textWidth*42 && mouseCordY >= textHeight*19 &&  mouseCordY < textHeight*20 || mouseCordX >=textWidth*30 && mouseCordX < textWidth*33 && mouseCordY >= textHeight*20 &&  mouseCordY < textHeight*21)
			{
				triesLeft--;
				numCharSame = 0;
			}
			// FOURTEENTH WORD
			else if(mouseCordX >=textWidth*32 && mouseCordX < textWidth*40 && mouseCordY >= textHeight*22 &&  mouseCordY < textHeight*23)
			{
				triesLeft--;
				numCharSame = 1;
			}		

			// For the character sets
			// ONE
			else if(mouseCordX >=textWidth*10 && mouseCordX < textWidth*19 && mouseCordY >= textHeight*6 &&  mouseCordY < textHeight*7)
			{
				if (chosenHelpers[0] == 0)
				{
					chosenHelpers[0] = 1;
					characters2[4][7] = ".";
					characters2[4][8] = ".";
					characters2[4][9] = ".";
					characters2[4][10] = ".";
					characters2[4][11] = ".";
					characters2[4][12] = ".";
					characters2[4][14] = ".";
					characters2[4][13] = ".";
					characters1[0][2] = ".";
					characters1[0][3] = ".";
					characters1[0][4] = ".";
					characters1[0][5] = ".";
					characters1[0][6] = ".";
					characters1[0][7] = ".";
					characters1[0][8] = ".";
					characters1[0][9] = ".";
					characters1[0][10] = ".";
				}
				else{}
			}
			// TWO
			else if(mouseCordX >=textWidth*9 && mouseCordX < textWidth*16 && mouseCordY >= textHeight*13 &&  mouseCordY < textHeight*14)
			{
				if (chosenHelpers[1] == 0)
				{
					chosenHelpers[1] = 1;
					characters2[13][7] = ".";
					characters2[13][8] = ".";
					characters2[13][9] = ".";
					characters2[13][10] = ".";
					characters2[13][11] = ".";
					characters2[13][12] = ".";
					characters2[13][14] = ".";
					characters2[13][13] = ".";
					characters1[7][1] = ".";
					characters1[7][2] = ".";
					characters1[7][3] = ".";
					characters1[7][4] = ".";
					characters1[7][5] = ".";
					characters1[7][6] = ".";
					characters1[7][7] = ".";
				}
				else
				{}
			}		
			// THREE
			else if(mouseCordX >=textWidth*13 && mouseCordX < textWidth*17 && mouseCordY >= textHeight*15 &&  mouseCordY < textHeight*16)
			{
				if (chosenHelpers[2] == 0)
				{
					chosenHelpers[2] = 1;
					characters1[1][4] = ".";
					characters1[1][5] = ".";
					characters1[1][6] = ".";
					characters1[1][7] = ".";
					characters1[1][8] = ".";
					characters1[1][9] = ".";
					characters1[1][10] = ".";
					characters1[1][11] = ".";
					characters1[9][5] = ".";
					characters1[9][6] = ".";
					characters1[9][7] = ".";
					characters1[9][8] = ".";
				}
				else
				{}
			}		
			// FOUR
			else if(mouseCordX >=textWidth*16 && mouseCordX < textWidth*20 && mouseCordY >= textHeight*17 &&  mouseCordY < textHeight*18 || mouseCordX >=textWidth*8 && mouseCordX < textWidth*11 && mouseCordY >= textHeight*18 &&  mouseCordY < textHeight*19)
			{
				if (chosenHelpers[3] == 0)
				{
					chosenHelpers[3] = 1;
					characters2[16][2] = ".";
					characters2[16][3] = ".";
					characters2[16][4] = ".";
					characters2[16][5] = ".";
					characters2[16][6] = ".";
					characters2[16][7] = ".";
					characters2[16][8] = ".";
					characters2[16][9] = ".";
					characters1[11][2] = ".";
					characters1[11][8] = ".";
					characters1[11][9] = ".";
					characters1[11][10] = ".";
					characters1[11][11] = ".";
					characters1[11][12] = ".";
					characters1[11][13] = ".";
					characters1[11][14] = ".";
				}
				else
				{}
			}	
			// FIVE
			else if(mouseCordX >=textWidth*33 && mouseCordX < textWidth*39 && mouseCordY >= textHeight*8 &&  mouseCordY < textHeight*9)
			{
				if (chosenHelpers[4] == 0)
				{
					chosenHelpers[4] = 1;
					characters1[3][2] = ".";
					characters1[3][3] = ".";
					characters1[3][4] = ".";
					characters1[3][5] = ".";
					characters1[3][6] = ".";
					characters1[3][7] = ".";
					characters1[3][8] = ".";
					characters1[3][9] = ".";
					characters2[2][3] = ".";
					characters2[2][4] = ".";
					characters2[2][5] = ".";
					characters2[2][6] = ".";
					characters2[2][7] = ".";
					characters2[2][8] = ".";
				}
				else
				{}
					
			}	
			// SIX
			else if(mouseCordX >=textWidth*37 && mouseCordX < textWidth*42 && mouseCordY >= textHeight*15 &&  mouseCordY < textHeight*16 || mouseCordX >=textWidth*30 && mouseCordX < textWidth*33 && mouseCordY >= textHeight*16 &&  mouseCordY < textHeight*17)
			{
				if (chosenHelpers[5] == 0)
				{
					chosenHelpers[5] = 1;
					characters1[4][10] = ".";
					characters1[4][11] = ".";
					characters1[4][12] = ".";
					characters1[4][13] = ".";
					characters1[4][14] = ".";
					characters1[4][15] = ".";
					characters1[4][16] = ".";
					characters1[4][17] = ".";
					characters2[9][7] = ".";
					characters2[9][8] = ".";
					characters2[9][9] = ".";
					characters2[9][10] = ".";
					characters2[9][11] = ".";
					characters2[9][12] = ".";
					characters2[9][13] = ".";
					characters2[9][14] = ".";
				}
				else
				{}
			}	
			// SEVEN
			else if(mouseCordX >=textWidth*41 && mouseCordX < textWidth*42 && mouseCordY >= textHeight*18 &&  mouseCordY < textHeight*19 || mouseCordX >=textWidth*30 && mouseCordX < textWidth*34 && mouseCordY >= textHeight*19 &&  mouseCordY < textHeight*20)
			{
				if (chosenHelpers[6] == 0)
				{
					chosenHelpers[6] = 1;
					characters2[8][3] = ".";
					characters2[8][4] = ".";
					characters2[8][5] = ".";
					characters2[8][6] = ".";
					characters2[8][7] = ".";
					characters2[8][8] = ".";
					characters2[8][9] = ".";
					characters2[8][10] = ".";
					characters2[12][11] = ".";
					characters2[12][12] = ".";
					characters2[12][13] = ".";
					characters2[12][14] = ".";
					characters2[12][15] = ".";
				}
				else
				{}
			}	

			if(triesLeft ==0)
			{
				gameFinished = 1;
			}
		}


		// EVENT TO UPDATE WHERE MOUSE IS
		else if(events.type == ALLEGRO_EVENT_MOUSE_AXES)
		{
			mouseCordX = events.mouse.x;
			mouseCordY = events.mouse.y;
			if (subtractTry==true)
			{
				triesLeft--;
				subtractTry = false;
			}
			
			if(triesLeft==3)
			{
				al_draw_text(font, green, textWidth*20, textHeight*4, ALLEGRO_ALIGN_LEFT,"[] [] []   ");
			}
			else if(triesLeft==4)
			{
				al_draw_text(font, green, textWidth*20, textHeight*4, ALLEGRO_ALIGN_LEFT,"[] [] [] []");
			}
			else if(triesLeft==2)
			{
				al_draw_text(font, green, textWidth*20, textHeight*4, ALLEGRO_ALIGN_LEFT,"[] []      ");
			}
			else if(triesLeft==1)
			{
				al_draw_text(font, green, textWidth*20, textHeight*4, ALLEGRO_ALIGN_LEFT,"[]         ");
			}
				
	
			// LOGIC FOR WHERE MOUSE IS


			// Drawing each character for set 1
			ycoord = 6*textHeight;
			xcoord = 8*textWidth;
			int i,j;
			const char *k;
			for (i=0;i<=16;i++)
			{
				for(j=0;j<=11;j++)
				{
					k=characters1[i][j].c_str();

					
					if(mouseCordX >= xcoord+textWidth*j && mouseCordX < xcoord+textWidth*(j+1) && mouseCordY >= ycoord+textHeight*i && mouseCordY < ycoord+textHeight*(i+1))
					{
						al_draw_filled_rectangle(xcoord + textWidth*j, ycoord + textHeight*i+4, xcoord+textWidth*(j+1), ycoord + textHeight*(i+1)+4,green);
						al_draw_text(font, black, xcoord + textWidth*j, ycoord + textHeight*i, ALLEGRO_ALIGN_LEFT,k);
						
					}
					else
					{
						al_draw_text(font, green, xcoord + textWidth*j, ycoord + textHeight*i, ALLEGRO_ALIGN_LEFT,k);
					}
				}
			}

			// Drawing each character for set 2
			ycoord = 6*textHeight;
			xcoord = 30*textWidth;

			int m,o;
			for (m=0;m<=16;m++)
			{
				for(o=0;o<=11;o++)
				{
					k=characters2[m][o].c_str();

					
					if(mouseCordX >= xcoord+textWidth*o && mouseCordX < xcoord+textWidth*(o+1) && mouseCordY >= ycoord+textHeight*m && mouseCordY < ycoord+textHeight*(m+1))
					{
						al_draw_filled_rectangle(xcoord + textWidth*o, ycoord + textHeight*m+4, xcoord+textWidth*(o+1), ycoord + textHeight*(m+1)+4,green);
						al_draw_text(font, black, xcoord + textWidth*o, ycoord + textHeight*m, ALLEGRO_ALIGN_LEFT,k);
						
					}
					else
					{
						al_draw_text(font, green, xcoord + textWidth*o, ycoord + textHeight*m, ALLEGRO_ALIGN_LEFT,k);
					}
				}
			}


			// FIRST WORD
			if(mouseCordX >=textWidth*12 && mouseCordX < textWidth*20 && mouseCordY >= textHeight*7 &&  mouseCordY < textHeight*8)
			{
				if(chosenHelpers[2]==0)
				{
					al_draw_text(font, blue,textWidth*12, textHeight*7, ALLEGRO_ALIGN_LEFT, "PICKAXES");
					al_draw_text(font, blue,textWidth*44, textHeight*22, ALLEGRO_ALIGN_LEFT, "PICKAXES");
				}
				else
				{
					al_draw_text(font, blue,textWidth*12, textHeight*7, ALLEGRO_ALIGN_LEFT, "........");
				}
			}
			// SECOND WORD
			else if(mouseCordX >=textWidth*10 && mouseCordX < textWidth*18 && mouseCordY >= textHeight*9 &&  mouseCordY < textHeight*10)
			{
				if(chosenHelpers[4]==0)
				{
					al_draw_text(font, blue,textWidth*10, textHeight*9, ALLEGRO_ALIGN_LEFT, "ALLIANCE");
					al_draw_text(font, blue,textWidth*44, textHeight*22, ALLEGRO_ALIGN_LEFT, "ALLIANCE");
				}
				else
				{
					al_draw_text(font, blue,textWidth*10, textHeight*9, ALLEGRO_ALIGN_LEFT, "........");
				}
			}			
			// THIRD WORD
			else if(mouseCordX >=textWidth*18 && mouseCordX < textWidth*20 && mouseCordY >= textHeight*10 &&  mouseCordY < textHeight*11 || mouseCordX >=textWidth*8 && mouseCordX < textWidth*14 && mouseCordY >= textHeight*11 &&  mouseCordY < textHeight*12)
			{
				if(chosenHelpers[5] == 0)
				{
					al_draw_text(font, blue,textWidth*18, textHeight*10, ALLEGRO_ALIGN_LEFT, "WI");
					al_draw_text(font, blue,textWidth*8, textHeight*11, ALLEGRO_ALIGN_LEFT, "LDCARD");
					al_draw_text(font, blue,textWidth*44, textHeight*22, ALLEGRO_ALIGN_LEFT, "WILDCARD");
				}
				else
				{
					al_draw_text(font, blue,textWidth*18, textHeight*10, ALLEGRO_ALIGN_LEFT, "..");
					al_draw_text(font, blue,textWidth*8, textHeight*11, ALLEGRO_ALIGN_LEFT, "......");
				}
			}
			// FOURTH WORD
			else if(mouseCordX >=textWidth*13 && mouseCordX < textWidth*20 && mouseCordY >= textHeight*14 &&  mouseCordY < textHeight*15 || mouseCordX >=textWidth*8 && mouseCordX < textWidth*9 && mouseCordY >= textHeight*15 &&  mouseCordY < textHeight*16)
			{
				if(chosenHelpers[8] == 0)
				{
					al_draw_text(font, blue,textWidth*13, textHeight*14, ALLEGRO_ALIGN_LEFT, "GUNFIGH");
					al_draw_text(font, blue,textWidth*8, textHeight*15, ALLEGRO_ALIGN_LEFT, "T");
					al_draw_text(font, blue,textWidth*44, textHeight*22, ALLEGRO_ALIGN_LEFT, "GUNFIGHT");
				}
				else
				{
					al_draw_text(font, blue,textWidth*13, textHeight*14, ALLEGRO_ALIGN_LEFT, ".......");
					al_draw_text(font, blue,textWidth*8, textHeight*15, ALLEGRO_ALIGN_LEFT, ".");
				}
			}
			// FIFTH WORD
			else if(mouseCordX >=textWidth*17 && mouseCordX < textWidth*20 && mouseCordY >= textHeight*16 &&  mouseCordY < textHeight*17 || mouseCordX >=textWidth*8 && mouseCordX < textWidth*14 && mouseCordY >= textHeight*17 &&  mouseCordY < textHeight*18)
			{
				if(chosenHelpers[8] == 0)
				{
					al_draw_text(font, blue,textWidth*17, textHeight*16, ALLEGRO_ALIGN_LEFT, "REC");
					al_draw_text(font, blue,textWidth*8, textHeight*17, ALLEGRO_ALIGN_LEFT, "ORDING");
					al_draw_text(font, blue,textWidth*44, textHeight*22, ALLEGRO_ALIGN_LEFT, "RECORDING");
				}
				else
				{
					al_draw_text(font, blue,textWidth*17, textHeight*16, ALLEGRO_ALIGN_LEFT, "...");
					al_draw_text(font, blue,textWidth*8, textHeight*17, ALLEGRO_ALIGN_LEFT, "......");
				}
			}
			// SIXTH WORD
			/*else if(mouseCordX >=textWidth*16 && mouseCordX < textWidth*20 && mouseCordY >= textHeight*18 &&  mouseCordY < textHeight*19 || mouseCordX >=textWidth*8 && mouseCordX < textWidth*12 && mouseCordY >= textHeight*19 &&  mouseCordY < textHeight*20)
			{
				if(chosenHelpers[8] ==0)
				{
					al_draw_text(font, blue,textWidth*16, textHeight*18, ALLEGRO_ALIGN_LEFT, "HEAD");
					al_draw_text(font, blue,textWidth*8, textHeight*19, ALLEGRO_ALIGN_LEFT, "SHOT");
					al_draw_text(font, blue,textWidth*44, textHeight*22, ALLEGRO_ALIGN_LEFT, "HEADSHOT");
				}
				else
				{
					al_draw_text(font, blue,textWidth*16, textHeight*18, ALLEGRO_ALIGN_LEFT, "....");
					al_draw_text(font, blue,textWidth*8, textHeight*19, ALLEGRO_ALIGN_LEFT, "....");
				}
			}*/		
			// SEVENTH WORD
			else if(mouseCordX >=textWidth*13 && mouseCordX < textWidth*20 && mouseCordY >= textHeight*19 &&  mouseCordY < textHeight*20 || mouseCordX >=textWidth*8 && mouseCordX < textWidth*9 && mouseCordY >= textHeight*20 &&  mouseCordY < textHeight*21)
			{
				if(chosenHelpers[8] == 0)
				{
					al_draw_text(font, blue,textWidth*13, textHeight*19, ALLEGRO_ALIGN_LEFT, "WARCRAF");
					al_draw_text(font, blue,textWidth*8, textHeight*20, ALLEGRO_ALIGN_LEFT, "T");
					al_draw_text(font, blue,textWidth*44, textHeight*22, ALLEGRO_ALIGN_LEFT, "WARCRAFT");
				}
				else
				{
					al_draw_text(font, blue,textWidth*13, textHeight*19, ALLEGRO_ALIGN_LEFT, ".......");
					al_draw_text(font, blue,textWidth*8, textHeight*20, ALLEGRO_ALIGN_LEFT, ".");
				}
			}
			// EIGHTH WORD
			else if(mouseCordX >=textWidth*32 && mouseCordX < textWidth*40 && mouseCordY >= textHeight*7 &&  mouseCordY < textHeight*8)
			{
				if(1==1)
				{
					al_draw_text(font, blue,textWidth*32, textHeight*7, ALLEGRO_ALIGN_LEFT, "PANGOLIN");
					al_draw_text(font, blue,textWidth*44, textHeight*22, ALLEGRO_ALIGN_LEFT, "PANGOLIN");
				}
				else
				{
					al_draw_text(font, blue,textWidth*32, textHeight*7, ALLEGRO_ALIGN_LEFT, "........");
				}
			}
			// NINTH WORD
			else if(mouseCordX >=textWidth*37 && mouseCordX < textWidth*42 && mouseCordY >= textHeight*10 &&  mouseCordY < textHeight*11 || mouseCordX >=textWidth*30 && mouseCordX < textWidth*33 && mouseCordY >= textHeight*11 &&  mouseCordY < textHeight*12)
			{
				if(chosenHelpers[0] == 0)
				{
					al_draw_text(font, blue,textWidth*37, textHeight*10, ALLEGRO_ALIGN_LEFT, "ELECT");
					al_draw_text(font, blue,textWidth*30, textHeight*11, ALLEGRO_ALIGN_LEFT, "RON");
					al_draw_text(font, blue,textWidth*44, textHeight*22, ALLEGRO_ALIGN_LEFT, "ELECTRON");
				}
				else
				{
					al_draw_text(font, blue,textWidth*37, textHeight*10, ALLEGRO_ALIGN_LEFT, ".....");
					al_draw_text(font, blue,textWidth*30, textHeight*11, ALLEGRO_ALIGN_LEFT, "...");
				}
			}
			// TENTH WORD
			else if(mouseCordX >=textWidth*36 && mouseCordX < textWidth*42 && mouseCordY >= textHeight*13 &&  mouseCordY < textHeight*14 || mouseCordX >=textWidth*30 && mouseCordX < textWidth*32 && mouseCordY >= textHeight*14 &&  mouseCordY < textHeight*15)
			{
				if(chosenHelpers[8] == 0)
				{
					al_draw_text(font, blue,textWidth*36, textHeight*13, ALLEGRO_ALIGN_LEFT, "ABRASI");
					al_draw_text(font, blue,textWidth*30, textHeight*14, ALLEGRO_ALIGN_LEFT, "VE");
					al_draw_text(font, blue,textWidth*44, textHeight*22, ALLEGRO_ALIGN_LEFT, "ABRASIVE");
				}
				else
				{
					al_draw_text(font, blue,textWidth*36, textHeight*13, ALLEGRO_ALIGN_LEFT, "......");
					al_draw_text(font, blue,textWidth*30, textHeight*14, ALLEGRO_ALIGN_LEFT, "..");
				}
			}		
			// ELEVENTH WORD
			else if(mouseCordX >=textWidth*33 && mouseCordX < textWidth*41 && mouseCordY >= textHeight*14 &&  mouseCordY < textHeight*15)
			{
				if(chosenHelpers[6] == 0)
				{
					al_draw_text(font, blue,textWidth*33, textHeight*14, ALLEGRO_ALIGN_LEFT, "SEASHELL");
					al_draw_text(font, blue,textWidth*44, textHeight*22, ALLEGRO_ALIGN_LEFT, "SEASHELL");
				}
				else
				{
					al_draw_text(font, blue,textWidth*33, textHeight*14, ALLEGRO_ALIGN_LEFT, "........");
				}
			}
			// TWELTH WORD
			/*else if(mouseCordX >=textWidth*31 && mouseCordX < textWidth*39 && mouseCordY >= textHeight*17 &&  mouseCordY < textHeight*18)
			{
				if(chosenHelpers[11] == 0)
				{
					al_draw_text(font, blue,textWidth*31, textHeight*17, ALLEGRO_ALIGN_LEFT, "CHIPPING");
					al_draw_text(font, blue,textWidth*44, textHeight*22, ALLEGRO_ALIGN_LEFT, "CHIPPING");
				}
				else
				{
					al_draw_text(font, blue,textWidth*31, textHeight*17, ALLEGRO_ALIGN_LEFT, "........");
				}
			}*/			
			// THIRTEENTH WORD
			else if(mouseCordX >=textWidth*37 && mouseCordX < textWidth*42 && mouseCordY >= textHeight*19 &&  mouseCordY < textHeight*20 || mouseCordX >=textWidth*30 && mouseCordX < textWidth*33 && mouseCordY >= textHeight*20 &&  mouseCordY < textHeight*21)
			{
				if(chosenHelpers[1]==0)
				{
					al_draw_text(font, blue,textWidth*37, textHeight*19, ALLEGRO_ALIGN_LEFT, "DISPA");
					al_draw_text(font, blue,textWidth*30, textHeight*20, ALLEGRO_ALIGN_LEFT, "TCH");
					al_draw_text(font, blue,textWidth*44, textHeight*22, ALLEGRO_ALIGN_LEFT, "DISPATCH");
				}
				else
				{
					al_draw_text(font, blue,textWidth*37, textHeight*19, ALLEGRO_ALIGN_LEFT, ".....");
					al_draw_text(font, blue,textWidth*30, textHeight*20, ALLEGRO_ALIGN_LEFT, "...");
				}
			}
			// FOURTEENTH WORD
			else if(mouseCordX >=textWidth*32 && mouseCordX < textWidth*40 && mouseCordY >= textHeight*22 &&  mouseCordY < textHeight*23)
			{
				if(chosenHelpers[3]==0)
				{
					al_draw_text(font, blue,textWidth*32, textHeight*22, ALLEGRO_ALIGN_LEFT, "MUSICIAN");
					al_draw_text(font, blue,textWidth*44, textHeight*22, ALLEGRO_ALIGN_LEFT, "MUSICIAN");
				}
				else
				{
					al_draw_text(font, blue,textWidth*32, textHeight*22, ALLEGRO_ALIGN_LEFT, "........");
				}
			}		

			// For the character sets
			else if(mouseCordX >=textWidth*10 && mouseCordX < textWidth*11 && mouseCordY >= textHeight*6 &&  mouseCordY < textHeight*7)
			{
				if (chosenHelpers[0] == 0)
					al_draw_text(font, blue,textWidth*10, textHeight*6, ALLEGRO_ALIGN_LEFT, "(*/!#^&$)");
				else
					al_draw_text(font, blue,textWidth*10, textHeight*6, ALLEGRO_ALIGN_LEFT, ".........");
			}
			
			else if(mouseCordX >=textWidth*9 && mouseCordX < textWidth*10 && mouseCordY >= textHeight*13 &&  mouseCordY < textHeight*14)
			{
				if (chosenHelpers[1] == 0)
					al_draw_text(font, blue,textWidth*9, textHeight*13, ALLEGRO_ALIGN_LEFT, "[%#@&!]");
				else
					al_draw_text(font, blue,textWidth*9, textHeight*13, ALLEGRO_ALIGN_LEFT, ".......");
			}		
			
			else if(mouseCordX >=textWidth*13 && mouseCordX < textWidth*14 && mouseCordY >= textHeight*15 &&  mouseCordY < textHeight*16)
			{
				if (chosenHelpers[2] == 0)
					al_draw_text(font, blue,textWidth*13, textHeight*15, ALLEGRO_ALIGN_LEFT, "<*&>");
				else
					al_draw_text(font, blue,textWidth*13, textHeight*15, ALLEGRO_ALIGN_LEFT, "....");
			}		

			else if(mouseCordX >=textWidth*16 && mouseCordX < textWidth*17 && mouseCordY >= textHeight*17 &&  mouseCordY < textHeight*18)
			{
				if (chosenHelpers[3] == 0){
					al_draw_text(font, blue,textWidth*16, textHeight*17, ALLEGRO_ALIGN_LEFT, "<^:^");
					al_draw_text(font, blue,textWidth*8, textHeight*18, ALLEGRO_ALIGN_LEFT, "$?>");}
				else{
					al_draw_text(font, blue,textWidth*16, textHeight*17, ALLEGRO_ALIGN_LEFT, "....");
					al_draw_text(font, blue,textWidth*8, textHeight*18, ALLEGRO_ALIGN_LEFT, "...");}
			}	

			else if(mouseCordX >=textWidth*33 && mouseCordX < textWidth*34 && mouseCordY >= textHeight*8 &&  mouseCordY < textHeight*9)
			{
				if (chosenHelpers[4] == 0)
					al_draw_text(font, blue,textWidth*33, textHeight*8, ALLEGRO_ALIGN_LEFT, "[^*@$]");
				else
					al_draw_text(font, blue,textWidth*33, textHeight*8, ALLEGRO_ALIGN_LEFT, "......");
			}	

			else if(mouseCordX >=textWidth*37 && mouseCordX < textWidth*38 && mouseCordY >= textHeight*15 &&  mouseCordY < textHeight*16)
			{
				if (chosenHelpers[5] == 0){
					al_draw_text(font, blue,textWidth*37, textHeight*15, ALLEGRO_ALIGN_LEFT, "<*#;~");
					al_draw_text(font, blue,textWidth*30, textHeight*16, ALLEGRO_ALIGN_LEFT, "+*>");}
				else{
					al_draw_text(font, blue,textWidth*37, textHeight*15, ALLEGRO_ALIGN_LEFT, ".....");
					al_draw_text(font, blue,textWidth*30, textHeight*16, ALLEGRO_ALIGN_LEFT, "...");}
			}	
			
			else if(mouseCordX >=textWidth*41 && mouseCordX < textWidth*42 && mouseCordY >= textHeight*18 &&  mouseCordY < textHeight*19)
			{
				if (chosenHelpers[6] == 0){
					al_draw_text(font, blue,textWidth*41, textHeight*18, ALLEGRO_ALIGN_LEFT, "{");
					al_draw_text(font, blue,textWidth*30, textHeight*19, ALLEGRO_ALIGN_LEFT, "&@%}");}
				else{
					al_draw_text(font, blue,textWidth*41, textHeight*18, ALLEGRO_ALIGN_LEFT, ".");
					al_draw_text(font, blue,textWidth*30, textHeight*19, ALLEGRO_ALIGN_LEFT, "....");}
			}	


			// Printing Header
			
			al_draw_text(font, green, 0, textHeight*1, ALLEGRO_ALIGN_LEFT,"ROBCO INDUSTRIES (TM) TERMLINK PROTOCOL");
			al_draw_text(font, green, 0, textHeight*2, ALLEGRO_ALIGN_LEFT,"ENTER PASSWORD NOW");
			al_draw_text(font, green, textWidth*1, textHeight*4, ALLEGRO_ALIGN_LEFT," ATTEMPT(S) LEFT:");
			string s = to_string(triesLeft);
			const char *a = s.c_str();
			al_draw_text(font, green, 0, textHeight*4, ALLEGRO_ALIGN_LEFT,a);
	
	

			// Printing Hex Values
			al_draw_text(font, green, textWidth*0,textHeight*6, ALLEGRO_ALIGN_LEFT, "0x87FA");
			al_draw_text(font, green,textWidth*0,textHeight*7,ALLEGRO_ALIGN_LEFT, "0x39E7");
			al_draw_text(font, green,textWidth*0,textHeight*8,ALLEGRO_ALIGN_LEFT, "0x7A78");
			al_draw_text(font, green,textWidth*0,textHeight*9,ALLEGRO_ALIGN_LEFT, "0x721B");
			al_draw_text(font, green,textWidth*0,textHeight*10,ALLEGRO_ALIGN_LEFT, "0x45EB");
			al_draw_text(font, green,textWidth*0,textHeight*11,ALLEGRO_ALIGN_LEFT, "0x4E73");
			al_draw_text(font, green,textWidth*0,textHeight*12,ALLEGRO_ALIGN_LEFT, "0x6D61");
			al_draw_text(font, green,textWidth*0,textHeight*13,ALLEGRO_ALIGN_LEFT, "0x31DF");
			al_draw_text(font, green,textWidth*0,textHeight*14,ALLEGRO_ALIGN_LEFT, "0x5CC2");
			al_draw_text(font, green,textWidth*0,textHeight*15,ALLEGRO_ALIGN_LEFT, "0x4FE2");
			al_draw_text(font, green,textWidth*0,textHeight*16,ALLEGRO_ALIGN_LEFT, "0x52F5");
			al_draw_text(font, green,textWidth*0,textHeight*17,ALLEGRO_ALIGN_LEFT, "0x64E8");
			al_draw_text(font, green,textWidth*0,textHeight*18,ALLEGRO_ALIGN_LEFT, "0x7D94");
			al_draw_text(font, green,textWidth*0,textHeight*19,ALLEGRO_ALIGN_LEFT, "0x2879");
			al_draw_text(font, green,textWidth*0,textHeight*20,ALLEGRO_ALIGN_LEFT, "0x26F0");
			al_draw_text(font, green,textWidth*0,textHeight*21,ALLEGRO_ALIGN_LEFT, "0x7BE5");
			al_draw_text(font, green,textWidth*0,textHeight*22,ALLEGRO_ALIGN_LEFT, "0x3259");
	
	
	
			al_draw_text(font, green,textWidth*22,textHeight*6,ALLEGRO_ALIGN_LEFT, "0x1F0A");
			al_draw_text(font, green,textWidth*22,textHeight*7,ALLEGRO_ALIGN_LEFT, "0x6BD1");
			al_draw_text(font, green,textWidth*22,textHeight*8,ALLEGRO_ALIGN_LEFT, "0x6154");
			al_draw_text(font, green,textWidth*22,textHeight*9,ALLEGRO_ALIGN_LEFT, "0x4A03");
			al_draw_text(font, green,textWidth*22,textHeight*10,ALLEGRO_ALIGN_LEFT, "0x3B72");
			al_draw_text(font, green,textWidth*22,textHeight*11,ALLEGRO_ALIGN_LEFT, "0x2988");
			al_draw_text(font, green,textWidth*22,textHeight*12,ALLEGRO_ALIGN_LEFT, "0x1045");
			al_draw_text(font, green,textWidth*22,textHeight*13,ALLEGRO_ALIGN_LEFT, "0x789A");
			al_draw_text(font, green,textWidth*22,textHeight*14,ALLEGRO_ALIGN_LEFT, "0x6437");
			al_draw_text(font, green,textWidth*22,textHeight*15,ALLEGRO_ALIGN_LEFT, "0x8315");
			al_draw_text(font, green,textWidth*22,textHeight*16,ALLEGRO_ALIGN_LEFT, "0x53F4");
			al_draw_text(font, green,textWidth*22,textHeight*17,ALLEGRO_ALIGN_LEFT, "0x4602");
			al_draw_text(font, green,textWidth*22,textHeight*18,ALLEGRO_ALIGN_LEFT, "0x278E");
			al_draw_text(font, green,textWidth*22,textHeight*19,ALLEGRO_ALIGN_LEFT, "0x7A39");
			al_draw_text(font, green,textWidth*22,textHeight*20,ALLEGRO_ALIGN_LEFT, "0x2047");
			al_draw_text(font, green,textWidth*22,textHeight*21,ALLEGRO_ALIGN_LEFT, "0x3851");
			al_draw_text(font, green,textWidth*22,textHeight*22,ALLEGRO_ALIGN_LEFT, "0x367D");

			al_draw_text(font, green,textWidth*43,textHeight*22,ALLEGRO_ALIGN_LEFT, ">");
			al_draw_text(font, green,textWidth*43,textHeight*20,ALLEGRO_ALIGN_LEFT, "Number of matching characters:");
			string l = to_string(numCharSame);
			const char *b = l.c_str();
			al_draw_text(font, green,textWidth*73,textHeight*20,ALLEGRO_ALIGN_LEFT, b);

	
			al_flip_display();
			al_clear_to_color(black);
			}
		}





	if(gameWon == 1)
	{
		al_clear_to_color(black);
		al_draw_text(font, al_map_rgb(255,0,255),350,180,ALLEGRO_ALIGN_CENTER,"YOU WIN!");
	}
	else
	{
		al_clear_to_color(black);
		al_draw_text(font, al_map_rgb(255,0,255),350,180,ALLEGRO_ALIGN_CENTER,"YOU LOSE!");
	}
	//// END LOCATION
	al_flip_display();
	al_rest(5.0);
	al_destroy_font(font);
	al_destroy_display(display);



}

void endGame()
{

}