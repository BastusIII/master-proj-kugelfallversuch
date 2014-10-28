#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <iostream>
#include <pthread.h>
#include <unix.h>
#include <time.h>
#include <semaphore.h>
#include <errno.h>

#define NUMBER_OF_THREADS 3
#define NUMBER_OF_SEGMENTS 64
#define PI 3.14159265359
#define SIZE_SPEED_BUFFER 100
#define MAX_SPEED_ERROR 0.0005
// TODO: insert proper constants
#define CONST_H 0.4 // Höhe
#define CONST_G 9.81 // Erdanziehungskraft
#define CONST_T_f 1 // Falldauer bis Platte
#define CONST_T_d 1 // Durchfalldauer durch Scheibe
#define CONST_PHI_l 1 // Winkel des Lochs
#define CONST_PHI_event 1 // Winkel bei dem das Event Loch eintrifft



struct sharedMemoryStruct {
	double speedBuffer[SIZE_SPEED_BUFFER]; // speed in rps
	int elapsedTime; // time in ms
	int constant; // true if speed is constant
	int currentSpeed; // the current speed
	int timer; // true if drop was initiated
	int terminateThreads; // indicate if threads should be terminated
	sem_t* sem_elapsedTime; // semaphore to notify speed calculator that new time is available
	sem_t* sem_currentSpeed; // semaphore to notify time calculator that speed has changed
	sem_t* sem_sleep;
	sem_t* sem_dropInitiated;
};

void* timeProducer(void* args) {
	std::cout << "time producer starting... "<< std::endl;
	sharedMemoryStruct memory = *(sharedMemoryStruct*)args;
	while(memory.terminateThreads == 0) {
		/*timespec start;
		timespec end;
		clock_gettime(CLOCK_REALTIME, &start);
		start.tv_nsec += 1000 * 1000 * 12; // add some milliseconds
		sem_timedwait(memory.sleep, &start);
		clock_gettime(CLOCK_REALTIME, &end);
		memory.elapsedTime = (end.tv_sec - start.tv_sec) * 1000 + ((end.tv_nsec - start.tv_nsec) / (1000*1000));
		sem_post(memory.newTime);*/
	}
	std::cout << "time producer terminating... "<< std::endl;
	pthread_exit(0);
}

void* calculateSpeed(void* args) {
	std::cout << "speed calculator starting... "<< std::endl;
	sharedMemoryStruct memory = *(sharedMemoryStruct*)args;

	while(!memory.terminateThreads) {
		sem_wait(memory.sem_elapsedTime);

		double speedSum = 0;
		double errorSum = 0;
		for(int i = 0; i < SIZE_SPEED_BUFFER-1; ++i) {
			speedSum += memory.speedBuffer[i]; // calculate speed sum
			errorSum += memory.speedBuffer[i+1] - memory.speedBuffer[i]; // calculate error sum
			memory.speedBuffer[i+1] = memory.speedBuffer[i];
		}
		memory.speedBuffer[0]  = (double)1 / NUMBER_OF_SEGMENTS / memory.elapsedTime * 1000; // n := rps
		speedSum += memory.speedBuffer[0];
		errorSum += memory.speedBuffer[1] - memory.speedBuffer[0];

		memory.currentSpeed = speedSum/SIZE_SPEED_BUFFER;
		double averageError = errorSum/SIZE_SPEED_BUFFER;

		// TODO: maybe calculation is not sufficient
		memory.constant = averageError < MAX_SPEED_ERROR;
		if(!memory.constant) {
			// inform time calculation that new speed is available
			sem_post(memory.sem_currentSpeed);
		}
	}
	std::cout << "speed calculator terminating... "<< std::endl;
	pthread_exit(0);
}

void* calculateTimer(void* args) {
	std::cout << "time calculator starting... "<< std::endl;
	sharedMemoryStruct memory = *(sharedMemoryStruct*)args;

	while(!memory.terminateThreads) {
		sem_wait(memory.sem_currentSpeed);
		// calculation is done if speed is constant
		if(memory.constant) {
			// TODO: get omega outta there, e.g. 2*PI stuff
			double phi_buf = CONST_PHI_l - 2 * PI * memory.currentSpeed * CONST_T_d;
			double phi_drop = 2 * PI * memory.currentSpeed * CONST_T_f - phi_buf/2;
			memory.timer = (phi_drop - phi_buf) * 2 * PI * memory.currentSpeed;
		}
	}
	std::cout << "time calculator terminating... "<< std::endl;
	pthread_exit(0);
}

int main(void) {

	std::cout << "Program starting" << std::endl;

	// create shared memory
	sharedMemoryStruct memory;
	memory.constant = 0;
	memory.timer = 0;
	memory.elapsedTime = 0;
	memory.terminateThreads = 0;

	// some options for the created thread
	pthread_attr_t attr;
	// creates a standard pthread_attr
	pthread_attr_init(&attr);
	// manipulate pthread_attr: Joinable -> calling thread will wait for this thread to finish
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE );

	// allocate the needed memory on the stack
	pthread_t thread[2];

	if(pthread_create(&thread[0], &attr, &timeProducer, &memory ) != EOK) {
		perror("time producer thread could not be created");
	}

	if(pthread_create(&thread[1], &attr, &calculateSpeed, &memory ) != EOK) {
		perror("calculate timer thread could not be created");
	}

	/*if(pthread_create(&thread[2], &attr, &calculateTimer, &sharedMemory ) != EOK) {
		perror("calculate speed thread could not be created");
	}*/

	// let this stuff go on for some time
	sleep(1);
	memory.terminateThreads = 1;

	std::cout << "joining threads"<< std::endl;
	for (int i = 0; i < 2; i++) {
		int thread_id;
		// join created so the main thread waits until the created thread has terminated and then continues
		if(pthread_join(thread[i], (void**) &thread_id) != EOK) {
			perror("error joining thread");
		}
	}
	return EXIT_SUCCESS;
}
