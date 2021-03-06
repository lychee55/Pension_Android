package com.warehouse.video;


import android.view.Surface;

public class VideoPlayer {

    static {
        System.loadLibrary("native-lib");
    }

    private final long nativeHandle;

    public VideoPlayer() {
        nativeHandle = nativeInit();
    }

    public void setDataSource(String path) {
        setDataSource(nativeHandle, path);
    }

    // 获取媒体文件音视频信息，准备好解码器
    public void prepare() {
        prepare(nativeHandle);
    }

    public void setSurface(Surface surface) {
        setSurface(nativeHandle, surface);
    }//用来传递surface，作用是传递ANativeWindow窗口

    public void start() {
        start(nativeHandle);
    }


    public void stop() {
        stop(nativeHandle);
    }


    private native long nativeInit();

    private native void setDataSource(long nativeHandle, String path);

    private native void prepare(long nativeHandle);

    private native void start(long nativeHandle);

    private native void setSurface(long nativeHandle, Surface surface);

    private native void stop(long nativeHandle);

    private void onError(int errorCode) {
        if (null != onErrorListener) {
            onErrorListener.onError(errorCode);
        }
    }

    private void onPrepare() {
        if (null != onPrepareListener) {
            onPrepareListener.onPrepared();
        }
    }

    private void onProgress(int progress) {
        if (null != onProgressListener) {
            onProgressListener.onProgress(progress);
        }
    }

    private OnErrorListener onErrorListener;
    private OnProgressListener onProgressListener;
    private OnPrepareListener onPrepareListener;

    public void setOnErrorListener(OnErrorListener onErrorListener) {
        this.onErrorListener = onErrorListener;
    }

    public void setOnPrepareListener(OnPrepareListener onPrepareListener) {
        this.onPrepareListener = onPrepareListener;
    }

    public void setOnProgressListener(OnProgressListener onProgressListener) {
        this.onProgressListener = onProgressListener;
    }

    public interface OnErrorListener {
        void onError(int err);
    }

    public interface OnPrepareListener {
        void onPrepared();
    }

    public interface OnProgressListener {
        void onProgress(int progress);
    }


}
