.PHONY:build run clean

SRC=${wildcard *.java}

build:$(SRC)
	javac $^

run:
	java TestThreadPool

clean:
	rm -f *.class
