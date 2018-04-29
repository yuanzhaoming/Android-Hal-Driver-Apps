#define LOG_TAG "LedService"

#include "jni.h"
#include "JNIHelp.h"
#include "android_runtime/AndroidRuntime.h"

#include <utils/misc.h>
#include <utils/Log.h>
#include <hardware_legacy/vibrator.h>

#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/ioctl.h>



namespace android
{

static jint fd;

jint native_ledopen(JNIEnv *env , jobject thiz)
{
	fd = open("/dev/leds",O_RDWR);
	
	__android_log_print(ANDROID_LOG_DEBUG,"led_jni","led_open...%d \r\n",fd);
	if(fd<0)
		return -1;
	return 0;
}


void native_ledclose(JNIEnv *env , jobject thiz)
{
	__android_log_print(ANDROID_LOG_DEBUG,"led_jni","led_close...");
	close(fd);
}


jint native_ledctl(JNIEnv *env , jobject thiz ,jint number, jint state)
{
	int ret = ioctl(fd,state,number);
	__android_log_print(ANDROID_LOG_DEBUG,"led_jni","led_control:%d,%d...",number,state);

	return ret;
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









