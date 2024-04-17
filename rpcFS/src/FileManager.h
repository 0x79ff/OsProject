#pragma once
#include "FileSystem.h"
#include "OpenFileManager.h"
#include "File.h"

class FileManager
{
public:
	/* 目录搜索模式，用于NameI()函数 */
	enum DirectorySearchMode
	{
		OPEN = 0,		/* 以打开文件方式搜索目录 */
		CREATE = 1,		/* 以新建文件方式搜索目录 */
		DELETE = 2		/* 以删除文件方式搜索目录 */
	};

	/* Functions */
public:
	FileManager();
	~FileManager();


	/* 
	 * @comment 初始化对全局对象的引用
	 */
	void Initialize();//ok

	/* 
	 * @comment Open()系统调用处理过程
	 */
	void Open();//ok

	/* 
	 * @comment Creat()系统调用处理过程
	 */
	void Creat();//ok

	/* 
	 * @comment Open()、Creat()系统调用的公共部分
	 */
	void Open1(Inode* pInode, int mode, int trf);//ok

	/* 
	 * @comment Close()系统调用处理过程
	 */
	void Close();//ok

	/* 
	 * @comment Seek()系统调用处理过程
	 */
	void Seek();//ok

	/* 
	 * @comment FStat()获取文件信息
	 */
	void FStat();

	/* 
	 * @comment Stat()获取文件信息
	 */
	void Stat();

	/* FStat()和Stat()系统调用的共享例程 */
	void Stat1(Inode* pInode, unsigned long statBuf);

	/* 
	 * @comment Read()系统调用处理过程
	 */
	void Read();

	/* 
	 * @comment Write()系统调用处理过程
	 */
	void Write();

	/* 
	 * @comment 读写系统调用公共部分代码
	 */
	void Rdwr(enum File::FileFlags mode);

	/* 
	 * @comment 目录搜索，将路径转化为相应的Inode，
	 * 返回上锁后的Inode
	 */
	Inode* NameI(char (*func)(), enum DirectorySearchMode mode);

	/* 
	 * @comment 获取路径中的下一个字符
	 */
	static char NextChar();//ok

	/* 
	 * @comment 被Creat()系统调用使用，用于为创建新文件分配内核资源
	 */
	Inode* MakNode(unsigned int mode);//ok

	/* 
	 * @comment 向父目录的目录文件写入一个目录项
	 */
	void WriteDir(Inode* pInode);//ok

	/*
	 * @comment 设置当前工作路径
	 */
	void SetCurDir(char* pathname);//ok

	/* 
	 * @comment 检查对文件或目录的搜索、访问权限，作为系统调用的辅助函数
	 */
	int Access(Inode* pInode, unsigned int mode);//ok


	/* 改变当前工作目录 */
	void ChDir();//ok
    
	/* 取消文件 */
	void UnLink();

	/* 用于建立特殊设备文件的系统调用 */
	void MkNod();
	
public:
	/* 根目录内存Inode */
	Inode* rootDirInode;

	/* 对全局对象g_FileSystem的引用，该对象负责管理文件系统存储资源 */
	FileSystem* m_FileSystem;
	
	/* 对全局对象g_InodeTable的引用，该对象负责内存Inode表的管理 */
	InodeTable* m_InodeTable;

	/* 对全局对象g_OpenFileTable的引用，该对象负责打开文件表项的管理 */
	OpenFileTable* m_OpenFileTable;
};


class DirectoryEntry
{
public:
	static const int DIRSIZ = 28;	/* 目录项中路径部分的最大字符串长度 */
public:
	DirectoryEntry();
	~DirectoryEntry();
public:
	int m_ino;		/* 目录项中Inode编号部分 */
	char m_name[DIRSIZ];	/* 目录项中路径名部分 */
};

