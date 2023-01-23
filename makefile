CC=gcc
OF=_output

build:
	$(CC) -Iinclude -o $(OF)/main.o sources/main.c -c -std=c99
	$(CC) -Iinclude -o $(OF)/ccb_loader.o sources/ccb_loader.c -c -std=c99
	$(CC) -Iinclude -o $(OF)/ccb_runner.o sources/ccb_runner.c -c -std=c99
	$(CC) -Iinclude -o $(OF)/ccb_stack.o sources/ccb_stack.c -c -std=c99
	$(CC) -Iinclude -o $(OF)/ccb_instructions.o sources/ccb_instructions.c -c -std=c99
	$(CC) -Iinclude -o $(OF)/cmdparser.o sources/cmdparser.c -c -std=c99

	$(CC) -Iinclude $(OF)/main.o $(OF)/ccb_loader.o $(OF)/ccb_runner.o $(OF)/ccb_stack.o  $(OF)/ccb_instructions.o $(OF)/cmdparser.o -o $(OF)/ccvm.exe -std=c99
