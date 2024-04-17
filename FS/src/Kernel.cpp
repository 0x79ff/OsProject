#include "Kernel.h"

Kernel Kernel::instance;

/*
 * 设备管理、高速缓存管理全局manager
 */
BufferManager g_BufferManager;

/*
 * 文件系统相关全局manager
 */
FileSystem g_FileSystem;
FileManager g_FileManager;

/**/
DiskDriver g_DiskDriver;

/**/
User g_User;


Kernel::Kernel()
{
}

Kernel::~Kernel()
{
}


Kernel& Kernel::Instance()
{
	return Kernel::instance;
}

/**/
void Kernel::InitDiskDriver()
{
	this->m_DiskDriver = &g_DiskDriver;
    //不用了 磁盘已经格式化了
    //this->GetDiskDriver().Initialize();
}


void Kernel::InitBuffer()
{
	this->m_BufferManager = &g_BufferManager;
	this->GetBufferManager().Initialize();

}

void Kernel::InitFileSystem()
{
	this->m_FileSystem = &g_FileSystem;
	this->m_FileManager = &g_FileManager;

	this->GetFileSystem().Initialize();
	this->GetFileManager().Initialize();
}

void Kernel::InitUser()
{
	this->m_User = &g_User;
	/*初始化User操作 如下*/
	//TBD
}

void Kernel::Initialize()
{
    InitDiskDriver();
	InitBuffer();
	InitFileSystem();
	InitUser();
}
/**/

BufferManager& Kernel::GetBufferManager()
{
	return *(this->m_BufferManager);
}

DiskDriver& Kernel::GetDiskDriver()
{
	return *(this->m_DiskDriver);
}

FileSystem& Kernel::GetFileSystem()
{
	return *(this->m_FileSystem);
}

FileManager& Kernel::GetFileManager()
{
	return *(this->m_FileManager);
}

User& Kernel::GetUser()
{
	return *(this->m_User);
}
