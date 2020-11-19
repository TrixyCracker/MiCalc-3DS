#include <3ds.h>
#include <citro3d.h>
#include <citro2d.h>

#include <stdbool.h>

#include "cstring.h"
#include "tag_utils.h"

struct Button {
    int px;
    int py;
    int width;
    int height;
};

typedef struct Button Button;

C3D_RenderTarget * top_screen;
C3D_RenderTarget * bot_screen;

void draw_background(void);

void draw_button(const Button button, const u32 button_color, const C2D_Text * text, const u32 text_color);
void new_button(Button * button, const int px, const int py, const int width, const int height);
bool button_onclick(const Button button);

int main() 
{
    char buffer[1024];
    C2D_TextBuf g_staticBuf = C2D_TextBufNew(4096);
    C2D_Text txt;

    u32 x, y;

    gfxInitDefault();
    C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
    C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
    C2D_Prepare();

    top_screen = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
    bot_screen = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);

    draw_background();
    
    Button keyboard_button[16];
    Button calculate_button;
    Button delete_button;

    //DRAW KEYBOARD
    C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
        C2D_SceneBegin(bot_screen);
        for (int c = 0; c < 4; ++c)
        {

            for (int r = 0; r < 5; ++r)
            {

                if (r == 4) {
                    C2D_TextBufClear(g_staticBuf);
                    C2D_TextParse(&txt, g_staticBuf, "CALCULATE");

                    x = 12;
                    y = 10 + r * (40 + 4);

                    new_button(&calculate_button, x, y, 200, 40);
                    draw_button(calculate_button, C2D_Color32(0xFE, 0xCE, 0xA8, 0xFF), &txt, 0x000000FF);

                    C2D_TextBufClear(g_staticBuf);
                    C2D_TextParse(&txt, g_staticBuf, "<--");
                    new_button(&delete_button, x + 206, y, 90, 40);
                    draw_button(delete_button, C2D_Color32(0xFE, 0xCE, 0xA8, 0xFF), &txt, 0x000000FF);
                }
                else
                {
                    sprintf(buffer, "%1X", r*4 + c);
                    C2D_TextBufClear(g_staticBuf);
                    C2D_TextParse(&txt, g_staticBuf, buffer);

                    x = 11 + c * (70 + 6);
                    y = 10 + r * (40 + 4);

                    new_button(&keyboard_button[r * 4 + c], x, y, 70, 40);
                    draw_button(keyboard_button[r * 4 + c], C2D_Color32(0xFE, 0xCE, 0xA8, 0xFF), &txt, 0x000000FF);
                }


            }

        }
    C3D_FrameEnd(0);
    //END

    buffer[0] = '\0';
    u8 flag;
    u32 kDown;
    while(aptMainLoop())
    {

        gspWaitForVBlank();

        // Scan all HID (Human Inteface Device)
        hidScanInput();

        // Check key pressed
        kDown = hidKeysDown();
        if (kDown & KEY_START) break;
        
        C2D_TextBufClear(g_staticBuf);

        flag = 0;
        for (u8 i = 0; i < 16; ++i)
        {

            if (button_onclick(keyboard_button[i]))
            {
                string_addchar(buffer, uint8_to_char(i));

                flag = 1;
            }

        }

        if (button_onclick(calculate_button))
        {
            if (string_lenght(buffer) != 8) continue;

            char buffer2[1024];
            
            u8 uid[4];
            string_to_uint8_array(uid, buffer, 4);

            u8 mizip_keys[10][6];
            mizip_calculate_allkeys(mizip_keys, uid);

            for (int i = 0; i < 10; ++i)
            {
                uint8_array_to_string(buffer, mizip_keys[i], 6);
                string_addstring(buffer2, buffer);
                string_addstring(buffer2, "  ");
                if (i % 2) string_addchar(buffer2, '\n');
            }

            C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
            C2D_SceneBegin(top_screen);
            C2D_TextParse(&txt, g_staticBuf, buffer2);
            C2D_TextOptimize(&txt);
            C2D_DrawText(&txt, C2D_WithColor, 5, 30, 0, 0.9, 1, C2D_Color32(0xFE, 0xCE, 0xA8, 0xFF));
            C3D_FrameEnd(0);

        }
        else if (button_onclick(delete_button))
        {
            string_removelastchar(buffer);

            flag = 1;
        }

        if (flag)
        {
            C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
                C2D_SceneBegin(top_screen);
                C2D_TargetClear(top_screen, C2D_Color32(0x2A, 0x36, 0x3B, 0xFF));
                C2D_TextParse(&txt, g_staticBuf, buffer);
                C2D_TextOptimize(&txt);
                C2D_DrawText(&txt, C2D_WithColor, 5, 5, 0, 1, 1, C2D_Color32(0xFE, 0xCE, 0xA8, 0xFF));
            C3D_FrameEnd(0);
        }

    }

    // Flush
    gfxFlushBuffers();
    gfxSwapBuffers();

    C2D_Fini();
    C3D_Fini();
    gfxExit();

    return 0;
}

void draw_background(void)
{

    C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
        C2D_SceneBegin(top_screen);
        C2D_TargetClear(top_screen, C2D_Color32(0x2A, 0x36, 0x3B, 0xFF));
        C2D_SceneBegin(bot_screen);
        C2D_TargetClear(bot_screen, C2D_Color32(0x2A, 0x36, 0x3B, 0xFF));
    C3D_FrameEnd(0);

} 

void new_button(Button * button, const int px, const int py, const int width, const int height)
{
    button->px = px;
    button->py = py;
    button->width = width;
    button->height = height;
}

void draw_button(const Button button, const u32 button_color, const C2D_Text * text, const u32 text_color) 
{
    float out_width;
    float out_height;

    C2D_SceneBegin(bot_screen);
    C2D_DrawRectangle(button.px, button.py, 0, button.width, button.height, button_color, button_color, button_color, button_color);
    C2D_TextOptimize(text);
    C2D_TextGetDimensions(text, 1, 1, &out_width, &out_height);
    C2D_DrawText(text, 0, button.px + button.width / 2 - out_width / 2, button.py + button.height / 2 - out_height / 2, 0, 1, 1, text_color);
}

bool button_onclick(const Button button) 
{
    touchPosition touch;

    hidScanInput();
    hidTouchRead(&touch);

    if (button.px <= touch.px && touch.px <= button.px + button.width && button.py <= touch.py && touch.py <= button.py + button.height)
    {
        //Wait release
        while(button.px <= touch.px && touch.px <= button.px + button.width && button.py <= touch.py && touch.py <= button.py + button.height) 
        {
            hidScanInput();
            hidTouchRead(&touch);
            svcSleepThread(10e5);
        }

        return true;
    }

    return false;
}
