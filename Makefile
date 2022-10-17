CC     = arm-linux-gnueabihf-g++ -g -O
STRIP  = arm-linux-gnueabihf-strip 


#ifeq ($(v),0)
##LIBSIP  = ./libs/libaudio.so ./libs/libasound.so.2 -ldl 
#else 
#STAGING_DIR = /home/david/gcc-sigmastar-9.1.0-2020.07-x86_64_arm-linux-gnueabihf/arm-linux-gnueabihf/libc
#STAGING_LIB = $(STAGING_DIR)/usr/lib
LIBSIP  = ./lib/libsipengine.so ./lib/libmediaengine.so ./lib/libnwayrtcsdk.so
#endif
#target
NWAYRTCSDKDEMO  = ./nWayRtcSdkDemo
SRCS = $(wildcard ./*.cpp) $(wildcard ./*.c) $(wildcard ./*.c)
OBJS = $(patsubst %.cpp,%.o,$(SRCS))
LIBS = $(LIBSIP) -lstdc++ -lpthread
INCLUDES = -I./headers/
VERSIONRELEASE=10


$(NWAYRTCSDKDEMO): $(OBJS)
	$(CC) -fPIC -o $@ $^ $(LIBS) $(INCLUDES)

%.o: %.cpp
	$(CC) $(CFLAGS) -fPIC -std=gnu++11 -DXAPP_VERSION_RELEASE=$(VERSIONRELEASE) $(INCLUDES) $(FLAG) -o $@ -c $< 

clean:
	rm ./*.o
	rm $(NWAYRTCSDKDEMO)
