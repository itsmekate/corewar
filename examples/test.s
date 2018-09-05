.name""
.comment""

l2:
		live %43
		sti r1, :live, %5	#6
		#and r1, %0, %:abc		#7

live:	live %-5, sad	#5
		zjmp %7	#3
# .name"sdf;sdfsdssdf;sdfsdssdf;sdfsdssdf;sdfsdssdf;sdfsdssdf;sdfsdssdf;sdfsdssdf;sdfsdssdf;sdfsdssdf;sdfsdssdf;sdfsdssdf;sdfsdssdf;sdfsdssdf;sdfsdssdf;sdfsdssdf;sdfsdssdf;sdfsdssdf;sdfsdssdf;sdfsdssdf;sdfsdssdf;sdfsdssdf;sdfsdssdf;sdfsdssdf;sdfsdssdf;sdfsduu"
# .comment"ad#sdfsdffdsf"


# .comment "adfdsf"

# .name "sdf"

#sti r1, %:live, %1,%:live
#sti r1, %:live

	  sti			r1   ,   	%:live
# live: