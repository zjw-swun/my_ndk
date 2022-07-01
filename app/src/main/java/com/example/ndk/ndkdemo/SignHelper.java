package com.example.ndk.ndkdemo;

import android.content.Context;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.Signature;

/**
 * Created by Liszt on 2019/7/6.
 */

public class SignHelper {
    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
//    public static native String stringFromJNI();

    public static native String getSign(Context context);
    public static native String getSignToken(Context context,String userId);
    public static native String getSignaturesSha1(Context context);
    public static native boolean checkSha1(Context context);
    public static native void throwNativeCrash();



    public static String getSignature(Context context) {
        try {
            PackageInfo packageInfo = context.getPackageManager().getPackageInfo(context.getPackageName(), PackageManager.GET_SIGNATURES);
            Signature[] signatures = packageInfo.signatures;
            if (signatures != null) {
                return signatures[0].toCharsString();
            }
        } catch (PackageManager.NameNotFoundException e) {
            e.printStackTrace();
        }
        return "";
    }

}
