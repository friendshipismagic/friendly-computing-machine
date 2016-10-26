main:
	lwi $r1 2h
	lwi $r2 14h ; load 20
	lwi $r3 1h
	loop:
	mulu  $r1 $r1 $r2
	sub   $r2 $r2 $r3
	bne   -2h $r2 $r0  ; loop
