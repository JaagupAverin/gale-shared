#include <zephyr/kernel.h>

#include "tests/multicore.hpp"

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(main, LOG_LEVEL_DBG);

int main() {
	LOG_INF("Hello, world!");

	test_multicore();

	int i = 0;
	while (true) {
		LOG_INF("TICK #%d!", i++);
		k_sleep(K_MSEC(10000));
	}
	return 0;
}
