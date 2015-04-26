#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>

#include <linux/cdev.h>
#include <linux/fs.h>

#include <asm/io.h>
#include <asm/uaccess.h>

#define NAME "gamepad"
#define MAJOR_NUMBER 42

#define GPIO_PA_BASE 0x40006000
#define GPIO_PC_BASE 0x40006048

#define GPIO_PORT_REGION_SIZE 0x20

#define GPIO_PC_MODEL    ((volatile uint32_t *)(GPIO_PC_BASE + 0x04))
#define GPIO_PC_DOUT     ((volatile uint32_t *)(GPIO_PC_BASE + 0x0c))
#define GPIO_EXTIPSELL   ((volatile uint32_t *)(GPIO_PA_BASE + 0x100))
#define GPIO_EXTIRISE    ((volatile uint32_t *)(GPIO_PA_BASE + 0x108))
#define GPIO_EXTIFALL    ((volatile uint32_t *)(GPIO_PA_BASE + 0x10c))

#define GPIO_PC_DIN      ((volatile const uint32_t *)(GPIO_PC_BASE + 0x1c))


static struct cdev cdev;

ssize_t read(struct file * filp, char __user * buff, size_t count, loff_t * offp)
{
    // Note that only the lower 8 bits are interesting.
    uint32_t din = ioread32(GPIO_PC_DIN);
    copy_to_user(buff, &din, 1);
    return 1;
}

static struct file_operations fops
    = { .owner = THIS_MODULE,
        .read = read,
    };

static void __init setup_cdev(void)
{
    dev_t dev = MKDEV(MAJOR_NUMBER, 0);
    register_chrdev_region(dev, 1, NAME);

    cdev_init(&cdev, &fops);
    cdev.owner = THIS_MODULE;
    cdev_add(&cdev, dev, 1);
}

static void __init setup_gpio(void)
{
//    request_mem_region(GPIO_PC_BASE, GPIO

    iowrite32(0x33333333, GPIO_PC_MODEL);
    iowrite32(0xff, GPIO_PC_DOUT);
}

static void __exit destroy_cdev(void)
{
    dev_t dev = cdev.dev;
    cdev_del(&cdev);
    unregister_chrdev_region(dev, 1);
}


static int __init init(void)
{
	printk("Hello World, here is your module speaking better\n");

    setup_gpio();

    // After this call we are live
    setup_cdev();

	return 0;
}

static void __exit cleanup(void)
{
	 printk("Short life for a small module...\n");

     destroy_cdev();
}

module_init(init);
module_exit(cleanup);

MODULE_DESCRIPTION("Small module, demo only, not very useful.");
MODULE_LICENSE("GPL");

