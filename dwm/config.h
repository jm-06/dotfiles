
/* Constants */
#define TERMINAL "st"
#define TERMCLASS "St"

/* appearance */
static const unsigned int borderpx = 0;   /* border pixel of windows */
static const unsigned int snap     = 32;  /* snap pixel */
static const unsigned int gappx    = 0;   /* pixel gap between clients */
static const int swallowfloating   = 1;   /* 1 means swallow floating windows by default*/
static const int showbar           = 1;   /* 0 means no bar */
static const int topbar            = 1;   /* 0 means bottom bar */
static const int horizpadbar       = 1;   /* horizontal padding for statusbar */
static const int vertpadbar        = 1;   /* vertical padding for statusbar */

/*fonts*/
static const char *fonts[]     = {"Terminus:size=8", "Terminus:size=8"};
static const char dmenufont[]  = "Terminus:size=8";

						     	
static const char col_1[]  = "#babfca"; /* background colour of bar */
static const char col_2[]  = "#babfca"; /* border colour unfocused windows */
static const char col_3[]  = "#010101"; /* text colour */
static const char col_4[]  = "#7b8aa2"; /* border colour focused windows and tags */
/* bar opacity 
 * 0xff is no transparency.
 * 0xee adds wee bit of transparency.
 * 0xdd adds adds a bit more transparency.
 * Play with the value to get desired transparency.
 */
static const unsigned int baralpha    = 0xff; 
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]        = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_3, col_1, col_2 },
	[SchemeSel]  = { col_3, col_4, col_4 },
};
static const unsigned int alphas[][3] = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX" }; 


static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating	isterminal   noswallow	 monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,          0, 	      0,	  -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,          0,	     -1, 	  -1 },
	{ "St",	      NULL,	  NULL,	      0,	    0,		1,	      0,	  -1 },
	{ "ranger",   NULL,	  NULL,	      0,	    0,		1,	      0,	  -1 },
};

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* layout(s) */
static const float mfact     = 0.50; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */

#include "layouts.c"
static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
	{ "HHH",      grid },
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(CHAIN,KEY,TAG) \
	{ MODKEY,                       CHAIN,    KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           CHAIN,    KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             CHAIN,    KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, CHAIN,    KEY,      toggletag,      {.ui = 1 << TAG} },
#define CMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* dmenu */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
/* If you are using the standard dmenu program, use the following. */
static const char *dmenucmd[]    = { "dmenu_run", "-p", "Run: ", NULL };

/* static const char *dmenucmd[]    = { "dmenu_run", "-g", "10", "-l", "48", "-p", "Run: ", NULL }; */

/* the st terminal */
static const char *termcmd[]     = { TERMINAL,  "-e",  NULL };

static const char *ranger[] = {"st", "-e", "/usr/bin/ranger", NULL };


static Key keys[] = {
	/* modifier             chain key  key        function        argument */
	{ MODKEY|ShiftMask,     -1,        XK_Return, spawn,          {.v = dmenucmd } },
	{ MODKEY,               -1,        XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,               -1,        XK_b,      togglebar,      {0} },
	{ MODKEY|ShiftMask,     -1,        XK_j,      rotatestack,    {.i = +1 } },
	{ MODKEY|ShiftMask,     -1,        XK_k,      rotatestack,    {.i = -1 } },
	{ MODKEY,               -1,        XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,               -1,        XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,               -1,        XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,               -1,        XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,               -1,        XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,               -1,        XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ControlMask,   -1,        XK_Return, zoom,           {0} },
	{ MODKEY,               -1,        XK_a,      view,           {0} },
	{ MODKEY,    		-1,	   XK_c,      killclient,     {0} },
	{ MODKEY,		-1,	   XK_w,      spawn,          CMD("icecat") },
	{ MODKEY|ShiftMask,	-1,        XK_w,      spawn,	      CMD("librewolf") },
	{ MODKEY,		-1,        XK_x,      spawn,	      CMD("betterlockscreen -l") },
	{ MODKEY|Mod1Mask,	-1,	   XK_m,      spawn,	      CMD("rpcs3 ~/Roms/PS3_Roms/MetalGearSolid-HDCollection") },
	{ MODKEY|Mod1Mask,	-1,	   XK_l,      spawn,	      CMD("lutris") },

    /*Terminal Commands*/
	{ MODKEY|ShiftMask,	-1,        XK_m,      spawn,	      SHCMD(TERMINAL " -e ~/.config/ncmpcpp/ncmpcpp-ueberzug/ncmpcpp-ueberzug") },
	{ MODKEY|ShiftMask,	-1,	   XK_f,      spawn,	      {.v = ranger } },
	{ MODKEY|ShiftMask,	-1,	   XK_a,      spawn,          SHCMD(TERMINAL " -e alsamixer") },	
	{ MODKEY,		-1,	   XK_e,      spawn,	      SHCMD(TERMINAL " -e htop") },
	{ MODKEY|ShiftMask,	-1,	   XK_e,      spawn,	      SHCMD(TERMINAL " -e gotop") },
	{ MODKEY,		-1,        XK_y,      spawn,          SHCMD(TERMINAL " -e ytfzf") },
	{ MODKEY|ShiftMask,     -1,	   XK_c,      spawn,	      CMD(" cd ~/.config/chancli && ./chancli.py") },
	{ MODKEY|Mod1Mask,	-1,	   XK_q,      spawn,          SHCMD(TERMINAL " -e sudo poweroff") },
	{ MODKEY|Mod1Mask,	-1,	   XK_r,      spawn,          SHCMD(TERMINAL " -e sudo reboot") }, 
	{ MODKEY,		-1,	   XK_s,      spawn, 	      CMD(" cd ~/Games/steam-dmenu && ./steam_dmenu.py") },

    /*Volume Controls*/
	{ MODKEY,		-1,	   XK_F12,	      spawn,	     SHCMD("pamixer --allow-boost -i 5") },
	{ MODKEY,		-1,	   XK_F11,	      spawn,	     SHCMD("pamixer --allow-boost -d 5") },
	{ MODKEY,		-1,	   XK_F10,	      spawn,	     SHCMD("pamixer -t") },
	{ MODKEY,		-1,	   XK_F9,	      spawn,	     SHCMD("mpc stop") },
	{ MODKEY,		-1,	   XK_F8,	      spawn,	     SHCMD("mpc pause") },
	{ MODKEY,		-1,	   XK_F7,	      spawn,	     SHCMD("mpc play") },
	{ MODKEY,		-1,	   XK_F6,	      spawn,	     SHCMD("mpc next") }, 
	{ MODKEY,		-1, 	   XK_F5,	      spawn,	     SHCMD("mpc prev") },

    /* Layout manipulation */
	{ MODKEY,               -1,        XK_Tab,    cyclelayout,    {.i = -1 } },
	{ MODKEY|ShiftMask,     -1,        XK_Tab,    cyclelayout,    {.i = +1 } },
	{ MODKEY,               -1,        XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,     -1,        XK_space,  togglefloating, {0} },
	
    /* Switch to specific layouts */
	{ MODKEY,               -1,        XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,               -1,        XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,               -1,        XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,               -1,        XK_g,      setlayout,      {.v = &layouts[3]} },

	{ MODKEY,               -1,        XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,     -1,        XK_0,      tag,            {.ui = ~0 } },

    /* Switching between monitors */
	{ MODKEY,               -1,        XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,               -1,        XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,     -1,        XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,     -1,        XK_period, tagmon,         {.i = +1 } },
	
    /* Keybindings for programs using the format SUPER + ALT + "key" */
	{ MODKEY|Mod1Mask,      -1,        XK_s,      spawn,          CMD("steam") }, 
	{ MODKEY|Mod1Mask,	-1,	   XK_d,      spawn,	      CMD("ripcord") },
	{ MODKEY|Mod1Mask,	-1,	   XK_w,      spawn,	      CMD("qutebrowser") },
	{ MODKEY|Mod1Mask,	-1,	   XK_f,      spawn,	      CMD("pcmanfm") },
	
	
    /* Dmenu scripts launched with emacs-style keychords SUPER + p followed by "key" */
	{ MODKEY,               XK_p,      XK_e,      spawn,          CMD("./dmscripts/dm-confedit") },
	{ MODKEY,               XK_p,      XK_i,      spawn,          CMD("./dmscripts/dm-maim") },
	{ MODKEY,               XK_p,      XK_k,      spawn,          CMD("./dmscripts/dm-kill") },
	{ MODKEY,               XK_p,      XK_l,      spawn,          CMD("./dmscripts/dm-logout") },
	{ MODKEY,               XK_p,      XK_m,      spawn,          CMD("./dmscripts/dm-man") },
	{ MODKEY,               XK_p,      XK_s,      spawn,          CMD("./dmscripts/dm-websearch") },
	{ MODKEY,               XK_p,      XK_p,      spawn,          CMD("passmenu") },
    
    /* Doom emacs keybindings use the keychord CTRL + e followed by "key" */
	{ ControlMask,          XK_e,      XK_e,      spawn,          CMD("emacsclient -c -a 'emacs'") },
	{ ControlMask,          XK_e,      XK_b,      spawn,          CMD("emacsclient -c -a 'emacs' --eval '(ibuffer)'") },
	{ ControlMask,          XK_e,      XK_d,      spawn,          CMD("emacsclient -c -a 'emacs' --eval '(dired nil)'") },
	{ ControlMask,          XK_e,      XK_m,      spawn,          CMD("emacsclient -c -a 'emacs' --eval '(mu4e)'") },
	{ ControlMask,          XK_e,      XK_n,      spawn,          CMD("emacsclient -c -a 'emacs' --eval '(elfeed)'") },
	{ ControlMask,          XK_e,      XK_s,      spawn,          CMD("emacsclient -c -a 'emacs' --eval '(eshell)'") },
	{ ControlMask,          XK_e,      XK_v,      spawn,          CMD("emacsclient -c -a 'emacs' --eval '(+vterm/here nil)'") },

	TAGKEYS(                -1,        XK_1,                      0)
	TAGKEYS(                -1,        XK_2,                      1)
	TAGKEYS(                -1,        XK_3,                      2)
	TAGKEYS(                -1,        XK_4,                      3)
	TAGKEYS(                -1,        XK_5,                      4)
	TAGKEYS(                -1,        XK_6,                      5)
	TAGKEYS(                -1,        XK_7,                      6)
	TAGKEYS(                -1,        XK_8,                      7)
	TAGKEYS(                -1,        XK_9,                      8)
	{ MODKEY|ShiftMask,     -1,        XK_q,      quit,	     {0} },
    	{ MODKEY|ShiftMask,     -1,        XK_r,      quit,          {1} }, 
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click           event mask   button          function        argument */
	{ ClkLtSymbol,     0,           Button1,        setlayout,      {0} },
	{ ClkLtSymbol,     0,           Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,     0,           Button2,        zoom,           {0} },
	{ ClkStatusText,   0,           Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,    MODKEY,      Button1,        movemouse,      {0} },
	{ ClkClientWin,    MODKEY,      Button2,        togglefloating, {0} },
	{ ClkClientWin,    MODKEY,      Button3,        resizemouse,    {0} },
	{ ClkTagBar,       0,           Button1,        view,           {0} },
	{ ClkTagBar,       0,           Button3,        toggleview,     {0} },
	{ ClkTagBar,       MODKEY,      Button1,        tag,            {0} },
	{ ClkTagBar,       MODKEY,      Button3,        toggletag,      {0} },
};


