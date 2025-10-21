#ifndef DEF_H
#define DEF_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <QRect>

using namespace std;

// 鼠标光标图标
#define CURSOR_HAND ":/Image/Util/icon_cursorHand.png"
#define CURSOR_NORMAL ":/Image/Util/icon_mouse.png"
#define CURSOR_FORBID ":/Image/Util/icon_forbidden.png"


//#define STACK_WIDTH 710
//#define STACK_HEIGHT 580
#define STACK_WIDTH 1080
#define STACK_HEIGHT 702

enum EnumSplitMode {
    SplitSingle = 0,
    SplitFour,
    SplitOneBigFiveSmall,
    SplitNineGrid,
    SplitNull
};

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
