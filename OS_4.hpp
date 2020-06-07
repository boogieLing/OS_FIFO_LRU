#include <bits/stdc++.h>
#include "OS_4.h"

namespace osBASE
{
	#define PARM_IN  
	#define PARM_OUT  

	void initPAGE( 	PARM_OUT pagetabp &head , 
					PARM_IN const int iniCNT  )
	//��ʼ��ҳ��
	{
		printf("��ʼ��ҳ��ʼ\n") ;
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
				//β�巨 
				p->next=q->next ;
				q->next=p ;
				q=p ;
				//move
			}
			q->pnum=i ;
			q->isedit=NO ; 
			q->lastuse=0 ;
			printf("��%dҳ�Ƿ��������У�(y/n)",i) ;
			scanf("%c",&ch) ;
			getchar() ;
			//printf("%d\n",ch) ;
			
			if( 'y'==ch )
			{
				q->isin=YES ;
				printf("��%dҳ���ڴ���:",i) ;
				scanf("%d",&q->blocknum) ;
				getchar() ;
				q->lastuse=timeCNT ;
				++timeCNT ;
			}
			else if( 'n'==ch )
			{
				q->isin=NO ;
				//���ڴ����ϵ�ҳ���Ӧ��ҳĿ¼�����עΪ�����ڡ�
				printf("��%dҳ�Ĵ���λ��:",i) ;
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
	//��ʼ������ָ��� 
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
			
			printf("�������%d��ָ��\n",i ) ;
			scanf("%c %d %d %d %d",&q->opcode,&q->pnum1,&q->padder1,&q->pnum2,&q->padder2) ;
			
			getchar() ;
			printf("operation:%c\n",q->opcode) ;
		}
	}
	bool isINmem( 	PARM_OUT pagetabp &ans ,
					PARM_IN pnum_t num , PARM_IN pagetabp head )
	//���ݸ�������ж�ҳ���Ƿ����ڴ沢ʹ��p���� 
	{
		pagetabp q=head ;
		while( nullptr!=q )
		{
			if( num==q->pnum )
			{
				ans=q ;
				if( 1==q->isin )
				//�����ڴ��� 
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
	//���ҳ��
	{
		pagetabp p=head ;
		printf("ʹ��\tҳ��\t���\t������\t�޸ı��\t����λ��\n") ;
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
	//�������ʹ��ʱ�� 
	{
		p->lastuse=lastTIME ;
		return ; 
	} 
	
	void fifoSCH( 	PARM_OUT pagetabp &head ,
					PARM_IN pagetabp p )
	//fifo����
	//�����ȳ�������û��ʹ�ö�����н���ά�������Դ˴����Ϊ���� 
	{ 
		pagetabp q=head ;
		pagetabp pre=head ;
		pagetabp r ;
		pagetabp t ;
		
		printf("����page:%d\n",head->pnum) ;
		while( nullptr!=pre )
		//��p��ǰһ���ڵ� 
		{
			if( pre->next==p )
				break ;
			else
				pre=pre->next ; 
		}
		if( nullptr==pre )
			printf("ҳ�治���ڣ�\n") ;
		else ;
		
		while( nullptr!=q )
		//Ѱ�����һ�������ڴ�Ľڵ㣬������ҳ��p����β 
		{
			//printf("%d\n",p->pnum) ;
			if( 1==q->next->isin )
			{
				q=q->next ;
				continue ;
			}
			else ;
			if( q->next!=p )
			//����Ѿ��������ô����Ҫ����
			//��pβ�壬��p->nextͷ�壬�൱�ڶ���β������ 
			{
				r=q->next ;
				q->next=p ;
				t=p->next ;
				p->next=r ;
				//pre�ŵ�����ҳ��ԭ����λ�ã�ʹ������next 
				pre->next=t ;
			}
			else ;
			//�޸�Ҫ�滻��ͷ�ڵ�
			//�޸��½ڵ�p����Ϣ 
			p->isedit=YES ;
			head->isedit=YES ;
			p->blocknum=head->blocknum ; 
			head->diskpos=p->diskpos ;
			//����head 
			head->isin=NO ; 
			p->isin=YES ;
			
			//�滻ͷ�ڵ� 
			//��ͷ�ڵ�ӵ���p֮�� 
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
	//Lru����
	//�����ڶ�ջ�Լ�ʱ���������ÿ�λ��������������δʹ�õ�ҳ�� 
	{
		pagetabp q=head ;
		pagetabp pre=head ;
		pagetabp r ;
		pagetabp t ;
		
		pagetabp turnPAGE=head ;
		
		int nowTIME=p->lastuse ;
		int ansTIME=0 ; 
		//osBASE::printPAGE( head ) ;
		//Ѱ�����δʹ��ҳ�� 
		while( nullptr!=q )
		{
			if( ansTIME<( q->lastuse-p->lastuse ) )
			{
				ansTIME=q->lastuse-p->lastuse ;
				turnPAGE=q ;
			}
			q=q->next ;
		}
		printf("���δʹ��page:%d\n",turnPAGE->pnum) ;
		
		pagetabp preHEAD=(pagetabp)malloc( sizeof(pagetab_t) ) ;
		preHEAD->next=head ;
		pagetabp cnt=preHEAD ;
		//�����ڱ��ڵ� 
		//Ѱ����Ҫ�û�ҳ���ǰһ���ڵ㣬��ɾ�� 
		//�˲���������һ�������Ż�������Ϊ�˿ɶ�����debug��������ֿ����� 
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
		
		//Ѱ����Ҫ���ص�ҳ���ǰһ��ҳ�棬�Ͽ����ӷ�ֹѭ�� 
		while( nullptr!=pre )
		{
			if( pre->next==p )
				break ;
			else
				pre=pre->next ;
		}
		
		q=head ;
		while( nullptr!=q )
		//Ѱ�����һ�������ڴ�Ľڵ㣬������ҳ��p
		{
			//printf("%d\n",p->pnum) ;
			if( 1==q->next->isin )
			{
				q=q->next ;
				continue ;
			}
			else ;
			if( q->next!=p )
			//����Ѿ��������ô����Ҫ����
			//��pβ�壬��p->nextͷ�壬�൱�ڶ���β������ 
			{
				r=q->next ;
				q->next=p ;
				t=p->next ;
				p->next=r ;
				//turnPAGE�ŵ�����ҳ��ԭ����λ�ã�ʹ������next 
				pre->next=t ;
			}
			else ;
			//osBASE::printPAGE( preHEAD->next ) ;
			//�޸�Ҫ�滻��ͷ�ڵ�
			//�޸��½ڵ�p����Ϣ 
			p->isedit=YES ;
			turnPAGE->isedit=YES ;
			p->blocknum=turnPAGE->blocknum ; 
			turnPAGE->diskpos=p->diskpos ;
			//����turnPAGE 
			turnPAGE->isin=NO ; 
			p->isin=YES ;
			
			//�滻ͷ�ڵ� 
			//��ͷ�ڵ�ӵ���p֮�� 
			r=turnPAGE ; 
			turnPAGE=turnPAGE->next ;
			t=p->next ;
			//p�Ѿ�����β������ָ���û�������ҳ�棬Ҳ�����û�ҳ����뵽p�� 
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
	//�������е�ָ����в���
	{
		operatep q=head ;
		
		//ָ��ҳ�� 
		pagetabp p_1=nullptr ;
		pagetabp p_2=nullptr ;
		//��ȡĿǰ�ж��ٱ�ʹ�õģ���Ϊʱ��ͳ�� 
		int timeCNT=cntUSE_index(page) ;
		++timeCNT ;
		 
		 
		while( nullptr!=q )
		{
			printf("Ŀǰʱ��%d\n",timeCNT) ;
			bool isin_1=osBASE::isINmem( p_1 , q->pnum1 , page ) ;
			useTIME( p_1 , timeCNT ) ;
			//printf("num1:%d\n",q->pnum1);
			//std::cout<<isin_1<<std::endl ;
			if( FIFO==choise )
			{
				if( !isin_1 )
				//δ����� 
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
			
			printf("�߼�ָ�%c %d %d %d %d\n", q->opcode , q->pnum1 , q->padder1 , q->pnum2 , q->padder2 ) ;
			printf("����ָ�%c %d %d %d %d\n", q->opcode , p_1->blocknum ,  p_1->blocknum*1024+q->padder1 , p_2->blocknum , p_2->blocknum*1024+q->padder2 ) ;
			q=q->next ;
			printf("\n") ;
			//osBASE::printODER( q ) ;
			++timeCNT ;
		}
	} 

	#undef PARM_IN
	#undef PARM_OUT
}
