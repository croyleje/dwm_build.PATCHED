/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int swallowfloating    = 0;        /* 1 means swallow floating windows by default */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int horizpadbar        = 2;        /* horizontal padding for statusbar */
static const int vertpadbar         = 2;        /* vertical padding for statusbar */
static const char *fonts[]          = { "monospace:size=10" };
static const char dmenufont[]       = "monospace:size=10";
static const char col_gray1[]       = "#282a36";
static const char col_gray2[]       = "#44475a";
static const char col_gray3[]       = "#cdcdc9";
static const char col_gray4[]       = "#f8f8f2";
static const char col_cyan[]        = "#8be9fd";
static const char col_pink[]        = "#ff79c6";
static const char col_purple[]      = "#bd93f9";
static const char col_urgborder[]   = "#f1fa8c";
static const unsigned int baralpha = 0xd0;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray1 },
	[SchemeSel]  = { col_gray4, col_purple,  col_pink  },
	[SchemeUrg]  = { col_gray1, col_urgborder,  col_urgborder  },
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
	[SchemeUrg]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class        instance  title           tags mask  isfloating  isterminal  noswallow  monitor */
	/* { "BINARY",  NULL,     NULL,           1 << 8,    0,          -1,         0,         -1 }, */
	{ "Alacritty",  NULL,     NULL,           0,         0,          1,          0,         -1 },
	{ "St",         NULL,     NULL,           0,         0,          1,          0,         -1 },
	{ NULL,         NULL,     "Event Tester", 0,         0,          0,          1,         -1 }, /* xev */
};

/* layout(s) */
static const float mfact     = 0.52; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },
#define STACKKEYS(MOD,ACTION) \
	{ MOD, XK_j,     ACTION##stack, {.i = INC(+1) } }, \
	{ MOD, XK_k,     ACTION##stack, {.i = INC(-1) } }, \
	{ MOD, XK_grave, ACTION##stack, {.i = PREVSEL } },
	/* { MOD, XK_q,     ACTION##stack, {.i = 0 } }, \ */
	/* { MOD, XK_a,     ACTION##stack, {.i = 1 } }, \ */
	/* { MOD, XK_z,     ACTION##stack, {.i = 2 } }, \ */
	/* { MOD, XK_x,     ACTION##stack, {.i = -1 } }, */

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
/* static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL }; */
/* static const char *termcmd[]  = { "st", NULL }; */
static const char *dmenucmd[] = { "rofi", "-show", "drun" };
static const char *termcmd[]  = { "alacritty", NULL };

#include "focusurgent.c"
static Key keys[] = {
	/* modifier                     key                function        argument */
	{ MODKEY,                       XK_p,              spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return,         spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,              togglebar,      {0} },
	/* { MODKEY,                       XK_j,              focusstack,     {.i = +1 } }, */
	/* { MODKEY,                       XK_k,              focusstack,     {.i = -1 } }, */
	STACKKEYS(MODKEY,                          focus)
	STACKKEYS(MODKEY|ShiftMask,                push)
	{ MODKEY,                       XK_period,  viewnext,       {0} },
	{ MODKEY,                       XK_comma,   viewprev,       {0} },
	{ MODKEY|ShiftMask,             XK_period,  tagtonext,      {0} },
	{ MODKEY|ShiftMask,             XK_comma,   tagtoprev,      {0} },
	{ MODKEY,                       XK_i,              incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,              incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,              setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,              setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_h,      setcfact,       {.f = +0.25} },
	{ MODKEY|ShiftMask,             XK_l,      setcfact,       {.f = -0.25} },
	{ MODKEY|ShiftMask,             XK_o,      setcfact,       {.f =  0.00} },
	{ MODKEY|ShiftMask,             XK_Return,         zoom,           {0} },
	{ MODKEY,                       XK_Tab,            view,           {0} },
	{ MODKEY,                       XK_BackSpace,      killclient,     {0} },
	{ MODKEY,                       XK_t,              setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,              setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,              setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,          setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,          togglefloating, {0} },
	{ MODKEY|ShiftMask,             XK_f,              togglefullscr,  {0} },
	{ MODKEY,                       XK_0,              view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,              tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_Down,   moveresize,     {.v = "0x 25y 0w 0h" } },
	{ MODKEY,                       XK_Up,     moveresize,     {.v = "0x -25y 0w 0h" } },
	{ MODKEY,                       XK_Right,  moveresize,     {.v = "25x 0y 0w 0h" } },
	{ MODKEY,                       XK_Left,   moveresize,     {.v = "-25x 0y 0w 0h" } },
    { MODKEY|ShiftMask,             XK_Down,   moveresize,     {.v = "0x 0y 0w 25h" } },
	{ MODKEY|ShiftMask,             XK_Up,     moveresize,     {.v = "0x 0y 0w -25h" } },
	{ MODKEY|ShiftMask,             XK_Right,  moveresize,     {.v = "0x 0y 25w 0h" } },
	{ MODKEY|ShiftMask,             XK_Left,   moveresize,     {.v = "0x 0y -25w 0h" } },
    /* -Wunused-function warning focusmon & tagmon  */
	/* { MODKEY,                       XK_comma,          focusmon,       {.i = -1 } }, */
	/* { MODKEY,                       XK_period,         focusmon,       {.i = +1 } }, */
	/* { MODKEY|ShiftMask,             XK_comma,          tagmon,         {.i = -1 } }, */
	/* { MODKEY|ShiftMask,             XK_period,         tagmon,         {.i = +1 } }, */
	TAGKEYS(                        XK_1,                              0)
	TAGKEYS(                        XK_2,                              1)
	TAGKEYS(                        XK_3,                              2)
	TAGKEYS(                        XK_4,                              3)
	TAGKEYS(                        XK_5,                              4)
	TAGKEYS(                        XK_6,                              5)
	TAGKEYS(                        XK_7,                              6)
	TAGKEYS(                        XK_8,                              7)
	TAGKEYS(                        XK_9,                              8)
    { MODKEY|ControlMask,           XK_space,  focusmaster,    {0} },
	{ MODKEY|ShiftMask,             XK_q,              quit,           {0} },
	{ MODKEY,                       XK_u,      focusurgent,    {0} },
/* +	{ MODKEY|ShiftMask,             XK_BackSpace, quit,        {0} }, */
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
