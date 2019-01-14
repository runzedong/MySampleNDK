## Android NDK Sample Project
### !!! This project is still under development. !!!
### Setup !! build with ndk-build command. It's not the most updated CMake approach
1. Make sure NDK configure properly. Run `ndk-build` in the terminal to verify
2. Look at [Google NDK guide](https://developer.android.com/ndk/samples/sample_hellojni) to create C source file, build script and Java JNI class
3. Since it's a deprecated approach we need to do the following tweaks to make it work:
- Be careful with the project structure. `jni` and `libs` folder location
- Run `ndk-build` under `jni` folder alone with `.mk` file and C source code, this will generate the share file under libs folder for `arm`, `x86` arch
- In order to tell Gradle where the share files are, add `android.useDeprecatedNdk=true;` at `gradle.properties` and make sure add `ndk.dir` at `local.properties`, for an instance `ndk.dir=$home/Library/Android/sdk/ndk-bundle`
- Explicitly point out jni libs directory at app `build.gradle`
```
// build.gradle
android {
//
   //...
    sourceSets {
        main {
            jniLibs.srcDirs  'src/main/libs'
        }
    }
}    
```

It should be all set to build up the project.

### Work with prebuilt library - [FFMpeg](https://ffmpeg.org/)
In order to configure FFmpeg C library into sample, we need to do the following:
1. Cross compile FFmpeg for Android.
- Ideally we need to compile FFMpeg for `arm64`, `arm`, `x86_64`, `x86` and `mips` arch. But since most mobile devices
are powered by ARM, so only `arm` 32 bits is workable for this project, considering backward compatibility of `arm64` arch.
- Honestly it's huge work on compiling this library with proper configuration. Different configuration will reflect different share file size, which will directly affect app size in production concern. Here are some blogs I looked at, unfortunately they are Chinese resource. But I believes there are more valuable English resources on Google.
[Android FFmpeg HelloWorld](https://blog.csdn.net/leixiaohua1020/article/details/47008825)
[Android FFmpeg Basic A](https://blog.csdn.net/yhaolpz/article/details/76408829)
[Android FFmegp Basic B](https://www.jianshu.com/p/6e556d336b1d)
