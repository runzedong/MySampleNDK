package com.twobulls.myapplication.jni;

public class SimpleJni {

    /*
     * a native method implemented by the `hello-jni` libbrary
     * packaged in the application.
     */
    public static native String stringFromJni();

    /*
     * This is another native method but *not* implemented. This is simply to show that
     * you can declare as many native methods in your java code as you want, and their
     * implementation will be searched in the currently loaded native libs only the first time
     * you call them.
     *
     * Try to call this function will result in a java.lang.UnsatisfiedLinkError exception.
     */
    public static native String unimplementedStringFromJni();

    /*
     * this is to load the 'hello-jni' library on application start up. The library has already been
     * unpacked into ./libs
     */
    static {
        System.loadLibrary("hello-jni");
    }
}
