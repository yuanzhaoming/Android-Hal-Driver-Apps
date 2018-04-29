
package com.android.server;
import android.os.ILedService;

public class LedService extends ILedService.Stub{
    private static final String TAG = "LedService";
     

    public int ledctl(int which, int state) throws android.os.RemoteException
    {
        return native_ledctl(which,state);
    }

	public LedService()
	{
	    native_ledopen();
	}

	public void ledClose()
	{
		native_ledclose();
	}

	

	 public native static  int native_ledctl(int which, int state);
	 public native static  int native_ledopen( );
	 public native static  void native_ledclose( );
}























