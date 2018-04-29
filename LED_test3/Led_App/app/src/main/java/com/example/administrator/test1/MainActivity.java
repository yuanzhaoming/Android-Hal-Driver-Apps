package com.example.administrator.test1;

import android.content.Context;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.Gravity;
import android.view.KeyEvent;
import android.view.View;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.CompoundButton;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {
    private Button button1;
    private CheckBox checkbox1;
    private CheckBox checkbox2;
    private CheckBox checkbox3;
    private CheckBox checkbox4;


    private int button_pressed = 0;
    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        ledControl.ledopen();
        button1 = (Button)findViewById(R.id.button);
        checkbox1 = (CheckBox) findViewById(R.id.checkBox);
        checkbox2 = (CheckBox) findViewById(R.id.checkBox2);
        checkbox3 = (CheckBox) findViewById(R.id.checkBox3);
        checkbox4 = (CheckBox) findViewById(R.id.checkBox4);
        button1.setOnClickListener(
                new View.OnClickListener() {
                    @Override
                    public void onClick(View v) {
                        Context context = getApplicationContext();
                        CharSequence text = "Hello toast!";
                        if(button_pressed == 0){
                            text = "all led on!";
                            checkbox1.setChecked(true);
                            checkbox2.setChecked(true);
                            checkbox3.setChecked(true);
                            checkbox4.setChecked(true);

                            for(int i = 0 ;  i < 4 ; i ++){

                                ledControl.ledcontrol(i,1);
                            }
                        }
                        else
                        {
                            text = "all led off!";
                            checkbox1.setChecked(false);
                            checkbox2.setChecked(false);
                            checkbox3.setChecked(false);
                            checkbox4.setChecked(false);

                            for(int i = 0 ;  i < 4 ; i ++){

                                ledControl.ledcontrol(i,0);
                            }
                        }
                        button_pressed ++;
                        button_pressed = button_pressed % 2;

                        int duration = Toast.LENGTH_SHORT;
                        Toast toast = Toast.makeText(context, text, duration);
                        toast.setGravity(Gravity.BOTTOM| Gravity.CENTER_VERTICAL, 0, 0);
                        toast.show();
                    }
                }
        );

        checkbox1.setOnClickListener(
                new View.OnClickListener() {
                    @Override
                    public void onClick(View v) {
                        Context context = getApplicationContext();
                        CharSequence text = "checkbox2 clicked";

                        if(checkbox1.isChecked()){
                            text = "led1 on";

                            ledControl.ledcontrol(0,1);
                        }
                        else
                        {
                            text = "led1 off";
                            ledControl.ledcontrol(0,0);
                        }

                        int duration = Toast.LENGTH_SHORT;

                        Toast toast = Toast.makeText(context, text, duration);
                        toast.setGravity(Gravity.BOTTOM| Gravity.CENTER_VERTICAL, 0, 0);
                        toast.show();
                    }
                }
        );

        checkbox2.setOnClickListener(
                new View.OnClickListener() {
                    @Override
                    public void onClick(View v) {
                        Context context = getApplicationContext();
                        CharSequence text = "checkbox2 clicked";

                        if(checkbox2.isChecked()){
                            text = "led2 on";
                            ledControl.ledcontrol(1,1);
                        }
                        else
                        {
                            text = "led2 off";
                            ledControl.ledcontrol(1,0);
                        }

                        int duration = Toast.LENGTH_SHORT;

                        Toast toast = Toast.makeText(context, text, duration);
                        toast.setGravity(Gravity.BOTTOM| Gravity.CENTER_VERTICAL, 0, 0);
                        toast.show();
                    }
                }
        );

        checkbox3.setOnClickListener(
                new View.OnClickListener() {
                    @Override
                    public void onClick(View v) {
                        Context context = getApplicationContext();
                        CharSequence text = "checkbox3 clicked";

                        if(checkbox3.isChecked()){
                            text = "led3 on";
                            ledControl.ledcontrol(2,1);
                        }
                        else
                        {
                            text = "led3 off";
                            ledControl.ledcontrol(2,0);
                        }
                        int duration = Toast.LENGTH_SHORT;
                        Toast toast = Toast.makeText(context, text, duration);
                        toast.setGravity(Gravity.BOTTOM| Gravity.CENTER_VERTICAL, 0, 0);
                        toast.show();
                    }
                }
        );

        checkbox4.setOnClickListener(
                new View.OnClickListener() {
                    @Override
                    public void onClick(View v) {
                        Context context = getApplicationContext();
                        CharSequence text = "checkbox3 clicked";

                        if(checkbox4.isChecked()){
                            text = "led4 on";
                            ledControl.ledcontrol(3,1);
                        }
                        else
                        {
                            text = "led4 off";
                            ledControl.ledcontrol(3,0);
                        }
                        int duration = Toast.LENGTH_SHORT;
                        Toast toast = Toast.makeText(context, text, duration);
                        toast.setGravity(Gravity.BOTTOM| Gravity.CENTER_VERTICAL, 0, 0);
                        toast.show();
                    }
                }
        );
        // Example of a call to a native method
        //TextView tv = (TextView) findViewById(R.id.sample_text);
        //tv.setText(stringFromJNI());
    }




    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
}
