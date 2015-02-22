#ifndef INCLUDED_GAME_H
#define INCLUDED_GAME_H

#include <assert.h>

typedef unsigned int   uint32;
typedef   signed int    int32;
typedef unsigned short uint16;
typedef   signed short  int16;
typedef unsigned char  uint8 ;
typedef   signed char   int8 ;


#pragma warning(disable:4244; disable:4305; disable:4018)

// virtual screen size
#define SIZE_X  480
#define SIZE_Y  360

// main.c
extern void error(char *s);
extern void ods(char *fmt, ...);


// game.c
extern void init_game(void);
extern void draw_main(void);
extern void process_tick(float dt);


#define BUTTON_MAX 15
typedef struct
{
   int id;
   uint8 buttons[BUTTON_MAX];
   float axes[4];
   float triggers[2];
} gamepad;

extern gamepad pads[4];


#endif
