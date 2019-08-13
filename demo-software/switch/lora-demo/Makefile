all: switch relay

bcm2835.o : bcm2835.c bcm2835.h
	g++ -c bcm2835.c -o bcm2835.o

SX1272.o : SX1272.cpp SX1272.h
	g++ -c SX1272.cpp -o SX1272.o

switch : switch.cpp bcm2835.o SX1272.o
	g++ switch.cpp bcm2835.o SX1272.o -o switch

relay : relay.cpp bcm2835.o SX1272.o
	g++ relay.cpp bcm2835.o SX1272.o -o relay
 
