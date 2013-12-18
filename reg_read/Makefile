nowin:
	gcc -o read-reg read_reg.c

read_reg:
	gcc -Wl,-subsystem,windows -o read-reg read_reg.c

other:
	gcc -mwindows -o read-reg read-reg.c

clean:
	@rm read-reg.exe

