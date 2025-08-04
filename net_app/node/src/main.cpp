#include <app_version.h>
#include <zephyr/kernel.h>

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(main, LOG_LEVEL_DBG);

int main() {
    LOG_INF("Hello, world?! " APP_VERSION_STRING);

    int i = 0;
    while (true) {
        LOG_INF("TICK #%d!", i++);
        k_sleep(K_MSEC(10000));
    }
    return 0;
}
