#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include"DiskDriver.h"

/*SuperBlock  Inode  文件区*/

/*
 * 文件系统存储资源管理块(Super Block)的定义。
 */
class SuperBlock
{
	/* Functions */
public:
	/* Constructors */
	//SuperBlock();
	/* Destructors */
	//~SuperBlock();
	
	/* Members */
public:
	int		s_isize;		/* 外存Inode区占用的盘块数 1022*/
	int		s_fsize;		/* 盘块总数 2000 - 1024 = 976*/
	
	int		s_nfree;		/* 直接管理的空闲盘块数量 */
	int		s_free[100];	/* 直接管理的空闲盘块索引表 */
	
	int		s_ninode;		/* 直接管理的空闲外存Inode数量 */
	int		s_inode[100];	/* 直接管理的空闲外存Inode索引表 */
	
	int		s_flock;		/* 封锁空闲盘块索引表标志 用不到*/
	int		s_ilock;		/* 封锁空闲Inode表标志 用不到*/
	
	int		s_fmod;			/* 内存中super block副本被修改标志，意味着需要更新外存对应的Super Block */
	int		s_ronly;		/* 本文件系统只能读出 用不到*/
	int		s_time;			/* 最近一次更新时间 */
	int		padding[47];	/* 填充使SuperBlock块大小等于1024字节，占据2个扇区 */
};

//目录项
class DirectoryEntry 
{
public:
	static const int DIRSIZ = 28;
public:
	int ino;                   
	char name[DIRSIZ];           
public:
    DirectoryEntry(){
        this->ino = 0;
        memset(this->name,0,sizeof(this->name));        
    };
    //~DirectoryEntry();
};

//组长块
class GroupLeaderBlock
{
public:
    int s_nfree;
	int s_free[100];
	int padding[27];
public:
    GroupLeaderBlock(){
		this->s_nfree=0;
		memset(this->s_free,0,sizeof(this->s_free));	
	};
};

class FileSystem
{
public:
	/* static consts */
    static const int BLOCK_SIZE = 512;
    static const int INODE_SIZE = 64;
    
    static const int DISK_SECTOR_NUMBER = 9000*1024/512;/*18000*/

	static const int ROOTINO = 1;			/* 文件系统根目录外存Inode编号 */

	static const int INODE_NUMBER_PER_SECTOR = BLOCK_SIZE/INODE_SIZE;     /* 外存INode对象长度为64字节，每个磁盘块可以存放512/64 = 8个外存Inode */
	static const int INODE_ZONE_START_SECTOR = 2;		/* 外存Inode区位于磁盘上的起始扇区号 */
	static const int INODE_ZONE_SIZE = 1024 - INODE_ZONE_START_SECTOR;		/* 磁盘上外存Inode区占据的扇区数 */
    static const int INODE_NUMBER_ALL = INODE_ZONE_SIZE*INODE_NUMBER_PER_SECTOR;
    
	static const int DATA_ZONE_START_SECTOR = 1024;		/* 数据区的起始扇区号 */
	static const int DATA_ZONE_END_SECTOR = DISK_SECTOR_NUMBER - 1;	/* 数据区的结束扇区号 */
	static const int DATA_ZONE_SIZE = DISK_SECTOR_NUMBER - DATA_ZONE_START_SECTOR;	/* 数据区占据的扇区数量 */
    

	SuperBlock* superBlock;
    DiskDriver* diskDriver;
	
    /* Functions */
public:
	/* Constructors */
	FileSystem();
	/* Destructors */
	//~FileSystem();

    void FormatSuperBlock();
    void FormatImg();

};