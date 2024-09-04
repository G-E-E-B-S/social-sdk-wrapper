#import <Foundation/Foundation.h>

#if defined(__cplusplus)
extern "C" {
#endif
    void onShareSuccess();
    void onShareFailed(NSString* error);
    void onContextChooseFailed(NSString* error);
    void onContextChooseComplete(NSString* contextId);
    void onContextCreateComplete(NSString* contextId);
    void onContextCreateFailed(NSString* error);
    void onContextSwitchComplete();
    void onContextSwitchFailed(NSString* error);
#if defined(__cplusplus)
}
#endif
