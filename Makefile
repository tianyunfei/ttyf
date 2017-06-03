CFLAGS=-std=c++11 -Wno-unknown-pragmas -Wall

CFLAGS+= `pkg-config --cflags opencv`
LDFLAGS+=`pkg-config --libs opencv`

MXNET_ROOT=/home/ttt/mxnet

CFLAGS+= -I$(MXNET_ROOT)/include 
LDFLAGS+= $(MXNET_ROOT)/lib/libmxnet.so

attribute_predict: attribute_predict.o face_detect.o
	g++ -O3 -o attribute_predict attribute_predict.o face_detect.o $(LDFLAGS)

attribute_predict.o: attribute_predict.cc
	g++ -O3 -c attribute_predict.cc ${CFLAGS}
	
face_detect.o: face_detect.cc
	g++ -O3 -c face_detect.cc ${CFLAGS}
	
clean: 
	rm attribute_predict
	rm -f *.d *.o
