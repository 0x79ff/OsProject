#include "BufferManager.h"
#include "Kernel.h"
#include "Buf.h"

BufferManager::BufferManager()
{
    //nothing to do
}

BufferManager::~BufferManager()
{
    //nothing to do
}
	
void BufferManager::Initialize()
{
	/* 缓存控制块队列的初始化。将缓存控制块中b_addr指向相应缓冲区首地址。*/

	int i;
	Buf* bp;

	this->bFreeList.b_forw = this->bFreeList.b_back = &(this->bFreeList);
    //this->bFreeList.av_forw = this->bFreeList.av_back = &(this->bFreeList);

	for(i = 0; i < NBUF; i++)
	{
		bp = &(this->m_Buf[i]);
		bp->b_addr = this->Buffer[i];
		/* 初始化队列 */
		bp->b_back = &(this->bFreeList);
		bp->b_forw = this->bFreeList.b_forw;
		this->bFreeList.b_forw->b_back = bp;
		this->bFreeList.b_forw = bp;
		bp->b_flags = Buf::B_BUSY;
		Brelse(bp);
	}

	this->m_DiskDriver = &Kernel::Instance().GetDiskDriver();
	return;
}

Buf* BufferManager::GetBlk(int blkno)//这几个函数有点乱 好好学一下BUF再看看
{
    /* 申请一块缓存，用于读写设备dev上的字符块blkno。*/
    Buf* bp;
	Buf* dp = &(this->bFreeList);

	/*先在队列中找*/
	for(bp=dp->b_forw;bp!=dp;bp=bp->b_forw){
		if(bp->b_blkno != blkno){
			continue;
		}
		bp->b_flags |= Buf::B_BUSY;
		return bp;
	}

	/*取自由缓存队列中第一个空闲块*/
	bp=this->bFreeList.b_forw;
	
	if(bp->b_flags & Buf::B_DELWRI){
		this->Bwrite(bp);
	}

	bp->b_flags = Buf::B_BUSY;


    /*把bp从头部拿出来放到尾部*/
    bp->b_back->b_forw = bp->b_forw;
    bp->b_forw->b_back = bp->b_back;

    bp->b_back = this->bFreeList.b_back;
    this->bFreeList.b_back->b_forw = bp;
    bp->b_forw = &this->bFreeList;
    this->bFreeList.b_back = bp;

    bp->b_blkno = blkno;
    return bp;
}
    

void BufferManager::Brelse(Buf* bp)
{
	/* 注意以下操作并没有清除B_DELWRI、B_WRITE、B_READ、B_DONE标志
	 * B_DELWRI表示虽然将该控制块释放到自由队列里面，但是有可能还没有些到磁盘上。
	 * B_DONE则是指该缓存的内容正确地反映了存储在或应存储在磁盘上的信息 
	 */
	bp->b_flags &= ~(Buf::B_WANTED | Buf::B_BUSY | Buf::B_ASYNC);
		
	//X86Assembly::STI();
	return;
}	

Buf* BufferManager::Bread(int blkno)
{
    /* 读一个磁盘块。dev为主、次设备号，blkno为目标磁盘块逻辑块号。 */
	Buf* bp;
	/* 根据设备号，字符块号申请缓存 */
	bp = this->GetBlk(blkno);
	/* 如果在设备队列中找到所需缓存，即B_DONE已设置，就不需进行I/O操作 */
	if(bp->b_flags & Buf::B_DONE)
	{
		return bp;
	}
	/* 没有找到相应缓存，构成I/O读请求块 */
	bp->b_flags |= Buf::B_READ;
	bp->b_wcount = BufferManager::BUFFER_SIZE;

	
	/* 
	 * 将I/O请求块送入相应设备I/O请求队列，如无其它I/O请求，则将立即执行本次I/O请求；
	 * 否则等待当前I/O请求执行完毕后，由中断处理程序启动执行此请求。
	 * 注：Strategy()函数将I/O请求块送入设备请求队列后，不等I/O操作执行完毕，就直接返回。
	 */
	//this->m_DeviceManager->GetBlockDevice(Utility::GetMajor(dev)).Strategy(bp);
	/* 同步读，等待I/O操作结束 */
	//this->IOWait(bp);

	//DiskDriver直接读取信息
	this->m_DiskDriver->IO(bp);
	
	return bp;
}

void BufferManager::Bwrite(Buf* bp)
{
    /* 写一个磁盘块 */
    unsigned int flags;

	flags = bp->b_flags;
	bp->b_flags &= ~(Buf::B_READ | Buf::B_DONE | Buf::B_ERROR | Buf::B_DELWRI);//B_WRITE应该就足够了吧..
	bp->b_wcount = BufferManager::BUFFER_SIZE;		/* 512字节 */

	this->m_DiskDriver->IO(bp);
	this->Brelse(bp);

    bp->b_back->b_forw = bp->b_forw;
    bp->b_forw->b_back = bp->b_back;

    bp->b_back = this->bFreeList.b_back;
    this->bFreeList.b_back->b_forw = bp;
    bp->b_forw = &this->bFreeList;
    this->bFreeList.b_back = bp;
	return;
}


void BufferManager::Bdwrite(Buf* bp)
{
    /* 延迟写磁盘块 */
    /* 置上B_DONE允许其它进程使用该磁盘块内容 */
	bp->b_flags |= (Buf::B_DELWRI | Buf::B_DONE);
	bp->b_wcount = BufferManager::BUFFER_SIZE;
	this->Brelse(bp);
	bp->b_back->b_forw = bp->b_forw;
    bp->b_forw->b_back = bp->b_back;

    bp->b_back = this->bFreeList.b_back;
    this->bFreeList.b_back->b_forw = bp;
    bp->b_forw = &this->bFreeList;
    this->bFreeList.b_back = bp;
	return;
}

void BufferManager::ClrBuf(Buf* bp)
{
    /* 清空缓冲区内容 */
    int* pInt = (int *)bp->b_addr;

	/* 将缓冲区中数据清零 */
	for(unsigned int i = 0; i < BufferManager::BUFFER_SIZE / sizeof(int); i++)
	{
		pInt[i] = 0;
	}
	return;
}

void BufferManager::Bflush()
{
    /* 将dev指定设备队列中延迟写的缓存全部输出到磁盘 */
    Buf* bp;

	//X86Assembly::CLI();
	for(unsigned int i = 0; i < NBUF; i++)
	{
		/* 找出自由队列中所有延迟写的块 */
		bp = this->m_Buf+i;
		if( (bp->b_flags & Buf::B_DELWRI) /*&& (dev == DeviceManager::NODEV || dev == bp->b_dev)*/ )
		{
			//bp->b_flags |= Buf::B_ASYNC;
			//this->NotAvail(bp);
			this->Bwrite(bp);
		}
	}
	//X86Assembly::STI();
	return;
}

// Buf& BufferManager::GetBFreeList()
// {
//     /* 获取自由缓存队列控制块Buf对象引用 */
//     return this->bFreeList;
// }