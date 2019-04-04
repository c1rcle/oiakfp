.section .text
.global addBytes
.type addBytes, @function

addBytes:
    pushl %ebp
    movl %esp, %ebp
    movl 8(%ebp), %eax
    movl 12(%ebp), %ebx
    movl 16(%ebp), %edx
    xorl %ecx, %ecx
    movl (%eax,%ecx,4), %esi
    addl %esi, (%ebx,%ecx,4)
    incl %ecx
    jmp addSecondDoubleWord
    addNextDoubleWord:
    popfl
    addSecondDoubleWord:
    movl (%eax,%ecx,4), %esi
    adcl %esi, (%ebx,%ecx,4)
    incl %ecx
    pushfl
    cmpl %edx, %ecx
    jb addNextDoubleWord
    popfl
    setc carryFlagStatus
    xorl %eax, %eax
    movl %ebp, %esp
    popl %ebp
    ret
