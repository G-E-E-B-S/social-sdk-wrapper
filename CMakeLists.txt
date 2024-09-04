set (PROJ_SOURCES
    ${CMAKE_CURRENT_LIST_DIR}/android/cpp/NativeShare.cpp
    ${CMAKE_CURRENT_LIST_DIR}/android/cpp/FacebookShare.cpp
    ${CMAKE_CURRENT_LIST_DIR}/android/cpp/FacebookGamingShare.cpp
    ${CMAKE_CURRENT_LIST_DIR}/android/cpp/TournamentController.cpp
    ${CMAKE_CURRENT_LIST_DIR}/android/cpp/ScheduledNotification.cpp
    # ${CMAKE_CURRENT_LIST_DIR}/socialsdk/dynamic_links/FirebaseDynamicLinksReceiver.cpp
    # ${CMAKE_CURRENT_LIST_DIR}/socialsdk/dynamic_links/FirebaseDynamicLinksUtils.cpp
    ${CMAKE_CURRENT_LIST_DIR}/bindings/manual/TournamentListenerJS.cpp
    ${CMAKE_CURRENT_LIST_DIR}/bindings/manual/SocialJSHelper.cpp
    ${CMAKE_CURRENT_LIST_DIR}/bindings/manual/ShareListenerJS.cpp
)
add_definitions(-DIS_ANDROID)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DTARGET_PLATFORM=1")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DTARGET_PLATFORM=1")

if (COCOS_3_7_PLUS)
    list(APPEND PROJ_SOURCES
        ${CMAKE_CURRENT_LIST_DIR}/bindings/auto/3.7.x/jsb_social_auto.cpp
    )
elseif(COCOS_3_X_PLUS)
    list(APPEND PROJ_SOURCES
        ${CMAKE_CURRENT_LIST_DIR}/bindings/auto/3.x.x_3.6.x/jsb_social_auto.cpp
    )
else()
    list(APPEND PROJ_SOURCES
        ${CMAKE_CURRENT_LIST_DIR}/bindings/auto/2.x/jsb_social_auto.cpp
    )
endif()

set(SOCIAL_SDK_INCLUDE_LIST
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/external
)

add_library(social_sdk STATIC ${PROJ_SOURCES})    

target_include_directories(social_sdk PUBLIC 
    ${COCOS_X_PATH}
    ${COCOS_X_PATH}/cocos
    ${COCOS_X_PATH}/cocos/renderer
    ${platform_spec_path}/include/v8
    ${JSB_HELPER_INCLUDE_DIR}
    ${LOG_WRAPPER_INCLUDE_DIR}
    ${SOCIAL_SDK_INCLUDE_LIST}
)

target_link_libraries(social_sdk
    PRIVATE logging
    PRIVATE jsb-helper)