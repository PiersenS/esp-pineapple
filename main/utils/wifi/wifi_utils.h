#ifndef WIFI_UTILS_H
#define WIFI_UTILS_H

#include "esp_wifi.h"
#include "esp_log.h"

esp_err_t wifi_init();
esp_err_t wifi_scan();
uint16_t wifi_get_ap_num();
wifi_ap_record_t* wifi_get_ap_records(uint16_t num_ap);

wifi_ap_record_t wifi_find_ssid_record(char* ssid);

#endif
