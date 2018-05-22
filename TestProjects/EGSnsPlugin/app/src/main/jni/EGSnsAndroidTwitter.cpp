// FEGSnsAndroidTwitter 테스트용
#include <com_lsm1987_egsnsplugin_EGSnsTwitter.h>
#include <android/log.h>

JNIEXPORT void JNICALL Java_com_lsm1987_egsnsplugin_EGSnsTwitter_nativeOnLoggedIn(JNIEnv* jenv, jobject thiz, jboolean bSuccess)
{
    __android_log_print(ANDROID_LOG_DEBUG, "EGSnsPlugin", "EGSnsTwitter_nativeOnLoggedIn()");
    __android_log_print(ANDROID_LOG_DEBUG, "EGSnsPlugin", "bSuccess: %d", (bSuccess == JNI_TRUE) ? 1 : 0);
}

JNIEXPORT void JNICALL Java_com_lsm1987_egsnsplugin_EGSnsTwitter_nativeOnShared(JNIEnv* jenv, jobject thiz, jboolean bSuccess, jstring ErrorMessage)
{
    __android_log_print(ANDROID_LOG_DEBUG, "EGSnsPlugin", "EGSnsTwitter_nativeOnShared()");
    __android_log_print(ANDROID_LOG_DEBUG, "EGSnsPlugin", "bSuccess: %d", (bSuccess == JNI_TRUE) ? 1 : 0);

    if (ErrorMessage != nullptr)
    {
        const char *strErrorMessage = jenv->GetStringUTFChars(ErrorMessage, 0);
        __android_log_print(ANDROID_LOG_DEBUG, "EGSnsPlugin", "ErrorMessage: %s", strErrorMessage);
        jenv->ReleaseStringUTFChars(ErrorMessage, strErrorMessage);
    }
    else
    {
        __android_log_print(ANDROID_LOG_DEBUG, "EGSnsPlugin", "ErrorMessage: (null)");
    }
}