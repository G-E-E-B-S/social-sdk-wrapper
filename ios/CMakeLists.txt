cmake_minimum_required(VERSION 3.8)

set(SOCIAL_JS_BINDING_SRC
    ${CMAKE_CURRENT_LIST_DIR}/../bindings/manual/ShareListenerJS.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../bindings/manual/ShareListenerJS.h
    ${CMAKE_CURRENT_LIST_DIR}/../bindings/manual/SocialJSHelper.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../bindings/manual/SocialJSHelper.h
    ${CMAKE_CURRENT_LIST_DIR}/../bindings/manual/TournamentListenerJS.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../bindings/manual/TournamentListenerJS.h
    )

if (COCOS_3_7_PLUS)
    list(APPEND SOCIAL_JS_BINDING_SRC
        ${CMAKE_CURRENT_LIST_DIR}/../bindings/auto/3.7.x/jsb_social_auto.cpp
    )
elseif(COCOS_3_X_PLUS)
    list(APPEND SOCIAL_JS_BINDING_SRC
        ${CMAKE_CURRENT_LIST_DIR}/../bindings/auto/3.x.x_3.6.x/jsb_social_auto.cpp
    )
else()
    list(APPEND SOCIAL_JS_BINDING_SRC
        ${CMAKE_CURRENT_LIST_DIR}/../bindings/auto/2.x/jsb_social_auto.cpp
    )
endif()

source_group(TREE ${CMAKE_CURRENT_LIST_DIR}/../bindings PREFIX "js-bindings/social-sdk" FILES ${SOCIAL_JS_BINDING_SRC})

list(APPEND CC_ALL_SOURCES ${SOCIAL_JS_BINDING_SRC})