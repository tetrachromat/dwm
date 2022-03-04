/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 6;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const int user_bh            = 20;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const Bool statusmarkup      = True;     /* True means use pango markup in status message */
static const char font[]            = "monospace 8";
static const char dmenufont[]       = "monospace:size=8";
static const char col_black[]       = "#030303";
static const char col_white[]       = "#fbf5f3";
static const char col_red[]         = "#fe3198";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_red, col_black, col_black },
	[SchemeSel]  = { col_red, col_black, col_red  },
  // Statusbar right {text,background,not used but cannot be empty}
	[SchemeStatus]  = { col_white, col_black,  "#000000"  }, 
  // Tagbar left selected {text,background,not used but cannot be empty}
	[SchemeTagsSel]  = { col_red, col_black,  "#000000"  }, 
  // Tagbar left unselected {text,background,not used but cannot be empty}
  [SchemeTagsNorm]  = { col_white, col_black,  "#000000"  }, 
  // infobar middle  selected {text,background,not used but cannot be empty}
  [SchemeInfoSel]  = { col_white, col_black,  "#000000"  }, 
  // infobar middle  unselected {text,background,not used but cannot be empty}
  [SchemeInfoNorm]  = { col_white, col_black,  "#000000"  }, 
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "10" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class  instance    title     tags mask isfloating monitor float x,y,w,h  floatborderpx*/
	{ "st",   NULL,   "scratchpad", 0,        1,         -1,     0,0,1916,300,  1 },
	{ "zoom", NULL,   NULL,					0,        1,         -1,     0,0,-1,-1, 1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static int attachbelow = 1;    /* 1 means attach after the currently active window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[F]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define ALTKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define HOLDKEY XK_Super_L 

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
/* component of dmenucmd, manipulated in spawn() */
static char dmenumon[2] = "0"; 
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-i", "-hp", "discord", NULL };
static const char *termcmd[]  = { "st", NULL };
static const char *spotifytoggle[] = { "playerctl", "-p", "spotify", "play-pause", NULL };
static const char *vlctoggle[] = { "playerctl", "-p", "vlc", "play-pause", NULL };
static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };
static const char *scrotcmd[] = { "screenshot", NULL };
static const char *firefox[] = { "firefox", NULL };
static const char *incbl[] = { "derp", "i", NULL };
static const char *decbl[] = { "derp", "d", NULL };
static const char *incabl[] = { "aderp", "i", NULL };
static const char *decabl[] = { "aderp", "d", NULL };
static const char *zzz[] = { "sz", NULL };
static const char *ZZZ[] = { "sZ", NULL };
static const char *pst[] = { "pst", NULL };
static const char *dunstclear[] = { "dunstctl", "close", NULL };
static const char *vold[] = { "vold", NULL };
static const char *volu[] = { "volu", NULL };
static const char *volm[] = { "volm", NULL };
static const char *volg[] = { "volg", NULL };
static const char *lock[] = { "slock", NULL };
static const char *lzzz[] = { "lzzz", NULL };

#include "movestack.c"
// keysyms can be found at /usr/include/X11/keysymdef.h
static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_d,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_y,      togglescratch,  {.v = scratchpadcmd } },
	{ MODKEY,                       XK_m,      spawn,          {.v = spotifytoggle } },
	{ MODKEY|ShiftMask,             XK_m,      spawn,          {.v = vlctoggle } },
	{ MODKEY,                       XK_c,      spawn,          {.v = firefox } },
	{ MODKEY,                       XK_s,      spawn,          {.v = scrotcmd } },
	{ MODKEY|ALTKEY,                XK_equal,  spawn,          {.v = incbl } },
	{ MODKEY|ALTKEY,                XK_minus,  spawn,          {.v = decbl } },
	{ MODKEY|ALTKEY|ShiftMask,      XK_equal,  spawn,          {.v = incabl } },
	{ MODKEY|ALTKEY|ShiftMask,      XK_minus,  spawn,          {.v = decabl } },
	{ MODKEY|ControlMask,           XK_p,      spawn,          {.v = pst } },
	{ MODKEY|ControlMask,           XK_z,      spawn,          {.v = zzz } },
	{ MODKEY|ShiftMask|ControlMask, XK_z,      spawn,          {.v = ZZZ } },
	{ MODKEY,                       XK_u,		   spawn,          {.v = dunstclear } },
	{ MODKEY|ControlMask,           XK_l,		   spawn,          {.v = lock } },
	{ MODKEY|ControlMask|ShiftMask, XK_l,		   spawn,          {.v = lzzz } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_o,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05 } },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05 } },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY,                       XK_space,  zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_q,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} }, // set tiling
	{ MODKEY|ShiftMask,             XK_f,      setlayout,      {.v = &layouts[1]} }, // floating
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[2]} }, // set monocle / fullscreen
	{ MODKEY|ShiftMask,             XK_t,      setlayout,      {0} }, // floating
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_minus,  view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_minus,  tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = +1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_a,      setgaps,        {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_s,      setgaps,        {.i = +1 } },
	{ MODKEY|ShiftMask|ControlMask, XK_s,      setgaps,        {.i = 0  } },
  // volume keys
	{ 0,              XF86XK_AudioLowerVolume, spawn,          {.v = vold } },
	{ 0,              XF86XK_AudioRaiseVolume, spawn,          {.v = volu } },
	{ 0,              XF86XK_AudioMicMute,     spawn,          {.v = volm } },
	{ 0,              XF86XK_Tools,            spawn,          {.v = volg } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	TAGKEYS(                        XK_0,                      9)
	{ MODKEY|ControlMask|ShiftMask, XK_q,      quit,           {0} },
	{ MODKEY|ControlMask|ShiftMask, XK_r,      quit,           {1} }, 
	{ 0,                            HOLDKEY,   holdbar,        {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

