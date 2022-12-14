#include "unicode切片.h"
/******************************************************************************
 * 将以'\0'结尾的utf8编码字符串转换为一个新的 unicode切片，然后返回 新切片控制块
 * utf8字符串：源utf8字符串 的首地址
 *****************************************************************************/
unicode切片 原始utf8字符串转unicode切片(char * utf8字符串指针) {
    utf8字符体  读入utf8字符;
    unicode字符 读入unicode字符;
    unicode切片 新切片;
    int i = 0;
    unicode切片_初始化(&新切片, 1); //初始化为 1 字符空间
    // 开始读取字符
    读入utf8字符 = 原始utf8字符串_读取utf8字符(&utf8字符串指针[i]);
    读入unicode字符 = utf8转unicode(读入utf8字符);
    while (读入unicode字符 != '\0') { //原始字符串以 '\0' 作为结尾
        unicode切片_追加(&新切片, 读入unicode字符);
        i += 读入utf8字符.长度;
        读入utf8字符 = 原始utf8字符串_读取utf8字符(&utf8字符串指针[i]);
        读入unicode字符 = utf8转unicode(读入utf8字符);
    }
    return 新切片;
} 
/******************************************************************************
 * 将unicode切片转换为以'\0'结尾的utf8编码字符串，然后返回新字符串数组的首地址
 * 切片：需要进行转换的切片
 * 提示：字符串位于堆内存中，注意手动释放
 *****************************************************************************/
char * unicode切片转原始utf8字符串(unicode切片 切片) {
    unicode字符 当前字符unicode编码;
    utf8字符体 utf8字符;
    int 总字节数 = 0;
    // 统计总计需要的字节数，别忘了末尾的 '\0'
    for (int i=0; i<切片.长度; i++) {
        utf8字符 = unicode转utf8(切片.数据[i]);
        总字节数 += utf8字符.长度;
    }
    总字节数 += 1; // 末尾'\0'，需要额外1字节空间
    // 申请堆内存空间
    char * 新字符串 = (char*)malloc(总字节数*sizeof(char));
    // 转换unicode字符，写入新
    新字符串[总字节数-1] = '\0'; //先写入末尾
    int 字节索引 = 0;
    for (int i=0; i<切片.长度; i++) { //遍历unicode串
        当前字符unicode编码 = 切片.数据[i];
        utf8字符 = unicode转utf8(当前字符unicode编码);
        //写入字符串
        for (int j=0; j<utf8字符.长度; j++) {
            新字符串[字节索引] = utf8字符.编码[j];
            字节索引++;
        }
    }
    return 新字符串;
}
/**********************************************************
 * 初始化unicode切片
 * 切片指针：unicode切片/字符串存储结构
 * 初始容量：切片/字符串初始化分配空间
 *********************************************************/
void unicode切片_初始化(unicode切片 * 切片指针, int 初始容量) {
    if (切片指针 != NULL) {
        切片指针->容量 = 初始容量;
        切片指针->长度 = 0;
        切片指针->数据 = (unicode字符 *)malloc(初始容量 * sizeof(unicode字符));
    }
}
/**********************************************************
 * 清空unicode切片的数据区，并将数据区指针 置为 NULL
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
 * 重置已有非空切片到初始化状态
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
    unicode字符 * 数据区;
    while (新容量 < 期望容量) {
        新容量 *= 2;          // 翻倍扩容
    }
    数据区 = realloc(切片指针->数据, 新容量 * sizeof(unicode字符));
    // realloc失败检查
    if (数据区 == NULL) {
        perror("切片扩容内存分配失败！\n");
    }
    // 更新容量和数据区指针
    切片指针->容量 = 新容量;
    切片指针->数据 = 数据区;
}
/**********************************************************
 * 追加单个unicode字符到unicode切片/字符串对象，
 * 警告：超过unicode编码范围，会添加0长字符，即静默且不添加字符
 * 切片指针：unicode切片/字符串存储结构
 * 待追加字符：需要追加到尾部的unicode字符
 *********************************************************/
void unicode切片_追加(unicode切片 * 切片指针, unicode字符 待追加字符) {
    // 检查是否在unicode 31位编码之内
    if ((待追加字符 & 0x70000000) != 0) { //非法编码，直接返回
        return;
    } else { // unicode 编码为31位，最高位应为0
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
}
/**********************************************************
 * 深度复制一个新的切片，然后返回 新切片的结构体
 * 切片指针：unicode切片/字符串存储结构
 *********************************************************/
unicode切片 unicode切片_复制(unicode切片 源切片) {
    unicode切片 新切片;
    unicode切片_初始化(&新切片, 源切片.长度); //初始化数据区空间
    // 逐个追加数据区数组元素
    for (int i=0; i<源切片.长度; i++) {
        新切片.数据[i] = 源切片.数据[i];
    }
    新切片.长度 = 源切片.长度;
    return 新切片;
}
/**********************************************************
 * 深度比对两个切片，判断两个unicode切片的数据视图是否完全相对
 * 被比对切片：被比对的unicode切片
 * 比对切片：与被比对切片进行比较的切片
 *********************************************************/
bool unicode切片_判等(unicode切片 被比对切片, unicode切片 比对切片) {
    // 首先进行长度判断
    if (被比对切片.长度 != 比对切片.长度) {
        return false;
    }
    // 再逐个比对字符
    for (int i=0; i<(被比对切片.长度); i++) {
        if (被比对切片.数据[i] != 比对切片.数据[i]) {
            return false;
        }
    }
    // 以上都相同，则为相对
    return true;
}
/**********************************************************
 * 比对一个unicode切片和一个utf8字符串，判断其是否相同
 * 被比对切片：被比对的unicode切片
 * utf8字符串首指针：与被比对切片进行比较的切片
 *********************************************************/
bool unicode切片_原始utf8字符串_判等(unicode切片 被比对切片, char* utf8字符串指针) {
    utf8字符体  字符串utf8字符;
    unicode字符 字符串unicode字符;
    int i = 0; //被比对切片索引
    int j = 0; //字符串字节索引
    // 开始读取字符，每次从utf8字符串读取一个字符的utf8编码，解码为unicode后比对
    字符串utf8字符 = 原始utf8字符串_读取utf8字符(&utf8字符串指针[j]);
    字符串unicode字符 = utf8转unicode(字符串utf8字符);
    while (i<被比对切片.长度 && 字符串unicode字符!='\0') { //当两串都不结束时，继续
        if (被比对切片.数据[i] != 字符串unicode字符) { return false; } //比对当前字符
        // 更新切片和字符串索引，更新字符串字符计数
        i ++;
        j += 字符串utf8字符.长度;
        // 从utf8字符串读入下一字符
        字符串utf8字符 = 原始utf8字符串_读取utf8字符(&utf8字符串指针[j]);
        字符串unicode字符 = utf8转unicode(字符串utf8字符);
    }
    // 某一个字符串读取结束，且之前的字符全部相等
    // 如果都到此结束，则相等
    if (i==被比对切片.长度 && 字符串unicode字符=='\0') {
        return true;
    } else {
        return false;
    }
}
/**********************************************************
 * 以utf8格式打印字符串
 * 切片指针：unicode切片/字符串存储结构
 * 输出文件：输出到的目标文件
 *********************************************************/
void unicode切片_文件打印(unicode切片 切片, FILE * 输出文件) {
    utf8字符体 utf8字符;
    // 遍历切片数据区，逐个打印 unicode 字符
    for (int i = 0; i < 切片.长度; i++) {
        utf8字符 = unicode转utf8(切片.数据[i]);
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
void unicode切片_文件序列化打印(unicode切片 切片, FILE * 输出文件) {
    utf8字符体 utf8字符;
    // 打印相关信息
    fprintf(输出文件, "{%d %d [\"", 切片.长度, 切片.容量);
    if (切片.数据 != NULL) {
        // 遍历切片数据区，逐个打印 unicode 字符
        for (int i = 0; i < 切片.长度; i++) {
            utf8字符 = unicode转utf8(切片.数据[i]);
            // 根据编码字节数，逐个输出字节
            for (int j = 0; j < utf8字符.长度; j++) {
                fputc(utf8字符.编码[j], 输出文件);
            }
        }
    }
    // 打印结尾
    fprintf(输出文件, "\"]}");
}
/**********************************************************
 * 字符串转换：将'前缀'数字字符串转换为对应的机器整数，返回
 * 切片指针：unicode切片/字符串存储结构
 * 进制: 只支持2进制、8进制、10进制、16进制
 *      为0则根据前缀判断， 指定进制则认为没有前缀
 *********************************************************/
int64_t unicode切片_转整数(unicode切片 切片, uint8_t 进制) {
    uint64_t 数字值 = 0;
    int i = 0;
    if (进制 == 0) {
        if (切片.数据[0]=='0') {       // 自动判断进制，并调整第一个有效数字字符指针 i
            i=2; 
            if (切片.数据[1]=='x' || 切片.数据[1]=='h') { 进制=16;} // 0xff 0hff
            else if (切片.数据[1]=='b') { 进制=2;}    //2进制 0b1111
            else if (切片.数据[1]=='o') { 进制=8;}    //8进制 0o73
            else if (切片.数据[1]=='d') { 进制=10;}    //10进制 0d15
            else if (是10进制数字(切片.数据[1])) { i=0; 进制=10; } // 有多余0前缀的10进制数字
        } else {
            i = 0;
            进制 = 10;
        }
    }
    for (; i < 切片.长度; i++) {
        数字值 = 数字值*进制 + 十六进制字符转数字(切片.数据[i]);
    }
    return 数字值;
}
/**********************************************************
 * 计算散列值：使用哈希散列函数，计算对应字符串的散列值
 * 切片指针：unicode切片/字符串存储结构
 * 最大值：哈希值的范围，最终结果范围是[0, 最大值]
 *********************************************************/
uint32_t unicode切片_计算散列值(unicode切片 切片, uint32_t 最大值) {
    uint32_t 散列值 = 0;
    uint32_t tmp;
    for (int i=0; i<切片.长度; i++) {
        散列值 = (散列值<<4) + 切片.数据[i];
        tmp = 散列值 & 0xf0000000;  // 取高4位
        if (tmp!=0) { 散列值 ^= ~tmp; } // 如果高4位不为0，取到数据。
        散列值 &= ~tmp;
    }
    return 散列值 % 最大值;
}

// 以下为未测试方法

/**********************************************************
 * unicode切片转静态串，从切片创建一个等价的静态串，返回静态串地址
 * 切片指针：unicode切片/字符串存储结构
 *********************************************************/
unicode静态串 * unicode切片_转静态串(unicode切片 切片) {
    // 申请容纳空间
    unicode静态串 * 新静态串 = (unicode静态串 *)malloc(sizeof(unicode静态串)+(切片.长度)*sizeof(unicode字符));
    // 复制数据
    新静态串->长度 = 切片.长度;
    for (int i=0; i<切片.长度; i++) {
        新静态串->数据[i] = 切片.数据[i];
    }
    return 新静态串;
}
/**********************************************************
 * unicode切片转动态串，从切片创建一个等价的动态串，返回动态串地址
 * 切片指针：unicode切片/字符串存储结构
 *********************************************************/
unicode动态串 * unicode切片_转动态串(unicode切片 切片) {
    unicode动态串 * 新动态串 = (unicode动态串 *)malloc(sizeof(unicode动态串)+(切片.容量)*sizeof(unicode字符));
    // 复制数据
    新动态串->长度 = 切片.长度;
    新动态串->容量 = 切片.容量;
    for (int i=0; i<切片.长度; i++) {
        新动态串->数据[i] = 切片.数据[i];
    }
    return 新动态串;
}
/**********************************************************
 * 深度比对两个切片，判断两个unicode切片的数据视图是否完全相对
 * 被比对切片：被比对的unicode切片
 * 比对切片：与被比对切片进行比较的切片
 *********************************************************/
bool unicode切片_unicode静态串_判等(unicode切片 * 被比对切片, unicode静态串 静态串) {
    // 首先进行长度判断
    if (被比对切片->长度 != 静态串.长度) {
        return false;
    }
    // 再逐个比对字符
    for (int i=0; i<(被比对切片->长度); i++) {
        if (被比对切片->数据[i] != 静态串.数据[i]) {
            return false;
        }
    }
    // 以上都相同，则为相对
    return true;
}