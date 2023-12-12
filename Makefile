all:
	gcc leetingHome.c -o leetingHome.o
val:
	gcc leetingHome.c -g -Wall -o leetingHome.o
test:
	gcc testingC.c -g -Wall -o testingC.o
data:
	gcc data_structures.c -g -Wall -o data_structures.o
