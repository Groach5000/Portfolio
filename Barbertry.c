#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#define seats 5 // this is 4 waiting seats and 1 in chair

//Garrett Roach Sleeping Barber Problem

pthread_mutex_t queue = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t wait = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t sleeps = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t SleepingBarber = PTHREAD_COND_INITIALIZER;
pthread_cond_t BarberWorking= PTHREAD_COND_INITIALIZER;

void *CreateCustomer();
void *BarberShop();
void *WaitingRoom();

void WaitInLine();

time_t begin, end;
double time_open = 60; // current operation time (or time the shop is open)
int current_num = 0;
int sleeping = 0; // true or false if barber is sleeping

int main()
{
		pthread_t barberd,customerd;
		pthread_attr_t barberA, customerA;

		pthread_attr_init(&barberA);
		pthread_attr_init(&customerA);

		pthread_create(&customerd,&customerA,CreateCustomer,NULL);//create customer
		pthread_create(&barberd,&barberA,BarberShop,NULL);//create barber
		pthread_join(barberd,NULL);
		pthread_join(customerd,NULL);
		return 0;
}

void *CreateCustomer()
{
		int g=0;
		pthread_t customer[seats+1];
		pthread_attr_t customerAttr[seats+1];
		while(g < (seats+1))
		{
				g++;
				pthread_attr_init(&customerAttr[g]);
				sleep(rand() % 5 + 1);
				pthread_create(&customer[g],&customerAttr[g],WaitingRoom,NULL);
		}
		pthread_exit(0);
}

void *BarberShop()
{
		int condition=1;
		printf("\tThe barber has opened the shop.\n");
		printf("\tThe shop will be open for %f seconds\n", time_open);
		time(&begin);
		while(condition==1)
		{
			if(current_num==0)
			{
				if (time_open  <= (double)(end-begin))
				{
					condition = 0;
					printf("\tClosing time and customers: %d.\n", current_num);
					printf("\tBarber goes home for the day.\n");
					pthread_exit(0);
				}
				else
				{
					printf("\tNo customers, barber sleeps.\n");
					pthread_mutex_lock(&sleeps);
					sleeping=1;
					pthread_cond_wait(&SleepingBarber,&sleeps);
					sleeping=0;
					pthread_mutex_unlock(&sleeps);
					printf("\tBarber wakes up.\n");
				}
			}
			else
			{
				printf("\tBarber begins cutting hair.\n");
				sleep(rand() % 8 + 1);
				current_num--;
				printf("\tHair cut complete, Customer leaves barber shop\n");
				printf("\tCustomers in shop: %d.\n", current_num);
				pthread_cond_signal(&BarberWorking);
			}
		}
		pthread_exit(0);
}

void *WaitingRoom()
{
		pthread_mutex_lock(&queue);
		WaitInLine();
		sleep(rand() % 20 + 1);
		WaitingRoom();
}

void WaitInLine()
{
		current_num++;
		printf("Customer has arrived in the barber shop.\n");
		time(&end);
		printf("  Customers in shop: %d of %d\n",current_num, seats);
		if(time_open  <= (double)(end-begin))
		{
			printf("  Time: %f seconds, shop closed to new customers at %f\n", (double)(end - begin), time_open);
			printf("  The shop is closed to new customers, customer goes home\n");
			current_num--;
			pthread_mutex_unlock(&queue);
			return;
		}	
		else if(current_num <= seats)
		{
				if(sleeping==1)
				{
						printf("\tBarber is sleeping, customer wakes him up.\n");
						pthread_cond_signal(&SleepingBarber);
				}
				else
					printf("  Customer waits in waiting area.\n");
				pthread_mutex_unlock(&queue);
				pthread_mutex_lock(&wait);
				pthread_cond_wait(&BarberWorking,&wait);
				pthread_mutex_unlock(&wait);
				return;
		}
		else
		{
				printf("All chairs full, customer goes home.\n");
				current_num--;
				pthread_mutex_unlock(&queue);
				return;
		}
}

