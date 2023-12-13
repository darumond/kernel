#include "keyboard.h"

const uint32_t UNKNOWN = 0xFFFFFFFF;
const uint32_t SCRLCK = 0xFFFFFFFF - 18;
const uint32_t HOME = 0xFFFFFFFF - 19;
const uint32_t PGUP = 0xFFFFFFFF - 24;
const uint32_t PGDOWN = 0xFFFFFFFF - 25;
const uint32_t END = 0xFFFFFFFF - 26;

const uint32_t keys[128] = {
    UNKNOWN, KEY_ESC, '1', '2', '3', '4', '5', '6', '7', '8',
    '9', '0', '-', '=', '\b', '\t', 'q', 'w', 'e', 'r',
    't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', KEY_CTRL,
    'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',
    '\'', '`', KEY_LSHIFT, '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',',
    '.', '/', KEY_RSHIFT, '*', KEY_ALT, ' ', KEY_MAJLOCK, KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_f9, KEY_F10,
    KEY_MAJLOCK, SCRLCK, HOME, KEY_UP, PGUP, '-', KEY_LEFT, UNKNOWN, KEY_RIGHT,
    '+', END, KEY_DOWN, PGDOWN, KEY_INSER, KEY_SUPPR, UNKNOWN, UNKNOWN, UNKNOWN, KEY_F11, KEY_F12, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN,
    UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN,
    UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN,
    UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN, UNKNOWN};


void initKeyboard()
{
    irq_install_handler(1, &keyboardHandler);
}
int getkey(void)
{
    int lastKeyPressed = inb(0x60) & 0x7F;

    return lastKeyPressed;
}
void keyboardHandler()
{
    int key = getkey();
    char press = inb(0x60) & 0x80;

    if (press == 0)
    {
        return;
    }
    printf("%c", keys[key]);
}