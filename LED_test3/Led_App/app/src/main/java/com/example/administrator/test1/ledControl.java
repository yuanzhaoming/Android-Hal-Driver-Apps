package com.example.administrator.test1;

/**
 * Created by Administrator on 2018/4/3.
 */

public class ledControl {
    public static native  int ledopen();
    public static native  void ledclose();
    public static native  int ledcontrol(int number,int state);

    static {
        System.loadLibrary("led");
    }
}
