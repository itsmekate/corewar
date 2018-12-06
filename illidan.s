.name		"Illidan Stormrage"
.comment	"Remember when wings, hooves and horns were strange in Warcraft? Ah, the good old days"

start:

	sti r1, %:load_row, %1
	sti r1, %:load_fork, %1
	sti r1, %:load_live, %1
	sti r1, %:copy, %1
	ld %128, r3
	ld %2, r6
	ld %5, r7
	ld %0, r16

declare:
	ld %68, r2
	aff r2
	ld %105, r2
	aff r2
	ld %101, r2
	aff r2
	ld %44, r2
	aff r2
	ld %32, r2
	aff r2
	ld %102, r2
	aff r2
	ld %111, r2
	aff r2
	ld %111, r2
	aff r2
	ld %108, r2
	aff r2
	ld %10, r2
	aff r2

load_fork:
	live %42
	ld %655349, r4
	fork %:copy

load_row:
	live %42
	sub r3, r7, r3
	ld %190317571, r4
	fork %:copy

load_row2:
	add r3, r6, r3
	ld %67305472, r4
	fork %:copy

load_live:
	live %42
	sub r3, r6, r3
	sub r3, r7, r3
	ld %33554431, r4
	fork %:copy

load_live2:
	ld %1, r6
	add r3, r6, r3
	st r1, r4
	fork %:load_live

copy:
	live %42
	sti r4, r3, %64
	sti r4, r3, %256
	sti r4, r3, %500
	xor %11, r16, r16
	fork %:start
