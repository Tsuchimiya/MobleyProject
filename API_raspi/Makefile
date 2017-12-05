PACKAGE = `pkg-config --cflags --libs gtk+-3.0`
LIBS = `pkg-config --libs gtk+-3.0`


all : main



main:
	gcc init_all.c com_CAN/listen.c com_CAN/communicationSTM.c IHM/ihm_handler.c -o init $(PACKAGE) $(CFLAGS) -lpthread


clean:
	rm -rf *.o
