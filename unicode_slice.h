#ifndef UNICODE_SLICE_H
#define UNICODE_SLICE_H

    #include "utf8_unicode/utf8_unicode.h"
    #include <stdint.h>

    // unicode切片结构体，支持最多6,5536个字符，参考go切片、rust切片等切片设计
    typedef struct {
        uint16_t 长度;
        uint16_t 容量;
        unicode字符 * 数据;
    } unicode切片;

    // 提供以下操作函数
    void unicode切片_初始化(unicode切片 * 切片指针, int 初始容量); //√ 已测试
    void unicode切片_清空(unicode切片 * 切片指针); //√ 已测试
    void unicode切片_重置(unicode切片 * 切片指针); //√ 已测试
    void unicode切片_扩容(unicode切片 * 切片指针, int 期望容量);  //√ 已测试
    void unicode切片_追加(unicode切片 * 切片指针, unicode字符 待追加字符); //√ 已测试
    void unicode切片_文件打印(unicode切片 * 切片指针, FILE * 输出文件); //√ 已测试
    void unicode切片_文件序列化打印(unicode切片 * 切片指针, FILE * 输出文件); //√ 已测试
    // 以下为 纯函数
    int64_t unicode切片_转整数(unicode切片 * 切片指针, uint8_t 进制); //√ 已测试
    uint32_t unicode切片_计算散列值(unicode切片 * 切片指针, uint32_t 最大值); //√ 已测试
#endif