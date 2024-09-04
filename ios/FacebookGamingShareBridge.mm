#include "FacebookGamingShareBridge.hpp"
#include "NativeShare.h"
using namespace wrapper::social;
void onShareSuccess() {
    NativeShare::getInstance()->getListener()->onShareComplete(true);
}
void onShareFailed(NSString* error) {
    NativeShare::getInstance()->getListener()->onShareFailed([error UTF8String]);
}
void onContextChooseFailed(NSString* error) {
    NativeShare::getInstance()->getListener()->onContextChooseFailed([error UTF8String]);
}
void onContextChooseComplete(NSString* contextId) {
    NativeShare::getInstance()->getListener()->onContextChooseComplete([contextId UTF8String]);
}
void onContextCreateComplete(NSString* contextId) {
    NativeShare::getInstance()->getListener()->onContextCreateComplete([contextId UTF8String]);
}
void onContextCreateFailed(NSString* error) {
    NativeShare::getInstance()->getListener()->onContextCreateFailed([error UTF8String]);
}
void onContextSwitchComplete() {
    NativeShare::getInstance()->getListener()->onContextSwitchComplete();
}
void onContextSwitchFailed(NSString* error) {
    NativeShare::getInstance()->getListener()->onContextSwitchFailed([error UTF8String]);
}
