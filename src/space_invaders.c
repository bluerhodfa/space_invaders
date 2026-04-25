#include "raylib.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 750
#define MAX_ALIENS 48
#define MAX_SHOTS 50
#define MAX_SHOTS_ALIENS 25
#define DEVELOPER "Programmed in C/raylib by Ira Theobold, 2026"
#define VERSION 0.1


typedef enum options {MENU, GAMEPLAY, GAMEOVER} options;


typedef struct 
{
    Vector2 position;
    Vector2 size;
    int direction;
    bool active;
    int curentFrame;
    float timeFrame;
    Texture2D *frames;
    int numFrames;
} spaceShip;

typedef struct 
{
    Vector2 position;
    Vector2 size;
    int direction;
    bool active;
    int curentFrame;
    float timeFrame;
    Texture2D *frames;
    int numFrames;
} alien;

typedef struct 
{
    Vector2 position;
    Vector2 size;
    bool active;
} shot_aliens;

typedef struct 
{
    Vector2 position;
    Vector2 size;
    int direction;
    int speed;
    bool active;
    int curentFrame;
    float timeFrame;
    Texture2D *frames;
    int numFrames;
} mysterySpaceShip;

typedef struct 
{
    Vector2 position;
    Vector2 size;
    bool active;
} Shot;

mysterySpaceShip mysteryShip = {0};
spaceShip ship = {0};
alien   alien1 = {0};
alien   alien2 = {0};
alien   alien3 = {0};

int level = 1;
options optionsActual = MENU;
Shot shots[MAX_SHOTS] = { 0 };

int currentScore = 0;
int score = 0;
int totalScore = 0;
int highScore = 0;
int lives = 3;
bool alive = false;

// Functions
// drawScreen
//----------------------------------------------------------------------------------
    void drawScreen ( void ) 
{
// Create the default screen layout
// Update rectangle bounds
//----------------------------------------------------------------------------------
        Rectangle rec = 
        {
           WINDOW_WIDTH/2 - (WINDOW_WIDTH-20)/2,
           WINDOW_HEIGHT/2 - (WINDOW_HEIGHT-100)/2,
           WINDOW_WIDTH-20, WINDOW_HEIGHT-100
        };
        DrawRectangleRoundedLinesEx( rec, 0.1f, 20, 1.0f, LIGHTGRAY); // Draw rectangle with rounded edges outline
//--------------------------------------------------------------------------------------
// Draw the base window layoot and titles
        DrawText("SCORE", 10, 5, 20, LIGHTGRAY);
        DrawText("HI-SCORE", 690, 5, 20, LIGHTGRAY);
        DrawText("LEVEL: 1" , 690, 720, 20, LIGHTGRAY);
        DrawText(DEVELOPER  , (WINDOW_WIDTH/2) - (sizeof(DEVELOPER)*2) , 730, 10, LIGHTGRAY);

};
// updateScore
//----------------------------------------------------------------------------------
    int updateScore( int score, int highScore )
{
        currentScore = score + 1;
   //      highScore =  1;
            if(currentScore > highScore) 
            {
                highScore = currentScore;
//                saveHighScoreToFile( highScore );
            };

        DrawText(TextFormat("%06d",currentScore), 10, 25, 20, LIGHTGRAY);
        DrawText(TextFormat("%06d",highScore), 720, 25, 20, LIGHTGRAY);
        // checkForHighScore( highScore );
        return currentScore;


};

// fire laser
    void fireLaser( void ) 
    {
        bool alienHit = false;
        if (alienHit == true) 
        {
            updateScore(0, 0);
        }

    }

//----------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    InitAudioDevice();
    Sound menu = LoadSound("../resources/sounds/spaceinvaders.ogg");
    Sound gameplay = LoadSound("../resources/sounds/music.ogg");
    Sound gameover = LoadSound("../resources/sounds/spaceinvaders.ogg");
    Sound laserFire = LoadSound("../resources/sounds/laser.ogg");
    // Sound explosion = LoadSound("../resources/sounds/explosion.ogg");

    SetSoundVolume(menu, 0.5f);
    SetSoundVolume(gameplay, 0.5f);
    SetSoundVolume(gameover, 0.5f);
    double timeLastSpawn = 0.0;
    int mysteryShipSpawnInterval = GetRandomValue(10, 20);
    PlaySound(menu);

    //options currentOption = MENU;

    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Space Invaders");

// -----------------------------------------------------------------------------------------
    Texture2D alien1Frames[1];

    alien1Frames[0] = LoadTexture("../resources/images/alien1.png");
    alien1.frames = alien1Frames;
    alien1.numFrames = 1;
    alien1.timeFrame = 0;
    alien1.size = (Vector2){ alien1Frames[0].width, alien1Frames[0].height};
    alien1.position = (Vector2){50 - alien1Frames[0].width/2 ,WINDOW_HEIGHT-600};
// -----------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------
    Texture2D alien2Frames[1];

    alien2Frames[0] = LoadTexture("../resources/images/alien2.png");
    alien2.frames = alien2Frames;
    alien2.numFrames = 1;
    alien2.timeFrame = 0;
    alien2.size = (Vector2){ alien2Frames[0].width, alien2Frames[0].height};
    alien2.position = (Vector2){50 - alien2Frames[0].width/2 ,WINDOW_HEIGHT-550};
// -----------------------------------------------------------------------------------------

// -----------------------------------------------------------------------------------------
    Texture2D alien3Frames[1];

    alien3Frames[0] = LoadTexture("../resources/images/alien3.png");
    alien3.frames = alien3Frames;
    alien3.numFrames = 1;
    alien3.timeFrame = 0;
    alien3.size = (Vector2){ alien3Frames[0].width, alien3Frames[0].height};
    alien3.position = (Vector2){50 - alien3Frames[0].width/2 ,WINDOW_HEIGHT-450};
// -----------------------------------------------------------------------------------------

    
    Texture2D shipFrames[1];
    static int timesshot = 0;

    shipFrames[0] = LoadTexture("../resources/images/spaceship.png");
    ship.frames = shipFrames;
    ship.numFrames = 1;
    ship.timeFrame = 0;
    ship.size = (Vector2){ shipFrames[0].width , shipFrames[0].height };
    ship.position = (Vector2){WINDOW_WIDTH/2 - shipFrames[0].width/2 , WINDOW_HEIGHT-100};  // Start in the middle

    // Mystery ship
    Texture2D mysteryShipFrames[1];

    mysteryShipFrames[0] = LoadTexture("../resources/images/mystery.png");
    mysteryShip.frames = mysteryShipFrames;
    mysteryShip.numFrames = 1;
    mysteryShip.timeFrame = 0;
    mysteryShip.speed = 1;
    mysteryShip.size = (Vector2){ mysteryShipFrames[0].width , mysteryShipFrames[0].height };
    mysteryShip.position = (Vector2){ WINDOW_WIDTH - 900 , WINDOW_HEIGHT-650};
       

// get a randow side to start the mystery ship from
        int side = GetRandomValue(0, 1);
        if(side == 0) 
        {
            mysteryShip.position.x = 25;
            mysteryShip.speed = 3;
        } else 
        {
            mysteryShip.position.x = GetScreenWidth() - mysteryShipFrames[0].width + 50 ;
            mysteryShip.speed = -3;
        }
            mysteryShipSpawnInterval = GetRandomValue(10, 20);
            double currentTime = GetTime();

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //Texture2D imageGamePlay = LoadTexture("images/universe.jpg");

    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
       // float deltaTime = GetFrameTime();
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        //DrawTexture(imageGamePlay, 0, 0 , WHITE);
        DrawText(TextFormat("%06d",currentScore), 10, 25, 20, LIGHTGRAY);
        DrawText(TextFormat("%06d",highScore), 720, 25, 20, LIGHTGRAY);

            ClearBackground(BLACK);
            
            switch(optionsActual) 
            {
                case MENU:
                break;

                case GAMEPLAY:
                break;

                case GAMEOVER:

                break;
            }

            optionsActual = GAMEPLAY;
        
            drawScreen();
            
            alive = true;
            // set up for the mystery ship 
            if(currentTime - timeLastSpawn > mysteryShipSpawnInterval) {
               alive = true;
               //DrawTexture(mysteryShipFrames[0], mysteryShip.position.x , mysteryShip.position.y , WHITE);
               //mysteryship.Spawn();
               timeLastSpawn = GetTime();
            }

            if(alive) 
            {
                mysteryShip.position.x += mysteryShip.speed;

            if(mysteryShip.position.x > GetScreenWidth() - mysteryShipFrames[0].width -25 || mysteryShip.position.x < 25) 
            {
                //alive = false;
            }
                DrawTexture(mysteryShipFrames[0], mysteryShip.position.x , mysteryShip.position.y , WHITE);
            }

           // DrawText(TextFormat("mysteryShip.position.x %d mysterySkip.position.y %d",mysteryShip.position.x, mysteryShip.position.y),70 ,50 , 20, YELLOW);
            DrawTexture(shipFrames[0], ship.position.x, ship.position.y, WHITE);

            int xoffset = 50;
            int yoffset = 55;
            for (int i = 0; i < MAX_ALIENS / 4; i++) 
            {
               DrawTexture(alien1Frames[0], alien1.position.x + xoffset, alien1.position.y, WHITE);
               DrawTexture(alien2Frames[0], alien2.position.x + xoffset, alien2.position.y, WHITE);
               DrawTexture(alien3Frames[0], alien3.position.x + xoffset, alien3.position.y, WHITE);
               for (int j = 0; j  < 2; j++) 
               {
        //            DrawTexture(alien1Frames[0], alien1.position.x + xoffset, alien1.position.y + yoffset, WHITE);
                    DrawTexture(alien2Frames[0], alien2.position.x + xoffset, alien2.position.y + yoffset, WHITE);
                    DrawTexture(alien3Frames[0], alien3.position.x + xoffset, alien3.position.y + yoffset, WHITE);
               };
               xoffset += 55;
            };


//            DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
            for (int i = 0; i < MAX_SHOTS; i++) shots[i].active = false;


        // move the spaceship   
        //----------------------------------------------------------------------------------
            if (IsKeyDown(KEY_LEFT) && ship.position.x > 0)
               ship.position.x -= 5; 
            if (IsKeyDown(KEY_RIGHT) && ship.position.x + ship.size.x < WINDOW_WIDTH)
                   ship.position.x += 5;     

            if (IsKeyDown(KEY_SPACE)) 
            { 
                 PlaySound(laserFire);
                 fireLaser();
             }
            if (timesshot <= 0 && IsKeyDown(KEY_SPACE)) 
            {
                for (int i = 0; i < MAX_ALIENS; i++) 
                {
                    if (!shots[i].active) 
                    {
                        shots[i].position = (Vector2){ ship.position.x + ship.size.x / 2 - 2, ship.position.y };
                        shots[i].size = (Vector2){4, 12};
                        shots[i].active = true;
                        timesshot = 25;
                        break;
                    }
                }
            }
        //----------------------------------------------------------------------------------


        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    void UnloadTexture2D(Texture2D alien1Frames[0]);     
    void UnloadTexture2D(Texture2D alien2Frames[0]);     
    void UnloadTexture2D(Texture2D alien3Frames[0]);     
    void UnloadTexture2D(Texture2D shipFrames[0]);     
    void UnloadTexture2D(Texture2D mysteryShipFrames[0]);     
    void UnloadSound(Sound menu);
    void UnloadSound(Sound gameplay);
    void UnloadSound(Sound gameover);
    void UnloadSound(Sound explosion);
    void UnloadSound(Sound laser);
    void CloseAudioDevice();     // Close audio device

    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
