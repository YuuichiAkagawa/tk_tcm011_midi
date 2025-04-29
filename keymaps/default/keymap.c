// Copyright 2025 Yuuichi Akagawa
// ELECOM TK-TCM011 Ten-keyboard (19key) MIDI Mod
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

extern MidiDevice midi_device;
extern midi_config_t midi_config;
static bool led_state = false;


void keyboard_post_init_user(void) {
    // channel setting CH1(0)
    midi_config.channel = 0;
    // octave setting C1 = 36 (0x24)
    midi_config.octave = 2;

    // GPIO setting
    gpio_set_pin_input_high(EXTRA_SWITCH_PIN);

    // LED setting
    led_state = true;
    gpio_set_pin_output(LED_PIN);
    gpio_write_pin(LED_PIN, led_state);
}

bool read_extra_switch(uint8_t index) {
    switch (index) {
      case 0:
        return gpio_read_pin(EXTRA_SWITCH_PIN); 
      default:
        return false;
    }
}

void matrix_scan_user(void) {
    static bool extra_switch_state = true;
    bool current_state = read_extra_switch(0);

    if (current_state && !extra_switch_state) {  // pressed
        // do nothing
    } else if (!current_state && extra_switch_state) { // released
        // flip LED
        led_state = !led_state;
        gpio_write_pin(LED_PIN, led_state);
#if 0
        if(led_state){
            layer_off(1);
        }else{
            layer_on(1);
        }
#endif
        }
    extra_switch_state = current_state;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┐
     * │Tab│ / │ * │BS │
     * ├───┼───┼───┼───┤
     * │ 7 │ 8 │ 9 │ - │
     * ├───┼───┼───┼───┤
     * │ 4 │ 5 │ 6 │ + │
     * ├───┼───┼───┼───┤
     * │ 1 │ 2 │ 3 │ E │
     * ├───┼───┼───┤ n │
     * │ 0 │00 │ . │ t │
     * └───┴───┴───┴───┘
     */
	[0] = LAYOUT(
          MI_C2,  MI_Cs2, MI_D2,  MI_Ds2,
          MI_Gs1, MI_A1,  MI_As1, MI_B1,
          MI_E1,  MI_F1,  MI_Fs1, MI_G1,
          MI_C1,  MI_Cs1, MI_D1,  MI_Ds1,
          MI_A,   MI_As,  MI_B
        ),
};
