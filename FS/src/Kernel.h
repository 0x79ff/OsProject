#pragma once

#include "User.h"
#include "BufferManager.h"
#include "FileManager.h"
#include "FileSystem.h"

class Kernel
{
public:
	Kernel();
	~Kernel();
	static Kernel& Instance();
	void Initialize();

	BufferManager& 	GetBufferManager();
	FileSystem& 	GetFileSystem();
	FileManager& 	GetFileManager();
    DiskDriver& 	GetDiskDriver();
	User& 			GetUser();

private:
	void InitDiskDriver();
	void InitBuffer();
	void InitFileSystem();
	void InitUser();

private:
	static Kernel instance;		/* Kernel单体类实例 */

    BufferManager 	*m_BufferManager;
    FileSystem 		*m_FileSystem;
    FileManager 	*m_FileManager;
    DiskDriver 		*m_DiskDriver;
    User 			*m_User;
};
