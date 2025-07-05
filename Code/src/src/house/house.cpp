#include <stdio.h>
#include "pico/stdlib.h"
#include "LoRa-RP2040.h"
#include "hardware/gpio.h"

#define MOTOR_A_PIN 27
#define MOTOR_B_PIN 26

void motor_forwards() {
    printf("forwards\n");
    gpio_put(MOTOR_A_PIN, 0);
    gpio_put(MOTOR_B_PIN, 1);
}

void motor_reverse() {
    printf("reverse\n");
    gpio_put(MOTOR_A_PIN, 1);
    gpio_put(MOTOR_B_PIN, 0);
}

void motor_stop() {
    printf("stop\n");
    gpio_put(MOTOR_A_PIN, 0);
    gpio_put(MOTOR_B_PIN, 0);
}

int comp_buff(char* buff, const char* str, int l) {
    for (int i = 0; i < l; i++) {
        printf("%d, %c, %c\n", i, buff[i], str[i]);
        
        if (buff[i] != str[i]) return 0;
    }
    return 1;
}

int main() {
    stdio_init_all();

    gpio_init(MOTOR_A_PIN);
    gpio_init(MOTOR_B_PIN);
    gpio_set_dir(MOTOR_A_PIN, GPIO_OUT);
    gpio_set_dir(MOTOR_B_PIN, GPIO_OUT);
    
    sleep_ms(2000);

    if (!LoRa.begin(500E6)) {
        printf("Starting LoRa failed!\n");
        while (1);
    }

    printf("LoRa Started\n");

    while (true) {
        int packet_size = LoRa.parsePacket();
    
        if (packet_size) {
            printf("Received packet\n");

            char buffer[packet_size];

            for (int i = 0; i < packet_size; i++) {
                buffer[i] = LoRa.read();
            }

            if (comp_buff(buffer, "OPEN", packet_size)) {
                printf("opening door\n");
                motor_forwards();
                sleep_ms(3000);
                motor_stop();
            }
            else if (comp_buff(buffer, "CLOSED", packet_size)) {
                printf("closing door\n");
                motor_reverse();
                sleep_ms(3000);
                motor_stop();
            }
        }
    }
}