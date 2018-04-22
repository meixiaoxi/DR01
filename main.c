#include "common.h"



 void capture_start()
{
	T1CRH |=((1<<7)|(1<<0)); 
}

void main()
{
	DI();		
	system_init();


	//start
	EI();
	capture_start();

	do{
		
		}while(1);
	
}
