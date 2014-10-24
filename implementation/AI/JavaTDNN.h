/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class JavaTDNN */

#ifndef _Included_JavaTDNN
#define _Included_JavaTDNN
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     JavaTDNN
 * Method:    TDNN_init
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_JavaTDNN_TDNN_1init
  (JNIEnv *, jclass);

/*
 * Class:     JavaTDNN
 * Method:    TDNN_make_move
 * Signature: ([I)I
 */
JNIEXPORT jint JNICALL Java_JavaTDNN_TDNN_1make_1move
  (JNIEnv *, jclass, jintArray);

/*
 * Class:     JavaTDNN
 * Method:    TDNN_prune
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_JavaTDNN_TDNN_1prune
  (JNIEnv *, jclass, jint);

/*
 * Class:     JavaTDNN
 * Method:    TDNN_free
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_JavaTDNN_TDNN_1free
  (JNIEnv *, jclass);

/*
 * Class:     JavaTDNN
 * Method:    TDNN_depth
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_JavaTDNN_TDNN_1depth
  (JNIEnv *, jclass, jint);

#ifdef __cplusplus
}
#endif
#endif
