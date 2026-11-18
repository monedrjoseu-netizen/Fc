plugins {
    id("com.android.application")
    kotlin("android")
}

android {
    namespace = "com.example.fortnitecheat"
    compileSdk = 33

    defaultConfig {
        applicationId = "com.example.fortnitecheat"
        minSdk = 24
        targetSdk = 33
        versionCode = 1
        versionName = "1.0"

        externalNativeBuild {
            cmake {
                cppFlags("-O3 -fvisibility=hidden -Wall")
                abiFilters("arm64-v8a")
            }
        }
    }

    buildTypes {
        release {
            isMinifyEnabled = false
        }
    }

    externalNativeBuild {
        cmake {
            path = file("src/main/cpp/CMakeLists.txt")
            version = "3.22.1"
        }
    }
}

dependencies {
    implementation("androidx.core:core-ktx:1.9.0")
    implementation("androidx.appcompat:appcompat:1.6.1")
}
