;unfitting operands
mov #1, #4r
add #1,  #43
sub #1, #45
lea #1, #4f
lea r5 , #1f

; illegal operands
W: mov illegal_label, r1
add W, 3 
bne W_ sf
sub W, !@
lea W, 3
bne B.3
.struct 3, "f

;extra text after command
not W, #3, 4  

; empty label
label:

;illegal numbers
mov #23a, r1
mov r1, #23a

;missing numbers
.data
.struct

;illegal comma
.data ,3

;illegal string
.string "
.struct 5,
.string 
.data
.struct
.string

;illegal label name
_!@+: hlt

;declaring an already defined label as external
 hello: hlt
 .extern hello

;defining label that already declared as external
.extern G
G: hlt
&^%$: .entry h
&^$#: .struct "342" , 3
#@$@#@: hlt
;b should be discarded
b: .extern c

;missing label after ".entry" \ ".extern"
.extern
.entry
