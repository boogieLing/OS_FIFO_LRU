#include "OS_4.hpp"
using namespace std ;

signed main()
{
	pagetabp pt ;
	operatep opert;
	int iniCNT=6 ;
	int operCNT=5 ;
	osBASE::initPAGE( pt , iniCNT ) ;
	osBASE::iniOPER( opert , operCNT ) ;
	printf("初始表:\n") ;
	osBASE::printPAGE(pt) ;
	//osBASE::printODER( opert ) ;
	
	algorithm::opera( opert , LRU , pt ) ;
	
	printf("结束表:\n") ;
	osBASE::printPAGE(pt) ;
	return 0 ; 
} 
/*
y
3
y
4
y
5
n
30
n
25
n
26
+ 0 30 2 3
- 1 50 2 5
* 2 1 5 4
/ 3 7 1 31
r 4 34 3 25




*/
