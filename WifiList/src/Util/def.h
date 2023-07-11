#ifndef DEF_H
#define DEF_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <string>
#include <QRect>

using namespace std;

#define IS_RELEASE_MODE	0

#define KDLED_NUM	0x01	/* num lock led */
#define KDLED_CAP	0x02	/* caps lock led */
#define KDLED_SCR	0x04	/* scroll lock led */

#define GET_WIDTH 240
#define GET_HEIGHT 724
#define GET_SPACE 7
#define PUSH_SPACE 14
#define GETPUSH_SPACE 26

// 预览界面长宽
#define REVIEW_WIDHT 178
#define REVIEW_HEIGHT 100

// QListWidgetItem的高度
#define ITEM_HEIGHT 150
#define MAX_HEIGHT 156

// 主窗口的长宽
#define MAIN_WIDTH 1920
#define MAIN_HEIGHT 1080

//ocr添加框的各大小宽度
#define ADD_ITEM_SMALL_WIDTH    35
#define ADD_ITEM_SMALL_HEIGHT   27
#define ADD_ITEM_MIDDLE_WIDTH   55
#define ADD_ITEM_MIDDLE_HEIGHT  40
#define ADD_ITEM_BIG_WIDTH      72
#define ADD_ITEM_BIG_HEIGHT     58

// 鼠标光标图标
#define CURSOR_HAND ":/Image/Util/icon_cursorHand.png"
#define CURSOR_NORMAL ":/Image/Util/icon_mouse.png"
#define CURSOR_FORBID ":/Image/Util/icon_forbidden.png"

// 方便测试内存泄漏的宏定义
#define IS_GET_ATUO 0 // 接管是否自动刷新
#define IS_GET_ADD_ITEM 1 // 是否允许添加item
#define IS_GET_TRAN 0 // 是否允许创建透明窗口
#define IS_GET_REVIEW 0 // 是否允许预览显示

#define _WITH_AI        1

#define setbit(x,y) x|=(1<<y); //将X的第Y位置1
#define clrbit(x,y) x&=~(1<<y); //将X的第Y位清0

#define MENU_WIDTH 240
#define MENU_HEIGHT 100

//#define STACK_WIDTH 710
//#define STACK_HEIGHT 580
#define STACK_WIDTH 1080
#define STACK_HEIGHT 702

// 语言
typedef enum{
    UI_CH,
    UI_EN
}LANGUAGE;

// 快捷键类型(包括组合键)
enum HotKeyType{
    HKT_F5,
    HKT_Esc,
    HKT_Meta,
    HKT_Enter,
    HKT_CtrlAndF1,
    HKT_CtrlAndF2,
    HKT_ShiftAndEnter,
    HKT_DoubleShift,
    HKT_DoubleCtrl,
    HKT_DoubleAlt,
    HKT_CtrlAndAdd,     //Ctrl + +
    HKT_CtrlAndSub,     //Ctrl + -
    HKT_AltAndZ,
    HKT_ScrollLock,
    HKT_Pause,
    HKT_SysReq,
    HKT_Backslash,
};

// 鼠标动作
enum MouseAction{
    MS_Press,
    MS_Move,
    MS_Release,
    MS_Drag,
    MS_DragMove,
    MS_Drop,
};

// 位置
enum EnumPos {
    POS_A =0,
    POS_B,
    POS_C,
    POS_D,
    POS_E,
    POS_F,
    POS_G,
    POS_H,
    POS_I,
    POS_J,
    POS_K,
    POS_L,
    POS_M
};

// 边框颜色
enum EnumColor {
    No =0,
    Red,
    Blue
};

// 用于控制只显示中英文、虚拟键盘是否显示的枚举
enum EnumControl {
    CH_keyHide = 0,
    CH_KeyShow,
    EN_keyHide,
    EN_KeyShow
};

// 拖拽类型
enum EnumDragType {
    DragEnter =0,
    DragMove,
    DragLeave
};

// view窗口偏移枚举
enum EnumWin {
    WIN_Language = 0,
    WIN_LanguageM,
    WIN_LanguageH,
    WIN_KeyBoard,
    WIN_LoginOut,
    WIN_Meeting,
    Reserve1,       //2022-0708预留的位置，暂时未用到，，此位置在 32位中的 14位
    Reserve2,       //15位

    OCR_Set_TxtEnter,    //16位开始为ocr,占8位  16-23位
    OCR_Set_TxtTab,
    OCR_Set_TxtSpace,
    OCR_Set_TxtNull,
    OCR_Set_ScreenEnter,
    OCR_Set_ScreenTab,
    OCR_Set_ScreenSpace,
    OCR_Set_ScreenNull,
};

// 用于控制只显示某个界面的枚举
enum EnumGetPush {
    Get = 0,
    GetPush,
    Push,
    BigScr,
    Meeting,
    Set,
    Split,
    Polling,        //轮询
    Tag,            //标签
    AI,
    Login,
    LoginOut,
    HotKey,
    Get_LoginOut,
    GetPush_LoginOut,
    Push_LoginOut,
    BigScr_LoginOut,
    Meeting_Hide,
    Set_LoginOut,
    HotKey_LoginOut, // 快捷键界面与注销界面同时显示
    Set_User,
	Set_User_Group,         //用户组显示界面
    Set_User_Add_Group,     //添加用户组界面
    Set_Matrix,
    Set_ModifyPasswd,
    Set_TempAuth,
    Set_Language,
    User,
    Matrix,
    ModifyPasswd,
    TempAuth,
    Usb,
    Logo,
    AllClose,
    Set_ADDomain,           //设置AD域
    Set_SysLabel,           //设置系统标签
    Other
};

typedef enum
{
    KVM_PRE_MODE_SP,	//单一画面(Single picture)
    KVM_PRE_MODE_PIP,	//画中画(Painting in painting)
    KVM_PRE_MODE_OBTS,	//一大两小(One big two small)
    KVM_PRE_MODE_FB,	//四等分(Four bisection)
    KVM_PRE_MODE_MAX,	//最大化(Maximize)
    KVM_PRE_MODE_TB,	//二等分(Two Bisection)
    //KVM_PRE_MODE_OBSS,	//一大7小(One big seven small)
    KVM_PRE_MODE_OBES,	//一大八小(One big eight small)
    KVM_PRE_MODE_OPT,	//1+12(One plus twelve)
    KVM_PRE_MODE_UALB,	//上下等分(Upper and lower bisection)
    KVM_PRE_MODE_OBFS,	//一大5小(One big five small)
    KVM_PRE_MODE_JG,	//九宫格(Jiugong grid)
    KVM_PRE_MODE_CUSTOM0,//自定义0
    KVM_PRE_MODE_CUSTOM1,//自定义1
    KVM_PRE_MODE_CUSTOM2,//自定义2
    KVM_PRE_MODE_CUSTOM3,//自定义3
    KVM_PRE_MODE_CUSTOM4,//自定义4
    KVM_PRE_MODE_CUSTOM5,//自定义5
    KVM_PRE_MODE_CUSTOM6,//自定义6
    KVM_PRE_MODE_CUSTOM7,//自定义7
    KVM_PRE_MODE_CUSTOM8,//自定义8
    KVM_PRE_MODE_CUSTOM9,//自定义9
    KVM_PRE_MODE_BUTT
}KVM_PRE_MODE_E;


typedef struct StructGrid {
public:
    QRect rect;
    bool isPress;

    // 默认构造函数
    StructGrid() {

    }

    // 构造函数初始化
    StructGrid(QRect _rect, bool _isPress = false)
    {
        rect = _rect;
        isPress = _isPress;
    }

    void setVal(bool val) {
        isPress = val;
    }
}StGrid;



#endif // DEF_H
