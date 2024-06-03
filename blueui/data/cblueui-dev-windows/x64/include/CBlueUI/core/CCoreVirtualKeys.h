#ifndef CBLUEUI_VIRTUALKEYS_DEFS_BLXDY_INC_H_
#define CBLUEUI_VIRTUALKEYS_DEFS_BLXDY_INC_H_

#pragma once

/*
 * Virtual Keys, Standard Set
 */
#define VKEY_LBUTTON 0x01
#define VKEY_RBUTTON 0x02
#define VKEY_CANCEL  0x03
#define VKEY_MBUTTON 0x04 /* NOT contiguous with L & RBUTTON */


#define VKEY_XBUTTON1 0x05 /* NOT contiguous with L & RBUTTON */
#define VKEY_XBUTTON2 0x06 /* NOT contiguous with L & RBUTTON */

/*
 * 0x07 : reserved
 */

#define VKEY_BACK 0x08
#define VKEY_TAB  0x09

/*
 * 0x0A - 0x0B : reserved
 */

#define VKEY_CLEAR  0x0C
#define VKEY_RETURN 0x0D

/*
 * 0x0E - 0x0F : unassigned
 */

#define VKEY_SHIFT   0x10
#define VKEY_CONTROL 0x11
#define VKEY_MENU    0x12
#define VKEY_PAUSE   0x13
#define VKEY_CAPITAL 0x14

#define VKEY_KANA    0x15
#define VKEY_HANGEUL 0x15 /* old name - should be here for compatibility */
#define VKEY_HANGUL  0x15
#define VKEY_IME_ON  0x16
#define VKEY_JUNJA   0x17
#define VKEY_FINAL   0x18
#define VKEY_HANJA   0x19
#define VKEY_KANJI   0x19
#define VKEY_IME_OFF 0x1A

#define VKEY_ESCAPE 0x1B

#define VKEY_CONVERT    0x1C
#define VKEY_NONCONVERT 0x1D
#define VKEY_ACCEPT     0x1E
#define VKEY_MODECHANGE 0x1F

#define VKEY_SPACE    0x20
#define VKEY_PRIOR    0x21
#define VKEY_NEXT     0x22
#define VKEY_END      0x23
#define VKEY_HOME     0x24
#define VKEY_LEFT     0x25
#define VKEY_UP       0x26
#define VKEY_RIGHT    0x27
#define VKEY_DOWN     0x28
#define VKEY_SELECT   0x29
#define VKEY_PRINT    0x2A
#define VKEY_EXECUTE  0x2B
#define VKEY_SNAPSHOT 0x2C
#define VKEY_INSERT   0x2D
#define VKEY_DELETE   0x2E
#define VKEY_HELP     0x2F

/* VKEY_0 - VKEY_9 are the same as ASCII '0' - '9' (0x30 - 0x39)*/
#define VKEY_0 0x30
#define VKEY_1 0x31
#define VKEY_2 0x32
#define VKEY_3 0x33
#define VKEY_4 0x34
#define VKEY_5 0x35
#define VKEY_6 0x36
#define VKEY_7 0x37
#define VKEY_8 0x38
#define VKEY_9 0x39



/*
 * 0x3A - 0x40 : unassigned
 * VKEY_A - VKEY_Z are the same as ASCII 'A' - 'Z' (0x41 - 0x5A)
 */
#define VKEY_Colon     0x3a
#define VKEY_Semicolon 0x3b
#define VKEY_Less      0x3c
#define VKEY_Equal     0x3d
#define VKEY_Greater   0x3e
#define VKEY_Question  0x3f
#define VKEY_At        0x40
#define VKEY_A         0x41
#define VKEY_B         0x42
#define VKEY_C         0x43
#define VKEY_D         0x44
#define VKEY_E         0x45
#define VKEY_F         0x46
#define VKEY_G         0x47
#define VKEY_H         0x48
#define VKEY_I         0x49
#define VKEY_J         0x4a
#define VKEY_K         0x4b
#define VKEY_L         0x4c
#define VKEY_M         0x4d
#define VKEY_N         0x4e
#define VKEY_O         0x4f
#define VKEY_P         0x50
#define VKEY_Q         0x51
#define VKEY_R         0x52
#define VKEY_S         0x53
#define VKEY_T         0x54
#define VKEY_U         0x55
#define VKEY_V         0x56
#define VKEY_W         0x57
#define VKEY_X         0x58
#define VKEY_Y         0x59
#define VKEY_Z         0x5a


#define VKEY_LWIN 0x5B
#define VKEY_RWIN 0x5C
#define VKEY_APPS 0x5D

/*
 * 0x5E : reserved
 */

#define VKEY_SLEEP     0x5F
#define VKEY_NUMPAD0   0x60
#define VKEY_NUMPAD1   0x61
#define VKEY_NUMPAD2   0x62
#define VKEY_NUMPAD3   0x63
#define VKEY_NUMPAD4   0x64
#define VKEY_NUMPAD5   0x65
#define VKEY_NUMPAD6   0x66
#define VKEY_NUMPAD7   0x67
#define VKEY_NUMPAD8   0x68
#define VKEY_NUMPAD9   0x69
#define VKEY_MULTIPLY  0x6A
#define VKEY_ADD       0x6B
#define VKEY_SEPARATOR 0x6C
#define VKEY_SUBTRACT  0x6D
#define VKEY_DECIMAL   0x6E
#define VKEY_DIVIDE    0x6F
#define VKEY_F1        0x70
#define VKEY_F2        0x71
#define VKEY_F3        0x72
#define VKEY_F4        0x73
#define VKEY_F5        0x74
#define VKEY_F6        0x75
#define VKEY_F7        0x76
#define VKEY_F8        0x77
#define VKEY_F9        0x78
#define VKEY_F10       0x79
#define VKEY_F11       0x7A
#define VKEY_F12       0x7B
#define VKEY_F13       0x7C
#define VKEY_F14       0x7D
#define VKEY_F15       0x7E
#define VKEY_F16       0x7F
#define VKEY_F17       0x80
#define VKEY_F18       0x81
#define VKEY_F19       0x82
#define VKEY_F20       0x83
#define VKEY_F21       0x84
#define VKEY_F22       0x85
#define VKEY_F23       0x86
#define VKEY_F24       0x87



/*
 * 0x88 - 0x8F : UI navigation
 */

#define VKEY_NAVIGATION_VIEW   0x88 // reserved
#define VKEY_NAVIGATION_MENU   0x89 // reserved
#define VKEY_NAVIGATION_UP     0x8A // reserved
#define VKEY_NAVIGATION_DOWN   0x8B // reserved
#define VKEY_NAVIGATION_LEFT   0x8C // reserved
#define VKEY_NAVIGATION_RIGHT  0x8D // reserved
#define VKEY_NAVIGATION_ACCEPT 0x8E // reserved
#define VKEY_NAVIGATION_CANCEL 0x8F // reserved


#define VKEY_NUMLOCK 0x90
#define VKEY_SCROLL  0x91

/*
 * NEC PC-9800 kbd definitions
 */
#define VKEY_OEM_NEC_EQUAL 0x92 // '=' key on numpad

/*
 * Fujitsu/OASYS kbd definitions
 */
#define VKEY_OEM_FJ_JISHO   0x92 // 'Dictionary' key
#define VKEY_OEM_FJ_MASSHOU 0x93 // 'Unregister word' key
#define VKEY_OEM_FJ_TOUROKU 0x94 // 'Register word' key
#define VKEY_OEM_FJ_LOYA    0x95 // 'Left OYAYUBI' key
#define VKEY_OEM_FJ_ROYA    0x96 // 'Right OYAYUBI' key

/*
 * 0x97 - 0x9F : unassigned
 */

/*
 * VKEY_L* & VKEY_R* - left and right Alt, Ctrl and Shift virtual keys.
 * Used only as parameters to GetAsyncKeyState() and GetKeyState().
 * No other API or message will distinguish left and right keys in this way.
 */
#define VKEY_LSHIFT   0xA0
#define VKEY_RSHIFT   0xA1
#define VKEY_LCONTROL 0xA2
#define VKEY_RCONTROL 0xA3
#define VKEY_LMENU    0xA4
#define VKEY_RMENU    0xA5

#define VKEY_BROWSER_BACK      0xA6
#define VKEY_BROWSER_FORWARD   0xA7
#define VKEY_BROWSER_REFRESH   0xA8
#define VKEY_BROWSER_STOP      0xA9
#define VKEY_BROWSER_SEARCH    0xAA
#define VKEY_BROWSER_FAVORITES 0xAB
#define VKEY_BROWSER_HOME      0xAC

#define VKEY_VOLUME_MUTE         0xAD
#define VKEY_VOLUME_DOWN         0xAE
#define VKEY_VOLUME_UP           0xAF
#define VKEY_MEDIA_NEXT_TRACK    0xB0
#define VKEY_MEDIA_PREV_TRACK    0xB1
#define VKEY_MEDIA_STOP          0xB2
#define VKEY_MEDIA_PLAY_PAUSE    0xB3
#define VKEY_LAUNCH_MAIL         0xB4
#define VKEY_LAUNCH_MEDIA_SELECT 0xB5
#define VKEY_LAUNCH_APP1         0xB6
#define VKEY_LAUNCH_APP2         0xB7


/*
 * 0xB8 - 0xB9 : reserved
 */

#define VKEY_OEM_1      0xBA // ';:' for US
#define VKEY_OEM_PLUS   0xBB // '+' any country
#define VKEY_OEM_COMMA  0xBC // ',' any country
#define VKEY_OEM_MINUS  0xBD // '-' any country
#define VKEY_OEM_PERIOD 0xBE // '.' any country
#define VKEY_OEM_2      0xBF // '/?' for US
#define VKEY_OEM_3      0xC0 // '`~' for US

/*
 * 0xC1 - 0xC2 : reserved
 */


/*
 * 0xC3 - 0xDA : Gamepad input
 */

#define VKEY_GAMEPAD_A                       0xC3 // reserved
#define VKEY_GAMEPAD_B                       0xC4 // reserved
#define VKEY_GAMEPAD_X                       0xC5 // reserved
#define VKEY_GAMEPAD_Y                       0xC6 // reserved
#define VKEY_GAMEPAD_RIGHT_SHOULDER          0xC7 // reserved
#define VKEY_GAMEPAD_LEFT_SHOULDER           0xC8 // reserved
#define VKEY_GAMEPAD_LEFT_TRIGGER            0xC9 // reserved
#define VKEY_GAMEPAD_RIGHT_TRIGGER           0xCA // reserved
#define VKEY_GAMEPAD_DPAD_UP                 0xCB // reserved
#define VKEY_GAMEPAD_DPAD_DOWN               0xCC // reserved
#define VKEY_GAMEPAD_DPAD_LEFT               0xCD // reserved
#define VKEY_GAMEPAD_DPAD_RIGHT              0xCE // reserved
#define VKEY_GAMEPAD_MENU                    0xCF // reserved
#define VKEY_GAMEPAD_VIEW                    0xD0 // reserved
#define VKEY_GAMEPAD_LEFT_THUMBSTICK_BUTTON  0xD1 // reserved
#define VKEY_GAMEPAD_RIGHT_THUMBSTICK_BUTTON 0xD2 // reserved
#define VKEY_GAMEPAD_LEFT_THUMBSTICK_UP      0xD3 // reserved
#define VKEY_GAMEPAD_LEFT_THUMBSTICK_DOWN    0xD4 // reserved
#define VKEY_GAMEPAD_LEFT_THUMBSTICK_RIGHT   0xD5 // reserved
#define VKEY_GAMEPAD_LEFT_THUMBSTICK_LEFT    0xD6 // reserved
#define VKEY_GAMEPAD_RIGHT_THUMBSTICK_UP     0xD7 // reserved
#define VKEY_GAMEPAD_RIGHT_THUMBSTICK_DOWN   0xD8 // reserved
#define VKEY_GAMEPAD_RIGHT_THUMBSTICK_RIGHT  0xD9 // reserved
#define VKEY_GAMEPAD_RIGHT_THUMBSTICK_LEFT   0xDA // reserved


#define VKEY_OEM_4 0xDB //  '[{' for US
#define VKEY_OEM_5 0xDC //  '\|' for US
#define VKEY_OEM_6 0xDD //  ']}' for US
#define VKEY_OEM_7 0xDE //  ''"' for US
#define VKEY_OEM_8 0xDF

/*
 * 0xE0 : reserved
 */

/*
 * Various extended or enhanced keyboards
 */
#define VKEY_OEM_AX   0xE1 //  'AX' key on Japanese AX kbd
#define VKEY_OEM_102  0xE2 //  "<>" or "\|" on RT 102-key kbd.
#define VKEY_ICO_HELP 0xE3 //  Help key on ICO
#define VKEY_ICO_00   0xE4 //  00 key on ICO

#define VKEY_PROCESSKEY 0xE5
#define VKEY_ICO_CLEAR  0xE6
#define VKEY_PACKET     0xE7


/*
 * 0xE8 : unassigned
 */

/*
 * Nokia/Ericsson definitions
 */
#define VKEY_OEM_RESET   0xE9
#define VKEY_OEM_JUMP    0xEA
#define VKEY_OEM_PA1     0xEB
#define VKEY_OEM_PA2     0xEC
#define VKEY_OEM_PA3     0xED
#define VKEY_OEM_WSCTRL  0xEE
#define VKEY_OEM_CUSEL   0xEF
#define VKEY_OEM_ATTN    0xF0
#define VKEY_OEM_FINISH  0xF1
#define VKEY_OEM_COPY    0xF2
#define VKEY_OEM_AUTO    0xF3
#define VKEY_OEM_ENLW    0xF4
#define VKEY_OEM_BACKTAB 0xF5

#define VKEY_ATTN      0xF6
#define VKEY_CRSEL     0xF7
#define VKEY_EXSEL     0xF8
#define VKEY_EREOF     0xF9
#define VKEY_PLAY      0xFA
#define VKEY_ZOOM      0xFB
#define VKEY_NONAME    0xFC
#define VKEY_PA1       0xFD
#define VKEY_OEM_CLEAR 0xFE


#endif