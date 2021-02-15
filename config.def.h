#include <X11/XF86keysym.h>
/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 1;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 5;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 5;       /* vert inner gap between windows */
static const unsigned int gappoh    = 5;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 5;       /* vert outer gap between windows and screen edge */
static const int smartgaps          = 0;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const int viewontag          = 1;     /* Switch view on tag switch */
static const char *fonts[]          = { "FiraCode Nerd Font:size=10" };
static const char dmenufont[]       = "FiraCode Nerd Font:size=10";
static const char col_gray1[]       = "#222222";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#bbbbbb";
static const char col_gray4[]       = "#ffffff";
static const char col_cyan[]        = "#37474F";
static const char col_border[]      = "#008000";
static const unsigned int baralpha  = 0xd0;
static const unsigned int borderalpha = OPAQUE;
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_border  },
	[SchemeHid]  = { col_cyan,  col_gray1, col_border  },
};
static const unsigned int alphas[][3]      = {
	/*               fg      bg        border     */
	[SchemeNorm] = { OPAQUE, baralpha, borderalpha },
	[SchemeSel]  = { OPAQUE, baralpha, borderalpha },
};

/* tagging */
//static const char *tags[] = { "一", "二", "三", "四", "五", "六", "七", "八", "九" };
static const char *tags[] = { "\uf120", "\uf7ae", "\uf121", "\uf001", "\uf718", "\uf04b", "\uf251", "\uf537", "\uf684" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",     NULL,       NULL,       0,            1,           -1 },
	{ "Firefox",  NULL,       NULL,       1 << 8,       0,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask         /* 前缀键，Mod1Mask:Alt  Mod4Mask:Windows */
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[]      = { "rofi","-show","run", NULL };
static const char *termcmd[]       = { "st", NULL };
static const char *sshcmd[]        = { "rofi","-show","ssh", NULL };
static const char *upvol[]         = { "/home/yuan/.dwm/manual/vol-up.sh",  NULL };
static const char *downvol[]       = { "/home/yuan/.dwm/manual/vol-down.sh",  NULL };
static const char *mutevol[]       = { "/home/yuan/.dwm/manual/vol-toggle.sh",  NULL };
static const char *uplight[]       = { "/home/yuan/.dwm/manual/light-up.sh",  NULL };
static const char *downlight[]     = { "/home/yuan/.dwm/manual/light-down.sh",  NULL };
static const char *screenshotcmd[] = { "/home/yuan/.dwm/manual/screenshot.sh", NULL };
static const char *trayercmd[]     = { "/home/yuan/.dwm/manual/trayer.sh", NULL };

static const char scratchpadname[] = "scratchpad";
static const char *scratchpadcmd[] = { "st", "-t", scratchpadname, "-g", "120x34", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },      /* 启动器 */
	{ MODKEY|ControlMask,           XK_p,      spawn,          {.v = sshcmd } },        /* ssh */
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = termcmd } },       /* 终端 */
	{ MODKEY,                       XK_grave,  togglescratch,  {.v = scratchpadcmd } }, /* 打开浮动终端*/
	{ MODKEY,                       XK_b,      togglebar,      {0} },					/* 隐藏/显示bar */
	{ MODKEY|ShiftMask,             XK_l,      rotatestack,    {.i = +1 } },			/* 窗口循环旋转 */
	{ MODKEY|ShiftMask,             XK_h,      rotatestack,    {.i = -1 } },
	{ MODKEY,			            XK_l,      focusstackvis,  {.i = +1 } },			/* 窗口循环选择*/
	{ MODKEY,                       XK_h,      focusstackvis,  {.i = -1 } },
	{ MODKEY,                       XK_k,      focusstackhid,  {.i = +1 } },			/* 窗口循环选择（包含被隐藏窗口）*/
	{ MODKEY,                       XK_j,      focusstackhid,  {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_equal,  incnmaster,     {.i = +1 } },			/* + ,增加主区域窗口数量*/
	{ MODKEY,                       XK_minus,  incnmaster,     {.i = -1 } },			/* - ,减少主区域窗口数量*/
	{ MODKEY|ControlMask,           XK_h,      setmfact,       {.f = -0.05} },          /* 增加主区域大小 */
	{ MODKEY|ControlMask,           XK_l,      setmfact,       {.f = +0.05} },

	{ 0,            XF86XK_AudioLowerVolume,   spawn,          {.v = downvol } },       /* 音量和屏幕亮度 */
	{ 0,            XF86XK_AudioMute,          spawn,          {.v = mutevol } },
	{ 0,            XF86XK_AudioRaiseVolume,   spawn,          {.v = upvol   } },
	{ 0,		    XF86XK_MonBrightnessDown,  spawn,          {.v = downlight  } },
	{ 0,		    XF86XK_MonBrightnessUp,    spawn,          {.v = uplight    } },
	{ MODKEY,                       XK_F1,     spawn,          {.v = mutevol } },
	{ MODKEY,                       XK_F2,     spawn,          {.v = downvol } },
	{ MODKEY,				        XK_F3,     spawn,          {.v = upvol   } },
	{ MODKEY,				        XK_F11,    spawn,          {.v = downlight  } },
	{ MODKEY,				        XK_F12,    spawn,          {.v = uplight    } },
	{ MODKEY|ControlMask,           XK_a,      spawn,          {.v = screenshotcmd } }, /* 截图 */
	{ ControlMask,                  XK_t,      spawn,          {.v = trayercmd } },     /* 系统托盘 */

	/*
	{ MODKEY|Mod4Mask,              XK_h,      incrgaps,       {.i = +1 } },
	{ MODKEY|Mod4Mask,              XK_l,      incrgaps,       {.i = -1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_h,      incrogaps,      {.i = +1 } },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_l,      incrogaps,      {.i = -1 } },
	{ MODKEY|Mod4Mask|ControlMask,  XK_h,      incrigaps,      {.i = +1 } },
	{ MODKEY|Mod4Mask|ControlMask,  XK_l,      incrigaps,      {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_0,      togglegaps,     {0} },
	{ MODKEY|Mod4Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },
	{ MODKEY,                       XK_y,      incrihgaps,     {.i = +1 } },
	{ MODKEY,                       XK_o,      incrihgaps,     {.i = -1 } },
	{ MODKEY|ControlMask,           XK_y,      incrivgaps,     {.i = +1 } },
	{ MODKEY|ControlMask,           XK_o,      incrivgaps,     {.i = -1 } },
	{ MODKEY|Mod4Mask,              XK_y,      incrohgaps,     {.i = +1 } },
	{ MODKEY|Mod4Mask,              XK_o,      incrohgaps,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_y,      incrovgaps,     {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_o,      incrovgaps,     {.i = -1 } },
	*/
	{ MODKEY,                       XK_Return, zoom,           {0} },					/* 所选窗口在主区域和堆栈间切换 */
	{ MODKEY,                       XK_Tab,    view,           {0} },                   /* tag切换*/
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },                   /* 关闭程序 */
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },    /* 平铺模式 */
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },	/* 浮动模式 alt+mouseleft移动窗口 alt+mouseright调整窗口大小 */
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },    /* 全屏模式 */
	{ MODKEY|ShiftMask,             XK_f,      fullscreen,     {0} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },					/* 所选窗口置顶 */
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },					/* 所选窗口浮动 */
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },           /* 所有窗口集中显示 */
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },			/* alt + . 主副屏幕间移动焦点 */
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },            /* alt + > 主副屏幕间移动窗口 */
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_s,      show,           {0} },                   /* 设置当前窗口为显示状态 */
	{ MODKEY,                       XK_s,      hide,           {0} },					/* 设置当前窗口为隐藏状态 */
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_q,      quit,           {0} },                    /* 退出dwm */
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button1,        togglewin,      {0} },
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

