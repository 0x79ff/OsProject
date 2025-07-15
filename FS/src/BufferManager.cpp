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

void BufferManager::NotAvail(Buf *bp)	// 摘除缓存块bp
{
    bp->av_back->av_forw = bp->av_forw;
    bp->av_forw->av_back = bp->av_back;
	return;
}

void BufferManager::Avail(Buf *bp)		// 缓存块bp解锁、插队尾
{
	bp->b_flags &= ~Buf::B_BUSY;
    bp->av_back = this->bFreeList.av_back;
    this->bFreeList.av_back->av_forw = bp;
    bp->av_forw = &this->bFreeList;
    this->bFreeList.av_back = bp;
	return;
}
	
void BufferManager::Initialize()
{
	/* 缓存控制块队列的初始化。将缓存控制块中b_addr指向相应缓冲区首地址。*/

	int i;
	Buf* bp;

	this->bFreeList.av_forw = this->bFreeList.av_back = &(this->bFreeList);

	for(i = 0; i < NBUF; i++)
	{
		bp = &(this->m_Buf[i]);
		bp->b_addr = this->Buffer[i];
		Avail(bp);
	}

	this->m_DiskDriver = &Kernel::Instance().GetDiskDriver();
	return;
}

Buf* BufferManager::GetBlk(int blkno) // LRU队列完全由GetBlk维护：将数据块blkno从队列摘除，送队尾
{
    /* 申请一块缓存，用于读写设备dev上的字符块blkno。*/
    Buf* bp;
	Buf* dp = &(this->bFreeList);

	/*先在队列中找*/
	for(bp=dp->av_forw;bp!=dp;bp=bp->av_forw){
		if(bp->b_blkno != blkno){
			continue;
		}
		bp->b_flags |= Buf::B_BUSY;
		NotAvail(bp);
		Avail(bp);
		return bp;
	}

	/*取自由缓存队列中第一个空闲块*/
	bp=this->bFreeList.av_forw;
	
	if(bp->b_flags & Buf::B_DELWRI){
		this->Bwrite(bp);
	}

	bp->b_flags = Buf::B_BUSY;
	bp->b_blkno = blkno;

	NotAvail(bp);
	Avail(bp);

    return bp;
}
    

void BufferManager::Brelse(Buf* bp)
{
	bp->b_flags &= ~(Buf::B_WANTED | Buf::B_BUSY | Buf::B_ASYNC);		
	return;
}	

Buf* BufferManager::Bread(int blkno)
{
	Buf* bp;
	/* 根据字符块号申请缓存 */
	bp = this->GetBlk(blkno);
	/* 如果在设备队列中找到所需缓存，即B_DONE已设置，就不需进行I/O操作 */
	if(bp->b_flags & Buf::B_DONE)
	{
		return bp;
	}
	/* 没有找到相应缓存，构成I/O读请求块 */
	bp->b_flags |= Buf::B_READ;
	bp->b_wcount = BufferManager::BUFFER_SIZE;
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
	return;
}


void BufferManager::Bdwrite(Buf* bp)
{
    /* 延迟写磁盘块 */
    /* 置上B_DONE允许其它进程使用该磁盘块内容 */
	bp->b_flags |= (Buf::B_DELWRI | Buf::B_DONE);
	bp->b_wcount = BufferManager::BUFFER_SIZE;
	this->Brelse(bp);
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