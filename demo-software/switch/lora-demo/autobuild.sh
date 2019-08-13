g++ -c SX1272.cpp -o SX1272.o
g++  switch.cpp SX1272.o -lbcm2835 -o switch

