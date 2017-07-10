#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#include "gamepad.h"

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

static const char* button_names[] = {
	"d-pad up",
	"d-pad down",
	"d-pad left",
	"d-pad right",
	"start",
	"back",
	"left thumb",
	"right thumb",
	"left shoulder",
	"right shoulder",
	"???",
	"???",
	"A",
	"B",
	"X",
	"Y"
};

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

void print_event();
void get_gx(GAMEPAD_DEVICE dev);
void get_but(GAMEPAD_DEVICE dev, char const but[3]);
void reset_flags_g0();
void get_button_mos(GAMEPAD_DEVICE dev,char const button_wanted[6]); //longest button name is start
void g_mos_reset();
bool g0_x=0;
bool g0_y=0;
bool g0_a=0;
bool g0_b=0;


bool g_mos[10];

static int line = 0;

void g_mos_reset()
{
	int i;
	for(i=0;i<10;i++)
		g_mos[i]=FALSE;
}

void reset_flags_g0(){
	g0_a=0;
	g0_b=0;
	g0_x=0;
	g0_y=0;
}

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

void get_gx(GAMEPAD_DEVICE dev){	//gets X-Button, One Click event, wont trigger multiple times with one click
	static bool new_bool,old_bool=FALSE;
	move(dev, 0);
	new_bool=GamepadButtonDown(dev, BUTTON_X);

	if(old_bool==TRUE&&new_bool==TRUE)
	{
		g0_x=FALSE;		
	}
	else if(old_bool==FALSE&&new_bool==TRUE)
	{
		g0_x=TRUE;
	}
	else
	{
		g0_x=FALSE;
	}
	old_bool=new_bool;
}

void get_but(GAMEPAD_DEVICE dev, char const but[3])
{
	
		
}

static void logevent(const char* format, ...) {
	va_list va;

	move(9 + line, 0);
	clrtoeol();

	move(8 + line, 0);
	clrtoeol();

	va_start(va, format);
	vwprintw(stdscr, format, va);
	va_end(va);

	if (++line == 14) {
		line = 0;
	}
}

static void update(GAMEPAD_DEVICE dev) {
	float lx, ly, rx, ry;

	move(dev, 0);

	if (!GamepadIsConnected(dev)) {
		printw("%d) n/a\n", dev);
		return;
	}

	GamepadStickNormXY(dev, STICK_LEFT, &lx, &ly);
	GamepadStickNormXY(dev, STICK_RIGHT, &rx, &ry);

	printw("%d) L:(%+.3f,%+.3f :: %+.3f,%+.3f) R:(%+.3f, %+.3f :: %+.3f,%+.3f) LT:%+.3f RT:%+.3f",
		dev,
		lx, ly,
		GamepadStickAngle(dev, STICK_LEFT),
		GamepadStickLength(dev, STICK_LEFT),
		rx, ry,
		GamepadStickAngle(dev, STICK_RIGHT),
		GamepadStickLength(dev, STICK_RIGHT),
		GamepadTriggerLength(dev, TRIGGER_LEFT),
		GamepadTriggerLength(dev, TRIGGER_RIGHT));
	printw("U:%d D:%d L:%d R:%d",
		GamepadButtonDown(dev, BUTTON_DPAD_UP),
		GamepadButtonDown(dev, BUTTON_DPAD_DOWN),
		GamepadButtonDown(dev, BUTTON_DPAD_LEFT),
		GamepadButtonDown(dev, BUTTON_DPAD_RIGHT));
	printw("A:%d B:%d X:%d Y:%d Bk:%d St:%d",
		GamepadButtonDown(dev, BUTTON_A),
		GamepadButtonDown(dev, BUTTON_B),
		GamepadButtonDown(dev, BUTTON_X),
		GamepadButtonDown(dev, BUTTON_Y),
		GamepadButtonDown(dev, BUTTON_BACK),
		GamepadButtonDown(dev, BUTTON_START));
	printw("LB:%d RB:%d LS:%d RS:%d\n",
		GamepadButtonDown(dev, BUTTON_LEFT_SHOULDER),
		GamepadButtonDown(dev, BUTTON_RIGHT_SHOULDER),
		GamepadButtonDown(dev, BUTTON_LEFT_THUMB),
		GamepadButtonDown(dev, BUTTON_RIGHT_THUMB));

		g0_a=GamepadButtonDown(dev, BUTTON_A);
}

void print_event()
{
	int i,j,k;
			for (j = 0; j != BUTTON_COUNT; ++j) {
				if (GamepadButtonTriggered(i, j)) {
					logevent("[%d] button triggered: %s", i, button_names[j]);
				} else if (GamepadButtonReleased(i, j)) {
					logevent("[%d] button released:  %s", i, button_names[j]);
				}
			}
			for (j = 0; j != TRIGGER_COUNT; ++j) {
				if (GamepadTriggerTriggered(i, j)) {
					logevent("[%d] trigger pressed:  %d", i, j);
				} else if (GamepadTriggerReleased(i, j)) {
					logevent("[%d] trigger released: %d", i, j);
				}
			}
			for (j = 0; j != STICK_COUNT; ++j) {
				for (k = 0; k != STICKDIR_COUNT; ++k) {
					if (GamepadStickDirTriggered(i, j, k)) {
						logevent("[%d] stick direction:  %d -> %d", i, j, k);
					}
				}

			}

}

int main(){

	
	char ch;
    //initscr();
    cbreak();
   // noecho();
    timeout(1);
    GamepadInit();

	unsigned long int i;
	enum gamepad_all_items my_gamepad_items;
	struct gamepad_items *choice = NULL;
	puts("hallo");
	//for(i=0, choice=NULL;i<NUMBER_GAMEPAD_BUT;i++) // alte Define-Lösung
	for(i=0, choice=NULL;i< sizeof gamepad_but_list/sizeof (struct gamepad_items);i++)
	{
		puts("hallo");
		if (strcmp("a", gamepad_but_list[i].name) == 0)
		{
			choice = gamepad_but_list + i;
			break;
		}
	}

	my_gamepad_items = choice ? choice ->id : UNKNOWN;

	switch(my_gamepad_items)
	{
		case BUT_RB:
			puts("SIEG");
			break;
		case BUT_A:
			puts("fett");
			break;
		default:
			puts("Die Russen kommen");
			break;
	}

	while((ch==getch())!='q'){
		
		get_button_mos(GAMEPAD_0,"left_stick");
		get_button_mos(GAMEPAD_0,"y");
		get_button_mos(GAMEPAD_0,"x");
		if(g_mos[BUTTON_X_define_mos]==TRUE)
			puts("X-cock");
		if(g_mos[BUTTON_Y_define_mos]==TRUE)
			puts("Y-cock");
		if(g_mos[BUTTON_LEFT_STICK_define_mos]==TRUE)
			puts("cock");
		sleep(1);
		g_mos_reset();
		puts("test");
	}
	

	//get_button_mos(dev,"rb");
	

	while((ch==getch())!='q'){
		GamepadUpdate();
		get_gx(GAMEPAD_0);
		if(g0_x==TRUE){
			puts("Lore\r");
		}
		//get_but(GAMEPAD_0,"aa");
	}

	

	while((ch==getch())!='q'){
		GamepadUpdate();

		update(GAMEPAD_0);
		//print_event();

		if(g0_a==1)
		{
			puts("jud");
		}

		reset_flags_g0();
	}
	return 0;
}
