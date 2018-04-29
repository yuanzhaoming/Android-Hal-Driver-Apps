#define LOG_TAG "LedService"

#include "jni.h"
#include "JNIHelp.h"
#include "android_runtime/AndroidRuntime.h"

#include <utils/misc.h>
#include <utils/Log.h>


#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/ioctl.h>



namespace android
{
	led_device_t *led_device;

static jint fd;

jint native_ledopen(JNIEnv *env , jobject thiz)
{
	jint err;
	hw_module_t *module;

	hw_device_t *device;
	
	err = hw_get_module("led",(const struct hw_module_t * * )&module);

	if(err == 0){
		err = module->methods->open(module,NULL,&device);
		if(err == 0){
			led_device = (led_device_t *)device;
			return led_device->led_open(led_device);
		}
		else{
			return -1;
		}
	}
	return -1;
}


void native_ledclose(JNIEnv *env , jobject thiz)
{
	__android_log_print(ANDROID_LOG_DEBUG,"led_jni","led_close...");
	
}


jint native_ledctl(JNIEnv *env , jobject thiz ,jint number, jint state)
{

	
	__android_log_print(ANDROID_LOG_DEBUG,"led_jni","led_control:%d,%d...",number,state);

	return led_device->led_ctrl(led_device,number,state);
}


static JNINativeMethod methods[] = {
    { "native_ledctl", "(II)I", (void*) native_ledctl },
    { "native_ledopen", "()I", (void*) native_ledopen },
    { "native_ledclose", "()V", (void*) native_ledclose }
};

int register_android_server_LedService(JNIEnv *env)
{
    return jniRegisterNativeMethods(env, "com/android/server/LedService",
            methods, NELEM(methods));
}

};









