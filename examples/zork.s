.name "zork"
.comment "I'M ALIIIIVE"

l2:		sti r1, %:live, %1 #6
		and r1, %0, r1		#7

live:	live %1		#5
		zjmp %:live	#3
