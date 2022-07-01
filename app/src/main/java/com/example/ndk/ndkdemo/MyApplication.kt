package com.example.ndk.ndkdemo

import android.app.Application
import com.example.lib_signal.SignalConst
import com.example.lib_signal.SignalController

class MyApplication : Application() {
    override fun onCreate() {
        super.onCreate()
        SignalController(this).initWithSignals(intArrayOf(SignalConst.SIGQUIT,SignalConst.SIGABRT))
    }
}