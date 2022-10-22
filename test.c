#include "utf8_unicode/utf8_unicode.h"
#include "unicode_slice.h"

// gcc -g -Wall test.c unicode_slice.c utf8_unicode/utf8_unicode.c && ./a.out
// 测试用例
int main() {
    unicode切片 切片;
    // 初始化切片
    unicode切片_初始化(&切片, 8);
    unicode切片_文件序列化打印(&切片, stdout);
    fputc('\n', stdout);
    // test.txt 文件字符追加
    FILE * inputFile = fopen("test.txt", "r");
    utf8字符体 输入字符 = 文件_读取utf8字符(inputFile); // 读取utf8编码
    while (输入字符.长度 != 0) {
        unicode切片_追加(&切片, utf8转unicode(输入字符));
        // 读入下一个字符
        输入字符=文件_读取utf8字符(inputFile);
    }
    unicode切片_文件序列化打印(&切片, stdout);
    fputc('\n', stdout);
    // 清空测试
    unicode切片_清空(&切片);
    unicode切片_文件序列化打印(&切片, stdout);
    fputc('\n', stdout);
}