main:
	lwi   $r1 200h ; a
	lwi   $r2 0h   ; s
	lwi   $r3 ah   ; i
	lwi   $r5 4h   ; constant 4
	lwi   $r6 1h   ; constant 1
	loop:
	lw   $r1 $r4 0h  ; r4 = *(a + 0)
	add  $r2 $r2 $r4 ; s = s + r4 <=> s += *a
	add  $r1 $r1 $r5 ; a += 4
	sub  $r3 $r3 $r6 ; i++
	bne  -4h $r3 $r0
