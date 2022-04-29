run:
	gcc main.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o main
	./main

convert:
	gcc converter.c -o convert
	./convert -i ./songs/test.qua -o ./songs/test.vsrg
	rm ./convert

clean:
	rm main