.name "zork"
.comment "I'M ALIIIIVE"

l2:
		live %1
		sti r1, :live, %5	#6
		and r1, %0, r1		#7

live:	live %-5	#5
		zjmp %7	#3
