#include "aj_keyboard.h"
#include <QDebug>
#include <QThread>

QVector<int> AjKeyboard::extended_keys;

AjKeyboard::AjKeyboard()
{
    ;
}

void AjKeyboard::init()
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

int aj_keyCode(QString key)
{
    if( key.size()<2 )
    {
        return -1;
    }
    key = key.toLower();
    if( key[0]=='f' )
    {
        key.remove(0,1);
        int key_int = key.toInt();
        if( key_int>0 && key_int<13 )
        {
            return VK_F1 + key_int - 1;
        }
        else
        {
            qDebug() << "Error: Wrong function key number"
                     << key_int;
            return -1;
        }
    }
    else if( key=="up" )
    {
        return KEY_UP;
    }
    else if( key=="down" )
    {
        return KEY_DOWN;
    }
    else if( key=="left" )
    {
        return KEY_LEFT;
    }
    else if( key=="right" )
    {
        return KEY_RIGHT;
    }
    qDebug() << "Error: Wrong key code entered";
    return -1;
}

AjKey aj_getKey(QString key)
{
    int key_int = -1, alt_key=0, ctrl_key=0, shift_key=0, meta_key=0;
    key = key.toLower();
    QStringList key_list = key.split('+');
    for( int i=0; i<key_list.size(); i++ )
    {
        if( i==key_list.size()-1 )
        {
            key = key_list[i];
            if( key.size()>1 )
            {
                key_int = aj_keyCode(key);
            }
            else
            {
                key_int = key.toUpper().toStdString()[0];
            }
        }
        else if( key_list[i].contains("alt") )
        {
            alt_key = 1;
        }
        else if( key_list[i].contains("ctrl") )
        {
            ctrl_key = 1;
        }
        else if( key_list[i].contains("shift") )
        {
            shift_key = 1;
        }
        else if( key_list[i].contains("super") )
        {
            meta_key = 1;
        }
        else
        {
            qDebug() << "Error: Unrecognised key";
            exit(0);
        }
    }
    AjKey ret;
    ret.key = key_int;
    ret.alt_key = alt_key;
    ret.ctrl_key = ctrl_key;
    ret.meta_key = meta_key;
    ret.shift_key = shift_key;
    return ret;
}

void AjKeyboard::execKey(AjKey *key)
{
    if( key->alt_key )
    {
        pressKey(KEY_LEFTALT);
    }
    if( key->ctrl_key )
    {
        QThread::msleep(20);
        pressKey(KEY_LEFTCTRL);
    }
    if( key->shift_key )
    {
        QThread::msleep(20);
        pressKey(KEY_LEFTSHIFT);
    }
    if( key->meta_key )
    {
        QThread::msleep(20);
        pressKey(KEY_META);
    }
    QThread::msleep(1000);
    sendKey(key->key);
    if( key->alt_key )
    {
        QThread::msleep(20);
        releaseKey(KEY_LEFTALT);
    }
    if( key->ctrl_key )
    {
        QThread::msleep(20);
        releaseKey(KEY_LEFTCTRL);
    }
    if( key->shift_key )
    {
        QThread::msleep(20);
        releaseKey(KEY_LEFTSHIFT);
    }
    if( key->meta_key )
    {
        QThread::msleep(20);
        releaseKey(KEY_META);
    }

}
