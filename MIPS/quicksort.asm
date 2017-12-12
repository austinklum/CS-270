# Austin Klum
# 2017/11/23
# Takes in user input into an array and prints out the array in sorted order using quicksort.
	.data
array:    .space 80
lblSort:  .asciiz "Sorted: "
	  .align 2
lblSpace: .asciiz " "
	  .align 2

	.text
	#s0 = array, s1 = i, s2 = length, s3 = arr[i], s4 = arr + i*4,
main:	addi	$v0, $zero, 5		#Get things ready for user input
	syscall
	add	$s2, $zero, $v0	 	#s2 = user inputted length 
	add	$s1, $zero, $zero	# set s1 to i
	la 	$s0, array		#Load first addr of array into s0

startl:	slt 	$t0, $s1, $s2 	 	# length < i ? 1 : 0
	beq 	$t0, $zero,endl 	# if i > input; stop user inputting
	
	#Get input
	sll	$t0, $s1, 2 		#t0 = i * 4
	add	$s4, $s0, $t0 	 	#s4 = arr + i*4
	lw	$s3, 0($s4)	 	#s3 = arr[i]
	addi 	$v0, $zero, 5 	 	#Get things ready for user input
	syscall

	#Add to array
	add 	$s3, $zero, $v0  	#arr[i] = user input
	sw	$s3, 0($s4)	 	#save the new value

	addi	$s1, $s1, 1 	 	#i++
	j startl			#Jump to start of loop

	#get things ready to call quick sort
endl: 	add	$a0, $s0, $zero		#a0 = array sart pos
	add 	$a1, $s2, $zero		#a1 = length
	jal	sort			#call sort
	
	#Loop through and print sorted array
	la	$a0, lblSort		# load lblSorted
	addi	$v0, $zero, 4		# Tell system we want to print
	syscall   
	add 	$s1, $zero, $zero	#i = 0
print:	slt	$t0, $s1, $s2  		#t0 = i < length ? 1 : 0
	beq	$t0, $zero, exit 	#!(i < length) -> exit
	sll	$t0, $s1, 2 	 	# t0 = i * 4
	add	$t0, $s0, $t0 	 	#t0 = arr + i*4
	lw	$t1, 0($t0)		#t1 = arr[i]

	#Load into arguments array[i]
	add	$a0, $t1, $zero 	# Load arr[i] into the args
	addi	$v0, $zero, 1		# Tell system we want to print an integer
	syscall
	la	$a0, lblSpace  	 	#Load lblSpace into the args
	addi 	$v0, $zero, 4	 	# Tell system we want to print
	syscall
	
	addi	$s1, $s1, 1 	 	#i++
	j print		
	
exit:	addi	$v0, $zero, 10		# Tell system to exit
	syscall

	# quick_sort 
	# Sorts an int[] array
	# @param arr
	# @param length
sort:   addi	$sp, $sp, -4		#Add to the stack
	sw	$ra, 0($sp)		#store $ra
# -------------------------------------------------------------------------------
	#Get things ready to call the helper
	addi	$a2, $a1, -1		#a2 = length -1
	add 	$a1, $zero, $zero	#a1 = 0
	jal 	help
# -------------------------------------------------------------------------------
	lw	$ra, 0($sp)		#restore $ra
	addi	$sp, $sp, 4		#pop stack
	jr  	$ra

	# quick_sort_helper
	# recursive helper method
	# @param arr
	# @param left
	# @param right
help:   addi 	$sp, $sp, -20		#add to stack
	
	#store ra,s0
	sw	$a0,  16($sp)		# Save arr
	sw 	$a1,  12($sp)		# left
	sw	$a2,  8($sp)		# right	
	sw 	$ra,  4($sp)		#$ra
	sw	$s0,  0($sp)		#index

# -------------------------------------------------------------------------------
	#call partition, Should be safe to call
	jal 	part
	lw	$a0, 16($sp)	
	lw	$a1, 12($sp)
	lw	$a2,  8($sp)		
	add 	$s0, $v0, $zero 	#index = partition(arr, left, right)
# -------------------------------------------------------------------------------		
	addi	$t0, $s0, -1		#t0 = index - 1
	slt	$t1, $a1, $t0		#t0 = left < index - 1
	beq 	$t1, $zero, else	# !(left < index-1) -> else
	# get things ready for recursion
	add	$a2, $t0, $zero 	#a2 = index - 1
	jal 	help
	lw	$a0, 16($sp)		# restore array addr
	lw	$a1, 12($sp)		# left
	lw	$a2,  8($sp)		# right

else:	slt	$t0, $s0, $a2		# t0 = index < right
	beq 	$t0, $zero, ret		# !(index < right) -> ret
	add	$a1, $s0, $zero		# a1 = index
	jal	help
	lw	$a0, 16($sp)	
	lw	$a1, 12($sp)
	lw	$a2,  8($sp)

ret:	#restore values
	lw 	$ra, 4($sp)		#$ra
	lw	$s0, 0($sp)		#index
	addi	$sp, $sp, 20		#pop stack
	jr 	$ra			#return

part:	# partition
	# does the actual sorting
	# @param arr
	# @param left
	# @param right

	#store s0 = i, s1 = j, s2 = pivot
	addi 	$sp, $sp, -12		#make room	
	sw	$s2, 8($sp)		
	sw	$s1, 4($sp)
	sw 	$s0, 0($sp)
	
	add	$s0, $a1, $zero		# i = left
	add	$s1, $a2, $zero		# j = right	
	add	$t0, $a1, $a2		# t0 = left + right

	srl	$t0, $t0, 1		# t0 = (left + right) / 2
	sll	$t0, $t0, 2		# ((left + right) / 2) * 4

	add	$t0, $t0, $a0		# arr + ((left + right) / 2) * 4
	lw 	$s2, 0($t0)		# s2 = arr[(left + right) / 2]
	
while1:	slt 	$t0, $s1, $s0		# !(j < i) == j >= i
	bne	$t0, $zero, pRet	# !(j >= i) -> pRet
while2: sll	$t0, $s0, 2		# t0 = i * 4
	add	$t0, $t0, $a0		# t0 = arr + i *4
	lw	$t0, 0($t0)		# t0 = arr[i]
	
	slt 	$t0, $t0, $s2		#arr[i] < pivot
	beq	$t0, $zero, while3	#!(arr[i] < pivot)
	addi	$s0, $s0, 1		#i++
	j while2
while3:	sll	$t0, $s1, 2		# j * 4
	add	$t0, $t0, $a0		# t0 = arr + j *4
	lw	$t0, 0($t0)		# t0 = arr[j]

	slt 	$t0, $s2, $t0		# pivot < arr[j]
	beq	$t0, $zero, if		# !(pivot < arr[j]) -> if
	addi	$s1, $s1, -1		# j--
	j while3
if: 	slt 	$t0, $s1, $s0		# !(j < i) == j >= i
	bne	$t0, $zero, jump	# !(j >= i) -> pRet
	
	# load arr[i] into t1 with t0 storing the addr
	sll	$t0, $s0, 2		# t0 = i * 4
	add	$t0, $t0, $a0		# t0 = arr + i *4
	lw	$t9, 0($t0)		# tmp = arr[i]
	
	# load arr[j] into t2 with t3 storing the addr
	sll	$t2, $s1, 2		# t2 = j * 4
	add	$t3, $t2, $a0		# t3 = arr + j *4
	lw	$t2, 0($t3)		# t2 = arr[j]
	
	sw	$t2, 0($t0)		# arr[i] = arr[j]
	sw	$t9, 0($t3)		# arr[j] = tmp
	
	addi	$s0, $s0, 1		#i++
	addi	$s1, $s1, -1		# j--		
jump:	j while1
pRet:   add 	$v0, $s0, $zero		#v0 = i
	
	#restore s0, s1, s2
	lw	$s2, 8($sp)		
	lw	$s1, 4($sp)
	lw 	$s0, 0($sp)
	addi 	$sp, $sp, 12		#pop stack
	
	jr $ra 	
	
	
