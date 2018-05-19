// FEGSnsAndroidTwitter 테스트용
#include <com_lsm1987_egsnsplugin_EGSnsTwitter.h>
#include <android/log.h>

JNIEXPORT void JNICALL Java_com_lsm1987_egsnsplugin_EGSnsTwitter_nativeOnLoggedIn(JNIEnv* jenv, jobject thiz, jboolean bSuccess)
{
    __android_log_print(ANDROID_LOG_DEBUG, "EGSnsPlugin", "EGSnsTwitter_nativeOnLoggedIn()");
    __android_log_print(ANDROID_LOG_DEBUG, "EGSnsPlugin", "bSuccess: %d", (bSuccess == JNI_TRUE) ? 1 : 0);
}