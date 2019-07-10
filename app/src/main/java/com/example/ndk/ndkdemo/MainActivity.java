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

//        if (SignHelper.getSignature(this).contains(SignHelper.getSign(this))) {
//            System.out.println("成功");
//        } else {
//            System.out.println("失败");
//        }

        String aesEncode = CyptoUtils.aesEncode("我会好好的");
        System.out.println("加密后：" + aesEncode);
        String aesDecode = CyptoUtils.aesDecode(aesEncode);
        System.out.println("解密后：" + aesDecode);
        System.out.println("----------------------------------------------------");
        String aesEncodeNative = CyptoUtils.encode(this, "我会好好的");
        System.out.println("native加密后：" + aesEncodeNative);
        String aesDecodeN = CyptoUtils.decode(this, aesEncodeNative);
        System.out.println("native解密后：" + aesDecodeN);
    }


}

