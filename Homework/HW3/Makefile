#MAKE SURE YOUR CODE COMPILES WITH THESE FLAGS!
#WARNINGS = NO COMPILE = ZERO!
#also can add to the list of flags if you so desire. At your own risk. 
CFLAGS = -g -Wall -Werror

#add what you need to make HW3 get compiled. IT IS YOUR RESPONSIBILITY TO 
#MAKE SURE EVERYTHING GETS IN THE COMPILATION. 
#Depending on your choice of implementation, change what you need to change. 

#Getting this to work is probably the hardest part of HW3. Use your 
#resources to figure out how this thing works. 
all: Gauntlet

Gauntlet: game.o shop.o heroes.o io.o parse.o boss.o fight.o
	gcc game.o shop.o heroes.o io.o boss.o parse.o fight.o -g -o Gauntlet

game.o: game.c game.h
	gcc game.c -c -g -Wall -Werror -o game.o

shop.o: shop.c game.h
	gcc shop.c -c -g -Wall -Werror -o shop.o

heroes.o: heroes.c game.h
	gcc heroes.c -c -g -Werror -Wall -o heroes.o

io.o: io.c game.h
	gcc io.c -c -g -Wall -Werror -o io.o

parse.o: parse.c game.h
	gcc parse.c -c -g -Wall -Werror -o parse.o

fight.o: fight.c game.h
	gcc fight.c -c -g -Wall -Werror -o fight.o

boss.o: boss.c game.h
	gcc boss.c -c -g -Wall -Werror -o boss.o

clean:
	rm -f *.o Gauntlet
