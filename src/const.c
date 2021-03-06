 
/***************************************************************************
*  Original Diku Mud copyright (C) 1990, 1991 by Sebastian Hammer,        *
*  Michael Seifert, Hans Henrik St{rfeldt, Tom Madsen, and Katja Nyboe.   *
*
*  Merc Diku Mud improvments copyright (C) 1992, 1993 by Michael          *
*  Chastain, Michael Quan, and Mitchell Tse.                              *
*                                                                         *
*  In order to use any part of this Merc Diku Mud, you must comply with   *
*  both the original Diku license in 'license.doc' as well the Merc       *
*  license in 'license.txt'.  In particular, you may not remove either of *
*  these copyright notices.                                               *
*                                                                         *
*  Much time and thought has gone into this software and you are          *
*  benefitting.  We hope that you share your changes too.  What goes      *
*  around, comes around.                                                  *
***************************************************************************/

/***************************************************************************
*	ROM 2.4 is copyright 1993-1996 Russ Taylor			   *
*	ROM has been brought to you by the ROM consortium		   *
*	    Russ Taylor (rtaylor@efn.org)				   *
*	    Gabrielle Taylor						   *
*	    Brian Moore (zump@rom.org)					   *
*	By using this code, you have agreed to follow the terms of the	   *
*	ROM license, in the file Rom24/doc/rom.license			   *
***************************************************************************/

#if defined(macintosh)
#include <types.h>
#else
#include <sys/types.h>
#endif
#include <stdio.h>
#include <time.h>
#include "merc.h"
#include "magic.h"
#include "interp.h"


/* item type list */
const struct item_type		item_table	[]	=
{
    {	ITEM_LIGHT,	"light"		},
    {	ITEM_SCROLL,	"scroll"	},
    {	ITEM_WAND,	"wand"		},
    {   ITEM_STAFF,	"staff"		},
    {   ITEM_WEAPON,	"weapon"	},
    {   ITEM_TREASURE,	"treasure"	},
    {   ITEM_EXPLOSIVE,	"explosive"	},
    {   ITEM_ARMOR,	"armor"		},
    {	ITEM_POTION,	"potion"	},
    {	ITEM_CLOTHING,	"clothing"	},
    {   ITEM_FURNITURE,	"furniture"	},
    {	ITEM_TRASH,	"trash"		},
    {	ITEM_CONTAINER,	"container"	},
    {	ITEM_DRINK_CON, "drink"		},
    {	ITEM_KEY,	"key"		},
    {	ITEM_FOOD,	"food"		},
    {	ITEM_MONEY,	"money"		},
    {	ITEM_BOAT,	"boat"		},
    {	ITEM_CORPSE_NPC,"npc_corpse"	},
    {	ITEM_CORPSE_PC,	"pc_corpse"	},
    {   ITEM_FOUNTAIN,	"fountain"	},
    {	ITEM_PILL,	"pill"		},
    {	ITEM_PROTECT,	"protect"	},
    {	ITEM_MAP,	"map"		},
    {	ITEM_PORTAL,	"portal"	},
    {	ITEM_WARP_STONE,"warp_stone"	},
    {	ITEM_ROOM_KEY,	"room_key"	},
    {	ITEM_GEM,	"gem"		},
    {	ITEM_JEWELRY,	"jewelry"	},
    {   ITEM_JUKEBOX,	"jukebox"	},
    {   0,		NULL		}
};

/*god table*/

const   struct  god_type       god_table            []  =
{

/*
{
  name,
  player_good,  player_neutral,   player_evil
},
*/

{ "Nobody",         FALSE, FALSE, FALSE },
{ "Truth",       TRUE,  TRUE, TRUE },
{ "Justice",         TRUE,  TRUE, TRUE },
{ "War",         TRUE,  TRUE, TRUE },
{ "Greed",        TRUE,  TRUE, TRUE },
{ "Chaos",          TRUE,  TRUE, TRUE },
{ "Magic",      TRUE,  TRUE, TRUE },
{ "None",       TRUE,  TRUE, TRUE },
{ "Aurim",          FALSE, FALSE,  FALSE },
{ "Ashe",           FALSE, FALSE,  FALSE },
{ "Boreas",         FALSE, FALSE,  FALSE },
{ "Tarong",         FALSE, FALSE,  FALSE },
{ "Vannan",         FALSE, FALSE,  FALSE },
{ "Lauresh",        FALSE, FALSE,  FALSE },
{ "Shatana",        FALSE, FALSE,  FALSE },
{ "Chardros",       FALSE, FALSE, FALSE },
{ "Megalon",        FALSE, FALSE, FALSE },
{ "Shagrath",       FALSE, FALSE, FALSE },
{ "Skirin",         FALSE, FALSE, FALSE },
{ "Mordakk",        FALSE, FALSE, FALSE },
{ "Seareth",        FALSE, FALSE, FALSE },
{ "Sylania",        FALSE, FALSE, FALSE }

};




/* weapon selection table */
const	struct	weapon_type	weapon_table	[]	=
{
   { "sword",	OBJ_VNUM_SCHOOL_SWORD,	WEAPON_SWORD,	&gsn_sword	},
   { "mace",	OBJ_VNUM_SCHOOL_MACE,	WEAPON_MACE,	&gsn_mace 	},
   { "dagger",	OBJ_VNUM_SCHOOL_DAGGER,	WEAPON_DAGGER,	&gsn_dagger	},
   { "axe",	OBJ_VNUM_SCHOOL_AXE,	WEAPON_AXE,	&gsn_axe	},
   { "staff",	OBJ_VNUM_SCHOOL_STAFF,	WEAPON_STAFF,	&gsn_staff	},
   { "flail",	OBJ_VNUM_SCHOOL_FLAIL,	WEAPON_FLAIL,	&gsn_flail	},
   { "whip",	OBJ_VNUM_SCHOOL_WHIP,	WEAPON_WHIP,	&gsn_whip	},
   { "polearm",	OBJ_VNUM_SCHOOL_POLEARM,WEAPON_POLEARM,	&gsn_polearm	},
   { NULL,	0,				0,	NULL		}
};


 
/* wiznet table and prototype for future flag setting */
const   struct wiznet_type      wiznet_table    []              =
{
   {    "on",           WIZ_ON,         IM },
   {    "prefix",	WIZ_PREFIX,	IM },
   {    "ticks",        WIZ_TICKS,      IM },
   {    "logins",       WIZ_LOGINS,     IM },
   {    "sites",        WIZ_SITES,      L4 },
   {    "links",        WIZ_LINKS,      L7 },
   {	"newbies",	WIZ_NEWBIE,	IM },
   {	"spam",		WIZ_SPAM,	L5 },
   {    "deaths",       WIZ_DEATHS,     IM },
   {    "resets",       WIZ_RESETS,     L4 },
   {    "mobdeaths",    WIZ_MOBDEATHS,  L4 },
   {    "flags",	WIZ_FLAGS,	L5 },
   {	"penalties",	WIZ_PENALTIES,	L5 },
   {	"saccing",	WIZ_SACCING,	L5 },
   {	"levels",	WIZ_LEVELS,	IM },
   {	"load",		WIZ_LOAD,	L2 },
   {	"restore",	WIZ_RESTORE,	L2 },
   {	"snoops",	WIZ_SNOOPS,	L2 },
   {	"switches",	WIZ_SWITCHES,	L2 },
   {	"secure",	WIZ_SECURE,	L1 },
   {	NULL,		0,		0  }
};

/* attack table  -- not very organized :( */
const 	struct attack_type	attack_table	[MAX_DAMAGE_MESSAGE]	=
{
    { 	"none",		"hit",		-1		},  /*  0 */
    {	"slice",	"slice", 	DAM_SLASH	},	
    {   "stab",		"stab",		DAM_PIERCE	},
    {	"slash",	"slash",	DAM_SLASH	},
    {	"whip",		"whip",		DAM_SLASH	},
    {   "claw",		"claw",		DAM_SLASH	},  /*  5 */
    {	"blast",	"blast",	DAM_BASH	},
    {   "pound",	"pound",	DAM_BASH	},
    {	"crush",	"crush",	DAM_BASH	},
    {   "grep",		"grep",		DAM_SLASH	},
    {	"bite",		"bite",		DAM_PIERCE	},  /* 10 */
    {   "pierce",	"pierce",	DAM_PIERCE	},
    {   "suction",	"suction",	DAM_BASH	},
    {	"beating",	"beating",	DAM_BASH	},
    {   "digestion",	"digestion",	DAM_ACID	},
    {	"charge",	"charge",	DAM_BASH	},  /* 15 */
    { 	"slap",		"slap",		DAM_BASH	},
    {	"punch",	"punch",	DAM_BASH	},
    {	"wrath",	"wrath",	DAM_ENERGY	},
    {	"magic",	"magic",	DAM_ENERGY	},
    {   "divine",	"divine power",	DAM_HOLY	},  /* 20 */
    {	"cleave",	"cleave",	DAM_SLASH	},
    {	"scratch",	"scratch",	DAM_PIERCE	},
    {   "peck",		"peck",		DAM_PIERCE	},
    {   "peckb",	"peck",		DAM_BASH	},
    {   "chop",		"chop",		DAM_SLASH	},  /* 25 */
    {   "sting",	"sting",	DAM_PIERCE	},
    {   "smash",	 "smash",	DAM_BASH	},
    {   "shbite",	"shocking bite",DAM_LIGHTNING	},
    {	"flbite",	"flaming bite", DAM_FIRE	},
    {	"frbite",	"freezing bite", DAM_COLD	},  /* 30 */
    {	"acbite",	"acidic bite", 	DAM_ACID	},
    {	"chomp",	"chomp",	DAM_PIERCE	},
    {  	"drain",	"life drain",	DAM_NEGATIVE	},
    {   "thrust",	"thrust",	DAM_PIERCE	},
    {   "slime",	"slime",	DAM_ACID	},
    {	"shock",	"shock",	DAM_LIGHTNING	},
    {   "thwack",	"thwack",	DAM_BASH	},
    {   "hamster",	"hamster",	DAM_BASH	},
    {   "flame",	"flame",	DAM_FIRE	},
    {   "chill",	"chill",	DAM_COLD	},
    {   NULL,		NULL,		0		}
};

/* race table */
const 	struct	race_type	race_table	[]		=
{
/*
    {
	name,		pc_race?,
	act bits,	aff_by bits,	off bits,
	imm,		res,		vuln,
	form,		parts 
    },
*/
    { "unique",		FALSE, 0, 0, 0, 0, 0, 0, 0, 0 },


    { 
	"jezram",		TRUE, 
	0,		0, 		0,
	0, 		0,		0,
	A|H|M|V,	A|B|C|D|E|F|G|H|I|J|K
    },

    {
	"kang",			TRUE,
	0,		0,	0,
	0,		0,	0,
	A|H|M|V,	A|B|C|D|E|F|G|H|I|J|K
    },

    {
	"sethuut",		TRUE,
	0,		0,	0,
	0,	        0,      0,
	A|H|M|V,	A|B|C|D|E|F|G|H|I|J|K
    },

    {
        "sylvan",                 TRUE,
        0,              AFF_INFRARED|AFF_DETECT_HIDDEN,    0,
        0,              0,       0,
        A|H|M|V,        A|B|C|D|E|F|G|H|I|J|K
    },

    {
        "thstaar",                TRUE,
        0,              AFF_INFRARED,         0,
        0,              0,            0,
        A|H|M|V,        A|B|C|D|E|F|G|H|I|J|K
    },

    {
        "hobbit",               TRUE,
        0,              AFF_HIDE,             0,
        0,              RES_COLD,            VULN_FIRE,
        A|H|M|V,        A|B|C|D|E|F|G|H|I|J|K

    },
    
    {
        "saurig",               TRUE,
         0,              0,             0,
         0,              0,             0,
         A|H|M|V,        A|B|C|D|E|F|G|H|I|J|K
    },
    
 
    {
        "nrsang",                TRUE,
         0,              AFF_DARK_VISION,              0,
         0,              0,              VULN_FIRE,
         A|H|M|V,        A|B|C|D|E|F|G|H|I|J|K
    },

    {
	"bat",			FALSE,
	0,		AFF_FLYING|AFF_DARK_VISION,	OFF_DODGE|OFF_FAST,
	0,		0,		VULN_LIGHT,
	A|G|V,		A|C|D|E|F|H|J|K|P
    },

    {
	"bear",			FALSE,
	0,		0,	OFF_CRUSH|OFF_DISARM|OFF_BERSERK,
	0,		RES_BASH|RES_COLD,	0,
	A|G|V,		A|B|C|D|E|F|H|J|K|U|V
    },

    {
	"cat",			FALSE,
	0,		AFF_DARK_VISION,	OFF_FAST|OFF_DODGE,
	0,		0,		0,
	A|G|V,		A|C|D|E|F|H|J|K|Q|U|V
    },

    {
	"centipede",		FALSE,
	0,		AFF_DARK_VISION,	0,
	0,		RES_PIERCE|RES_COLD,	VULN_BASH,
 	A|B|G|O,		A|C|K	
    },

    {
	"dog",			FALSE,
	0,		0,		OFF_FAST,
	0,		0,		0,
	A|G|V,		A|C|D|E|F|H|J|K|U|V
    },

    {
	"doll",			FALSE,
	0,		0,		0,
	IMM_COLD|IMM_POISON|IMM_HOLY|IMM_NEGATIVE|IMM_MENTAL|IMM_DISEASE
	|IMM_DROWNING,	RES_BASH|RES_LIGHT,
	VULN_SLASH|VULN_FIRE|VULN_ACID|VULN_LIGHTNING|VULN_ENERGY,
	E|J|M|cc,	A|B|C|G|H|K
    },

    { 	"dragon", 		FALSE, 
	0, 			AFF_INFRARED|AFF_FLYING,0,	
	0,			RES_FIRE|RES_BASH|RES_CHARM, 
	VULN_PIERCE|VULN_COLD,
	A|H|Z,		A|C|D|E|F|G|H|I|J|K|P|Q|U|V|X
    },

    {
	"fido",			FALSE,
	0,		0,		OFF_DODGE|ASSIST_RACE,
	0,		0,			VULN_MAGIC,
	A|B|G|V,	A|C|D|E|F|H|J|K|Q|V
    },		
   
    {
	"fox",			FALSE,
	0,		AFF_DARK_VISION,	OFF_FAST|OFF_DODGE,
	0,		0,		0,
	A|G|V,		A|C|D|E|F|H|J|K|Q|V
    },

    {
	"goblin",		FALSE,
	0,		AFF_INFRARED,	0,
	0,		RES_DISEASE,	VULN_MAGIC,
	A|H|M|V,	A|B|C|D|E|F|G|H|I|J|K
    },

    {
	"hobgoblin",		FALSE,
	0,		AFF_INFRARED,	0,
	0,		RES_DISEASE|RES_POISON,	0,
	A|H|M|V,        A|B|C|D|E|F|G|H|I|J|K|Y
    },

    {
	"kobold",		FALSE,
	0,		AFF_INFRARED,	0,
	0,		RES_POISON,	VULN_MAGIC,
	A|B|H|M|V,	A|B|C|D|E|F|G|H|I|J|K|Q
    },

    {
	"lizard",		FALSE,
	0,		0,	0,
	0,		RES_POISON,	VULN_COLD,
	A|G|X|cc,	A|C|D|E|F|H|K|Q|V
    },

    {
	"modron",		FALSE,
	0,		AFF_INFRARED,	ASSIST_RACE|ASSIST_ALIGN,
	IMM_CHARM|IMM_DISEASE|IMM_MENTAL|IMM_HOLY|IMM_NEGATIVE,
			RES_FIRE|RES_COLD|RES_ACID,	0,
	H,		A|B|C|G|H|J|K
    },

    {
	"orc",			FALSE,
	0,		AFF_INFRARED,	0,
	0,		RES_DISEASE,	VULN_LIGHT,
	A|H|M|V,	A|B|C|D|E|F|G|H|I|J|K
    },

    {
	"pig",			FALSE,
	0,		0,		0,
	0,		0,		0,
	A|G|V,	 	A|C|D|E|F|H|J|K
    },	

    {
	"rabbit",		FALSE,
	0,		0,		OFF_DODGE|OFF_FAST,
	0,		0,		0,
	A|G|V,		A|C|D|E|F|H|J|K
    },
    
    {
	"school monster",	FALSE,
	ACT_NOALIGN,		0,		0,
	IMM_CHARM|IMM_SUMMON,	0,		VULN_MAGIC,
	A|M|V,		A|B|C|D|E|F|H|J|K|Q|U
    },	

    {
	"snake",		FALSE,
	0,		0,		0,
	0,		RES_POISON,	VULN_COLD,
	A|G|X|Y|cc,	A|D|E|F|K|L|Q|V|X
    },
 
    {
	"song bird",		FALSE,
	0,		AFF_FLYING,		OFF_FAST|OFF_DODGE,
	0,		0,		0,
	A|G|W,		A|C|D|E|F|H|K|P
    },

    {
	"troll",		FALSE,
	0,		AFF_REGENERATION|AFF_INFRARED|AFF_DETECT_HIDDEN,
	OFF_BERSERK,
 	0,	RES_CHARM|RES_BASH,	VULN_FIRE|VULN_ACID,
	A|B|H|M|V,		A|B|C|D|E|F|G|H|I|J|K|U|V
    },

    {
	"water fowl",		FALSE,
	0,		AFF_SWIM|AFF_FLYING,	0,
	0,		RES_DROWNING,		0,
	A|G|W,		A|C|D|E|F|H|K|P
    },		
  
    {
	"wolf",			FALSE,
	0,		AFF_DARK_VISION,	OFF_FAST|OFF_DODGE,
	0,		0,		0,	
	A|G|V,		A|C|D|E|F|J|K|Q|V
    },

    {
	"wyvern",		FALSE,
	0,		AFF_FLYING|AFF_DETECT_INVIS|AFF_DETECT_HIDDEN,
	OFF_BASH|OFF_FAST|OFF_DODGE,
	IMM_POISON,	0,	VULN_LIGHT,
	A|B|G|Z,		A|C|D|E|F|H|J|K|Q|V|X
    },

    {
	"unique",		FALSE,
	0,		0,		0,
	0,		0,		0,		
	0,		0
    },


    {
	NULL, 0, 0, 0, 0, 0, 0
    }
};

const	struct	pc_race_type	pc_race_table	[]	=
{
    { "null race", "", 0, { 100, 100, 100, 100 },
      { "" }, { 13, 13, 13, 13, 13 }, { 18, 18, 18, 18, 18 }, 0 },
 
/*
    {
	"race name", 	short name, 	points,	{ class multipliers },
	{ bonus skills },
	{ base stats },		{ max stats },		size 
    },
*/
    {
	"jez",	"Jezram",	3,
        { 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200 },
	{ "drag" },
        { 12, 12, 12, 12, 12 }, { 25, 25, 25, 25, 25 }, SIZE_MEDIUM
    },

    { 	
	"kan",		"Kang",	3,
        { 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200 },
	{ "drag" },
        { 12, 12, 12, 12, 12 }, { 25, 25, 25, 25, 25 },SIZE_MEDIUM
    },

    {
	"set",	"Sethuut",	3,
        { 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200, 200 },
	{ "drag" },
        { 12, 12, 12, 12, 12 }, { 25, 25, 25, 25, 25 },SIZE_MEDIUM
    },

    {
        "syl",          "Sylvan",          6,
        { 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300 },
        { "drag" },
        { 12, 12, 12, 12, 12 }, { 25, 25, 25, 25, 25},SIZE_MEDIUM
    },    
    
    {    
        "ths",         "Thstaar",         6,
        { 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300 },
        { "drag" },    
        { 12, 12, 12, 12, 12 }, { 25, 25, 25, 25, 25},SIZE_SMALL
    },

    {
        "hob",        "Hobbit",        6,
        { 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300 },
        { "drag" },   
        { 12, 12, 12, 12, 12 }, { 25, 25, 25, 25, 25},SIZE_SMALL
    },

    {
        "sau",        "Saurig",        6,
        { 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300 },
        { "drag" },
        { 12, 12, 12, 12, 12 }, { 25, 25, 25, 25, 25 },SIZE_LARGE
    },

    {
       "nrs",         "Nrsang",        6,
       { 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300, 300 },
       { "drag" },
       { 12, 12, 12, 12, 12 }, { 25, 25, 25, 25, 25 },SIZE_MEDIUM
    },

};

	
      	

/*
 * Class table.
 */
const	struct	class_type	class_table	[MAX_CLASS]	=
{
    {
        "adventurer", "Adv",  STAT_STR,  OBJ_VNUM_SCHOOL_DAGGER,
	{ 3008 },  75,  20, 6,  6,  8, TRUE,
	"adv basics", "adv default"
    },

    {
        "arcane", "Arc",  STAT_INT,  OBJ_VNUM_SCHOOL_DAGGER,
	{ 3008 },  75,  20, 6,  6,  8, TRUE,
	"mage basics", "mage default"
    },

    {
        "shaman", "Sha",  STAT_WIS,  OBJ_VNUM_SCHOOL_MACE,
	{ 3008 },  75,  20, 2,  7, 10, TRUE,
	"cleric basics", "cleric default"
    },

    {
        "rogue", "Rog",  STAT_DEX,  OBJ_VNUM_SCHOOL_DAGGER,
	{ 3008 },  75,  20,  -4,  8, 13, TRUE,
	"thief basics", "thief default"
    },

    {
	"Martial", "Mar",  STAT_STR,  OBJ_VNUM_SCHOOL_SWORD,
	{ 3008 },  75,  20,  -10,  11, 15, TRUE,
	"warrior basics", "warrior default"
    },

    {
       "cavalier", "Cav",  STAT_WIS,  OBJ_VNUM_SCHOOL_POLEARM,
        { 3008 },  75,  20,  -10,  11, 15, TRUE,
        "warrior basics", "cavalier default",
    }

};



/*
 * Titles.
 */
char *	const			title_table	[MAX_CLASS][MAX_LEVEL+1][2] =
{
    {
	{ "Man",			"Woman"				},

	{ "Initiate",	                "Initiate"		        },
	{ "Apprentice",		        "Apprentice"			},
	{ "Scholar",     		"Scholar"	       	        },
	{ "Delver in Spells",		"Delver in Spells"		},
	{ "Carver of Stone",		"Carver of Stone"		},

	{ "Scribe of Stone",		"Scribess of Stone"		},
	{ "Seer",			"Seeress"			},
	{ "Sage",			"Sage"				},
	{ "Illuminator",		"Illuminator"			},
	{ "Abjurer",			"Abjuress"			},

	{ "Invoker",			"Invoker"			},
	{ "Invoker",			"Invoker"			},
	{ "Invoker",			"Invoker"			},
	{ "Invoker",			"Invoker"                       },
	{ "Creator",			"Creator"			},

	{ "Savant",			"Savant"			},
	{ "Savant",			"Savant"                        },
	{ "Wizard",			"Wizard"			},
	{ "Sorcerers Scribe",	        "Sorcerers Scribe"              },
	{ "Sorcerer",			"Sorceress"			},

	{ "Elder Sorcerer",		"Elder Sorceress"		},
	{ "Grand Sorcerer",		"Grand Sorceress"		},
	{ "Great Sorcerer",		"Great Sorceress"		},
	{ "Maker of Forces",            "Maker of Forces"               },
	{ "Greater Maker of Forces",	"Greater Maker of Forces"       },

	{ "Maker of Stones",		"Maker of Stones",		},
	{ "Maker of Potions",		"Maker of Potions",		},
	{ "Maker of Scrolls",		"Maker of Scrolls",		},
	{ "Maker of Wands",		"Maker of Wands",		},
	{ "Maker of Staves",		"Maker of Staves",		},

	{ "Demon Summoner",		"Demon Summoner"		},
	{ "Greater Demon Summoner",	"Greater Demon Summoner"	},
	{ "Dragon Charmer",		"Dragon Charmer"		},
	{ "Greater Dragon Charmer",	"Greater Dragon Charmer"	},
	{ "Master of all Magic",	"Master of all Magic"		},

 	{ "Master Mage",		"Master Mage"			},
        { "Master Mage",                "Master Mage"                   },
        { "Master Mage",                "Master Mage"                   },
        { "Master Mage",                "Master Mage"                   },
        { "Master Mage",                "Master Mage"                   },

        { "Master Mage",                "Master Mage"                   },
        { "Master Mage",                "Master Mage"                   },
        { "Master Mage",                "Master Mage"                   },
        { "Master Mage",                "Master Mage"                   },
        { "Master Mage",                "Master Mage"                   },

        { "Master Mage",                "Master Mage"                   },
        { "Master Mage",                "Master Mage"                   },
        { "Master Mage",                "Master Mage"                   },
        { "Master Mage",                "Master Mage"                   },
        { "Master Mage",                "Master Mage"                   },

	{ "Mage Hero",			"Mage Heroine"			},
	{ "Avatar of Magic",		"Avatar of Magic"		},
	{ "Angel of Magic",		"Angel of Magic"		},
	{ "Demigod of Magic",		"Demigoddess of Magic"		},
	{ "Immortal of Magic",		"Immortal of Magic"		},
	{ "God of Magic",		"Goddess of Magic"		},
	{ "Deity of Magic",		"Deity of Magic"		},
	{ "Supremity of Magic",		"Supremity of Magic"		},
	{ "Creator",			"Creator"			},
	{ "Implementor",		"Implementress"			}
    },

    {
	{ "Man",			"Woman"				},

	{ "Believer",			"Believer"			},
	{ "Attendant",			"Attendant"			},
	{ "Acolyte",			"Acolyte"			},
	{ "Novice",			"Novice"			},
	{ "Missionary",			"Missionary"			},

	{ "Adept",			"Adept"				},
	{ "Deacon",			"Deaconess"			},
	{ "Vicar",			"Vicaress"			},
	{ "Priest",			"Priestess"			},
	{ "Minister",			"Lady Minister"			},

	{ "Canon",			"Canon"				},
	{ "Levite",			"Levitess"			},
	{ "Curate",			"Curess"			},
	{ "Monk",			"Nun"				},
	{ "Healer",			"Healess"			},

	{ "Chaplain",			"Chaplain"			},
	{ "Expositor",			"Expositress"			},
	{ "Bishop",			"Bishop"			},
	{ "Arch Bishop",		"Arch Lady of the Church"	},
	{ "Patriarch",			"Matriarch"			},

	{ "Elder Patriarch",		"Elder Matriarch"		},
	{ "Grand Patriarch",		"Grand Matriarch"		},
	{ "Great Patriarch",		"Great Matriarch"		},
	{ "Demon Killer",		"Demon Killer"			},
	{ "Greater Demon Killer",	"Greater Demon Killer"		},

	{ "Cardinal of the Sea",	"Cardinal of the Sea"		},
	{ "Cardinal of the Earth",	"Cardinal of the Earth"		},
	{ "Cardinal of the Air",	"Cardinal of the Air"		},
	{ "Cardinal of the Ether",	"Cardinal of the Ether"		},
	{ "Cardinal of the Heavens",	"Cardinal of the Heavens"	},

	{ "Avatar of an Immortal",	"Avatar of an Immortal"		},
	{ "Avatar of a Deity",		"Avatar of a Deity"		},
	{ "Avatar of a Supremity",	"Avatar of a Supremity"		},
	{ "Avatar of an Implementor",	"Avatar of an Implementor"	},
	{ "Master of all Divinity",	"Mistress of all Divinity"	},

	{ "Master Cleric",		"Master Cleric"			},
	{ "Master Cleric",		"Master Cleric"			},
	{ "Master Cleric",		"Master Cleric"			},
	{ "Master Cleric",		"Master Cleric"			},	
	{ "Master Cleric",		"Master Cleric"			},

	{ "Master Cleric",		"Master Cleric"			},
	{ "Master Cleric",		"Master Cleric"			},
	{ "Master Cleric",		"Master Cleric"			},
	{ "Master Cleric",		"Master Cleric"			},
	{ "Master Cleric",		"Master Cleric"			},

	{ "Master Cleric",		"Master Cleric"			},
	{ "Master Cleric",		"Master Cleric"			},
	{ "Master Cleric",		"Master Cleric"			},
	{ "Master Cleric",		"Master Cleric"			},
	{ "Master Cleric",		"Master Cleric"			},

	{ "Holy Hero",			"Holy Heroine"			},
	{ "Holy Avatar",		"Holy Avatar"			},
	{ "Angel",			"Angel"				},
	{ "Demigod",			"Demigoddess",			},
	{ "Immortal",			"Immortal"			},
	{ "God",			"Goddess"			},
	{ "Deity",			"Deity"				},
	{ "Supreme Master",		"Supreme Mistress"		},
        { "Creator",                    "Creator"                       },
	{ "Implementor",		"Implementress"			}
    },

    {
	{ "Man",			"Woman"				},

	{ "Pilferer",			"Pilferess"			},
	{ "Footpad",			"Footpad"			},
	{ "Filcher",			"Filcheress"			},
	{ "Pick-Pocket",		"Pick-Pocket"			},
	{ "Sneak",			"Sneak"				},

	{ "Pincher",			"Pincheress"			},
	{ "Cut-Purse",			"Cut-Purse"			},
	{ "Snatcher",			"Snatcheress"			},
	{ "Sharper",			"Sharpress"			},
	{ "Rogue",			"Rogue"				},

	{ "Robber",			"Robber"			},
	{ "Magsman",			"Magswoman"			},
	{ "Highwayman",			"Highwaywoman"			},
	{ "Burglar",			"Burglaress"			},
	{ "Thief",			"Thief"				},

	{ "Knifer",			"Knifer"			},
	{ "Quick-Blade",		"Quick-Blade"			},
	{ "Killer",			"Murderess"			},
	{ "Brigand",			"Brigand"			},
	{ "Cut-Throat",			"Cut-Throat"			},

	{ "Spy",			"Spy"				},
	{ "Grand Spy",			"Grand Spy"			},
	{ "Master Spy",			"Master Spy"			},
	{ "Assassin",			"Assassin"			},
	{ "Greater Assassin",		"Greater Assassin"		},

	{ "Master of Vision",		"Mistress of Vision"		},
	{ "Master of Hearing",		"Mistress of Hearing"		},
	{ "Master of Smell",		"Mistress of Smell"		},
	{ "Master of Taste",		"Mistress of Taste"		},
	{ "Master of Touch",		"Mistress of Touch"		},

	{ "Crime Lord",			"Crime Mistress"		},
	{ "Infamous Crime Lord",	"Infamous Crime Mistress"	},
	{ "Greater Crime Lord",		"Greater Crime Mistress"	},
	{ "Master Crime Lord",		"Master Crime Mistress"		},
	{ "Godfather",			"Godmother"			},

        { "Master Thief",               "Master Thief"                  },
        { "Master Thief",               "Master Thief"                  },
        { "Master Thief",               "Master Thief"                  },
        { "Master Thief",               "Master Thief"                  },
        { "Master Thief",               "Master Thief"                  },

        { "Master Thief",               "Master Thief"                  },
        { "Master Thief",               "Master Thief"                  },
        { "Master Thief",               "Master Thief"                  },
        { "Master Thief",               "Master Thief"                  },
        { "Master Thief",               "Master Thief"                  },

        { "Master Thief",               "Master Thief"                  },
        { "Master Thief",               "Master Thief"                  },
        { "Master Thief",               "Master Thief"                  },
        { "Master Thief",               "Master Thief"                  },
        { "Master Thief",               "Master Thief"                  },

	{ "Assassin Hero",		"Assassin Heroine"		},
	{ "Avatar of Death",		"Avatar of Death",		},
	{ "Angel of Death",		"Angel of Death"		},
	{ "Demigod of Assassins",	"Demigoddess of Assassins"	},
	{ "Immortal Assasin",		"Immortal Assassin"		},
	{ "God of Assassins",		"God of Assassins",		},
	{ "Deity of Assassins",		"Deity of Assassins"		},
	{ "Supreme Master",		"Supreme Mistress"		},
        { "Creator",                    "Creator"                       },
	{ "Implementor",		"Implementress"			}
    },

    {
	{ "Man",			"Woman"				},

	{ "Swordpupil",			"Swordpupil"			},
	{ "Recruit",			"Recruit"			},
	{ "Sentry",			"Sentress"			},
	{ "Fighter",			"Fighter"			},
	{ "Soldier",			"Soldier"			},

	{ "Warrior",			"Warrior"			},
	{ "Veteran",			"Veteran"			},
	{ "Swordsman",			"Swordswoman"			},
	{ "Fencer",			"Fenceress"			},
	{ "Combatant",			"Combatess"			},

	{ "Hero",			"Heroine"			},
	{ "Myrmidon",			"Myrmidon"			},
	{ "Swashbuckler",		"Swashbuckleress"		},
	{ "Mercenary",			"Mercenaress"			},
	{ "Swordmaster",		"Swordmistress"			},

	{ "Lieutenant",			"Lieutenant"			},
	{ "Champion",			"Lady Champion"			},
	{ "Dragoon",			"Lady Dragoon"			},
	{ "Cavalier",			"Lady Cavalier"			},
	{ "Knight",			"Lady Knight"			},

	{ "Grand Knight",		"Grand Knight"			},
	{ "Master Knight",		"Master Knight"			},
	{ "Paladin",			"Paladin"			},
	{ "Grand Paladin",		"Grand Paladin"			},
	{ "Demon Slayer",		"Demon Slayer"			},

	{ "Greater Demon Slayer",	"Greater Demon Slayer"		},
	{ "Dragon Slayer",		"Dragon Slayer"			},
	{ "Greater Dragon Slayer",	"Greater Dragon Slayer"		},
	{ "Underlord",			"Underlord"			},
	{ "Overlord",			"Overlord"			},

	{ "Baron of Thunder",		"Baroness of Thunder"		},
	{ "Baron of Storms",		"Baroness of Storms"		},
	{ "Baron of Tornadoes",		"Baroness of Tornadoes"		},
	{ "Baron of Hurricanes",	"Baroness of Hurricanes"	},
	{ "Baron of Meteors",		"Baroness of Meteors"		},

	{ "Master Warrior",		"Master Warrior"		},
        { "Master Warrior",             "Master Warrior"                },
        { "Master Warrior",             "Master Warrior"                },
        { "Master Warrior",             "Master Warrior"                },
        { "Master Warrior",             "Master Warrior"                },

        { "Master Warrior",             "Master Warrior"                },
        { "Master Warrior",             "Master Warrior"                },
        { "Master Warrior",             "Master Warrior"                },
        { "Master Warrior",             "Master Warrior"                },
        { "Master Warrior",             "Master Warrior"                },

        { "Master Warrior",             "Master Warrior"                },
        { "Master Warrior",             "Master Warrior"                },
        { "Master Warrior",             "Master Warrior"                },
        { "Master Warrior",             "Master Warrior"                },
        { "Master Warrior",             "Master Warrior"                },

	{ "Knight Hero",		"Knight Heroine"		},
	{ "Avatar of War",		"Avatar of War"			},
	{ "Angel of War",		"Angel of War"			},
	{ "Demigod of War",		"Demigoddess of War"		},
	{ "Immortal Warlord",		"Immortal Warlord"		},
	{ "God of War",			"God of War"			},
	{ "Deity of War",		"Deity of War"			},
	{ "Supreme Master of War",	"Supreme Mistress of War"	},
        { "Creator",                    "Creator"                       },
	{ "Implementor",		"Implementress"			}
    },

    {
        { "Man",                        "Woman",                        },

        { "Squire",                     "Squire",                       },
        { "Squire",                     "Squire",                       },
        { "Squire",                     "Squire",                       },
        { "Squire",                     "Squire",                       },

        { "Footman",                    "Footwoman",                    },
        { "Footman",                    "Footwoman",                    },
        { "Footman",                    "Footwoman",                    },
        { "Footman",                    "Footwoman",                    },
        { "Footman",                    "Footwoman",                    },

        { "Veteran",                    "Veteran",                      },
        { "Veteran",                    "Veteran",                      },
        { "Swordsman",                  "Swordswoman",                  },
        { "Swordsman",                  "Swordswoman",                  },
        { "Champion",                   "Champion",                     },

        { "Champion",                   "Champion",                     },
        { "Gallant",                    "Gallant",                      },
        { "Gallant",                    "Gallant",                      },
        { "Keeper",                     "Keeper",                       },
        { "Keeper",                     "Keeper",                       },

        { "Protector",                  "Protector",                    },
        { "Protector",                  "Protector",                    },
        { "Defender",                   "Defender",                     },
        { "Defender",                   "Defender",                     },
        { "Warder",                     "Warder",                       },
       
        { "Warder",                     "Warder",                       },
        { "Warder",                     "Warder",                       },
        { "Guardian",                   "Guardian",                     },
        { "Guardian",                   "Guardian",                     },
        { "Guardian",                   "Guardian",                     },

        { "Chevalier",                  "Chevalier",                    },
        { "Chevalier",                  "Chevalier",                    },
        { "Chevalier",                  "Chevalier",                    },
        { "Justicar",                   "Justicar",                     },
        { "Justicar",                   "Justicar",                     },

        { "Paladin",                    "Paladin",                      },
        { "Paladin",                    "Paladin",                      },
        { "Paladin",                    "Paladin",                      },
        { "Paladin",                    "Paladin",                      },
        { "Avenger",                    "Avenger",                      },

        { "Holy Avenger",               "Holy Avenger",                 },
        { "Holy Avenger",               "Holy Avenger",                 },
        { "Holy Avenger",               "Holy Avenger",                 },
        { "Holy Avenger",               "Holy Avenger",                 },
        { "Holy Avenger",               "Holy Avenger",                 },

        { "Holy Avenger",               "Holy Avenger",                 },
        { "Holy Avenger",               "Holy Avenger",                 },
        { "Holy Avenger",               "Holy Avenger",                 },
        { "Holy Avenger",               "Holy Avenger",                 },
        { "Holy Avenger",               "Holy Avenger",                 },

        { "Grand Paladin",              "Grand Paladin",                },
        { "Avatar",                     "Avatar",                       },
        { "Angel Of Light",             "Angel Of Light",               },
        { "DemiGod",                    "DemiGod",                      },
        { "Immortal",                   "Immortal",                     },
        { "God",                        "God",                          },
        { "Deity",                      "Deity",                        },
        { "Supreme",                    "Supreme",                      },
        { "Creator",                    "Creator",                      },
        { "Implementor",                "Implementress",                }
    },

    {
	{ "Man",			"Woman"				},

	{ "Pilferer",			"Pilferess"			},
	{ "Footpad",			"Footpad"			},
	{ "Filcher",			"Filcheress"			},
	{ "Pick-Pocket",		"Pick-Pocket"			},
	{ "Sneak",			"Sneak"				},

	{ "Pincher",			"Pincheress"			},
	{ "Cut-Purse",			"Cut-Purse"			},
	{ "Snatcher",			"Snatcheress"			},
	{ "Sharper",			"Sharpress"			},
	{ "Rogue",			"Rogue"				},

	{ "Robber",			"Robber"			},
	{ "Magsman",			"Magswoman"			},
	{ "Highwayman",			"Highwaywoman"			},
	{ "Burglar",			"Burglaress"			},
	{ "Thief",			"Thief"				},

	{ "Knifer",			"Knifer"			},
	{ "Quick-Blade",		"Quick-Blade"			},
	{ "Killer",			"Murderess"			},
	{ "Brigand",			"Brigand"			},
	{ "Cut-Throat",			"Cut-Throat"			},

	{ "Spy",			"Spy"				},
	{ "Grand Spy",			"Grand Spy"			},
	{ "Master Spy",			"Master Spy"			},
	{ "Assassin",			"Assassin"			},
	{ "Greater Assassin",		"Greater Assassin"		},

	{ "Master of Vision",		"Mistress of Vision"		},
	{ "Master of Hearing",		"Mistress of Hearing"		},
	{ "Master of Smell",		"Mistress of Smell"		},
	{ "Master of Taste",		"Mistress of Taste"		},
	{ "Master of Touch",		"Mistress of Touch"		},

	{ "Crime Lord",			"Crime Mistress"		},
	{ "Infamous Crime Lord",	"Infamous Crime Mistress"	},
	{ "Greater Crime Lord",		"Greater Crime Mistress"	},
	{ "Master Crime Lord",		"Master Crime Mistress"		},
	{ "Godfather",			"Godmother"			},

        { "Master Thief",               "Master Thief"                  },
        { "Master Thief",               "Master Thief"                  },
        { "Master Thief",               "Master Thief"                  },
        { "Master Thief",               "Master Thief"                  },
        { "Master Thief",               "Master Thief"                  },

        { "Master Thief",               "Master Thief"                  },
        { "Master Thief",               "Master Thief"                  },
        { "Master Thief",               "Master Thief"                  },
        { "Master Thief",               "Master Thief"                  },
        { "Master Thief",               "Master Thief"                  },

        { "Master Thief",               "Master Thief"                  },
        { "Master Thief",               "Master Thief"                  },
        { "Master Thief",               "Master Thief"                  },
        { "Master Thief",               "Master Thief"                  },
        { "Master Thief",               "Master Thief"                  },

	{ "Assassin Hero",		"Assassin Heroine"		},
	{ "Avatar of Death",		"Avatar of Death",		},
	{ "Angel of Death",		"Angel of Death"		},
	{ "Demigod of Assassins",	"Demigoddess of Assassins"	},
	{ "Immortal Assasin",		"Immortal Assassin"		},
	{ "God of Assassins",		"God of Assassins",		},
	{ "Deity of Assassins",		"Deity of Assassins"		},
	{ "Supreme Master",		"Supreme Mistress"		},
        { "Creator",                    "Creator"                       },
	{ "Implementor",		"Implementress"			}
    },

    {
	{ "Man",			"Woman"				},

	{ "Believer",			"Believer"			},
	{ "Attendant",			"Attendant"			},
	{ "Acolyte",			"Acolyte"			},
	{ "Novice",			"Novice"			},
	{ "Missionary",			"Missionary"			},

	{ "Adept",			"Adept"				},
	{ "Deacon",			"Deaconess"			},
	{ "Vicar",			"Vicaress"			},
	{ "Priest",			"Priestess"			},
	{ "Minister",			"Lady Minister"			},

	{ "Canon",			"Canon"				},
	{ "Levite",			"Levitess"			},
	{ "Curate",			"Curess"			},
	{ "Monk",			"Nun"				},
	{ "Healer",			"Healess"			},

	{ "Chaplain",			"Chaplain"			},
	{ "Expositor",			"Expositress"			},
	{ "Bishop",			"Bishop"			},
	{ "Arch Bishop",		"Arch Lady of the Church"	},
	{ "Patriarch",			"Matriarch"			},

	{ "Elder Patriarch",		"Elder Matriarch"		},
	{ "Grand Patriarch",		"Grand Matriarch"		},
	{ "Great Patriarch",		"Great Matriarch"		},
	{ "Demon Killer",		"Demon Killer"			},
	{ "Greater Demon Killer",	"Greater Demon Killer"		},

	{ "Cardinal of the Sea",	"Cardinal of the Sea"		},
	{ "Cardinal of the Earth",	"Cardinal of the Earth"		},
	{ "Cardinal of the Air",	"Cardinal of the Air"		},
	{ "Cardinal of the Ether",	"Cardinal of the Ether"		},
	{ "Cardinal of the Heavens",	"Cardinal of the Heavens"	},

	{ "Avatar of an Immortal",	"Avatar of an Immortal"		},
	{ "Avatar of a Deity",		"Avatar of a Deity"		},
	{ "Avatar of a Supremity",	"Avatar of a Supremity"		},
	{ "Avatar of an Implementor",	"Avatar of an Implementor"	},
	{ "Master of all Divinity",	"Mistress of all Divinity"	},

	{ "Master Cleric",		"Master Cleric"			},
	{ "Master Cleric",		"Master Cleric"			},
	{ "Master Cleric",		"Master Cleric"			},
	{ "Master Cleric",		"Master Cleric"			},	
	{ "Master Cleric",		"Master Cleric"			},

	{ "Master Cleric",		"Master Cleric"			},
	{ "Master Cleric",		"Master Cleric"			},
	{ "Master Cleric",		"Master Cleric"			},
	{ "Master Cleric",		"Master Cleric"			},
	{ "Master Cleric",		"Master Cleric"			},

	{ "Master Cleric",		"Master Cleric"			},
	{ "Master Cleric",		"Master Cleric"			},
	{ "Master Cleric",		"Master Cleric"			},
	{ "Master Cleric",		"Master Cleric"			},
	{ "Master Cleric",		"Master Cleric"			},

	{ "Holy Hero",			"Holy Heroine"			},
	{ "Holy Avatar",		"Holy Avatar"			},
	{ "Angel",			"Angel"				},
	{ "Demigod",			"Demigoddess",			},
	{ "Immortal",			"Immortal"			},
	{ "God",			"Goddess"			},
	{ "Deity",			"Deity"				},
	{ "Supreme Master",		"Supreme Mistress"		},
        { "Creator",                    "Creator"                       },
	{ "Implementor",		"Implementress"			}
    },

    {
	{ "Man",			"Woman"				},

	{ "Swordpupil",			"Swordpupil"			},
	{ "Recruit",			"Recruit"			},
	{ "Sentry",			"Sentress"			},
	{ "Fighter",			"Fighter"			},
	{ "Soldier",			"Soldier"			},

	{ "Warrior",			"Warrior"			},
	{ "Veteran",			"Veteran"			},
	{ "Swordsman",			"Swordswoman"			},
	{ "Fencer",			"Fenceress"			},
	{ "Combatant",			"Combatess"			},

	{ "Hero",			"Heroine"			},
	{ "Myrmidon",			"Myrmidon"			},
	{ "Swashbuckler",		"Swashbuckleress"		},
	{ "Mercenary",			"Mercenaress"			},
	{ "Swordmaster",		"Swordmistress"			},

	{ "Lieutenant",			"Lieutenant"			},
	{ "Champion",			"Lady Champion"			},
	{ "Dragoon",			"Lady Dragoon"			},
	{ "Cavalier",			"Lady Cavalier"			},
	{ "Knight",			"Lady Knight"			},

	{ "Grand Knight",		"Grand Knight"			},
	{ "Master Knight",		"Master Knight"			},
	{ "Paladin",			"Paladin"			},
	{ "Grand Paladin",		"Grand Paladin"			},
	{ "Demon Slayer",		"Demon Slayer"			},

	{ "Greater Demon Slayer",	"Greater Demon Slayer"		},
	{ "Dragon Slayer",		"Dragon Slayer"			},
	{ "Greater Dragon Slayer",	"Greater Dragon Slayer"		},
	{ "Underlord",			"Underlord"			},
	{ "Overlord",			"Overlord"			},

	{ "Baron of Thunder",		"Baroness of Thunder"		},
	{ "Baron of Storms",		"Baroness of Storms"		},
	{ "Baron of Tornadoes",		"Baroness of Tornadoes"		},
	{ "Baron of Hurricanes",	"Baroness of Hurricanes"	},
	{ "Baron of Meteors",		"Baroness of Meteors"		},

	{ "Master Warrior",		"Master Warrior"		},
        { "Master Warrior",             "Master Warrior"                },
        { "Master Warrior",             "Master Warrior"                },
        { "Master Warrior",             "Master Warrior"                },
        { "Master Warrior",             "Master Warrior"                },

        { "Master Warrior",             "Master Warrior"                },
        { "Master Warrior",             "Master Warrior"                },
        { "Master Warrior",             "Master Warrior"                },
        { "Master Warrior",             "Master Warrior"                },
        { "Master Warrior",             "Master Warrior"                },

        { "Master Warrior",             "Master Warrior"                },
        { "Master Warrior",             "Master Warrior"                },
        { "Master Warrior",             "Master Warrior"                },
        { "Master Warrior",             "Master Warrior"                },
        { "Master Warrior",             "Master Warrior"                },

	{ "Knight Hero",		"Knight Heroine"		},
	{ "Avatar of War",		"Avatar of War"			},
	{ "Angel of War",		"Angel of War"			},
	{ "Demigod of War",		"Demigoddess of War"		},
	{ "Immortal Warlord",		"Immortal Warlord"		},
	{ "God of War",			"God of War"			},
	{ "Deity of War",		"Deity of War"			},
	{ "Supreme Master of War",	"Supreme Mistress of War"	},
        { "Creator",                    "Creator"                       },
	{ "Implementor",		"Implementress"			}
    },

    {
	{ "Man",			"Woman"				},

	{ "Swordpupil",			"Swordpupil"			},
	{ "Recruit",			"Recruit"			},
	{ "Sentry",			"Sentress"			},
	{ "Fighter",			"Fighter"			},
	{ "Soldier",			"Soldier"			},

	{ "Warrior",			"Warrior"			},
	{ "Veteran",			"Veteran"			},
	{ "Swordsman",			"Swordswoman"			},
	{ "Fencer",			"Fenceress"			},
	{ "Combatant",			"Combatess"			},

	{ "Hero",			"Heroine"			},
	{ "Myrmidon",			"Myrmidon"			},
	{ "Swashbuckler",		"Swashbuckleress"		},
	{ "Mercenary",			"Mercenaress"			},
	{ "Swordmaster",		"Swordmistress"			},

	{ "Lieutenant",			"Lieutenant"			},
	{ "Champion",			"Lady Champion"			},
	{ "Dragoon",			"Lady Dragoon"			},
	{ "Cavalier",			"Lady Cavalier"			},
	{ "Knight",			"Lady Knight"			},

	{ "Grand Knight",		"Grand Knight"			},
	{ "Master Knight",		"Master Knight"			},
	{ "Paladin",			"Paladin"			},
	{ "Grand Paladin",		"Grand Paladin"			},
	{ "Demon Slayer",		"Demon Slayer"			},

	{ "Greater Demon Slayer",	"Greater Demon Slayer"		},
	{ "Dragon Slayer",		"Dragon Slayer"			},
	{ "Greater Dragon Slayer",	"Greater Dragon Slayer"		},
	{ "Underlord",			"Underlord"			},
	{ "Overlord",			"Overlord"			},

	{ "Baron of Thunder",		"Baroness of Thunder"		},
	{ "Baron of Storms",		"Baroness of Storms"		},
	{ "Baron of Tornadoes",		"Baroness of Tornadoes"		},
	{ "Baron of Hurricanes",	"Baroness of Hurricanes"	},
	{ "Baron of Meteors",		"Baroness of Meteors"		},

	{ "Master Warrior",		"Master Warrior"		},
        { "Master Warrior",             "Master Warrior"                },
        { "Master Warrior",             "Master Warrior"                },
        { "Master Warrior",             "Master Warrior"                },
        { "Master Warrior",             "Master Warrior"                },

        { "Master Warrior",             "Master Warrior"                },
        { "Master Warrior",             "Master Warrior"                },
        { "Master Warrior",             "Master Warrior"                },
        { "Master Warrior",             "Master Warrior"                },
        { "Master Warrior",             "Master Warrior"                },

        { "Master Warrior",             "Master Warrior"                },
        { "Master Warrior",             "Master Warrior"                },
        { "Master Warrior",             "Master Warrior"                },
        { "Master Warrior",             "Master Warrior"                },
        { "Master Warrior",             "Master Warrior"                },

	{ "Knight Hero",		"Knight Heroine"		},
	{ "Avatar of War",		"Avatar of War"			},
	{ "Angel of War",		"Angel of War"			},
	{ "Demigod of War",		"Demigoddess of War"		},
	{ "Immortal Warlord",		"Immortal Warlord"		},
	{ "God of War",			"God of War"			},
	{ "Deity of War",		"Deity of War"			},
	{ "Supreme Master of War",	"Supreme Mistress of War"	},
        { "Creator",                    "Creator"                       },
	{ "Implementor",		"Implementress"			}
    },

    {
	{ "Man",			"Woman"				},

	{ "Apprentice of Magic",	"Apprentice of Magic"		},
	{ "Spell Student",		"Spell Student"			},
	{ "Scholar of Magic",		"Scholar of Magic"		},
	{ "Delver in Spells",		"Delveress in Spells"		},
	{ "Medium of Magic",		"Medium of Magic"		},

	{ "Scribe of Magic",		"Scribess of Magic"		},
	{ "Seer",			"Seeress"			},
	{ "Sage",			"Sage"				},
	{ "Illusionist",		"Illusionist"			},
	{ "Abjurer",			"Abjuress"			},

	{ "Invoker",			"Invoker"			},
	{ "Enchanter",			"Enchantress"			},
	{ "Conjurer",			"Conjuress"			},
	{ "Magician",			"Witch"				},
	{ "Creator",			"Creator"			},

	{ "Savant",			"Savant"			},
	{ "Magus",			"Craftess"			},
	{ "Wizard",			"Wizard"			},
	{ "Warlock",			"War Witch"			},
	{ "Sorcerer",			"Sorceress"			},

	{ "Elder Sorcerer",		"Elder Sorceress"		},
	{ "Grand Sorcerer",		"Grand Sorceress"		},
	{ "Great Sorcerer",		"Great Sorceress"		},
	{ "Golem Maker",		"Golem Maker"			},
	{ "Greater Golem Maker",	"Greater Golem Maker"		},

	{ "Maker of Stones",		"Maker of Stones",		},
	{ "Maker of Potions",		"Maker of Potions",		},
	{ "Maker of Scrolls",		"Maker of Scrolls",		},
	{ "Maker of Wands",		"Maker of Wands",		},
	{ "Maker of Staves",		"Maker of Staves",		},

	{ "Demon Summoner",		"Demon Summoner"		},
	{ "Greater Demon Summoner",	"Greater Demon Summoner"	},
	{ "Dragon Charmer",		"Dragon Charmer"		},
	{ "Greater Dragon Charmer",	"Greater Dragon Charmer"	},
	{ "Master of all Magic",	"Master of all Magic"		},

 	{ "Master Mage",		"Master Mage"			},
        { "Master Mage",                "Master Mage"                   },
        { "Master Mage",                "Master Mage"                   },
        { "Master Mage",                "Master Mage"                   },
        { "Master Mage",                "Master Mage"                   },

        { "Master Mage",                "Master Mage"                   },
        { "Master Mage",                "Master Mage"                   },
        { "Master Mage",                "Master Mage"                   },
        { "Master Mage",                "Master Mage"                   },
        { "Master Mage",                "Master Mage"                   },

        { "Master Mage",                "Master Mage"                   },
        { "Master Mage",                "Master Mage"                   },
        { "Master Mage",                "Master Mage"                   },
        { "Master Mage",                "Master Mage"                   },
        { "Master Mage",                "Master Mage"                   },

	{ "Mage Hero",			"Mage Heroine"			},
	{ "Avatar of Magic",		"Avatar of Magic"		},
	{ "Angel of Magic",		"Angel of Magic"		},
	{ "Demigod of Magic",		"Demigoddess of Magic"		},
	{ "Immortal of Magic",		"Immortal of Magic"		},
	{ "God of Magic",		"Goddess of Magic"		},
	{ "Deity of Magic",		"Deity of Magic"		},
	{ "Supremity of Magic",		"Supremity of Magic"		},
	{ "Creator",			"Creator"			},
	{ "Implementor",		"Implementress"			}
    },

    {
	{ "Man",			"Woman"				},

	{ "Apprentice of Magic",	"Apprentice of Magic"		},
	{ "Spell Student",		"Spell Student"			},
	{ "Scholar of Magic",		"Scholar of Magic"		},
	{ "Delver in Spells",		"Delveress in Spells"		},
	{ "Medium of Magic",		"Medium of Magic"		},

	{ "Scribe of Magic",		"Scribess of Magic"		},
	{ "Seer",			"Seeress"			},
	{ "Sage",			"Sage"				},
	{ "Illusionist",		"Illusionist"			},
	{ "Abjurer",			"Abjuress"			},

	{ "Invoker",			"Invoker"			},
	{ "Enchanter",			"Enchantress"			},
	{ "Conjurer",			"Conjuress"			},
	{ "Magician",			"Witch"				},
	{ "Creator",			"Creator"			},

	{ "Savant",			"Savant"			},
	{ "Magus",			"Craftess"			},
	{ "Wizard",			"Wizard"			},
	{ "Warlock",			"War Witch"			},
	{ "Sorcerer",			"Sorceress"			},

	{ "Elder Sorcerer",		"Elder Sorceress"		},
	{ "Grand Sorcerer",		"Grand Sorceress"		},
	{ "Great Sorcerer",		"Great Sorceress"		},
	{ "Golem Maker",		"Golem Maker"			},
	{ "Greater Golem Maker",	"Greater Golem Maker"		},

	{ "Maker of Stones",		"Maker of Stones",		},
	{ "Maker of Potions",		"Maker of Potions",		},
	{ "Maker of Scrolls",		"Maker of Scrolls",		},
	{ "Maker of Wands",		"Maker of Wands",		},
	{ "Maker of Staves",		"Maker of Staves",		},

	{ "Demon Summoner",		"Demon Summoner"		},
	{ "Greater Demon Summoner",	"Greater Demon Summoner"	},
	{ "Dragon Charmer",		"Dragon Charmer"		},
	{ "Greater Dragon Charmer",	"Greater Dragon Charmer"	},
	{ "Master of all Magic",	"Master of all Magic"		},

 	{ "Master Mage",		"Master Mage"			},
        { "Master Mage",                "Master Mage"                   },
        { "Master Mage",                "Master Mage"                   },
        { "Master Mage",                "Master Mage"                   },
        { "Master Mage",                "Master Mage"                   },

        { "Master Mage",                "Master Mage"                   },
        { "Master Mage",                "Master Mage"                   },
        { "Master Mage",                "Master Mage"                   },
        { "Master Mage",                "Master Mage"                   },
        { "Master Mage",                "Master Mage"                   },

        { "Master Mage",                "Master Mage"                   },
        { "Master Mage",                "Master Mage"                   },
        { "Master Mage",                "Master Mage"                   },
        { "Master Mage",                "Master Mage"                   },
        { "Master Mage",                "Master Mage"                   },

	{ "Mage Hero",			"Mage Heroine"			},
	{ "Avatar of Magic",		"Avatar of Magic"		},
	{ "Angel of Magic",		"Angel of Magic"		},
	{ "Demigod of Magic",		"Demigoddess of Magic"		},
	{ "Immortal of Magic",		"Immortal of Magic"		},
	{ "God of Magic",		"Goddess of Magic"		},
	{ "Deity of Magic",		"Deity of Magic"		},
	{ "Supremity of Magic",		"Supremity of Magic"		},
	{ "Creator",			"Creator"			},
	{ "Implementor",		"Implementress"			}
    }
};



/*
 * Attribute bonus tables.
 */
const	struct	str_app_type	str_app		[26]		=
{
    { -5, -4,   0,  0 },  /* 0  */
    { -5, -4,   3,  1 },  /* 1  */
    { -3, -2,   3,  2 },
    { -3, -1,  10,  3 },  /* 3  */
    { -2, -1,  25,  4 },
    { -2, -1,  55,  5 },  /* 5  */
    { -1,  0,  80,  6 },
    { -1,  0,  90,  7 },
    {  0,  0, 100,  8 },
    {  0,  0, 100,  9 },
    {  0,  0, 115, 10 }, /* 10  */
    {  0,  0, 115, 11 },
    {  0,  0, 130, 12 },
    {  0,  0, 130, 13 }, /* 13  */
    {  0,  1, 140, 14 },
    {  1,  1, 150, 15 }, /* 15  */
    {  1,  2, 165, 16 },
    {  2,  3, 180, 22 },
    {  2,  3, 200, 25 }, /* 18  */
    {  3,  4, 225, 30 },
    {  3,  5, 250, 35 }, /* 20  */
    {  4,  6, 300, 40 },
    {  4,  6, 350, 45 },
    {  5,  7, 400, 50 },
    {  5,  8, 450, 55 },
    {  6,  9, 500, 60 }  /* 25   */
};



const	struct	int_app_type	int_app		[26]		=
{
    {  3 },	/*  0 */
    {  5 },	/*  1 */
    {  7 },
    {  8 },	/*  3 */
    {  9 },
    { 10 },	/*  5 */
    { 11 },
    { 12 },
    { 13 },
    { 15 },
    { 17 },	/* 10 */
    { 19 },
    { 22 },
    { 25 },
    { 28 },
    { 31 },	/* 15 */
    { 34 },
    { 37 },
    { 40 },	/* 18 */
    { 44 },
    { 49 },	/* 20 */
    { 55 },
    { 60 },
    { 70 },
    { 80 },
    { 85 }	/* 25 */
};



const	struct	wis_app_type	wis_app		[26]		=
{
    { 0 },	/*  0 */
    { 0 },	/*  1 */
    { 0 },
    { 0 },	/*  3 */
    { 0 },
    { 1 },	/*  5 */
    { 1 },
    { 1 },
    { 1 },
    { 1 },
    { 1 },	/* 10 */
    { 1 },
    { 1 },
    { 1 },
    { 1 },
    { 2 },	/* 15 */
    { 2 },
    { 2 },
    { 3 },	/* 18 */
    { 3 },
    { 3 },	/* 20 */
    { 3 },
    { 4 },
    { 4 },
    { 4 },
    { 5 }	/* 25 */
};



const	struct	dex_app_type	dex_app		[26]		=
{
    {   60 },   /* 0 */
    {   50 },   /* 1 */
    {   50 },
    {   40 },
    {   30 },
    {   20 },   /* 5 */
    {   10 },
    {    0 },
    {    0 },
    {    0 },
    {    0 },   /* 10 */
    {    0 },
    {    0 },
    {    0 },
    {    0 },
    { - 10 },   /* 15 */
    { - 15 },
    { - 20 },
    { - 30 },
    { - 40 },
    { - 50 },   /* 20 */
    { - 60 },
    { - 75 },
    { - 90 },
    { -105 },
    { -120 }    /* 25 */
};


const	struct	con_app_type	con_app		[26]		=
{
    { -4, 20 },   /*  0 */
    { -3, 25 },   /*  1 */
    { -2, 30 },
    { -2, 35 },	  /*  3 */
    { -1, 40 },
    { -1, 45 },   /*  5 */
    { -1, 50 },
    {  0, 55 },
    {  0, 60 },
    {  0, 65 },
    {  0, 70 },   /* 10 */
    {  0, 75 },
    {  0, 80 },
    {  0, 85 },
    {  0, 88 },
    {  1, 90 },   /* 15 */
    {  2, 95 },
    {  2, 97 },
    {  3, 99 },   /* 18 */
    {  3, 99 },
    {  4, 99 },   /* 20 */
    {  4, 99 },
    {  5, 99 },
    {  6, 99 },
    {  7, 99 },
    {  8, 99 }    /* 25 */
};



/*
 * Liquid properties.
 * Used in world.obj.
 */
const	struct	liq_type	liq_table	[]	=
{
/*    name			color	proof, full, thirst, food, ssize */
    { "water",			"clear",	{   0, 1, 10, 0, 16 }	},
    { "beer",			"amber",	{  12, 1,  8, 1, 12 }	},
    { "red wine",		"burgundy",	{  30, 1,  8, 1,  5 }	},
    { "ale",			"brown",	{  15, 1,  8, 1, 12 }	},
    { "dark ale",		"dark",		{  16, 1,  8, 1, 12 }	},

    { "whisky",			"golden",	{ 120, 1,  5, 0,  2 }	},
    { "lemonade",		"pink",		{   0, 1,  9, 2, 12 }	},
    { "firebreather",		"boiling",	{ 190, 0,  4, 0,  2 }	},
    { "local specialty",	"clear",	{ 151, 1,  3, 0,  2 }	},
    { "slime mold juice",	"green",	{   0, 2, -8, 1,  2 }	},

    { "milk",			"white",	{   0, 2,  9, 3, 12 }	},
    { "tea",			"tan",		{   0, 1,  8, 0,  6 }	},
    { "coffee",			"black",	{   0, 1,  8, 0,  6 }	},
    { "blood",			"red",		{   0, 2, -1, 2,  6 }	},
    { "salt water",		"clear",	{   0, 1, -2, 0,  1 }	},

    { "coke",			"brown",	{   0, 2,  9, 2, 12 }	}, 
    { "root beer",		"brown",	{   0, 2,  9, 2, 12 }   },
    { "elvish wine",		"green",	{  35, 2,  8, 1,  5 }   },
    { "white wine",		"golden",	{  28, 1,  8, 1,  5 }   },
    { "champagne",		"golden",	{  32, 1,  8, 1,  5 }   },

    { "mead",			"honey-colored",{  34, 2,  8, 2, 12 }   },
    { "rose wine",		"pink",		{  26, 1,  8, 1,  5 }	},
    { "benedictine wine",	"burgundy",	{  40, 1,  8, 1,  5 }   },
    { "vodka",			"clear",	{ 130, 1,  5, 0,  2 }   },
    { "cranberry juice",	"red",		{   0, 1,  9, 2, 12 }	},

    { "orange juice",		"orange",	{   0, 2,  9, 3, 12 }   }, 
    { "absinthe",		"green",	{ 200, 1,  4, 0,  2 }	},
    { "brandy",			"golden",	{  80, 1,  5, 0,  4 }	},
    { "aquavit",		"clear",	{ 140, 1,  5, 0,  2 }	},
    { "schnapps",		"clear",	{  90, 1,  5, 0,  2 }   },

    { "icewine",		"purple",	{  50, 2,  6, 1,  5 }	},
    { "amontillado",		"burgundy",	{  35, 2,  8, 1,  5 }	},
    { "sherry",			"red",		{  38, 2,  7, 1,  5 }   },	
    { "framboise",		"red",		{  50, 1,  7, 1,  5 }   },
    { "rum",			"amber",	{ 151, 1,  4, 0,  2 }	},

    { "cordial",		"clear",	{ 100, 1,  5, 0,  2 }   },
    { NULL,			NULL,		{   0, 0,  0, 0,  0 }	}
};



/*
 * The skill and spell table.
 * Slot numbers must never be changed as they appear in #OBJECTS sections.
 */
#define SLOT(n)	n

const	struct	skill_type	skill_table	[MAX_SKILL]	=
{

/*
 * Magic spells.
 */

    {
	"reserved",
        { 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99 },
        { 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99 },
	0,			
	TAR_IGNORE,	
	POS_STANDING,
	NULL,
	SLOT( 0),
	0,
 	0,
	"",
	"",
	"",
        NULL, 
	SPLIT
    },

    {
        "aurasight",
        { 28, 58, 58, 58, 58, 58, 58, 58, 58, 28, 23, 1 },
        { 1,  1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1 },
        spell_aurasight,
        TAR_CHAR_SELF,     
	POS_STANDING,
        NULL,                   
	SLOT(588),       
	20,     
	12,
        "",                     
	"",
	"!Aurasight!",	 
	"levitate",   
	SPLIT
    },
    
    {
        "combat mind",
        { 28, 58, 58, 58, 58, 58, 58, 58, 58, 28, 23, 2 },
        { 1,  1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1 },
        spell_combat_mind,       
 	TAR_CHAR_SELF,     
	POS_STANDING,
        NULL,                   
	SLOT(587),       
	20,     
	12,
        "",                     
	"!Combat Mind!",
	"", 
	"awe",   
	SPLIT
    },

    {
        "awe",
        { 28, 58, 58, 58, 58, 58, 58, 58, 58, 28, 23, 3 },
        { 1,  1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1 },
        spell_awe,       
	TAR_CHAR_SELF,     
	POS_STANDING,
        NULL,                   
	SLOT(586),       
	20,     
	12,
        "",                     
	"!Awe!",
	"",  
	"aurasight",   
	SPLIT
    },

    {
        "true path",
        { 28, 58, 58, 58, 58, 58, 58, 58, 58, 28, 23, 4 },
        { 1,  1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1 },
        spell_true_path,       
	TAR_IGNORE,     
	POS_STANDING,
        NULL,                   
	SLOT(585),       
	20,     
	12,
        "",                     
	"!True Path!",
	"",  
	"combat mind", 
	SPLIT
    },

    {
        "shadowpet",
        { 28, 58, 58, 58, 58, 58, 58, 58, 58, 28, 23, 5 },
        { 1,  1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1 },
        spell_shadowpet,       
	TAR_IGNORE,     
	POS_STANDING,
        NULL,                   
	SLOT(584),       
	20,     
	12,
        "",                     
	"!Shadowpet!", 
	"", 
	NULL, 
	SPLIT
    },

    {
        "poison sense",
        { 28, 58, 58, 58, 58, 58, 58, 58, 58, 28, 23, 6 },
        { 1,  1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1 },
        spell_poison_sense,     
	TAR_IGNORE,     
	POS_STANDING,
        NULL,                  
	SLOT(583),       
	20,     
	12,
        "",                     
	"!Poison Sense!",
	"",  
	NULL, 
	SPLIT
    },

    {
        "true pain",
        { 28, 58, 58, 58, 58, 58, 58, 58, 58, 28, 23, 7 },
        { 1,  1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1 },
        spell_true_pain,     
	TAR_CHAR_OFFENSIVE,     
	POS_FIGHTING,
        NULL,                   
	SLOT(582),       
	20,     
	12,
        "true pain",                     
	"!True Pain!",
	"",  
	NULL, 
	SPLIT
    },

    {
        "levitate",
        { 28, 58, 58, 58, 58, 58, 58, 58, 58, 28, 23, 8 },
        { 1,  1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1 },
        spell_levitate,        
	TAR_CHAR_DEFENSIVE,     	
	POS_STANDING,
        NULL,                   
	SLOT(581),       
	20,     
	12,
        "",                     
	"!Levitate!",
	"",  
	"stone skin", 
	SPLIT
    },

    {
        "astral walk",
        { 28, 58, 58, 58, 58, 58, 58, 58, 58, 28, 23, 10 },
        { 1,  1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1 },
        spell_astral_walk,        
	TAR_CHAR_SELF,     
	POS_STANDING,
        NULL,                   
	SLOT(580),       
	20,     
	12,
        "",                     
	"!Astral Walk!",
	"",  
	NULL, 
	SPLIT
    },

    {
        "life detect",
        { 28, 58, 58, 58, 58, 58, 58, 58, 58, 28, 23, 11 },
        { 1,  1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1 },
        spell_life_detect,        
	TAR_CHAR_SELF,     
	POS_STANDING,
        NULL,                   
	SLOT(579),       
	20,     
	12,
        "",                     
	"!Life Detect!",
	"", 
	NULL, 
	SPLIT
    },

    {
        "adrenalin",
        { 28, 58, 58, 58, 58, 58, 58, 58, 58, 28, 23, 15 },
        { 1,  1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1 },
        spell_adrenalin,      
	TAR_CHAR_DEFENSIVE,     
	POS_STANDING,
        NULL,                   
	SLOT(578),       
	20,     
	12,
        "",                     
	"!Adrenalin!",
	"", 
	NULL, 
	SPLIT
    },

    {
        "mind bar",
        { 28, 58, 58, 58, 58, 58, 58, 58, 58, 28, 23, 16 },
        { 1,  1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1 },
        spell_mind_bar,      
	TAR_CHAR_DEFENSIVE,     
	POS_STANDING,
        NULL,                   
	SLOT(577),       
	20,     12,
        "",                     
	"!Mind Bar!",
	"",  
	NULL, 
	SPLIT
    },

    {
        "control body",
        { 28, 58, 58, 58, 58, 58, 58, 58, 58, 28, 23, 17 },
        { 1,  1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1 },
        spell_control_body,      
	TAR_CHAR_DEFENSIVE,     	
	POS_STANDING,
        NULL,                   
	SLOT(576),       
	20,     	
	12,
        "",                     	
	"!Control Body!",
	"",  
	NULL, 
	SPLIT
    },

    {
        "drunken",
        { 28, 58, 58, 58, 58, 58, 58, 58, 58, 28, 23, 18 },
        { 1,  1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1 },
        spell_drunken,      
	TAR_CHAR_OFFENSIVE,     
	POS_FIGHTING,
        NULL,                   
	SLOT(575),       
	20,    
	12,
        "",                     
	"!Drunken!",
	"",  
	NULL, 
	SPLIT
    },

    {
        "domination",
        { 28, 58, 58, 58, 58, 58, 58, 58, 58, 28, 23, 22 },
        { 1,  1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1 },
        spell_domination,      
	TAR_CHAR_OFFENSIVE,     
	POS_STANDING,
        NULL,                   
	SLOT(574),       
	20,     
	12,
        "",                     
	"!Domination!",
	"",  
	NULL, 
	SPLIT
    },

    {
        "fireblast",
        { 28, 58, 58, 58, 58, 58, 58, 58, 58, 28, 23, 22 },
        { 1,  1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1 },
        spell_fireblast,       
	TAR_CHAR_OFFENSIVE,     
	POS_FIGHTING,
        NULL,                   
	SLOT(573),       
	20,     
	12,
        "fiery spell",                     
	"!Fireblast!",
	"", 
	NULL, 
	SPLIT
    },

    {
        "project force",
        { 28, 58, 58, 58, 58, 58, 58, 58, 58, 28, 23, 30 },
        { 1,  1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1 },
        spell_project_force,       
	TAR_CHAR_OFFENSIVE,     
	POS_STANDING,
        NULL,                   
	SLOT(572),       
	20,     
	12,
        "unseen force",          
	"!Project Force!",
	"", 	
	NULL, 
	SPLIT
    },

    {
        "complete heal",
        { 28, 58, 58, 58, 58, 58, 58, 58, 58, 28, 23, 31 },
        { 1,  1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1 },
        spell_complete_heal,       
	TAR_CHAR_DEFENSIVE,     
	POS_FIGHTING,
        NULL,                   
	SLOT(571),       
	20,     
	12,
        "",          
	"!Complete Heal!",
	"", 
	"mass heal", 
	SPLIT
    },

    {
        "cell adjust",
        { 28, 58, 58, 58, 58, 58, 58, 58, 58, 28, 23, 32 },
        { 1,  1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1 },
        spell_cell_adjust,       TAR_CHAR_DEFENSIVE,     POS_FIGHTING,
        NULL,                   SLOT(570),       20,     12,
        "",          "!Cell Adjust!","",  NULL , SPLIT
    },

    {
        "object lore",
        { 28, 58, 58, 58, 58, 58, 58, 58, 58, 28, 23, 33 },
        { 1,  1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1 },
        spell_object_lore,       
	TAR_OBJ_INV,     
	POS_STANDING,
        NULL,                   
	SLOT(569),       
	20,     
	12,
        "",                     
	"!Object Lore!",	
	"", 
	NULL, 	
	SPLIT
    },

    {
        "flesh armor",
        { 28, 58, 58, 58, 58, 58, 58, 58, 58, 28, 23, 35 },
        { 1,  1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1 },
        spell_flesh_armor,       
	TAR_CHAR_DEFENSIVE,     	
	POS_STANDING,
        NULL,                   
	SLOT(568),       	
	20,     
	12,
        "",                     
	"!Flesh Armor!",
	"", 
	"nexus", 
	SPLIT
    },

    {
        "life drain",
        { 28, 58, 58, 58, 58, 58, 58, 58, 58, 28, 23, 36 },
        { 1,  1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1 },
        spell_life_drain,       
	TAR_CHAR_OFFENSIVE,     
	POS_FIGHTING,
        NULL,                   
	SLOT(567),       
	20,     
	12,
        "soul suck",                     
	"!Life Drain!",
	"", 
	NULL, 
	SPLIT

    },

    {
	"acid blast",
        { 28, 58, 58, 58, 58, 58, 58, 58, 58, 28, 23, 50 },
        { 1,  1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_acid_blast,	
	TAR_CHAR_OFFENSIVE,	
	POS_FIGHTING,
	NULL,			
	SLOT(70),	
	20,		
	12,
	"acid blast",		
	"!Acid Blast!",
	"", 
	NULL, 
	SPLIT

    },

    {
        "guards",
        { 53, 53, 53, 53, 15, 53, 53, 53, 53, 53, 53, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        spell_guards,          
	TAR_IGNORE,        
	POS_STANDING,
        NULL,                  
	SLOT(199),    
	75,     
	15,
        "",                    
	"!Guards!",          
	"", 
	NULL, 
	SPLIT

    },

    {
        "animate",
        { 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 16, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        spell_animate,         
	TAR_IGNORE,         
	POS_STANDING,
        NULL,                  
	SLOT(55),    	
	50,      
	15,
        "",                    
	"!Animate!",           
	"", 
	NULL, 
	SPLIT

    },

    {
	"armor",
        {  7, 2, 53, 53, 2, 3, 1, 8, 18, 53, 15, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_armor,		
	TAR_CHAR_DEFENSIVE,	
	POS_STANDING,
	NULL,			
	SLOT( 1),	 
	5,	
	12,
	"",			
	"You feel less armored.",	
	"", 
	"faerie fire", 
	SPLIT

    },
    {
	"ghost",
        {  7, 2, 53, 53, 2, 3, 1, 8, 18, 53, 15, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_ghost,		
	TAR_CHAR_DEFENSIVE,	
	POS_STANDING,
	NULL,			
	SLOT( 1),	 
	5,	
	12,
	"",			
	"You feel less armored.",	
	"", 
	NULL, 
	SPLIT

    },

    {
        "galamadriel",
        { 7, 2, 15, 15, 1, 11, 10, 10, 32, 5, 5, 50},
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        spell_galamadriel,          
	TAR_CHAR_DEFENSIVE,     
	POS_STANDING,
        NULL,                   
	SLOT(589),       
	5,     
	12,
        "",                     
	"You feel less fair.",           
	"", 
	NULL, 
	SPLIT

    },
               
    {
	"bless",
        { 53, 5, 53, 53, 6, 53, 1, 53, 53, 53, 53, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_bless,		
	TAR_OBJ_CHAR_DEF,	
	POS_STANDING,
	NULL,			
	SLOT( 3),	 
	5,		
	12,
	"",			
	"You feel less righteous.", 
	"$p's holy aura fades.", 
	NULL, 
	SPLIT

    },

{
	"iceshield",		
        { 20, 30, 30, 30, 30, 30, 30, 30, 30, 30, 50 }, 
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_iceshield,	
	TAR_CHAR_DEFENSIVE,	
	POS_STANDING,
	NULL,			
	SLOT(410),	
	75,	
	12,
	"chilling touch",	
	"Your icy shield slowly melts away.",
	"", 
	NULL, 
	SPLIT

},

{
	"fireshield",		
        { 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 31, 50 }, 
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_fireshield,	
	TAR_CHAR_DEFENSIVE,	
	POS_STANDING,
	NULL,			
	SLOT(411),	
	75,		
	12,
	"fireball",		
	"Your firey shield gutters out.",
	"", 
	NULL, 
	SPLIT

},

{
	"shockshield",		
        { 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 35, 50 }, 
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_shockshield, 		
	TAR_CHAR_DEFENSIVE,	
	POS_STANDING,
	NULL,			
	SLOT(412),	
	75,	
	12,
	"lightning bolt",	
	"Your crackling shield sizzles and fades.",
	"", 
	NULL, 
	SPLIT

},


    {
	"blindness",
        {  13, 18, 53, 53, 30, 6, 53, 28, 53, 9, 4, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        spell_blindness,        
	TAR_CHAR_OFFENSIVE,     	
	POS_FIGHTING,
	&gsn_blindness,		
	SLOT( 4),	 
	5,	
	12,
	"",			
	"You can see again.",	
	"", 
	"weaken", 
	SPLIT

    },

    {
	"burning hands",
        {  7, 53, 53, 53, 53, 53, 53, 53, 53, 28, 3, 50},
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_burning_hands,	
	TAR_CHAR_OFFENSIVE,	
	POS_FIGHTING,
	NULL,			
	SLOT( 5),	
	15,	
	12,
	"burning hands",	
	"!Burning Hands!", 	
	"", 
	"chill touch", 
	SPLIT

    },

    {
	"call lightning",
        { 53, 18, 53, 53, 11, 53, 53, 53, 53, 53, 53, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_call_lightning,	
	TAR_IGNORE,		
	POS_FIGHTING,
	NULL,			
	SLOT( 6),	
	15,	
	12,
	"lightning bolt",	
	"!Call Lightning!",	
	"", 
	NULL, 
	SPLIT

    },

    {   "calm",
        { 53, 16, 53, 53, 20, 53, 10, 53, 53, 53, 53, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_calm,		
	TAR_IGNORE,		
	POS_FIGHTING,
	NULL,			
	SLOT(509),	
	30,	
	12,
	"",			
	"You have lost your peace of mind.",	
	"", 
	NULL, 
	SPLIT

    },

    {
        "cancellation",
        { 18, 26, 53, 53, 53, 53, 22, 53, 53, 53, 22, 50  },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_cancellation,	
	TAR_CHAR_DEFENSIVE,	
	POS_FIGHTING,
	NULL,			
	SLOT(507),	
	20,	
	12,
	""			
	"!cancellation!",	
	"",
	"", 
	NULL, 
	SPLIT

    },

    {
        "cause critical",
        { 53,  26, 53, 53, 53, 28, 53, 53, 53, 53, 16, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_cause_critical,	
	TAR_CHAR_OFFENSIVE,	
	POS_FIGHTING,
	NULL,			
	SLOT(63),	
	20,		
	12,
	"spell",		
	"!Cause Critical!",	
	"", 
	"blindness", 	
	SPLIT

    },

    {
        "cause light",
        { 53, 14, 53, 53, 53, 23, 53, 53, 53, 53, 1, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_cause_light,	
	TAR_CHAR_OFFENSIVE,	
	POS_FIGHTING,
	NULL,			
	SLOT(62),	
	15,	
	12,
	"spell",		
	"!Cause Light!",	
	"", 
	"poison", 
	SPLIT

    },

    {
        "cause serious",
        { 53, 22, 53, 53, 53, 53, 53, 53, 53, 53, 9, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_cause_serious,	
	TAR_CHAR_OFFENSIVE,	
	POS_FIGHTING,
	NULL,			
	SLOT(64),	
	17,	
	12,
	"spell",		
	"!Cause Serious!",	
	"", 
	"plague", 
	SPLIT

    },

    {   
        "chain lightning",
        { 30, 53, 53, 53, 53, 53, 53, 17, 53, 53, 53, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_chain_lightning,	
	TAR_CHAR_OFFENSIVE,	
	POS_FIGHTING,
	NULL,			
	SLOT(500),	
	25,	
	12,
	"lightning",		
	"!Chain Lightning!",	
	"", 
	NULL, 
	SPLIT

    }, 

    {
        "change sex",
        { 18, 20, 53, 53, 53, 53, 15, 53, 53, 16, 18, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_change_sex,	
	TAR_CHAR_DEFENSIVE,	
	POS_FIGHTING,
	NULL,			
	SLOT(82),	
	15,	
	12,
	"",			
	"Your body feels familiar again.",	
	"", 
	NULL,
	SPLIT

    },

    {
        "charm person",
        { 20, 23, 23, 53, 30, 15, 15, 15, 15, 14, 15, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_charm_person,	
	TAR_CHAR_OFFENSIVE,	
	POS_STANDING,
	&gsn_charm_person,	
	SLOT( 7),	 
	5,	
	12,
	"",			
	"You feel more self-confident.",	
	"", 
	NULL, 
	SPLIT

    },

    {
        "chill touch",
        {  4, 53, 6, 6, 18, 23, 15, 15, 15, 15, 1, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_chill_touch,	
	TAR_CHAR_OFFENSIVE,	
	POS_FIGHTING,
	NULL,			
	SLOT( 8),	
	15,	
	12,
	"chilling touch",	
	"You feel less cold.",	
	"", 
	"colour spray", 
	SPLIT

    },

    {
        "colour spray",
        { 16, 53, 22, 20, 55, 15, 15, 15, 15, 1, 7, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_colour_spray,	
	TAR_CHAR_OFFENSIVE,	
	POS_FIGHTING,
	NULL,			
	SLOT(10),	
	15,	
	12,
	"colour spray",		
	"!Colour Spray!",	
	"", 
	"chain lightning", 	
	SPLIT

    },

    {
        "continual light",
        {  6,  4, 53, 53, 5, 15, 14, 20, 15, 1, 23, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_continual_light,	
	TAR_IGNORE,		
	POS_STANDING,
	NULL,			
	SLOT(57),	 
	7,	
	12,
	"",			
	"!Continual Light!",		
	"", 
	NULL, 
	SPLIT

    },

    {
        "control weather",
        { 15, 24, 28, 22, 27, 15, 15, 19, 15, 53, 15, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_control_weather,	
	TAR_IGNORE,		
	POS_STANDING,
	NULL,			
	SLOT(11),	
	25,	
	12,
	"",			
	"!Control Weather!",	
	"", 
	NULL, 
	SPLIT

    },

    {
        "create food",
        { 10, 5, 11, 12, 4, 15, 5, 3, 15, 3, 35, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_create_food,	
	TAR_IGNORE,		
	POS_STANDING,
	NULL,			
	SLOT(12),	 
	5,	
	12,
	"",			
	"!Create Food!",	
	"", 
	"create spring", 
	SPLIT

    },

    {
        "create rose",
        { 16, 11, 10, 24, 13, 15, 18, 25, 15, 3, 45, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_create_rose,	
	TAR_IGNORE,		
	POS_STANDING,
	NULL,			
	SLOT(511),	
	30, 	
	12,
	"",			
	"!Create Rose!",	
	"", 
	NULL, 
	SPLIT

    },  
    

    {
        "create spring",
        { 14, 17, 23, 20, 20, 15, 14, 2, 15, 15, 45, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_create_spring,	
	TAR_IGNORE,		
	POS_STANDING,
	NULL,			
	SLOT(80),	
	20,	
	12,
	"",			
	"!Create Spring!",	
	"", 
	NULL, 
	SPLIT

    },

    {
        "create water",
        { 8,  3, 12, 11, 5, 15, 4, 15, 15, 3, 40, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_create_water,	
	TAR_OBJ_INV,		
	POS_STANDING,
	NULL,			
	SLOT(13),	 
	5,	
	12,
	"",			
	"!Create Water!",	
	"", 
	"create food", 
	SPLIT

    },

    {
        "cure blindness",
        { 53, 6, 53, 8, 8, 15, 3, 15, 15, 15, 15, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_cure_blindness,	
	TAR_CHAR_DEFENSIVE,	
	POS_FIGHTING,
	NULL,			
	SLOT(14),	 
	5,	
	12,
	"",			
	"!Cure Blindness!",	
	"", 
"cure serious", 
	SPLIT

    },

    {
        "cure critical",
        { 53, 13, 53, 19, 10, 15, 9, 15, 15, 15, 15, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_cure_critical,	
	TAR_CHAR_DEFENSIVE,	
	POS_FIGHTING,
	NULL,			
	SLOT(15),	
	20,	
	12,
	"",			
	"!Cure Critical!",	
	"", 
	"cure disease", 
	SPLIT

    },

    {
        "cure disease",
        { 53, 13, 53, 14, 17, 15, 11, 15, 15, 15, 15, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_cure_disease,	
	TAR_CHAR_DEFENSIVE,	
	POS_STANDING,
	NULL,			
	SLOT(501),	
	20,	
	12,
	"",			
	"!Cure Disease!",	
	"", 
	"complete heal", 
	SPLIT

    },

    {
        "cure light",
        { 53,  1, 53, 3, 1, 4, 1, 15, 15, 15, 15, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_cure_light,	
	TAR_CHAR_DEFENSIVE,	
	POS_FIGHTING,
	NULL,			
	SLOT(16),	
	10,	
	12,
	"",			
	"!Cure Light!",		
	"", 
	"cure blindness", 
	SPLIT

    },

    {
        "cure poison",
        { 53,  14, 53, 16, 30, 15, 12, 15, 15, 15, 15, 50},
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_cure_poison,	
	TAR_CHAR_DEFENSIVE,	
	POS_STANDING,
	NULL,			
	SLOT(43),	 
	5,	
	12,
	"",			
	"!Cure Poison!",	
	"", 
	"cure critical", 
	SPLIT

    },

    {
        "cure serious",
        { 53, 7, 53, 10, 5, 15, 5, 15, 15, 15, 15, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_cure_serious,	
	TAR_CHAR_DEFENSIVE,	
	POS_FIGHTING,
	NULL,			
	SLOT(61),	
	15,	
	12,
	"",			
	"!Cure Serious!",	
	"", 
	"cure poison", 
	SPLIT

    },

    {
        "curse",
        { 18, 18, 26, 22, 40, 39, 15, 15, 15, 29, 19, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_curse,		
	TAR_OBJ_CHAR_OFF,	
	POS_FIGHTING,
	&gsn_curse,			
	SLOT(17),	
	20,	
	12,
	"curse",		
	"The curse wears off.", 
	"$p is no longer impure.", 
	NULL, 
	SPLIT

    },

    {
        "demonfire",
        { 53, 34, 53, 45, 45, 15, 15, 15, 15, 27, 25, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_demonfire,	
	TAR_CHAR_OFFENSIVE,	
	POS_FIGHTING,
	NULL,			
	SLOT(505),		
	20,	
	12,
	"torment",		
	"!Demonfire!",		
	"", 
	NULL, 
	SPLIT

    },	

    {
        "detect evil",
        { 11,  4, 12, 53, 1, 15, 16, 16, 15, 16, 20, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_detect_evil,	
	TAR_CHAR_SELF,		
	POS_STANDING,
	NULL,			
	SLOT(18),	 
	5,	
	12,
	"",			
	"The red in your vision disappears.",	
	"", 
	NULL, 
	SPLIT

    },

    {
        "detect good",
        { 11,  4, 12, 53, 17, 15, 16, 16, 15, 16, 20, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        spell_detect_good,      
	TAR_CHAR_SELF,          
	POS_STANDING,
        NULL,                   
	SLOT(513),        
	5,     
	12,
        "",                     
	"The gold in your vision disappears.",	
	"", 
	NULL, 
	SPLIT

    },

    {
        "detect hidden",
        { 15, 11, 10, 53, 10, 9, 23, 23, 5, 20, 25, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_detect_hidden,	
	TAR_CHAR_SELF,		
	POS_STANDING,
	NULL,			
	SLOT(44),	 
	5,
	12,
	"",			
	"You feel less aware of your surroundings.",	
	"", 
	NULL, 
	SPLIT

    },

    {
        "detect invis",
        {  3, 8, 6, 53, 7, 7, 23, 23, 3, 20, 25, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_detect_invis,	
	TAR_CHAR_SELF,		
	POS_STANDING,
	NULL,			
	SLOT(19),	 
	5,	
	30,
	"",			
	"You no longer see invisible objects.",
	"", 
	"detect hidden", 
	SPLIT

    },

    {
        "detect magic",
        {  2,  6, 5, 53, 6, 15, 14, 17, 15, 10, 10, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_detect_magic,	TAR_CHAR_SELF,		POS_STANDING,
	NULL,			SLOT(20),	 5,	12,
	"",			"The detect magic wears off.",	"",
"detect invis", SPLIT

    },

    {
        "detect poison",
        { 15,  7, 9, 53, 17, 15, 15, 21, 15, 23, 10, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_detect_poison,	TAR_OBJ_INV,		POS_STANDING,
	NULL,			SLOT(21),	 5,	12,
	"",			"!Detect Poison!",	"", NULL, SPLIT

    },

    {
        "dispel evil",
        { 53, 15, 53, 21, 30, 15, 25, 14, 20, 20, 26, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_dispel_evil,	TAR_CHAR_OFFENSIVE,	POS_FIGHTING,
	NULL,			SLOT(22),	15,	12,
	"dispel evil",		"!Dispel Evil!",	"", NULL, SPLIT

    },

    {
        "dispel good",
        { 53, 15, 53, 21, 40, 15, 10, 15, 20, 20, 26, 50},
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        spell_dispel_good,      TAR_CHAR_OFFENSIVE,     POS_FIGHTING,
        NULL,                   SLOT(512),      15,     12,
        "dispel good",          "!Dispel Good!",	"", NULL, SPLIT

    },

    {
        "dispel magic",
        { 16, 24, 30, 30, 30, 15, 23, 15, 10, 26, 32, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_dispel_magic,	TAR_CHAR_OFFENSIVE,	POS_FIGHTING,
	NULL,			SLOT(59),	15,	12,
	"",			"!Dispel Magic!",	"", NULL, SPLIT

    },

    {
        "earthquake",
        { 53,  17, 53, 14, 20, 15, 15, 15, 15, 15, 15, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_earthquake,	TAR_IGNORE,		POS_FIGHTING,
	NULL,			SLOT(23),	15,	12,
	"earthquake",		"!Earthquake!",		"", NULL, SPLIT

    },

    {
        "enchant armor",
        { 16, 53, 53, 53, 30, 15, 15, 15, 15, 36, 26, 50  },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_enchant_armor,	TAR_OBJ_INV,		POS_STANDING,
	NULL,			SLOT(510),	100,	24,
	"",			"!Enchant Armor!",	"", NULL, SPLIT

    },

    {
        "enchant weapon",
        { 17, 53, 53, 53, 30, 15, 15, 15, 15, 37, 27, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_enchant_weapon,	TAR_OBJ_INV,		POS_STANDING,
	NULL,			SLOT(24),	100,	24,
	"",			"!Enchant Weapon!",	"", NULL, SPLIT

    },

    {
        "energy drain",
        { 19, 22, 26, 23, 30, 15, 15, 15, 15, 24, 13, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_energy_drain,	TAR_CHAR_OFFENSIVE,	POS_FIGHTING,
	NULL,			SLOT(25),	35,	12,
	"energy drain",		"!Energy Drain!",	"", NULL, SPLIT

    },

    {
        "faerie fire",
        {  6,  3, 5, 8, 20, 8, 7, 11, 13, 1, 17, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_faerie_fire,	TAR_CHAR_OFFENSIVE,	POS_FIGHTING,
	NULL,			SLOT(72),	 5,	12,
	"faerie fire",		"The pink aura around you fades away.",
	"", "faerie fog", SPLIT

    },

    {
        "faerie fog",
        { 14, 21, 16, 24, 30, 15, 15, 26, 15, 12, 15, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_faerie_fog,	TAR_IGNORE,		POS_STANDING,
	NULL,			SLOT(73),	12,	12,
	"faerie fog",		"!Faerie Fog!",		"", "shield",
SPLIT

    },

    {
        "farsight",
        { 14, 16, 16, 53, 30, 15, 15, 24, 15, 27, 15, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_farsight,		TAR_IGNORE,		POS_STANDING,
	NULL,			SLOT(521),	36,	20,
	"farsight",		"!Farsight!",		"", NULL, SPLIT

    },	

    {
        "fireball",
        { 22, 53, 30, 26, 35, 15, 15, 15, 15, 25, 28, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_fireball,		TAR_CHAR_OFFENSIVE,	POS_FIGHTING,
	NULL,			SLOT(26),	15,	12,
	"fireball",		"!Fireball!",		"", "shocking
grasp", SPLIT

    },
  
    {
        "fireproof",
        { 13, 12, 19, 18, 20, 15, 13, 15, 32, 23, 15, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_fireproof,	TAR_OBJ_INV,		POS_STANDING,
	NULL,			SLOT(523),	10,	12,
	"",			"",	"$p's protective aura fades.", 
	"project force", SPLIT

    },

    {
        "flamestrike",
        { 53, 20, 53, 27, 13, 18, 14, 17, 20, 19, 15, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_flamestrike,	TAR_CHAR_OFFENSIVE,	POS_FIGHTING,
	NULL,			SLOT(65),	20,	12,
	"flamestrike",		"!Flamestrike!",		"", 
	"fireproof", SPLIT

    },

    {
        "fly",
        { 10, 18, 20, 22, 19, 15, 15, 15, 15, 11, 26, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_fly,		TAR_CHAR_DEFENSIVE,	POS_STANDING,
	NULL,			SLOT(56),	10,	18,
	"",			"You slowly float to the ground.",	"", 
	"invisibility", SPLIT

    },

    {
        "floating disc",
        {  4, 10, 7, 16, 18, 15, 26, 36, 15, 7, 15, 50},
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_floating_disc,	TAR_IGNORE,		POS_STANDING,
	NULL,			SLOT(522),	40,	24,
	"",			"!Floating disc!",	"", NULL, SPLIT

    },

    {
        "frenzy",
        { 53, 24, 53, 26, 35, 15, 28, 15, 15, 6, 15, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        spell_frenzy,           TAR_CHAR_DEFENSIVE,     POS_STANDING,
        NULL,                   SLOT(504),      30,     24,
        "",                     "Your rage ebbs.",	"",
NULL, SPLIT

    },

    {
        "gate",
        { 27, 17, 32, 28, 28, 15, 26, 35, 15, 27, 29, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_gate,		TAR_IGNORE,		POS_FIGHTING,
	NULL,			SLOT(83),	80,	12,
	"",			"!Gate!",		"", NULL, SPLIT

    },

    {
        "giant strength",
        {  11, 53, 22, 20, 20, 15, 15, 15, 15, 33, 19, 50},
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_giant_strength,	TAR_CHAR_DEFENSIVE,	POS_STANDING,
	NULL,			SLOT(39),	20,	12,
	"",			"You feel weaker.",	"", "frenzy",
SPLIT

    },

    {
        "harm",
        { 53, 23, 53, 28, 45, 15, 15, 15, 15, 27, 29, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_harm,		TAR_CHAR_OFFENSIVE,	POS_FIGHTING,
	NULL,			SLOT(27),	35,	12,
	"harm spell",		"!Harm!",		"", NULL, SPLIT

    },
  
    {
        "haste",
        { 21, 53, 26, 29, 29, 15, 15, 15, 15, 21, 27, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_haste,		TAR_CHAR_DEFENSIVE,	POS_FIGHTING,
	NULL,			SLOT(502),	30,	12,
	"",			"You feel yourself slow down.",	"",
"summon", SPLIT

    },

    {
        "heal",
        { 53, 21, 33, 30, 25, 15, 20, 15, 15, 30, 35, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_heal,		TAR_CHAR_DEFENSIVE,	POS_FIGHTING,
	NULL,			SLOT(28),	50,	12,
	"",			"!Heal!",		"", NULL, SPLIT

    },
  
    {
        "heat metal",
        { 53, 16, 53, 23, 23, 15, 15, 15, 15, 20, 15, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_heat_metal,	TAR_CHAR_OFFENSIVE,	POS_FIGHTING,
	NULL,			SLOT(516), 	25,	18,
	"spell",		"!Heat Metal!",		"", "flamestrike",
SPLIT

    },

    {
        "holy word",
        { 53, 36, 53, 42, 25, 15, 15, 15, 15, 25, 37, 50 },
        { 2,  2,  2,  2, 2, 2, 2, 2, 2, 2, 2, 2 },
	spell_holy_word,	TAR_IGNORE,	POS_FIGHTING,
	NULL,			SLOT(506), 	200,	24,
	"divine wrath",		"!Holy Word!",		"", NULL, SPLIT

    },

    {
        "identify",
        { 15, 16, 18, 53, 53, 15, 21, 31, 15, 17, 17, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_identify,		TAR_OBJ_INV,		POS_STANDING,
	NULL,			SLOT(53),	12,	24,
	"",			"!Identify!",		"", NULL, SPLIT

    },

    {
        "infravision",
        {  9, 13, 10, 16, 16, 5, 15, 15, 15, 3, 18, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_infravision,	TAR_CHAR_DEFENSIVE,	POS_STANDING,
	NULL,			SLOT(77),	 5,	18,
	"",			"You no longer see in the dark.",	"", 
	"detect magic", SPLIT

    },

    {
        "invisibility",
        {  5, 53, 9, 53, 53, 15, 15, 25, 15, 2, 5, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_invis,		TAR_OBJ_CHAR_DEF,	POS_STANDING,
	&gsn_invis,		SLOT(29),	 5,	12,
	"",			"You are no longer invisible.",		
	"$p slowly fades into view.", "slow", SPLIT

    },
    {
        "know alignment",
        {  12, 9, 20, 53, 4, 15, 20, 30, 15, 10, 11, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_know_alignment,	TAR_CHAR_DEFENSIVE,	POS_FIGHTING,
	NULL,			SLOT(58),	 9,	12,
	"",			"!Know Alignment!",	"", NULL, SPLIT

    },

    {
        "lightning bolt",
        {  13, 23, 18, 16, 30, 15, 15, 15, 15, 9, 23, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_lightning_bolt,	TAR_CHAR_OFFENSIVE,	POS_FIGHTING,
	NULL,			SLOT(30),	15,	12,
	"lightning bolt",	"!Lightning Bolt!",	"", NULL, SPLIT

    },

    {
        "locate object",
        { 9, 15, 11, 53, 19, 25, 17, 30, 19, 16, 21, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_locate_object,	TAR_IGNORE,		POS_STANDING,
	NULL,			SLOT(31),	20,	18,
	"",			"!Locate Object!",	"", NULL, SPLIT

    },

    {
        "magic missile",
        {  1, 53, 2, 2, 10, 15, 15, 15, 15, 14, 11, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_magic_missile,	TAR_CHAR_OFFENSIVE,	POS_FIGHTING,
	NULL,			SLOT(32),	15,	12,
	"magic missile",	"!Magic Missile!",	"", "fireball",
SPLIT

    },

    {
        "mass healing",
        { 53, 38, 53, 46, 30, 15, 28, 15, 15, 33, 35, 50 },
        { 2,  2,  2,  2, 2, 2, 2, 2, 2, 2, 2, 2 },
	spell_mass_healing,	TAR_IGNORE,		POS_STANDING,
	NULL,			SLOT(508),	100,	36,
	"",			"!Mass Healing!",	"", NULL, SPLIT

    },

    {
        "mass invis",
        { 22, 25, 31, 53, 53, 15, 15, 38, 15, 12, 30, 50 },
        { 2,  2,  2,  2, 2, 2, 2, 2, 2, 2, 2, 2 },
	spell_mass_invis,	TAR_IGNORE,		POS_STANDING,
	&gsn_mass_invis,	SLOT(69),	20,	24,
	"",			"You are no longer invisible.",		"", 
	NULL, SPLIT

    },

    {
        "nexus",
        { 40, 35, 50, 45, 45, 15, 50, 50, 15, 15, 50, 50 },
        { 2,  2,  2,  2, 2, 2, 2, 2, 2, 2, 2, 2 },
        spell_nexus,            TAR_IGNORE,             POS_STANDING,
        NULL,                   SLOT(520),       150,   36,
        "",                     "!Nexus!",		"", NULL, SPLIT

    },

    {
        "pass door",
        { 24, 32, 25, 37, 37, 15, 15, 15, 15, 17, 18, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_pass_door,	TAR_CHAR_SELF,		POS_STANDING,
	NULL,			SLOT(74),	20,	12,
	"",			"You feel solid again.",	"", NULL, SPLIT

    },

    {
        "plague",
        { 23, 17, 36, 26, 45, 13, 30, 15, 15, 35, 20, 50 },
        { 2,  2,  2,  2, 2, 2, 2, 2, 2, 2, 2, 2 },
	spell_plague,		TAR_CHAR_OFFENSIVE,	POS_FIGHTING,
	&gsn_plague,		SLOT(503),	20,	12,
	"sickness",		"Your sores vanish.",	"", "cause
critical", SPLIT

    },

    {
        "poison",
        { 17,  12, 15, 21, 40, 5, 15, 15, 15, 25, 10, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_poison,		TAR_OBJ_CHAR_OFF,	POS_FIGHTING,
	&gsn_poison,		SLOT(33),	10,	12,
	"poison",		"You feel less sick.",	
	"The poison on $p dries up.", "cause serious", SPLIT

    },

    {
        "portal",
        { 35, 30, 45, 40, 40, 15, 35, 40, 15, 15, 30, 50 },
        { 2,  2,  2,  2, 2, 2, 2, 2, 2, 2, 2, 2 },
        spell_portal,           TAR_IGNORE,             POS_STANDING,
        NULL,                   SLOT(519),       100,     24,
        "",                     "!Portal!",		"", NULL, SPLIT

    },

    {
        "protection evil",
        { 12,  9, 17, 11, 10, 15, 15, 15, 15, 15, 30, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_protection_evil,	TAR_CHAR_SELF,		POS_STANDING,
	NULL,			SLOT(34), 	5,	12,
	"",			"You feel less protected.",	"", NULL, SPLIT

    },

    {
        "protection good",
        { 12,  9, 17, 11, 10, 15, 20, 20, 15, 15, 16, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        spell_protection_good,  TAR_CHAR_SELF,          POS_STANDING,
        NULL,                   SLOT(514),       5,     12,
        "",                     "You feel less protected.",	"", NULL, SPLIT

    },

    {
        "ray of truth",
        { 53, 35, 53, 47, 47, 15, 15, 15, 15, 35, 37, 50 },
        { 2,  2,  2,  2, 2, 2, 2, 2, 2, 2, 2, 2 },
        spell_ray_of_truth,     TAR_CHAR_OFFENSIVE,     POS_FIGHTING,
        NULL,                   SLOT(518),      20,     12,
        "ray of truth",         "!Ray of Truth!",	"", NULL, SPLIT

    },

    {
        "recharge",
        { 9, 53, 53, 53, 54, 15, 15, 15, 15, 15, 21, 50},
        { 2,  2,  2,  2, 2, 2, 2, 2, 2, 2, 2, 2 },
	spell_recharge,		TAR_OBJ_INV,		POS_STANDING,
	NULL,			SLOT(517),	60,	24,
	"",			"!Recharge!",		"", NULL, SPLIT

    },

    {
        "refresh",
        {  8,  5, 12, 9, 15, 15, 4, 15, 15, 13, 15, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_refresh,		TAR_CHAR_DEFENSIVE,	POS_STANDING,
	NULL,			SLOT(81),	12,	18,
	"refresh",		"!Refresh!",		"", NULL, SPLIT

    },

    {
        "remove curse",
        { 53, 18, 53, 22, 18, 15, 14, 15, 28, 15, 30, 50 },
        { 2,  2,  2,  2, 2, 2, 2, 2, 2, 2, 2, 2 },
	spell_remove_curse,	TAR_OBJ_CHAR_DEF,	POS_STANDING,
	NULL,			SLOT(35),	 5,	12,
	"",			"!Remove Curse!",	"", NULL, SPLIT

    },

    {
        "sanctuary",
        { 36, 20, 42, 30, 25, 15, 19, 15, 36, 15, 15, 50 },
        { 2,  2,  2,  2, 2, 2, 2, 2, 2, 2, 2, 2 },
	spell_sanctuary,	TAR_CHAR_DEFENSIVE,	POS_STANDING,
	&gsn_sanctuary,		SLOT(36),	75,	12,
	"",			"The white aura around your body fades.",
	"", NULL, SPLIT

    },

    {
        "shield",
        { 20, 35, 35, 40, 15, 15, 35, 30, 35, 20, 20, 50 },
        { 2,  2,  2,  2, 2, 2, 2, 2, 2, 2, 2, 2 },
	spell_shield,		TAR_CHAR_DEFENSIVE,	POS_STANDING,
	NULL,			SLOT(67),	12,	18,
	"",			"Your force shield shimmers then fades away.",
	"", "sanctuary", SPLIT

    },

    {
        "shocking grasp",
        {  10, 53, 14, 13, 25, 15, 15, 15, 15, 25, 15, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_shocking_grasp,	TAR_CHAR_OFFENSIVE,	POS_FIGHTING,
	NULL,			SLOT(53),	15,	12,
	"shocking grasp",	"!Shocking Grasp!",	"", "burning
hands", SPLIT

    },

    {
        "sleep",
        { 10, 20, 11, 53, 53, 20, 15, 15, 15, 18, 15, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_sleep,		TAR_CHAR_OFFENSIVE,	POS_STANDING,
	&gsn_sleep,		SLOT(38),	15,	12,
	"",			"You feel less tired.",	"", NULL, SPLIT

    },

    {
        "slow",
        { 23, 30, 29, 32, 32, 32, 15, 15, 15, 29, 23, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        spell_slow,             TAR_CHAR_OFFENSIVE,     POS_FIGHTING,
        NULL,                   SLOT(515),      30,     12,
        "",                     "You feel yourself speed up.",	"",
"haste", SPLIT

    },

    {
        "stone skin",
        { 25, 40, 40, 45, 45, 30, 40, 15, 45, 15, 22, 50 },
        { 2,  2,  2,  2, 2, 2, 2, 2, 2, 2, 2, 2 },
	spell_stone_skin,	TAR_CHAR_SELF,		POS_STANDING,
	NULL,			SLOT(66),	12,	18,
	"",			"Your skin feels soft again.",	"",
"flesh armor", SPLIT

    },

    {
        "summon",
        { 24, 12, 29, 22, 21, 15, 20, 24, 15, 15, 24, 50},
        { 2,  2,  2,  2, 2, 2, 2, 2, 2, 2, 2, 2 },
	spell_summon,		TAR_IGNORE,		POS_STANDING,
	NULL,			SLOT(40),	50,	12,
	"",			"!Summon!",		"", "teleport",
SPLIT

    },

    {
        "teleport",
        {  13, 22, 25, 36, 20, 15, 20, 15, 15, 15, 20, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_teleport,		TAR_CHAR_SELF,		POS_FIGHTING,
	NULL,	 		SLOT( 2),	35,	12,
	"",			"!Teleport!",		"", "nexus", SPLIT

    },

    {
        "ventriloquate",
        {  1, 53, 2, 53, 53, 15, 15, 5, 15, 1, 5, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_ventriloquate,	TAR_IGNORE,		POS_STANDING,
	NULL,			SLOT(41),	 5,	12,
	"",			"!Ventriloquate!",	"", NULL, SPLIT

    },

    {
        "weaken",
        {  11, 14, 16, 17, 17, 15, 25, 15, 15, 23, 11, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_weaken,		TAR_CHAR_OFFENSIVE,	POS_FIGHTING,
	NULL,			SLOT(68),	20,	12,
	"spell",		"You feel stronger.",	"", "animate",
SPLIT

    },

    {
        "word of recall",
        { 32, 28, 40, 30, 30, 15, 28, 15, 15, 26, 32, 50  },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_word_of_recall,	TAR_CHAR_SELF,		POS_RESTING,
	NULL,			SLOT(42),	 5,	12,
	"",			"!Word of Recall!",	"", NULL, SPLIT

    },

/*
 * Dragon breath
 */
    {
        "acid breath",
        { 31, 32, 33, 34, 34, 40, 40, 40, 40, 40, 40, 40 },
        { 2,  2,  2,  2, 2, 2, 2, 2, 2, 2, 2, 2 },
	spell_acid_breath,	TAR_CHAR_OFFENSIVE,	POS_FIGHTING,
	NULL,			SLOT(200),	100,	24,
	"blast of acid",	"!Acid Breath!",	"", NULL, SPLIT

    },

    {
        "fire breath",
        { 40, 45, 50, 51, 51, 40, 40, 40, 40, 40, 40, 40 },
        { 2,  2,  2,  2, 2, 2, 2, 2, 2, 2, 2, 2 },
	spell_fire_breath,	TAR_CHAR_OFFENSIVE,	POS_FIGHTING,
	NULL,			SLOT(201),	200,	24,
	"blast of flame",	"The smoke leaves your eyes.",	"", NULL, SPLIT

    },

    {
        "frost breath",
        { 34, 36, 38, 40, 40, 40, 40, 40, 40, 40, 40, 40  },
        { 2,  2,  2,  2, 2, 2, 2, 2, 2, 2, 2, 2 },
	spell_frost_breath,	TAR_CHAR_OFFENSIVE,	POS_FIGHTING,
	NULL,			SLOT(202),	125,	24,
	"blast of frost",	"!Frost Breath!",	"", NULL, SPLIT

    },

    {
        "gas breath",
        { 39, 43, 47, 50, 50, 40, 40, 40, 40, 40, 40, 40 },
        { 2,  2,  2,  2, 2, 2, 2, 2, 2, 2, 2, 2 },
	spell_gas_breath,	TAR_IGNORE,		POS_FIGHTING,
	NULL,			SLOT(203),	175,	24,
	"blast of gas",		"!Gas Breath!",		"", NULL, SPLIT

    },

    {
        "lightning breath",
        { 37, 40, 43, 46, 46, 40, 40, 40, 40, 40, 40, 40 },
        { 2,  2,  2,  2, 2, 2, 2, 2, 2, 2, 2, 2 },
	spell_lightning_breath,	TAR_CHAR_OFFENSIVE,	POS_FIGHTING,
	NULL,			SLOT(204),	150,	24,
	"blast of lightning",	"!Lightning Breath!",	"", NULL, SPLIT

    },


    {
        "hunt",
        { 35, 37, 15, 20, 30, 17, 25, 1, 10, 36, 35, 40 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        spell_null,     TAR_IGNORE,    POS_RESTING,
        &gsn_hunt,      SLOT( 0),     0,      12,
        "",             "!hunt!", "", NULL, SPLIT

    },
        
/*
 * Spells for mega1.are from Glop/Erkenbrand.
 */
    {
        "general purpose",
        { 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        spell_general_purpose,  TAR_CHAR_OFFENSIVE,     POS_FIGHTING,
        NULL,                   SLOT(401),      0,      12,
        "general purpose ammo", "!General Purpose Ammo!",	"", NULL, SPLIT

    },
 
    {
        "high explosive",
        { 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        spell_high_explosive,   TAR_CHAR_OFFENSIVE,     POS_FIGHTING,
        NULL,                   SLOT(402),      0,      12,
        "high explosive ammo",  "!High Explosive Ammo!",	"", NULL, SPLIT

    },


/* combat and weapons skills */

    {
	"critical strike",
	{ 1, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 },
	{ 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8 },
	spell_null,	TAR_IGNORE,	POS_FIGHTING,
	&gsn_critical,	SLOT( 0),  0,   0,
        "",	"!Critical Strike!", "", NULL, SPLIT

    },

    {
        "axe",
        { 1, 1, 1,  1, 1, 1, 1, 1, 1,  1, 1,1},
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        spell_null,             TAR_IGNORE,             POS_FIGHTING,
        &gsn_axe,            	SLOT( 0),       0,      0,
        "",                     "!Axe!",		"", "enhanced
damage", SPLIT

    },

    {
        "dagger",
        { 1, 1, 1,  1, 1, 1, 1, 1, 1,  1, 1, 1},
        { 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        spell_null,             TAR_IGNORE,             POS_FIGHTING,
        &gsn_dagger,            SLOT( 0),       0,      0,
        "",                     "!Dagger!",		"", "enhanced
damage", SPLIT

    },
 
    {
        "flail",
        { 1,  1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        spell_null,             TAR_IGNORE,             POS_FIGHTING,
        &gsn_flail,            	SLOT( 0),       0,      0,
        "",                     "!Flail!",		"", "enhanced
damage", SPLIT

    },

    {
        "mace",
        { 1,  1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        spell_null,             TAR_IGNORE,             POS_FIGHTING,
        &gsn_mace,            	SLOT( 0),       0,      0,
        "",                     "!Mace!",		"", "enhanced
damage", SPLIT

    },

    {
        "polearm",
        { 1,  1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        spell_null,             TAR_IGNORE,             POS_FIGHTING,
        &gsn_polearm,           SLOT( 0),       0,      0,
        "",                     "!Polearm!",		"", "enhanced
damage", SPLIT

    },
    
    {
        "shield block",
        { 1, 21, 7, 1, 1, 12, 17, 10, 21, 21, 21, 1 },
        { 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_null,		TAR_IGNORE,		POS_FIGHTING,
	&gsn_shield_block,	SLOT(0),	0,	0,
	"",			"!Shield!",		"", NULL, SPLIT

    },
 
    {
        "staff",
        { 1,  1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        spell_null,             TAR_IGNORE,             POS_FIGHTING,
        &gsn_staff,            	SLOT( 0),       0,      0,
        "",                     "!Staff!",		"", "enhanced
damage", SPLIT

    },

    {
        "sword",
        { 1,  1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        spell_null,             
	TAR_IGNORE,             
	POS_FIGHTING,
        &gsn_sword,            	
	SLOT( 0),       
	0,      
	0,
        "",                     
	"!sword!",		
	"", 
	"enhanced damage", 
	SPLIT

    },

    {
        "whip",
        { 1,  1, 1,  1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        spell_null,             TAR_IGNORE,             POS_FIGHTING,
        &gsn_whip,            	SLOT( 0),       0,      0,
        "",                     "!Whip!",	"", "enhanced damage",
SPLIT

    },

    {
        "backstab",
        { 53, 53, 10, 53, 53, 1, 53, 30, 30, 53, 53, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        spell_null,             TAR_IGNORE,             POS_STANDING,
        &gsn_backstab,          SLOT( 0),        0,     24,
        "backstab",             "!Backstab!",		"", "circle",
SPLIT

    },

    {
        "circle",
        { 53, 53, 20, 53, 53, 10, 53, 53, 53, 53, 53, 50 },
        { 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 },
        spell_null,             TAR_IGNORE,            POS_FIGHTING,
        &gsn_circle,            SLOT( 0),        0,     36,
        "circle",               "!Circle!",             "", "envenom",
SPLIT

    },

    {
        "bash",
        { 1, 53, 53,  1, 10, 15, 53, 27, 5, 53, 53, 50 },
        { 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        spell_null,             TAR_IGNORE,             POS_FIGHTING,
        &gsn_bash,            	SLOT( 0),       0,      24,
        "bash",                 "!Bash!",		"", "kick", SPLIT

    },

    {
        "berserk",
        { 33, 27, 28, 18, 25, 30, 23, 23, 1, 37, 33, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        spell_null,             TAR_IGNORE,             POS_FIGHTING,
        &gsn_berserk,        	SLOT( 0),       0,      24,
        "",                     "You feel your pulse slow down.",	"", 
	"lore", SPLIT

    },

    {
        "dirt kicking",
        { 25, 27, 3, 3, 53, 3, 37, 5, 10, 38, 38, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_null,		TAR_IGNORE,		POS_FIGHTING,
	&gsn_dirt,		SLOT( 0),	0,	24,
	"kicked dirt",		"You rub the dirt out of your eyes.",	"", 
	"round", SPLIT

    },

    {
        "disarm",
        { 53, 53, 12, 10, 8, 13, 18, 11, 30, 53, 53, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        spell_null,             TAR_IGNORE,             POS_FIGHTING,
        &gsn_disarm,            SLOT( 0),        0,     24,
        "",                     "!Disarm!",		"", "fast
healing", SPLIT

    },
 
    {
        "dodge",
        { 20, 22,  1, 13, 1, 18, 18, 9, 18, 20, 20, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        spell_null,             TAR_IGNORE,             POS_FIGHTING,
        &gsn_dodge,             SLOT( 0),        0,     0,
        "",                     "!Dodge!",		"", NULL, SPLIT

    },
 
    {
        "enhanced damage",
        { 37, 30, 25, 1, 3, 11, 5, 7, 5, 37, 37, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        spell_null,             TAR_IGNORE,             POS_FIGHTING,
        &gsn_enhanced_damage,   SLOT( 0),        0,     0,
        "",                     "!Enhanced Damage!",	"", "critical
strike", SPLIT

    },

    {
        "envenom",
        { 35, 37, 30, 36, 53, 16, 53, 37, 37, 36, 25, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_null,		TAR_IGNORE,	  	POS_RESTING,
	&gsn_envenom,		SLOT(0),	0,	36,
	"",			"!Envenom!",		"", NULL, SPLIT

    },

    {
        "hand to hand",
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_null,		TAR_IGNORE,		POS_FIGHTING,
	&gsn_hand_to_hand,	SLOT( 0),	0,	0,
	"",			"!Hand to Hand!",	""
    },

    {
        "round",
        { 40, 6, 40, 40, 40, 40, 40, 40, 40, 40, 40, 40 },
        { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
        spell_null,             TAR_CHAR_OFFENSIVE,    POS_FIGHTING,
        &gsn_round,             SLOT( 0),        0,    12,
        "roundhouse",                "!Round!","",  "second attack", SPLIT

    },

    {
        "kick",
        { 53, 12, 14, 8, 10, 12, 8, 8, 10, 8, 8, 30 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        spell_null,             TAR_CHAR_OFFENSIVE,     POS_FIGHTING,
        &gsn_kick,              SLOT( 0),        0,     12,
        "kick",                 "!Kick!",		"", "dirt
kicking", SPLIT

    },

    {
        "parry",
        { 1, 20, 13, 1, 1, 11, 5, 5, 13, 5, 5, 30 },
        { 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        spell_null,             TAR_IGNORE,             POS_FIGHTING,
        &gsn_parry,             SLOT( 0),        0,     0,
        "",                     "!Parry!",		"", NULL, SPLIT

    },

    {
        "wanted",
        { 53, 53, 53, 53, 20, 53, 53, 53, 53, 53, 53, 53 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        spell_null,             TAR_IGNORE,           POS_FIGHTING,
        &gsn_wanted,            SLOT( 0),         0,    0,
        "",                     "!Wanted!",            "", NULL, SPLIT

    },

    {
        "rescue",
        { 1, 53, 53, 1, 1, 53, 10, 20, 30, 20, 20, 50 },
        { 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        spell_null,             TAR_IGNORE,             POS_FIGHTING,
        &gsn_rescue,            SLOT( 0),        0,     12,
        "",                     "!Rescue!",		"", NULL, SPLIT

    },

    {
        "trip",
        { 1, 53, 1, 13, 18, 8, 25, 25, 20, 25, 25, 10 },
        { 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_null,		TAR_IGNORE,		POS_FIGHTING,
	&gsn_trip,		SLOT( 0),	0,	36,
	"trip",			"!Trip!",		"", NULL, SPLIT

    },
 
    {
        "second",
        { 1, 24, 12, 5, 8, 10, 25, 8, 10, 25, 25, 17 },
        { 5, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        spell_null,             TAR_IGNORE,             POS_FIGHTING,
        &gsn_second,            SLOT( 0),       0,      36,
        ""                      "!Second!",             "","", NULL, SPLIT

    },

    {
        "second attack",
        { 30, 24, 12, 5, 8, 10, 25, 8, 10, 25, 25, 14 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        spell_null,             TAR_IGNORE,             POS_FIGHTING,
        &gsn_second_attack,     SLOT( 0),        0,     0,
        "",                     "!Second Attack!",	"", "third
attack", SPLIT

    },

    {
        "third attack",
        { 37, 35, 24, 12, 11, 16, 27, 25, 32, 35, 35, 35 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        spell_null,             TAR_IGNORE,             POS_FIGHTING,
        &gsn_third_attack,      SLOT( 0),        0,     0,
        "",                     "!Third Attack!",	"", NULL, SPLIT

    },

/* non-combat skills */

    { 
        "fast healing",
        { 15, 9, 16, 6, 7, 9, 3, 6, 16, 16, 16, 23 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_null,		TAR_IGNORE,		POS_SLEEPING,
	&gsn_fast_healing,	SLOT( 0),	0,	0,
	"",			"!Fast Healing!",	"", "berserk",
SPLIT

    },

    {
        "haggle",
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_null,		TAR_IGNORE,		POS_RESTING,
	&gsn_haggle,		SLOT( 0),	0,	0,
	"",			"!Haggle!",		"", NULL, SPLIT

    },
 
    {
        "camo",
        { 33, 33, 6, 18, 40, 8, 19, 2, 18, 32, 32, 12 },
        { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
        spell_null,            TAR_IGNORE,          POS_RESTING,
        &gsn_camo,             SLOT( 0),       0,   12,
        "",                    "!Camo!",            "", "dodge", SPLIT

    },

    {
        "hide",
        { 53, 53,  1,  12, 53, 4, 12, 4, 12, 12, 22, 8 },
        { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
	spell_null,		TAR_IGNORE,		POS_RESTING,
	&gsn_hide,		SLOT( 0),	 0,	12,
	"",			"!Hide!",		"", "camo", SPLIT

    },

    {
        "lore",
        { 20, 20, 18, 21, 19, 19, 20, 18, 20, 20, 20, 20 },
        { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
	spell_null,		TAR_IGNORE,		POS_RESTING,
	&gsn_lore,		SLOT( 0),	0,	36,
	"",			"!Lore!",		"", NULL, SPLIT

    },

    {
        "meditation",
        { 6, 6, 15, 15, 12, 16, 6, 16, 53, 5, 6, 2 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_null,		TAR_IGNORE,		POS_SLEEPING,
	&gsn_meditation,	SLOT( 0),	0,	0,
	"",			"Meditation",		"", NULL, SPLIT

    },

    {
        "peek",
        {  28, 21, 1, 53, 53, 14, 53, 30, 30, 53, 20, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_null,		TAR_IGNORE,		POS_STANDING,
	&gsn_peek,		SLOT( 0),	 0,	 0,
	"",			"!Peek!",		"", "pick lock",
SPLIT

    },

    {
        "pick lock",
        { 53, 53,  7, 53, 53, 25, 53, 53, 53, 53, 53, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_null,		TAR_IGNORE,		POS_STANDING,
	&gsn_pick_lock,		SLOT( 0),	 0,	12,
	"",			"!Pick!",		"", "sharpen",
SPLIT

    },

    {
        "sneak",
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_null,		TAR_IGNORE,		POS_STANDING,
	&gsn_sneak,		SLOT( 0),	 0,	12,
	"",			"You no longer feel stealthy.",	"",
"hide", SPLIT

    },

    {
        "steal",
        { 53, 53, 5, 53, 53, 20, 53, 53, 53, 53, 53, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_null,		TAR_IGNORE,		POS_STANDING,
	&gsn_steal,		SLOT( 0),	 0,	24,
	"",			"!Steal!",		"", "peek", SPLIT

    },

    {
        "scrolls",
        {  1,  1,  1,  1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_null,		TAR_IGNORE,		POS_STANDING,
	&gsn_scrolls,		SLOT( 0),	0,	24,
	"",			"!Scrolls!",		"", NULL, SPLIT

    },

    {
        "staves",
        {  1,  1,  1,  1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_null,		TAR_IGNORE,		POS_STANDING,
	&gsn_staves,		SLOT( 0),	0,	12,
	"",			"!Staves!",		"", NULL, SPLIT

    },
    
    {
        "wands",
        {  1,  1,  1,  1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_null,		TAR_IGNORE,		POS_STANDING,
	&gsn_wands,		SLOT( 0),	0,	12,
	"",			"!Wands!",		"", NULL, SPLIT

    },

    {
        "recall",             
        {  1,  1,  1,  1, 1, 1, 1, 1, 1, 1, 1, 1 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	spell_null,		TAR_IGNORE,		POS_STANDING,
	&gsn_recall,		SLOT( 0),	0,	12,
	"",			"!Recall!",		"", NULL, SPLIT

    },

    {
        "sharpen",           
        { 30, 30, 30, 18, 25, 30, 30, 20, 17, 30, 30, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        spell_null,             TAR_IGNORE,            POS_RESTING,
        &gsn_sharpen,           SLOT( 0),        0,    36,
        "",                     "!Sharpen!",           "", NULL, SPLIT

    },

    {
        "butcher",
        { 30, 30, 30, 27, 30, 30, 30, 1, 15, 30, 30, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        spell_null,             TAR_IGNORE,            POS_STANDING,
        &gsn_butcher,           SLOT( 0),        0,     36,
        "",                     "!Butcher!",            "", NULL, SPLIT

    },

    {
        "skin",
        { 30, 30, 30, 4, 30, 30, 30, 7, 14, 30, 30, 50 },
        { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        spell_null,             TAR_IGNORE,            POS_STANDING,
        &gsn_skin,              SLOT( 0),        0,     36,
        "",                     "!Skin!",               "", NULL, SPLIT

    },

    {
        "push",
        { 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5 },
        { 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 },
        spell_null,           TAR_IGNORE,           POS_STANDING,
        &gsn_push,            SLOT( 0),         0,     36,
        "",                   "!Push!",                "", NULL, SPLIT

    },

    {
        "drag", 
        { 1, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53, 53 },
        { 5, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 },
        spell_null,           TAR_IGNORE,        POS_STANDING,
        &gsn_drag,            SLOT( 0),        0,      36,
        "",                   "!Drag!",                "", NULL, SPLIT

    }

};

const   struct  group_type      group_table     [MAX_GROUP]     =
{

    {
        "rom basics",           { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ "sword", "recall", "hand to hand", "drag", "dagger", "second" }
    },

    {
        "adv basics",          { 0, -1, -1, -1, -1, -1, -1, -1, -1, 0, 0, -1 },
	{ "shield block", "rescue", "parry", "trip", }
    },

    {
        "mage basics",          { 0, -1, -1, -1, -1, -1, -1, -1, -1, 0, 0, -1 },
	{ "armor", "meditation" }
    },

    {
        "cleric basics",        { -1, 0, -1, -1, 0, -1, 0, -1, -1, -1, -1, -1 },
	{ "mace", "meditation" }
    },
   
    {
        "thief basics",         { -1, -1, 0, -1, -1, 0, -1, -1, -1, -1, -1, -1 },
	{ "whip", "staff" }
    },

    {
        "warrior basics",       { -1, -1, -1, 0, 0, -1, -1, 0, 0, -1, -1, -1 },
	{ "weaponsmaster", "bash", "disarm" }
    },

    {
        "adv default",         { 40, -1, -1, -1, -1, -1, -1, -1, -1 ,40,40,-1 },
        { "bash" } 
    },

    {
        "mage default",         { 40, -1, -1, -1, -1, -1, -1, -1, -1 ,40,40,-1 },
        { "create water", "infravision", "fly", "magic missile" }
    },

    {
        "cleric default",       { -1, 40, -1, -1, 40, -1, 40, -1, -1, -1, -1, -1 },
        { "cure light", "cause light", "heat metal", "true path" }

    },
 
    {
        "thief default",        { -1, -1, 40, -1, -1, 40, -1, -1, -1, -1, -1, -1 },
        { "steal", "sneak", "backstab" }
    },

    {
        "warrior default",      { -1, -1, -1, 40, 40, -1, -1, 40, 40, -1,-1,-1 },
	{ "weaponsmaster" }
    },

    {   "cavalier default",     { -1, 40, -1, 40, 40, -1, -1, -1, -1, -1,-1,-1 },
        { "axe", "sword", "polearm", "cavone", "cavtwo", "cavthr" }
    },

    {
        "assassin default",   { -1, -1, 40, -1, -1, 40, -1, -1, -1, -1, -1,-1},
        { "dagger", "sword", "assone", "asstwo" }
    },

    {
        "healer default",    { -1, 40, -1, -1, -1, -1, 40, -1, -1, -1, -1,-1},
        { "flail", "staff", "mace", "whip", "heaone", "heatwo", 
          "heathr", "heafou", "heafiv", "shockshield" }
    },

    {
        "hunter default",    { 1, 1, 1, 1, 1, 1, 1, 40, 1, 1, 1, -1},
        { "weaponsmaster", "hunone", "huntwo" }
    },

    {
        "barbarian default",   { -1, -1, -1, 40, -1, -1, -1, -1, 40, -1,-1,-1 },
        { "axe", "sword", "warone", "wartwo", "thione", "berserk" }
    },

    {
        "crafter default",  { 40, -1, -1, -1, -1, -1, -1, -1, -1, 40, -1,-1},
        { "dagger", "combat", "invocation", "creation", "draconian",
          "enchantment", "enhancement", "meditation", "parry" }
    },

    {
        "necromancer default",  { 40, -1, -1, -1, -1, -1, -1, -1, -1, -1,40,-1 },
        { "dagger", "necone", "nectwo", "necthr", "iceshield" }
    },

    {
        "psi default", { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 50 },
        { "psione", "psitwo", "hide", "camo", "second", "second attack",
          "trip" }
    },

    {
        "weaponsmaster",        { 40, 40, 40, 20, 20, 20, 20, 20, 20, 20, 20,20 },
	{ "axe", "dagger", "flail", "mace", "polearm", "staff",
          "sword","whip" }
    },

    {
        "combat",               { -1, 5, -1, 8, 30, 23, 37, 35, 37, 25, 15, 20},
	{ "demonfire", "earthquake", "flamestrike",
	  "heat metal", "ray of truth", "calm", "charm person", "sleep",
          "bless", "calm", "frenzy", "holy word", "remove curse" }
    },

    {
        "invocation",               { 6, -1, 10, 10, 10, 20,32,30,37,22,16,20 },
	{ "acid blast", "burning hands", "chain lightning",
	  "colour spray", "fireball", "lightning bolt", "magic missile", }
    },

    {
        "creation",             { 4, 4, 8, 8, 15, 15, 15, 15, 15, 15, 15, 15 },
	{ "continual light", "yuins feast", "create spring", "create
water",
	  "create rose", "floating disc" }
    },

    {
        "draconian",            { 8, -1, -1, -1, -1, -1, -1, -1, -1, 8, 8, 8 },
	{ "acid breath", "fire breath", "frost breath", "gas breath",
	  "lightning breath"  }
    },

    {
        "enchantment",          { 6, 25, 24, 20, 10, 10, 10, 10, 10, 10,10,10 },
	{ "enchant armor", "enchant weapon", "fireproof", "recharge", "calm",
          "charm person", "sleep" }
    },

    { 
        "enhancement",          { 5, -1, 9, 9,15,20,30,32,25,15,15,15 },
	{ "giant strength", "haste", "infravision", "refresh", "burning hands",
          "fly", "teleport", "control weather", "change sex", "shocking grasp", 
          "pass door", "word of recall" }
    },

    {
        "warone",              { 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 },
	{ "parry", "enhanced damage", "rescue", "shield block",
          "dirt kicking", "second attack", "fast healing",
          "kick" }
    },

    {
        "wartwo",             { 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 },
        { "disarm", "third attack", "dodge", "bash", "trip", 
          "meditation", "berserk", "lore", "sharpen", "butcher", 
          "second", "skin" }
    },

    {
        "psione",                 { 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 },
        { "aurasight", "combat mind", "awe", "true path", "shadowpet",
          "poison sense", "true pain", "levitate", "astral walk",
          "life detect", "adrenalin", "mind bar" }
    },

    {
        "psitwo",                 { 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
        { "control body", "drunken", "domination", "fireblast",
          "project force", "complete heal", "cell adjust",
          "flesh armor", "life drain" }
    }
          
};
