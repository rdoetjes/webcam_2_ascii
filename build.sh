g++ $(pkg-config --cflags --libs opencv4) -std=c++11  main.cpp -o main.o
g++ -o ascii main.o
