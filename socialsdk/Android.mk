LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := socialsdk

LOCAL_MODULE_FILENAME := lib$(LOCAL_MODULE)

ifeq ($(USE_ARM_MODE),1)
LOCAL_ARM_MODE := arm
endif

LOCAL_SRC_FILES := ../bindings/manual/TournamentListenerJS.cpp \
	../bindings/manual/SocialJSHelper.cpp \
	../bindings/manual/ShareListenerJS.cpp \
	../bindings/auto/2.x/jsb_social_auto.cpp \
	./dynamic_links/FirebaseDynamicLinksReceiver.cpp \
	./dynamic_links/FirebaseDynamicLinksUtils.cpp \
	../android/cpp/NativeShare.cpp \
	../android/cpp/FacebookShare.cpp \
	../android/cpp/FacebookGamingShare.cpp \
	../android/cpp/TournamentController.cpp \
	../android/cpp/ScheduledNotification.cpp
				
LOCAL_CFLAGS    += -DTARGET_PLATFORM=1

LOCAL_STATIC_LIBRARIES := cocos2dx_static
LOCAL_STATIC_LIBRARIES += logging
LOCAL_STATIC_LIBRARIES += firebase-dynamic-links
LOCAL_STATIC_LIBRARIES += jsbhelper

LOCAL_C_INCLUDES = $(LOCAL_PATH)/../
LOCAL_C_INCLUDES += $(LOCAL_PATH)/js-bindings/
LOCAL_C_INCLUDES += $(LOCAL_PATH)/dynamic_links/
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../utils/
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_C_INCLUDES)

include $(BUILD_STATIC_LIBRARY)

$(call import-module, logging)
$(call import-module, cocos)
$(call import-module, firebase)
$(call import-module, jsb-helper)
