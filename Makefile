assembler:
	@ gcc ./assembler.c -o assembler.exe

teste:
	./assembler.exe codigo.txt

clear:
	@ rm assembler.exe
	@ rm codigo.mem