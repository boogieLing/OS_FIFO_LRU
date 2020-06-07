
#define FIFO 1
#define LRU 0
#define YES 1
#define NO  0

typedef int pnum_t ; 
//ҳ����� 
typedef int bnum_t ;
//������
typedef int dispos_t ;
//����λ��
typedef int padder_t ;
//��Ԫ��ַ 
typedef int lastuse_t ;
//��һ��ʹ�õ�ʱ��λ 
typedef char opcode_t ;
//������ 

//Ԥ������ 
typedef struct pagetab_t
//ҳ��
{
	pnum_t 		pnum ;
	bnum_t 		blocknum ;
	dispos_t 	diskpos ;
	lastuse_t	lastuse ;
	
	int 		isedit ;
	//�޸ı�� 
	int 		isin ;
	//״̬��� 
	
	struct pagetab_t* next ;
}pagetab_t , * pagetabp ;

typedef struct operate
//����ָ��
{
	opcode_t	opcode ;
	pnum_t		pnum1 ;
	padder_t	padder1 ;
	pnum_t		pnum2 ;
	padder_t	padder2 ;
	
	struct operate* next ;
}operate_t, * operatep ;


