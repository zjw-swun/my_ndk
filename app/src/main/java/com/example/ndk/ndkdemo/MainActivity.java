package com.example.ndk.ndkdemo;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        // Example of a call to a native method
        TextView tv = (TextView) findViewById(R.id.sample_text);
        tv.setText(SignHelper.getSignature(this));

        TextView tv_show = (TextView) findViewById(R.id.tv_show);
        tv_show.setText(SignHelper.getSign(this));

        if (SignHelper.getSignature(this).contains(SignHelper.getSign(this))) {
            System.out.println("成功");
        } else {
            System.out.println("失败");
        }


    }


}
