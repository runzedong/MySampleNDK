package com.twobulls.myapplication

import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import com.twobulls.myapplication.jni.SimpleJni
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        my_text_view.text = SimpleJni.stringFromJni()
    }
}
