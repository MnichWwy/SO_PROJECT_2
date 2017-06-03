#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

#define CUSTOM_READERS 5
#define CUSTOM_WRITERS 2

#define test_errno(msg) do{if (errno) {perror(msg); exit(EXIT_FAILURE);}} while(0)


int readersQueque=0,writersQueque=0,inReaders=0,inWriters=0;

pthread_mutex_t mutexReadersRoom,mutexReaders;

pthread_cond_t turn;

void *writer();

void *reader();

void consoleOutput();

void initThreads(int readersCounter,int writersCounter);

void waitForEntryReader();

void waitForEntryWriter();

void inReadingRoom();

int main(int argc, char* argv[])
{

if (argc==3){
readersQueque=strtol(argv[1], NULL, 10);
writersQueque=strtol(argv[2], NULL, 10);
initThreads(strtol(argv[1], NULL, 10),strtol(argv[2], NULL, 10));
}
else{
readersQueque=CUSTOM_READERS;
writersQueque=CUSTOM_WRITERS;
initThreads(CUSTOM_READERS,CUSTOM_WRITERS);
}



if (argc==3){
initThreads(strtol(argv[1], NULL, 10),strtol(argv[2], NULL, 10));
}
else{
initThreads(CUSTOM_READERS,CUSTOM_WRITERS);
}
printf("Koniec");
 return 0;

}

void initThreads(int readersCounter,int writersCounter)
{
pthread_t idReaders[readersCounter];
pthread_t idWriters[writersCounter];

    pthread_mutex_init(&mutexReaders,NULL);
    pthread_mutex_init(&mutexReadersRoom,NULL);
    pthread_cond_init(&turn, NULL);	
    pthread_mutex_unlock(&mutexReaders);
    pthread_mutex_unlock(&mutexReadersRoom);

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
pthread_cond_destroy(&turn);	

}

void *writer()
{

while ( 1 )
  {
	waitForEntryWriter();
	pthread_mutex_lock(&mutexReadersRoom);

	writersQueque++;
	consoleOutput();

	while (inReaders || inWriters)
	{
	 pthread_cond_wait(&turn,&mutexReadersRoom);
	}

	inWriters++;
	writersQueque--;
	consoleOutput();
	
	pthread_mutex_unlock(&mutexReadersRoom);

	inReadingRoom();

	pthread_mutex_lock(&mutexReadersRoom);
	
	inWriters--;
	writersQueque++;
	consoleOutput();

	pthread_cond_broadcast(&turn);
	pthread_mutex_unlock(&mutexReadersRoom);


  }
}


void *reader()

{

while ( 1 )
  {
	waitForEntryReader();
	pthread_mutex_lock(&mutexReaders);
	
	while (inWriters)
	{
	 pthread_cond_wait(&turn,&mutexReadersRoom);
	}
	
	readersQueque--;
	inReaders++;
	consoleOutput();

	pthread_mutex_unlock(&mutexReadersRoom);
	inReadingRoom();

	pthread_mutex_lock(&mutexReadersRoom);
	inReaders--;
	readersQueque++;
	consoleOutput();

	pthread_cond_broadcast(&turn);
	pthread_mutex_unlock(&mutexReadersRoom);


  }

}

void waitForEntryReader(){
sleep(1/20);
}

void waitForEntryWriter(){
sleep(1/80);
}

void inReadingRoom(){
sleep(1/50);
}

void consoleOutput(){
printf("ReaderQ: %d WriterQ: %d [in: R:%d W:%d]\n", readersQueque,writersQueque,inReaders,inWriters);
}
