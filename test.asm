# TEST FILE


main:
    endl
    printf STARTING_TESTS
    endl
    endl


# TEST 1 ALU OPERATIONS
li x5, 10
li x6, 20
li x7, 30

add x28, x5, x6
bne x28, x7, fail

sub x29, x7, x5
li x30, 20
bne x29, x30, fail

addi x31, x5, 15
li x5, 25
bne x31, x5, fail

li x10, 2
li x11, 8
sll x12, x10, x11
li x13, 512
bne x12, x13, fail

li x14, 1024
srl x15, x14, x10
li x16, 256
bne x15, x16, fail

li x17, -10
sra x18, x17, x10
li x19, -3
bne x18, x19, fail

li x20, 5
li x21, -5
slt x22, x21, x20
li x23, 1
bne x22, x23, fail

sltu x24, x21, x20
bne x24, zero, fail

li x25, 7
li x26, 3
and x27, x25, x26
li x5, 3
bne x27, x5, fail

or x6, x25, x26
li x7, 7
bne x6, x7, fail

xor x28, x25, x26
li x29, 4
bne x28, x29, fail

lui x30, 2
li x31, 8192
bne x30, x31, fail

mul x10, x26, x25
li x11, 21
bne x10, x11, fail

li x12, 100
li x13, 10
div x14, x12, x13
li x15, 10
bne x14, x15, fail

printf TEST_1_ALU_TEST_PASSED
endl


# TEST 2 BRANCH OPERATIONS
li x10, 15
li x11, 80
li x12, -10
li x13, 0

beq x10, x10, L1
j fail

L1:
bne x10, x11, L2
j fail

L2:
blt x10, x11, L3
j fail

L3:
bge x11, x10, L4
j fail

L4:
ble x10, x10, L5
j fail

L5:
bgt x11, x10, L6
j fail

L6:
bnez x10, L7
j fail

L7:
beqz x13, L8
j fail

L8:
bltz x12, L9
j fail

L9:
bgez x13, L10
j fail

L10:
bgtz x10, L11
j fail

L11:
blez x13, L12
j fail

L12:
# Unsigned check: -10 (large) vs 80 (small)
bleu x11, x12, L13
j fail

L13:
bgtu x12, x11, L14
j fail

L14:
printf TEST_2_BRANCH_PASSED
endl



# TEST 3 COMPARE OPERATIONS
li x5, 100
li x6, 200
slt x7, x5, x6
li x8, 1
bne x7, x8, fail

li x5, -50
li x6, -20
slt x7, x5, x6
bne x7, x8, fail

li x5, 10
li x6, -10
slt x7, x5, x6
bne x7, zero, fail

li x5, 50
li x6, 50
slt x7, x5, x6
bne x7, zero, fail

li x5, 15
slti x7, x5, 20
bne x7, x8, fail

li x5, -10
slti x7, x5, -5
bne x7, x8, fail

li x5, 30
slti x7, x5, 30
bne x7, zero, fail

li x5, -1
slti x7, x5, 0
bne x7, x8, fail

li x5, 1
li x6, -1
sltu x7, x5, x6
bne x7, x8, fail

li x5, -2
li x6, -1
sltu x7, x5, x6
bne x7, x8, fail

li x5, 500
li x6, 100
sltu x7, x5, x6
bne x7, zero, fail

li x5, 10
sltiu x7, x5, 11
bne x7, x8, fail

li x5, 0
sltiu x7, x5, -1
bne x7, x8, fail

li x5, 4000
sltiu x7, x5, 100
bne x7, zero, fail

li t0, 500
li t1, 1000
slt t2, t0, t1
bne t2, x8, fail

li t0, -100
slti t2, t0, -50
bne t2, x8, fail

li t0, 1
sltiu t2, t0, 2
bne t2, x8, fail

printf TEST_3_COMPARE_PASSED
endl


# TEST 4 LOGICAL OPERATIONS
li t0, 15
li t1, 10
li t2, 5

and t3, t0, t1
li t4, 10
bne t3, t4, fail

andi t3, t0, 5
bnefortests t3, 5, fail

or t3, t1, t2
li t4, 15
bne t3, t4, fail

ori t3, t1, 4
bnefortests t3, 14, fail

xor t3, t0, t2
li t4, 10
bne t3, t4, fail

xori t3, t1, 15
bnefortests t3, 5, fail

li t0, 0
not t1, t0
bnefortests t1, -1, fail

li t0, -1
not t1, t0
bnefortests t1, 0, fail

li t0, 100
neg t1, t0
bnefortests t1, -100, fail

li t0, -50
neg t1, t0
bnefortests t1, 50, fail

li t0, 1
li t1, 1
and t2, t0, t1
bnefortests t2, 1, fail

or t2, t0, t1
bnefortests t2, 1, fail

xor t2, t0, t1
bnefortests t2, 0, fail

printf TEST_4_LOGICAL_PASSED
endl


# TEST 5 SHIFT OPERATIONS
li t0, 1
slli t1, t0, 1
bnefortests t1, 2, fail

slli t1, t0, 10
bnefortests t1, 1024, fail

li t0, 3
li t1, 2
sll t2, t0, t1
bnefortests t2, 12, fail

li t0, 1024
srli t1, t0, 10
bnefortests t1, 1, fail

li t0, -1
srli t1, t0, 31
bnefortests t1, 1, fail

li t0, 64
li t1, 3
srl t2, t0, t1
bnefortests t2, 8, fail

li t0, -1
srai t1, t0, 1
bnefortests t1, -1, fail

li t0, -16
srai t1, t0, 2
bnefortests t1, -4, fail

li t0, -32
li t1, 3
sra t2, t0, t1
bnefortests t2, -4, fail

li t0, 1
li t1, 32
sll t2, t0, t1
bnefortests t2, 1, fail

li t0, 15
li t1, 36
sll t2, t0, t1
bnefortests t2, 240, fail

li t0, 1
slli t1, t0, 31
li t2, 0
bge t1, t2, fail

srli t2, t1, 31
bnefortests t2, 1, fail

srai t2, t1, 31
bnefortests t2, -1, fail

printf TEST_5_SHIFT_PASSED
endl


# TEST 6 LOAD OPERATIONS
addi x2, x2, -16

li x5, 16909060
sw x5, 0(x2)

lw x6, 0(x2)
bnefortests x6, 16909060, fail

lb x7, 0(x2)
bnefortests x7, 4, fail

lb x8, 1(x2)
bnefortests x8, 3, fail

lb x9, 2(x2)
bnefortests x9, 2, fail

lb x10, 3(x2)
bnefortests x10, 1, fail

li x11, -1
sw x11, 4(x2)

lb x12, 4(x2)
bnefortests x12, -1, fail

lbu x13, 4(x2)
bnefortests x13, 255, fail

lh x14, 4(x2)
bnefortests x14, -1, fail

lhu x15, 4(x2)
bnefortests x15, 65535, fail

li x16, 32767
sh x16, 8(x2)
lh x17, 8(x2)
bnefortests x17, 32767, fail

li x18, 128
sb x18, 12(x2)
lb x19, 12(x2)
bnefortests x19, -128, fail

lbu x20, 12(x2)
bnefortests x20, 128, fail

lui x21, 1
bnefortests x21, 4096, fail

addi x2, x2, 16

printf TEST_6_LOAD_PASSED
endl


# TEST 7 STORE OPERATIONS
addi x2, x2, -16

li x5, 0
sw x5, 0(x2)
sw x5, 4(x2)
sw x5, 8(x2)
sw x5, 12(x2)

li x6, 1
sb x6, 0(x2)
lw x7, 0(x2)
bnefortests x7, 1, fail

li x6, 2
sb x6, 1(x2)
lw x7, 0(x2)
bnefortests x7, 513, fail

li x6, 3
sb x6, 2(x2)
lw x7, 0(x2)
bnefortests x7, 197121, fail

li x6, 4
sb x6, 3(x2)
lw x7, 0(x2)
bnefortests x7, 67305985, fail

li x8, 1
sh x8, 4(x2)
lw x9, 4(x2)
bnefortests x9, 1, fail

li x8, 1
sh x8, 6(x2)
lw x9, 4(x2)
bnefortests x9, 65537, fail

li x11, -1
sb x11, 8(x2)
lbu x12, 8(x2)
bnefortests x12, 255, fail

sb x11, 9(x2)
lhu x12, 8(x2)
bnefortests x12, 65535, fail

li x13, 999
sw x13, 12(x2)
lw x14, 12(x2)
bne x13, x14, fail

addi x2, x2, 16

printf TEST_7_STORE_PASSED
endl


# TEST 8 FUNCTION OPERATIONS
addi sp, sp, -4
sw ra, 0(sp)
li a0, 5
li a1, 15
jal ra, sum_function
lw ra, 0(sp)
addi sp, sp, 4
bnefortests a0, 20, fail

addi sp, sp, -4
sw ra, 0(sp)
li a0, 7
jal ra, recursive_check
lw ra, 0(sp)
addi sp, sp, 4
bnefortests a0, 14, fail

addi sp, sp, -12
li t0, 100
sw t0, 8(sp)
sw ra, 0(sp)
jal ra, stack_param_function
lw ra, 0(sp)
lw t1, 8(sp)
addi sp, sp, 12
bnefortests a0, 101, fail
bnefortests t1, 101, fail

li a0, 10
li a1, 20
li a2, 30
call triple_sum
bnefortests a0, 60, fail

printf TEST_8_FUNCTION_PASSED
endl



# TEST 9 OTHER FUNCTIONS
li t0, 500
mv t1, t0
bne t1, t0, fail

li t0, -100
mv t1, t0
bnefortests t1, -100, fail

li t2, 0
mv t3, zero
bne t3, t2, fail

mv t4, t1
bnefortests t4, -100, fail

strlen Hello
bnefortests a0, 5, fail

strlen Architecture
bnefortests a0, 12, fail

strlen FreeUni
bnefortests a0, 7, fail

li t0, 10
mv a1, t0
li a0, 5
add a2, a0, a1
bnefortests a2, 15, fail

printf TEST_9_OTHER_PASSED
endl


# TEST 10 RECURSION
li a0, 5
li s1, 120
addi sp, sp, -4
sw ra, 0(sp)
jal ra, complex_recursion
lw ra, 0(sp)
addi sp, sp, 4

mv t0, a0
bne t0, s1, fail

li t1, 4
slli t2, t1, 2
andi t3, t2, 15
bnefortests t3, 0, fail

strlen RecursiveTest
bnefortests a0, 13, fail

printf TEST_10_COMPLEX_PASSED
endl

# TEST 11 BUFFER
addi sp, sp, -16
li t0, 0
li t1, 4
li t2, 10

write_loop:
slli t3, t0, 2
add t4, sp, t3
addi t5, t0, 1
sw t5, 0(t4)
addi t0, t0, 1
blt t0, t1, write_loop

li t0, 0
li s0, 0

read_verify_loop:
slli t3, t0, 2
add t4, sp, t3
lw t5, 0(t4)
slli t6, t5, 1
addi t6, t6, -1
xori t6, t6, 2
add s0, s0, t6
addi t0, t0, 1
blt t0, t1, read_verify_loop

bnefortests s0, 16, fail

li x10, 255
li x11, 15
and x12, x10, x11
slli x12, x12, 4
ori x12, x12, 15
bnefortests x12, 255, fail

li x20, 100
li x21, 50
slt x22, x21, x20
slti x23, x20, 101
and x24, x22, x23
bnefortests x24, 1, fail

addi sp, sp, 16

printf TEST_11_BUFFER_LOGIC_PASSED
endl

j passed_all


sum_function:
add a0, a0, a1
ret

recursive_check:
addi sp, sp, -8
sw ra, 4(sp)
sw a0, 0(sp)
li t0, 2
mul a0, a0, t0
lw ra, 4(sp)
addi sp, sp, 8
ret

stack_param_function:
lw t0, 8(sp)
addi t0, t0, 1
mv a0, t0
sw t0, 8(sp)
ret

triple_sum:
add a0, a0, a1
add a0, a0, a2
ret

complex_recursion:
addi sp, sp, -8
sw ra, 4(sp)
sw a0, 0(sp)

li t0, 2
slt t1, a0, t0
bne t1, zero, base_case

addi a0, a0, -1
jal ra, complex_recursion

lw t0, 0(sp)
mul a0, a0, t0
j end_func

base_case:
li a0, 1

end_func:
lw ra, 4(sp)
addi sp, sp, 8
ret

# TESTS SUCCESS
passed_all:
    endl
    printf ALL_TESTS_PASSED_SUCCESSFULLY!
    endl
    li a0, 10
    ecall


# TEST_FAILED
fail:
    printf TEST_FAILED!!!!!!!
    endl
    li a0, 10
    ecall