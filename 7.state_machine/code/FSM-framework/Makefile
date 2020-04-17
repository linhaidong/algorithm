NAME=fsm
object=action.o fsm.o main.o
$(NAME): $(object)
	gcc  $^ -o $@

main.o:main.c
	gcc -c main.c 

action.o:action.c
	gcc -c action.c action.h 

fsm.o:fsm.c fsm.h
	gcc -c fsm.h fsm.c 

 
clean:
	echo $(object)
	rm -fr $(NAME) $(object)
