/*
SPTool by Maxwell Sherman (Qwertie64982)
Last modified 2018-09-24 3PM PDT
*/

#include <3ds.h>
#include <stdio.h>

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
    
    u32 x, y, pos;
    for (x = 0; x < 400; x++) {
        for (y = 0; y < 720; y += 3) {
            pos = x * 720 + y;
            fb[pos] = 0; // blue
            fb[pos + 1] = 0; // green
            fb[pos + 2] = 255; // red
        }
    }
    
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
