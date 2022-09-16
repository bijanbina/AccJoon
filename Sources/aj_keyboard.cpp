#include "aj_keyboard.h"
#include <QDebug>

AjKeyboard::AjKeyboard()
{
    extended_keys << VK_INSERT;
    extended_keys << VK_DELETE;
    extended_keys << VK_HOME;
    extended_keys << VK_END;
    extended_keys << VK_PRIOR;
    extended_keys << VK_NEXT;
    extended_keys << VK_LEFT;
    extended_keys << VK_UP;
    extended_keys << VK_DOWN;
    extended_keys << VK_RIGHT;
}

AjKeyboard::~AjKeyboard()
{

}

void AjKeyboard::sendKey(int key_val)
{
    pressKey(key_val);
    releaseKey(key_val);
}

void AjKeyboard::pressKey(int key_val)
{
    INPUT input;
    ZeroMemory(&input, sizeof(input));

    input.type = INPUT_KEYBOARD;
    input.ki.wVk = key_val;
    if( isExtended(key_val) )
    {
        input.ki.dwFlags = KEYEVENTF_EXTENDEDKEY;
    }

    UINT ret = SendInput(1, &input, sizeof(INPUT));
    qDebug() << "SendInput" << ret;
}

void AjKeyboard::releaseKey(int key_val)
{
    INPUT input;
    ZeroMemory(&input, sizeof(input));

    input.type = INPUT_KEYBOARD;
    input.ki.wVk = key_val;
    input.ki.dwFlags = KEYEVENTF_KEYUP;
    if( isExtended(key_val) )
    {
        input.ki.dwFlags |= KEYEVENTF_EXTENDEDKEY;
    }

    SendInput(1, &input, sizeof(INPUT));
}

bool AjKeyboard::isExtended(int key_val)
{
    if( extended_keys.contains(key_val) )
    {
        return true;
    }
    return false;
}
