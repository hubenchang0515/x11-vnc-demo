#ifndef KEY_H
#define KEY_H

#include <xcb/xcb.h>
#include <xcb/xcb_keysyms.h>
#include <xcb/xtest.h>

#define VNC_BUTTON_MASK_LEFT        rfbButton1Mask
#define VNC_BUTTON_MASK_MIDDLE      rfbButton2Mask
#define VNC_BUTTON_MASK_RIGHT       rfbButton3Mask
#define VNC_BUTTON_MASK_UP          rfbWheelUpMask
#define VNC_BUTTON_MASK_DOWN        rfbWheelDownMask

#define X11_BUTTON_LEFT     XCB_BUTTON_INDEX_1
#define X11_BUTTON_MIDDLE   XCB_BUTTON_INDEX_2
#define X11_BUTTON_RIGHT    XCB_BUTTON_INDEX_3
#define X11_BUTTON_UP       XCB_BUTTON_INDEX_4
#define X11_BUTTON_DOWN     XCB_BUTTON_INDEX_5

// 发送按键
void send_keycode(xcb_connection_t *conn, xcb_keycode_t keycode, int press);

// 发送按键
void send_keysym(xcb_connection_t *conn, xcb_keysym_t keysym, int press);

// 发送鼠标按钮
void send_button(xcb_connection_t *conn, xcb_button_t button, int press);

// 发送鼠标移动
void send_motion(xcb_connection_t *conn, int16_t x, int16_t y);

#endif // KEY_H