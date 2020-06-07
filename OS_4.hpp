#include <bits/stdc++.h>
#include "OS_4.h"

namespace osBASE
{
	#define PARM_IN  
	#define PARM_OUT  

	void initPAGE( 	PARM_OUT pagetabp &head , 
					PARM_IN const int iniCNT  )
	//初始化页表
	{
		printf("初始化页表开始\n") ;
		char ch ;
		pagetabp q ;
		int timeCNT=0 ;
		for( int i=0 ; i<iniCNT ; ++i )
		{
			pagetabp p=(pagetabp)malloc( sizeof(pagetab_t) ) ;
			if( 0==i )
			{
				head=p ;
				q=p ;
				q->next=nullptr ;
			}
			else
			{
				//尾插法 
				p->next=q->next ;
				q->next=p ;
				q=p ;
				//move
			}
			q->pnum=i ;
			q->isedit=NO ; 
			q->lastuse=0 ;
			printf("第%d页是否在主存中？(y/n)",i) ;
			scanf("%c",&ch) ;
			getchar() ;
			//printf("%d\n",ch) ;
			
			if( 'y'==ch )
			{
				q->isin=YES ;
				printf("第%d页的内存块号:",i) ;
				scanf("%d",&q->blocknum) ;
				getchar() ;
				q->lastuse=timeCNT ;
				++timeCNT ;
			}
			else if( 'n'==ch )
			{
				q->isin=NO ;
				//处于磁盘上的页表对应的页目录项将被标注为不存在。
				printf("第%d页的磁盘位置:",i) ;
				scanf("%d",&q->diskpos) ;
				getchar() ;
			}
			else
			{
				printf("INPUT ERROR!\n"); 
			}
			printf("\n") ;
		}
		return ;
	}
	void iniOPER( 	PARM_OUT operatep &head ,
					PARM_IN const int operCNT )
	//初始化操作指令表 
	{
		operatep q ;
		for( int i=0 ; i<operCNT ; ++i )
		{
			operatep p = (operatep)malloc( sizeof(operate_t) ) ;
			if( 0==i )
			{
				head=p ;
				q=p ;
				q->next=nullptr ;
			}
			else
			{
				p->next=q->next ;
				q->next=p ;
				q=p ;
			}
			
			printf("请输入第%d条指令\n",i ) ;
			scanf("%c %d %d %d %d",&q->opcode,&q->pnum1,&q->padder1,&q->pnum2,&q->padder2) ;
			
			getchar() ;
			printf("operation:%c\n",q->opcode) ;
		}
	}
	bool isINmem( 	PARM_OUT pagetabp &ans ,
					PARM_IN pnum_t num , PARM_IN pagetabp head )
	//根据给定序号判断页面是否在内存并使用p返回 
	{
		pagetabp q=head ;
		while( nullptr!=q )
		{
			if( num==q->pnum )
			{
				ans=q ;
				if( 1==q->isin )
				//存在于磁盘 
				{
					return true ; 
				}else
				{
					return false ;
				}
			}
			q=q->next ;
		}
		printf("num not found!\n") ;
		return false ;
	} 
	void printPAGE( PARM_IN pagetabp head )
	//输出页表
	{
		pagetabp p=head ;
		printf("使用\t页号\t标记\t主存块号\t修改标记\t磁盘位置\n") ;
		while( nullptr!=p )
		{
			if( 1==p->isin )
			{
				printf("%d\t%d\t%d\t%d\t\t%d\n", p->lastuse , p->pnum , p->isin , p->blocknum , p->isedit ) ;
			}
			else
			{
				printf("%d\t%d\t%d\t\t\t%d\t\t%d\n", p->lastuse , p->pnum , p->isin , p->isedit , p->diskpos ) ;
			}
			p=p->next ;
		}
		printf("Print DONE!\n") ;
	} 
	void printODER(	PARM_IN operatep head )
	{
		operatep p=head ;
		while( nullptr!=p )
		{
			printf("%c\n",p->opcode) ;
			p=p->next ;
		}
	}
	#undef PARM_IN
	#undef PARM_OUT
}

namespace algorithm
{
	#define PARM_IN  
	#define PARM_OUT 
	
	void useTIME(	PARM_OUT pagetabp &p , PARM_IN const int lastTIME )
	//设置最近使用时间 
	{
		p->lastuse=lastTIME ;
		return ; 
	} 
	
	void fifoSCH( 	PARM_OUT pagetabp &head ,
					PARM_IN pagetabp p )
	//fifo调度
	//先来先出，由于没有使用额外队列进行维护，所以此代码较为繁琐 
	{ 
		pagetabp q=head ;
		pagetabp pre=head ;
		pagetabp r ;
		pagetabp t ;
		
		printf("换出page:%d\n",head->pnum) ;
		while( nullptr!=pre )
		//找p的前一个节点 
		{
			if( pre->next==p )
				break ;
			else
				pre=pre->next ; 
		}
		if( nullptr==pre )
			printf("页面不存在！\n") ;
		else ;
		
		while( nullptr!=q )
		//寻找最后一个到达内存的节点，并挂载页面p到队尾 
		{
			//printf("%d\n",p->pnum) ;
			if( 1==q->next->isin )
			{
				q=q->next ;
				continue ;
			}
			else ;
			if( q->next!=p )
			//如果已经在最后那么不需要挂载
			//对p尾插，对p->next头插，相当于队列尾部挂载 
			{
				r=q->next ;
				q->next=p ;
				t=p->next ;
				p->next=r ;
				//pre放到挂载页面原本的位置，使用他的next 
				pre->next=t ;
			}
			else ;
			//修改要替换的头节点
			//修改新节点p的信息 
			p->isedit=YES ;
			head->isedit=YES ;
			p->blocknum=head->blocknum ; 
			head->diskpos=p->diskpos ;
			//换出head 
			head->isin=NO ; 
			p->isin=YES ;
			
			//替换头节点 
			//将头节点接到新p之后 
			r=head ; 
			head=head->next ;
			t=p->next ;
			p->next=r ;
			r->next=t ;
			break ;
		}
		osBASE::printPAGE( head ) ;
	}
	
	
	void lruSCH( 	PARM_OUT pagetabp &head , 
					PARM_IN pagetabp p )
	//Lru调度
	//依赖于堆栈以及时间计数器，每次换出距离现在最久未使用的页面 
	{
		pagetabp q=head ;
		pagetabp pre=head ;
		pagetabp r ;
		pagetabp t ;
		
		pagetabp turnPAGE=head ;
		
		int nowTIME=p->lastuse ;
		int ansTIME=0 ; 
		//osBASE::printPAGE( head ) ;
		//寻找最久未使用页面 
		while( nullptr!=q )
		{
			if( ansTIME<( q->lastuse-p->lastuse ) )
			{
				ansTIME=q->lastuse-p->lastuse ;
				turnPAGE=q ;
			}
			q=q->next ;
		}
		printf("最久未使用page:%d\n",turnPAGE->pnum) ;
		
		pagetabp preHEAD=(pagetabp)malloc( sizeof(pagetab_t) ) ;
		preHEAD->next=head ;
		pagetabp cnt=preHEAD ;
		//增加哨兵节点 
		//寻找需要置换页面的前一个节点，并删除 
		//此操作可在上一个流程优化，但是为了可读性与debug，在这里分开处理 
		while( nullptr!=cnt )
		{
			if( cnt->next==turnPAGE || cnt==turnPAGE )
				break ;
			cnt=cnt->next ;
		}
		pagetabp temp=turnPAGE->next ;
		cnt->next=temp ;
		head=preHEAD->next ;
		//osBASE::printPAGE( head ) ;
		
		//寻找需要挂载的页面的前一个页面，断开连接防止循环 
		while( nullptr!=pre )
		{
			if( pre->next==p )
				break ;
			else
				pre=pre->next ;
		}
		
		q=head ;
		while( nullptr!=q )
		//寻找最后一个到达内存的节点，并挂载页面p
		{
			//printf("%d\n",p->pnum) ;
			if( 1==q->next->isin )
			{
				q=q->next ;
				continue ;
			}
			else ;
			if( q->next!=p )
			//如果已经在最后那么不需要挂载
			//对p尾插，对p->next头插，相当于队列尾部挂载 
			{
				r=q->next ;
				q->next=p ;
				t=p->next ;
				p->next=r ;
				//turnPAGE放到挂载页面原本的位置，使用他的next 
				pre->next=t ;
			}
			else ;
			//osBASE::printPAGE( preHEAD->next ) ;
			//修改要替换的头节点
			//修改新节点p的信息 
			p->isedit=YES ;
			turnPAGE->isedit=YES ;
			p->blocknum=turnPAGE->blocknum ; 
			turnPAGE->diskpos=p->diskpos ;
			//换出turnPAGE 
			turnPAGE->isin=NO ; 
			p->isin=YES ;
			
			//替换头节点 
			//将头节点接到新p之后 
			r=turnPAGE ; 
			turnPAGE=turnPAGE->next ;
			t=p->next ;
			//p已经处于尾部，再指向置换出来的页面，也就是置换页面插入到p后 
			p->next=r ;
			r->next=t ;
			break ;
		}
		osBASE::printPAGE( head ) ;
		 
	}
	
	int cntUSE_index(	PARM_IN pagetabp head )
	{
		pagetabp p=head ;
		int cntUSE=0 ;
		while( 0!=p->isin )
		{
			++cntUSE ;
			p=p->next ;
		}
		return cntUSE-1 ;
	}
	
	void opera( 	PARM_IN operatep head , PARM_IN const int choise ,
					PARM_OUT pagetabp &page )
	//根据已有的指令进行操作
	{
		operatep q=head ;
		
		//指向页表 
		pagetabp p_1=nullptr ;
		pagetabp p_2=nullptr ;
		//获取目前有多少被使用的，作为时刻统计 
		int timeCNT=cntUSE_index(page) ;
		++timeCNT ;
		 
		 
		while( nullptr!=q )
		{
			printf("目前时刻%d\n",timeCNT) ;
			bool isin_1=osBASE::isINmem( p_1 , q->pnum1 , page ) ;
			useTIME( p_1 , timeCNT ) ;
			//printf("num1:%d\n",q->pnum1);
			//std::cout<<isin_1<<std::endl ;
			if( FIFO==choise )
			{
				if( !isin_1 )
				//未分配块 
				{
					
					printf("Operate page:%d\n" , p_1->pnum ) ;
					//osBASE::printPAGE(page) ;
					fifoSCH( page , p_1 ) ;
				}
				else 
					printf("Do not need operate page:%d\n", p_1->pnum) ;
			}
			else if( LRU==choise )
			{
				if( !isin_1 )
				{
					printf("Operate page:%d\n" , p_1->pnum ) ;
					lruSCH( page , p_1 ) ;
				}
				else 
					printf("Do not need operate page:%d\n", p_1->pnum) ;
			}else{
				printf("Algorithm ERROR!\n") ;
			}
			++timeCNT ; 
			bool isin_2=osBASE::isINmem( p_2 , q->pnum2 , page ) ;
			useTIME( p_2 , timeCNT ) ;
			//printf("num2:%d\n",q->pnum2);
			if( FIFO==choise )
			{
				if( !isin_2 )
				{
					printf("Operate page:%d\n" , p_2->pnum ) ;
					//osBASE::printPAGE(page) ;
					fifoSCH( page, p_2 ) ;
				}	
				else 
					printf("Do not need operate page:%d\n", p_2->pnum) ;
			}
			else if( LRU==choise )
			{
				if( !isin_2 )
				{
					printf("Operate page:%d\n" , p_2->pnum ) ;
					lruSCH( page , p_2 ) ;
				} 	
				else 
					printf("Do not need operate page:%d\n", p_2->pnum) ;
			}else{
				printf("Algorithm ERROR!\n") ;
			}
			
			printf("逻辑指令：%c %d %d %d %d\n", q->opcode , q->pnum1 , q->padder1 , q->pnum2 , q->padder2 ) ;
			printf("物理指令：%c %d %d %d %d\n", q->opcode , p_1->blocknum ,  p_1->blocknum*1024+q->padder1 , p_2->blocknum , p_2->blocknum*1024+q->padder2 ) ;
			q=q->next ;
			printf("\n") ;
			//osBASE::printODER( q ) ;
			++timeCNT ;
		}
	} 

	#undef PARM_IN
	#undef PARM_OUT
}
