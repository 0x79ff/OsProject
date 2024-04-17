#pragma once
#include"Inode.h"
#include"BufferManager.h"
#include"DiskDriver.h"

/*SuperBlock  Inode  文件区*/


class SuperBlock
{
	/* Functions */
public:
	SuperBlock();
	~SuperBlock();
	
	/* Members */
public:
	int		s_isize;		/* 外存Inode区占用的盘块数 */
	int		s_fsize;		/* 盘块总数 */
	
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




class FileSystem
{
public:
	/* static consts */
    
    static const int SUPER_BLOCK_SECTOR_NUMBER = 0;	/* 定义SuperBlock位于磁盘上的扇区号，占据01两个扇区。 */

	static const int ROOTINO = 1;			/* 文件系统根目录外存Inode编号 */

	static const int INODE_NUMBER_PER_SECTOR = 8;		/* 外存INode对象长度为64字节，每个磁盘块可以存放512/64 = 8个外存Inode */
	static const int INODE_ZONE_START_SECTOR = 2;		/* 外存Inode区位于磁盘上的起始扇区号 */
	static const int INODE_ZONE_SIZE = 1024 - 2;		/* 磁盘上外存Inode区占据的扇区数 */

	static const int DATA_ZONE_START_SECTOR = 1024;		/* 数据区的起始扇区号 */
	static const int DATA_ZONE_END_SECTOR = 18000 - 1;	/* 数据区的结束扇区号 */
	static const int DATA_ZONE_SIZE = 18000 - DATA_ZONE_START_SECTOR;	/* 数据区占据的扇区数量 */
	
    /* Functions */
public:
	/* Constructors */
	FileSystem();
	/* Destructors */
	~FileSystem();

	/* 
	* 初始化成员变量
	*/
	void Initialize();
	/* 
	* 系统初始化时读入 SuperBlock
	*/
	void LoadSuperBlock();

	/* 
	* 获取该文件系统的 SuperBlock
	*/
	SuperBlock *GetFS();

	/* 
	* 将 SuperBlock 对象的内存副本更新到
	* 存储设备的 SuperBlock 中去
	*/
	void Update();

	/* 
	* 在存储设备 dev 上分配一个空闲
	* 外存 INode，一般用于创建新的文件。
	*/
	Inode *IAlloc();

	/* 
	* 释放存储设备 dev 上编号为 number
	* 的外存 INode，一般用于删除文件。
	*/
	void IFree(int number);

	/* 
	* 在存储设备 dev 上分配空闲磁盘块
	*/
	Buf *Alloc();
	
	/* 
	* 释放存储设备上编号为 blkno 的磁盘块
	*/
	void Free(int blkno);
private:
	BufferManager *m_BufferManager; /* FileSystem 类需要缓存管理模块(BufferManager)提供的接口 */

};