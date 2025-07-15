#pragma once

class Buf
{
public:
    enum BufFlag /* b_flags 中标志位 */
    {
        B_WRITE = 0x1, /* 写操作。将缓存中的信息写到硬盘上去 */
        B_READ = 0x2, /* 读操作。从盘读取信息到缓存中 */
        B_DONE = 0x4, /* I/O 操作结束 */
        B_ERROR = 0x8, /* I/O 因出错而终止 */
        B_BUSY = 0x10, /* 相应缓存正在使用中 */
        B_WANTED = 0x20, /* 有进程正在等待使用该 buf 管理的资源，清 B_BUSY 标志时，要唤醒这种进程 */
        B_ASYNC = 0x40, /* 异步 I/O，不需要等待其结束 */
        B_DELWRI = 0x80 /* 延迟写，在相应缓存要移做他用时，再将其内容写到相应块设备上 */
    };
public:
    unsigned int b_flags; /* 缓存控制块标志位 */
    int padding; /* 4 字节填充，使得 b_forw 和 b_back 在 Buf 类中与 Devtab 类中的字段顺序能够一致，否则强制转换会出错。 */
    
    /* 缓存控制块队列勾连指针 */
    Buf*    av_forw;
    Buf*    av_back;


    int     b_wcount; /* 需传送的字节数 */
    unsigned char *b_addr; /* 指向该缓存控制块所管理的缓冲区的首地址 */
	int		b_blkno;		/* 磁盘逻辑块号 */

};
