
#ifndef _HARDWARE_led_H
#define _HARDWARE_led_H

#include <hardware/hardware.h>

__BEGIN_DECLS

struct led_device_t {
      
    struct hw_device_t common;
	int (*led_open)(struct led_device_t* dev);
	//void (*led_close)(struct led_device_t* dev);
	int (*led_ctrl)(struct led_device_t* dev,int number,int state);
};



__END_DECLS

#endif  // _HARDWARE_VIBRATOR_H











