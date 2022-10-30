#ifndef UNICODE切片_H
#define UNICODE切片_H

    #include "../utf8_unicode/utf8_unicode.h"
    #include <stdint.h>
    #include <stdio.h>
    #include <stdlib.h>
    
    typedef struct {// unicode只读静态串结构，使用 变长数组
        uint16_t 长度;
        unicode字符 数据[0];
    } unicode静态串;
    
    typedef struct {// unicode连续动态串结构，使用 变长数组
        uint16_t 长度;
        uint16_t 容量;
        unicode字符 数据[0];
    } unicode动态串;
    
    typedef struct {// unicode切片结构体，支持最多6,5536个字符，参考go切片、rust切片等切片设计
        uint16_t 长度;
        uint16_t 容量;
        unicode字符 * 数据;
    } unicode切片;

    // 提供以下操作函数
    void        unicode切片_初始化(unicode切片 * 切片指针, int 初始容量); //√ 已测试
    char*       unicode切片转原始utf8字符串(unicode切片 切片);
    unicode切片 原始utf8字符串转unicode切片(char * utf8字符串); //√ 已测试
    void        unicode切片_清空(unicode切片 * 切片指针); //√ 已测试
    void        unicode切片_重置(unicode切片 * 切片指针); //√ 已测试
    void        unicode切片_扩容(unicode切片 * 切片指针, int 期望容量);  //√ 已测试
    void        unicode切片_追加(unicode切片 * 切片指针, unicode字符 待追加字符); //√ 已测试
    unicode切片 unicode切片_复制(unicode切片 源切片);
    void        unicode切片_文件打印(unicode切片 切片, FILE * 输出文件); //√ 已测试
    void        unicode切片_文件序列化打印(unicode切片 切片, FILE * 输出文件); //√ 已测试
    // 以下为 纯函数
    bool        unicode切片_判等(unicode切片 被比对切片, unicode切片 比对切片); //√ 已测试
    int64_t     unicode切片_转整数(unicode切片 切片, uint8_t 进制); //√ 已测试
    uint32_t    unicode切片_计算散列值(unicode切片 切片, uint32_t 模); //√ 已测试
#endif