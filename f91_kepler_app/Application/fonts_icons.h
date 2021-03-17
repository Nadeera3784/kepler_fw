/*
 * fonts_icons.h
 *
 *  Created on: Dec 13, 2020
 *      Author: Pegor Karoglanian
 */
#include <stdint.h>
#ifndef CUSTOM_FONTS_H_
#define CUSTOM_FONTS_H_

// page size: 4
const uint8_t numbers_15x25[10][60] = {
            {0x7f, 0xbf, 0xdf, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xdf, 0xbf, 0x7f,
            0xf7, 0xe3, 0xc1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xc1, 0xe3, 0xf7,
            0xff, 0xfe, 0xfd, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0xfd, 0xfe, 0xff,
            0x0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x0}, // 0
            {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1f, 0x3f, 0x7f,
            0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xc1, 0xe3, 0xf7,
            0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xfc, 0xfe, 0xff,
            0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}, // 1
            {0x0, 0x80, 0xc0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xdf, 0xbf, 0x7f,
            0x7, 0xb, 0x1d, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0xdc, 0xe8, 0xf0,
            0xff, 0xfe, 0xfd, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x1, 0x0, 0x0,
            0x0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x0}, // 2
            {0x0, 0x80, 0xc0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xdf, 0xbf, 0x7f,
            0x0, 0x8, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0xdd, 0xeb, 0xf7,
            0x0, 0x0, 0x1, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0xfd, 0xfe, 0xff,
            0x0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x0}, // 3
            {0x7f, 0x3f, 0x1f, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1f, 0x3f, 0x7f,
            0xf0, 0xe8, 0xdc, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0xdd, 0xeb, 0xf7,
            0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xfc, 0xfe, 0xff,
            0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}, // 4
            {0x7f, 0xbf, 0xdf, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xc0, 0x80, 0x0,
            0xf0, 0xe8, 0xdc, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1d, 0xb, 0x7,
            0x0, 0x0, 0x1, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0xfd, 0xfe, 0xff,
            0x0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x0}, // 5
            {0x7f, 0xbf, 0xdf, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xc0, 0x80, 0x0,
            0xf7, 0xeb, 0xdd, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1d, 0xb, 0x7,
            0xff, 0xfe, 0xfd, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0xfd, 0xfe, 0xff,
            0x0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x0}, // 6
            {0x0, 0x80, 0xc0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xdf, 0xbf, 0x7f,
            0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xc1, 0xe3, 0xf7,
            0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xfc, 0xfe, 0xff,
            0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}, // 7
            {0x7f, 0xbf, 0xdf, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xdf, 0xbf, 0x7f,
            0xf7, 0xeb, 0xdd, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0xdd, 0xeb, 0xf7,
            0xff, 0xfe, 0xfd, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0xfd, 0xfe, 0xff,
            0x0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x0}, // 8
            {0x7f, 0xbf, 0xdf, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xdf, 0xbf, 0x7f,
            0xf0, 0xe8, 0xdc, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0xdd, 0xeb, 0xf7,
            0x0, 0x0, 0x1, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0xfd, 0xfe, 0xff,
            0x0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x0}}; // 9

// page size: 2
const uint8_t numbers_9x13[10][18] = {
            {0x7d, 0xb8, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xb8, 0x7d, 0xf0, 0xe8, 0x18, 0x18, 0x18, 0x18, 0x18, 0xe8, 0xf0}, // 0
            {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x38, 0x7d, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xe0, 0xf0}, // 1
            {0x1, 0x82, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xba, 0x7c, 0xf0, 0xe8, 0x18, 0x18, 0x18, 0x18, 0x18, 0x8, 0x0}, // 2
            {0x0, 0x82, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xba, 0x7d, 0x0, 0x8, 0x18, 0x18, 0x18, 0x18, 0x18, 0xe8, 0xf0}, // 3
            {0x7c, 0x3a, 0x6, 0x6, 0x6, 0x6, 0x6, 0x3a, 0x7d, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xe0, 0xf0}, // 4
            {0x7c, 0xba, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x82, 0x1, 0x0, 0x8, 0x18, 0x18, 0x18, 0x18, 0x18, 0xe8, 0xf0}, // 5
            {0x7d, 0xba, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0x82, 0x1, 0xf0, 0xe8, 0x18, 0x18, 0x18, 0x18, 0x18, 0xe8, 0xf0}, // 6
            {0x0, 0x80, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xb8, 0x7d, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xe0, 0xf0}, // 7
            {0x7d, 0xba, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xba, 0x7d, 0xf0, 0xe8, 0x18, 0x18, 0x18, 0x18, 0x18, 0xe8, 0xf0}, // 8
            {0x7c, 0xba, 0xc6, 0xc6, 0xc6, 0xc6, 0xc6, 0xba, 0x7d, 0x0, 0x8, 0x18, 0x18, 0x18, 0x18, 0x18, 0xe8, 0xf0}}; // 9

// page size: 2
const uint8_t icons_12x9[5][24] = {
            {0xff, 0xc0, 0xa0, 0x90, 0x88, 0x84, 0x84, 0x88, 0x90, 0xa0, 0xc0, 0xff, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80}, // email
            {0x0, 0xfe, 0x82, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0x81, 0xff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x0}, // text
            {0x1c, 0x22, 0x22, 0x22, 0x1e, 0x2, 0x2, 0x1e, 0x22, 0x22, 0x22, 0x1c, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}, // voicemail
            {0x1, 0x3, 0x47, 0x27, 0x14, 0xc, 0x14, 0xa4, 0xc7, 0xe7, 0x3, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}, // missed_call
            {0x0, 0x0, 0x22, 0x14, 0x8, 0xff, 0x88, 0x55, 0x22, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x80, 0x80, 0x0, 0x0, 0x0, 0x0, 0x0}}; // bluetooth

// page size: 5
const uint8_t call_from_96x39[480] = {
            0xff, 0xff, 0xc0, 0xdf, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd1, 0xd1, 0xd1, 0xd1, 0xd1, 0xd1, 0xd1,
            0xd1, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xdf, 0xc1, 0xfd, 0xfd, 0xfd, 0xfd,
            0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd,
            0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd,
            0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd,
            0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd,
            0xfd, 0xfd, 0xfe, 0xff, 0xff, 0xff, 0xff, 0x0, 0xff, 0x0, 0x0, 0x7, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xfc, 0xfc,
            0x8c, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
            0x0, 0x0, 0x0, 0x3e, 0x41, 0x41, 0x41, 0x22, 0x0, 0x3f, 0x48, 0x48, 0x48, 0x3f, 0x0,
            0x7f, 0x1, 0x1, 0x1, 0x1, 0x0, 0x7f, 0x1, 0x1, 0x1, 0x1, 0x0, 0x0, 0x0, 0x0,
            0x0, 0x7f, 0x48, 0x48, 0x48, 0x40, 0x0, 0x7f, 0x48, 0x48, 0x48, 0x37, 0x0, 0x3e, 0x41,
            0x41, 0x41, 0x3e, 0x0, 0x7f, 0x20, 0x10, 0x20, 0x7f, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
            0x0, 0x0, 0x0, 0xff, 0xff, 0xff, 0xff, 0x0, 0xff, 0x0, 0x0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0, 0x0, 0x10,
            0x38, 0x7c, 0xfe, 0xff, 0x38, 0x38, 0x38, 0x38, 0x38, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
            0x0, 0x0, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
            0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
            0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
            0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x0, 0x0, 0x0, 0x0, 0x0,
            0x0, 0x0, 0x0, 0xff, 0xff, 0xff, 0xff, 0x0, 0xff, 0x0, 0x0, 0xc0, 0xf8, 0xfe, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x7f, 0x7f,
            0x63, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1,
            0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1,
            0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1,
            0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1,
            0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1,
            0x1, 0x1, 0x0, 0xff, 0xff, 0xfe, 0xfe, 0x6, 0xf6, 0x16, 0x16, 0x16, 0x16, 0x16, 0x16, 0x16, 0x16, 0x16, 0x16, 0x16, 0x16,
            0x16, 0x16, 0x16, 0x16, 0x16, 0x16, 0x16, 0x16, 0x16, 0xf6, 0x6, 0x7e, 0x7e, 0x7e, 0x7e,
            0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e,
            0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e,
            0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e,
            0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e,
            0x7e, 0x7e, 0xfe, 0xfe, 0xfe}; // call_from

// page size: 5
const uint8_t text_from_96x39[480] = {
            0xff, 0xff, 0xc0, 0xdf, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0,
            0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xd0, 0xdf, 0xc1, 0xfd, 0xfd, 0xfd, 0xfd,
            0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd,
            0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd,
            0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd,
            0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd, 0xfd,
            0xfd, 0xfd, 0xfe, 0xff, 0xff, 0xff, 0xff, 0x0, 0xff, 0x0, 0xf, 0x1f, 0x3f, 0x7b, 0x7b, 0x7b, 0x7b, 0x7b, 0x7b, 0x7b, 0x7d,
            0x7d, 0x7d, 0x7d, 0x7d, 0x7d, 0x3f, 0x1f, 0xf, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
            0x0, 0x0, 0x0, 0x40, 0x40, 0x7f, 0x40, 0x40, 0x0, 0x7f, 0x49, 0x49, 0x41, 0x41, 0x0,
            0x77, 0x8, 0x8, 0x8, 0x77, 0x0, 0x40, 0x40, 0x7f, 0x40, 0x40, 0x0, 0x0, 0x0, 0x0,
            0x0, 0x7f, 0x48, 0x48, 0x48, 0x40, 0x0, 0x7f, 0x48, 0x48, 0x48, 0x37, 0x0, 0x3e, 0x41,
            0x41, 0x41, 0x3e, 0x0, 0x7f, 0x20, 0x10, 0x20, 0x7f, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
            0x0, 0x0, 0x0, 0xff, 0xff, 0xff, 0xff, 0x0, 0xff, 0x0, 0xff, 0xff, 0xff, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0xdd,
            0xdd, 0xdd, 0xdd, 0xdd, 0xdd, 0xff, 0xff, 0xff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
            0x0, 0x0, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
            0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
            0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40,
            0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x0, 0x0, 0x0, 0x0, 0x0,
            0x0, 0x0, 0x0, 0xff, 0xff, 0xff, 0xff, 0x0, 0xff, 0x0, 0x0, 0x80, 0xc0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0, 0xe0,
            0xe0, 0xf0, 0xf8, 0xfc, 0xfe, 0xe0, 0xc0, 0x80, 0x0, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1,
            0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1,
            0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1,
            0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1,
            0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1,
            0x1, 0x1, 0x0, 0xff, 0xff, 0xfe, 0xfe, 0x6, 0xf6, 0x16, 0x16, 0x16, 0x16, 0x16, 0x16, 0x16, 0x16, 0x16, 0x16, 0x16, 0x16,
            0x16, 0x16, 0x16, 0x16, 0x16, 0x16, 0x16, 0x16, 0x16, 0xf6, 0x6, 0x7e, 0x7e, 0x7e, 0x7e,
            0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e,
            0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e,
            0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e,
            0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e,
            0x7e, 0x7e, 0xfe, 0xfe, 0xfe}; // text_from

// page size: 4
const uint8_t semicolon_3x27[12] = {
            0x3, 0x3, 0x3, 0x80, 0x80, 0x80, 0x38, 0x38, 0x38, 0x0, 0x0, 0x0}; // semicolon

// page size: 1
const uint8_t pm_12x7[12] = {
            0xfe, 0x90, 0x90, 0x60, 0x0, 0xfe, 0x40, 0x20, 0x10, 0x20, 0x40, 0xfe}; // PM

// page size: 1
const uint8_t ellipsis_5x7[5] = {
            0x2, 0x0, 0x2, 0x0, 0x2}; // ellipsis


#endif /* CUSTOM_FONTS_H_ */
