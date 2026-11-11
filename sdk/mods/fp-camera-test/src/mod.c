
#include "bearite_api.h"
#include "bearite_il2cpp.h"

static void check_class(
    const BeariteApi* api,
    const char* mod_id,
    const char* ns,
    const char* name
) {
    if (bearite_find_class(ns, name)) {
        char msg[160];
        snprintf(msg, sizeof(msg), "НАЙДЕН класс: %s", name);
        api->log(mod_id, msg);
    } else {
        char msg[160];
        snprintf(msg, sizeof(msg), "НЕ НАЙДЕН класс: %s", name);
        api->log(mod_id, msg);
    }
}

__attribute__((visibility("default")))
void bearite_mod_init(const BeariteApi* api, const char* mod_id) {
    if (!api || api->version != BEARITE_API_VERSION) return;

    api->log(mod_id, "FP Camera Test запущен");

    if (!bearite_il2cpp_init(api)) {
        api->log(mod_id, "Ошибка инициализации IL2CPP");
        return;
    }

    check_class(api, mod_id, "", "PlayerBearController");
    check_class(api, mod_id, "", "CameraController");
    check_class(api, mod_id, "", "ThirdPersonCamera");
    check_class(api, mod_id, "", "CameraManager");

    check_class(api, mod_id, "UnityEngine", "Camera");
    check_class(api, mod_id, "UnityEngine", "Transform");

    if (bearite_find_method(
        "UnityEngine", "Camera", "get_main", 0
    )) {
        api->log(mod_id, "НАЙДЕН метод Camera.get_main");
    } else {
        api->log(mod_id, "НЕ НАЙДЕН метод Camera.get_main");
    }

    api->log(mod_id, "Проверка завершена");
}

