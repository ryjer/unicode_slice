#include "../utf8_unicode/utf8_unicode.h"
#include "unicode切片.h"

// gcc -g -Wall test.c unicode切片.c ../utf8_unicode/utf8_unicode.c && ./a.out
// 测试用例
int main() {
    unicode切片 切片;
    FILE * 输出文件 = stdout;
// 原始字符串 转 切片
    fprintf(输出文件, "#### 字符串转切片 ####\n");
    unicode切片 来自字符串的切片 = 原始utf8字符串转unicode切片("hello");
    unicode切片_文件序列化打印(来自字符串的切片, 输出文件);
    fputc('\n', 输出文件);
// 切片 转 原始字符串
    fprintf(输出文件, "#### 切片转字符串 ####\n");
    char * 新字符串 = unicode切片转原始utf8字符串(来自字符串的切片);
    fprintf(输出文件, "%s\n", 新字符串);
// 初始化切片
    unicode切片_初始化(&切片, 8);
    fprintf(输出文件, "#### 初始化 ####\n");
    unicode切片_文件序列化打印(切片, 输出文件);
    fputc('\n', 输出文件);
// test.txt 文件字符追加
    fprintf(输出文件, ".......字符追加中.......\n");
    // utf8文件读取
    FILE * inputFile = fopen("test.txt", "r");
    utf8字符体 输入字符 = 文件_读取utf8字符(inputFile); // 读取utf8编码
    while (输入字符.长度 != 0) {
        unicode切片_追加(&切片, utf8转unicode(输入字符));
        // 读入下一个字符
        输入字符=文件_读取utf8字符(inputFile);
    }
    fprintf(输出文件, "......字符追加完成......\n");
// 序列化测试
    fprintf(输出文件, "#### 序列化 ####\n");
    unicode切片_文件序列化打印(切片, 输出文件);
    fputc('\n', 输出文件);
// 复制测试
    fprintf(输出文件, "切片复制测试，新切片序列化: \n");
    unicode切片 新切片 = unicode切片_复制(切片);
    unicode切片_文件序列化打印(新切片, 输出文件);
// 计算散列值
    fprintf(输出文件, "\n模%d散列值: %u \n", 63, unicode切片_计算散列值(切片, 63));
// 切片判等测试
    fprintf(输出文件, "#### 切片判等测试 ####\n");
    // 新切片 ？？ 切片
    unicode切片_文件序列化打印(新切片, 输出文件);
    fprintf(输出文件, " %c= ", unicode切片_判等(新切片, 切片)?'=':'!');
    unicode切片_文件序列化打印(切片, 输出文件);
    fputc('\n', 输出文件);
    // 新切片 ？？ 来自字符串的切片
    unicode切片_文件序列化打印(新切片, 输出文件);
    fprintf(输出文件, " %c= ", unicode切片_判等(新切片, 来自字符串的切片)?'=':'!');
    unicode切片_文件序列化打印(来自字符串的切片, 输出文件);
    fputc('\n', 输出文件);
// 切片-原始utf8字符串 判等测试
    fprintf(输出文件, "#### 切片-utf8字符串 判等 ####\n");
    char * 待比对utf8字符串;
    // 新切片 ？？ 切片
    待比对utf8字符串 = "你好";
    unicode切片_文件序列化打印(新切片, 输出文件);
    fprintf(输出文件, " %c= ", unicode切片_原始utf8字符串_判等(新切片, 待比对utf8字符串)?'=':'!');
    fprintf(输出文件, "\"%s\" \n", 待比对utf8字符串);
    // 新切片 ？？ 来自字符串的切片
    待比对utf8字符串 = "你好？";
    unicode切片_文件序列化打印(新切片, 输出文件);
    fprintf(输出文件, " %c= ", unicode切片_原始utf8字符串_判等(新切片, 待比对utf8字符串)?'=':'!');
    fprintf(输出文件, "\"%s\" \n", 待比对utf8字符串);
// 文件打印测试
    fprintf(输出文件, "文件打印测试：\n");
    unicode切片_文件打印(切片, 输出文件);
    fputc('\n', 输出文件);
// 重置测试
    fprintf(输出文件, "重置测试：\n");
    unicode切片_重置(&切片);
    unicode切片_文件序列化打印(切片, 输出文件);
    fputc('\n', 输出文件);
}