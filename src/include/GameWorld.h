#pragma once

#include "Player.h"

typedef struct GameWorld {
    Player *player;
} GameWorld;

GameWorld *createGameWorld( void );

void destroyGameWorld( GameWorld *gw );

void updateGameWorld( GameWorld *gw, float delta );

void drawGameWorld( GameWorld *gw );
