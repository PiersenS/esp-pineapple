#include "wifi_utils.h"

static const char* TAG = "wifi_utils"; // TAG variable for logging

esp_err_t wifi_init() {
    esp_event_loop_create_default(); // give wifi an event loop

    esp_log_level_set("TAG", ESP_LOG_INFO);
    /* Init Wifi */
    ESP_LOGI(TAG, "Starting WiFi Initialization");
    wifi_init_config_t wifi_config = WIFI_INIT_CONFIG_DEFAULT();
    esp_wifi_init(&wifi_config);
    esp_wifi_set_mode(WIFI_MODE_STA);
    return esp_wifi_start();
}

esp_err_t wifi_scan() {
    ESP_LOGI(TAG, "Starting WiFi Scan");
    esp_err_t error = esp_wifi_scan_start(NULL, 1); // params: default settings, block caller (finish scan and find all APs?)

    ESP_LOGI(TAG, "Scan completed!");
    return error;
}

uint16_t wifi_get_ap_num() {
    uint16_t num_ap_found;
    esp_wifi_scan_get_ap_num(&num_ap_found);

    ESP_LOGI(TAG, "Number of APs found: %d", num_ap_found);
    return num_ap_found;
}

wifi_ap_record_t* wifi_get_ap_records(uint16_t num_ap) {
    wifi_ap_record_t* ap_records = malloc(sizeof(wifi_ap_record_t) * num_ap);
    esp_wifi_scan_get_ap_records(&num_ap, ap_records);
    ESP_LOGI(TAG, "AP Records retrieved.");

    return ap_records;
}

wifi_ap_record_t wifi_find_ssid_record(char* ssid) {
    wifi_scan();
    uint16_t ap_num = wifi_get_ap_num();
    wifi_ap_record_t* ap_records = wifi_get_ap_records(ap_num);

    ESP_LOGI(TAG, "Listing SSIDs found . . .");
    wifi_ap_record_t record;
    for (int i = 0; i < ap_num; i++) {
        if (strcmp((char*)ap_records[i].ssid, "SpectrumSetup-47") == 0) {
            record = ap_records[i];
            break;
        }
    }

    ESP_LOGI(TAG, "SSID Found: %s", record.ssid);
    return record;

}
