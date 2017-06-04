#include "endThreads.h"

void endThreads(int readersCounter,int writersCounter)
{

pthread_t idReaders[readersCounter];
pthread_t idWriters[writersCounter];
	int i;

	for (i=0; i < readersCounter; i++) {
		errno = pthread_join(idReaders[i], NULL);
		test_errno("Blad konczenia watkow czytelnikow");
	}

	for (i=0; i < writersCounter; i++) {
		errno = pthread_join(idWriters[i], NULL);
		test_errno("Blad konczenia watkow pisarzy");
	}
pthread_mutex_destroy(&mutexReadersRoom);
pthread_mutex_destroy(&mutexReaders);	

}
