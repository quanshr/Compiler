	=const 6 7 0
	- 6 0 6
	def 9 0 300
	def 10 0 2
	=const 10001 2 0
	=const 10002 0 0
	[]= 10 10002 10001
	=const 10004 -9 0
	=const 10005 1 0
	[]= 10 10005 10004
	jump 0 0 0
	outpara 16 1 0
	= 17 16 0
	printstr 1 0 0
	printint 17 0 0
	printstr 2 0 0
	= 18 16 0
	=const 19 0 0
	> 18 18 19
	beqz 18 4 0
	jump 2 0 0
label_4
	jump 3 0 0
label_2
	= 22 16 0
	=const 23 1 0
	- 22 22 23
	inpara 22 1 0
	jumptofunc 15 0 0
	outres 21 0 0
	= 20 16 0
	= 24 21 0
	* 20 20 24
	=const 25 1 0
	- 20 20 25
	inres 20 0 0
	return 0 0 0
	jump 5 0 0
label_3
	= 26 16 0
	=const 27 1 0
	- 26 26 27
	inres 26 0 0
	return 0 0 0
label_5
	=const 28 0 0
	inres 28 0 0
	return 0 0 0
	return 0 0 0
	outpara 30 1 0
	= 31 30 0
	printstr 3 0 0
	printint 31 0 0
	printstr 4 0 0
	= 32 30 0
	=const 33 0 0
	< 32 32 33
	beqz 32 9 0
	jump 7 0 0
label_9
	jump 8 0 0
label_7
	=const 34 1 0
	- 34 0 34
	inres 34 0 0
	return 0 0 0
	jump 10 0 0
label_8
	= 37 30 0
	=const 38 1 0
	- 37 37 38
	inpara 37 1 0
	jumptofunc 29 0 0
	outres 36 0 0
	= 40 30 0
	inpara 40 1 0
	jumptofunc 15 0 0
	outres 39 0 0
	= 35 36 0
	= 41 39 0
	+ 35 35 41
	inres 35 0 0
	return 0 0 0
label_10
	=const 42 0 0
	inres 42 0 0
	return 0 0 0
	return 0 0 0
	outpara 44 1 0
	outpara 45 2 0
	outpara 46 3 0
	= 47 44 0
	=const 48 1 0
	- 47 47 48
	= 44 47 0
	=const 50 0 0
	[] 49 45 50
	=const 51 1 0
	- 49 49 51
	=const 52 0 0
	[]= 45 52 49
	=const 54 0 0
	=const 55 0 0
	=const 56 1 0
	* 56 54 56
	+ 56 56 55
	[] 53 46 56
	=const 57 1 0
	- 53 53 57
	=const 58 0 0
	=const 59 0 0
	=const 60 1 0
	* 60 58 60
	+ 60 60 59
	[]= 46 60 53
	return 0 0 0
	return 0 0 0
	return 0 0 0
	return 0 0 0
label_0
	def 64 1 9
	def 65 1 2
	=const 10007 1 0
	=const 10008 0 0
	[]= 65 10008 10007
	=const 10009 5 0
	=const 10010 1 0
	[]= 65 10010 10009
	getint 10011 0 0
	getint 10013 0 0
	getint 10015 0 0
	=const 10020 0 0
	[]= 65 10020 10015
	printstr 5 0 0
	inpara 10011 1 0
	jumptofunc 15 0 0
	outres 10022 0 0
	inpara 10013 1 0
	jumptofunc 15 0 0
	outres 10025 0 0
	=const 10027 0 0
	inpara 10027 1 0
	jumptofunc 15 0 0
	outres 10028 0 0
	inpara 10028 1 0
	jumptofunc 15 0 0
	outres 10030 0 0
	printint 10022 0 0
	printstr 7 0 0
	printint 10025 0 0
	printstr 8 0 0
	printint 10030 0 0
	printstr 9 0 0
	=const 10036 0 0
	[] 10037 65 10036
	inpara 10037 1 0
	jumptofunc 29 0 0
	outres 10038 0 0
	inpara 10038 1 0
	jumptofunc 29 0 0
	outres 10040 0 0
	=const 10042 1 0
	+ 10043 10042 10040
	inpara 10043 1 0
	jumptofunc 29 0 0
	outres 10044 0 0
	printint 10044 0 0
	printstr 11 0 0
	=const 10047 0 0
	[] 10048 9 10047
	=const 10053 0 0
	[] 10054 65 10053
	printstr 12 0 0
	printint 10013 0 0
	printstr 13 0 0
	printint 10048 0 0
	printstr 14 0 0
	printint 10054 0 0
	printstr 15 0 0
	= 10056 9 0
	inpara 10013 1 0
	inpara 10056 2 0
	inpara 65 3 0
	jumptofunc 43 0 0
	=const 10059 0 0
	[] 10060 9 10059
	=const 10065 0 0
	[] 10066 65 10065
	printstr 16 0 0
	printint 10013 0 0
	printstr 17 0 0
	printint 10060 0 0
	printstr 18 0 0
	printint 10066 0 0
	printstr 19 0 0
label_14
	jump 15 0 0
	jump 16 0 0
label_15
	jump 20 0 0
	jump 18 0 0
label_20
	jump 19 0 0
label_18
	jump 14 0 0
label_19
	printstr 20 0 0
label_21
	jump 22 0 0
	jump 23 0 0
label_22
	jump 27 0 0
	jump 25 0 0
label_27
	jump 26 0 0
label_25
	jump 21 0 0
label_26
	printstr 21 0 0
label_28
	jump 29 0 0
	jump 30 0 0
label_29
	jump 34 0 0
	jump 32 0 0
label_34
	jump 33 0 0
label_32
	jump 28 0 0
label_33
	printstr 22 0 0
label_35
	jump 36 0 0
	jump 37 0 0
label_36
	jump 41 0 0
	jump 39 0 0
label_41
	jump 40 0 0
label_39
	jump 35 0 0
label_40
	printstr 23 0 0
label_42
	jump 43 0 0
	jump 44 0 0
label_43
	jump 48 0 0
	jump 46 0 0
label_48
	jump 47 0 0
label_46
	jump 42 0 0
	jump 49 0 0
label_47
	printstr 24 0 0
label_49
	jump 44 0 0
	jump 42 0 0
label_44
	jump 37 0 0
	jump 35 0 0
label_37
	jump 30 0 0
	jump 28 0 0
label_30
	jump 23 0 0
	jump 21 0 0
label_23
	jump 16 0 0
	jump 14 0 0
label_16
	END 0 0 0
	END 0 0 0
	END 0 0 0
