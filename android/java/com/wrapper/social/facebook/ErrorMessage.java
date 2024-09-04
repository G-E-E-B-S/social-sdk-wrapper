package com.wrapper.social.facebook;

public enum ErrorMessage {
    // called USER_INPUT to be consistent with FB sdk
    USER_CANCEL {
        public String toString() {
            return "USER_INPUT";
        }
    }
}
