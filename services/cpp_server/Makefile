

CXX=g++

SRC_FILES=main.cc

OBJ_FILES=main.o
OBJ_DIR=objects

TARGET=Server
INCLUDE_DIR=include
LIB_DIR=lib

LIBS=-lnghttp2_asio -lboost_system -lssl -lcrypto -lnghttp2

TARGET_DIR=build
SRC_DIR=src

.PHONY: all clean certs

all: main

main: $(OBJ_FILES)
	$(CXX) -o $(TARGET_DIR)/$(TARGET) $(OBJ_DIR)/$(OBJ_FILES) -I$(INCLUDE_DIR)/ -I$(SRC_DIR)/server/ -L$(LIB_DIR)/ $(LIBS)

main.o: 
	$(CXX) -c $(SRC_DIR)/$(SRC_FILES) -o $(OBJ_DIR)/$(OBJ_FILES) -I$(INCLUDE_DIR)/

certs:
	rm -rf certs/*
	openssl ecparam -name prime256v1 -genkey -noout -out certs/ca.key
	openssl req -new -x509 -sha256 -config openssl.conf -key certs/ca.key -out certs/ca.crt -subj "/CN=RootCA"
	openssl ecparam -name prime256v1 -genkey -noout -out certs/server.key
	openssl req -new -sha256 -config openssl.conf -key certs/server.key -out certs/server.csr -subj "/CN=localhost"
	openssl x509 -req -in certs/server.csr -CA certs/ca.crt -CAkey certs/ca.key -CAcreateserial -out certs/server.crt -days 1000 -sha256
	openssl ecparam -name prime256v1 -genkey -noout -out certs/client.key
	openssl req -new -sha256 -config openssl.conf -key certs/client.key -out certs/client.csr -subj "/CN=client"
	openssl x509 -req -in certs/client.csr -CA certs/ca.crt -CAkey certs/ca.key -CAcreateserial -out certs/client.crt -days 1000 -sha256
	

clean:
	rm -rf objects/*.o
	rm build/Server
