/*******************************************************************************************
*
*   raylib [core] example - basic window
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2016 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#define MAX_ENEMIGOS 70 //cantidad de bolas
#define MAX_EXPLOSIONES 70 //cantidad de explosiones

typedef struct Enemies{ //estructura de los enemigos
    int speed;
    Rectangle body;
} Enemies;
typedef struct Explo{ //estructura de los explosivos
    Rectangle frameRec;
    bool blow;
} Explo;

int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 720;
    int screenHeight = 980;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    Rectangle fondojuego = { 0, 0, screenWidth, screenHeight }; //fondo
    Texture2D mira = LoadTexture("mira.png"); //textura de la mira
    Texture2D texture = LoadTexture("explosion.png"); //textura de la explosion
    
    Enemies bola [MAX_ENEMIGOS];
    for(int i = 0; i < MAX_ENEMIGOS; i++) //array con velocidad, tamaño, posicion de los enemigos, posicion y tamaño del sprite
    {
        bola[i].body.width = 40;
        bola[i].body.height = 40;
        bola[i].body.x = GetRandomValue(0, screenWidth-bola[i].body.width);
        bola[i].body.y = GetRandomValue(0, screenHeight * -2);
        bola[i].speed = -3;
    }     
    Explo sivos [MAX_EXPLOSIONES];
    for(int i = 0; i < MAX_EXPLOSIONES; i++) //array con velocidad, tamaño, posicion de los enemigos, posicion y tamaño del sprite
    {
        sivos[i].frameRec.x = 0;
        sivos[i].frameRec.y = 0;
        sivos[i].frameRec.width = texture.width/4;
        sivos[i].frameRec.height = texture.height/4;
        sivos[i].blow = false;
        
    }       
    Rectangle fondo = { 0, 0, screenWidth, screenHeight }; //fondo gameover
    Vector2 MiraPosition = { 0.0f, 0.0f };
    Vector2 explosionPos = { 0.0, 0.0 };//posicion inicial explosion
    HideCursor();
    
   int currentFrameX = 0;//frames de explosiones
   int currentFrameY = 0;    
    
    int puntoplayer = 0; //puntuacion
    int hightscore = 0; //record de puntuacionº
    
    bool GameOver = true;
    bool pause = false;
    int frameop = 0; //frames de la animacion de explosion
    int framesCounter = 30; //frames del pausa
    SetTargetFPS(30);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        
        MiraPosition = GetMousePosition();
        
        if(GameOver) 
            {
                if (!pause)
                    {
                     
                        for(int i = 0; i < MAX_ENEMIGOS; i++)
                            {        
                                if(bola[i].body.y >= screenHeight + 40) //reset de enemigos
                                {
                                    bola[i].body.x = GetRandomValue(0, screenWidth-bola[i].body.width);
                                    bola[i].body.y = GetRandomValue(0, screenHeight * -2);                                    
                                }
                                bola[i].body.y -= bola[i].speed; //direccion de los enemigos
                                if(puntoplayer >= 500) //level de juego
                                    {
                                        bola[i].speed = -5;
                                    }
                                if(puntoplayer >= 1000) //level de juego
                                    {
                                       bola[i].speed = -7;
                                    }
                                if(puntoplayer >= 1500) //level de juego
                                    {
                                        bola[i].speed = -9;
                                    }
                                if(puntoplayer >= 2000) //level de juego
                                    {
                                        bola[i].speed = -15;
                                    }
                                for(int j = 0; j < MAX_EXPLOSIONES; j++)
                                {
                                    if(CheckCollisionPointRec(GetMousePosition(), bola[i].body))
                                        {
                                            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))//EXPLOSION
                                                {
                                                    sivos[j].blow = true;
                                                    explosionPos.x = bola[i].body.x;
                                                    explosionPos.y = bola[i].body.y;
                                                    bola[i].body.x = GetRandomValue(0, screenWidth-bola[i].body.width);
                                                    bola[i].body.y = GetRandomValue(0, screenHeight * -2);                          
                                                    puntoplayer += 10; //suma de puntuacion                                            
                                                }
                                            if(puntoplayer >= hightscore) //si el puntuaje supera el highscore
                                            {
                                                hightscore = puntoplayer;
                                            }                                                
                                        }                                                
                                    if(CheckCollisionPointRec(GetMousePosition(), fondojuego))
                                        {
                                            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                                                {
                                                    
                                                }
                                        }                                    
                                }
                            }
                            for(int i = 0; i < MAX_EXPLOSIONES; i++)
                            {
                                if(sivos[i].blow)//Efecto de explosion
                                {
                                    frameop++;         
                                    if(frameop >= 1)
                                        {
                                            frameop = 0;
                                            currentFrameX++;      
                                            if(currentFrameX >= 4)
                                                {
                                                    currentFrameX = 0;
                                                    currentFrameY++;
                                                    if(currentFrameY >= 4 )
                                                        {
                                                            currentFrameY = 0;
                                                            sivos[i].blow = false;
                                                            explosionPos.x = 0;
                                                            explosionPos.y = 0;
                                                        }
                                                }
                                        }
                                        sivos[i].frameRec.x = currentFrameX*texture.width/4;
                                        sivos[i].frameRec.y = currentFrameY*texture.height/4;
                                               
                                }                                
                            }                            
                    }
            }
        if (IsKeyPressed(KEY_P)) //pausa
            {
                pause = !pause;
                framesCounter = 30;
            }
        if(!GameOver)
            {
                if(IsKeyPressed (KEY_ENTER)) //tecla de reset
                    {
                        for(int i = 0; i < MAX_ENEMIGOS; i++) 
                        {
                            bola[i].speed = -3;
                            bola[i].body.x = GetRandomValue(0, screenWidth-bola[i].body.width);
                            bola[i].body.y = GetRandomValue(0, screenHeight * -2);
                            puntoplayer = 0;                        
                            GameOver = true;  
                            pause = false;                            
                        }                        
                    }           
            }
            else 
            {
                framesCounter++;
            }
             
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);
            
            DrawRectangleRec(fondojuego, YELLOW);//fondo del mal
            DrawText(FormatText("%i", puntoplayer), 100, 10, 80, RED); //puntuacion
            DrawText(FormatText("%i", hightscore), 300, 10, 80, GREEN); //alta puntuacion
            for(int i = 0; i < MAX_ENEMIGOS; i++)
            {                
                DrawRectangle(bola[i].body.x,bola[i].body.y,bola[i].body.width,bola[i].body.height,RED); //enemigos
            }
            for(int i = 0; i < MAX_EXPLOSIONES; i++)
            {
                if(sivos[i].blow) //Dibujo de la explosion
                    {
                        DrawTextureRec(texture, sivos[i].frameRec, explosionPos, WHITE);
                    }                
            }            
                
                if(pause)
                {
                    if((framesCounter/50)%2) DrawText("PAUSE", (screenWidth - MeasureText("PAUSE", 85))/2, screenHeight/2.25 -5, 75, RED); //pausa
                }            
            if(!GameOver) 
            {
                DrawRectangleRec(fondo,BLACK); //fondo game over
                DrawText("GAMEOVER", 450, 300, 60, LIGHTGRAY);
                DrawText("Press ENTER to restart", 350, 430, 60, LIGHTGRAY); // boton de reset
            }
            DrawTextureV(mira, MiraPosition, WHITE);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    UnloadTexture(texture);
    UnloadTexture(mira);
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}