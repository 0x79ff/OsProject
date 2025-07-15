#pragma once

#include "File.h"
#include "Inode.h"
#include "FileManager.h"

class User
{
public:
	enum ErrorCode	// 0~32来自Linux。 避免与系统冲突，加前缀 MY
	{
		MYNOERROR	= 0,	/* No error */
		MYEPERM		= 1,	/* Operation not permitted */
		MYENOENT	= 2,	/* No such file or directory */
		MYESRCH		= 3,	/* No such process */
		MYEINTR		= 4,	/* Interrupted system call */
		MYEIO		= 5,	/* I/O error */
		MYENXIO		= 6,	/* No such device or address */
		MYE2BIG		= 7,	/* Arg list too long */
		MYENOEXEC	= 8,	/* Exec format error */
		MYEBADF		= 9,	/* Bad file number */
		MYECHILD	= 10,	/* No child processes */
		MYEAGAIN	= 11,	/* Try again */
		MYENOMEM	= 12,	/* Out of memory */
		MYEACCES	= 13,	/* Permission denied */
		MYEFAULT  	= 14,	/* Bad address */
		MYENOTBLK	= 15,	/* Block device required */
		MYEBUSY 	= 16,	/* Device or resource busy */
		MYEEXIST	= 17,	/* File exists */
		MYEXDEV		= 18,	/* Cross-device link */
		MYENODEV	= 19,	/* No such device */
		MYENOTDIR	= 20,	/* Not a directory */
		MYEISDIR	= 21,	/* Is a directory */
		MYEINVAL	= 22,	/* Invalid argument */
		MYENFILE	= 23,	/* File table overflow */
		MYEMFILE	= 24,	/* Too many open files */
		MYENOTTY	= 25,	/* Not a typewriter(terminal) */
		MYETXTBSY	= 26,	/* Text file busy */
		MYEFBIG		= 27,	/* File too large */
		MYENOSPC	= 28,	/* No space left on device */
		MYESPIPE	= 29,	/* Illegal seek */
		MYEROFS		= 30,	/* Read-only file system */
		MYEMLINK	= 31,	/* Too many links */
		MYEPIPE		= 32,	/* Broken pipe */
		MYENOSYS	= 100,
		//MYEFAULT	= 106
	};

public:
    OpenFiles 	u_ofiles;     		// 打开文件表

    char 		u_curdir[128];   	// 当前工作目录，绝对路径名（字符串）
    Inode* 		u_cdir;				// 		内存Inode
    Inode* 		u_pdir;				// 		父目录的内存Inode

    int 		u_arg[5];			// 命令参数
    int 		u_ar0;     			//     	返回值
    ErrorCode 	u_error;      		//    	出错码
    char* 		u_dirp;				//     	命令 Fopen,Fcreate,Mkdir,Fdelete,Cd 的路径名

    IOParameter u_IOParam;      	// IO参数

    // 线性目录搜索。当前目录文件，遍历目录项，匹配当前文件名分量
    DirectoryEntry 	u_dent;   							// 当前目录项
    char 			u_dbuf[DirectoryEntry::DIRSIZ];    // 文件名分量

     // short u_uid;	  // 单用户系统，暂不需要
     // short u_gid;
     // short u_ruid;
     // short u_rgid;
};

