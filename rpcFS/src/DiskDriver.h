#pragma once
#include <stdio.h>
#include "Buf.h"


class DiskDriver
{
private:
	static const char *DISK_FILE_NAME; /* 磁盘镜像文件名 */
	static const int BLOCK_SIZE = 512; /* 数据块大小为 512 字节 */
	FILE *fp; /* 磁盘镜像文件指针 */
public:
	DiskDriver();
	~DiskDriver();
	//void Initialize(); /* 初始化磁盘镜像 */
	void IO(Buf *bp); /* 根据 IO 请求块进行读写 */
};

