#ifndef _WAITFORENTRYWRITER_H_
#define _WAITFORENTRYWRITER_H_

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

extern int readersQueque,writersQueque,inReaders,inWriters;

extern pthread_mutex_t mutexReadersRoom,mutexReaders;

void waitForEntryWriter();

#endif //_WAITFORENTRYWRITER_H
