package com.example.ndk.ndkdemo;

import com.google.common.io.BaseEncoding;

import java.net.URLDecoder;
import java.net.URLEncoder;

import javax.crypto.Cipher;
import javax.crypto.spec.IvParameterSpec;
import javax.crypto.spec.SecretKeySpec;

/**
 * 加密解密工具包
 * AES加密后不能直接通过new String()转变为字符串
 *
 * @author Winter Lau
 * @date 2011-12-26
 */
public class CyptoUtils {

    public static final String DES_KEY = "king@7cc";

    public static final String AS_KEY = "VX9/jMv2Ggb2XAeZ";
    public static final byte[] IVBTS = {0x38, 0x31, 0x37, 0x34, 0x36, 0x33, 0x35, 0x33, 0x32, 0x31, 0x34, 0x38, 0x37, 0x36, 0x35, 0x32};
    public static final String KEY_ALGORITHM = "AES";
    public static final String KEY_ALGORITHM_PADDING = "AES/CBC/PKCS5Padding";
//	static {
//		System.loadLibrary("dc");
//	}


    //AES  decrypt解密
    public static String aesDecode(String txt) {
        try {
            byte[] baBytes = BaseEncoding.base64().decode(URLDecoder.decode(txt, "utf-8"));
            IvParameterSpec zeroIv = new IvParameterSpec(IVBTS);
            SecretKeySpec key = new SecretKeySpec(AS_KEY.getBytes(), KEY_ALGORITHM);
            Cipher cipher = Cipher.getInstance(KEY_ALGORITHM_PADDING);
            cipher.init(Cipher.DECRYPT_MODE, key, zeroIv);
            byte[] bytes = cipher.doFinal(baBytes);
            return new String(bytes);
        } catch (Exception e) {
            e.printStackTrace();
        }
        return null;
    }

    //AES  decrypt加密
    public static String aesEncode(String txt) {
        IvParameterSpec zeroIv = new IvParameterSpec(IVBTS);
        SecretKeySpec key = new SecretKeySpec(AS_KEY.getBytes(), KEY_ALGORITHM);
        try {
            Cipher cipher = Cipher.getInstance(KEY_ALGORITHM_PADDING);
            cipher.init(Cipher.ENCRYPT_MODE, key, zeroIv);
            byte[] bytes = cipher.doFinal(txt.getBytes());
            String en64 = BaseEncoding.base64().encode(bytes);
            return URLEncoder.encode(en64, "utf-8");
        } catch (Exception e) {
            e.printStackTrace();
        }
        return "";

    }

}
