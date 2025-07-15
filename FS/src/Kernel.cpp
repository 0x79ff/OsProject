#include "Kernel.h"

Kernel Kernel::instance;

User 		g_User;
FileManager g_FileManager;
FileSystem 	g_FileSystem;
BufferManager  g_BufferManager;
DiskDriver 	g_DiskDriver;

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

void Kernel::InitDiskDriver()
{
	this->m_DiskDriver = &g_DiskDriver;
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
}

void Kernel::Initialize()
{
    InitDiskDriver();
	InitBuffer();
	InitFileSystem();
	InitUser();
}

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
