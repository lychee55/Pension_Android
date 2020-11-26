//
// Created by Administrator on 2019/11/14.
//这里使用了继承，音频和视频有一些公有的方法
//

#ifndef PLAYER_BASECHANNEL_H
#define PLAYER_BASECHANNEL_H

extern "C" {
#include <libavcodec/avcodec.h>
};

#include "safe_queue.h"
#include "JavaCallHelper.h"
#include "../Log.h"
class BaseChannel {
public:
    BaseChannel(int channelId, JavaCallHelper *helper, AVCodecContext *avCodecContext, AVRational
    base) : channelId(channelId),
            helper(helper),
            avCodecContext(avCodecContext),
            time_base(base) {
        pkt_queue.setReleaseHandle(releaseAvPacket);
        frame_queue.setReleaseHandle(releaseAvFrame);
    }


    virtual ~BaseChannel() {
        if (avCodecContext) {
            avcodec_close(avCodecContext);
            avcodec_free_context(&avCodecContext);
            avCodecContext = 0;
        }
        pkt_queue.clear();
        frame_queue.clear();
    };

    virtual void play() = 0;//纯虚函数

    virtual void stop() = 0;

    virtual void decode() = 0;

    void setEnable(bool enable) {
        pkt_queue.setEnable(enable);
        frame_queue.setEnable(enable);
    }

    static void releaseAvFrame(AVFrame *&frame) {
        if (frame) {
            av_frame_free(&frame);
            frame = 0;
        }
    }


    static void releaseAvPacket(AVPacket *&packet) {
        if (packet) {
            av_packet_free(&packet);
            packet = 0;
        }
    }



public:
    int channelId;
    JavaCallHelper *helper;
    AVCodecContext *avCodecContext;
    AVRational time_base;

    SafeQueue<AVPacket *> pkt_queue;//线程中使用队列，必须保证是线程安全的队列，可以通过锁，互斥量保证安全
    SafeQueue<AVFrame *> frame_queue;
    bool isPlaying = false;

    double clock = 0;

};

#endif //PLAYER_BASECHANNEL_H
