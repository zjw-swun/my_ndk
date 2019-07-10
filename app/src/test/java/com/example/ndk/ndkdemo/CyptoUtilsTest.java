package com.example.ndk.ndkdemo;

import org.junit.Test;

/**
 * Created by LL130386 on 2019/7/9.
 */
public class CyptoUtilsTest {

    @Test
    public void aesDecode() {
        String aesEncode = CyptoUtils.aesEncode("我会好好的");
        System.out.println("加密后：" + aesEncode);
        String aesDecode = CyptoUtils.aesDecode(aesEncode);
        System.out.println("解密后：" + aesDecode);
    }


    @Test
    public void aesEncode() {

    }

}