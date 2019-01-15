package com.twobulls.myapplication.jni;

public class FFmpegJni {

    public static native void run(String[] commands);

    static {
        System.loadLibrary("avcodec-57");
        System.loadLibrary("avdevice-57");
        System.loadLibrary("avformat-57");
        System.loadLibrary("avutil-55");
        System.loadLibrary("avfilter-6");
        System.loadLibrary("postproc-54");
        System.loadLibrary("swscale-4");
        System.loadLibrary("swresample-2");
        System.loadLibrary("ffmpeg-jni");
    }
}
