/*
 * TODO: Create event handler for WIFI_EVENT_SCAN_DONE event
 */

#include <stdio.h>
#include <stdbool.h>
#include "esp_wifi.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "driver/gpio.h"

static const char* TAG = "esp-pineapple"; // TAG variable for logging

esp_err_t connect_wifi();
void blink_error();
void blink_number(uint16_t num);

void app_main(void) {
    esp_log_level_set("TAG", ESP_LOG_INFO);
    
    /* init flash storage */
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }

    /* Init Wifi */
    ESP_LOGI(TAG, "Starting WiFi Initialization");
    wifi_init_config_t wifi_config = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&wifi_config);
    esp_wifi_set_mode(WIFI_MODE_STA);
    
    /* Scan for Piersen's Wifi: SpectrumSetup-47 */
    ESP_LOGI(TAG, "Starting WiFi Scan");
    esp_wifi_scan_start(NULL, 1); // params: default settings, block caller (finish scan and find all APs?)
    
    ESP_LOGI(TAG, "Getting number of APs found");
    uint16_t num_ap_found;
    esp_wifi_scan_get_ap_num(&num_ap_found);

    ESP_LOGI(TAG, "Blinking the number of APs found");
    blink_number(num_ap_found);
}

void blink_error() {
    while(1) {
        gpio_set_level(GPIO_NUM_2, 1); // turn LED on
        vTaskDelay(100 / portTICK_PERIOD_MS);
    
        gpio_set_level(GPIO_NUM_2, 0); // turn LED off
        vTaskDelay(100 / portTICK_PERIOD_MS);
    }
    
}

void blink_number(uint16_t num) {
    gpio_set_direction(GPIO_NUM_2, 1);
    
    for (uint16_t i = 0; i < num; i++) {
        /* Turn LED on */
        gpio_set_level(GPIO_NUM_2, 1);
        vTaskDelay(500 / portTICK_PERIOD_MS);

        /* Turn LED off */
        gpio_set_level(GPIO_NUM_2, 0);
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}
