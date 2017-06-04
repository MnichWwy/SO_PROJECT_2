#include "writer.h"

void *writer()
{

while ( 1 )
  {
	waitForEntryWriter();
	writersQueque++;
	consoleOutput();
	pthread_mutex_lock(&mutexReadersRoom);

	inWriters++;
	writersQueque--;
	consoleOutput();

	inReadingRoom();
	
	inWriters--;
	consoleOutput();

	pthread_mutex_unlock(&mutexReadersRoom);


  }
}
