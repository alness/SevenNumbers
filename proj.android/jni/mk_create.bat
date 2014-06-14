echo LOCAL_PATH := $(call my-dir)> Android.mk
echo;>> Android.mk
echo include $(CLEAR_VARS)>> Android.mk
echo;>> Android.mk
echo LOCAL_MODULE := cocos2dcpp_shared>> Android.mk
echo;>> Android.mk
echo LOCAL_MODULE_FILENAME := libcocos2dcpp>> Android.mk
echo;>> Android.mk



set startDir=%cd%
cd ..
cd ..
cd %cd%/Classes

setlocal enabledelayedexpansion
type nul > dir.txt
for /f "usebackq tokens=*" %%i in (`dir *.cpp /b/s`) do (

set line=%%i
set outtext=../../Classes!line:%cd%=!
echo !outtext:\=/! \>> dir.txt
)

type nul > headerDir.txt
set local=$(LOCAL_PATH)
echo LOCAL_C_INCLUDES := %local%/../../Classes \>> headerDir.txt
for /f "usebackq tokens=*" %%j in (`dir /b/a:d /s`) do (
set headerline=%%j
set headertext=/../../Classes!headerline:%cd%=!
echo !local!!headertext:\=/! \>> headerDir.txt
)


endlocal

cd %startDir%

setlocal enabledelayedexpansion

set /a COUNT=0
for /f %%A in ('find /c /v "" ^< ../../Classes/dir.txt') do set L=%%A

for /f "delims=" %%b in (../../Classes/dir.txt) do (
    set /a COUNT=COUNT+1
    set target=%%b
    IF "!L!" == "!COUNT!" (
       echo                    !target:~0,-2!>> Android.mk
    ) ELSE IF "1" == "!COUNT!" (
       echo LOCAL_SRC_FILES := hellocpp/main.cpp \>> Android.mk
       echo                    !target!>> Android.mk
    ) ELSE (
       echo                    !target!>> Android.mk
    )
)

echo;>> Android.mk


set /a COUNT=0
for /f %%A in ('find /c /v "" ^< ../../Classes/headerDir.txt') do set L=%%A

for /f "delims=" %%b in (../../Classes/headerDir.txt) do (
    set /a COUNT=COUNT+1
    set target=%%b
    IF "!L!" == "!COUNT!" (
       echo                    !target:~0,-2!>> Android.mk
    ) ELSE IF "1" == "!COUNT!" (
       echo !target!>> Android.mk
    )ELSE (
       echo                    !target!>> Android.mk
    )
)

endlocal


echo;>> Android.mk
echo LOCAL_WHOLE_STATIC_LIBRARIES += cocos2dx_static>> Android.mk
echo LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static>> Android.mk
echo LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static>> Android.mk
echo LOCAL_WHOLE_STATIC_LIBRARIES += chipmunk_static>> Android.mk
echo LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static>> Android.mk
echo;>> Android.mk
echo include $(BUILD_SHARED_LIBRARY)>> Android.mk
echo;>> Android.mk
echo $(call import-module,cocos2dx)>> Android.mk
echo $(call import-module,cocos2dx/platform/third_party/android/prebuilt/libcurl)>> Android.mk
echo $(call import-module,CocosDenshion/android)>> Android.mk
echo $(call import-module,extensions)>> Android.mk
echo $(call import-module,external/Box2D)>> Android.mk
echo $(call import-module,external/chipmunk)>> Android.mk