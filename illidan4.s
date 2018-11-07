.name		"Illidan Stormrage"
.comment	"I'm blind, not deaf"

sti r1, %:alive, %1

declare:
	ld %70, r2
	aff r2
	ld %111, r2
	aff r2
	ld %111, r2
	aff r2
	ld %108, r2
	aff r2

alive:
	live %42

index:
	ld %0, r3
	ld %128, r4
	ld %4, r5
	add r3, r4, r3
	sti r3, %:index, %2

copy:
	lldi %:declare, r7, r6
	zjmp %:declare
	sti r6, r3, r7
	add r5, r7, r7
	xor r16, r16, r16
	zjmp %:copy

