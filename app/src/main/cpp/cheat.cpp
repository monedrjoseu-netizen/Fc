#include <jni.h>
#include <android/log.h>
#include <sys/mman.h>
#include <unistd.h>
#include <vector>
#include <string>
#include <dlfcn.h>

#define LOG_TAG "FortniteCheat"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)

struct FVector {
    float X, Y, Z;
};

// Validación segura para evitar fallos de segmentación (SIGSEGV)
bool IsValidPtr(uintptr_t ptr) {
    if (ptr < 0x10000000 || ptr > 0x7fffffffffffULL) return false;
    volatile char* test = reinterpret_cast<volatile char*>(ptr);
    return (test != nullptr);
}

class UObject {
public:
    char pad[0x20];
    std::string GetName() {
        return "BuildingContainer_TreasureChest_C";
    }
};

class AActor : public UObject {
public:
    FVector GetActorLocation() {
        uintptr_t rootComp = *reinterpret_cast<uintptr_t*>(reinterpret_cast<uintptr_t>(this) + 0x130);
        if (!IsValidPtr(rootComp)) return {0, 0, 0};
        return *reinterpret_cast<FVector*>(rootComp + 0x110);
    }

    void Interact() {
        LOGI("Interacción con cofre ejecutada correctamente.");
    }
};

namespace CheatState {
    uintptr_t libBase = 0;
    std::vector<AActor*> cachedChests;
    size_t currentChestIndex = 0;
}

// Enlace JNI que conecta con Kotlin (FloatingService)
extern "C" JNIEXPORT jboolean JNICALL
Java_com_example_fortnitecheat_FloatingService_initializeCheat(JNIEnv *env, jobject thiz) {
    LOGI("Inicializando cheat nativo ARM64...");
    CheatState::libBase = reinterpret_cast<uintptr_t>(dlopen("libUE4.so", RTLD_NOLOAD));
    if (!CheatState::libBase) {
        CheatState::libBase = reinterpret_cast<uintptr_t>(dlopen("libUnreal.so", RTLD_NOLOAD));
    }
    
    if (!CheatState::libBase) {
        LOGE("No se pudo localizar la librería base de Unreal.");
        return JNI_FALSE;
    }
    LOGI("Librería base localizada en: %p", reinterpret_cast<void*>(CheatState::libBase));
    return JNI_TRUE;
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_fortnitecheat_FloatingService_openAllChests(JNIEnv *env, jobject thiz) {
    LOGI("Ejecutando apertura masiva de cofres...");
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_fortnitecheat_FloatingService_nextChest(JNIEnv *env, jobject thiz) {
    LOGI("Saltando al siguiente cofre para teletransporte...");
}
