
#ifndef NWAYRTC_H
#define NWAYRTC_H

#include <cstdio>
#include <stdint.h>
#include "IRtcEngineEventHandler.h"
#include <list>

namespace nwayrtc {

class NWayRtc
{
public:
    //SipEngineManager *getSipEngineManager();
    //QVariantList getRecordingDeviceList();
    //QVariantList getPlayoutDeviceList();
    //QVariantList getVideoDeviceList();
    virtual int setRecordingDevice(const char* guid) = 0;
    virtual int setPlayoutDevice(const char* guid) = 0;
    virtual int setVideoDevice(const char* guid) = 0;
    virtual int registerAccount(const char* serverIp, const char* username,
                            const char* password, const char* displayname) = 0;
    virtual int call(const char* calleeUri) = 0;
    virtual void callForward(std::list<const char*> callForwardUsers, const char* localDisplayName,
                             bool isVideo, bool hwAcceleration, int width,
                             int height, int fps, int bitrate, const char* deviceType) = 0;
    virtual int earlyAnswer(int callId) = 0;
    virtual int answer(int callId) = 0;
    virtual int hangup(int callId) = 0;
    //virtual void setupLocalVideo(int callId, VideoSink* videoSink) = 0;
    //virtual void setupRemoteVideo(int callId, VideoSink* videoSink) = 0;
    virtual void setNWayRtcEvent(IRtcEngineEventHandler* iRtcEngineEventHandler) = 0;
    virtual void flowStream() = 0;

    virtual void sendVideoPacket(const uint8_t* packet, int len, uint8_t payloadType, uint32_t timeStamp) = 0;
public:
    static NWayRtc* createNWayRtcEngine();
};

} //end of nwayrtc namespace

#endif // NWAYRTC_H
