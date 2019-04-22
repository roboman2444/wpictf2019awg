_start:
jmp realstart
db "yeet"	; extra ya because the jmp is only 2 
realstart:

;mov rax, faggotshit
lea rax, [rel faggotshit]
;add rax, 0x30
mov rdi, "ripbilly"

dec rax
egghunt:
inc rax
mov rbx, [rax]
cmp rbx, rdi
jnz egghunt

add rax, 0x8

; ok, movie data is at rax

push rax

; lets prompt them

mov rax, 1
mov rdi, 0
lea rsi, [rel promptext]
mov rdx, 0x38	; length of prompttext, im too lazy to figure out how to nasm that
syscall


; read
sub rsp, 0x10
mov rax, 0
mov rdi, 1
mov rsi, rsp
mov rdx, 0x10
syscall

mov rbp, rsp


; time to pipe
sub rsp, 0x8
mov rax, 22
mov rdi, rsp
syscall

; ok lets fork

mov rax, 57
syscall
test rax, rax
jnz decryp

; we are child

;dup2
mov rax, 33
mov rdi, 0
mov edi, [rsp]
mov rsi, 0
syscall


;find envp
mov rdi, "SHELL=/bi"
mov rax, rsp
shellhunt:
inc rax
mov rbx, [rax]
cmp rbx, rdi
jnz shellhunt

;ok, pointer to SHELL= is at rax
; lets hunt for that ptr
mov rdx, rsp
shellptrhunt:
inc rdx
mov rbx, [rdx]
cmp rbx, rax
jnz shellptrhunt

;; todo search backwards for zeeeros, but...ehhh


;execve
mov rax, 59
;mov rdx, 0 ;;rdx should be set to envp start from last one
push rdx
lea rdi, [rel prog]
push 0
lea rsi, [rel arg]
push rsi
;;version that calls bash first?
;lea rsi, [rel arg2]
;push rsi
;lea rsi, [rel arg1]
;push rsi
push rdi
mov rsi, rsp
syscall


decryp:

; get pipe fd
mov rdi, 0
mov edi, [rsp+0x4]
add rsp, 0x8

;get pw bytes
pop r15	; first bytes
pop r14 ; second bytes

; better switcheroo
;xchg r15, r14

;get the egghaunt
;pop rsi
;sub rsp, 0x8 ; scratch space?

;get egghunt and make scratch space
; r12 version
mov r12, [rsp]
mov rsi, rsp


;rsp version
mov rsi, [rsp]
xchg rsp, rsi


writeloop:

;;; r12 version
;mov r13, [r12]
;add r12, 8
;xor r13, r15
;mov [rsi], r13
;xchg r15, r14

;;;rsp versoion
pop r13
xor r13, r15
mov [rsi], r13
xchg r15, r14


mov rdx, 0x8
mov rax, 1
syscall
;add rsi, 0x8
jmp writeloop



promptext db "Please enter the 16 byte password (not the flag u dummy)"

prog db "/usr/bin/mpv", 0
arg db "-", 0
;prog db "/bin/bash", 0
;arg1 db "-c", 0
;arg2 db "mpv -", 0

faggotshit:
dq 0, 0
;db "ripbilly"
