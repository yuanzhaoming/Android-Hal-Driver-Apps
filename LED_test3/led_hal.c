
#include <hardware/hardware.h>
#include <cutils/log.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <math.h>
#include <hardware/led_hal.h>

#include <utils/Log.h>

#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/ioctl.h>


static int led_close(struct hw_device_t* dev);
static int led_open(struct led_device_t* dev);
static int led_ctrl(struct led_device_t* dev,int number,int state);


struct led_device_t led_dev={
	.common = {
		.close = led_close,
	},
	.led_open = led_open,
	.led_ctrl = led_ctrl,
};

static int fd;



static int led_close(struct hw_device_t* dev)
{
	close(fd);

	return 0;
}


static int led_ctrl(struct led_device_t* dev,int number,int state)
{
	int ret = ioctl(fd,state,number);
	__android_log_print(ANDROID_LOG_DEBUG,"led_jni","led_control:%d,%d...",number,state);

	return ret;

}

static int led_open(struct led_device_t* dev)
{
	fd = open("/dev/leds",O_RDWR);
	
	__android_log_print(ANDROID_LOG_DEBUG,"led_jni","led_open...%d \r\n",fd);
	if(fd<0)
		return -1;
	return 0;
}



int led_device_open(const struct hw_module_t* module, const char* id,
		struct hw_device_t** device)
{
	 *device = (hw_device_t *)&led_dev;

	return 0;
}

static struct hw_module_methods_t led_module_methods = {
    .open = led_device_open,
};

struct hw_module_t HAL_MODULE_INFO_SYM = {
    .tag = "led",
    .id = "led",
    .name = "Default led HAL",
    .author = "wit_yuan",
    .methods = &led_module_methods,
};



