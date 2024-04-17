#pragma once

#include "File.h"
#include "Inode.h"
#include "FileManager.h"

class User
{
public:

	/* u_error's Error Code */
	/* 1~32 来自linux 的内核代码中的/usr/include/asm/errno.h, 其余for V6++ */
	enum ErrorCode//??与系统冲突??
	{
		MYNOERROR	= 0,	/* No error */
		MYEPERM	= 1,	/* Operation not permitted */
		MYENOENT	= 2,	/* No such file or directory */
		MYESRCH	= 3,	/* No such process */
		MYEINTR	= 4,	/* Interrupted system call */
		MYEIO		= 5,	/* I/O error */
		MYENXIO	= 6,	/* No such device or address */
		MYE2BIG	= 7,	/* Arg list too long */
		MYENOEXEC	= 8,	/* Exec format error */
		MYEBADF	= 9,	/* Bad file number */
		MYECHILD	= 10,	/* No child processes */
		MYEAGAIN	= 11,	/* Try again */
		MYENOMEM	= 12,	/* Out of memory */
		MYEACCES	= 13,	/* Permission denied */
		MYEFAULT  = 14,	/* Bad address */
		MYENOTBLK	= 15,	/* Block device required */
		MYEBUSY 	= 16,	/* Device or resource busy */
		MYEEXIST	= 17,	/* File exists */
		MYEXDEV	= 18,	/* Cross-device link */
		MYENODEV	= 19,	/* No such device */
		MYENOTDIR	= 20,	/* Not a directory */
		MYEISDIR	= 21,	/* Is a directory */
		MYEINVAL	= 22,	/* Invalid argument */
		MYENFILE	= 23,	/* File table overflow */
		MYEMFILE	= 24,	/* Too many open files */
		MYENOTTY	= 25,	/* Not a typewriter(terminal) */
		MYETXTBSY	= 26,	/* Text file busy */
		MYEFBIG	= 27,	/* File too large */
		MYENOSPC	= 28,	/* No space left on device */
		MYESPIPE	= 29,	/* Illegal seek */
		MYEROFS	= 30,	/* Read-only file system */
		MYEMLINK	= 31,	/* Too many links */
		MYEPIPE	= 32,	/* Broken pipe */
		MYENOSYS	= 100,
		//MYEFAULT	= 106
	};

public:
	/* 系统调用相关成员 */
	int u_ar0;                  //此处简化,存放系统调用返回值
	int u_arg[5];				/* 存放当前系统调用参数 */
	char *u_filename;
	char* u_dirp;				/* 系统调用参数(一般用于Pathname)的指针 */

	/* 文件系统相关成员 */
	Inode* u_cdir;		/* 指向当前目录的Inode指针 */
	Inode* u_pdir;		/* 指向父目录的Inode指针 */

	DirectoryEntry u_dent;					/* 当前目录的目录项 */
	char u_dbuf[DirectoryEntry::DIRSIZ];	/* 当前路径分量 */
	char u_curdir[128];						/* 当前工作目录完整路径 */

	ErrorCode u_error;			/* 存放错误码 */
	// int u_segflg;				/* 表明I/O针对用户或系统空间 */

	// /* 进程的用户标识 */
	// short u_uid;		/* 有效用户ID */
	// short u_gid;		/* 有效组ID */
	// short u_ruid;		/* 真实用户ID */
	// short u_rgid;		/* 真实组ID */
	
	/* 文件系统相关成员 */
	OpenFiles u_ofiles;		/* 进程打开文件描述符表对象 */

	/* 文件I/O操作 */
	IOParameter u_IOParam;	/* 记录当前读、写文件的偏移量，用户目标区域和剩余字节数参数 */

};
