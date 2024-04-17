#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <iostream>
#include <cstring>

const char diskFileName[] = "SecondaryFS.img";

class DiskDriver {
public:
	FILE* pointer;                     //磁盘文件指针

public:
	DiskDriver() 
	{
		pointer = fopen(diskFileName, "rb+"); /*读写打开二进制文件 文件必须存在*/
		if(pointer==NULL){
			//创建1000kb的文件
			pointer = fopen(diskFileName,"wb");
			for(int i=0;i<8000*1024;i++){
				char zero = 0;
				fwrite(&zero,sizeof(zero),1,pointer);
			}
			fclose(pointer);
		    pointer = fopen(diskFileName, "rb+"); /*读写打开二进制文件 文件必须存在*/
		}
	}
	~DiskDriver() 
	{
		if (pointer != NULL) {
			fclose(pointer);
		}
	}

	//写磁盘函数
	void write(const char* inBuffer, int inSize, int offset = -1, int origin = SEEK_SET) {
		if (offset >= 0)
			fseek(pointer, offset, origin);
		fwrite(inBuffer, inSize, 1, pointer);
		return;
	}

	//读磁盘函数
	void read(char* outBuffer, int outSize, int offset = -1, int origin = SEEK_SET) {
		if (offset >= 0)
			fseek(pointer, offset, origin);
		fread(outBuffer, outSize, 1, pointer);
		return;
	}

};

class DiskINode{
public:
	unsigned int d_mode; /* 文件类型 和 访问控制位 */
	int d_nlink; /* 硬联结计数，即该文件在目录树中不同路径名的数量 */
	short d_uid; /* 文件所有者的uid*/
	short d_gid; /* 文件所有者的gid */
	int d_size; /* 文件长度，字节为单位 */
	int d_addr[10]; /* 地址映射表，登记逻辑块和物理块之间的映射关系 */
	int d_atime; /* 最后访问时间 */
	int d_mtime; /* 最后修改时间 */

public:
	DiskINode()
	{
		this->d_mode = 0;
		this->d_nlink = 0;
		this->d_uid = 0;
		this->d_gid = 0;//?
		this->d_size = 0;
		memset(d_addr,0,sizeof(d_addr));
		this->d_atime = 0;
		this->d_mtime = 0;
	}
	//~DiskINode();
};