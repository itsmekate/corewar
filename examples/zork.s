.name "zork"
.comment "I'M ALIIIIVE"

l2:		sti r1, 211, %5 #6
		and r1, %0, r1		#7

live:	live %1		#5
		zjmp %7	#3
