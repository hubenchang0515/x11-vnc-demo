#include <xcb/xcb.h>
#include <rfb/rfb.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "window.h"
#include "input.h"

xcb_connection_t* conn;

static void keyCallback(rfbBool down, rfbKeySym keySym, rfbClientPtr client)
{
    (void)(client);
    send_keysym(conn, keySym, (int)down);
}

static void mouseCallback(int buttonMask, int x, int y, rfbClientPtr client)
{
    (void)(client);

    send_button(conn, X11_BUTTON_LEFT, !!(buttonMask & VNC_BUTTON_MASK_LEFT));
    send_button(conn, X11_BUTTON_MIDDLE, !!(buttonMask & VNC_BUTTON_MASK_MIDDLE));
    send_button(conn, X11_BUTTON_RIGHT, !!(buttonMask & VNC_BUTTON_MASK_RIGHT));
    send_button(conn, X11_BUTTON_UP, !!(buttonMask & VNC_BUTTON_MASK_UP));
    send_button(conn, X11_BUTTON_DOWN, !!(buttonMask & VNC_BUTTON_MASK_DOWN));

    send_motion(conn, (int16_t)x, (int16_t)y);
}

int main(int argc, char* argv[])
{
    // 建立连接
    conn = xcb_connect(NULL, NULL);
    assert(conn != NULL);

    const xcb_setup_t* setup = xcb_get_setup(conn);
    assert(setup != NULL);

    // 获取 screen
    xcb_screen_iterator_t iter = xcb_setup_roots_iterator(setup);
    xcb_screen_t* screen = iter.data;
    assert(screen != NULL);

    // 获取 root 窗口
    xcb_window_t root = screen->root;

    // 获取窗口的大小并给图像分配内存
    int16_t width;
    int16_t height;
    get_window_size(conn, root, &width, &height);
    char* frameBuffer = (char*)malloc(3UL * width * height);
    assert(frameBuffer);

    rfbScreenInfoPtr rfbScreen = rfbGetScreen(&argc, argv, (int)width, (int)height, 8, 3, 3);
    assert(rfbScreen != NULL);

    rfbScreen->desktopName = "LibVNCServer X11 Example";
    rfbScreen->frameBuffer = frameBuffer;
    rfbScreen->alwaysShared = TRUE;
    rfbScreen->kbdAddEvent = keyCallback;
    rfbScreen->ptrAddEvent = mouseCallback;
    rfbInitServer(rfbScreen);
    
    while (TRUE)
    {
        // 没有客户端连接，不进行处理仅空转
        while (rfbScreen->clientHead == NULL)
			rfbProcessEvents(rfbScreen, 1000000 / 144);

        rfbProcessEvents(rfbScreen, 1000000 / 144);
        get_window_image(conn, root, frameBuffer);
        rfbMarkRectAsModified(rfbScreen, 0, 0, (int)width, (int)height);
    }

    xcb_disconnect(conn);
    return EXIT_SUCCESS;
}