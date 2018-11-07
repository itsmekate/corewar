.name		"Illidan Stormrage"
.comment	"I'm blind, not deaf"

sti r1, %:alive, %1
sti r1, %:copy, %1
sti r1, %:declare, %1

index:
	ld %4, r5
	ld %128, r3

declare:
	live %42
	ld %70, r2
	aff r2
	ld %111, r2
	aff r2
	ld %111, r2
	aff r2
	ld %108, r2
	aff r2
	fork %:declare

alive:
	live %42
	fork %:copy
	ld %0, r7
	fork %150

copy:
	live %42
	lldi %:alive, r7, r6
	zjmp %:jump
	sti r6, r3, r7
	add r5, r7, r7
	xor r16, r16, r16
	zjmp %:copy
	
jump:
	zjmp %107
