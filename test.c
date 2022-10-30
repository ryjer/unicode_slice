#include "../utf8_unicode/utf8_unicode.h"
#include "unicode切片.h"

// gcc -g -Wall test.c unicode切片.c ../utf8_unicode/utf8_unicode.c && ./a.out
// 测试用例
int main() {
    unicode切片 切片;
    FILE * 输出文件 = stdout;
// 从字符串构造切片
    fprintf(输出文件, "#### 从字符串构造 ####\n");
    unicode切片 来自字符串的切片 = 原始utf8字符串转unicode切片("hello");
    unicode切片_文件序列化打印(来自字符串的切片, 输出文件);
    fputc('\n', 输出文件);
// 初始化切片
    unicode切片_初始化(&切片, 8);
    fprintf(输出文件, "#### 初始化 ####");
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

    unicode切片_文件序列化打印(新切片, 输出文件);
    fprintf(输出文件, " %c= ", unicode切片_判等(新切片, 切片)?'=':'!');
    unicode切片_文件序列化打印(切片, 输出文件);
    fputc('\n', 输出文件);

    unicode切片_文件序列化打印(新切片, 输出文件);
    fprintf(输出文件, " %c= ", unicode切片_判等(新切片, 来自字符串的切片)?'=':'!');
    unicode切片_文件序列化打印(来自字符串的切片, 输出文件);
    fputc('\n', 输出文件);
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