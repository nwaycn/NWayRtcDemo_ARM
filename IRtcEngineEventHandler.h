#ifndef IRTCENGINEEVENTHANDLER_H
#define IRTCENGINEEVENTHANDLER_H

namespace nwayrtc {

class IRtcEngineEventHandler {

public:
    IRtcEngineEventHandler() {}

    //注册
    virtual void onRegistrationState(int accId, int code, const char* reason) = 0;
    virtual void onMessage(const char* message) = 0;

    //拨号
    virtual void onIncomingCall(int callId, const char* callerDisplayName, const char* callerUri) = 0;
    virtual void onCallStateChange(int callId, int stateCode, int reasonCode) = 0;

    //媒体控制
    virtual void onLocalVideoReady(int callId) = 0;
    virtual void onRemoteVideoReady(int callId) = 0;
    virtual void onUpdatedByLocal(int callId, bool video) = 0;
    virtual void onUpdatedByRemote(int callId, bool video) = 0;

protected:
    virtual ~IRtcEngineEventHandler() {}   
};

}
#endif // IRTCENGINEEVENTHANDLER_H
