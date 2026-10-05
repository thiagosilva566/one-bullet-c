#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "include/raylib/raylib.h"

#include "include/Player.h"

static void updatePlayerVelocity( Player *player, float delta );
static void updatePlayerRotationalVelocity( Player *player, float delta );

Player *createPlayer( float xIni, float yIni, float radius, Color color ) {

    Player *player = (Player*) malloc(sizeof(Player));

    player->center = (Vector2) { xIni, yIni };
    player->velocity = (Vector2) { 0, 0 };
    player->rotationalVelocity = 0;

    player->radius = radius;
    player->angle = 0;
    player->color = color;

    return player;

}

void destroyPlayer( Player *player ) {
    
    if ( player != NULL ) {
        free(player);
    }

}

void updatePlayer( Player *player, float delta ) {

    // records the inputs
    bool spaceKey = IsKeyDown( KEY_SPACE );

    // if space is pressed, reset the velocity and update the player rotational velocity
    if ( spaceKey ) {
        player->velocity.x = 0;
        player->velocity.y = 0;
        updatePlayerRotationalVelocity( player, delta );

    // else, reset the rotational velocity and update player velocity
    } else { 
        player->rotationalVelocity = 0;
        updatePlayerVelocity( player, delta );
    }

    // update the coordinates of the center
    player->center.x += player->velocity.x * delta;
    player->center.y += player->velocity.y * delta;

    // update the player oritentation
    player->angle += player->rotationalVelocity * delta;

}

void drawPlayer( const Player *player ) {

    DrawCircleV( player->center, player->radius, player->color );

    // to provide guidance
    float n = 20;
    Vector2 endCord = (Vector2) {
        .x = player->center.x + n * sin(player->angle),
        .y = player->center.y + n * cos(player->angle)
    };
    DrawLineEx( player->center, endCord, 5.0, RED );
}

static void updatePlayerVelocity( Player *player, float delta ) {

    float velLimit = 1000;
    float acceleration = 5000;

    // records the inputs
    bool rightKey = IsKeyDown( KEY_RIGHT ) || IsKeyDown( KEY_D ); 
    bool leftKey = IsKeyDown( KEY_LEFT ) || IsKeyDown( KEY_A ); 
    bool upKey = IsKeyDown( KEY_UP ) || IsKeyDown( KEY_W );
    bool downKey = IsKeyDown( KEY_DOWN ) || IsKeyDown( KEY_S );

    // movement in the x-axis

    // the player stops if no key is pressed
    if ( !rightKey && !leftKey ) {
        player->velocity.x = 0;
    }

    // right movement 
    if ( rightKey ) {

        // stops the player if he was walking to the left
        if ( player->velocity.x < 0 ) {
            player->velocity.x = 0;
        }

        // applies acceleration and checks whether it has reached
        // the speed limit
        player->velocity.x += acceleration * delta;
        if ( player->velocity.x > velLimit ) player->velocity.x = velLimit;
    }

    // left movement
    if ( leftKey ) {

        // stops the player if he was walking to the right
        if ( player->velocity.x > 0 ) {
            player->velocity.x = 0;
        }

        // applies acceleration and checks whether it has reached
        // the speed limit
        player->velocity.x -= acceleration * delta;
        if ( player->velocity.x < -velLimit ) player->velocity.x = -velLimit;
    }

    // the player stors if both keys are pressed
    if ( rightKey && leftKey ) {
        player->velocity.x = 0;
    }

    // movement in the y-axis

    // the player stops if no key is pressed
    if ( !downKey && !upKey ) {
        player->velocity.y = 0;
    }

    // down movement
    if ( downKey ) {

        // stops the player if he was walking to the up 
        if ( player->velocity.y < 0 ) {
            player->velocity.y = 0;
        }

        // applies acceleration and checks whether it has reached
        // the speed limit
        player->velocity.y += acceleration * delta;
        if ( player->velocity.y < -velLimit ) player->velocity.y = velLimit;
    }

    // up movement
    if ( upKey ) {

        // stops the player if he was walking to the down
        if ( player->velocity.y > 0 ) {
            player->velocity.y = 0;
        }

        // applies acceleration and checks whether it has reached
        // the speed limit
        player->velocity.y -= acceleration * delta;
        if ( player->velocity.y < -velLimit ) player->velocity.y = -velLimit;
    }

    // the player stors if both keys are pressed
    if ( downKey && upKey ) {
        player->velocity.y = 0;
    }


}

static void updatePlayerRotationalVelocity( Player *player, float delta ) {

    float rotationalSpeed = PI * 2;
    
    // if no key is pressed, the initial value is not overwritten
    // so the player will not spin
    player->rotationalVelocity = 0;

    // records the inputs
    bool rightKey = IsKeyDown( KEY_RIGHT ) || IsKeyDown( KEY_D ); 
    bool leftKey = IsKeyDown( KEY_LEFT ) || IsKeyDown( KEY_A ); 

    // rotational movement
    if ( leftKey ) {
        player->rotationalVelocity = rotationalSpeed ;
    }

    if ( rightKey ) {
        player->rotationalVelocity = -rotationalSpeed;
    }

    // the player stors if both keys are pressed
    if ( leftKey && rightKey ) {
        player->rotationalVelocity = 0;
    }

}
