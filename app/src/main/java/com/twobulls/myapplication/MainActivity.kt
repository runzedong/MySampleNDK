package com.twobulls.myapplication

import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.widget.Toast
import com.twobulls.myapplication.jni.FFmpegJni
import com.twobulls.myapplication.jni.SimpleJni
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        my_text_view.text = SimpleJni.stringFromJni()

        FFmpegJni.run(arrayOf("-version"))
//        val command = arrayOf("ffmpeg", "-version")
//        val result = FFmpegJni.run(command)
//        Toast.makeText(this, "Command result: ${result}", Toast.LENGTH_LONG).show()
    }
}
