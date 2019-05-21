


output: main.o BadRequestException.o NotFoundException.o permissionException.o publisher.o notification.o maneger.o film.o client.o comment.o
	g++ main.o BadRequestException.o NotFoundException.o permissionException.o publisher.o notification.o maneger.o film.o client.o comment.o -o NetFlix.out

main.o: main.cpp classes.h
	g++ -c main.cpp

BadRequestException.o: BadRequestException.cpp classes.h
	g++ -c BadRequestException.cpp

NotFoundException.o: NotFoundException.cpp classes.h
	g++ -c NotFoundException.cpp

permissionException.o: permissionException.cpp classes.h
	g++ -c permissionException.cpp

publisher.o: publisher.cpp classes.h
	g++ -c publisher.cpp

notification.o: notification.cpp classes.h
	g++ -c notification.cpp

maneger.o: maneger.cpp classes.h
	g++ -c maneger.cpp

film.o: film.cpp classes.h
	g++ -c film.cpp

client.o: client.cpp classes.h
	g++ -c client.cpp

comment.o: comment.cpp classes.h
	g++ -c comment.cpp


# target: dependencies
# 	action

clean:
	rm *.o NetFlix.out
