#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <linux/fs.h>
#include <asm/io.h>

MODULE_LICENSE("GPL");
#define LED_MARJOR  250
static void hello_release(struct device *dev);

struct file_operations led_fops = {
	.owner = THIS_MODULE,
};

struct resource fs4412_led_resource[] = {
	[0]= {	
		.start  = 0x11000c40,
		.end    = 0x11000c40+0x4,
		.flags  =IORESOURCE_MEM,
	},
	[1] = {
		.start  = 0x11000c20,
		.end   = 0x11000c20 + 0x4,
		.flags  = IORESOURCE_MEM,
	},
	[2] = {
		.start  = 0x114001e0,
		.end  = 0x114001e0+0x4,
		.flags = IORESOURCE_MEM,
	},
};

struct platform_device device = {
	.name = "duang",
	.id = -1,
	.resource = fs4412_led_resource,
	.num_resources = ARRAY_SIZE(fs4412_led_resource),
	.dev.release  = hello_release,
};


static int hello_probe(struct platform_device *pdev)
{
   	register_chrdev(LED_MARJOR,"led",&led_fops);	
	printk("match  ok  \n");
	return 0;
}
static int hello_remove(struct platform_device *device)
{
	unregister_chrdev(LED_MARJOR,"led");
	printk("hello_remove  \n");
	return 0;
}
struct platform_driver driver = {
	.driver.name ="duang",
	.probe  = hello_probe,
	.remove  = hello_remove,
};

int  hello_init(void)
{
	platform_driver_register(&driver);
	platform_device_register(&device);
	printk("hello_init  \n");
	return  0;
}

void  hello_exit(void)
{	
	platform_device_unregister(&device);
	platform_driver_unregister(&driver);
	printk("hello_exit  \n");
}

static void hello_release(struct device *dev)
{
	printk("hello_release \n");
}

module_init(hello_init);
module_exit(hello_exit);
