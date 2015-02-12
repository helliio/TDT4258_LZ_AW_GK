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

        GPIO_I .req r4
        ldr GPIO_I, =GPIO_PC_BASE

        GPIO_O .req r5
        ldr GPIO_O, =GPIO_PA_BASE

        GPIO .req r6
        ldr GPIO, =GPIO_BASE

        // Enable GPIO IO-clock.

        ldr r2, =CMU_BASE
        ldr r1, [r2, #CMU_HFPERCLKEN0]
        orr r1, r1, #( 1 << CMU_HFPERCLKEN0_GPIO )
        str r1, [r2, #CMU_HFPERCLKEN0]


        // == Setup outputs in port A ==

        // Set alternative drive strength on port A to 2mA (low)
        // High drive strength results in eyebleed.
        ldr r1, =0x3
        str r1, [GPIO, #GPIO_CTRL]

        // Port A pins 8-15: set to push-pull with alternative drive strength.

        ldr r1, =0x55555555
        str r1, [GPIO_O, #GPIO_MODEH]


        // Inputs
        ldr r1, =0x00ff
        str r1, [GPIO_I, #GPIO_DOUT]

        ldr r1, =0x33333333
        str r1, [GPIO_I, #GPIO_MODEL]


        // Interrupts
        ldr r1, =0x22222222
        str r1, [GPIO, #GPIO_EXTIPSELL]

        ldr r1, =0x00ff
        //str r1, [GPIO, #GPIO_EXTIRISE]
        str r1, [GPIO, #GPIO_EXTIFALL]
        str r1, [GPIO, #GPIO_IEN]

        ldr r1, =( 1<< 1 | 1<< 11 )
        ldr r2, =ISER0
        str r1, [r2]

        ldr r1, =( 1<< 1 | 1<< 2 )
        ldr r2, =SCR
        str r1, [r2]

        wfi
        b .-1


    /////////////////////////////////////////////////////////////////////////////
    //
    // GPIO handler
    // The CPU will jump here when there is a GPIO interrupt
    //
    /////////////////////////////////////////////////////////////////////////////

    .thumb_func
    gpio_handler:
        ldr r1, [GPIO, #GPIO_IF]
        str r1, [GPIO, #GPIO_IFC]

        ldr r1, [GPIO_I, #GPIO_DIN]
        lsl r1, r1, #8
        str r1, [GPIO_O, #GPIO_DOUT]

        bx lr

    /////////////////////////////////////////////////////////////////////////////

    .thumb_func
    dummy_handler:
        b .  // do nothing
