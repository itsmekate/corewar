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
	lfork %:declare

copy:
	ld :alive, r3
	sti r3, r4, r5
	add r4, r5, r4
