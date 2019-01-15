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
[Android FFmpeg HelloWorld](https://blog.csdn.net/leixiaohua1020/article/details/47008825),
[Android FFmpeg Basic A](https://blog.csdn.net/yhaolpz/article/details/76408829),
[Android FFmegp Basic B](https://www.jianshu.com/p/6e556d336b1d)
- All FFmepg JNI source are inside `jni-ffmpeg`. run `ndk-build NDK_PROJECT_PATH={path/to/jni-ffmpeg} NDK_APPLICATION_MK={path/to/jni-ffmpeg/Application.mk}`, which will explicitly tell
NDK to compile FFmpeg JNI.
- Copy new generate `ffmpeg-jni.so` to JNI libs and should be good to build up the project.

### !!! App still crash when run FFmpeg-JNI. NDK debugging needs to be investigated based on the following logcat.
```
2019-01-15 17:52:18.147 5860-5860/? I/s.myapplicatio: Late-enabling -Xcheck:jni
2019-01-15 17:52:18.222 5860-5860/com.twobulls.myapplication I/s.myapplicatio: The ClassLoaderContext is a special shared library.
2019-01-15 17:52:18.331 5860-5875/com.twobulls.myapplication D/libEGL: loaded /vendor/lib/egl/libEGL_adreno.so
2019-01-15 17:52:18.336 5860-5875/com.twobulls.myapplication D/libEGL: loaded /vendor/lib/egl/libGLESv1_CM_adreno.so
2019-01-15 17:52:18.352 5860-5875/com.twobulls.myapplication D/libEGL: loaded /vendor/lib/egl/libGLESv2_adreno.so
2019-01-15 17:52:18.436 5860-5860/com.twobulls.myapplication W/s.myapplicatio: Accessing hidden method Landroid/view/View;->computeFitSystemWindows(Landroid/graphics/Rect;Landroid/graphics/Rect;)Z (light greylist, reflection)
2019-01-15 17:52:18.437 5860-5860/com.twobulls.myapplication W/s.myapplicatio: Accessing hidden method Landroid/view/ViewGroup;->makeOptionalFitsSystemWindows()V (light greylist, reflection)
2019-01-15 17:52:18.479 5860-5860/com.twobulls.myapplication D/FFMPEG_ANDROID: ----------command begin---------
2019-01-15 17:52:18.482 5860-5860/com.twobulls.myapplication I/AVLOG: ffmpeg version 3.3.9
2019-01-15 17:52:18.482 5860-5860/com.twobulls.myapplication I/AVLOG:  Copyright (c) 2000-2018 the FFmpeg developers
2019-01-15 17:52:18.482 5860-5860/com.twobulls.myapplication I/AVLOG:   built with gcc 4.9.x (GCC) 20150123 (prerelease)
2019-01-15 17:52:18.482 5860-5860/com.twobulls.myapplication I/AVLOG:   configuration: --target-os=linux --prefix=./android/arm --enable-cross-compile --enable-runtime-cpudetect --disable-asm --arch=arm --cc=/Users/runze/ffmpeg-ndk/android-ndk-r15c/toolchains/arm-linux-androideabi-4.9/prebuilt/darwin-x86_64/bin/arm-linux-androideabi-gcc --cross-prefix=/Users/runze/ffmpeg-ndk/android-ndk-r15c/toolchains/arm-linux-androideabi-4.9/prebuilt/darwin-x86_64/bin/arm-linux-androideabi- --disable-stripping --nm=/Users/runze/ffmpeg-ndk/android-ndk-r15c/toolchains/arm-linux-androideabi-4.9/prebuilt/darwin-x86_64/bin/arm-linux-androideabi-nm --sysroot=/Users/runze/ffmpeg-ndk/android-ndk-r15c/platforms/android-14/arch-arm --enable-gpl --enable-shared --disable-static --enable-small --disable-ffprobe --disable-ffplay --disable-ffmpeg --disable-debug --extra-cflags='-fPIC -DANDROID -D__thumb__ -mthumb -Wfatal-errors -Wno-deprecated -mfloat-abi=softfp -marm -march=armv7-a'
2019-01-15 17:52:18.482 5860-5860/com.twobulls.myapplication I/AVLOG:   libavutil      55. 58.100 / 55. 58.100
2019-01-15 17:52:18.482 5860-5860/com.twobulls.myapplication I/AVLOG:   libavcodec     57. 89.100 / 57. 89.100
2019-01-15 17:52:18.482 5860-5860/com.twobulls.myapplication I/AVLOG:   libavformat    57. 71.100 / 57. 71.100
2019-01-15 17:52:18.482 5860-5860/com.twobulls.myapplication I/AVLOG:   libavdevice    57.  6.100 / 57.  6.100
2019-01-15 17:52:18.482 5860-5860/com.twobulls.myapplication I/AVLOG:   libavfilter     6. 82.100 /  6. 82.100
2019-01-15 17:52:18.482 5860-5860/com.twobulls.myapplication I/AVLOG:   libswscale      4.  6.100 /  4.  6.100
2019-01-15 17:52:18.482 5860-5860/com.twobulls.myapplication I/AVLOG:   libswresample   2.  7.100 /  2.  7.100
2019-01-15 17:52:18.482 5860-5860/com.twobulls.myapplication I/AVLOG:   libpostproc    54.  5.100 / 54.  5.100
2019-01-15 17:52:18.482 5860-5860/com.twobulls.myapplication I/AVLOG: Splitting the commandline.
2019-01-15 17:52:18.482 5860-5860/com.twobulls.myapplication I/AVLOG: Finished splitting the commandline.
2019-01-15 17:52:18.482 5860-5860/com.twobulls.myapplication I/AVLOG: Parsing a group of options: global .
2019-01-15 17:52:18.482 5860-5860/com.twobulls.myapplication I/AVLOG: Successfully parsed a group of options.
2019-01-15 17:52:18.482 5860-5860/com.twobulls.myapplication I/AVLOG: Hyper fast Audio and Video encoder
2019-01-15 17:52:18.482 5860-5860/com.twobulls.myapplication I/AVLOG: usage: ffmpeg [options] [[infile options] -i infile]... {[outfile options] outfile}...
2019-01-15 17:52:18.483 5860-5860/com.twobulls.myapplication E/AVLOG: Use -h to get full help or, even better, run 'man ffmpeg'
2019-01-15 17:52:18.483 5860-5860/com.twobulls.myapplication E/AVLOG: At least one output file must be specified
2019-01-15 17:52:18.483 5860-5860/com.twobulls.myapplication I/AVLOG: Stream mapping:
2019-01-15 17:52:18.483 5860-5860/com.twobulls.myapplication I/AVLOG: Press [q] to stop, [?] for help
2019-01-15 17:52:18.483 5860-5860/com.twobulls.myapplication I/AVLOG: No more output streams to write to, finishing.
2019-01-15 17:52:18.483 5860-5860/com.twobulls.myapplication A/libc: Fatal signal 11 (SIGSEGV), code 1 (SEGV_MAPERR), fault addr 0x0 in tid 5860 (s.myapplication), pid 5860 (s.myapplication)
```
