#pragma once


class Utility
{
public:
    static int Min(int a, int b);
    static int StringLength(char *pString);
    static void StringCopy(char *src, char *dst);

    /* 用于在读、写文件时，高速缓存与用户指定目标内存区域之间数据传送 */
    static void IOMove(unsigned char *from, unsigned char *to, int count);
    
    /* 以 src 为源地址，dst 为目的地址，复制 count 个双字 */
    static void DWordCopy(int *src, int *dst, int count);
};