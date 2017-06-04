#include "initThreads.h"

void initThreads(int readersCounter,int writersCounter)
{

pthread_t idReaders[readersCounter];
pthread_t idWriters[writersCounter];

    pthread_mutex_init(&mutexReaders,NULL);
    pthread_mutex_init(&mutexReadersRoom,NULL);

	int i;

	for (i=0; i < readersCounter; i++) {
		errno = pthread_create(&idReaders[i], NULL, reader, NULL);
		test_errno("Blad tworzenia watkow czytelnikow");
	}

	for (i=0; i < writersCounter; i++) {
		errno = pthread_create(&idWriters[i], NULL, writer, NULL);
		test_errno("Blad tworzenia watkow pisarzy");
	}

}
