CC=g++
#CFLAG=-O3 -g -std=c++11 -flto
CFLAG=-O3 -g -std=c++11
AR=ar rcs
SRC=./src
INC=./include/quadtree
TMP=./.tmp
FILES=${TMP}/rect.o ${TMP}/quadtree.o ${TMP}/point.o \
			${TMP}/node.o ${TMP}/trapezium.o ${TMP}/node_accessor.o \
			${TMP}/node_pool.o ${TMP}/node_iterator.o \
			${TMP}/node_iterators.o ${TMP}/node_viewer.o \
			${TMP}/dynamic_node_list.o ${TMP}/quadtree_iterators.o \
			${TMP}/quadtree_active_iterators.o ${TMP}/evaluator.o

main.out:main.cpp ${TMP} libquadtree.a
	${CC} ${CFLAG} $< -o $@ -lquadtree -L.

all:create_dir libquadtree.a

.INTERMEDIATE:${FILES}

.PHONY: create_dir all clear test

${TMP}:
	@${MAKE} create_dir

create_dir:
	@if [ ! -d "${TMP}" ]; then \
		mkdir ${TMP}; \
  fi

clear: create_dir
	rm ${TMP} -r
	rm libquadtree.a

${TMP}/%.o : ${SRC}/%.cpp
	${CC} ${CFLAG} -c $< -o $@

libquadtree.a:${FILES}
	${AR} $@ $^

test:
	sudo perf record -g ./main.out -f 10000 --stack-depth 256 --call-graph dwarf
	sudo perf script | ./FlameGraph/stackcollapse-perf.pl | ./FlameGraph/flamegraph.pl > flame.svg
