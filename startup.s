    .thumb
    .syntax unified

	.section .vector_interrupt, "x"
g_pfnVectors:
	.word 	_stack_start
	.word 	_Reset
	.word	NMI           /* NMI Handler */
	.word	HardFault     /* Hard Fault Handler */
	.word	MemManage     /* MPU Fault Handler */
	.word	BusFault      /* Bus Fault Handler */
	.word	UsageFault    /* Usage Fault Handler */
	.word	0             /* Reserved */
	.word	0             /* Reserved */
	.word	0             /* Reserved */
	.word	0             /* Reserved */
	.word	SVC           /* SVCall Handler */
	.word	DebugMon      /* Debug Monitor Handler */
	.word	0             /* Reserved */
	.word	PendSV        /* PendSV Handler */
	.word	SysTick       /* SysTick Handler */

	.text

	.global _Reset
	.thumb_func
_Reset:
	@@ Copy data to RAM.
    ldr   r0, = _flash_sdata
    ldr   r1, = _ram_sdata
    ldr   r2, = _data_size

    @@ Handle data_size == 0
    cmp   r2, #0
    beq   init_bss
copy:
    ldrb   r4, [r0], #1
    strb   r4, [r1], #1
    subs   r2, r2, #1
    bne    copy
init_bss:
    @@ Initialize .bss
    ldr   r0, = _sbss
    ldr   r1, = _ebss
    ldr   r2, = _bss_size

    @@ Handle bss_size == 0
    cmp   r2, #0
    beq   init

    mov   r4, #0
zero:
    strb  r4, [r0], #1
    subs  r2, r2, #1
    bne   zero
init:
	bl    main
stop:
	b     stop  @ Infinite loop to stop execution



	.align	1
	.thumb_func
	.weak	Default_Handler
	.type	Default_Handler, %function
Default_Handler:
	b	.

	/* Macro to define default handlers */
	.macro	def_handler	handler_name
		.weak	\handler_name
		.set	\handler_name, Default_Handler
	.endm

	def_handler	NMI
	def_handler	HardFault
	def_handler	MemManage
	def_handler	BusFault
	def_handler	UsageFault
	def_handler	SVC
	def_handler	DebugMon
	def_handler	PendSV
	def_handler	SysTick
	def_handler	DEF_IRQHandler
