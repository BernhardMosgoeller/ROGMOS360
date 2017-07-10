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
void update_all_but(GAMEPAD_DEVICE dev);
void test_all_but_mos(GAMEPAD_DEVICE GAMEPAD_0);
void g_mos_reset();
void init_gamepad_rogmos();


void get_button_mos(GAMEPAD_DEVICE dev,char const button_wanted[6])
{
	static bool new_bool,old_bool[10],first_run=TRUE;
	//static char old_button[6];
	int chosen_but;
	unsigned long int i;

	GamepadUpdate();
	if(first_run==TRUE)
	{
		//strcpy(old_button, button_wanted);
		first_run=FALSE;
		for(i=0;i<10;i++)
		{
			old_bool[i]=FALSE;
		}
	}
	move(dev, 0);
	//need to save ult button so new and old bool function can work


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


//	printf("\nold:%d\nnew%d\n",old_bool,new_bool);
	if(old_bool[chosen_but]==TRUE&&new_bool==TRUE)
	{
		g_mos[chosen_but]=FALSE;		
	}
	else if(old_bool[chosen_but]==FALSE&&new_bool==TRUE)
	{
		g_mos[chosen_but]=TRUE;
	}
	else
	{
		g_mos[chosen_but]=FALSE;
	}


	old_bool[chosen_but]=new_bool;
}

void update_all_but(GAMEPAD_DEVICE dev)
{
	static bool new_bool,old_bool[10],first_run=TRUE;
	//static char old_button[6];
	int chosen_but,i;

	GamepadUpdate();
	if(first_run==TRUE)
	{
		//strcpy(old_button, button_wanted);
		first_run=FALSE;
		for(i=0;i<sizeof gamepad_but_list/sizeof (struct gamepad_items);i++)
		{
			old_bool[i]=FALSE;
		}
	}
	move(dev, 0);
		for(i=0;i<sizeof gamepad_but_list/sizeof (struct gamepad_items);i++)
		{
			switch(i)	//da muasd nu alles ausfüllen
			{
				case BUTTON_RB_define_mos:
					new_bool=GamepadButtonDown(dev, BUTTON_RIGHT_SHOULDER);
					chosen_but=BUTTON_RB_define_mos;
					break;
				case BUTTON_LB_define_mos:
					new_bool=GamepadButtonDown(dev, BUTTON_LEFT_SHOULDER);
					chosen_but=BUTTON_LB_define_mos;
					break;
				case BUTTON_START_define_mos:
					new_bool=GamepadButtonDown(dev, BUTTON_START);
					chosen_but=BUTTON_START_define_mos;
					break;
				case BUTTON_BACK_define_mos:
					new_bool=GamepadButtonDown(dev, BUTTON_BACK);
					chosen_but=BUTTON_BACK_define_mos;
					break;
				case BUTTON_A_define_mos:
					new_bool=GamepadButtonDown(dev, BUTTON_A);
					chosen_but=BUTTON_A_define_mos;
					break;
				case BUTTON_B_define_mos:
					new_bool=GamepadButtonDown(dev, BUTTON_B);
					chosen_but=BUTTON_B_define_mos;
					break;
				case BUTTON_Y_define_mos:
					new_bool=GamepadButtonDown(dev, BUTTON_Y);
					chosen_but=BUTTON_Y_define_mos;
					break;
				case BUTTON_X_define_mos:
					new_bool=GamepadButtonDown(dev, BUTTON_X);
					chosen_but=BUTTON_X_define_mos;
					break;
				case BUTTON_LEFT_STICK_define_mos:
					new_bool=GamepadButtonDown(dev, BUTTON_LEFT_THUMB);
					chosen_but=BUTTON_LEFT_STICK_define_mos;
					break;
				case BUTTON_RIGHT_STICK_define_mos:
					new_bool=GamepadButtonDown(dev, BUTTON_RIGHT_THUMB);
					chosen_but=BUTTON_RIGHT_STICK_define_mos;
					break;
				default:
					puts("Die Russen kommen");
					break;
			}

			if(old_bool[chosen_but]==TRUE&&new_bool==TRUE)
			{
				g_mos[chosen_but]=FALSE;		
			}
			else if(old_bool[chosen_but]==FALSE&&new_bool==TRUE)
			{
				g_mos[chosen_but]=TRUE;
			}
			else
			{
				g_mos[chosen_but]=FALSE;
			}
			old_bool[chosen_but]=new_bool;
	}

}

void test_all_but_mos(GAMEPAD_DEVICE GAMEPAD_0)
{
	char ch;
	ch='0';
	puts("TEST all button update. Press BACK to continue test");
	while(ch!='1'){
		update_all_but(GAMEPAD_0);
		if(g_mos[BUTTON_X_define_mos]==TRUE)
			puts("X-lore");
		if(g_mos[BUTTON_Y_define_mos]==TRUE)
			puts("Y-lore");
		if(g_mos[BUTTON_A_define_mos]==TRUE)
			puts("A-lore");
		if(g_mos[BUTTON_B_define_mos]==TRUE)
			puts("B-lore");
		if(g_mos[BUTTON_LEFT_STICK_define_mos]==TRUE)
			puts("light-stick-lore");
		if(g_mos[BUTTON_RIGHT_STICK_define_mos]==TRUE)
			puts("right-stick-lore");
		if(g_mos[BUTTON_START_define_mos]==TRUE)
			puts("START-lore");
		if(g_mos[BUTTON_BACK_define_mos]==TRUE){
			puts("BACK-lore");
			ch='1';
		}
		if(g_mos[BUTTON_LB_define_mos]==TRUE)
			puts("LB-lore");
		if(g_mos[BUTTON_RB_define_mos]==TRUE)
			puts("RB-lore");
		g_mos_reset();
	}
	ch='0';
	puts("TEST all single buttons update. Press START to exit test");
	while(ch!='1'){
		get_button_mos(GAMEPAD_0,"x");
		get_button_mos(GAMEPAD_0,"y");
		get_button_mos(GAMEPAD_0,"a");
		get_button_mos(GAMEPAD_0,"b");
		get_button_mos(GAMEPAD_0,"left_stick");
		get_button_mos(GAMEPAD_0,"right_stick");
		get_button_mos(GAMEPAD_0,"start");
		get_button_mos(GAMEPAD_0,"back");
		get_button_mos(GAMEPAD_0,"rb");
		get_button_mos(GAMEPAD_0,"lb");
		if(g_mos[BUTTON_X_define_mos]==TRUE)
			puts("X-lore");
		if(g_mos[BUTTON_Y_define_mos]==TRUE)
			puts("Y-lore");
		if(g_mos[BUTTON_A_define_mos]==TRUE)
			puts("A-lore");
		if(g_mos[BUTTON_B_define_mos]==TRUE)
			puts("B-lore");
		if(g_mos[BUTTON_LEFT_STICK_define_mos]==TRUE)
			puts("light-stick-lore");
		if(g_mos[BUTTON_RIGHT_STICK_define_mos]==TRUE)
			puts("right-stick-lore");
		if(g_mos[BUTTON_START_define_mos]==TRUE){
			puts("START-lore");
			ch='1';
		}
		if(g_mos[BUTTON_BACK_define_mos]==TRUE)
			puts("BACK-lore");
		if(g_mos[BUTTON_LB_define_mos]==TRUE)
			puts("LB-lore");
		if(g_mos[BUTTON_RB_define_mos]==TRUE)
			puts("RB-lore");
		g_mos_reset();
	}

}

void g_mos_reset(){
	int i;
	for(i=0;i<sizeof gamepad_but_list/sizeof (struct gamepad_items);i++)
		g_mos[i]=FALSE;
}

void init_gamepad_rogmos()
{
	cbreak();
    timeout(1);
    GamepadInit();

}

int main(){
	char ch;

	init_gamepad_rogmos();

	test_all_but_mos(GAMEPAD_0);
/*
	while((ch==getch())!='q'){
		get_button_mos(GAMEPAD_0,"left_stick");
		get_button_mos(GAMEPAD_0,"y");
		get_button_mos(GAMEPAD_0,"x");
		update_all_but(GAMEPAD_0);
		if(g_mos[BUTTON_X_define_mos]==TRUE)
			puts("X-lore");
		if(g_mos[BUTTON_Y_define_mos]==TRUE)
			puts("Y-lore");
		if(g_mos[BUTTON_LEFT_STICK_define_mos]==TRUE)
			puts("light stick lore");
		g_mos_reset();
	}*/

	return 0;
}

