/*
 * ---------------------------------------------------------------------
 * Copyright (c) 2014~2016 All Right Reserved
 * This software is developed for study and improve coding skill ...
 *
 * Project:  Enjoyable Coding< EC >
 *
 * iOS_AudioRender.h
 * Here we define a class to Package the iOS platform audio render.
 *
 * Eamil:   epengao@126.com
 * Author:  Peter Gao
 * Version: Intial first version.
 * --------------------------------------------------------------------
 */

#ifndef IOS_AUDIO_RENDER_H
#define IOS_AUDIO_RENDER_H

#define MAX_BUFFER_SIZE     192000
#define QUEUE_BUFFER_COUNT       4


#include "ECSignal.h"
#include "MediaCommon.h"
#include "ECSemaphore.h"
#include "AudioRenderDeviceI.h"
#include <AudioToolbox/AudioToolbox.h>

class iOS_AudioRender : public AudioRenderDeviceI
{
public:
    iOS_AudioRender();
    ~iOS_AudioRender();
public:
    EC_U32 Init(MediaCtxInfo* pMediaInfo,
                AudioPCMBuffer *pFirstFrame);
    EC_VOID Uninit();
    EC_VOID Run();
    EC_VOID Pause();
    EC_VOID Stop();
    EC_VOID Flush();
    EC_VOID SendPCMData(AudioPCMBuffer *pBuffer, EC_U32 nSize);
private:
    static EC_VOID PlaySoundCallback(
                                     EC_VOID *pUserData,
                                     AudioQueueRef inQueue,
                                     AudioQueueBufferRef outQueueBuf);
private:
    ECMutex                     m_mtxPCMBuffer;
    EC_U32                      m_nCurrFillBufIndex;
    EC_BOOL                     m_bNeedFillBufQueue;
    ECSemaphore                 m_semRendStopedSignal;
    ECSemaphore                 m_semFillPCMBufSignal;
    ECSemaphore                 m_semRendFinishedSignal;
    MediaEngStatus              m_nStatus;
    AudioQueueRef               m_rAudioQueue;
    AudioQueueBufferRef         m_sCurrAudioQueueBuf;
    AudioQueueBufferRef         m_sAudioQueueBuffers[QUEUE_BUFFER_COUNT];
    AudioStreamBasicDescription m_sAudioDescription;
    EC_BOOL                     m_bRndCallbackFinished;
};

#endif /* IOS_AUDIO_RENDER_H */
