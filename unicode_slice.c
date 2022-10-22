#include "unicode_slice.h"
/**********************************************************
 * 初始化unicode切片
 * 切片指针：unicode切片/字符串存储结构
 * 初始容量：切片/字符串初始化分配空间
 *********************************************************/
void unicode切片_初始化(unicode切片 * 切片指针, int 初始容量) {
    if (切片指针 != NULL) {
        切片指针->容量 = 初始容量;
        切片指针->长度 = 0;
        切片指针->数据 = (unicode字符 *)malloc(sizeof(unicode字符) * 初始容量);
    }
}
/**********************************************************
 * 清空unicode切片的数据区
 * 切片指针：unicode切片/字符串存储结构
 *********************************************************/
void unicode切片_清空(unicode切片 * 切片指针) {
    if (切片指针 != NULL) { //保证切片存在
        if (切片指针->数据 != NULL) { //数据区存在，释放数据区
            free(切片指针->数据);
            切片指针->数据 = NULL;
        }
        // 再清空描述块
        切片指针->长度 = 0;
        切片指针->容量 = 0;
    }
}
/**********************************************************
 * 重置切片到初始化状态
 * 切片指针：unicode切片/字符串存储结构
 *********************************************************/
void unicode切片_重置(unicode切片 * 切片指针) {
    unicode切片_清空(切片指针);
    unicode切片_初始化(切片指针, 8);  //初始分配8字符的空间
}
/**********************************************************
 * 拓展unicode切片容量到足够容纳期望容量
 * 切片指针：unicode切片/字符串存储结构
 * 期望容量：切片要达到的最低容量，这里保证分配的容量不小于该值
 *********************************************************/
void unicode切片_扩容(unicode切片 * 切片指针, int 期望容量) {
    int 新容量 = 切片指针->容量;
    unicode字符 * 数据区指针;
    while (新容量 < 期望容量) {
        新容量 *= 2;          // 翻倍扩容
    }
    数据区指针 = realloc(切片指针->数据, sizeof(unicode字符) * 新容量);
    // realloc失败检查
    if (数据区指针 == NULL) {
        error("切片扩容内存分配失败！\n");
    }
    // 更新容量和数据区指针
    切片指针->容量 = 新容量;
    切片指针->数据 = 数据区指针;
}
/**********************************************************
 * 追加单个unicode字符到unicode切片/字符串对象
 * 切片指针：unicode切片/字符串存储结构
 * 待追加字符：需要追加到尾部的unicode字符
 *********************************************************/
void unicode切片_追加(unicode切片 * 切片指针, unicode字符 待追加字符) {
    int 新长度 = 切片指针->长度 + 1;
    // 先检查扩容
    if (新长度 > (切片指针->容量)) {
        unicode切片_扩容(切片指针, 新长度);
    }
    // 然后添加字符
    (切片指针->数据)[新长度-1] = 待追加字符;
    // 最后更新长度
    切片指针->长度 = 新长度;
}

/**********************************************************
 * 以utf8格式打印字符串
 * 切片指针：unicode切片/字符串存储结构
 * 输出文件：输出到的目标文件
 *********************************************************/
void unicode切片_文件打印(unicode切片 * 切片指针, FILE * 输出文件) {
    utf8字符体 utf8字符;
    // 遍历切片数据区，逐个打印 unicode 字符
    for (int i = 0; i < 切片指针->长度; i++) {
        utf8字符 = unicode转utf8(切片指针->数据[i]);
        // 根据编码字节数，逐个输出字节
        for (int j = 0; j < utf8字符.长度; j++) {
            fputc(utf8字符.编码[j], 输出文件);
        }
    }
}

/**********************************************************
 * 序列化：将整个切片序列化后打印到指定文件，用于调试
 * 切片指针：unicode切片/字符串存储结构
 * 输出文件：输出到的目标文件
 *********************************************************/
void unicode切片_文件序列化打印(unicode切片 * 切片指针, FILE * 输出文件) {
    utf8字符体 utf8字符;
    // 打印相关信息
    fprintf(输出文件, "{%d %d [", 切片指针->长度, 切片指针->容量);
    if (切片指针->数据 != NULL) {
        // 遍历切片数据区，逐个打印 unicode 字符
        for (int i = 0; i < 切片指针->长度; i++) {
            utf8字符 = unicode转utf8(切片指针->数据[i]);
            // 根据编码字节数，逐个输出字节
            for (int j = 0; j < utf8字符.长度; j++) {
                fputc(utf8字符.编码[j], 输出文件);
            }
        }
    }
    // 打印结尾
    fprintf(输出文件, "]}");
}