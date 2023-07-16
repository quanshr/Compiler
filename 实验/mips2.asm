.data
a:.space 4000
str_1:.asciiz "20231077\n"
str_2:.asciiz "20231077\n"
str_3:.asciiz ""
str_4:.asciiz "\n"
str_5:.asciiz "20231077\n"
str_6:.asciiz "20231077\n"
str_7:.asciiz "20231077\n"
str_8:.asciiz "20231077\n"
str_9:.asciiz "20231077\n"
str_10:.asciiz "20231077\n"
str_11:.asciiz "20231077\n"

.text
j main

li $9 5
sw $9 0
label_1:
sw $ra 0($sp)
subi $sp $sp 4
lw $9 4
sw $9 0($sp)
subi $sp $sp 4
lw $9 8
sw $9 0($sp)
subi $sp $sp 4
lw $9 12
sw $9 0($sp)
subi $sp $sp 4
lw $9 16
sw $9 0($sp)
subi $sp $sp 4
lw $9 20
sw $9 0($sp)
subi $sp $sp 4
sw $4 4
sw $5 8
sw $6 12
lw $10 4320
lw $9 4($10)
sw $9 4324
lw $9 4324
lw $10 4320
sw $9 16($10)
lw $10 4320
lw $9 8($10)
sw $9 4336
lw $10 4320
lw $9 16($10)
sw $9 4348
lw $10 4336
lw $11 4348
slt $9 $11 $10
sw $9 4336
lw $9 4336
beqz $9 label_5
j label_3
label_5:
j label_4
label_3:
lw $10 4320
lw $9 8($10)
sw $9 4360
lw $9 4360
lw $10 4320
sw $9 16($10)
label_4:
lw $10 4320
lw $9 12($10)
sw $9 4372
lw $10 4320
lw $9 16($10)
sw $9 4384
lw $10 4372
lw $11 4384
slt $9 $11 $10
sw $9 4372
lw $9 4372
beqz $9 label_8
j label_6
label_8:
j label_7
label_6:
lw $10 4320
lw $9 12($10)
sw $9 4396
lw $9 4396
lw $10 4320
sw $9 16($10)
label_7:
lw $10 4320
lw $9 16($10)
sw $9 4408
lw $25 4408
j label_2
label_2:
addi $sp $sp 4
lw $9 0($sp)
sw $9 20
addi $sp $sp 4
lw $9 0($sp)
sw $9 16
addi $sp $sp 4
lw $9 0($sp)
sw $9 12
addi $sp $sp 4
lw $9 0($sp)
sw $9 8
addi $sp $sp 4
lw $9 0($sp)
sw $9 4
addi $sp $sp 4
lw $ra 0($sp)
jr $ra
label_9:
sw $ra 0($sp)
subi $sp $sp 4
lw $9 24
sw $9 0($sp)
subi $sp $sp 4
lw $9 28
sw $9 0($sp)
subi $sp $sp 4
lw $9 32
sw $9 0($sp)
subi $sp $sp 4
lw $9 36
sw $9 0($sp)
subi $sp $sp 4
sw $4 24
sw $5 28
lw $10 4320
lw $9 24($10)
sw $9 4420
lw $9 4420
lw $10 4320
sw $9 32($10)
lw $10 4320
lw $9 28($10)
sw $9 4432
lw $10 4320
lw $9 32($10)
sw $9 4444
lw $10 4432
lw $11 4444
slt $9 $11 $10
sw $9 4432
lw $9 4432
beqz $9 label_13
j label_11
label_13:
j label_12
label_11:
lw $10 4320
lw $9 28($10)
sw $9 4456
lw $9 4456
lw $10 4320
sw $9 32($10)
label_12:
lw $10 4320
lw $9 32($10)
sw $9 4468
lw $25 4468
j label_10
label_10:
addi $sp $sp 4
lw $9 0($sp)
sw $9 36
addi $sp $sp 4
lw $9 0($sp)
sw $9 32
addi $sp $sp 4
lw $9 0($sp)
sw $9 28
addi $sp $sp 4
lw $9 0($sp)
sw $9 24
addi $sp $sp 4
lw $ra 0($sp)
jr $ra
label_14:
sw $ra 0($sp)
subi $sp $sp 4
lw $9 40
sw $9 0($sp)
subi $sp $sp 4
lw $9 44
sw $9 0($sp)
subi $sp $sp 4
lw $9 48
sw $9 0($sp)
subi $sp $sp 4
lw $9 52
sw $9 0($sp)
subi $sp $sp 4
lw $9 56
sw $9 0($sp)
subi $sp $sp 4
lw $9 60
sw $9 0($sp)
subi $sp $sp 4
sw $4 40
sw $5 44
sw $6 48
sw $7 52
lw $10 4320
lw $9 40($10)
sw $9 4480
lw $9 4480
lw $10 4320
sw $9 56($10)
lw $10 4320
lw $9 44($10)
sw $9 4492
lw $10 4320
lw $9 56($10)
sw $9 4504
lw $10 4492
lw $11 4504
slt $9 $11 $10
sw $9 4492
lw $9 4492
beqz $9 label_18
j label_16
label_18:
j label_17
label_16:
lw $10 4320
lw $9 44($10)
sw $9 4516
lw $9 4516
lw $10 4320
sw $9 56($10)
label_17:
lw $10 4320
lw $9 48($10)
sw $9 4528
lw $10 4320
lw $9 56($10)
sw $9 4540
lw $10 4528
lw $11 4540
slt $9 $11 $10
sw $9 4528
lw $9 4528
beqz $9 label_21
j label_19
label_21:
j label_20
label_19:
lw $10 4320
lw $9 48($10)
sw $9 4552
lw $9 4552
lw $10 4320
sw $9 56($10)
label_20:
j label_15
label_15:
addi $sp $sp 4
lw $9 0($sp)
sw $9 60
addi $sp $sp 4
lw $9 0($sp)
sw $9 56
addi $sp $sp 4
lw $9 0($sp)
sw $9 52
addi $sp $sp 4
lw $9 0($sp)
sw $9 48
addi $sp $sp 4
lw $9 0($sp)
sw $9 44
addi $sp $sp 4
lw $9 0($sp)
sw $9 40
addi $sp $sp 4
lw $ra 0($sp)
jr $ra
label_22:
sw $ra 0($sp)
subi $sp $sp 4
li $9 1
sw $9 4564
lw $25 4564
j label_23
label_23:
addi $sp $sp 4
lw $ra 0($sp)
jr $ra
label_24:
sw $ra 0($sp)
subi $sp $sp 4
label_25:
addi $sp $sp 4
lw $ra 0($sp)
jr $ra
label_26:
sw $ra 0($sp)
subi $sp $sp 4
lw $9 64
sw $9 0($sp)
subi $sp $sp 4
lw $9 68
sw $9 0($sp)
subi $sp $sp 4
lw $9 72
sw $9 0($sp)
subi $sp $sp 4
lw $9 76
sw $9 0($sp)
subi $sp $sp 4
lw $9 80
sw $9 0($sp)
subi $sp $sp 4
lw $9 84
sw $9 0($sp)
subi $sp $sp 4
lw $9 88
sw $9 0($sp)
subi $sp $sp 4
sw $4 64
li $9 0
sw $9 4568
lw $9 4568
lw $10 4320
sw $9 68($10)
li $9 0
sw $9 4572
lw $9 4572
lw $10 4320
sw $9 76($10)
li $9 0
sw $9 4576
lw $9 4576
lw $10 4320
sw $9 84($10)
label_28:
lw $10 4320
lw $9 68($10)
sw $9 4580
li $9 5
sw $9 4592
lw $10 4580
lw $11 4592
slt $9 $10 $11
sw $9 4580
lw $9 4580
beqz $9 label_31
j label_29
label_31:
j label_30
label_29:
label_32:
lw $10 4320
lw $9 76($10)
sw $9 4596
li $9 4
sw $9 4608
lw $10 4320
lw $9 68($10)
sw $9 4612
lw $10 4608
lw $11 4612
sub $9 $10 $11
sw $9 4608
lw $10 4596
lw $11 4608
slt $9 $10 $11
sw $9 4596
lw $9 4596
beqz $9 label_35
j label_33
label_35:
j label_34
label_33:
lw $10 4320
lw $9 76($10)
sw $9 4628
lw $10 4320
lw $9 64($10)
sw $9 4644
lw $10 4644
lw $11 4628
add $9 $10 $11
sw $9 4644
lw $10 4644
lw $9 0($10)
sw $9 4624
lw $10 4320
lw $9 76($10)
sw $9 4652
li $9 1
sw $9 4668
lw $10 4652
lw $11 4668
add $9 $10 $11
sw $9 4652
lw $10 4320
lw $9 64($10)
sw $9 4672
lw $10 4672
lw $11 4652
add $9 $10 $11
sw $9 4672
lw $10 4672
lw $9 0($10)
sw $9 4648
lw $10 4624
lw $11 4648
slt $9 $11 $10
sw $9 4624
lw $9 4624
beqz $9 label_38
j label_36
label_38:
j label_37
label_36:
lw $10 4320
lw $9 76($10)
sw $9 4680
lw $10 4320
lw $9 64($10)
sw $9 4696
lw $10 4696
lw $11 4680
add $9 $10 $11
sw $9 4696
lw $10 4696
lw $9 0($10)
sw $9 4676
lw $9 4676
lw $10 4320
sw $9 84($10)
lw $10 4320
lw $9 76($10)
sw $9 4700
lw $10 4320
lw $9 76($10)
sw $9 4716
li $9 1
sw $9 4732
lw $10 4716
lw $11 4732
add $9 $10 $11
sw $9 4716
lw $10 4320
lw $9 64($10)
sw $9 4736
lw $10 4736
lw $11 4716
add $9 $10 $11
sw $9 4736
lw $10 4736
lw $9 0($10)
sw $9 4712
lw $9 4712
lw $10 4700
sw $9 64($10)
lw $10 4320
lw $9 76($10)
sw $9 4740
li $9 1
sw $9 4752
lw $10 4740
lw $11 4752
add $9 $10 $11
sw $9 4740
lw $10 4320
lw $9 84($10)
sw $9 4756
lw $9 4756
lw $10 4740
sw $9 64($10)
label_37:
lw $10 4320
lw $9 76($10)
sw $9 4768
li $9 1
sw $9 4780
lw $10 4768
lw $11 4780
add $9 $10 $11
sw $9 4768
lw $9 4768
lw $10 4320
sw $9 76($10)
j label_32
label_34:
li $9 0
sw $9 4784
lw $9 4784
lw $10 4320
sw $9 76($10)
lw $10 4320
lw $9 68($10)
sw $9 4788
li $9 1
sw $9 4800
lw $10 4788
lw $11 4800
add $9 $10 $11
sw $9 4788
lw $9 4788
lw $10 4320
sw $9 68($10)
j label_28
label_30:
li $9 0
sw $9 4808
lw $10 4320
lw $9 64($10)
sw $9 4816
lw $10 4816
lw $11 4808
add $9 $10 $11
sw $9 4816
lw $10 4816
lw $9 0($10)
sw $9 4804
lw $25 4804
j label_27
label_27:
addi $sp $sp 4
lw $9 0($sp)
sw $9 88
addi $sp $sp 4
lw $9 0($sp)
sw $9 84
addi $sp $sp 4
lw $9 0($sp)
sw $9 80
addi $sp $sp 4
lw $9 0($sp)
sw $9 76
addi $sp $sp 4
lw $9 0($sp)
sw $9 72
addi $sp $sp 4
lw $9 0($sp)
sw $9 68
addi $sp $sp 4
lw $9 0($sp)
sw $9 64
addi $sp $sp 4
lw $ra 0($sp)
jr $ra

main:
li $9 4
sw $9 92
li $9 5
sw $9 96
li $9 6
sw $9 100
li $9 8
sw $9 104
li $9 9
sw $9 108
li $9 3
sw $9 112
li $9 0
sw $9 116
li $9 1
sw $9 120
li $9 1
sw $9 124
li $9 2
sw $9 128
li $9 2
sw $9 132
li $9 8
sw $9 4820
lw $9 4820
lw $10 4320
sw $9 136($10)
li $9 7
sw $9 4824
lw $9 4824
lw $10 4320
sw $9 140($10)
li $9 6
sw $9 4828
lw $9 4828
lw $10 4320
sw $9 144($10)
li $9 5
sw $9 4832
lw $9 4832
lw $10 4320
sw $9 148($10)
li $9 4
sw $9 4836
lw $9 4836
lw $10 4320
sw $9 152($10)
li $9 9
sw $9 4840
lw $9 4840
lw $10 4320
sw $9 200($10)
li $9 10
sw $9 4844
lw $9 4844
lw $10 4320
sw $9 208($10)
li $9 11
sw $9 4848
lw $9 4848
lw $10 4320
sw $9 216($10)
li $9 1
sw $9 4852
lw $9 4852
lw $10 4320
sw $9 224($10)
li $9 9
sw $9 4856
lw $9 4856
lw $10 4320
sw $9 232($10)
li $9 19
sw $9 4860
lw $9 4860
lw $10 4320
sw $9 240($10)
li $9 1
sw $9 4864
lw $9 4864
lw $10 4320
sw $9 248($10)
li $9 1
sw $9 4868
lw $9 4868
lw $10 4320
sw $9 252($10)
li $9 2
sw $9 4872
lw $9 4872
lw $10 4320
sw $9 256($10)
li $9 2
sw $9 4876
lw $9 4876
lw $10 4320
sw $9 260($10)
li $9 0
sw $9 4880
lw $9 4880
lw $10 4320
sw $9 280($10)
li $v0 5
syscall
lw $9 4320
sw $v0 176($9)
li $9 3
sw $9 4888
lw $9 4888
move $4 $9
li $9 4
sw $9 4892
lw $9 4892
move $5 $9
li $9 5
sw $9 4896
lw $9 4896
move $6 $9
jal label_1
sw $25 4884
lw $9 4884
lw $10 4320
sw $9 288($10)
lw $9 4320
lw $4 136($9)
jal label_26
sw $25 4900
lw $9 4900
lw $10 4320
sw $9 296($10)
li $9 3
sw $9 4908
lw $9 4908
move $4 $9
li $9 4
sw $9 4912
lw $9 4912
move $5 $9
jal label_9
sw $25 4904
lw $9 4904
lw $10 4320
sw $9 304($10)
li $9 1
sw $9 4916
lw $10 4320
lw $11 4916
sub $9 $10 $11
sw $9 4916
lw $9 4916
lw $10 4320
sw $9 312($10)
li $9 1
sw $9 4920
li $v0 2
lw $9 4920
mult $9 $v0
mflo $10
sw $10 4920
li $9 1
sw $9 4924
lw $10 4920
lw $11 4924
add $9 $10 $11
sw $9 4920
li $9 7
sw $9 4928
lw $9 4928
lw $10 4920
sw $9 248($10)
li $9 1
sw $9 4932
li $9 9
sw $9 4936
lw $9 4936
lw $10 4932
sw $9 280($10)
li $9 1
sw $9 4940
li $9 1
sw $9 4948
li $9 1
sw $9 4952
li $v0 2
lw $9 4948
mult $9 $v0
mflo $10
sw $10 4948
lw $10 4948
lw $11 4952
add $9 $10 $11
sw $9 4948
lw $10 4948
lw $9 248($10)
sw $9 4944
lw $9 4944
lw $10 4940
sw $9 280($10)
li $9 1
sw $9 4956
li $v0 2
lw $9 4956
mult $9 $v0
mflo $10
sw $10 4956
li $9 1
sw $9 4960
lw $10 4956
lw $11 4960
add $9 $10 $11
sw $9 4956
li $9 99
sw $9 4964
lw $9 4964
lw $10 4956
sw $9 248($10)
li $9 1
sw $9 4972
li $9 1
sw $9 4976
li $v0 2
lw $9 4972
mult $9 $v0
mflo $10
sw $10 4972
lw $10 4972
lw $11 4976
add $9 $10 $11
sw $9 4972
lw $10 4972
lw $9 248($10)
sw $9 4968
li $9 99
sw $9 4980
lw $10 4968
lw $11 4980
slt $9 $10 $11
slt $12 $11 $10
nor $t9 $9 $12
sw $9 4968
lw $9 4968
beqz $9 label_42
j label_40
label_42:
j label_41
label_40:
label_41:
li $9 1
sw $9 4988
li $9 1
sw $9 4992
li $v0 2
lw $9 4988
mult $9 $v0
mflo $10
sw $10 4988
lw $10 4988
lw $11 4992
add $9 $10 $11
sw $9 4988
lw $10 4988
lw $9 248($10)
sw $9 4984
li $9 98
sw $9 4996
lw $10 4984
lw $11 4996
slt $9 $10 $11
slt $12 $11 $10
nor $t9 $9 $12
sw $9 4984
lw $9 4984
beqz $9 label_45
j label_43
label_45:
j label_44
label_43:
li $9 3
sw $9 5000
label_44:
lw $10 4320
lw $9 92($10)
sw $9 5004
li $9 4
sw $9 5016
lw $10 5004
lw $11 5016
add $9 $10 $11
sw $9 5004
lw $10 4320
lw $9 176($10)
sw $9 5020
li $9 4
sw $9 5032
lw $10 5020
lw $11 5032
sub $9 $10 $11
sw $9 5020
lw $10 5004
lw $11 5020
slt $9 $10 $11
xori $9 $9 1
sw $9 5004
lw $9 5004
beqz $9 label_48
lw $10 4320
lw $9 176($10)
sw $9 5004
li $9 4
sw $9 5044
lw $10 5004
lw $11 5044
mult $10 $11
mflo $9
sw $9 5004
lw $10 4320
lw $9 96($10)
sw $9 5048
li $9 60
sw $9 5060
lw $10 5048
lw $11 5060
mult $10 $11
mflo $9
sw $9 5048
lw $10 5004
lw $11 5048
slt $9 $11 $10
xori $9 $9 1
sw $9 5004
lw $9 5004
beqz $9 label_48
lw $10 4320
lw $9 176($10)
sw $9 5004
li $9 5
sw $9 5072
lw $10 5004
lw $11 5072
slt $9 $11 $10
sw $9 5004
lw $9 5004
beqz $9 label_48
j label_46
label_48:
lw $10 4320
lw $9 176($10)
sw $9 5004
li $9 4
sw $9 5084
lw $10 5004
lw $11 5084
div $10 $11
mflo $9
sw $9 5004
li $9 3
sw $9 5088
lw $10 5004
lw $11 5088
slt $9 $10 $11
sw $9 5004
lw $9 5004
beqz $9 label_49
j label_46
label_49:
lw $10 4320
lw $9 176($10)
sw $9 5004
li $9 3
sw $9 5100
lw $10 5004
lw $11 5100
div $10 $11
mfhi $9
sw $9 5004
li $9 1
sw $9 5104
lw $10 5004
lw $11 5104
slt $9 $10 $11
slt $12 $11 $10
nor $t9 $9 $12
sw $9 5004
lw $9 5004
beqz $9 label_50
j label_46
label_50:
lw $10 4320
lw $9 176($10)
sw $9 5004
li $9 1
sw $9 5116
lw $10 5004
lw $11 5116
sub $9 $10 $11
sw $9 5004
li $9 8
sw $9 5120
lw $10 5004
lw $11 5120
slt $9 $10 $11
slt $12 $11 $10
or $t9 $9 $12
sw $9 5004
lw $9 5004
beqz $9 label_51
j label_46
label_51:
lw $10 4320
lw $9 176($10)
sw $9 5004
li $9 40
sw $9 5136
lw $9 5136
move $4 $9
li $9 50
sw $9 5140
lw $9 5140
move $5 $9
li $9 1
sw $9 5148
li $9 1
sw $9 5152
li $v0 2
lw $9 5148
mult $9 $v0
mflo $10
sw $10 5148
lw $10 5148
lw $11 5152
add $9 $10 $11
sw $9 5148
lw $10 5148
lw $9 248($10)
sw $9 5144
lw $9 5144
move $6 $9
jal label_1
sw $25 5132
lw $10 5004
lw $11 5132
slt $9 $10 $11
sw $9 5004
lw $9 5004
beqz $9 label_52
j label_46
label_52:
lw $10 4320
lw $9 312($10)
sw $9 5004
lw $10 4320
lw $11 5004
slt $9 $10 $11
slt $12 $11 $10
or $t9 $9 $12
sw $9 5004
lw $9 5004
beqz $9 label_53
j label_46
label_53:
lw $10 4320
lw $9 312($10)
sw $9 5004
lw $10 4320
lw $11 5004
sub $9 $10 $11
sw $9 5004
lw $9 5004
beqz $9 label_54
j label_46
label_54:
lw $10 4320
lw $9 312($10)
sw $9 5004
lw $10 4320
lw $11 5004
add $9 $10 $11
sw $9 5004
lw $9 5004
beqz $9 label_55
j label_46
label_55:
jal label_22
sw $25 5004
lw $9 5004
beqz $9 label_56
j label_46
label_56:
j label_47
label_46:
li $v0 4
la $4 str_1
syscall
j label_57
label_47:
li $9 0
sw $9 5180
lw $9 5180
lw $10 4320
sw $9 288($10)
label_58:
lw $10 4320
lw $9 288($10)
sw $9 5184
li $9 6
sw $9 5196
lw $10 5184
lw $11 5196
slt $9 $10 $11
sw $9 5184
lw $9 5184
beqz $9 label_61
j label_59
label_61:
j label_60
label_59:
lw $10 4320
lw $9 288($10)
sw $9 5200
li $9 2
sw $9 5212
lw $10 5200
lw $11 5212
slt $9 $10 $11
slt $12 $11 $10
nor $t9 $9 $12
sw $9 5200
lw $9 5200
beqz $9 label_64
j label_62
label_64:
j label_63
label_62:
j label_60
label_63:
lw $10 4320
lw $9 288($10)
sw $9 5216
li $9 3
sw $9 5228
lw $10 5216
lw $11 5228
slt $9 $10 $11
slt $12 $11 $10
nor $t9 $9 $12
sw $9 5216
lw $9 5216
beqz $9 label_67
j label_65
label_67:
j label_66
label_65:
lw $10 4320
lw $9 288($10)
sw $9 5232
li $9 1
sw $9 5244
lw $10 5232
lw $11 5244
add $9 $10 $11
sw $9 5232
lw $9 5232
lw $10 4320
sw $9 288($10)
j label_58
label_66:
lw $10 4320
lw $9 288($10)
sw $9 5248
li $9 1
sw $9 5260
lw $10 5248
lw $11 5260
add $9 $10 $11
sw $9 5248
lw $9 5248
lw $10 4320
sw $9 288($10)
j label_58
label_60:
label_57:
li $v0 4
la $4 str_2
syscall
li $v0 4
la $4 str_3
syscall
lw $10 4320
lw $9 176($10)
sw $9 5264
li $v0 1
lw $4 5264
syscall
li $v0 4
la $4 str_4
syscall
li $v0 4
la $4 str_5
syscall
li $v0 4
la $4 str_6
syscall
li $v0 4
la $4 str_7
syscall
li $v0 4
la $4 str_8
syscall
li $v0 4
la $4 str_9
syscall
li $v0 4
la $4 str_10
syscall
li $v0 4
la $4 str_11
syscall
li $9 0
sw $9 5276
lw $25 5276
j label_39
label_39:
li $v0 10
syscall