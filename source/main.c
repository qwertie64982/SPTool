/*
SPTool by Maxwell Sherman (Qwertie64982)
Last modified 2018-09-26 9PM PDT
*/

#include <3ds.h>
#include <stdio.h>

enum {red, green, blue, yellow, cyan, magenta, white, black};

void fillScreen(u8* fb, int color);
void setColorText(int color);

int main(int argc, char **argv)
{
    gfxInitDefault();
    
    PrintConsole topScreen, bottomScreen;
    //consoleInit(GFX_TOP, &topScreen);
    consoleInit(GFX_BOTTOM, &bottomScreen);
    
    consoleSelect(&bottomScreen);
    
    // row, col starting at 1
    printf("\x1b[8;13HInstructions:");
    printf("\x1b[10;13HColor (L/R): ");
    printf("\x1b[12;13HFlash screen (A)");
    
    printf("\x1b[28;12H\x1b[33mEpilepsy warning!!");
    printf("\x1b[29;11H\x1b[37mPress Start to exit.");
    printf("\x1b[30;4H\x1b[36mby Maxwell Sherman (Qwertie64982)");
    
    gfxSetDoubleBuffering(GFX_TOP, false);
    u8* fb = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);
    
    int currentColor = red;
    int newColor = red;
    fillScreen(fb, currentColor); // initial screen is red
    setColorText(currentColor);
    
    u32 keysPressed;
    u32 keysReleased;
    u32 keysHeldDown;
    
    // Main loop
    while (aptMainLoop())
    {
        // Scan input
        hidScanInput();
        
        // Store button states in u32s
        keysPressed = hidKeysDown();
        keysReleased = hidKeysUp();
        keysHeldDown = hidKeysHeld();
        
        // If Start pressed, exit the UI loop
        if (keysPressed & KEY_START) {
            break;
        }
        
        // If D-Pad right, increment currentColor
        if (keysPressed & KEY_DRIGHT) {
            newColor++;
        }
        
        // If D-Pad left, decrement currentColor
        if (keysPressed & KEY_DLEFT) {
            newColor--;
        }
        
        // Validate and set new color
        if (newColor != currentColor && !(keysHeldDown & KEY_A)) { // Only set newColor if it's different
            if (newColor > black) {
                newColor = red;
            } else if (newColor < red) {
                newColor = black;
            }
            currentColor = newColor;
            fillScreen(fb, currentColor);
            setColorText(currentColor);
        }
        
        // If A, flash the screen
        if (keysHeldDown & KEY_A) {
            currentColor++;
            if (currentColor > black) {
                currentColor = red;
            }
            fillScreen(fb, currentColor);
        }
        /*
        if (keysReleased & KEY_A) {
            newColor = currentColor;
            fillScreen(fb, currentColor);
        }
        */
        
        gfxFlushBuffers();
        gfxSwapBuffers();
        
        gspWaitForVBlank();
    }
    
    gfxExit();
    return 0;
}

void fillScreen(u8* fb, int color) { // TODO: There are artifacts - is this a framebuffer issue?
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
        case cyan :
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

void setColorText(int color) {
    printf("\x1b[10;26H\x1b[40m"); // Move cursor to proper location and set BG to black
    switch(color) {
        case red :
            printf("\x1b[31mRed    ");
            break;
        case green :
            printf("\x1b[32mGreen  ");
            break;
        case blue :
            printf("\x1b[34mBlue   ");
            break;
        case yellow :
            printf("\x1b[33mYellow ");
            break;
        case cyan :
            printf("\x1b[36mCyan   ");
            break;
        case magenta :
            printf("\x1b[35mMagenta");
            break;
        case white :
            printf("\x1b[37mWhite  ");
            break;
        case black :
            printf("\x1b[30;47mBlack\x1b[40m  "); // black text on white BG
            break;
        default :
            printf("\x1b[30;47mBlack\x1b[40m  ");
            break;
    }
    printf("\x1b[37m\x1b[46m"); // Reset text FG/BG color to white/black respectively
}
