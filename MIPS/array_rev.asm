# Austin Klum
# 2017/11/19
# Takes in user input into an array and prints out the array in reverse order. As well as the maximum value
	.data
array:    .space 400
lblMax:	  .asciiz "\nMaximum: "
lblRev:   .asciiz "Reverse: "
lblSpace: .asciiz " "
	.text
main:	addi	$v0, $zero, 5 	 #Get things ready for user input
	syscall
	add	$s0, $zero, $v0	 #s0 = user input 
	addi	$s1, $zero, 0	 # set s1 to i
	la 	$s2, array	 #Load first addr of array into2
max:	addi	$s3, $zero, 1    #set max to 1
	sll	$s3, $s3, 31	 #set Max to min int
input:	slt 	$t0, $s1, $s0 	 # i < input ? 1 : 0
	beq 	$t0, $zero,endput# if i > input; stop user inputting
	#Get input
	sll	$t1, $s1, 2 	 #t1 = i * 4
	add	$s5, $t1, $s2 	 #s5 = arr + i*4
	lw	$s4, 0($s5)	 #s4 = arr[i]
	addi 	$v0, $zero, 5 	 #Get things ready for user input
	syscall

	#Add to array
	add 	$s4, $zero, $v0  #arr[i] = user input
	sw	$s4, 0($s5)	 #save the new value

	#check if input is larger than max and set new val
getMax:	slt	$t0, $s3, $s4 	 # max < input ? 1 : 0
	beq 	$t0, $zero, endIf# !(max<input) -> endif
	add	$s3, $s4, $zero  # max = input
endIf:  addi	$s1, $s1, 1 	 #i++
	j input			 #Jump to start of loop

	#end of loop, begin printing in reverse
endput: la 	$a0, lblRev 	 #set $a0 to lblRev
	addi 	$v0, $zero, 4 	 #Tell system we want to print
	syscall

rev:	addi	$s1, $s1, -1	 #i--
	slt	$t0, $s1, $zero  #t0 = i < 0 ? 1 : 0
	bne	$t0, $zero, prtMax #(i < 0) -> printMax
	sll	$t1, $s1, 2 	 # t1 = i * 4
	add	$s5, $t1, $s2 	 #s5 = arr + i*4
	lw	$s4, 0($s5)	 #s4 = arr[i]

	#Load into arguments array[i]
	la	$a0, 0($s4) 	 # Load arr[i] into the args
	addi	$v0, $zero, 1	 # Tell system we want to print
	syscall
	la	$a0, lblSpace  	 #Load lblSpace into the args
	addi 	$v0, $zero, 4	 # Tell system we want to print
	syscall
	j rev			 # Jump to top of rev loop

prtMax: la	$a0, lblMax 	 # Load lblMax into args
	addi	$v0, $zero, 4	 # Tell system we want to print
	syscall
	add	$a0, $s3 ,$zero	 #put max into args
	addi 	$v0, $zero, 1	 # Tell System we want to print
	syscall
	addi	$v0, $zero, 10	 # Tell system to exit
	syscall
	


	
	
