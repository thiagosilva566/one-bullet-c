#pragma once 

#include "raylib/raylib.h"

typedef struct Player {
    Vector2 center;
    Vector2 velocity;
    float rotationalVelocity;
    float radius;
    float angle;
    Color color;
} Player;

Player *createPlayer( float xIni, float yIni, float radius, Color color );
void destroyPlayer( Player *player );
void updatePlayer( Player *player, float delta );
void drawPlayer( const Player *player );
