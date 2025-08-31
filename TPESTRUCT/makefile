myprog: dlist.o hash.o deff.o defl.o apply.o shell.o
	gcc shell.c dlist.o deff.o defl.o apply.o hash.o primitivas.o -Wall -Wextra -Werror -std=c99 -g
	valgrind  -v ./a.out 

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

shell.o:
	gcc shell.c -c -Wall -Wextra -Werror -std=c99 -g