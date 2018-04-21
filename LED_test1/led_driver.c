#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/moduleparam.h>
#include <linux/slab.h>
#include <linux/ioctl.h>
#include <linux/cdev.h>
#include <linux/delay.h>
 
#include <linux/gpio.h>
#include <mach/gpio.h>
#include <plat/gpio-cfg.h>
#include <linux/device.h>


static int led_gpios[] = {
	EXYNOS4212_GPM4(0),
	EXYNOS4212_GPM4(1),
	EXYNOS4212_GPM4(2),
	EXYNOS4212_GPM4(3),
};




static int tiny4412_leds_open(struct inode *inode, struct file *file)
{
	int i ;
	for(i = 0 ; i < 4 ; i ++){
		s3c_gpio_cfgpin(led_gpios[i], S3C_GPIO_OUTPUT);
		gpio_set_value(led_gpios[i], 1);

	}

	return 0;
}


static long tiny4412_leds_ioctl(struct file *filp, unsigned int cmd,
		unsigned long arg)
{
	if((cmd!= 0) && (cmd!=1))
		return -EINVAL;

	if(arg>4)
		return -EINVAL;
		
	gpio_set_value(led_gpios[arg], !cmd);

	return arg;
}




static struct file_operations tiny4412_led_dev_fops = {
	.owner			= THIS_MODULE,
	.unlocked_ioctl	= tiny4412_leds_ioctl,
	.open           = tiny4412_leds_open,
};

static int major;
static struct class *cls;



static int __init tiny4412_leds_init(void)
{
	major = register_chrdev(0,"leds",&tiny4412_led_dev_fops);
	if(major <= 0){
		printk("register_chrdev error\r\n");
		return -1;
	}

	cls = class_create(THIS_MODULE,"led_cls");
	device_create(cls,NULL,MKDEV(major,0),NULL,"leds");

	return 0;
}

static void __exit tiny4412_leds_dev_exit(void) {
	device_destroy(cls,MKDEV(major,0));
	class_destroy(cls);
	unregister_chrdev(major,"leds");
}



module_init(tiny4412_leds_init);
module_exit(tiny4412_leds_dev_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("wit_yuan driver.");









