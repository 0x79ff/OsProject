#include"Kernel.h"
#include"User.h"
#include"FileManager.h"

#include <stdio.h>
#include <string.h>

//不考虑多用户

void InitSystem()
{
	    printf("Initialize System...\n");
	    Kernel::Instance().Initialize();     	// 1、初始化文件系统内核

	    FileManager *fileManager = &Kernel::Instance().GetFileManager();
	    fileManager->rootDirInode = g_InodeTable.IGet(FileSystem::ROOTINO);    // 2、加载根目录DiskInode

	    Kernel::Instance().GetFileSystem().LoadSuperBlock();   	// 3、加载超级块

	    User *u = &Kernel::Instance().GetUser();   	    		// 4、初始化user结构
	    u->u_cdir = g_InodeTable.IGet(FileSystem::ROOTINO);    	// 当前工作目录，根目录
	    strcpy(u->u_curdir, "/");

	    printf("Done.\n");
}

void HelpMenu()
{
    printf("1.ls\n");;
    printf("\t Usage:ls\n");
    printf("\t Description:Display a list of files in the current directory\n");
    
    printf("2.fopen\n");;
    printf("\t Usage:fopen [name]\n");
    printf("\t Description:Open a file named 'name'\n");
    
    printf("3.fclose\n");;
    printf("\t Usage:fclose [fd]\n");
    printf("\t Description:Close files with file descriptor 'fd'\n");
    
    printf("4.fread\n");;
    printf("\t Usage:fread [fd] [length]\n");
    printf("\t Description:Read length bytes from the file descriptor 'fd' and output them to the screen\n");
    
    printf("5.fwrite\n");;
    printf("\t Usage:fwrite [fd] [string]\n");
    printf("\t Description:Write the string to a 'file' with file descriptor 'fd'\n");
    
    printf("6.flseek\n");;
    printf("\t Usage:flseek [fd] [offset]\n");
    printf("\t Description:Move the pointer of the file descriptor 'fd' to 'offset'\n");

    printf("7.fcreate\n");;
    printf("\t Usage:fcreate [name]\n");
    printf("\t Description:Create a regular file named 'name'\n");
    
    printf("8.mkdir\n");;
    printf("\t Usage:mkdir [name]\n");
    printf("\t Description:Create a directory file named 'name'\n");
    
    printf("9.fdelete\n");;
    printf("\t Usage:fdelete [name]\n");
    printf("\t Description:Delete file named 'name'\n");
    
    printf("10.cd\n");;
    printf("\t Usage:cd [name]\n");
    printf("\t Description:Change the current working directory of the file system session to 'name'\n");
    
    printf("11.fin\n");;
    printf("\t Usage:fin [extername] [intername]\n");
    printf("\t Description:Store an external file named 'extername' into the SecondaryFS, and an internal file named 'intername' \n");

    printf("12.fout\n");;
    printf("\t Usage:fout [intername] [extername]\n");
    printf("\t Description:Write an internal file named 'intername' to an external file named 'extername'\n");

    printf("13.shutdown\n");;
    printf("\t Usage:shutdown\n");
    printf("\t Description:Safely shut down the SecondaryFS. Write dirty cache back to mirror file\n");

    printf("14.exit\n");
    printf("\t Usage:exit. Do not use. System will crash!\n");
    printf("\t Description:Close the program SecondaryFS. Equivalent to power outage, file system will lose data\n");

    printf("15.help\n");;
    printf("\t Usage:help\n");
    printf("\t Description:Get Help Menu\n");

}

// function declaration
void Ls();
void Fopen(char *name,int mode);
void Fclose(int fd);
void Fread(int fd, char *buffer, int length);
void Fwrite(int fd, char *buffer, int length);
void Flseek(int fd,int position,int mode);
void Fcreate(char* name,int mode);
void Mkdir(char* name);
void Fdelete(char *name);
void Cd(char *name);
void Fin(char *extername, char* intername);
void Fout(char* intername,char *extername);
void Fshutdown();

// 1 - Ls
void Ls()
{
    User *u = &Kernel::Instance().GetUser();
    u->u_ar0 = 0;
    Fopen(u->u_curdir, File::FREAD);
    int fd = u->u_ar0;
    //printf("Debugxxx fd:%d\n",fd);
    char buffer[32] = {0};
    //printf("%p",(void *)(buffer));
    while (1)
    {
        Fread(fd, buffer, 32);
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
    Fclose(fd);
}

// 2 - Fopen
void Fopen(char *name,int mode)
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
void Fclose(int fd)
{
    User *u = &Kernel::Instance().GetUser();
	u->u_ar0 = 0;
	u->u_arg[0] = fd;
	FileManager *fileManager = &Kernel::Instance().GetFileManager();
	fileManager->Close();
    return;
}

//4 - fread
void Fread(int fd, char *buffer, int length)
{
        //printf("Fun:fread\n");
	User *u = &Kernel::Instance().GetUser();
	u->u_ar0 = 0;
	u->u_arg[0] = fd;
    //u->u_filename = buffer;
	u->u_arg[1] = (int)(buffer);
	u->u_arg[2] = length;
	FileManager *fileManager = &Kernel::Instance().GetFileManager();
	fileManager->Read();
	return;
}


//5 - fwrite
void Fwrite(int fd, char *buffer, int length)
{

	User *u = &Kernel::Instance().GetUser();
	u->u_ar0 = 0;
	u->u_arg[0] = fd;
    //u->u_filename = buffer;
	u->u_arg[1] = (int)(buffer);
	u->u_arg[2] = length;
	FileManager *fileManager = &Kernel::Instance().GetFileManager();
	fileManager->Write();
	return ;
}

//6 - flseek 
void Flseek(int fd,int position,int mode)
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
void Fcreate(char* name,int mode)
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
void Mkdir(char* name)
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
void Fdelete(char *name)
{
    User *u = &Kernel::Instance().GetUser();
	u->u_ar0 = 0;
	u->u_dirp = name;
	FileManager *fileManager = &Kernel::Instance().GetFileManager();
	fileManager->UnLink();
}

//10 - cd
void Cd(char *name)
{
    User *u = &Kernel::Instance().GetUser();
	u->u_ar0 = 0;
	u->u_dirp = name;
	//u->u_filename = name;
    u->u_arg[0] = (int)(name);
	//printf("%s\n", (char *)u->u_arg[0]);
	FileManager *fileManager = &Kernel::Instance().GetFileManager();
	fileManager->ChDir();
}

//11 - fin
void Fin(char *extername, char* intername)
{
    User *u = &Kernel::Instance().GetUser();
	char buffer[4096] = {0};
    
	FILE *fp = fopen(extername, "rb");
    if(fp==NULL){
        printf("%s not exist!\n",extername);
        return;
    }
    int mode = 7|(7<<3)|(7<<6);
	Fcreate(intername, mode);
    int fd = u->u_ar0;

	int num = fread(buffer, 1, 4096, fp);
	while (num > 0)
	{
	    Fwrite(fd, buffer, num);
		num = fread(buffer, 1, 4096, fp);
	}
    if(fp!=NULL)
	    fclose(fp);
	Fclose(fd);
}

//12 - fout
void Fout(char* intername,char *extername)
{
    User *u = &Kernel::Instance().GetUser();
    int mode = File::FREAD | File::FWRITE;
	Fopen(intername, mode);
    if(u->u_error != User::MYNOERROR){
        printf("%s not exist!\n",intername);
        return;//打开文件失败
    }
    
    int fd = u->u_ar0;
	char buffer[4096] = {0};
	FILE *fp = fopen(extername, "wb");
    int num;
	Fread(fd, buffer, 4096);
	num = u->u_ar0;
    while (num > 0)
	{
		fwrite(buffer, 1, num, fp);
		Fread(fd, buffer, 4096);
        num=u->u_ar0;
	}
	if(fp!=NULL)
        fclose(fp);
    Fclose(fd);
}

//13 - shutdown
void Fshutdown()
{
    FileSystem *fileSystem = &Kernel::Instance().GetFileSystem();
    fileSystem->Update();
}

int main()
{
    //初始化一下
	InitSystem();
	User *u = &Kernel::Instance().GetUser();

    printf("welcome to my SecondFileSystem! Input 'help' to get more info!\n");

    while(1){
		printf("[%s]# ", u->u_curdir);
		u->u_error = User::MYNOERROR;

        char op[50];
        scanf("%s",op);
        
        //1 - ls
        if(strcmp(op,"ls")==0){
            Ls();
            continue;
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

            continue;
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

            continue;
        }
        
        //4 - fread
        if(strcmp(op,"fread")==0){
            int fd;
			char buffer[4096] = {0};
			int length;
			scanf("%d", &fd);
			scanf("%d", &length);
			Fread(fd, buffer, length);
			printf("fread %d chars: %s\n", u->u_ar0, buffer);

			continue;
        }

        //5 - fwrite
        if(strcmp(op,"fwrite")==0){
            int fd;
			char buffer[4096] = {0};
			scanf("%d", &fd);
			scanf("%s", buffer);
            Fwrite(fd, buffer, strlen(buffer));
			printf("fwrite: write %d chars\n", u->u_ar0);

			continue;
        }

        //6 - flseek 
        if(strcmp(op,"flseek")==0){
            int fd;
			int pos;
			int mode = 0;
			scanf("%d", &fd);
			scanf("%d", &pos);
			Flseek(fd, pos, mode);

			continue;
        }

        //7 - fcreate
        if(strcmp(op,"fcreate")==0){
            char name[50];
			int mode = 7 | (7<<3)|(7<<6); //文件类型为普通数据文件00
			scanf("%s", name);
            Fcreate(name,mode);
			printf("fcreat: return fd:%d\n", u->u_ar0);

			continue;
        }

        //8 - mkdir
        if(strcmp(op,"mkdir")==0){
            char name[50];
			scanf("%s", name);
			Mkdir(name);

			continue;
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

			continue;
        }

        //10 - cd
        if(strcmp(op,"cd")==0){
            char name[50];
			scanf("%s", name);
			Cd(name);
            if (u->u_error != User::MYNOERROR)
				printf("cd: error!\n");

			continue;
        }
        //11 - fin
        if(strcmp(op,"fin")==0){
            char intername[50];
			char extername[50];
			scanf("%s", extername);
			scanf("%s", intername);
			Fin(extername, intername);

			continue;
        }

        //12 - fout
        if(strcmp(op,"fout")==0){
            char intername[50];
			char extername[50];
			scanf("%s", intername);
			scanf("%s", extername);
			Fout(intername,extername);

			continue;
        }

        //13 - shutdown 必需安全关机
        if(strcmp(op,"shutdown")==0){
        	Fshutdown();
            break;
        }

        //14 - exit
        if(strcmp(op,"exit")==0){
        	printf("Try command ----- shutdown ----- please! \n");
			continue;
        }

        //15 - help
        if(strcmp(op,"help")==0){
            HelpMenu();
			continue;
        }
        
		printf("Bad Command! Try command ----- help ----- please! \n");
		char abort = 'a';
		while( abort != '\n' )
	        scanf("%c", &abort);
    }
    
    return 0;
}
