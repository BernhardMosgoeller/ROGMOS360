#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#include "gamepad.h"


//defines for global Booleans
#define BUTTON_X_define_mos 0
#define BUTTON_Y_define_mos 1
#define BUTTON_A_define_mos 2
#define BUTTON_B_define_mos 3
#define BUTTON_RB_define_mos 4
#define BUTTON_LB_define_mos 5
#define BUTTON_START_define_mos 6
#define BUTTON_BACK_define_mos 7
#define BUTTON_RIGHT_STICK_define_mos 8
#define BUTTON_LEFT_STICK_define_mos 9

// #define NUMBER_GAMEPAD_BUT 10 //old solution for for-loop
enum gamepad_all_items {BUT_X, BUT_Y, BUT_A, BUT_B, BUT_RB, BUT_LB, BUT_START, BUT_BACK, BUT_RIGHT_STICK, BUT_LEFT_STICK, UNKNOWN };

//global booleans
bool g_mos[10];

struct gamepad_items
{
	char *name;
	enum gamepad_all_items id;
} gamepad_but_list[] = {
	{"rb",BUT_RB},
	{"lb",BUT_LB},
	{"start",BUT_START},
	{"back",BUT_BACK},
	{"left_stick",BUT_LEFT_STICK},
	{"right_stick",BUT_RIGHT_STICK},
	{"a",BUT_A},
	{"b",BUT_B},
	{"x",BUT_X},
	{"y",BUT_Y}
};

void get_button_mos(GAMEPAD_DEVICE dev,char const button_wanted[11]); //longest button name is left_stick
void g_mos_reset();

void get_button_mos(GAMEPAD_DEVICE dev,char const button_wanted[6])
{
	static bool new_bool,old_bool=FALSE,first_run=TRUE;
	static char old_button[6];
	int chosen_but;

	GamepadUpdate();
	if(first_run==TRUE)
	{
		strcpy(old_button, button_wanted);
		first_run=FALSE;
	}
	move(dev, 0);
	//need to save ult button so new and old bool function can work

	unsigned long int i;
	enum gamepad_all_items my_gamepad_items;
	struct gamepad_items *choice = NULL;
	//puts("hallo");
	//for(i=0, choice=NULL;i<NUMBER_GAMEPAD_BUT;i++) // alte Define-Lösung
	for(i=0, choice=NULL;i< sizeof gamepad_but_list/sizeof (struct gamepad_items);i++)
	{
		//puts("hallo");
		if (strcmp(button_wanted, gamepad_but_list[i].name) == 0)
		{
			choice = gamepad_but_list + i;
			break;
		}
	}

	my_gamepad_items = choice ? choice ->id : UNKNOWN;

	switch(my_gamepad_items)	//da muasd nu alles ausfüllen
	{
		case BUT_RB:
			new_bool=GamepadButtonDown(dev, BUTTON_RIGHT_SHOULDER);
			chosen_but=BUTTON_RB_define_mos;
			break;
		case BUT_LB:
			new_bool=GamepadButtonDown(dev, BUTTON_LEFT_SHOULDER);
			chosen_but=BUTTON_LB_define_mos;
			break;
		case BUT_START:
			new_bool=GamepadButtonDown(dev, BUTTON_START);
			chosen_but=BUTTON_START_define_mos;
			break;
		case BUT_BACK:
			new_bool=GamepadButtonDown(dev, BUTTON_BACK);
			chosen_but=BUTTON_BACK_define_mos;
			break;
		case BUT_A:
			new_bool=GamepadButtonDown(dev, BUTTON_A);
			chosen_but=BUTTON_A_define_mos;
			break;
		case BUT_B:
			new_bool=GamepadButtonDown(dev, BUTTON_B);
			chosen_but=BUTTON_B_define_mos;
			break;
		case BUT_Y:
			new_bool=GamepadButtonDown(dev, BUTTON_Y);
			chosen_but=BUTTON_Y_define_mos;
			break;
		case BUT_X:
			new_bool=GamepadButtonDown(dev, BUTTON_X);
			chosen_but=BUTTON_X_define_mos;
			break;
		case BUT_LEFT_STICK:
			new_bool=GamepadButtonDown(dev, BUTTON_LEFT_THUMB);
			chosen_but=BUTTON_LEFT_STICK_define_mos;
			break;
		case BUT_RIGHT_STICK:
			new_bool=GamepadButtonDown(dev, BUTTON_RIGHT_THUMB);
			chosen_but=BUTTON_RIGHT_STICK_define_mos;
			break;
		default:
			puts("Die Russen kommen");
			break;
	}

	if(strcmp(old_button,button_wanted)==0)	//old_bool is right
	{
		puts("gleich");
		//old_bool=FALSE;
		printf("\nold:%d\nnew%d\n",old_bool,new_bool);
		if(old_bool==TRUE&&new_bool==TRUE)
		{
			g_mos[chosen_but]=FALSE;		
		}
		else if(old_bool==FALSE&&new_bool==TRUE)
		{
			g_mos[chosen_but]=TRUE;
		}
		else
		{
			g_mos[chosen_but]=FALSE;
		}
	}
	else	//old bool is wrong
	{
		g_mos[chosen_but]=new_bool;
	}


	old_bool=new_bool;
	strcpy(old_button, button_wanted);
}

void g_mos_reset(){
	int i;
	for(i=0;i<10;i++)
		g_mos[i]=FALSE;
}

