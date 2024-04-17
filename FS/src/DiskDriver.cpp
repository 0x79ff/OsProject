#include "DiskDriver.h"
#include <cstdio>
#include <iostream>

const char *DiskDriver::DISK_FILE_NAME = "SecondaryFS.img";

DiskDriver::DiskDriver()
{
	this->fp = fopen(DISK_FILE_NAME, "rb+");
}
DiskDriver::~DiskDriver()
{
	//nothing to do
	if(this->fp!=NULL){
		fclose(this->fp);
	}
}

// void DiskDriver::Initialize()
// {

// }
	
void DiskDriver::IO(Buf *bp)
{
	/* 根据 IO 请求块进行读写 */
	
	// Buf中的变量
    // int     b_wcount; /* 需传送的字节数 */
    // unsigned char *b_addr; /* 指向该缓存控制块所管理的缓冲区的首地址 */
	// int		b_blkno;		/* 磁盘逻辑块号 */
	
	//只有两种操作 读或者写 而且b_wcount都是512字节
	if(bp->b_flags & Buf::B_READ){
		//READ
		fseek(fp,bp->b_blkno* this->BLOCK_SIZE,SEEK_SET);
		fread(bp->b_addr,bp->b_wcount,1,this->fp);
		/*更改bp信息*/
		bp->b_flags &= ~(Buf::B_READ);
		bp->b_flags |= Buf::B_DONE;
	}
	else{
		//WRITE
		fseek(this->fp,bp->b_blkno* this->BLOCK_SIZE,SEEK_SET);
		fwrite(bp->b_addr,bp->b_wcount,1,this->fp);
		bp->b_flags &= ~(Buf::B_WRITE);
		bp->b_flags |= Buf::B_DONE;
	} 
	return;
}

