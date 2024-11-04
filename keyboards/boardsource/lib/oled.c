// Copyright 2024 jack (@waffle87)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "oled.h"

#define NUM_FRAMES 4
#define UPDATE_RATE 2

static int animct = 4;
static uint8_t mods;

void animate_frame4(void) {
    animct ++;
    int frame_idx = (animct / UPDATE_RATE) % NUM_FRAMES;
    oled_write_raw_P(layer4_imgs[frame_idx], sizeof(layer4_imgs[frame_idx]));
}

void render_layer_state(void) {
    switch (get_highest_layer(layer_state)) {
        case 0:
            mods = get_mods();
            if ((mods & MOD_MASK_CTRL) && (mods & MOD_MASK_ALT) && (mods & MOD_MASK_GUI)) {
                animate_frame4();
            } else {
                oled_write_raw_P(layer0_img, sizeof(layer0_img));
            }
            break;
        case 1:
            oled_write_raw_P(layer1_img, sizeof(layer1_img));
            break;
        case 2:
            oled_write_raw_P(layer2_img, sizeof(layer2_img));
            break;
        case 3:
            oled_write_raw_P(layer3_img, sizeof(layer3_img));
            break;
        case 4:
            animate_frame4();
            break;
    }
}
