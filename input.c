#include "input.h"
#include <stdio.h>

/************************************************************************
 * @brief 发送按键
 * @param[in] conn xcb连接
 * @param[in] keycode 键码
 * @param[in] press 是否按下
 * *********************************************************************/
void send_keycode(xcb_connection_t *conn, xcb_keycode_t keycode, int press) 
{
    xcb_test_fake_input(conn, press ? XCB_KEY_PRESS : XCB_KEY_RELEASE, keycode, XCB_CURRENT_TIME, XCB_NONE, 0, 0, 0);
    xcb_flush(conn);
}


/************************************************************************
 * @brief 发送按键
 * @param[in] conn xcb连接
 * @param[in] keysym 键码
 * @param[in] press 是否按下
 * *********************************************************************/
void send_keysym(xcb_connection_t *conn, xcb_keysym_t keysym, int press) 
{
    xcb_key_symbols_t* symbols = xcb_key_symbols_alloc(conn);
    xcb_keycode_t* code = xcb_key_symbols_get_keycode(symbols, keysym);
    for (; code != NULL && *code != XCB_NO_SYMBOL; code++)
    {
        send_keycode(conn, *code, press);
    }
    xcb_key_symbols_free(symbols);
}

/************************************************************************
 * @brief 发送鼠标按钮
 * @param[in] conn xcb连接
 * @param[in] button 按钮
 * @param[in] press 是否按下
 * *********************************************************************/
void send_button(xcb_connection_t *conn, xcb_button_t button, int press)
{
    xcb_test_fake_input(conn, press ? XCB_BUTTON_PRESS : XCB_BUTTON_RELEASE, button, XCB_CURRENT_TIME, XCB_NONE, 0, 0, 0);
    xcb_flush(conn);
}

/************************************************************************
 * @brief 发送鼠标移动
 * @param[in] conn xcb连接
 * @param[in] button 按钮
 * @param[in] press 是否按下
 * *********************************************************************/
void send_motion(xcb_connection_t *conn, int16_t x, int16_t y)
{
    xcb_test_fake_input(conn, XCB_MOTION_NOTIFY, 0, XCB_CURRENT_TIME, XCB_NONE, x, y, 0);
    xcb_flush(conn);
}