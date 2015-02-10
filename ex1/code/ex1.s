.syntax unified

.include "efm32gg.s"

/////////////////////////////////////////////////////////////////////////////
//
// Exception vector table
// This table contains addresses for all exception handlers
//
/////////////////////////////////////////////////////////////////////////////

.section .vectors

    .long   stack_top               /* Top of Stack                 */
    .long   _reset                  /* Reset Handler                */
    .long   dummy_handler           /* NMI Handler                  */
    .long   dummy_handler           /* Hard Fault Handler           */
    .long   dummy_handler           /* MPU Fault Handler            */
    .long   dummy_handler           /* Bus Fault Handler            */
    .long   dummy_handler           /* Usage Fault Handler          */
    .long   dummy_handler           /* Reserved                     */
    .long   dummy_handler           /* Reserved                     */
    .long   dummy_handler           /* Reserved                     */
    .long   dummy_handler           /* Reserved                     */
    .long   dummy_handler           /* SVCall Handler               */
    .long   dummy_handler           /* Debug Monitor Handler        */
    .long   dummy_handler           /* Reserved                     */
    .long   dummy_handler           /* PendSV Handler               */
    .long   dummy_handler           /* SysTick Handler              */

    /* External Interrupts */
    .long   dummy_handler
    .long   gpio_handler            /* GPIO even handler */
    .long   dummy_handler
    .long   dummy_handler
    .long   dummy_handler
    .long   dummy_handler
    .long   dummy_handler
    .long   dummy_handler
    .long   dummy_handler
    .long   dummy_handler
    .long   dummy_handler
    .long   gpio_handler            /* GPIO odd handler */
    .long   dummy_handler
    .long   dummy_handler
    .long   dummy_handler
    .long   dummy_handler
    .long   dummy_handler
    .long   dummy_handler
    .long   dummy_handler
    .long   dummy_handler
    .long   dummy_handler
    .long   dummy_handler
    .long   dummy_handler
    .long   dummy_handler
    .long   dummy_handler
    .long   dummy_handler
    .long   dummy_handler
    .long   dummy_handler
    .long   dummy_handler
    .long   dummy_handler
    .long   dummy_handler
    .long   dummy_handler
    .long   dummy_handler
    .long   dummy_handler
    .long   dummy_handler
    .long   dummy_handler
    .long   dummy_handler
    .long   dummy_handler
    .long   dummy_handler



.section .text

    /////////////////////////////////////////////////////////////////////////////
    //
    // Reset handler
    // The CPU will start executing here after a reset
    //
    /////////////////////////////////////////////////////////////////////////////

    .globl  _reset
    .type   _reset, %function
    .thumb_func
    _reset:

        // == Enable GPIO IO-clock ==

        ldr r1, =CMU_BASE
        ldr r2, [r1, CMU_HFPERCLKEN0]

        mov r3, 1
        lsl r3, CMU_HFPERCLKEN0_GPIO
        orr r2, r2, r3

        str r2, [r1, CMU_HFPERCLKEN0]


        // == Setup outputs in port A ==

        ldr r1, =GPIO_PA_BASE

        // Set alternative drive strength on port A to 2mA (low)
        // High drive strength results in eyebleed.
        mov r2, 0x3
        str r2, [r1, GPIO_CTRL]

        // Port A pins 8-15: set to push-pull with alternative drive strength.
        ldr r2, =0x55555555
        str r2, [r1, GPIO_MODEH]

        // Note that DOUT is active low.
        // Make sure the pins are GND to begin with.
        mov r2, 0xfe00
        str r2, [r1, GPIO_DOUT]


        // == Setup inputs on port C ==

        ldr r1, =GPIO_PC_BASE

        // Port C pins 0-7: set pull direction to up.
        mov r2, 0xff
        str r2, [r1, GPIO_DOUT]

        // Set Port C pins 0-7 to input with pull and glich-filter enabled.
        ldr r2, =0x33333333
        str r2, [r1, GPIO_MODEL]

        // Set interrupt generation source on GPIO pins 0-7 to port C.
        ldr r1, =GPIO_BASE
        ldr r2, =0x22222222
        str r2, [r1, GPIO_EXTIPSELL]

        // Enable interupt generation on both rise and fall.
        mov r2, 0xff
        str r2, [r1, GPIO_EXTIFALL]
        str r2, [r1, GPIO_IEN]


        // == Setup sleep ==

        // Enable SLEEPDEEP and SLEEPONEXIT
        ldr r1, =SCR
        mov r2, 0x6
        str r2, [r1]


        // == Enable interrupt handlers ==

        // Enable GPIO interrupt handlers (odd and even).
        // GPIO interrupts are IRQ 1 and 11.
        ldr r1, =0x802
        ldr r2, =ISER0
        str r1, [r2]


        // == Setup complete ==

        // Wait for interrupt
        wfi

    /////////////////////////////////////////////////////////////////////////////
    //
    // GPIO handler
    // The CPU will jump here when there is a GPIO interrupt
    //
    /////////////////////////////////////////////////////////////////////////////

    .thumb_func
    gpio_handler:
        ldr r0, =GPIO_BASE
        ldr r1, =GPIO_PA_BASE
        
	ldr r2, [r0, GPIO_IF]
        str r2, [r0, GPIO_IFC]
	
	// mvn r3, r2	
	// and r3, r3, 0x4000

	mov r3, r2 // Handle SW7
	and r3, r3, 0x40
	cbz r3, button_7_not_pushed
        
	ldr r3, [r1, GPIO_DOUT]
	lsr r3, r3, 1
	str r3, [r1, GPIO_DOUT]
	button_7_not_pushed:
	
        bx lr

    /////////////////////////////////////////////////////////////////////////////


	
    .thumb_func
    dummy_handler:
        b .  // do nothing
