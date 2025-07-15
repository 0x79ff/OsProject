#include"FileSystem.h"
#include "DiskDriver.h"

#include <time.h>

extern SuperBlock mySuperBlock;
extern DiskDriver myDiskDriver;


FileSystem::FileSystem()
{
    superBlock = &mySuperBlock;
    diskDriver = &myDiskDriver;
}


void FileSystem::FormatSuperBlock()
{
    superBlock->s_isize = FileSystem::INODE_ZONE_SIZE;
    superBlock->s_fsize = FileSystem::DATA_ZONE_END_SECTOR + 1;
    
    superBlock->s_nfree = 0;
	superBlock->s_free[0] = -1;
	superBlock->s_ninode = 0;

	superBlock->s_fmod = 0;
    superBlock->s_flock = 0;
    superBlock->s_ilock = 0;
    superBlock->s_ronly = 0;

	time((time_t*)&superBlock->s_time);
}


void FileSystem::Formatting()
{
    FormatSuperBlock();
    diskDriver->write((char *)(superBlock),sizeof(SuperBlock),0);
   
    // 0#
    DiskInode emptyDInode;
    diskDriver->write((char *)(&emptyDInode),sizeof(emptyDInode));

    //root 1#
    DiskInode rootDInode;
    rootDInode.d_mode=0140700;//0B1100000111000000;
    rootDInode.d_nlink=1;
    rootDInode.d_uid=-1;
    rootDInode.d_gid=-1;
    rootDInode.d_size = 7*32;
    rootDInode.d_addr[0] = 1024;
    diskDriver->write((char *)(&rootDInode),sizeof(rootDInode));

    //bin 2#
    DiskInode binDInode;
    binDInode.d_mode=0140700;//0B1100000111000000;
    binDInode.d_nlink=1;
    binDInode.d_uid=-1;
    binDInode.d_gid=-1;
    binDInode.d_size = 2*32;
    binDInode.d_addr[0] = 1025;
    diskDriver->write((char *)(&binDInode),sizeof(binDInode));

    //etc 3#
    DiskInode etcDInode;
    etcDInode.d_mode=0140700;//0B1100000111000000;
    etcDInode.d_nlink=1;
    etcDInode.d_uid=-1;
    etcDInode.d_gid=-1;
    etcDInode.d_size = 2*32;
    etcDInode.d_addr[0] = 1026;
    diskDriver->write((char *)(&etcDInode),sizeof(etcDInode));

    //dev 4#
    DiskInode devDInode;
    devDInode.d_mode=0140700;//0B1100000111000000;
    devDInode.d_nlink=1;
    devDInode.d_uid=-1;
    devDInode.d_gid=-1;
    devDInode.d_size = 3*32;
    devDInode.d_addr[0] = 1027;
    diskDriver->write((char *)(&devDInode),sizeof(devDInode));

    //home 5#
    DiskInode homeDInode;
    homeDInode.d_mode=0140710;//0B1100000111001000;
    homeDInode.d_nlink=1;
    homeDInode.d_uid=-1;
    homeDInode.d_gid=-1;
    homeDInode.d_size = 2*32;
    homeDInode.d_addr[0] = 1028;
    diskDriver->write((char *)(&homeDInode),sizeof(homeDInode));
    
    //shell 6#
    DiskInode shellDInode;
    shellDInode.d_mode=0140710;//0B1100000111001000;
    shellDInode.d_nlink=1;
    shellDInode.d_uid=-1;
    shellDInode.d_gid=-1;
    shellDInode.d_size = 8*BLOCK_SIZE;
    for(int i=0;i<7;i++){
        shellDInode.d_addr[i] = 1029+i;
    }
    //1035为索引块 存128个整数
    diskDriver->write((char *)(&shellDInode),sizeof(shellDInode));
    
    //tty1 7#
    DiskInode tty1Inode;
    tty1Inode.d_mode=0140770;//0B1100000111111000;
    tty1Inode.d_nlink=1;
    tty1Inode.d_uid=-1;
    tty1Inode.d_gid=-1;
    tty1Inode.d_size = 0;
    homeDInode.d_addr[0] = 0;
    diskDriver->write((char *)(&tty1Inode),sizeof(tty1Inode));

    //other DiskInode
    for (int i = 8; i < FileSystem::INODE_NUMBER_ALL; ++i) {
		if (superBlock->s_ninode < 100)
			superBlock->s_inode[superBlock->s_ninode++] = i;
		diskDriver->write((char*)&emptyDInode, sizeof(emptyDInode));
	}
    
    //数据块 
    //1024 root
    DirectoryEntry rootBlock[BLOCK_SIZE/sizeof(DirectoryEntry)];
    rootBlock[0].ino=1;strcpy(rootBlock[0].name,".");
    rootBlock[1].ino=1;strcpy(rootBlock[1].name,"..");
    rootBlock[2].ino=2;strcpy(rootBlock[2].name,"bin");
    rootBlock[3].ino=3;strcpy(rootBlock[3].name,"etc");
    rootBlock[4].ino=4;strcpy(rootBlock[4].name,"dev");
    rootBlock[5].ino=5;strcpy(rootBlock[5].name,"home");
    rootBlock[6].ino=6;strcpy(rootBlock[6].name,"shell");
    diskDriver->write((char*)&rootBlock, sizeof(rootBlock));

    //1025 bin
    DirectoryEntry binBlock[BLOCK_SIZE/sizeof(DirectoryEntry)];
    binBlock[0].ino=2;strcpy(binBlock[0].name,".");
    binBlock[1].ino=1;strcpy(binBlock[1].name,"..");
    diskDriver->write((char*)&binBlock, sizeof(binBlock));

    //1026 etc
    DirectoryEntry etcBlock[BLOCK_SIZE/sizeof(DirectoryEntry)];
    etcBlock[0].ino=3;strcpy(etcBlock[0].name,".");
    etcBlock[1].ino=1;strcpy(etcBlock[1].name,"..");
    diskDriver->write((char*)&etcBlock, sizeof(etcBlock));
     
    //1027 dev
    DirectoryEntry devBlock[BLOCK_SIZE/sizeof(DirectoryEntry)];
    devBlock[0].ino=4;strcpy(devBlock[0].name,".");
    devBlock[1].ino=1;strcpy(devBlock[1].name,"..");
    devBlock[2].ino=7;strcpy(devBlock[2].name,"tty1");
    diskDriver->write((char*)&devBlock, sizeof(devBlock));
    

    //1028 home
    DirectoryEntry homeBlock[BLOCK_SIZE/sizeof(DirectoryEntry)];
    homeBlock[0].ino=5;strcpy(homeBlock[0].name,".");
    homeBlock[1].ino=1;strcpy(homeBlock[1].name,"..");
    diskDriver->write((char*)&homeBlock, sizeof(homeBlock));

    //1029 - 1034
    char emptyBlock[BLOCK_SIZE];
    memset(emptyBlock,0,sizeof(emptyBlock));
    for(int i=1029;i<1035;i++){
        diskDriver->write((char*)&emptyBlock, sizeof(emptyBlock));
    }

    //1035，shell的索引块。那是128个元素的整数数组。
    int IndexBlock[BLOCK_SIZE/sizeof(int)];
    memset(IndexBlock,0,sizeof(IndexBlock));
    IndexBlock[0]=1036;
    IndexBlock[1]=1037;
    diskDriver->write((char*)&IndexBlock, sizeof(IndexBlock));

    //1036 - 1037。shell的2个数据块，留给它；虽然shell程序不存在。
    diskDriver->write((char*)&emptyBlock, sizeof(emptyBlock));
    diskDriver->write((char*)&emptyBlock, sizeof(emptyBlock));

    //1038 - 1999
    for(int i=1038;i<DATA_ZONE_END_SECTOR;i++){
        diskDriver->write((char*)&emptyBlock, sizeof(emptyBlock));
    }

    //------- 行至此，磁盘写操作完成。下面构造空闲盘块号栈：组长块blkno是100的倍数，存放s_nfree数组，倒着收录[blkno+1,blkno+100]区间的数据块--------

    GroupLeaderBlock groupLeaderBlock;
    
    for(int i=DATA_ZONE_END_SECTOR-1;i>=1038;i--){
        if(i%100==0){
            diskDriver->write((char *)(&groupLeaderBlock),sizeof(groupLeaderBlock),i*BLOCK_SIZE);
            memset(&groupLeaderBlock,0,sizeof(groupLeaderBlock));
        }
        groupLeaderBlock.s_free[groupLeaderBlock.s_nfree++] = i;
    }
    

    superBlock->s_nfree=groupLeaderBlock.s_nfree;
    for(int i=0;i<groupLeaderBlock.s_nfree;i++){
        superBlock->s_free[i] = groupLeaderBlock.s_free[i];
    }
    
    
    //重写superBlock
    diskDriver->write((char *)(superBlock),sizeof(SuperBlock),0);
}


