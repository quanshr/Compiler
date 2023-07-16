.data
a:.space 200000
str_1:.asciiz " "
str_2:.asciiz "\n"
str_3:.asciiz ""
str_4:.asciiz "\n"

.text
la $fp a

li $9 1
sw $9 0($fp)
subiu $sp $sp 200000
j label_0


label_1:
lw $9 0($fp)
sw $9 4($sp)
la $a0 str_1
li $v0 4
syscall
lw $9 4($sp)
move $a0 $9
li $v0 1
syscall
la $a0 str_2
li $v0 4
syscall
lw $9 0($fp)
sw $9 8($sp)
li $9 1
sw $9 12($sp)
lw $9 8($sp)
lw $10 12($sp)
add $11 $9 $10
sw $11 8($sp)
lw $9 8($sp)
sw $9 0($fp)
li $9 1
sw $9 16($sp)
lw $20 16($sp)
jr $ra
jr $ra

label_0:
sw $ra 0($sp)
subi $sp $sp 20
jal label_1

addi $sp $sp 20
lw $ra 0($sp)
sw $20 8($sp)
sw $ra 0($sp)
subi $sp $sp 20
jal label_1

addi $sp $sp 20
lw $ra 0($sp)
sw $20 12($sp)
li $9 11
sw $9 4($sp)
li $9 22
sw $9 16($sp)
lw $9 4($sp)
lw $10 16($sp)
mult $9 $10
mflo $11
sw $11 4($sp)
li $9 33
sw $9 20($sp)
lw $9 4($sp)
lw $10 20($sp)
div $9 $10
mflo $11
sw $11 4($sp)
li $9 44
sw $9 24($sp)
lw $9 4($sp)
lw $10 24($sp)
div $9 $10
mfhi $11
sw $11 4($sp)
li $9 55
sw $9 28($sp)
lw $9 4($sp)
lw $10 28($sp)
add $11 $9 $10
sw $11 4($sp)
li $9 66
sw $9 32($sp)
lw $9 4($sp)
lw $10 32($sp)
sub $11 $9 $10
sw $11 4($sp)
li $9 77
sw $9 36($sp)
li $9 0
lw $10 36($sp)
sub $11 $9 $10
sw $11 36($sp)
lw $9 4($sp)
lw $10 36($sp)
add $11 $9 $10
sw $11 4($sp)
li $9 88
sw $9 40($sp)
li $9 0
lw $10 40($sp)
add $11 $9 $10
sw $11 40($sp)
lw $9 4($sp)
lw $10 40($sp)
sub $11 $9 $10
sw $11 4($sp)
lw $9 12($sp)
sw $9 44($sp)
lw $9 4($sp)
lw $10 44($sp)
add $11 $9 $10
sw $11 4($sp)
lw $9 0($fp)
sw $9 48($sp)
la $a0 str_3
li $v0 4
syscall
lw $9 48($sp)
move $a0 $9
li $v0 1
syscall
la $a0 str_4
li $v0 4
syscall
li $v0 10
syscall
li $v0 10
syscall