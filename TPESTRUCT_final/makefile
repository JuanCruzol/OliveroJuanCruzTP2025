myprog: dlist.o hash.o deff.o defl.o apply.o cola.o search.o shell.o primitivas.o
	gcc shell.c dlist.o deff.o defl.o apply.o hash.o primitivas.o cola.o search.o -Wall -Wextra -Werror -std=c99 -g 
	valgrind -v ./a.out

dlist.o: 
	gcc dlist.c -c -Wall -Wextra -Werror -std=c99 -g

hash.o:
	gcc hash.c -c -Wall -Wextra -Werror -std=c99 -g

deff.o:
	gcc deff.c -c -Wall -Wextra -Werror -std=c99 -g

defl.o:
	gcc defl.c -c -Wall -Wextra -Werror -std=c99 -g

apply.o:
	gcc apply.c -c -Wall -Wextra -Werror -std=c99 -g

search.o:
	gcc search.c -c -Wall -Wextra -Werror -std=c99 -g

cola.o:
	gcc cola.c -c -Wall -Wextra -Werror -std=c99 -g

shell.o:
	gcc shell.c -c -Wall -Wextra -Werror -std=c99 -g


clean:
	rm -f *.o myprog