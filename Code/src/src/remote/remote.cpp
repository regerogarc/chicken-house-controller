#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
extern "C" {
#include "ImageData.h"
#include "OLED_0in49.h"
}
#include "LoRa-RP2040.h"

#define L_BUTTON    0
#define M_BUTTON    1
#define R_BUTTON    3

void open_door() {
    printf("Sending open door command\n");
    LoRa.beginPacket();
    LoRa.print("OPEN");
    LoRa.endPacket();

    OLED_0in49_Display(gImage_open);
}

void close_door() {
    printf("Sending close door command\n");
    LoRa.beginPacket();
    LoRa.print("CLOSE");
    LoRa.endPacket();

    OLED_0in49_Display(gImage_closed);
}

int main() {
    stdio_init_all();
    sleep_ms(5000);
    printf("hello---!\n");

    // Init display SPI and GPIO
    spi_init(spi1, 1*1000*1000);
    gpio_set_function(14, GPIO_FUNC_SPI);
    gpio_set_function(15, GPIO_FUNC_SPI);
    DEV_GPIO_Init();
    OLED_0in49_Init();
    OLED_0in49_Clear();

    // Init buttons
    gpio_init(L_BUTTON);
    gpio_init(M_BUTTON);
    gpio_init(R_BUTTON);
    gpio_set_dir(L_BUTTON, GPIO_IN);
    gpio_set_dir(M_BUTTON, GPIO_IN);
    gpio_set_dir(R_BUTTON, GPIO_IN);
    gpio_pull_up(L_BUTTON);
    gpio_pull_up(M_BUTTON);
    gpio_pull_up(R_BUTTON);

    // Init LoRa Module
	if (!LoRa.begin(500E6)) {
		while (1) {
		    printf("Starting LoRa failed!\n");
            sleep_ms(100);
        }
	}


    while (true) {
        // printf("yeetus\n");
        // sleep_ms(1000);
        // printf("bassl\n");
        // sleep_ms(1000);

        printf("loop\n");
        sleep_ms(500);

        int l = gpio_get(L_BUTTON);
        int m = gpio_get(M_BUTTON);
        int r = gpio_get(R_BUTTON);

        printf("l%d m%d r%d\n", l, m, r);

        if (!l) {
            open_door();
        } else if (!r) {
            close_door();
        }

    }
}