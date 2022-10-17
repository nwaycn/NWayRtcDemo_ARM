#include "nwayrtc.h"
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/statfs.h>  

/* This is for demo only. Should be replace with real H264 encoder output */
int read_one_frame_from_demo_video_file(unsigned char *pVideoBuf,unsigned int offset,unsigned int BufSize,unsigned int *IskeyFrame,unsigned int 
*FramLen,unsigned int *Frame_start)
{
    int pos = 0;
    int bNeedCal = 0;
    unsigned char NalType=0;
    int idx=0;
    if(BufSize<=5)
    {
        printf("bufSize is too small\n");
        return -1;
    }
    for(pos=0;pos <= BufSize-5;pos++)
    {
        if(pVideoBuf[pos]==0x00
            &&pVideoBuf[pos+1]==0x00
            &&pVideoBuf[pos+2]==0x00
            &&pVideoBuf[pos+3]==0x01)
        {
            NalType = pVideoBuf[pos + 4] & 0x1f;
            if(NalType == 0x7)
            {
                if(bNeedCal==1)
                {
                    *FramLen=pos-idx;
                    return 0;
                }
                
                *IskeyFrame = 1;
                *Frame_start = offset+pos;
                bNeedCal=1;
                idx=pos;
            }
            else if(NalType ==0x1)                
            {
               if(bNeedCal)
               {
                  *FramLen=pos-idx;
                  return 0;
               }
               *Frame_start=offset+pos;
               *IskeyFrame = 0;
               idx = pos;
               bNeedCal=1;
            }
        }
    }
    
    return 0;
}

int main()
{
    nwayrtc::NWayRtc* nwayRtc;
    nwayRtc = nwayrtc::NWayRtc::createNWayRtcEngine();
    nwayRtc->registerAccount("120.24.192.241", "1005", "2345", "david");
    usleep(1000000);
   
    printf("start live video 1\n");
    if(nwayRtc != nullptr) {
       nwayRtc->call("1003");
    }
    printf("start live video 2\n");

     
    char raw_fullpath[128] = {0};
    char info_fullpath[128] = {0};
    unsigned int FrameLen=0,Frame_start=0;
    unsigned int offset=0;
    unsigned int IsKeyFrame=0;
    unsigned char *pVideoBuf = NULL;
    sprintf(raw_fullpath, "./fp_video_out.h264");

    printf("start live video using %s \n",raw_fullpath);

    FILE *streamBin_fp = fopen(raw_fullpath, "rb");
    if((streamBin_fp == NULL))
    {
        printf("can't read live video file %s\n",raw_fullpath);
		return 0;
        pthread_exit(0);
    }
    fseek(streamBin_fp, 0, SEEK_END);
    unsigned int file_size = ftell(streamBin_fp);
    fseek(streamBin_fp, 0, SEEK_SET);
    pVideoBuf = (unsigned char *)malloc(file_size);
    fread(pVideoBuf, 1, file_size, streamBin_fp);

	while(1)
	{
		offset=Frame_start+FrameLen;
		if(offset>=file_size)
		{
			offset=0;
		}
		read_one_frame_from_demo_video_file(pVideoBuf+offset,offset,file_size-offset,&IsKeyFrame,&FrameLen,&Frame_start);
		//Note: For I frame of H264, SPS/PPS/SEI/IDR should be combined within one frame, and the NALU separator should NOT be deleted.

		int frameRate = 30;
		int sleepTick = 1000000/frameRate;
		/* Send HD video data to the SDK */
		nwayRtc->sendVideoPacket(pVideoBuf+Frame_start, FrameLen, 0, 0);

		usleep(sleepTick);
	}    
    return 1;
}

