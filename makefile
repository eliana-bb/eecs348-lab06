primary:
	@g++ main.cpp -o main

run: primary
	@./main

clean:
	rm main