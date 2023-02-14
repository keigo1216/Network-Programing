CPPFLAGS = -I include #ヘッダファイルのパスを指定
VPATH = src lib
LIBS = readline.o str_echo.o str_cli.o sigchildwait.o

.PHONY: all
all: tcpserv01 tcpcli01 tcpcli04 clean

tcpserv01: tcpserv01.o ${LIBS}
	gcc -o $@ $^

tcpcli01: tcpcli01.o ${LIBS}
	gcc -o $@ $^

tcpcli04: tcpcli04.o ${LIBS}
	gcc -o $@ $^

%o: %c
	gcc -c ${CFLAGS} $< -o $@

.PHONY: clean
clean: 
	-rm *.o
