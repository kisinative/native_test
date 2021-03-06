LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
                   ../../Classes/AppDelegate.cpp \
                   ../../Classes/TitleScene.cpp \
                   ../../Classes/PowerUpScene.cpp \
                   ../../Classes/GameOverScene.cpp \
                   ../../Classes/WinnerScene.cpp \
                   ../../Classes/KSAnimation.cpp \
                   ../../Classes/BFSprite.cpp \
                   ../../Classes/NendIconModule.cpp \
                   ../../Classes/NendModule.cpp \
                   ../../Classes/Android/AdViewManager.cpp \
                   ../../Classes/Android/AdGameFeat.cpp \
                   ../../Classes/HelloWorldScene.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../Classes/Android

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static


include $(BUILD_SHARED_LIBRARY)

$(call import-module,2d)
$(call import-module,audio/android)
$(call import-module,Box2D)
