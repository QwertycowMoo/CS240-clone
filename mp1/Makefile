
all:
	gcc -g main.c add_int.c capitalize.c emoji.c -DPART1 -DPART2 -DPART3 -o mp1

part1:
	gcc -g main.c add_int.c -DPART1 -o part1

part2:
	gcc main.c capitalize.c -DPART2 -o part2

part3:
	gcc main.c emoji.c -DPART3 -o part3

clean:
	rm -f part1 part2 part3 mp1