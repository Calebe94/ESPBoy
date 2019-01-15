# COMPONENT_DEPENDS := libnet80211
APP_LD_ARGS += -L$(ESPCOMP)/esp32/lib -lcore -lnet80211 -lphy -lrtc -lpp -lwpa -lsmartconfig -lcoexist -lwps -lwpa2
