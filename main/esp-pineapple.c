#include <stdio.h>
#include <stdbool.h>
#include "esp_log.h"
#include "esp_event.h"
#include "driver/gpio.h"

/* project includes */
#include "nvs_utils.h"
#include "wifi_utils.h"
#include "led_utils.h"

static const char* TAG = "esp-pineapple"; // TAG variable for logging

void blink_error();
void blink_number(uint16_t num);

void app_main(void) {
    esp_log_level_set("TAG", ESP_LOG_INFO);
    
    nvs_init();

    wifi_init();

    /* Scan for Piersen's Wifi: SpectrumSetup-47 */
    wifi_ap_record_t ap_record = wifi_find_ssid_record("SpectrumSetup-47");
    
}

void blink_error() {
    gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);
    while(1) {
        gpio_set_level(GPIO_NUM_2, 1); // turn LED on
        vTaskDelay(50 / portTICK_PERIOD_MS);
    
        gpio_set_level(GPIO_NUM_2, 0); // turn LED off
        vTaskDelay(50 / portTICK_PERIOD_MS);
    }
}

void blink_number(uint16_t num) {
    gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);
    
    for (uint16_t i = 0; i < num; i++) {
        /* Turn LED on */
        gpio_set_level(GPIO_NUM_2, 1);
        vTaskDelay(500 / portTICK_PERIOD_MS);

        /* Turn LED off */
        gpio_set_level(GPIO_NUM_2, 0);
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}
