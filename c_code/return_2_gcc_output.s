    .section        .text.startup,"ax",@progbits
    .p2align 4,,15
    .globl  main
    .type   main, @function
main:
    movl    $2, %eax
    ret
    .size   main, .-main
    .ident  "GCC: (GNU) 4.8.5 20150623 (Red Hat 4.8.5-39)"
    .section        .note.GNU-stack,"",@progbits