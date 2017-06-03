#include "writer.h"

void *writer()
{

while ( 1 )
  {
	waitForEntryWriter();
	writersQueque++;
	pthread_mutex_lock(&mutexReadersRoom);

	/*
	while (inReaders || inWriters)
	{
	 pthread_cond_wait(&turn,&mutexReadersRoom);
	}
	*/

	inWriters++;
	writersQueque--;
	consoleOutput();
	
	//pthread_mutex_unlock(&mutexReadersRoom);

	inReadingRoom();

	//pthread_mutex_lock(&mutexReadersRoom);
	
	inWriters--;
	consoleOutput();

	//pthread_cond_broadcast(&turn);
	pthread_mutex_unlock(&mutexReadersRoom);


  }
}
