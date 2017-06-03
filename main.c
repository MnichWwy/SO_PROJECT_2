#include <pthread.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>


#include "writer.h"
#include "reader.h"
#include "consoleOutput.h"
#include "initThreads.h"
#include "endThreads.h"
#include "waitForEntryReader.h"
#include "waitForEntryWriter.h"
#include "inReadingRoom.h"
#include "reader.h"


#define CUSTOM_READERS 5
#define CUSTOM_WRITERS 2

#define test_errno(msg) do{if (errno) {perror(msg); exit(EXIT_FAILURE);}} while(0)


int readersQueque=0,writersQueque=0,inReaders=0,inWriters=0;

pthread_mutex_t mutexReadersRoom,mutexReaders;

pthread_cond_t turn;

int main(int argc, char* argv[])
{

if (argc==3){
initThreads(strtol(argv[1], NULL, 10),strtol(argv[2], NULL, 10));
}
else{
initThreads(CUSTOM_READERS,CUSTOM_WRITERS);
}



if (argc==3){
endThreads(strtol(argv[1], NULL, 10),strtol(argv[2], NULL, 10));
}
else{
endThreads(CUSTOM_READERS,CUSTOM_WRITERS);
}
printf("Koniec");
 return 0;

}

