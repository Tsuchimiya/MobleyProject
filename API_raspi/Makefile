PACKAGE = `pkg-config --cflags --libs gtk+-3.0`
LIBS = `pkg-config --libs gtk+-3.0`
LIBS1 = `pkg-config --cflags --libs champlain-gtk-0.12` 



all : main



main:
	gcc init_all.c com_CAN/listen.c com_CAN/communicationSTM.c IHM/ihm_handler.c ../GPS/gps_comm.c -o init $(PACKAGE) $(CFLAGS) -lpthread -lgps -lm


clean:
	rm -rf *.o
