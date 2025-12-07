#include "console.h"
#include <stdarg.h>

static int cursor_x = 0;
static int cursor_y = 0;
static uint16_t *video_memory = (uint16_t *) 0xB8000;

void console_putc(char c) {
    if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
        return;
    }

    video_memory[cursor_y * 80 + cursor_x] = (0x0F << 8) | c;
    cursor_x++;

    if (cursor_x >= 80) {
        cursor_x = 0;
        cursor_y++;
    }
}

void kprintf(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    while (*fmt) {
        if (*fmt == '%') {
            fmt++;
            if (*fmt == 'd') {
                int val = va_arg(args, int);
                char buffer[32];
                int i = 0;
                if (val == 0) buffer[i++] = '0';
                while (val > 0) {
                    buffer[i++] = '0' + (val % 10);
                    val /= 10;
                }
                while (i--) console_putc(buffer[i]);
            }
            else if (*fmt == 's') {
                char *str = va_arg(args, char*);
                while (*str) console_putc(*str++);
            }
        } else {
            console_putc(*fmt);
        }
        fmt++;
    }

    va_end(args);
}
