#ifndef WINDOW_H
#define WINDOW_H

#include <xcb/xcb.h>

// 获取窗口尺寸
void get_window_size(xcb_connection_t* conn, xcb_window_t window, int16_t* width, int16_t* height);

// 获取窗口图像(RGB)
void get_window_image(xcb_connection_t* conn, xcb_window_t window, uint8_t* buff);

#endif // WINDOW_H