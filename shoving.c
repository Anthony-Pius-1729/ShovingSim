#include "raylib.h"
#include <math.h>
#define WIDTH 1200
#define HEIGHT 650
#define RADIUS 25
#define N 200

typedef struct Position {
    float x;
    float y;
}Position;

typedef struct Speed {
    float speed_x;
    float speed_y;
}Speed;

typedef struct Ball {
    Position pos;
    Speed vel;
}Ball;

Ball Balls[N];

// void CheckCollision (Ball* a, Ball* b) {

//     double d = (pow((b->pos.y - a->pos.y), 2) + pow((b->pos.x - a->pos.x), 2));
//     double r = (2 * RADIUS) * (2 * RADIUS);

//     if ( d < r) {
//         a->vel.speed_x *= -1;
//         a->vel.speed_y *= -1;
//         b->vel.speed_x *= -1;
//         b->vel.speed_y *= -1;

//     }

// }

void InitBalls (Ball Balls[N]) {

    for (int i = 0; i < N; i++) {
        Balls[i].pos.x = GetRandomValue(RADIUS, WIDTH-RADIUS);
        Balls[i].pos.y = GetRandomValue(RADIUS, HEIGHT-RADIUS);
        Balls[i].vel.speed_x = GetRandomValue(-100, 100) / 100.0f;
        Balls[i].vel.speed_y = GetRandomValue(-100, 100) / 100.0f;
    }

}


void DrawBalls (int n) {
    for (int i = 0; i < N; i++) {
        DrawCircle(Balls[i].pos.x , Balls[i].pos.y, RADIUS, WHITE);
    }
}

double getDistance (Ball* a, Ball* b) {

    double dy = b->pos.y - a->pos.y;
    double dx = b->pos.x - a->pos.x;

    return dx*dx + dy*dy;
}

bool CheckCollision (Ball* a, Ball* b) {

    double d = getDistance(a, b);
    double r = 2* RADIUS;
    double r2 = r*r;

    if (d  < r2) return true;

    return false;
}



void UpdateBalls () {

    float deltaTime = GetFrameTime()*5;

    for (int i = 0; i < N; i++) {

        Balls[i].pos.y += Balls[i].vel.speed_y*deltaTime;
        Balls[i].pos.x += Balls[i].vel.speed_x*deltaTime;

        if (Balls[i].pos.x < RADIUS || Balls[i].pos.x > (WIDTH - RADIUS) ) {
            Balls[i].vel.speed_x *= -1;
        }

        if (Balls[i].pos.y < RADIUS || Balls[i].pos.y > (HEIGHT - RADIUS) ) {
            Balls[i].vel.speed_y *= -1;
        }

    }

    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            if (CheckCollision(&Balls[i], &Balls[j])){
                double d = sqrt(getDistance(&Balls[i], &Balls[j]));
                double overlap = 2*RADIUS - d;
                

                float nx = ( Balls[j].pos.x - Balls[i].pos.x ) / d;
                float ny = ( Balls[j].pos.y - Balls[i].pos.y ) / d;

                Balls[i].pos.x -= nx * (overlap / 2.0f);
                Balls[i].pos.y -= ny * (overlap / 2.0f);

                Balls[j].pos.x += nx * (overlap / 2.0f);
                Balls[j].pos.y += ny * (overlap / 2.0f);

                float vrelx = Balls[i].vel.speed_x - Balls[j].vel.speed_x;
                float vrely = Balls[i].vel.speed_y - Balls[j].vel.speed_y;

                float nvel = nx * vrelx + ny * vrely;

                float restitution = 0.8f;
                float impulse = -(1.0f + restitution) * nvel / 2.0f;

                Balls[i].vel.speed_x += impulse * nx;
                Balls[i].vel.speed_y += impulse * ny;

                Balls[j].vel.speed_x -= impulse * nx;
                Balls[j].vel.speed_y -= impulse * ny;


            }
        }
    }



}



int main () {

    InitWindow(WIDTH, HEIGHT, "Shoving Simulation");

    InitBalls (Balls);

    
    while (!WindowShouldClose()) {

        UpdateBalls ();

        BeginDrawing();

        ClearBackground(BLACK);

        DrawBalls(N);
        

        EndDrawing();


    }

    CloseWindow();


    return 0;
}