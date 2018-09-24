/*
SPTool by Maxwell Sherman (Qwertie64982)
Last modified 2018-09-24 5PM PDT
*/

#include <3ds.h>
#include <stdio.h>

enum {red, green, blue, yellow, turquoise, magenta, white, black};

void fillScreen(u8* fb, int color);

int main(int argc, char **argv)
{
    gfxInitDefault();
    
    PrintConsole topScreen, bottomScreen;
    //consoleInit(GFX_TOP, &topScreen);
    consoleInit(GFX_BOTTOM, &bottomScreen);
    
    consoleSelect(&bottomScreen);
    
    // row, col starting at 1
    printf("\x1b[10;14HColor: ");
    
    printf("\x1b[10;21H\x1b[31mRed");
    
    //consoleSelect(&topScreen);
    //
    // Move cursor to 1,1
    // printf("\x1b[1;1H");
    // printf("\x1b[41m                                                  \n");
    
    printf("\x1b[30;11HPress Start to exit.");
    
    gfxSetDoubleBuffering(GFX_TOP, false);
    u8* fb = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);
    
    fillScreen(fb, red);
    
    // Main loop
    while (aptMainLoop())
    {
        hidScanInput();
        
        u32 kDown = hidKeysDown();
        
        if (kDown & KEY_START) {
            break;
        }
        
        gfxFlushBuffers();
        gfxSwapBuffers();
        
        gspWaitForVBlank();
    }
    
    gfxExit();
    return 0;
}

void fillScreen(u8* fb, int color) {
    int redValue, greenValue, blueValue;
    switch(color) {
        case red :
            redValue = 255;
            greenValue = blueValue = 0;
            break;
        case green :
            redValue = blueValue = 0;
            greenValue = 255;
            break;
        case blue :
            redValue = greenValue = 0;
            blueValue = 255;
            break;
        case yellow :
            redValue = greenValue = 255;
            blueValue = 0;
            break;
        case turquoise :
            redValue = 0;
            greenValue = blueValue = 255;
            break;
        case magenta :
            redValue = blueValue = 255;
            greenValue = 0;
            break;
        case white :
            redValue = greenValue = blueValue = 255;
            break;
        case black :
            redValue = greenValue = blueValue = 0;
            break;
        default :
            redValue = greenValue = blueValue = 0;
            break;
    }
    
    u32 x, y, pos;
    for (x = 0; x < 400; x++) {
        for (y = 0; y < 720; y += 3) {
            pos = x * 720 + y;
            fb[pos] = blueValue; // blue
            fb[pos + 1] = greenValue; // green
            fb[pos + 2] = redValue; // red
        }
    }
}
