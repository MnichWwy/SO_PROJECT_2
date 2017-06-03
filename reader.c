#include "reader.h"

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

