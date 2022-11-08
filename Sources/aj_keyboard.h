#ifndef AJ_KEYBOARD_H
#define AJ_KEYBOARD_H

#include <stdio.h>
#include <Windows.h>
#include <QVector>

#define KEY_1         '1'
#define KEY_2         '2'
#define KEY_3         '3'
#define KEY_4         '4'
#define KEY_5         '5'
#define KEY_6         '6'
#define KEY_7         '7'
#define KEY_8         '8'
#define KEY_9         '9'
#define KEY_A         'A'
#define KEY_B         'B'
#define KEY_C         'C'
#define KEY_D         'D'
#define KEY_E         'E'
#define KEY_F         'F'
#define KEY_M         'M'
#define KEY_N         'N'
#define KEY_P         'P'
#define KEY_R         'R'
#define KEY_T         'T'
#define KEY_V         'V'
#define KEY_W         'W'
#define KEY_ESC       VK_ESCAPE
#define KEY_UP        VK_UP
#define KEY_ENTER     VK_RETURN
#define KEY_LEFT      VK_LEFT
#define KEY_DOWN      VK_DOWN
#define KEY_RIGHT     VK_RIGHT
#define KEY_BACKSPACE VK_BACK
#define KEY_LEFTALT   VK_MENU
#define KEY_LEFTCTRL  VK_CONTROL
#define KEY_LEFTSHIFT VK_SHIFT
#define KEY_TAB       VK_TAB
#define KEY_META      VK_LWIN
#define KEY_PAGEUP    VK_PRIOR //Page Up
#define KEY_NEXT      VK_NEXT  //Page Down

#define KEY_F1        VK_F1
#define KEY_F2        VK_F2
#define KEY_F3        VK_F3
#define KEY_F4        VK_F4
#define KEY_F5        VK_F5
#define KEY_F6        VK_F6
#define KEY_F7        VK_F7
#define KEY_F8        VK_F8
#define KEY_F9        VK_F9

#define AJ_KEY_FMIN    VK_F1    //0x6f
#define AJ_KEY_FMAX    VK_F12+1 //0x7C

typedef struct AjKey
{
    int key;
    int alt_key;
    int ctrl_key;
    int shift_key;
    int meta_key;
}AjKey;

class AjKeyboard
{
public:
    AjKeyboard();
    ~AjKeyboard();

    void sendKey(int key_val);
    void pressKey(int key_val);
    void releaseKey(int key_val);
    void execKey(AjKey *key);

private:
    bool isExtended(int key_val);

    QVector<int> extended_keys;
    int uinput_f;
};

AjKey aj_getKey(QString key);
int aj_keyCode(QString key);

#endif // AJ_KEYBOARD_H
