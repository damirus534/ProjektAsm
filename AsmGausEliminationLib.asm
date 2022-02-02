.data

tablicaJednowymiarowa$ = 8
tablicaWynikow$ = 32

.code

AsmGausEliminationLib proc
$LoadRegistry:
        mov     QWORD PTR [rsp+32], r9                      ;loading tablica wynikow
        movq    xmm14, r8                                   ;loading ylength into xmm14 register
        movq    xmm15, rdx                                  ;loading xlength into xmm15 register
        mov     QWORD PTR [rsp+8], rcx                      ;loading tablica jednowymiarowa
        mov     r13, 0                                      ;setting 0 in r13 register 
        movq    xmm2, r13                                   ;loading my iterator into xmm2 register
        jmp     SHORT $1stLoop
$1stLoopInc:
        movq    rax, xmm2                                   ;moving my 1st iterator to rax register
        inc     rax                                         ;incrementing my 1st iterator
        movq    xmm2, rax                                   ;moving my incremented 1st iterator from rax register into xmm2 register
$1stLoop:
        movq    r15, xmm14                                  ;loading ylength to r15 register
        dec     r15                                         ;decrementing ylength but not in xmm14 register
        movq    r14, xmm2                                   ;moving my iterator to r14 register
        cmp     r14, r15                                    ;compairing iterator with ylength-1
        jge     $4thLoop                                    ;if ylength-1 is equal iterator we're jumping into 4th loop
        inc     r14                                         ;incrementing my iterator in r14 register
        movq    xmm3, r14                                   ;setting my 2nd iterator into xmm3 register
        jmp     SHORT $2ndLoop 
$2ndLoopInc:
        movq    rax, xmm3                                   ;setting my 2nd iterator from xmm3 register to rax register
        inc     rax                                         ;incrementing my 2nd iterator
        movq    xmm3, rax                                   ;setting my incremented 2nd iterator from rax register to xmm3 regisrer
$2ndLoop:
        movq    r14, xmm14                                  ;loading ylength to r14 register
        movq    r15, xmm3                                   ;loading 2nd iterator which is 1st iterator+1 into r15 register
        cmp     r15, r14                                    ;compairing 2nd iterator with yLength
        jge     $end1stLoop                                 ;if ylength is equal 2nd iterator we're jumping to end of 1st loop
        movaps  xmm4, xmm3                                  ;moving my 2nd iterator to xmm4
        pmullw  xmm4, xmm15                                 ;multiplying 2nd iterator with xLength [k*xLength]
        addss   xmm4, xmm2                                  ;adding to multiplication result the 1st iterator [k*xLength + i]
        movq    rax, xmm4                                   ;moving above result from xmm4 register to rax register
        movaps  xmm5, xmm2                                  ;moving to xmm5 my 1st iterator from xmm2
        pmullw  xmm5, xmm15                                 ;multiplying 1st iterator with xLength [i * xLength]
        paddw   xmm5, xmm2                                  ;adding to multiplication result the 1st iterator [i* xLength + i]
        movq    rcx, xmm5                                   ;moving above result from xmm5 register to rcx register
        mov     rdx, QWORD PTR tablicaJednowymiarowa$[rsp]  ;setting tablica jednowymiarowa to rdx register
        mov     r8, QWORD PTR tablicaJednowymiarowa$[rsp]   ;setting tablica jednowymiarowa to r8 register
        movss   xmm6, DWORD PTR [rdx+rax*4]                 ;moving my element from tablicaJednowymiarowa[k*xLength+i] to xmm6 register
        divss   xmm6, DWORD PTR [r8+rcx*4]                  ;dividing tablicaJednowymiarowa[k*xLength+i]/tablicaJednowymiarowa[i*xLength+i] and setting result to xmm6 register (ratio)
        mov     rsi, 0                                      ;moving 0 to rsi register
        movq    xmm8, rsi                                   ;moving above 0 to xmm8 and it's my 3rd iterator
        jmp     SHORT $3rdLoop
$3rdLoopInc:
        movq    rsi, xmm8                                   ;moving my 3rd iterator to rsi register
        inc     rsi                                         ;incrementing my 3rd iterator in rsi register
        movq    xmm8, rsi                                   ;moving my incremented 3rd iterator to xmm8 register from rsi
$3rdLoop:
        movq    r15, xmm15                                  ;moving xLength to r15 register
        movq    rsi, xmm8                                   ;moving my 3rd iterator to rsi register
        cmp     rsi, r15                                    ;compairing my 3rd iterator with xLength
        jg      $end2ndLoop                                 ;if 3rd iterator is higher than xLength jumping to end of 2nd loop
        movaps  xmm7, xmm3                                  ;moving my 2nd iterator to xmm7 register
        pmullw  xmm7, xmm15                                 ;multiplaying 2nd iterator with xLength [k* xLength]
        addss   xmm7, xmm8                                  ;adding to result of multplication the 3rd iterator [k* xLength + j]
        movq    rax, xmm7                                   ;moving above result to rax register
        movq    xmm9, xmm2                                  ;moving my 1st iterator to xmm9 register
        pmullw  xmm9, xmm15                                 ;multiplying 1st iterator with xLength
        addss   xmm9, xmm8                                  ;adding to result of multiplication the 3rd iterator [i*xLength + j]        
        movq    rcx, xmm9                                   ;moving above result to rcx register
        mov     rdx, QWORD PTR tablicaJednowymiarowa$[rsp]  ;moving tablica jednowymiarowa to rdx register
        movq    xmm11, xmm6                                 ;moving ratio to xmm11
        mulss   xmm11, DWORD PTR [rdx+rcx*4]                ;ratio * tablicajednowymiarowa[i * xLength +j]
        mov     rcx, QWORD PTR tablicaJednowymiarowa$[rsp]  ;moving tablica jednowymiarowa to rcx register
        movss   xmm10, DWORD PTR [rcx+rax*4]                ;moving element from tablicaJednowymiarowa[k* xLength + j] to xmm10 register
        subss   xmm10, xmm11                                ;tablicaJednowymiarowa[k*xLength + j] - ratio * tablicaJednowymiarowa[i *xLength +j]  
        movq    rax, xmm7                                   ;moving [k*xLength+j] to rax registry
        mov     rcx, QWORD PTR tablicaJednowymiarowa$[rsp]  ;setting tablicaJednowymiarowa to rcx register
        movss   DWORD PTR [rcx+rax*4], xmm10                ;setting data tablicaJednowymiarowa[k * xLength + j] = tablicaJednowymiarowa[k * xLength + j] - ratio * tablicaJednowymiarowa[i * xLength+ j]
        jmp     $3rdLoopInc
$end2ndLoop:
        jmp     $2ndLoopInc
$end1stLoop:
        jmp     $1stLoopInc
$4thLoop:
        movq    r15, xmm14                                  ;moving yLength to r15 register
        dec     r15                                         ;decrementing yLength in r15 register
        movq    xmm2, r15                                   ;setting my 4th iterator to xmm2 i=yLength -1
        jmp     SHORT $5thLoop
$Inc4thLoop:
        movq    r15, xmm2                                   ;moving my 4th iterator to r15 register
        dec     r15                                         ;decrementing 4th iterator
        movq    xmm2, r15                                   ;moving decremented 4th iterator to my xmm2 register
$5thLoop:
        movq    rax, xmm2                                   ;moving my 4th iterator to rax register
        cmp     rax, 0                                      ;compairing my 4th iterator with 0
        jl      $End4thLoop                                 ;if my 4th iterator is lower than 0 jump to end of 4th loop
        movss   xmm4, xmm2                                  ;moving 4th iterator to xmm4 register
        pmullw  xmm4, xmm15                                 ;multiplying 4th iterator with xLength
        addss   xmm4, xmm14                                 ;adding to multiplication result yLength [i *xLength +yLength]
        movq    rax, xmm4                                   ;moving above result to rax register
        movq    rcx, xmm2                                   ;moving 4th iterator to rcx register
        mov     rdx, QWORD PTR tablicaWynikow$[rsp]         ;setting tablicaWynikow to rdx register
        mov     r8, QWORD PTR tablicaJednowymiarowa$[rsp]   ;setting tablicaJednowymiarowa to r8 register
        movss   xmm5, DWORD PTR [r8+rax*4]                  ;setting element tablicaJednowymiarowa[l *xLength + yLength] to xmm5 register
        movss   DWORD PTR [rdx+rcx*4], xmm5                 ;setting element from xmm5 to tablicaWynikow[i]
        movq    r14, xmm2                                   ;moving my 4th iterator to r14 register
        inc     r14                                         ;incrementing my 4th iterator in r14 register
        movq    xmm3, r14                                   ;setting my 5th iterator to xmm3 j=i+1
        jmp     SHORT $Inside5thLoop
$Inc5thLoop:
        movq    rax, xmm3                                   ;moving my 5th iterator from xmm3 to rax register
        inc     rax                                         ;incrementing iterator in rax register
        movq    xmm3, rax                                   ;moving incremented iterator to xmm3 from rax register
$Inside5thLoop:
        movq    r14, xmm14                                  ;moving my yLength from to r14 register
        movq    rbx, xmm3                                   ;moving my 5th iterator from xmm3 to rbx register
        cmp     rbx, r14                                    ;compairing yLength with my 5th iterator
        jge     $Inside4thLoop                              ;if 5th iterator is equal yLength skip this loop
        movq    r14, xmm2                                   ;moving my 4th iterator from xmm2 to r14 register
        cmp     rbx, r14                                    ;my if function if(i != j)
        je      $end5thLoop                                 ;if above comparasion is false jump to end5thLoop
        movq    rax, xmm2                                   ;moving my 4th iterator from xmm2 to rax register
        movss   xmm6, xmm2                                  ;moving my 4th iterator from xmm2 to xmm6
        pmullw  xmm6, xmm15                                 ;multiplying 4th iterator with xLength  [i*xLength]
        addss   xmm6, xmm3                                  ;add to above multiplication my 5th iterator    [i*xLength+j]
        movq    rcx, xmm6                                   ;moving above result to rcx register
        movq    rdx, xmm3                                   ;moving 5th iterator to rdx register
        mov     r8, QWORD PTR tablicaJednowymiarowa$[rsp]   ;moving tablicaJednowymiarowa to r8 register
        mov     r9, QWORD PTR tablicaWynikow$[rsp]          ;moving tablicaWynikow to r9 register
        movss   xmm7, DWORD PTR [r8+rcx*4]                  ;moving element from TablicaJednowymiarowa[i*xLength + j] to xmm7 register
        mulss   xmm7, DWORD PTR [r9+rdx*4]                  ;multiply tablicaJednowymiarowa[i * xLength + j] * tablicaWynikow[j]       
        mov     rcx, QWORD PTR tablicaWynikow$[rsp]         ;move TavlicaWynikow to rcx register 
        movss   xmm8, DWORD PTR [rcx+rax*4]                 ;set TablicaWynikow[i] to xmm8
        subss   xmm8, xmm7                                  ;substract tablicaWynikow[i] - tablicaJednowymiarowa[i * xLength + j] * tablicaWynikow[j]
        movq    rax, xmm2                                   ;moving my 4th iterator to rax register
        mov     rcx, QWORD PTR tablicaWynikow$[rsp]         ;setting tablicaWynikow to rcx
        movss   DWORD PTR [rcx+rax*4], xmm8                 ;setting result: tablicaWynikow[i] = tablicaWynikow[i] - tablicaJednowymiarowa[i * xLength + j] * tablicaWynikow[j]
$end5thLoop:
        jmp     $Inc5thLoop
$Inside4thLoop:
        movq    rax, xmm2                                   ;moving 4th iterator to rax register
        movss   xmm9, xmm2                                  ;moving 4th iterator to xmm9 register
        pmullw  xmm9, xmm15                                 ;multiplying 4th iterator with xLength [i*xLength]
        addss   xmm9, xmm2                                  ;to multiplication result add 4th iterator [i*xLength+i]
        movq    rcx, xmm9                                   ;setting above result to rcx register
        mov     rdx, QWORD PTR tablicaWynikow$[rsp]         ;setting tablicaWinikow to rdx register
        mov     r8, QWORD PTR tablicaJednowymiarowa$[rsp]   ;setting tablicajednowymiarowa to r8 register
        movss   xmm10, DWORD PTR [rdx+rax*4]                ;moving element from tablicaWynikow[i] to xmm10 register
        divss   xmm10, DWORD PTR [r8+rcx*4]                 ;dividing tablicaWynikow[i] / tablicaJednowymiarowa[i * xLength + i]  
        movq    rax, xmm2                                   ;moving 4th iterator to rax register
        mov     rcx, QWORD PTR tablicaWynikow$[rsp]         ;setting tablicaWynikow to rcx register
        movss   DWORD PTR [rcx+rax*4], xmm10                ;setting into tablicaWynikow[i]=tablicaWynikow[i] / tablicaJednowymiarowa[i * xLength + i]
        jmp     $Inc4thLoop
$End4thLoop:                                 
ret     
AsmGausEliminationLib endp
end