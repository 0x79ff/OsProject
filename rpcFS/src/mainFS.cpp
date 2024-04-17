#include"Kernel.h"
#include"User.h"
#include"FileManager.h"

#include "mainFS.h"
#include <stdio.h>
#include <string.h>

//不考虑多用户

void myfs_InitSystem()
{
    printf("Initialize System...\n");
    Kernel::Instance().Initialize();
    FileManager *fileManager = &Kernel::Instance().GetFileManager();
    fileManager->rootDirInode = g_InodeTable.IGet(FileSystem::ROOTINO);
    Kernel::Instance().GetFileSystem().LoadSuperBlock();
    User *u = &Kernel::Instance().GetUser();
    u->u_error = User::MYNOERROR;
    u->u_cdir = g_InodeTable.IGet(FileSystem::ROOTINO);
    u->u_pdir = NULL;
    strcpy(u->u_curdir, "/");
    u->u_dirp = (char*)("/");
    memset(u->u_arg, 0, sizeof(u->u_arg));
    printf("Done.\n");
}


//declear
void myfs_Ls();
void myfs_Fopen(char *name,int mode);
void myfs_Fclose(int fd);
void myfs_Fread(int fd, char *buffer, int length);
void myfs_Fwrite(int fd, char *buffer, int length);
void myfs_Flseek(int fd,int position,int mode);
void myfs_Fcreate(char* name,int mode);
void myfs_Mkdir(char* name);
void myfs_Fdelete(char *name);
void myfs_Cd(char *name);
void myfs_Fin(char *extername, char* intername);
void myfs_Fout(char* intername,char *extername);



// 1 - Ls
void myfs_Ls()
{
    User *u = &Kernel::Instance().GetUser();
    u->u_ar0 = 0;
    myfs_Fopen(u->u_curdir, File::FREAD);
    int fd = u->u_ar0;
    //printf("Debugxxx fd:%d\n",fd);
    char buffer[32] = {0};
    //printf("%p",(void *)(buffer));
    while (1)
    {
        myfs_Fread(fd, buffer, 32);
	//printf("Fread end\n");
        if (u->u_ar0 == 0)
            break;
        else
        {
            DirectoryEntry *de = (DirectoryEntry *)buffer;
            if (de->m_ino == 0)
                continue;
            if(strcmp(de->m_name,"..")==0 || strcmp(de->m_name,".")==0){
                continue;
            }
            printf("%s ", de->m_name);
            memset(buffer, 0, 32);
        }
    }
    printf("\n");
    myfs_Fclose(fd);
}

// 2 - Fopen
void myfs_Fopen(char *name,int mode)
{
	User *u = &Kernel::Instance().GetUser();
	u->u_ar0 = 0;
	u->u_dirp = name;
	u->u_arg[1] = mode;
	FileManager *fileManager = &Kernel::Instance().GetFileManager();
	fileManager->Open();
	return;
}

// 3 - Fclose
void myfs_Fclose(int fd)
{
    User *u = &Kernel::Instance().GetUser();
	u->u_ar0 = 0;
	u->u_arg[0] = fd;
	FileManager *fileManager = &Kernel::Instance().GetFileManager();
	fileManager->Close();
    return;
}

//4 - fread
void myfs_Fread(int fd, char *buffer, int length)
{
        //printf("Fun:fread\n");
	User *u = &Kernel::Instance().GetUser();
	u->u_ar0 = 0;
	u->u_arg[0] = fd;
    u->u_filename = buffer;
	//u->u_arg[1] = (int)(buffer);
	u->u_arg[2] = length;
	FileManager *fileManager = &Kernel::Instance().GetFileManager();
	fileManager->Read();
	return;
}


//5 - fwrite
void myfs_Fwrite(int fd, char *buffer, int length)
{

	User *u = &Kernel::Instance().GetUser();
	u->u_ar0 = 0;
	u->u_arg[0] = fd;
        u->u_filename = buffer;
	//u->u_arg[1] = (int)(buffer);
	u->u_arg[2] = length;
	FileManager *fileManager = &Kernel::Instance().GetFileManager();
	fileManager->Write();
	return ;
}

//6 - flseek 
void myfs_Flseek(int fd,int position,int mode)
{
    User *u = &Kernel::Instance().GetUser();
	u->u_ar0 = 0;
	u->u_arg[0] = fd;
	u->u_arg[1] = position;
	u->u_arg[2] = mode;
	FileManager *fileManager = &Kernel::Instance().GetFileManager();
	fileManager->Seek();
	return ;
}
//7 - fcreate
void myfs_Fcreate(char* name,int mode)
{
    User *u = &Kernel::Instance().GetUser();
	u->u_ar0 = 0;
	u->u_dirp = name;
	u->u_arg[1] = mode;
	FileManager *fileManager = &Kernel::Instance().GetFileManager();
	fileManager->Creat();
	return;
}

//8 - mkdir
void myfs_Mkdir(char* name)
{
    User *u = &Kernel::Instance().GetUser();
	u->u_ar0 = 0;
	int mode = 040755;
	u->u_dirp = name;
	u->u_arg[1] = mode;
	u->u_arg[2] = 0;
	FileManager *fileManager = &Kernel::Instance().GetFileManager();
	fileManager->MkNod();
}

//9 - fdelete
void myfs_Fdelete(char *name)
{
    User *u = &Kernel::Instance().GetUser();
	u->u_ar0 = 0;
	u->u_dirp = name;
	FileManager *fileManager = &Kernel::Instance().GetFileManager();
	fileManager->UnLink();
}

//10 - cd
void myfs_Cd(char *name)
{
    User *u = &Kernel::Instance().GetUser();
	u->u_ar0 = 0;
	u->u_dirp = name;
	u->u_filename = name;
    //u->u_arg[0] = (int)(name);
	//printf("%s\n", (char *)u->u_arg[0]);
	FileManager *fileManager = &Kernel::Instance().GetFileManager();
	fileManager->ChDir();
}

//11 - fin
void myfs_Fin(char *extername, char* intername)
{
    User *u = &Kernel::Instance().GetUser();
	char buffer[1024] = {0};
   
	FILE *fp = fopen(extername, "rb");
    if(fp==NULL){
        printf("%s not exist!\n",extername);
        return;
    }
    int mode = 7|(7<<3)|(7<<6);
	myfs_Fcreate(intername, mode);
    int fd = u->u_ar0;
	int num = fread(buffer, 1, 1024, fp);
	while (num > 0)
	{
	    myfs_Fwrite(fd, buffer, num);
		num = fread(buffer, 1, 1024, fp);
	}
    if(fp!=NULL)
	    fclose(fp);
	myfs_Fclose(fd);
}

//12 - fout
void myfs_Fout(char* intername,char *extername)
{
    User *u = &Kernel::Instance().GetUser();
    int mode = File::FREAD | File::FWRITE;
	myfs_Fopen(intername, mode);
    if(u->u_error != User::MYNOERROR){
        printf("%s not exist!\n",intername);
        return;//打开文件失败
    }
    
    int fd = u->u_ar0;
	char buffer[1024] = {0};
	FILE *fp = fopen(extername, "wb");
    int num;
	myfs_Fread(fd, buffer, 1024);
	num = u->u_ar0;
    while (num > 0)
	{
		fwrite(buffer, 1, num, fp);
		myfs_Fread(fd, buffer, 1024);
        num=u->u_ar0;
	}
	if(fp!=NULL)
        fclose(fp);
    myfs_Fclose(fd);
}

/*
int main()
{
    //初始化一下
	InitSystem();
	User *u = &Kernel::Instance().GetUser();

    printf("welcome to me SecondFileSystem! Input 'help' to get more imformation!\n");

    while(1){
		printf("[%s]# ", u->u_curdir);
		u->u_error = User::MYNOERROR;

        char op[50];
        scanf("%s",op);
        
        //1 - ls
        if(strcmp(op,"ls")==0){
            Ls();
        }
        
        //2 - fopen
        if(strcmp(op,"fopen")==0){
            char name[50];
			int mode = File::FREAD | File::FWRITE;
			scanf("%s", name);
			Fopen(name, mode);
            
			if (u->u_error != User::MYNOERROR)
				printf("fopen: error!\n");
			else
				printf("fopen: return fd:%d\n", u->u_ar0);
        }
        
        //3 - fclose
        if(strcmp(op,"fclose")==0){
            int fd;
			scanf("%d", &fd);
			Fclose(fd);
            if (u->u_error != User::MYNOERROR)
				printf("fclose: error!\n");
			else
				printf("fclose: fd:%d is closed.\n", u->u_ar0);
        }
        
        //4 - fread
        if(strcmp(op,"fread")==0){
            int fd;
			char buffer[1024] = {0};
			int length;
			scanf("%d", &fd);
			scanf("%d", &length);
			Fread(fd, buffer, length);
			printf("fread:%s\n", buffer);
        }
        //5 - fwrite
        if(strcmp(op,"fwrite")==0){
            int fd;
			char buffer[1024] = {0};
			scanf("%d", &fd);
			scanf("%s", buffer);
            Fwrite(fd, buffer, strlen(buffer));
			printf("fwrite: write %d chars\n", u->u_ar0);
        }
        //6 - flseek 
        if(strcmp(op,"flseek")==0){
            int fd;
			int pos;
			int mode = 0;
			scanf("%d", &fd);
			scanf("%d", &pos);
			Flseek(fd, pos, mode);
        }
        //7 - fcreate
        if(strcmp(op,"fcreate")==0){
            char name[50];
			int mode = 7 | (7<<3)|(7<<6); //文件类型为普通数据文件00
			scanf("%s", name);
            Fcreate(name,mode);
			printf("fcreat: return fd:%d\n", u->u_ar0);
        }
        //8 - mkdir
        if(strcmp(op,"mkdir")==0){
            char name[50];
			scanf("%s", name);
			Mkdir(name);
        }
        //9 - fdelete
        if(strcmp(op,"fdelete")==0){
            char name[50];
			scanf("%s", name);
			Fdelete(name);
            if (u->u_error != User::MYNOERROR)
				printf("fdelete: error!\n");
			else
				printf("fdelete: success.\n", u->u_ar0);
        }
        //10 - cd
        if(strcmp(op,"cd")==0){
            char name[50];
			scanf("%s", name);
			Cd(name);
            if (u->u_error != User::MYNOERROR)
				printf("cd: error!\n");
        }
        //11 - fin
        if(strcmp(op,"fin")==0){
            char intername[50];
			char extername[50];
			scanf("%s", extername);
			scanf("%s", intername);
			Fin(extername, intername);
        }
        //12 - fout
        if(strcmp(op,"fout")==0){
            char intername[50];
			char extername[50];
			scanf("%s", intername);
			scanf("%s", extername);
			Fout(intername,extername);
        }
        //13 - shutdown
        if(strcmp(op,"shutdown")==0){
            FileSystem *fileSystem = &Kernel::Instance().GetFileSystem();
            fileSystem->Update();
            break;
        }
        //14 - exit
        if(strcmp(op,"exit")==0){
            break;
        }
        //15 - help
        if(strcmp(op,"help")==0){
            HelpMenu();
        }
        
    }
    
    return 0;
}*/
