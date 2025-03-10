#ifndef KEYMAPPING_H
#define KEYMAPPING_H

#include <QMap>
#include <QtGlobal>

/*hid的key值*/
// #define HID_KEY_NONE                        0x00
#define HID_KEY_A                           0x04
#define HID_KEY_B                           0x05
#define HID_KEY_C                           0x06
#define HID_KEY_D                           0x07
#define HID_KEY_E                           0x08
#define HID_KEY_F                           0x09
#define HID_KEY_G                           0x0A
#define HID_KEY_H                           0x0B
#define HID_KEY_I                           0x0C
#define HID_KEY_J                           0x0D
#define HID_KEY_K                           0x0E
#define HID_KEY_L                           0x0F
#define HID_KEY_M                           0x10
#define HID_KEY_N                           0x11
#define HID_KEY_O                           0x12
#define HID_KEY_P                           0x13
#define HID_KEY_Q                           0x14
#define HID_KEY_R                           0x15
#define HID_KEY_S                           0x16
#define HID_KEY_T                           0x17
#define HID_KEY_U                           0x18
#define HID_KEY_V                           0x19
#define HID_KEY_W                           0x1A
#define HID_KEY_X                           0x1B
#define HID_KEY_Y                           0x1C
#define HID_KEY_Z                           0x1D
#define HID_KEY_1                           0x1E
#define HID_KEY_2                           0x1F
#define HID_KEY_3                           0x20
#define HID_KEY_4                           0x21
#define HID_KEY_5                           0x22
#define HID_KEY_6                           0x23
#define HID_KEY_7                           0x24
#define HID_KEY_8                           0x25
#define HID_KEY_9                           0x26
#define HID_KEY_0                           0x27
#define HID_KEY_ENTER                       0x28
#define HID_KEY_ESCAPE                      0x29
#define HID_KEY_BACKSPACE                   0x2A
#define HID_KEY_TAB                         0x2B
#define HID_KEY_SPACE                       0x2C
#define HID_KEY_MINUS                       0x2D
#define HID_KEY_EQUAL                       0x2E
#define HID_KEY_BRACKET_LEFT                0x2F
#define HID_KEY_BRACKET_RIGHT               0x30
#define HID_KEY_BACKSLASH                   0x31
#define HID_KEY_EUROPE_1                    0x32
#define HID_KEY_SEMICOLON                   0x33
#define HID_KEY_APOSTROPHE                  0x34
#define HID_KEY_GRAVE                       0x35
#define HID_KEY_COMMA                       0x36
#define HID_KEY_PERIOD                      0x37
#define HID_KEY_SLASH                       0x38
#define HID_KEY_CAPS_LOCK                   0x39
#define HID_KEY_F1                          0x3A
#define HID_KEY_F2                          0x3B
#define HID_KEY_F3                          0x3C
#define HID_KEY_F4                          0x3D
#define HID_KEY_F5                          0x3E
#define HID_KEY_F6                          0x3F
#define HID_KEY_F7                          0x40
#define HID_KEY_F8                          0x41
#define HID_KEY_F9                          0x42
#define HID_KEY_F10                         0x43
#define HID_KEY_F11                         0x44
#define HID_KEY_F12                         0x45
#define HID_KEY_PRINT_SCREEN                0x46
#define HID_KEY_SCROLL_LOCK                 0x47
#define HID_KEY_PAUSE                       0x48
#define HID_KEY_INSERT                      0x49
#define HID_KEY_HOME                        0x4A
#define HID_KEY_PAGE_UP                     0x4B
#define HID_KEY_DELETE                      0x4C
#define HID_KEY_END                         0x4D
#define HID_KEY_PAGE_DOWN                   0x4E
#define HID_KEY_ARROW_RIGHT                 0x4F
#define HID_KEY_ARROW_LEFT                  0x50
#define HID_KEY_ARROW_DOWN                  0x51
#define HID_KEY_ARROW_UP                    0x52
#define HID_KEY_NUM_LOCK                    0x53
#define HID_KEY_KEYPAD_DIVIDE               0x54
#define HID_KEY_KEYPAD_MULTIPLY             0x55
#define HID_KEY_KEYPAD_SUBTRACT             0x56
#define HID_KEY_KEYPAD_ADD                  0x57
#define HID_KEY_KEYPAD_ENTER                0x58
#define HID_KEY_KEYPAD_1                    0x59
#define HID_KEY_KEYPAD_2                    0x5A
#define HID_KEY_KEYPAD_3                    0x5B
#define HID_KEY_KEYPAD_4                    0x5C
#define HID_KEY_KEYPAD_5                    0x5D
#define HID_KEY_KEYPAD_6                    0x5E
#define HID_KEY_KEYPAD_7                    0x5F
#define HID_KEY_KEYPAD_8                    0x60
#define HID_KEY_KEYPAD_9                    0x61
#define HID_KEY_KEYPAD_0                    0x62
#define HID_KEY_KEYPAD_DECIMAL              0x63
#define HID_KEY_EUROPE_2                    0x64
#define HID_KEY_APPLICATION                 0x65
#define HID_KEY_POWER                       0x66
#define HID_KEY_KEYPAD_EQUAL                0x67
#define HID_KEY_F13                         0x68
#define HID_KEY_F14                         0x69
#define HID_KEY_F15                         0x6A
#define HID_KEY_F16                         0x6B
#define HID_KEY_F17                         0x6C
#define HID_KEY_F18                         0x6D
#define HID_KEY_F19                         0x6E
#define HID_KEY_F20                         0x6F
#define HID_KEY_F21                         0x70
#define HID_KEY_F22                         0x71
#define HID_KEY_F23                         0x72
#define HID_KEY_F24                         0x73
#define HID_KEY_EXECUTE                     0x74
#define HID_KEY_HELP                        0x75
#define HID_KEY_MENU                        0x76
#define HID_KEY_SELECT                      0x77
#define HID_KEY_STOP                        0x78
#define HID_KEY_AGAIN                       0x79
#define HID_KEY_UNDO                        0x7A
#define HID_KEY_CUT                         0x7B
#define HID_KEY_COPY                        0x7C
#define HID_KEY_PASTE                       0x7D
#define HID_KEY_FIND                        0x7E
#define HID_KEY_MUTE                        0x7F
#define HID_KEY_VOLUME_UP                   0x80
#define HID_KEY_VOLUME_DOWN                 0x81
#define HID_KEY_LOCKING_CAPS_LOCK           0x82
#define HID_KEY_LOCKING_NUM_LOCK            0x83
#define HID_KEY_LOCKING_SCROLL_LOCK         0x84
#define HID_KEY_KEYPAD_COMMA                0x85
#define HID_KEY_KEYPAD_EQUAL_SIGN           0x86
#define HID_KEY_KANJI1                      0x87
#define HID_KEY_KANJI2                      0x88
#define HID_KEY_KANJI3                      0x89
#define HID_KEY_KANJI4                      0x8A
#define HID_KEY_KANJI5                      0x8B
#define HID_KEY_KANJI6                      0x8C
#define HID_KEY_KANJI7                      0x8D
#define HID_KEY_KANJI8                      0x8E
#define HID_KEY_KANJI9                      0x8F
#define HID_KEY_LANG1                       0x90
#define HID_KEY_LANG2                       0x91
#define HID_KEY_LANG3                       0x92
#define HID_KEY_LANG4                       0x93
#define HID_KEY_LANG5                       0x94
#define HID_KEY_LANG6                       0x95
#define HID_KEY_LANG7                       0x96
#define HID_KEY_LANG8                       0x97
#define HID_KEY_LANG9                       0x98
#define HID_KEY_ALTERNATE_ERASE             0x99
#define HID_KEY_SYSREQ_ATTENTION            0x9A
#define HID_KEY_CANCEL                      0x9B
#define HID_KEY_CLEAR                       0x9C
#define HID_KEY_PRIOR                       0x9D
#define HID_KEY_RETURN                      0x9E
#define HID_KEY_SEPARATOR                   0x9F
#define HID_KEY_OUT                         0xA0
#define HID_KEY_OPER                        0xA1
#define HID_KEY_CLEAR_AGAIN                 0xA2
#define HID_KEY_CRSEL_PROPS                 0xA3
#define HID_KEY_EXSEL                       0xA4

extern const QMap<int,quint8> KEY_HID_MAP = {
    {1, 0x01}, // 鼠标左键
    {2, 0x02},// 鼠标右键
    {Qt::Key_A,HID_KEY_A},
    {Qt::Key_B,HID_KEY_B},
    {Qt::Key_C,HID_KEY_C},
    {Qt::Key_D,HID_KEY_D},
    {Qt::Key_E,HID_KEY_E},
    {Qt::Key_F,HID_KEY_F},
    {Qt::Key_G,HID_KEY_G},
    {Qt::Key_H,HID_KEY_H},
    {Qt::Key_I,HID_KEY_I},
    {Qt::Key_J,HID_KEY_J},
    {Qt::Key_K,HID_KEY_K},
    {Qt::Key_L,HID_KEY_L},
    {Qt::Key_M,HID_KEY_M},
    {Qt::Key_N,HID_KEY_N},
    {Qt::Key_O,HID_KEY_O},
    {Qt::Key_P,HID_KEY_P},
    {Qt::Key_Q,HID_KEY_Q},
    {Qt::Key_R,HID_KEY_R},
    {Qt::Key_S,HID_KEY_S},
    {Qt::Key_T,HID_KEY_T},
    {Qt::Key_U,HID_KEY_U},
    {Qt::Key_V,HID_KEY_V},
    {Qt::Key_W,HID_KEY_W},
    {Qt::Key_X,HID_KEY_X},
    {Qt::Key_Y,HID_KEY_Y},
    {Qt::Key_Z,HID_KEY_Z},
    {Qt::Key_0,HID_KEY_0},
    {Qt::Key_1,HID_KEY_1},
    {Qt::Key_2,HID_KEY_2},
    {Qt::Key_3,HID_KEY_3},
    {Qt::Key_4,HID_KEY_4},
    {Qt::Key_5,HID_KEY_5},
    {Qt::Key_6,HID_KEY_6},
    {Qt::Key_7,HID_KEY_7},
    {Qt::Key_8,HID_KEY_8},
    {Qt::Key_9,HID_KEY_9},
    {Qt::Key_Escape,    HID_KEY_ESCAPE},          // 0x01000000 -> 0x29
    {Qt::Key_Tab,       HID_KEY_TAB},             // 0x01000001 -> 0x2B
    {Qt::Key_Backspace, HID_KEY_BACKSPACE},       // 0x01000003 -> 0x2A
    {Qt::Key_Return,     HID_KEY_ENTER},   // 回车键
    {Qt::Key_Space,     HID_KEY_SPACE},           // 0x20 -> 0x2C
    {Qt::Key_Delete,    HID_KEY_DELETE},          // 0x01000007 -> 0x4C
    {Qt::Key_F1,  HID_KEY_F1},     // 0x01000030 -> 0x3A
    {Qt::Key_F2,  HID_KEY_F2},     // 0x01000031 -> 0x3B
    {Qt::Key_F3,  HID_KEY_F3},     // 0x01000032 -> 0x3C
    {Qt::Key_F4,  HID_KEY_F4},     // 0x01000033 -> 0x3D
    {Qt::Key_F5,  HID_KEY_F5},     // 0x01000034 -> 0x3E
    {Qt::Key_F6,  HID_KEY_F6},     // 0x01000035 -> 0x3F
    {Qt::Key_F7,  HID_KEY_F7},     // 0x01000036 -> 0x40
    {Qt::Key_F8,  HID_KEY_F8},     // 0x01000037 -> 0x41
    {Qt::Key_F9,  HID_KEY_F9},     // 0x01000038 -> 0x42
    {Qt::Key_F10, HID_KEY_F10},    // 0x01000039 -> 0x43
    {Qt::Key_F11, HID_KEY_F11},    // 0x0100003A -> 0x44
    {Qt::Key_F12, HID_KEY_F12},    // 0x0100003B -> 0x45
    {Qt::Key_F13, HID_KEY_F13},    // 0x0100003C -> 0x68
    {Qt::Key_F14, HID_KEY_F14},    // 0x0100003D -> 0x69
    {Qt::Key_F15, HID_KEY_F15},    // 0x0100003E -> 0x6A
    {Qt::Key_F16, HID_KEY_F16},    // 0x0100003F -> 0x6B
    {Qt::Key_F17, HID_KEY_F17},    // 0x01000040 -> 0x6C
    {Qt::Key_F18, HID_KEY_F18},    // 0x01000041 -> 0x6D
    {Qt::Key_F19, HID_KEY_F19},    // 0x01000042 -> 0x6E
    {Qt::Key_F20, HID_KEY_F20},    // 0x01000043 -> 0x6F
    {Qt::Key_F21, HID_KEY_F21},    // 0x01000044 -> 0x70
    {Qt::Key_F22, HID_KEY_F22},    // 0x01000045 -> 0x71
    {Qt::Key_F23, HID_KEY_F23},    // 0x01000046 -> 0x72
    {Qt::Key_F24, HID_KEY_F24}     // 0x01000047 -> 0x73
};

extern const QMap<int,quint8> HID_KEY_MAP = {
    {0x00,0}, // 鼠标左键单击
    {0x01,1},// 鼠标右键单击
    {0x02,2},// 鼠标左键长按
    {0x03,3},// 鼠标右键长按
    {HID_KEY_A,Qt::Key_A},
    {HID_KEY_B,Qt::Key_B},
    {HID_KEY_C,Qt::Key_C},
    {HID_KEY_D,Qt::Key_D},
    {HID_KEY_E,Qt::Key_E},
    {HID_KEY_F,Qt::Key_F},
    {HID_KEY_G,Qt::Key_G},
    {HID_KEY_H,Qt::Key_H},
    {HID_KEY_I,Qt::Key_I},
    {HID_KEY_J,Qt::Key_J},
    {HID_KEY_K,Qt::Key_K},
    {HID_KEY_L,Qt::Key_L},
    {HID_KEY_M,Qt::Key_M},
    {HID_KEY_N,Qt::Key_N},
    {HID_KEY_O,Qt::Key_O},
    {HID_KEY_P,Qt::Key_P},
    {HID_KEY_Q,Qt::Key_Q},
    {HID_KEY_R,Qt::Key_R},
    {HID_KEY_S,Qt::Key_S},
    {HID_KEY_T,Qt::Key_T},
    {HID_KEY_U,Qt::Key_U},
    {HID_KEY_V,Qt::Key_V},
    {HID_KEY_W,Qt::Key_W},
    {HID_KEY_X,Qt::Key_X},
    {HID_KEY_Y,Qt::Key_Y},
    {HID_KEY_Z,Qt::Key_Z},
    {HID_KEY_1,Qt::Key_1},
    {HID_KEY_2,Qt::Key_2},
    {HID_KEY_3,Qt::Key_3},
    {HID_KEY_4,Qt::Key_4},
    {HID_KEY_5,Qt::Key_5},
    {HID_KEY_6,Qt::Key_6},
    {HID_KEY_7,Qt::Key_7},
    {HID_KEY_8,Qt::Key_8},
    {HID_KEY_9,Qt::Key_9},
    {HID_KEY_0,Qt::Key_0},
    {HID_KEY_ESCAPE      ,Qt::Key_Escape   },          // 0x01000000 -> 0x29
    {HID_KEY_TAB         ,Qt::Key_Tab     },             // 0x01000001 -> 0x2B
    {HID_KEY_BACKSPACE   ,Qt::Key_Backspace},       // 0x01000003 -> 0x2A
    {HID_KEY_ENTER       ,Qt::Key_Return},   // 回车键
    {HID_KEY_SPACE       ,Qt::Key_Space},           // 0x20 -> 0x2C
    {HID_KEY_DELETE      ,Qt::Key_Delete},          // 0x01000007 -> 0x4C
    {HID_KEY_F1,Qt::Key_F1  },     // 0x01000030 -> 0x3A
    {HID_KEY_F2,Qt::Key_F2  },     // 0x01000031 -> 0x3B
    {HID_KEY_F3,Qt::Key_F3  },     // 0x01000032 -> 0x3C
    {HID_KEY_F4,Qt::Key_F4  },     // 0x01000033 -> 0x3D
    {HID_KEY_F5,Qt::Key_F5  },     // 0x01000034 -> 0x3E
    {HID_KEY_F6,Qt::Key_F6  },     // 0x01000035 -> 0x3F
    {HID_KEY_F7,Qt::Key_F7  },     // 0x01000036 -> 0x40
    {HID_KEY_F8,Qt::Key_F8  },     // 0x01000037 -> 0x41
    {HID_KEY_F9,Qt::Key_F9  },     // 0x01000038 -> 0x42
    {HID_KEY_F10,Qt::Key_F10 },    // 0x01000039 -> 0x43
    {HID_KEY_F11,Qt::Key_F11 },    // 0x0100003A -> 0x44
    {HID_KEY_F12,Qt::Key_F12 },    // 0x0100003B -> 0x45
    {HID_KEY_F13,Qt::Key_F13 },    // 0x0100003C -> 0x68
    {HID_KEY_F14,Qt::Key_F14 },    // 0x0100003D -> 0x69
    {HID_KEY_F15,Qt::Key_F15 },    // 0x0100003E -> 0x6A
    {HID_KEY_F16,Qt::Key_F16 },    // 0x0100003F -> 0x6B
    {HID_KEY_F17,Qt::Key_F17 },    // 0x01000040 -> 0x6C
    {HID_KEY_F18,Qt::Key_F18 },    // 0x01000041 -> 0x6D
    {HID_KEY_F19,Qt::Key_F19 },    // 0x01000042 -> 0x6E
    {HID_KEY_F20,Qt::Key_F20 },    // 0x01000043 -> 0x6F
    {HID_KEY_F21,Qt::Key_F21 },    // 0x01000044 -> 0x70
    {HID_KEY_F22,Qt::Key_F22 },    // 0x01000045 -> 0x71
    {HID_KEY_F23,Qt::Key_F23 },    // 0x01000046 -> 0x72
    {HID_KEY_F24,Qt::Key_F24 }     // 0x01000047 -> 0x73
};
#endif // KEYMAPPING_H















