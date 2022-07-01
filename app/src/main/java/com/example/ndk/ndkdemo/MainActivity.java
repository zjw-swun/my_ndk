package com.example.ndk.ndkdemo;

import androidx.appcompat.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

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
        tv_show.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                SignHelper.throwNativeCrash();
            }
        });

        //是否二次打包
        if (SignHelper.checkSha1(this)) {
            System.out.println("没有被二次打包");
            Toast.makeText(this,"没有被二次打包",Toast.LENGTH_LONG).show();
        } else {
            System.out.println("被二次打包了");
            Toast.makeText(this,"被二次打包了",Toast.LENGTH_LONG).show();
        }

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

