#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unix.h>
#include <errno.h>
#include <queue.h>

#define NUMBER_OF_THREADS = 11;
#define SIZE_OF_MEASUREMENT_PACKET = 10;
#define SIZE_OF_MEASUREMENT_PACKET_BUFFER = 10;
#define SIZE_OF_SPEED_BUFFER = 10;

// BIIIG QUESTION: Should we use synchronisation/wait/notify at all or should we better use busy waiting

struct sharedMemoryStruct {
	measuredInformationStruct measurementPacketBuffer[SIZE_OF_MEASUREMENT_PACKET][SIZE_OF_MEASUREMENT_PACKET_BUFFER];	
	int speedBuffer[SIZE_OF_SPEED_BUFFER]; // maybe using queue here would be cool
	int speedIsConstant;
	int thread_terminate;	// set this to 1 to terminate all threads, dont forget to notify all threads after that
	int timer;
	pthread_cond_t* newSpeed;
	pthread_cond_t* newMeasurement;
	pthread_cond_t* constantSpeedReached;
	pthread_cond_t* gapDetected;	// this event is thrown when we have detected that the gap just drove by
};

struct measuredInformationStruct {
	int timestamp;
	int value;
};

void* calculateTimer(void* args) {	

	sharedMemoryStruct memory = *(sharedMemoryStruct*)args;
	
	while(!memory.thread_terminate) {
		pthread_cond_wait(memory.newSpeed);
		// TODO: calculate new timer here from the last measured Speed in speedBuffer and update timer
		// TODO: check if the speed in speedbuffer is constant, update speedIsContant and notify all on cond constantSpeedReached
	}
	pthread_exit(0);
}

void* calculateSpeed(void* args) {	

	sharedMemoryStruct memory = *(sharedMemoryStruct*)args;
	
	while(!memory.thread_terminate) {
		pthread_cond_wait(memory.newMeasurement);
		// TODO: calculate new speed here from the measurementPacketBuffer, update speedBuffer and notify all on cond newSpeed
		// TODO: check if there was the gap by analyzing the last measurements and if detected, notify all on cond gapDetected
		// TODO: option: maybe predict the next occurrence of the gap by interpolating it by the last occurancy times
	}
	pthread_exit(0);
}

int main(void) {
	
	// some options for the created thread
	pthread_attr_t attr;
	// creates a standard pthread_attr
	pthread_attr_init(&attr);
	// manipulate pthread_attr: Joinable -> calling thread will wait for this thread to finish
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE );

	// allocate the needed memory on the stack
	pthread_t thread[NUMBER_OF_THREADS];

	if(pthread_create(&thread[0], &attr, &calculateTimer, &sharedMemory ) != EOK) {
		perror("calculate timer thread could not be created");
	}
	if(pthread_create(&thread[1], &attr, &calculateSpeed, &sharedMemory ) != EOK) {
		perror("calculate speed thread could not be created");
	}

	for (int i = 0; i < NUMBER_OF_THREADS; i++) {
		int thread_id;
		// join created so the main thread waits until the created thread has terminated and then continues
		if(pthread_join(thread[i], (void**) &thread_id) != EOK) {
			perror("error joining thread");
		}
	}
	return EXIT_SUCCESS;
}
