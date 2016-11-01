main:
	lwi $r1 2h
	lwi $r2 2h
	lwi $r3 14h ; load 20
	lwi $r4 1h
	loop:
	mulu  $r1 $r1 $r2
	sub   $r3 $r2 $r3
	bne   loop $r3 $r0  ; loop
