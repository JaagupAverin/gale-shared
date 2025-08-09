#include <stdlib.h>
#include <zephyr/drivers/mbox.h>
#include <zephyr/kernel.h>

#include "tests/multicore.hpp"

#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(multicore);

static void test_mbox() {
	const mbox_dt_spec tx_channel = MBOX_DT_SPEC_GET(DT_PATH(mbox_consumer), tx);

	while (true) {
		// TX:
		LOG_INF("Server send (on channel %d)", tx_channel.channel_id);
		if (mbox_send_dt(&tx_channel, nullptr) < 0) {
			LOG_ERR("mbox_send() error");
			return;
		}
		k_sleep(K_SECONDS(1));
	}
}
K_THREAD_DEFINE(test_mbox_thread, 1024, test_mbox, NULL, NULL, NULL, 7, 0, K_FOREVER.ticks);

void test_multicore() { k_thread_start(test_mbox_thread); }
