/* See LICENSE file for copyright and license details. */
#include <X11/XF86keysym.h>

#define SESSION_FILE "/tmp/dwm-session"

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int gappx     = 6;        /* gaps between windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 0;        /* 0 means bottom bar */
static const int user_bh            = 20;        /* 0 means that dwm will calculate bar height, >= 1 means dwm will user_bh as bar height */
static const Bool statusmarkup      = True;     /* True means use pango markup in status message */
static const char font[]            = "monospace 8";
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

static const char scratchpadname[] = "scratchpad";
static const char scratchemacsname[] = "emacs-scratch";
static const Rule rules[] = {
    /* xprop(1):
     *	WM_CLASS(STRING) = instance, class
     *	WM_NAME(STRING) = title
     */
    /* class  instance   title      tags mask isfloating monitor float x,y,w,h  floatborderpx*/
    { "st",    NULL,   scratchpadname,   0,        1,         -1,     0,0,1916,300,  1 },
    { "Emacs", NULL,   scratchemacsname, 0,        1,         -1,     0,0,1916,300,  1 },
    { "zoom",  NULL,   NULL,					   0,        1,         -1,     0,0,-1,-1,     1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */
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
static const char *scratchpadcmd[] = { ".dwm/scripts/dwm-st", scratchpadname, NULL };
static const char *scratchemacscmd[] = {  ".dwm/scripts/dwm-emacs", scratchemacsname, NULL };
static const char *termcmd[]  = { "st", NULL };

#include "movestack.c"
// keysyms can be found at /usr/include/X11/keysymdef.h
// i'm using sxhkd, so I don't need defined keys here.
static Key keys[] = { NULL };

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

void
setlayoutex(const Arg *arg)
{
    setlayout(&((Arg) {
        .v = &layouts[arg->i]
    }));
}

void
viewex(const Arg *arg)
{
    view(&((Arg) {
        .ui = 1 << arg->ui
    }));
}

void
viewprev(const Arg *arg)
{
    view(&((Arg) {
        0
    }));
}

void
viewall(const Arg *arg)
{
    view(&((Arg) {
        .ui = ~0
    }));
}

void
toggleviewex(const Arg *arg)
{
    toggleview(&((Arg) {
        .ui = 1 << arg->ui
    }));
}

void
tagex(const Arg *arg)
{
    tag(&((Arg) {
        .ui = 1 << arg->ui
    }));
}

void
toggletagex(const Arg *arg)
{
    toggletag(&((Arg) {
        .ui = 1 << arg->ui
    }));
}

void
tagall(const Arg *arg)
{
    tag(&((Arg) {
        .ui = ~0
    }));
}

void
togglescratchex(const Arg *arg)
{
    togglescratch(&((Arg) {
        .v = scratchpadcmd
    }));
}

void
toggleemacsex(const Arg *arg)
{
    toggleemacs(&((Arg) {
        .v = scratchemacscmd
    }));
}

/* signal definitions */
/* signum must be greater than 0 */
/* trigger signals using `xsetroot -name "fsignal:<signame> [<type> <value>]"` */
static Signal signals[] = {
    /* signum           function */
    { "focusstack",     focusstack },
    { "setmfact",       setmfact },
    { "togglebar",      togglebar },
    { "incnmaster",     incnmaster },
    { "togglefloating", togglefloating },
    { "focusmon",       focusmon },
    { "tagmon",         tagmon },
    { "zoom",           zoom },
    { "view",           view },
    { "viewprev",       viewprev },
    { "viewall",        viewall },
    { "viewex",         viewex },
    { "toggleview",     view },
    { "toggleviewex",   toggleviewex },
    { "tag",            tag },
    { "tagall",         tagall },
    { "tagex",          tagex },
    { "toggletag",      tag },
    { "toggletagex",    toggletagex },
    { "killclient",     killclient },
    { "quit",           quit },
    { "setlayout",      setlayout },
    { "setlayoutex",    setlayoutex },
    { "holdbar",				holdbar },
    { "movestack",			movestack },
    { "togglescratch",	togglescratchex },
    { "toggleemacs",	  toggleemacsex },
};
