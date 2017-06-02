#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#define CUSTOM_READERS 5
#define CUSTOM_WRITERS 2

#define test_errno(msg) do{if (errno) {perror(msg); exit(EXIT_FAILURE);}} while(0)


int readersQueque=0,writersQueque=0,inReaders=0,inWriters=0;

pthread_mutex_t mutexReadersRoom,mutexReaders;

void *writer();

void *reader();

void consoleOutput();

void initThreads(int readersCounter,int writersCounter);

void waitForEntryReader();

void waitForEntryWriter();

void inReadingRoom();

int main(int argc, char* argv[])
{

if (argc==2){ 
initThreads(argv[0],argv[1]);
readersQueque=argv[0];
writersQueque=argv[1];
}
else{
initThreads(CUSTOM_READERS,CUSTOM_WRITERS);
readersQueque=5;
writersQueque=2;
}



if (argc==2){ 
initThreads(argv[0],argv[1]);
}
else{
initThreads(CUSTOM_READERS,CUSTOM_WRITERS);
}
 return 0;

}

void initThreads(int readersCounter,int writersCounter)
{
pthread_t idReaders[readersCounter];
pthread_t idWriters[writersCounter];
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

}

void *writer()
{

while ( 1 )
  { 
	waitForEntryWriter();
	pthread_mutex_lock(&mutexReadersRoom);
	inWriters++;
	writersQueque--;
	consoleOutput();
	inReadingRoom();
	inWriters--;
	writersQueque++;
	consoleOutput();
	pthread_mutex_unlock(&mutexReadersRoom);
 

  } 
}


void *reader()

{

while ( 1 )
  { 
	waitForEntryReader();
	pthread_mutex_lock(&mutexReaders);
	inReaders++;
	readersQueque--;
	if (inReaders==1) pthread_mutex_lock(&mutexReadersRoom); //wchodzi pierwszy czytelnik, pisarz nie moze juz wejsc
	pthread_mutex_unlock(&mutexReaders);
	consoleOutput();
	inReadingRoom();
	pthread_mutex_lock(&mutexReaders);
	inReaders--;
	readersQueque++;
	consoleOutput();
	if (inReaders==0) pthread_mutex_unlock(&mutexReadersRoom);
	pthread_mutex_unlock(&mutexReaders);
 

  } 

}

void waitForEntryReader(){
int i;
for (i=0;i<30;i++){};
}

void waitForEntryWriter(){
int i;
for (i=0;i<10;i++){};
}

void inReadingRoom(){
int i;
for (i=0;i<100;i++){};
}

void consoleOutput(){
printf("ReaderQ: %d WriterQ: %d [in: R:%d W:%d]\n", readersQueque,writersQueque,inReaders,inWriters);
}
