
#define FIFO 1
#define LRU 0
#define YES 1
#define NO  0

typedef int pnum_t ; 
//页面序号 
typedef int bnum_t ;
//主存块号
typedef int dispos_t ;
//磁盘位置
typedef int padder_t ;
//单元地址 
typedef int lastuse_t ;
//上一次使用的时刻位 
typedef char opcode_t ;
//操作符 

//预定义类 
typedef struct pagetab_t
//页表
{
	pnum_t 		pnum ;
	bnum_t 		blocknum ;
	dispos_t 	diskpos ;
	lastuse_t	lastuse ;
	
	int 		isedit ;
	//修改标记 
	int 		isin ;
	//状态标记 
	
	struct pagetab_t* next ;
}pagetab_t , * pagetabp ;

typedef struct operate
//操作指令
{
	opcode_t	opcode ;
	pnum_t		pnum1 ;
	padder_t	padder1 ;
	pnum_t		pnum2 ;
	padder_t	padder2 ;
	
	struct operate* next ;
}operate_t, * operatep ;


