LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_SRC_FILES := hellocpp/main.cpp \
				../../Classes/AppDelegate.cpp \
				../../Classes/Fighter/Fighter.cpp \
				../../Classes/Fighter/Items/AntiRocket.cpp \
				../../Classes/Fighter/Items/B52Bomb.cpp \
				../../Classes/Fighter/Items/BombSquad.cpp \
				../../Classes/Fighter/Items/FireBomb.cpp \
				../../Classes/Fighter/Items/IItem.cpp \
				../../Classes/Fighter/Items/Items.cpp \
				../../Classes/Fighter/Items/IndianSwat.cpp \
				../../Classes/Fighter/Items/MarineBomb.cpp \
				../../Classes/Fighter/Items/SpecialForce.cpp \
				../../Classes/Fighter/Items/ViewFinder.cpp \
				../../Classes/Missions/Land.cpp \
				../../Classes/Missions/Map.cpp \
				../../Classes/Missions/MapProccessor.cpp \
				../../Classes/Targets/IUnit.cpp \
				../../Classes/Targets/Target.cpp \
				../../Classes/Targets/map_berlin/BombWarning.cpp \
				../../Classes/Targets/map_car/FakedCar.cpp \
				../../Classes/Targets/map_car/NormalCar.cpp \
				../../Classes/Targets/map_egypt/CiviEgypt.cpp \
				../../Classes/Targets/map_egypt/ISEgypt.cpp \
				../../Classes/Targets/map_india/IsIndian.cpp \
				../../Classes/Targets/map_iraq/ISIraq.cpp \
				../../Classes/Targets/map_london_isarel/ISBodyInvi.cpp \
				../../Classes/Targets/map_morocco/ISFire.cpp \
				../../Classes/Targets/map_morocco/ISKnife.cpp \
				../../Classes/Targets/map_morocco/ISMorocco.cpp \
				../../Classes/Targets/map_morocco/ISVictim.cpp \
				../../Classes/Targets/map_morocco/ISVictim_Cage.cpp \
				../../Classes/Targets/map_pakistan/Alqueda.cpp \
				../../Classes/Targets/map_pakistan/AlquedaFire.cpp \
				../../Classes/Targets/map_pakistan/AlquedaRocket.cpp \
				../../Classes/Targets/map_pakistan/AlquedaVictim.cpp \
				../../Classes/Targets/map_paris/ISManHole.cpp \
				../../Classes/Targets/map_paris/NormalManHole.cpp \
				../../Classes/Targets/map_russia/SubMarine.cpp \
				../../Classes/Targets/map_syria/ISSyria.cpp \
				../../Classes/Targets/map_train/NormalBoxTrain.cpp \
				../../Classes/Targets/map_train/SeriousBoxTrain.cpp \
				../../Classes/GameOverScene.cpp \
				../../Classes/SplashScene.cpp \
				../../Classes/GameScene.cpp \
				../../Classes/Engine.cpp \
				../../Classes/ScreenManager.cpp \
				../../Classes/MainMenuScene.cpp	\
				../../Classes/SonarFrameworks.cpp \
				../../Classes/JNIHelpers.cpp \
				../../Classes/JNIResults.cpp \

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
					$(LOCAL_PATH)/../../Classes/Fighter \
					$(LOCAL_PATH)/../../Classes/Fighter/Items \
					$(LOCAL_PATH)/../../Classes/Missions \
					$(LOCAL_PATH)/../../Classes/Targets \
					$(LOCAL_PATH)/../../Classes/Targets/map_berlin \
					$(LOCAL_PATH)/../../Classes/Targets/map_car \
					$(LOCAL_PATH)/../../Classes/Targets/map_egypt \
					$(LOCAL_PATH)/../../Classes/Targets/map_india \
					$(LOCAL_PATH)/../../Classes/Targets/map_iraq \
					$(LOCAL_PATH)/../../Classes/Targets/map_london_isarel \
					$(LOCAL_PATH)/../../Classes/Targets/map_morocco \
					$(LOCAL_PATH)/../../Classes/Targets/map_paris \
					$(LOCAL_PATH)/../../Classes/Targets/map_pakistan \
					$(LOCAL_PATH)/../../Classes/Targets/map_russia \
					$(LOCAL_PATH)/../../Classes/Targets/map_syria \
					$(LOCAL_PATH)/../../Classes/Targets/map_train \
					$(LOCAL_PATH)/../../Classes/Utility 

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
