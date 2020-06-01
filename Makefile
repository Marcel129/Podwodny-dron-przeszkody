OBJ=./obj
CPPFLAGS= -c -g -Wall -pedantic -I inc -std=c++17

__start__: main.out
	./main.out

main.out: ${OBJ}/Dr3D_gnuplot_api.o ${OBJ}/main.o ${OBJ}/def_szab.o ${OBJ}/dron.o ${OBJ}/bryla.o ${OBJ}/int_rysowania.o ${OBJ}/powierzchnia.o \
${OBJ}/wirnik.o ${OBJ}/przesz_prost.o
	g++ -o main.out ${OBJ}/main.o ${OBJ}/Dr3D_gnuplot_api.o ${OBJ}/def_szab.o ${OBJ}/dron.o ${OBJ}/bryla.o ${OBJ}/int_rysowania.o ${OBJ}/powierzchnia.o \
	${OBJ}/wirnik.o ${OBJ}/przesz_prost.o -lpthread

${OBJ}:
	mkdir ${OBJ}

${OBJ}/main.o: src/main.cpp Dr3D_gnuplot_api.hh inc/Wektor.hh inc/Macierz.hh inc/rozmiar.h inc/dron.hh inc/bryla.hh inc/int_rysowania.hh inc/parametry_drona.hh\
inc/powierzchnia.hh inc/przesz_prost.hh
	g++ ${CPPFLAGS} -o ${OBJ}/main.o src/main.cpp

${OBJ}/dron.o: src/dron.cpp inc/Dr3D_gnuplot_api.hh inc/Wektor.hh inc/dron.hh inc/bryla.hh inc/int_rysowania.hh inc/wirnik.hh inc/parametry_drona.hh \
src/def_szab.cpp inc/przeszkoda.hh
	g++ ${CPPFLAGS} -o ${OBJ}/dron.o src/dron.cpp

${OBJ}/bryla.o: src/bryla.cpp inc/Dr3D_gnuplot_api.hh inc/Wektor.hh inc/Macierz.hh inc/rozmiar.h inc/bryla.hh inc/int_rysowania.hh inc/parametry_drona.hh
	g++ ${CPPFLAGS} -o ${OBJ}/bryla.o src/bryla.cpp

${OBJ}/Dr3D_gnuplot_api.o: src/Dr3D_gnuplot_api.cpp inc/Dr3D_gnuplot_api.hh
	g++ ${CPPFLAGS} -o ${OBJ}/Dr3D_gnuplot_api.o src/Dr3D_gnuplot_api.cpp

Dr3D_gnuplot_api.hh: inc/Draw3D_api_interface.hh
	touch inc/Dr3D_gnuplot_api.hh

${OBJ}/def_szab.o: src/def_szab.cpp src/Wektor.cpp inc/Wektor.hh src/Macierz.cpp inc/Macierz.hh inc/rozmiar.h 
	g++ ${CPPFLAGS} -o ${OBJ}/def_szab.o src/def_szab.cpp

${OBJ}/int_rysowania.o: src/int_rysowania.cpp inc/int_rysowania.hh inc/Dr3D_gnuplot_api.hh
	g++ ${CPPFLAGS} -o ${OBJ}/int_rysowania.o src/int_rysowania.cpp

${OBJ}/powierzchnia.o: src/powierzchnia.cpp inc/powierzchnia.hh inc/int_rysowania.hh inc/Dr3D_gnuplot_api.hh inc/przeszkoda.hh
	g++ ${CPPFLAGS} -o ${OBJ}/powierzchnia.o src/powierzchnia.cpp

${OBJ}/wirnik.o: inc/wirnik.hh src/wirnik.cpp inc/Macierz.hh inc/bryla.hh inc/Wektor.hh inc/parametry_drona.hh
	g++ ${CPPFLAGS} -o ${OBJ}/wirnik.o src/wirnik.cpp

${OBJ}/przesz_prost.o: inc/przesz_prost.hh src/przesz_prost.cpp inc/bryla.hh inc/przeszkoda.hh
	g++ ${CPPFLAGS} -o ${OBJ}/przesz_prost.o src/przesz_prost.cpp


clear:
	rm main.out main.o Dr3D_gnuplot_api.o
