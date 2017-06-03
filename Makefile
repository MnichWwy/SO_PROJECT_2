SO_PROJECT_2: main.o consoleOutput.o endThreads.o initThreads.o inReadingRoom.o reader.o writer.o waitForEntryReader.o waitForEntryWriter.o
	gcc main.c consoleOutput.c endThreads.c initThreads.c inReadingRoom.c reader.c writer.c waitForEntryReader.c waitForEntryWriter.c -pthread
