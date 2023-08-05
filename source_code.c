#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

bool processEvents()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            return true;
        }

        if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                    return true;
                    break;
                
                default:
                    break;
            }
        }
    }
    
    return false;
}

int drawTriangle(SDL_Renderer *renderer, float PosX, float PosY, int Size, float width, float mp)
{
    int Bottom_Left;
    int Bottom_Right;
    int Height = (int)PosY;

    for (int i = 0; i < Size; i++)
    {
        Bottom_Right = PosX+mp*i;
        Bottom_Left = PosX-mp*i;
        Height = PosY + width*i;

        if (Height >= 598 || Height <= 2)
        {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        } else 
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }

        SDL_RenderDrawPoint(renderer, Bottom_Left, (int)Height);
        SDL_RenderDrawPoint(renderer, Bottom_Right, (int)Height);
        
    }

    for (int i = 0; i < (Bottom_Right - Bottom_Left) || i < (Bottom_Left - Bottom_Right); i++)
    {
        if (i < (Bottom_Right - Bottom_Left)) 
        {
            SDL_RenderDrawPoint(renderer, Bottom_Left+i, Height);
        } else if (i < (Bottom_Left - Bottom_Right)) 
        {
            SDL_RenderDrawPoint(renderer, Bottom_Right+i, Height);
        }
        
        
    }

    printf("\nCoordinates are relative to window resolution(800x600)\nBottomLeft(X): %dpx\nBottomRight(X): %dpx\nHeight(Y): %dpx\n", Bottom_Left, Bottom_Right, Height);

    return Height;
}

void draw(SDL_Renderer *renderer, float *m, float *mp)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    int height;
    
    height = drawTriangle(renderer, 400, 300, 100, *m, *mp);

    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_S] && height < 598)
    {
        *m += 0.02;
    }

    if (state[SDL_SCANCODE_W] && height > 0)
    {
        *m -= 0.02;
    }

    if (state[SDL_SCANCODE_A])
    {
        *mp += 0.02;
    }

    if (state[SDL_SCANCODE_D])
    {
        *mp -= 0.02;
    }
    

    SDL_RenderPresent(renderer);
    SDL_Delay(5);
}


int main(int argc, char *argv[])
{
    SDL_Window *window;
    SDL_Renderer *renderer;
    bool doneDrawing = false;
    float vertical_trans = 0.5f;
    float horizontal_trans = 1.0f;
    int height = 0;    

    window = SDL_CreateWindow("Drawing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    renderer = SDL_CreateRenderer(window, -1, 0);

    while (!doneDrawing)
    {
        doneDrawing = processEvents();
        draw(renderer, &vertical_trans, &horizontal_trans);
        printf("\n#######Press ESCAPE to quit\n");
    }
    
    
    return 0;
}
