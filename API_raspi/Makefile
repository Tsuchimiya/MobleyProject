PACKAGE = `pkg-config --cflags --libs gtk+-3.0`
LIBS = `pkg-config --libs gtk+-3.0`
LIBS1 = `pkg-config --cflags --libs champlain-gtk-0.12` 



all : main



main:
	gcc init_all.c com_CAN/listen.c com_CAN/communicationSTM.c IHM/ihm_handler.c ../GPS/gps_comm.c ../GPS/Trajectoires/demiTour.c ../GPS/Trajectoires/segment.c ../GPS/Trajectoires/codeRegulPos.c ../parser/mapparser.c -o init $(PACKAGE) $(CFLAGS) -lgps -lpthread  -lm


clean:
	rm -rf *.o;


