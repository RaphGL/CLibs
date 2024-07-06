	.file	"maintest.c"
	.text
	.section	.rodata
.LC0:
	.string	"maintest.c"
.LC1:
	.string	"vec_is_empty(vector)"
	.align 8
.LC2:
	.string	"vec_len(vector) == 1 && vec_capacity(vector) == sizeof(void *)"
	.align 8
.LC3:
	.string	"vec_len(vector) == 2 && vec_capacity(vector) == sizeof(void *) * 2"
	.align 8
.LC4:
	.string	"vec_len(vector) == 8 && vec_capacity(vector) == sizeof(void *) * 8"
	.align 8
.LC5:
	.string	"*(int *)vec_get(vector, 2) == 3"
	.align 8
.LC6:
	.string	"*(int *)vec_get(vector, 7) == 8"
.LC7:
	.string	"vec_get(vector, 9) == NULL"
	.align 8
.LC8:
	.string	"*(int *)vec_pop(vector) == 8 && vec_len(vector) == 7"
.LC9:
	.string	"vec_len(vector) == 7"
	.align 8
.LC10:
	.string	"*(int *)vec_get(vector, 3) == 22"
.LC11:
	.string	"vec_len(vector) == 8"
	.align 8
.LC12:
	.string	"*(int *)vec_get(vector, 3) == 4"
	.align 8
.LC13:
	.string	"prelen + vec_len(vector) == vec_len(vector2)"
.LC14:
	.string	"Test passed."
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$40, %rsp
	.cfi_offset 3, -24
	call	vec_new@PLT
	movq	%rax, -32(%rbp)
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	vec_is_empty@PLT
	testb	%al, %al
	jne	.L2
	leaq	__PRETTY_FUNCTION__.0(%rip), %rax
	movq	%rax, %rcx
	movl	$7, %edx
	leaq	.LC0(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC1(%rip), %rax
	movq	%rax, %rdi
	call	__assert_fail@PLT
.L2:
	movq	-32(%rbp), %rax
	movl	$1, %esi
	movq	%rax, %rdi
	call	vec_push@PLT
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	vec_len@PLT
	cmpq	$1, %rax
	jne	.L3
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	vec_capacity@PLT
	cmpq	$8, %rax
	je	.L21
.L3:
	leaq	__PRETTY_FUNCTION__.0(%rip), %rax
	movq	%rax, %rcx
	movl	$10, %edx
	leaq	.LC0(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC2(%rip), %rax
	movq	%rax, %rdi
	call	__assert_fail@PLT
.L21:
	movq	-32(%rbp), %rax
	movl	$2, %esi
	movq	%rax, %rdi
	call	vec_push@PLT
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	vec_len@PLT
	cmpq	$2, %rax
	jne	.L5
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	vec_capacity@PLT
	cmpq	$16, %rax
	je	.L22
.L5:
	leaq	__PRETTY_FUNCTION__.0(%rip), %rax
	movq	%rax, %rcx
	movl	$13, %edx
	leaq	.LC0(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC3(%rip), %rax
	movq	%rax, %rdi
	call	__assert_fail@PLT
.L22:
	movq	-32(%rbp), %rax
	movl	$3, %esi
	movq	%rax, %rdi
	call	vec_push@PLT
	movq	-32(%rbp), %rax
	movl	$4, %esi
	movq	%rax, %rdi
	call	vec_push@PLT
	movq	-32(%rbp), %rax
	movl	$5, %esi
	movq	%rax, %rdi
	call	vec_push@PLT
	movq	-32(%rbp), %rax
	movl	$6, %esi
	movq	%rax, %rdi
	call	vec_push@PLT
	movq	-32(%rbp), %rax
	movl	$7, %esi
	movq	%rax, %rdi
	call	vec_push@PLT
	movq	-32(%rbp), %rax
	movl	$8, %esi
	movq	%rax, %rdi
	call	vec_push@PLT
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	vec_len@PLT
	cmpq	$8, %rax
	jne	.L7
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	vec_capacity@PLT
	cmpq	$64, %rax
	je	.L23
.L7:
	leaq	__PRETTY_FUNCTION__.0(%rip), %rax
	movq	%rax, %rcx
	movl	$21, %edx
	leaq	.LC0(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC4(%rip), %rax
	movq	%rax, %rdi
	call	__assert_fail@PLT
.L23:
	movq	-32(%rbp), %rax
	movl	$2, %esi
	movq	%rax, %rdi
	call	vec_get@PLT
	movl	(%rax), %eax
	cmpl	$3, %eax
	je	.L9
	leaq	__PRETTY_FUNCTION__.0(%rip), %rax
	movq	%rax, %rcx
	movl	$23, %edx
	leaq	.LC0(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC5(%rip), %rax
	movq	%rax, %rdi
	call	__assert_fail@PLT
.L9:
	movq	-32(%rbp), %rax
	movl	$7, %esi
	movq	%rax, %rdi
	call	vec_get@PLT
	movl	(%rax), %eax
	cmpl	$8, %eax
	je	.L10
	leaq	__PRETTY_FUNCTION__.0(%rip), %rax
	movq	%rax, %rcx
	movl	$24, %edx
	leaq	.LC0(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC6(%rip), %rax
	movq	%rax, %rdi
	call	__assert_fail@PLT
.L10:
	movq	-32(%rbp), %rax
	movl	$9, %esi
	movq	%rax, %rdi
	call	vec_get@PLT
	testq	%rax, %rax
	je	.L11
	leaq	__PRETTY_FUNCTION__.0(%rip), %rax
	movq	%rax, %rcx
	movl	$25, %edx
	leaq	.LC0(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC7(%rip), %rax
	movq	%rax, %rdi
	call	__assert_fail@PLT
.L11:
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	vec_pop@PLT
	movl	(%rax), %eax
	cmpl	$8, %eax
	jne	.L12
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	vec_len@PLT
	cmpq	$7, %rax
	je	.L24
.L12:
	leaq	__PRETTY_FUNCTION__.0(%rip), %rax
	movq	%rax, %rcx
	movl	$27, %edx
	leaq	.LC0(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC8(%rip), %rax
	movq	%rax, %rdi
	call	__assert_fail@PLT
.L24:
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	vec_len@PLT
	cmpq	$7, %rax
	je	.L14
	leaq	__PRETTY_FUNCTION__.0(%rip), %rax
	movq	%rax, %rcx
	movl	$29, %edx
	leaq	.LC0(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC9(%rip), %rax
	movq	%rax, %rdi
	call	__assert_fail@PLT
.L14:
	movq	-32(%rbp), %rax
	movl	$22, %edx
	movl	$3, %esi
	movq	%rax, %rdi
	call	vec_insert@PLT
	movq	-32(%rbp), %rax
	movl	$3, %esi
	movq	%rax, %rdi
	call	vec_get@PLT
	movl	(%rax), %eax
	cmpl	$22, %eax
	je	.L15
	leaq	__PRETTY_FUNCTION__.0(%rip), %rax
	movq	%rax, %rcx
	movl	$31, %edx
	leaq	.LC0(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC10(%rip), %rax
	movq	%rax, %rdi
	call	__assert_fail@PLT
.L15:
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	vec_len@PLT
	cmpq	$8, %rax
	je	.L16
	leaq	__PRETTY_FUNCTION__.0(%rip), %rax
	movq	%rax, %rcx
	movl	$32, %edx
	leaq	.LC0(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC11(%rip), %rax
	movq	%rax, %rdi
	call	__assert_fail@PLT
.L16:
	movq	-32(%rbp), %rax
	movl	$3, %esi
	movq	%rax, %rdi
	call	vec_remove@PLT
	movq	-32(%rbp), %rax
	movl	$3, %esi
	movq	%rax, %rdi
	call	vec_get@PLT
	movl	(%rax), %eax
	cmpl	$4, %eax
	je	.L17
	leaq	__PRETTY_FUNCTION__.0(%rip), %rax
	movq	%rax, %rcx
	movl	$35, %edx
	leaq	.LC0(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC12(%rip), %rax
	movq	%rax, %rdi
	call	__assert_fail@PLT
.L17:
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	vec_len@PLT
	cmpq	$7, %rax
	je	.L18
	leaq	__PRETTY_FUNCTION__.0(%rip), %rax
	movq	%rax, %rcx
	movl	$36, %edx
	leaq	.LC0(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC9(%rip), %rax
	movq	%rax, %rdi
	call	__assert_fail@PLT
.L18:
	call	vec_new@PLT
	movq	%rax, -24(%rbp)
	movq	-24(%rbp), %rax
	movl	$91, %esi
	movq	%rax, %rdi
	call	vec_push@PLT
	movq	-24(%rbp), %rax
	movl	$92, %esi
	movq	%rax, %rdi
	call	vec_push@PLT
	movq	-24(%rbp), %rax
	movl	$93, %esi
	movq	%rax, %rdi
	call	vec_push@PLT
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	vec_len@PLT
	movl	%eax, -36(%rbp)
	movq	-32(%rbp), %rdx
	movq	-24(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	vec_append@PLT
	movl	-36(%rbp), %eax
	movslq	%eax, %rbx
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	vec_len@PLT
	addq	%rax, %rbx
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	vec_len@PLT
	cmpq	%rax, %rbx
	je	.L19
	leaq	__PRETTY_FUNCTION__.0(%rip), %rax
	movq	%rax, %rcx
	movl	$44, %edx
	leaq	.LC0(%rip), %rax
	movq	%rax, %rsi
	leaq	.LC13(%rip), %rax
	movq	%rax, %rdi
	call	__assert_fail@PLT
.L19:
	movq	-32(%rbp), %rax
	movq	%rax, %rdi
	call	vec_free@PLT
	movq	-24(%rbp), %rax
	movq	%rax, %rdi
	call	vec_free@PLT
	leaq	.LC14(%rip), %rax
	movq	%rax, %rdi
	call	puts@PLT
	movl	$0, %eax
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.section	.rodata
	.type	__PRETTY_FUNCTION__.0, @object
	.size	__PRETTY_FUNCTION__.0, 5
__PRETTY_FUNCTION__.0:
	.string	"main"
	.ident	"GCC: (GNU) 12.2.0"
	.section	.note.GNU-stack,"",@progbits
