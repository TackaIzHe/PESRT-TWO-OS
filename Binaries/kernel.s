	.file	"kernel.c"
	.text
	.globl	videoMem
	.section	.bss
	.align 4
	.type	videoMem, @object
	.size	videoMem, 4
videoMem:
	.zero	4
	.comm	intToChar,4,4
	.comm	second,8,8
	.comm	keyBuffer,256,32
	.text
	.globl	ticks
	.type	ticks, @function
ticks:
.LFB0:
	pushl	%ebp
.LCFI0:
	movl	%esp, %ebp
.LCFI1:
	pushl	%ebx
	subl	$20, %esp
.LCFI2:
	call	getTackt
	cltd
	movl	%eax, -16(%ebp)
	movl	%edx, -12(%ebp)
	call	getTackt
	cltd
	movl	%eax, -24(%ebp)
	movl	%edx, -20(%ebp)
.L4:
	call	getTackt
	cltd
	movl	%eax, -24(%ebp)
	movl	%edx, -20(%ebp)
	movl	-24(%ebp), %eax
	movl	-20(%ebp), %edx
	subl	-16(%ebp), %eax
	sbbl	-12(%ebp), %edx
	movl	8(%ebp), %ecx
	movl	%ecx, %ebx
	sarl	$31, %ebx
	cmpl	%ecx, %eax
	movl	%edx, %eax
	sbbl	%ebx, %eax
	jnc	.L7
	jmp	.L4
.L7:
	nop
	movl	-24(%ebp), %edx
	movl	-16(%ebp), %eax
	subl	%eax, %edx
	movl	%edx, %eax
	addl	$20, %esp
	popl	%ebx
.LCFI3:
	popl	%ebp
.LCFI4:
	ret
.LFE0:
	.size	ticks, .-ticks
	.globl	printf
	.type	printf, @function
printf:
.LFB1:
	pushl	%ebp
.LCFI5:
	movl	%esp, %ebp
.LCFI6:
	subl	$16, %esp
	cmpl	$0, 12(%ebp)
	jne	.L9
	movl	$15, 12(%ebp)
.L9:
	movl	$0, -4(%ebp)
	movl	videoMem, %eax
	movl	%eax, -8(%ebp)
	jmp	.L10
.L11:
	movl	-4(%ebp), %edx
	movl	8(%ebp), %eax
	addl	%eax, %edx
	movl	-8(%ebp), %eax
	movl	(%eax), %eax
	movl	%eax, %ecx
	movzbl	(%edx), %eax
	movb	%al, (%ecx)
	movl	-8(%ebp), %eax
	movl	(%eax), %eax
	leal	1(%eax), %edx
	movl	-8(%ebp), %eax
	movl	%edx, (%eax)
	movl	-8(%ebp), %eax
	movl	(%eax), %eax
	movl	12(%ebp), %edx
	movb	%dl, (%eax)
	movl	-8(%ebp), %eax
	movl	(%eax), %eax
	leal	1(%eax), %edx
	movl	-8(%ebp), %eax
	movl	%edx, (%eax)
	addl	$1, -4(%ebp)
.L10:
	movl	-4(%ebp), %edx
	movl	8(%ebp), %eax
	addl	%edx, %eax
	movzbl	(%eax), %eax
	testb	%al, %al
	jne	.L11
	nop
	leave
.LCFI7:
	ret
.LFE1:
	.size	printf, .-printf
	.globl	print
	.type	print, @function
print:
.LFB2:
	pushl	%ebp
.LCFI8:
	movl	%esp, %ebp
.LCFI9:
	subl	$24, %esp
	movl	$0, -12(%ebp)
	cmpl	$9, 8(%ebp)
	jg	.L13
	movl	intToChar, %edx
	movl	8(%ebp), %eax
	addl	%edx, %eax
	movl	%eax, -12(%ebp)
	pushl	$0
	leal	-12(%ebp), %eax
	pushl	%eax
	call	printf
	addl	$8, %esp
	jmp	.L15
.L13:
	movl	8(%ebp), %ecx
	movl	$1717986919, %edx
	movl	%ecx, %eax
	imull	%edx
	sarl	$2, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	sall	$2, %eax
	addl	%edx, %eax
	addl	%eax, %eax
	subl	%eax, %ecx
	movl	%ecx, %edx
	movl	intToChar, %eax
	addl	%edx, %eax
	movl	%eax, -12(%ebp)
	movl	8(%ebp), %ecx
	movl	$1717986919, %edx
	movl	%ecx, %eax
	imull	%edx
	sarl	$2, %edx
	movl	%ecx, %eax
	sarl	$31, %eax
	subl	%eax, %edx
	movl	%edx, %eax
	subl	$12, %esp
	pushl	%eax
	call	print
	addl	$16, %esp
	subl	$8, %esp
	pushl	$0
	leal	-12(%ebp), %eax
	pushl	%eax
	call	printf
	addl	$16, %esp
.L15:
	nop
	leave
.LCFI10:
	ret
.LFE2:
	.size	print, .-print
	.globl	clearScrin
	.type	clearScrin, @function
clearScrin:
.LFB3:
	pushl	%ebp
.LCFI11:
	movl	%esp, %ebp
.LCFI12:
	subl	$16, %esp
	movl	videoMem, %eax
	movl	%eax, -4(%ebp)
	jmp	.L17
.L18:
	movl	-4(%ebp), %eax
	movl	(%eax), %eax
	movb	$0, (%eax)
	movl	-4(%ebp), %eax
	movl	(%eax), %eax
	leal	-2(%eax), %edx
	movl	-4(%ebp), %eax
	movl	%edx, (%eax)
.L17:
	movl	-4(%ebp), %eax
	movl	(%eax), %eax
	cmpl	$753664, %eax
	jne	.L18
	nop
	leave
.LCFI13:
	ret
.LFE3:
	.size	clearScrin, .-clearScrin
	.globl	init
	.type	init, @function
init:
.LFB4:
	pushl	%ebp
.LCFI14:
	movl	%esp, %ebp
.LCFI15:
	subl	$8, %esp
	movl	videoMem, %eax
	movl	$753664, (%eax)
	movl	$48, intToChar
	movl	$-1486618625, second
	movl	$232830643, second+4
	call	_start
	nop
	leave
.LCFI16:
	ret
.LFE4:
	.size	init, .-init
	.section	.rodata
.LC0:
	.string	"Hello, World!!!"
	.text
	.globl	main
	.type	main, @function
main:
.LFB5:
	leal	4(%esp), %ecx
.LCFI17:
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
.LCFI18:
	movl	%esp, %ebp
	pushl	%ecx
.LCFI19:
	subl	$4, %esp
	call	init
	call	clearScrin
	subl	$8, %esp
	pushl	$10
	pushl	$.LC0
	call	printf
	addl	$16, %esp
	movl	$0, %eax
	movl	-4(%ebp), %ecx
.LCFI20:
	leave
.LCFI21:
	leal	-4(%ecx), %esp
.LCFI22:
	ret
.LFE5:
	.size	main, .-main
	.section	.eh_frame,"aw",@progbits
.Lframe1:
	.long	.LECIE1-.LSCIE1
.LSCIE1:
	.long	0
	.byte	0x3
	.string	""
	.byte	0x1
	.byte	0x7c
	.byte	0x8
	.byte	0xc
	.byte	0x4
	.byte	0x4
	.byte	0x88
	.byte	0x1
	.align 4
.LECIE1:
.LSFDE1:
	.long	.LEFDE1-.LASFDE1
.LASFDE1:
	.long	.LASFDE1-.Lframe1
	.long	.LFB0
	.long	.LFE0-.LFB0
	.byte	0x4
	.long	.LCFI0-.LFB0
	.byte	0xe
	.byte	0x8
	.byte	0x85
	.byte	0x2
	.byte	0x4
	.long	.LCFI1-.LCFI0
	.byte	0xd
	.byte	0x5
	.byte	0x4
	.long	.LCFI2-.LCFI1
	.byte	0x83
	.byte	0x3
	.byte	0x4
	.long	.LCFI3-.LCFI2
	.byte	0xc3
	.byte	0x4
	.long	.LCFI4-.LCFI3
	.byte	0xc5
	.byte	0xc
	.byte	0x4
	.byte	0x4
	.align 4
.LEFDE1:
.LSFDE3:
	.long	.LEFDE3-.LASFDE3
.LASFDE3:
	.long	.LASFDE3-.Lframe1
	.long	.LFB1
	.long	.LFE1-.LFB1
	.byte	0x4
	.long	.LCFI5-.LFB1
	.byte	0xe
	.byte	0x8
	.byte	0x85
	.byte	0x2
	.byte	0x4
	.long	.LCFI6-.LCFI5
	.byte	0xd
	.byte	0x5
	.byte	0x4
	.long	.LCFI7-.LCFI6
	.byte	0xc5
	.byte	0xc
	.byte	0x4
	.byte	0x4
	.align 4
.LEFDE3:
.LSFDE5:
	.long	.LEFDE5-.LASFDE5
.LASFDE5:
	.long	.LASFDE5-.Lframe1
	.long	.LFB2
	.long	.LFE2-.LFB2
	.byte	0x4
	.long	.LCFI8-.LFB2
	.byte	0xe
	.byte	0x8
	.byte	0x85
	.byte	0x2
	.byte	0x4
	.long	.LCFI9-.LCFI8
	.byte	0xd
	.byte	0x5
	.byte	0x4
	.long	.LCFI10-.LCFI9
	.byte	0xc5
	.byte	0xc
	.byte	0x4
	.byte	0x4
	.align 4
.LEFDE5:
.LSFDE7:
	.long	.LEFDE7-.LASFDE7
.LASFDE7:
	.long	.LASFDE7-.Lframe1
	.long	.LFB3
	.long	.LFE3-.LFB3
	.byte	0x4
	.long	.LCFI11-.LFB3
	.byte	0xe
	.byte	0x8
	.byte	0x85
	.byte	0x2
	.byte	0x4
	.long	.LCFI12-.LCFI11
	.byte	0xd
	.byte	0x5
	.byte	0x4
	.long	.LCFI13-.LCFI12
	.byte	0xc5
	.byte	0xc
	.byte	0x4
	.byte	0x4
	.align 4
.LEFDE7:
.LSFDE9:
	.long	.LEFDE9-.LASFDE9
.LASFDE9:
	.long	.LASFDE9-.Lframe1
	.long	.LFB4
	.long	.LFE4-.LFB4
	.byte	0x4
	.long	.LCFI14-.LFB4
	.byte	0xe
	.byte	0x8
	.byte	0x85
	.byte	0x2
	.byte	0x4
	.long	.LCFI15-.LCFI14
	.byte	0xd
	.byte	0x5
	.byte	0x4
	.long	.LCFI16-.LCFI15
	.byte	0xc5
	.byte	0xc
	.byte	0x4
	.byte	0x4
	.align 4
.LEFDE9:
.LSFDE11:
	.long	.LEFDE11-.LASFDE11
.LASFDE11:
	.long	.LASFDE11-.Lframe1
	.long	.LFB5
	.long	.LFE5-.LFB5
	.byte	0x4
	.long	.LCFI17-.LFB5
	.byte	0xc
	.byte	0x1
	.byte	0
	.byte	0x4
	.long	.LCFI18-.LCFI17
	.byte	0x10
	.byte	0x5
	.byte	0x2
	.byte	0x75
	.byte	0
	.byte	0x4
	.long	.LCFI19-.LCFI18
	.byte	0xf
	.byte	0x3
	.byte	0x75
	.byte	0x7c
	.byte	0x6
	.byte	0x4
	.long	.LCFI20-.LCFI19
	.byte	0xc
	.byte	0x1
	.byte	0
	.byte	0x4
	.long	.LCFI21-.LCFI20
	.byte	0xc5
	.byte	0x4
	.long	.LCFI22-.LCFI21
	.byte	0xc
	.byte	0x4
	.byte	0x4
	.align 4
.LEFDE11:
	.ident	"GCC: (GNU) 8.4.0"
