.name		"ffffffffffffffQAAaaaaaaaaaaadffffffffffffffQAAaaaaaaaaaaadffffffffffffffQAAaaaaaaaaaadffffffffffffffQAAaaaaaaaaadffffffffffffff"
.comment	"Little tester"

ld %-100, r2
sti r1, r2, %-500
sti r1, %:l, %1

l:
live %21
