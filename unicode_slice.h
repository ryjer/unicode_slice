#ifndef UNICODE_SLICE_H
#define UNICODE_SLICE_H

    #include "utf8_unicode/utf8_unicode.h"
    #include <stdint.h>
    #include <stdlib.h>
    // unicode 切片结构体，参考go切片、rust切片等切片设计
    typedef struct {
        uint32_t 长度;
        uint32_t 容量;
        unicode字符 * 数据;
    } unicode切片;

    // 提供以下操作函数
    void unicode切片_初始化(unicode切片 * 切片指针, int 初始容量);
    void unicode切片_清空(unicode切片 * 切片指针);
    void unicode切片_重置(unicode切片 * 切片指针);
    void unicode切片_扩容(unicode切片 * 切片指针, int 期望容量);
    void unicode切片_追加(unicode切片 * 切片指针, unicode字符 待追加字符);
    void unicode切片_文件打印(unicode切片 * 切片指针, FILE * 输出文件);
    void unicode切片_文件序列化打印(unicode切片 * 切片指针, FILE * 输出文件);
#endif