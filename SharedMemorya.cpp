#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <time.h>
#include <iostream>
#include <string.h>

using namespace std;

   int main()
{
	sem_t sem;
	
	srand(time(0));
	sem_init(&sem, 1, 1);
	int value = 1;
	
	int fd = shm_open("Memory", O_CREAT | O_RDWR, 0666);
	ftruncate(fd, 1024);
	char* mem = (char*)mmap(0, 1024, PROT_WRITE, MAP_SHARED, fd, 0);
	
	pid_t pID = fork();

	while ( value <= 1000){
		int random = rand() % 2;
		if ( random + 1 ==2){
			sem_wait(&sem);
			sprintf(mem, "%d", value);
			!pID ? cout << "The parent prints: "<< mem << endl : cout;
			value++;
			sem_post(&sem);
		}
		if (pID != 0){
			wait(NULL);
                }
		else if (pID == 0){
			random = rand() % 2;
		if ( random +1 ==2){
			sem_wait(&sem);
			sprintf(mem, "%d", value);
			cout << "The child prints: " << mem << endl;
			value++;
			sem_post(&sem);
			}
		    }
		}


		sem_destroy(&sem);
		munmap(mem, 1024);
		close(fd);
		shm_unlink("Memory");
    
    return 0;
}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		


