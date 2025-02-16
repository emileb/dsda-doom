#include "doomdef.h"
#include "doomtype.h"
#include "doomstat.h"
#include "d_main.h"
#include "d_ticcmd.h"
#include "m_fixed.h"
#include "dsda/input.h"
#include <pthread.h>

#include "game_interface.h"

// FIFO STUFF ////////////////////
// Copied from FTEQW, I don't know if this is thread safe, but it's safe enough for a game :)
#define EVENTQUEUELENGTH 128
struct eventlist_s
{

	int scancode, unicode,state;

} eventlist[EVENTQUEUELENGTH];

volatile int events_avail; /*volatile to make sure the cc doesn't try leaving these cached in a register*/
volatile int events_used;

static struct eventlist_s *in_newevent(void)
{
	if (events_avail >= events_used + EVENTQUEUELENGTH)
		return NULL;
	return &eventlist[events_avail & (EVENTQUEUELENGTH-1)];
}

static void in_finishevent(void)
{
	events_avail++;
}
///////////////////////


int PortableKeyEvent(int state, int code, int unicode){

	//LOGI("PortableKeyEvent %d %d",state,code);
	struct eventlist_s *ev = in_newevent();
	if (!ev)
		return 0;

	ev->scancode = code;
	ev->unicode = code;
	ev->state = state;
	in_finishevent();
	return 0;
}

void PortableBackButton()
{
    PortableKeyEvent(1, KEYD_ESCAPE,0);
    PortableKeyEvent(0, KEYD_ESCAPE,0);
}

event_t event;
void Android_SendKeys( void )
{
	struct eventlist_s *ev;

	while (events_used != events_avail)
	{
		ev = &eventlist[events_used & (EVENTQUEUELENGTH-1)];
		if (ev->state)
			event.type = ev_keydown;
		else
			event.type = ev_keyup;

		event.data1 = (event_data_t)ev->scancode;

		D_PostEvent(&event);

		events_used++;
	}
}

extern int dsda_input_profile;
extern dsda_input_t dsda_input[DSDA_INPUT_PROFILE_COUNT][DSDA_INPUT_IDENTIFIER_COUNT];

// This only works if the
static void ActivateKey(int state, dsda_input_identifier_t dsdaId)
{
    dsda_input_t *input = &dsda_input[dsda_input_profile][dsdaId];

    if(input->num_keys)
    {
        int gameKey = input->key[0];
        PortableKeyEvent(state, gameKey, 0);
    }
    else
    {
        LOGE("DSDA: ERROR, key not bound to action %d", dsdaId);
    }
}

void PortableAction(int state, int action)
{
	LOGI("PortableAction %d %d",state, action);

	if ((action >= PORT_ACT_CUSTOM_0) && (action <= PORT_ACT_CUSTOM_17))
    {
        if( action <= PORT_ACT_CUSTOM_9 )
            PortableKeyEvent(state, KEYD_KEYPAD0 + action - PORT_ACT_CUSTOM_0, 0);
    }
	else if (( PortableGetScreenMode() == TS_MENU ) || ( PortableGetScreenMode() == TS_BLANK )  || ( PortableGetScreenMode() == TS_Y_N ))
	{
		if (action >= PORT_ACT_MENU_UP && action <= PORT_ACT_MENU_ABORT)
		{

			int sdl_code [] = { KEYD_UPARROW, KEYD_DOWNARROW, KEYD_LEFTARROW,
					KEYD_RIGHTARROW, KEYD_ENTER, KEYD_ESCAPE };
			PortableKeyEvent(state, sdl_code[action-PORT_ACT_MENU_UP],0);
			return;
		}
	}
	else
	{
		switch (action)
		{
		case PORT_ACT_LEFT:
            ActivateKey(state, dsda_input_turnleft);
			break;
		case PORT_ACT_RIGHT:
            ActivateKey(state, dsda_input_turnright);
			break;
		case PORT_ACT_FWD:
            ActivateKey(state, dsda_input_forward);
			break;
		case PORT_ACT_BACK:
            ActivateKey(state, dsda_input_backward);
			break;
		case PORT_ACT_MOVE_LEFT:
            ActivateKey(state, dsda_input_strafeleft);
			break;
		case PORT_ACT_MOVE_RIGHT:
            ActivateKey(state, dsda_input_straferight);
			break;
		case PORT_ACT_USE:
            ActivateKey(state, dsda_input_use);
			break;
		case PORT_ACT_ATTACK:
            ActivateKey(state, dsda_input_fire);
			break;
		case PORT_ACT_NEXT_WEP:
            ActivateKey(state, dsda_input_nextweapon);
			break;
		case PORT_ACT_PREV_WEP:
            ActivateKey(state, dsda_input_prevweapon);
			break;
		case PORT_ACT_JUMP:
            ActivateKey(state, dsda_input_jump);
			break;
		case PORT_ACT_MAP:
            ActivateKey(state, dsda_input_map);
			break;
		case PORT_ACT_MAP_UP:
            ActivateKey(state, dsda_input_map_up);
			break;
		case PORT_ACT_MAP_DOWN:
            ActivateKey(state, dsda_input_map_down);
			break;
		case PORT_ACT_MAP_LEFT:
            ActivateKey(state, dsda_input_map_left);
			break;
		case PORT_ACT_MAP_RIGHT:
            ActivateKey(state, dsda_input_map_right);
			break;
		case PORT_ACT_MAP_ZOOM_IN:
            ActivateKey(state, dsda_input_map_zoomin);
			break;
		case PORT_ACT_MAP_ZOOM_OUT:
            ActivateKey(state, dsda_input_map_zoomout);
			break;
		case PORT_ACT_WEAP1:
            ActivateKey(state, dsda_input_weapon1);
			break;
		case PORT_ACT_WEAP2:
            ActivateKey(state, dsda_input_weapon2);
			break;
		case PORT_ACT_WEAP3:
            ActivateKey(state, dsda_input_weapon3);
			break;
		case PORT_ACT_WEAP4:
            ActivateKey(state, dsda_input_weapon4);
			break;
		case PORT_ACT_WEAP5:
            ActivateKey(state, dsda_input_weapon5);
			break;
		case PORT_ACT_WEAP6:
            ActivateKey(state, dsda_input_weapon6);
			break;
		case PORT_ACT_WEAP7:
            ActivateKey(state, dsda_input_weapon7);
			break;
		case PORT_ACT_WEAP8:
            ActivateKey(state, dsda_input_weapon8);
            break;
        case PORT_ACT_WEAP9:
            ActivateKey(state, dsda_input_weapon9);
			break;
        case PORT_ACT_QUICKSAVE:
            ActivateKey(state, dsda_input_quicksave);
            break;
        case PORT_ACT_QUICKLOAD:
            ActivateKey(state, dsda_input_quickload);
            break;
        case PORT_ACT_DEMO_SPD_UP:
            ActivateKey(state, dsda_input_speed_up);
            break;
        case PORT_ACT_DEMO_SPD_DWN:
            ActivateKey(state, dsda_input_speed_down);
            break;
        case PORT_ACT_DEMO_SPD_DEF:
            ActivateKey(state, dsda_input_speed_default);
            break;
        case PORT_ACT_DEMO_JOIN:
            ActivateKey(state, dsda_input_quickload);
            break;
        case PORT_ACT_DEMO_CAMERA:
            ActivateKey(state, dsda_input_walkcamera);
            break;
        case PORT_ACT_GAMMA:
            ActivateKey(state, dsda_input_gamma);
            break;
		}
	}
}

// =================== FORWARD and SIDE MOVMENT ==============

static float forwardmove_android, sidemove_android; //Joystick mode

void PortableMoveFwd(float fwd)
{
	if (fwd > 1)
		fwd = 1;
	else if (fwd < -1)
		fwd = -1;

	forwardmove_android = fwd;
}

void PortableMoveSide(float strafe)
{
	if (strafe > 1)
		strafe = 1;
	else if (strafe < -1)
		strafe = -1;

	sidemove_android = strafe;
}

void PortableMove(float fwd, float strafe)
{
	PortableMoveFwd(fwd);
	PortableMoveSide(strafe);
}

//======================================================================

//Look up and down
static float look_pitch_mouse,look_pitch_abs,look_pitch_joy;
void PortableLookPitch(int mode, float pitch)
{
	switch(mode)
	{
	case LOOK_MODE_MOUSE:
		look_pitch_mouse -= pitch;
		break;
	case LOOK_MODE_JOYSTICK:
		look_pitch_joy = pitch;
		break;
	}
}

//left right
static float look_yaw_mouse,look_yaw_joy;
void PortableLookYaw(int mode, float yaw)
{
	switch(mode)
	{
	case LOOK_MODE_MOUSE:
		look_yaw_mouse += yaw;
		break;
	case LOOK_MODE_JOYSTICK:
		look_yaw_joy = yaw;
		break;
	}
}


static float am_zoom = 0;
static float am_pan_x = 0;
static float am_pan_y = 0;

void PortableAutomapControl(float zoom, float x, float y)
{
	am_zoom += zoom;
	am_pan_x += x;
	am_pan_y += y;
}

void PortableCommand(const char * cmd){}

void PortableInit(int argc,const char ** argv){

	extern int main_android(int argc, char **argv);
	main_android(argc, ( char **)argv);
}


extern  menuactive_t menuactive; // Type of menu overlaid, if any
extern dboolean         demoplayback;
extern enum automapmode_e automapmode;
extern dboolean         usergame;
touchscreemode_t PortableGetScreenMode()
{
    if( menuactive )
        return TS_MENU;
    else
        return TS_GAME;
    /*
    {
        if (automapmode & am_active)
            return TS_MAP;
            //return TS_GAME;
        else if( usergame )
            return TS_GAME;
        else if(demoplayback)
            return TS_DEMO;
        else
            return TS_BLANK;
    }
     */
}

void Mobile_AM_controls(double *zoom, fixed_t *pan_x, fixed_t *pan_y )
{
	if (am_zoom)
	{
        *zoom = am_zoom * 10;
		am_zoom = 0;
	}

	*pan_x += (fixed_t)(am_pan_x * 20000000);
	*pan_y += -(fixed_t)(am_pan_y * 10000000);
	am_pan_x = am_pan_y = 0;
	//LOGI("zoom = %f",*zoom);
}

//in g_game.c for max speeds
extern fixed_t forwardmove[2];
extern fixed_t sidemove[2];
extern int mlooky;

//Called by doom on each tick
void Mobile_IN_Move(ticcmd_t* cmd )
{
    int blockGamepad( void );
    int blockMove = blockGamepad() & ANALOGUE_AXIS_FWD;
    int blockLook = blockGamepad() & ANALOGUE_AXIS_PITCH;

    if( !blockMove )
    {
        float fwdSpeed =  forwardmove_android;
        float sideSpeed = sidemove_android;

        if(!isPlayerRunning())
        {
            fwdSpeed = fwdSpeed / 2;
            sideSpeed = sideSpeed /2;
        }

	    cmd->forwardmove  += fwdSpeed * forwardmove[1];
	    cmd->sidemove  += sideSpeed  * sidemove[1];
    }

    if( !blockLook )
    {
        mlooky += look_pitch_mouse * 30000;
        look_pitch_mouse = 0;
        mlooky += look_pitch_joy * 1000;

        cmd->angleturn += look_yaw_mouse * 80000;
        look_yaw_mouse = 0;
        cmd->angleturn += look_yaw_joy * 1000;
    }
/*
	if (newweapon != wp_nochange)
	{
		const player_t *player = &players[consoleplayer];

		if (newweapon == wp_shotgun && gamemode == commercial &&
				player->weaponowned[wp_supershotgun] &&
				(!player->weaponowned[wp_shotgun] ||
						player->readyweapon == wp_shotgun ||
						(player->readyweapon != wp_supershotgun &&
								P_WeaponPreferred(wp_supershotgun, wp_shotgun))))
			newweapon = wp_supershotgun;

		cmd->buttons |= BT_CHANGE;
		cmd->buttons |= newweapon<<BT_WEAPONSHIFT;
		newweapon = wp_nochange;
	}
 */
}

