#include "../utf8_unicode/utf8_unicode.h"
#include "slice_unicode.h"

// gcc -g -Wall test.c slice_unicode.c ../utf8_unicode/utf8_unicode.c && ./a.out
// 测试用例
int main() {
    unicode切片 切片;
    // 初始化切片
    unicode切片_初始化(&切片, 8);
    fprintf(stdout, "初始化与序列化: ");
    unicode切片_文件序列化打印(&切片, stdout);
    fputc('\n', stdout);
    // test.txt 文件字符追加
    fprintf(stdout, ".......字符追加中.......\n");
    // utf8文件读取
    FILE * inputFile = fopen("test.txt", "r");
    utf8字符体 输入字符 = 文件_读取utf8字符(inputFile); // 读取utf8编码
    while (输入字符.长度 != 0) {
        unicode切片_追加(&切片, utf8转unicode(输入字符));
        // 读入下一个字符
        输入字符=文件_读取utf8字符(inputFile);
    }
    fprintf(stdout, "......字符追加完成......\n");
    // 序列化测试
    fprintf(stdout, "序列化测试: \n");
    unicode切片_文件序列化打印(&切片, stdout);
    fputc('\n', stdout);
    // 计算散列值
    fprintf(stdout, "模%d散列值: %u \n",64 , unicode切片_计算散列值(&切片, 64));
    // 文件打印测试
    fprintf(stdout, "****文件打印测试：\n");
    unicode切片_文件打印(&切片, stdout);
    fputc('\n', stdout);
    // 清空测试
    fprintf(stdout, "****清空测试：\n");
    unicode切片_重置(&切片);
    unicode切片_文件序列化打印(&切片, stdout);
    fputc('\n', stdout);
}