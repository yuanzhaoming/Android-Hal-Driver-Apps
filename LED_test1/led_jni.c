#include "jni.h"
#include <stdlib.h>
#include <android/log.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/ioctl.h>

/**
*	arm-linux-gcc -fPIC -shared led_jni.c -o libled.so -I /usr/lib/jvm/java-1.7.0-openjdk-amd64/include -nostdlib /home/wityuan/Desktop/android-5.0.2/prebuilts/ndk/8/platforms/android-14/arch-arm/usr/lib/libc.so -I /home/wityuan/Desktop/android-5.0.2/prebuilts/ndk/8/platforms/android-14/arch-arm/usr/include/ /home/wityuan/Desktop/android-5.0.2/prebuilts/ndk/8/platforms/android-14/arch-arm/usr/lib/liblog.so
*
*/
static jint fd;


 
jint Java_com_example_administrator_test1_ledControl_ledopen(JNIEnv *env , jobject thiz)
{
	fd = open("/dev/leds",O_RDWR);
	
	__android_log_print(ANDROID_LOG_DEBUG,"led_jni","led_open...%d \r\n",fd);
	if(fd<0)
		return -1;
	return 0;
}


void Java_com_example_administrator_test1_ledControl_ledclose(JNIEnv *env , jobject thiz)
{
	__android_log_print(ANDROID_LOG_DEBUG,"led_jni","led_close...");
	close(fd);
}


jint Java_com_example_administrator_test1_ledControl_ledcontrol(JNIEnv *env , jobject thiz ,jint number, jint state)
{
	int ret = ioctl(fd,state,number);
	__android_log_print(ANDROID_LOG_DEBUG,"led_jni","led_control:%d,%d...",number,state);

	return ret;
}

static const JNINativeMethod methods[]={
		{"Java_com_example_administrator_test1_ledControl_ledopen","()I",(void *)Java_com_example_administrator_test1_ledControl_ledopen},
		{"Java_com_example_administrator_test1_ledControl_ledclose","()V",(void *)Java_com_example_administrator_test1_ledControl_ledclose},
		{"Java_com_example_administrator_test1_ledControl_ledcontrol","(II)I",(void *)Java_com_example_administrator_test1_ledControl_ledcontrol},
};



JNIEXPORT jint JNICALL JNIOnLoad
  (JavaVM *jvm, void *reserved)  
{  
	JNIEnv* env = NULL;  
	jclass cls;
	jint result=-1;  
	if( (*jvm)->GetEnv(jvm,(void**)&env , JNI_VERSION_1_4) != JNI_OK)  
			return JNI_ERR;	

	cls=(*env)->FindClass(env,"com/example/administrator/test1/led_control");  

	if(cls == NULL)
		return JNI_ERR;

	if((*env)->RegisterNatives(env,cls,methods,sizeof(methods)/sizeof(methods[0]))<0){
		return JNI_ERR;
	}

    return JNI_VERSION_1_4;  
}  













