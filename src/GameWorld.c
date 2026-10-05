#include <stdlib.h>

#include "include/raylib/raylib.h"

#include "include/GameWorld.h"
#include "include/Player.h"

GameWorld *createGameWorld( void ) {

    GameWorld *gw = (GameWorld*) malloc( sizeof( GameWorld ) );

    float radius = 12;
    float xIni = GetScreenWidth() / 2.0 - radius;
    float yIni = GetScreenHeight() / 2.0 - radius;
    Color color = RED;

    gw->player = createPlayer( xIni, yIni, radius, color );

    return gw;

}

void destroyGameWorld( GameWorld *gw ) {
    free( gw );
}

void updateGameWorld( GameWorld *gw, float delta ) {

    updatePlayer( gw->player, delta );
}

void drawGameWorld( GameWorld *gw ) {

    BeginDrawing();
    ClearBackground( WHITE );

    drawPlayer( gw->player );

    DrawFPS( 20, 20 );

    EndDrawing();

}
