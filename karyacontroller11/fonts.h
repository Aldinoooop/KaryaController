#pragma once

// Created by http://oleddisplay.squix.ch/ Consider a donation
// In case of problems make sure that you are using the font file with the correct version!

const uint8_t BASICFONT[] PROGMEM = {
  0x0C, // Width: 12
  0x11, // Height: 17
  0x20, // First char: 32
  0x5F, // Number of chars: 95
  // Jump Table:
  0xFF, 0xFF, 0x00, 0x03, // 32
  0x00, 0x00, 0x08, 0x04, // 33
  0x00, 0x08, 0x0A, 0x04, // 34
  0x00, 0x12, 0x10, 0x07, // 35
  0x00, 0x22, 0x0E, 0x06, // 36
  0x00, 0x30, 0x11, 0x07, // 37
  0x00, 0x41, 0x11, 0x07, // 38
  0x00, 0x52, 0x04, 0x03, // 39
  0x00, 0x56, 0x08, 0x04, // 40
  0x00, 0x5E, 0x08, 0x04, // 41
  0x00, 0x66, 0x0D, 0x06, // 42
  0x00, 0x73, 0x0D, 0x06, // 43
  0x00, 0x80, 0x05, 0x03, // 44
  0x00, 0x85, 0x0A, 0x05, // 45
  0x00, 0x8F, 0x05, 0x03, // 46
  0x00, 0x94, 0x0A, 0x05, // 47
  0x00, 0x9E, 0x0E, 0x06, // 48
  0x00, 0xAC, 0x08, 0x04, // 49
  0x00, 0xB4, 0x0E, 0x06, // 50
  0x00, 0xC2, 0x0E, 0x06, // 51
  0x00, 0xD0, 0x0E, 0x06, // 52
  0x00, 0xDE, 0x0E, 0x06, // 53
  0x00, 0xEC, 0x0E, 0x06, // 54
  0x00, 0xFA, 0x0D, 0x06, // 55
  0x01, 0x07, 0x0E, 0x06, // 56
  0x01, 0x15, 0x0D, 0x06, // 57
  0x01, 0x22, 0x05, 0x03, // 58
  0x01, 0x27, 0x05, 0x03, // 59
  0x01, 0x2C, 0x0E, 0x06, // 60
  0x01, 0x3A, 0x10, 0x07, // 61
  0x01, 0x4A, 0x0D, 0x06, // 62
  0x01, 0x57, 0x0D, 0x06, // 63
  0x01, 0x64, 0x1A, 0x0A, // 64
  0x01, 0x7E, 0x11, 0x07, // 65
  0x01, 0x8F, 0x11, 0x07, // 66
  0x01, 0xA0, 0x11, 0x07, // 67
  0x01, 0xB1, 0x11, 0x07, // 68
  0x01, 0xC2, 0x0E, 0x06, // 69
  0x01, 0xD0, 0x0D, 0x06, // 70
  0x01, 0xDD, 0x11, 0x07, // 71
  0x01, 0xEE, 0x11, 0x07, // 72
  0x01, 0xFF, 0x05, 0x03, // 73
  0x02, 0x04, 0x0E, 0x06, // 74
  0x02, 0x12, 0x11, 0x07, // 75
  0x02, 0x23, 0x0E, 0x06, // 76
  0x02, 0x31, 0x17, 0x09, // 77
  0x02, 0x48, 0x14, 0x08, // 78
  0x02, 0x5C, 0x11, 0x07, // 79
  0x02, 0x6D, 0x10, 0x07, // 80
  0x02, 0x7D, 0x11, 0x07, // 81
  0x02, 0x8E, 0x11, 0x07, // 82
  0x02, 0x9F, 0x11, 0x07, // 83
  0x02, 0xB0, 0x10, 0x06, // 84
  0x02, 0xC0, 0x11, 0x07, // 85
  0x02, 0xD1, 0x13, 0x08, // 86
  0x02, 0xE4, 0x19, 0x0A, // 87
  0x02, 0xFD, 0x11, 0x07, // 88
  0x03, 0x0E, 0x10, 0x07, // 89
  0x03, 0x1E, 0x0E, 0x06, // 90
  0x03, 0x2C, 0x08, 0x04, // 91
  0x03, 0x34, 0x0B, 0x05, // 92
  0x03, 0x3F, 0x08, 0x04, // 93
  0x03, 0x47, 0x0D, 0x06, // 94
  0x03, 0x54, 0x11, 0x06, // 95
  0x03, 0x65, 0x0A, 0x04, // 96
  0x03, 0x6F, 0x0E, 0x06, // 97
  0x03, 0x7D, 0x0E, 0x06, // 98
  0x03, 0x8B, 0x0B, 0x05, // 99
  0x03, 0x96, 0x0E, 0x06, // 100
  0x03, 0xA4, 0x0E, 0x06, // 101
  0x03, 0xB2, 0x0D, 0x05, // 102
  0x03, 0xBF, 0x0E, 0x06, // 103
  0x03, 0xCD, 0x0E, 0x06, // 104
  0x03, 0xDB, 0x05, 0x03, // 105
  0x03, 0xE0, 0x08, 0x04, // 106
  0x03, 0xE8, 0x0E, 0x06, // 107
  0x03, 0xF6, 0x05, 0x03, // 108
  0x03, 0xFB, 0x17, 0x09, // 109
  0x04, 0x12, 0x0E, 0x06, // 110
  0x04, 0x20, 0x0E, 0x06, // 111
  0x04, 0x2E, 0x0E, 0x06, // 112
  0x04, 0x3C, 0x0E, 0x06, // 113
  0x04, 0x4A, 0x0A, 0x05, // 114
  0x04, 0x54, 0x0E, 0x06, // 115
  0x04, 0x62, 0x0B, 0x05, // 116
  0x04, 0x6D, 0x0E, 0x06, // 117
  0x04, 0x7B, 0x0D, 0x06, // 118
  0x04, 0x88, 0x13, 0x08, // 119
  0x04, 0x9B, 0x11, 0x07, // 120
  0x04, 0xAC, 0x0E, 0x06, // 121
  0x04, 0xBA, 0x0E, 0x06, // 122
  0x04, 0xC8, 0x0B, 0x04, // 123
  0x04, 0xD3, 0x05, 0x03, // 124
  0x04, 0xD8, 0x0A, 0x04, // 125
  0x04, 0xE2, 0x0A, 0x05, // 126
  // Font Data:
  0x00, 0x00, 0x00, 0x7E, 0x03, 0x00, 0x7E, 0x03, // 33
  0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0B, 0x00, 0x00, 0x07, // 34
  0x48, 0x01, 0x00, 0xFE, 0x01, 0x00, 0x5E, 0x00, 0x00, 0xE8, 0x01, 0x00, 0xFE, 0x01, 0x00, 0x4A, // 35
  0x9C, 0x01, 0x00, 0x36, 0x02, 0x00, 0x27, 0x07, 0x00, 0x62, 0x03, 0x00, 0xCC, 0x01, // 36
  0x9C, 0x01, 0x00, 0xD2, 0x00, 0x00, 0x6E, 0x00, 0x00, 0xB0, 0x03, 0x00, 0x58, 0x02, 0x00, 0xCC, 0x01, // 37
  0xDC, 0x01, 0x00, 0xFE, 0x03, 0x00, 0x62, 0x02, 0x00, 0xDC, 0x01, 0x00, 0x80, 0x03, 0x00, 0xC0, 0x02, // 38
  0x0B, 0x00, 0x00, 0x07, // 39
  0xF8, 0x03, 0x00, 0xFE, 0x0F, 0x00, 0x03, 0x18, // 40
  0x03, 0x18, 0x00, 0xFE, 0x0F, 0x00, 0xF8, 0x03, // 41
  0x48, 0x00, 0x00, 0x68, 0x00, 0x00, 0x3E, 0x00, 0x00, 0x68, 0x00, 0x00, 0x48, // 42
  0x20, 0x00, 0x00, 0x20, 0x00, 0x00, 0xF8, 0x00, 0x00, 0x20, 0x00, 0x00, 0x20, // 43
  0x00, 0x0B, 0x00, 0x00, 0x07, // 44
  0x20, 0x00, 0x00, 0x20, 0x00, 0x00, 0x20, 0x00, 0x00, 0x20, // 45
  0x00, 0x03, 0x00, 0x00, 0x03, // 46
  0x80, 0x03, 0x00, 0xF8, 0x03, 0x00, 0xFE, 0x00, 0x00, 0x0E, // 47
  0xFE, 0x01, 0x00, 0xFF, 0x03, 0x00, 0x01, 0x02, 0x00, 0xFF, 0x03, 0x00, 0xFE, 0x01, // 48
  0x02, 0x00, 0x00, 0xFF, 0x03, 0x00, 0xFF, 0x03, // 49
  0x86, 0x03, 0x00, 0xC7, 0x03, 0x00, 0x61, 0x02, 0x00, 0x3F, 0x02, 0x00, 0x1E, 0x02, // 50
  0x86, 0x01, 0x00, 0x87, 0x03, 0x00, 0x11, 0x02, 0x00, 0xFF, 0x03, 0x00, 0xEE, 0x01, // 51
  0x7C, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x40, 0x00, 0x00, 0xFF, 0x03, 0x00, 0xFF, 0x03, // 52
  0x9F, 0x01, 0x00, 0x9F, 0x03, 0x00, 0x09, 0x02, 0x00, 0xF9, 0x03, 0x00, 0xF1, 0x01, // 53
  0xFE, 0x01, 0x00, 0xFF, 0x03, 0x00, 0x09, 0x02, 0x00, 0xF9, 0x03, 0x00, 0xF1, 0x01, // 54
  0x81, 0x03, 0x00, 0xE1, 0x03, 0x00, 0xF9, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x07, // 55
  0xEE, 0x01, 0x00, 0xFF, 0x03, 0x00, 0x31, 0x02, 0x00, 0xFF, 0x03, 0x00, 0xEE, 0x01, // 56
  0x3E, 0x02, 0x00, 0x7F, 0x02, 0x00, 0x41, 0x03, 0x00, 0xFF, 0x01, 0x00, 0xFE, // 57
  0x18, 0x03, 0x00, 0x18, 0x03, // 58
  0x18, 0x0B, 0x00, 0x18, 0x07, // 59
  0x40, 0x00, 0x00, 0xE0, 0x00, 0x00, 0xB0, 0x01, 0x00, 0x18, 0x03, 0x00, 0x08, 0x02, // 60
  0x90, 0x00, 0x00, 0x90, 0x00, 0x00, 0x90, 0x00, 0x00, 0x90, 0x00, 0x00, 0x90, 0x00, 0x00, 0x90, // 61
  0x08, 0x02, 0x00, 0x18, 0x03, 0x00, 0xB0, 0x01, 0x00, 0xE0, 0x00, 0x00, 0x40, // 62
  0x0C, 0x00, 0x00, 0x4E, 0x03, 0x00, 0x62, 0x03, 0x00, 0x3E, 0x00, 0x00, 0x1C, // 63
  0xF8, 0x07, 0x00, 0x0C, 0x0C, 0x00, 0xE6, 0x19, 0x00, 0xF2, 0x13, 0x00, 0x32, 0x12, 0x00, 0x32, 0x11, 0x00, 0xF6, 0x13, 0x00, 0x0C, 0x02, 0x00, 0xF8, 0x01, // 64
  0xFC, 0x03, 0x00, 0xFE, 0x03, 0x00, 0x47, 0x00, 0x00, 0x47, 0x00, 0x00, 0xFE, 0x03, 0x00, 0xFC, 0x03, // 65
  0xFF, 0x03, 0x00, 0xFF, 0x03, 0x00, 0x11, 0x02, 0x00, 0x11, 0x02, 0x00, 0xFF, 0x03, 0x00, 0xEE, 0x01, // 66
  0xFE, 0x01, 0x00, 0xFF, 0x03, 0x00, 0x01, 0x02, 0x00, 0x01, 0x02, 0x00, 0x8F, 0x03, 0x00, 0x8E, 0x01, // 67
  0xFF, 0x03, 0x00, 0xFF, 0x03, 0x00, 0x01, 0x02, 0x00, 0x03, 0x03, 0x00, 0xFF, 0x03, 0x00, 0xFE, 0x01, // 68
  0xFF, 0x03, 0x00, 0xFF, 0x03, 0x00, 0x11, 0x02, 0x00, 0x11, 0x02, 0x00, 0x11, 0x02, // 69
  0xFF, 0x03, 0x00, 0xFF, 0x03, 0x00, 0x11, 0x00, 0x00, 0x11, 0x00, 0x00, 0x11, // 70
  0xFE, 0x01, 0x00, 0xFF, 0x03, 0x00, 0x03, 0x03, 0x00, 0x21, 0x02, 0x00, 0xEF, 0x03, 0x00, 0xEE, 0x01, // 71
  0xFF, 0x03, 0x00, 0xFF, 0x03, 0x00, 0x10, 0x00, 0x00, 0x10, 0x00, 0x00, 0xFF, 0x03, 0x00, 0xFF, 0x03, // 72
  0xFF, 0x03, 0x00, 0xFF, 0x03, // 73
  0x00, 0x01, 0x00, 0x00, 0x03, 0x00, 0x00, 0x02, 0x00, 0xFF, 0x03, 0x00, 0xFF, 0x01, // 74
  0xFF, 0x03, 0x00, 0xFF, 0x03, 0x00, 0x70, 0x00, 0x00, 0xF8, 0x00, 0x00, 0xDF, 0x03, 0x00, 0x8F, 0x03, // 75
  0xFF, 0x03, 0x00, 0xFF, 0x03, 0x00, 0x00, 0x02, 0x00, 0x00, 0x02, 0x00, 0x00, 0x02, // 76
  0xFF, 0x03, 0x00, 0xFF, 0x03, 0x00, 0x78, 0x00, 0x00, 0xE0, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x78, 0x00, 0x00, 0xFF, 0x03, 0x00, 0xFF, 0x03, // 77
  0xFF, 0x03, 0x00, 0xFF, 0x03, 0x00, 0x3C, 0x00, 0x00, 0x70, 0x00, 0x00, 0xC0, 0x01, 0x00, 0xFF, 0x03, 0x00, 0xFF, 0x03, // 78
  0xFE, 0x01, 0x00, 0xFF, 0x03, 0x00, 0x01, 0x02, 0x00, 0x01, 0x02, 0x00, 0xFF, 0x03, 0x00, 0xFE, 0x01, // 79
  0xFF, 0x03, 0x00, 0xFF, 0x03, 0x00, 0x21, 0x00, 0x00, 0x21, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x1E, // 80
  0xFE, 0x01, 0x00, 0xFF, 0x03, 0x00, 0x01, 0x03, 0x00, 0x01, 0x06, 0x00, 0xFF, 0x0F, 0x00, 0xFE, 0x05, // 81
  0xFF, 0x03, 0x00, 0xFF, 0x03, 0x00, 0x21, 0x00, 0x00, 0x61, 0x00, 0x00, 0xFF, 0x03, 0x00, 0x9E, 0x03, // 82
  0x8E, 0x01, 0x00, 0x9F, 0x03, 0x00, 0x39, 0x02, 0x00, 0x31, 0x02, 0x00, 0xF7, 0x03, 0x00, 0xE6, 0x01, // 83
  0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0xFF, 0x03, 0x00, 0xFF, 0x03, 0x00, 0x01, 0x00, 0x00, 0x01, // 84
  0xFF, 0x01, 0x00, 0xFF, 0x03, 0x00, 0x00, 0x02, 0x00, 0x00, 0x02, 0x00, 0xFF, 0x03, 0x00, 0xFF, 0x01, // 85
  0x1F, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xF0, 0x03, 0x00, 0x00, 0x03, 0x00, 0xF0, 0x03, 0x00, 0xFF, 0x00, 0x00, 0x1F, // 86
  0xFF, 0x00, 0x00, 0xFF, 0x03, 0x00, 0xC0, 0x03, 0x00, 0xF0, 0x00, 0x00, 0x7C, 0x00, 0x00, 0xF0, 0x00, 0x00, 0xC0, 0x03, 0x00, 0xFF, 0x03, 0x00, 0xFF, // 87
  0x03, 0x03, 0x00, 0xCF, 0x03, 0x00, 0xFC, 0x00, 0x00, 0xFC, 0x00, 0x00, 0xCF, 0x03, 0x00, 0x03, 0x03, // 88
  0x0F, 0x00, 0x00, 0x3F, 0x00, 0x00, 0xF0, 0x03, 0x00, 0xF0, 0x03, 0x00, 0x3F, 0x00, 0x00, 0x0F, // 89
  0x81, 0x03, 0x00, 0xE1, 0x03, 0x00, 0xF9, 0x02, 0x00, 0x1F, 0x02, 0x00, 0x0F, 0x02, // 90
  0xFF, 0x0F, 0x00, 0xFF, 0x0F, 0x00, 0x01, 0x08, // 91
  0x1E, 0x00, 0x00, 0xFE, 0x00, 0x00, 0xF0, 0x07, 0x00, 0x80, 0x07, // 92
  0x01, 0x08, 0x00, 0xFF, 0x0F, 0x00, 0xFF, 0x0F, // 93
  0x10, 0x00, 0x00, 0x18, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x18, 0x00, 0x00, 0x10, // 94
  0x00, 0x0C, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x0C, // 95
  0x01, 0x00, 0x00, 0x01, 0x00, 0x00, 0x03, 0x00, 0x00, 0x02, // 96
  0x90, 0x01, 0x00, 0xD8, 0x03, 0x00, 0x48, 0x02, 0x00, 0xF8, 0x03, 0x00, 0xF0, 0x03, // 97
  0xFF, 0x03, 0x00, 0xFF, 0x03, 0x00, 0x08, 0x02, 0x00, 0xF8, 0x03, 0x00, 0xF0, 0x01, // 98
  0xF0, 0x01, 0x00, 0xF8, 0x03, 0x00, 0x08, 0x02, 0x00, 0x08, 0x02, // 99
  0xF0, 0x01, 0x00, 0xF8, 0x03, 0x00, 0x08, 0x02, 0x00, 0xFF, 0x03, 0x00, 0xFF, 0x03, // 100
  0xF0, 0x01, 0x00, 0xF8, 0x03, 0x00, 0x48, 0x02, 0x00, 0x78, 0x03, 0x00, 0x70, 0x01, // 101
  0x08, 0x00, 0x00, 0xFE, 0x03, 0x00, 0xFF, 0x03, 0x00, 0x09, 0x00, 0x00, 0x09, // 102
  0xF0, 0x19, 0x00, 0xF8, 0x1B, 0x00, 0x08, 0x1A, 0x00, 0xF8, 0x1F, 0x00, 0xF8, 0x0F, // 103
  0xFF, 0x03, 0x00, 0xFF, 0x03, 0x00, 0x10, 0x00, 0x00, 0xF0, 0x03, 0x00, 0xE0, 0x03, // 104
  0xFB, 0x03, 0x00, 0xFB, 0x03, // 105
  0x00, 0x10, 0x00, 0xFB, 0x1F, 0x00, 0xFB, 0x0F, // 106
  0xFF, 0x03, 0x00, 0xFF, 0x03, 0x00, 0xE0, 0x00, 0x00, 0xB8, 0x03, 0x00, 0x18, 0x03, // 107
  0xFF, 0x03, 0x00, 0xFF, 0x03, // 108
  0xF8, 0x03, 0x00, 0xF0, 0x03, 0x00, 0x18, 0x00, 0x00, 0xF8, 0x03, 0x00, 0xF0, 0x03, 0x00, 0x18, 0x00, 0x00, 0xF8, 0x03, 0x00, 0xF0, 0x03, // 109
  0xF8, 0x03, 0x00, 0xF0, 0x03, 0x00, 0x18, 0x00, 0x00, 0xF8, 0x03, 0x00, 0xF0, 0x03, // 110
  0xF0, 0x01, 0x00, 0xF8, 0x03, 0x00, 0x08, 0x02, 0x00, 0xF8, 0x03, 0x00, 0xF0, 0x01, // 111
  0xF8, 0x1F, 0x00, 0xF8, 0x1F, 0x00, 0x08, 0x02, 0x00, 0xF8, 0x03, 0x00, 0xF0, 0x01, // 112
  0xF0, 0x01, 0x00, 0xF8, 0x03, 0x00, 0x08, 0x02, 0x00, 0xF8, 0x1F, 0x00, 0xF8, 0x1F, // 113
  0xF8, 0x03, 0x00, 0xF0, 0x03, 0x00, 0x18, 0x00, 0x00, 0x08, // 114
  0x30, 0x01, 0x00, 0x78, 0x03, 0x00, 0xE8, 0x02, 0x00, 0xD8, 0x03, 0x00, 0x90, 0x01, // 115
  0x08, 0x00, 0x00, 0xFE, 0x01, 0x00, 0xFE, 0x03, 0x00, 0x08, 0x02, // 116
  0xF8, 0x01, 0x00, 0xF8, 0x03, 0x00, 0x00, 0x02, 0x00, 0xF8, 0x03, 0x00, 0xF8, 0x03, // 117
  0xF8, 0x00, 0x00, 0xF8, 0x01, 0x00, 0x00, 0x03, 0x00, 0xF8, 0x01, 0x00, 0xF8, // 118
  0xF8, 0x00, 0x00, 0xF8, 0x03, 0x00, 0xC0, 0x03, 0x00, 0x70, 0x00, 0x00, 0xC0, 0x03, 0x00, 0xF8, 0x03, 0x00, 0xF8, // 119
  0x08, 0x02, 0x00, 0xB8, 0x03, 0x00, 0xF0, 0x01, 0x00, 0xF0, 0x01, 0x00, 0xB8, 0x03, 0x00, 0x08, 0x02, // 120
  0xF8, 0x00, 0x00, 0xF8, 0x19, 0x00, 0x00, 0x19, 0x00, 0xF8, 0x1F, 0x00, 0xF8, 0x0F, // 121
  0x08, 0x03, 0x00, 0xC8, 0x03, 0x00, 0xE8, 0x02, 0x00, 0x38, 0x02, 0x00, 0x18, 0x02, // 122
  0x20, 0x00, 0x00, 0xFE, 0x07, 0x00, 0xDF, 0x0F, 0x00, 0x01, 0x08, // 123
  0x00, 0x00, 0x00, 0xFE, 0x0F, // 124
  0x01, 0x08, 0x00, 0xDF, 0x0F, 0x00, 0xFE, 0x07, 0x00, 0x20, // 125
  0x19, 0x00, 0x00, 0x1D, 0x00, 0x00, 0x17, 0x00, 0x00, 0x12, // 126
};
// Font generated or edited with the glyphEditor
const uint8_t BIGFONT[] PROGMEM = {
  0x10, // Width: 16
  0x18, // Height: 24
  0x20, // First char: 32
  0x5F, // Number of chars: 95
  // Jump Table:
  0xFF, 0xFF, 0x00, 0x05, // 32
  0x00, 0x00, 0x05, 0x04, // 33
  0x00, 0x05, 0x0D, 0x06, // 34
  0x00, 0x12, 0x17, 0x09, // 35
  0x00, 0x29, 0x14, 0x08, // 36
  0x00, 0x3D, 0x20, 0x0C, // 37
  0x00, 0x5D, 0x1D, 0x0A, // 38
  0x00, 0x7A, 0x04, 0x03, // 39
  0x00, 0x7E, 0x0F, 0x06, // 40
  0x00, 0x8D, 0x0E, 0x06, // 41
  0x00, 0x9B, 0x16, 0x09, // 42
  0x00, 0xB1, 0x17, 0x09, // 43
  0x00, 0xC8, 0x06, 0x03, // 44
  0x00, 0xCE, 0x0E, 0x06, // 45
  0x00, 0xDC, 0x05, 0x03, // 46
  0x00, 0xE1, 0x13, 0x08, // 47
  0x00, 0xF4, 0x14, 0x08, // 48
  0x01, 0x08, 0x0B, 0x05, // 49
  0x01, 0x13, 0x14, 0x09, // 50
  0x01, 0x27, 0x14, 0x08, // 51
  0x01, 0x3B, 0x14, 0x08, // 52
  0x01, 0x4F, 0x14, 0x08, // 53
  0x01, 0x63, 0x17, 0x09, // 54
  0x01, 0x7A, 0x13, 0x08, // 55
  0x01, 0x8D, 0x17, 0x09, // 56
  0x01, 0xA4, 0x17, 0x09, // 57
  0x01, 0xBB, 0x05, 0x03, // 58
  0x01, 0xC0, 0x06, 0x04, // 59
  0x01, 0xC6, 0x14, 0x08, // 60
  0x01, 0xDA, 0x17, 0x0A, // 61
  0x01, 0xF1, 0x17, 0x09, // 62
  0x02, 0x08, 0x10, 0x07, // 63
  0x02, 0x18, 0x26, 0x0E, // 64
  0x02, 0x3E, 0x1D, 0x0B, // 65
  0x02, 0x5B, 0x17, 0x09, // 66
  0x02, 0x72, 0x17, 0x09, // 67
  0x02, 0x89, 0x17, 0x09, // 68
  0x02, 0xA0, 0x14, 0x08, // 69
  0x02, 0xB4, 0x13, 0x08, // 70
  0x02, 0xC7, 0x17, 0x09, // 71
  0x02, 0xDE, 0x17, 0x09, // 72
  0x02, 0xF5, 0x05, 0x03, // 73
  0x02, 0xFA, 0x11, 0x07, // 74
  0x03, 0x0B, 0x17, 0x09, // 75
  0x03, 0x22, 0x14, 0x08, // 76
  0x03, 0x36, 0x20, 0x0C, // 77
  0x03, 0x56, 0x1A, 0x0A, // 78
  0x03, 0x70, 0x17, 0x09, // 79
  0x03, 0x87, 0x16, 0x09, // 80
  0x03, 0x9D, 0x18, 0x09, // 81
  0x03, 0xB5, 0x17, 0x09, // 82
  0x03, 0xCC, 0x17, 0x09, // 83
  0x03, 0xE3, 0x16, 0x09, // 84
  0x03, 0xF9, 0x17, 0x09, // 85
  0x04, 0x10, 0x19, 0x0A, // 86
  0x04, 0x29, 0x25, 0x0E, // 87
  0x04, 0x4E, 0x14, 0x08, // 88
  0x04, 0x62, 0x16, 0x09, // 89
  0x04, 0x78, 0x17, 0x09, // 90
  0x04, 0x8F, 0x0C, 0x05, // 91
  0x04, 0x9B, 0x12, 0x07, // 92
  0x04, 0xAD, 0x0C, 0x05, // 93
  0x04, 0xB9, 0x13, 0x07, // 94
  0x04, 0xCC, 0x18, 0x08, // 95
  0x04, 0xE4, 0x0D, 0x06, // 96
  0x04, 0xF1, 0x14, 0x08, // 97
  0x05, 0x05, 0x14, 0x08, // 98
  0x05, 0x19, 0x14, 0x08, // 99
  0x05, 0x2D, 0x14, 0x08, // 100
  0x05, 0x41, 0x14, 0x08, // 101
  0x05, 0x55, 0x0D, 0x06, // 102
  0x05, 0x62, 0x14, 0x08, // 103
  0x05, 0x76, 0x14, 0x08, // 104
  0x05, 0x8A, 0x05, 0x03, // 105
  0x05, 0x8F, 0x0C, 0x05, // 106
  0x05, 0x9B, 0x14, 0x08, // 107
  0x05, 0xAF, 0x05, 0x04, // 108
  0x05, 0xB4, 0x23, 0x0D, // 109
  0x05, 0xD7, 0x14, 0x08, // 110
  0x05, 0xEB, 0x14, 0x08, // 111
  0x05, 0xFF, 0x14, 0x08, // 112
  0x06, 0x13, 0x15, 0x08, // 113
  0x06, 0x28, 0x0D, 0x06, // 114
  0x06, 0x35, 0x14, 0x08, // 115
  0x06, 0x49, 0x0E, 0x06, // 116
  0x06, 0x57, 0x14, 0x08, // 117
  0x06, 0x6B, 0x13, 0x08, // 118
  0x06, 0x7E, 0x1F, 0x0C, // 119
  0x06, 0x9D, 0x14, 0x08, // 120
  0x06, 0xB1, 0x15, 0x09, // 121
  0x06, 0xC6, 0x14, 0x08, // 122
  0x06, 0xDA, 0x0F, 0x06, // 123
  0x06, 0xE9, 0x06, 0x03, // 124
  0x06, 0xEF, 0x0E, 0x06, // 125
  0x06, 0xFD, 0x16, 0x0C, // 126
  // Font Data:
  0xFF, 0x33, 0x00, 0xFF, 0x33, // 33
  0x1B, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1B, 0x00, 0x00, 0x0F, // 34
  0x00, 0x02, 0x00, 0x10, 0x1F, 0x00, 0xFE, 0x1F, 0x00, 0x3E, 0x02, 0x00, 0x10, 0x1F, 0x00, 0xFE, 0x1F, 0x00, 0x3E, 0x02, 0x00, 0x10, 0x02, // 35
  0xF8, 0x70, 0x00, 0xFC, 0xF1, 0x00, 0x8C, 0xC3, 0x00, 0x0F, 0xC7, 0x03, 0x0C, 0xCE, 0x00, 0x3C, 0x7C, 0x00, 0x38, 0x38, // 36
  0x3C, 0x00, 0x00, 0x6E, 0x00, 0x00, 0x66, 0x30, 0x00, 0x76, 0x3C, 0x00, 0x3C, 0x0F, 0x00, 0xC0, 0x03, 0x00, 0xF0, 0x3C, 0x00, 0x3C, 0x6E, 0x00, 0x0C, 0x66, 0x00, 0x00, 0x76, 0x00, 0x00, 0x3C, // 37
  0x00, 0x1E, 0x00, 0x3C, 0x3F, 0x00, 0xFE, 0x61, 0x00, 0xC6, 0x61, 0x00, 0xC6, 0x63, 0x00, 0x7E, 0x6E, 0x00, 0x3C, 0x3C, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x6E, 0x00, 0x00, 0x40, // 38
  0x1F, 0x00, 0x00, 0x1F, // 39
  0x80, 0x3F, 0x00, 0xF0, 0xFF, 0x01, 0xFC, 0xE0, 0x07, 0x06, 0x00, 0x0C, 0x03, 0x00, 0x18, // 40
  0x03, 0x00, 0x18, 0x06, 0x00, 0x0C, 0xFC, 0xE0, 0x07, 0xF0, 0xFF, 0x01, 0x80, 0x3F, // 41
  0x10, 0x00, 0x00, 0x90, 0x01, 0x00, 0xD0, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x7E, 0x00, 0x00, 0xD0, 0x00, 0x00, 0x90, 0x01, 0x00, 0x10, // 42
  0x80, 0x01, 0x00, 0x80, 0x01, 0x00, 0x80, 0x01, 0x00, 0xF0, 0x0F, 0x00, 0xF0, 0x0F, 0x00, 0x80, 0x01, 0x00, 0x80, 0x01, 0x00, 0x80, 0x01, // 43
  0x00, 0xE0, 0x02, 0x00, 0xE0, 0x01, // 44
  0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, 0x00, 0x00, 0x03, // 45
  0x00, 0x60, 0x00, 0x00, 0x60, // 46
  0x00, 0xC0, 0x00, 0x00, 0xF0, 0x00, 0x00, 0x3E, 0x00, 0xC0, 0x07, 0x00, 0xF8, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x06, // 47
  0xFC, 0x3F, 0x00, 0xFE, 0x7F, 0x00, 0x06, 0x60, 0x00, 0x06, 0x60, 0x00, 0x06, 0x60, 0x00, 0xFE, 0x7F, 0x00, 0xFC, 0x3F, // 48
  0x18, 0x00, 0x00, 0x1C, 0x00, 0x00, 0xFE, 0x7F, 0x00, 0xFE, 0x7F, // 49
  0x1C, 0x7C, 0x00, 0x1E, 0x7E, 0x00, 0x06, 0x67, 0x00, 0x86, 0x63, 0x00, 0xC6, 0x61, 0x00, 0xFE, 0x60, 0x00, 0x7C, 0x60, // 50
  0x0C, 0x30, 0x00, 0x0E, 0x70, 0x00, 0x86, 0x60, 0x00, 0xC6, 0x61, 0x00, 0xE6, 0x63, 0x00, 0x7E, 0x7F, 0x00, 0x3C, 0x3E, // 51
  0xF0, 0x07, 0x00, 0xF8, 0x07, 0x00, 0x00, 0x06, 0x00, 0x00, 0x06, 0x00, 0xFE, 0x7F, 0x00, 0xFE, 0x7F, 0x00, 0x00, 0x06, // 52
  0xFE, 0x31, 0x00, 0xFE, 0x70, 0x00, 0xC6, 0x60, 0x00, 0xC6, 0x60, 0x00, 0xC6, 0x71, 0x00, 0x86, 0x3F, 0x00, 0x06, 0x1F, // 53
  0xE0, 0x1F, 0x00, 0xF8, 0x3F, 0x00, 0xBC, 0x71, 0x00, 0xCE, 0x60, 0x00, 0xC6, 0x60, 0x00, 0xC6, 0x71, 0x00, 0x86, 0x3F, 0x00, 0x00, 0x1F, // 54
  0x06, 0x00, 0x00, 0x06, 0x7E, 0x00, 0x86, 0x7F, 0x00, 0xC6, 0x03, 0x00, 0xE6, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x3E, // 55
  0x38, 0x1E, 0x00, 0x7C, 0x3F, 0x00, 0xEE, 0x73, 0x00, 0xC6, 0x61, 0x00, 0xC6, 0x61, 0x00, 0xEE, 0x73, 0x00, 0x7C, 0x3F, 0x00, 0x38, 0x1E, // 56
  0xF8, 0x00, 0x00, 0xFC, 0x61, 0x00, 0x8E, 0x63, 0x00, 0x06, 0x63, 0x00, 0x06, 0x73, 0x00, 0x8E, 0x3D, 0x00, 0xFC, 0x1F, 0x00, 0xF8, 0x07, // 57
  0x30, 0x60, 0x00, 0x30, 0x60, // 58
  0x30, 0xE0, 0x02, 0x30, 0xE0, 0x01, // 59
  0x00, 0x01, 0x00, 0x80, 0x03, 0x00, 0x80, 0x03, 0x00, 0xC0, 0x06, 0x00, 0x40, 0x04, 0x00, 0x60, 0x0C, 0x00, 0x30, 0x18, // 60
  0x00, 0x00, 0x00, 0xC0, 0x0C, 0x00, 0xC0, 0x0C, 0x00, 0xC0, 0x0C, 0x00, 0xC0, 0x0C, 0x00, 0xC0, 0x0C, 0x00, 0xC0, 0x0C, 0x00, 0xC0, 0x0C, // 61
  0x30, 0x18, 0x00, 0x20, 0x08, 0x00, 0x60, 0x0C, 0x00, 0x40, 0x04, 0x00, 0xC0, 0x06, 0x00, 0x80, 0x02, 0x00, 0x80, 0x03, 0x00, 0x00, 0x01, // 62
  0x0C, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x06, 0x67, 0x00, 0x86, 0x67, 0x00, 0xFE, 0x00, 0x00, 0x7C, // 63
  0x80, 0x7F, 0x00, 0xF0, 0xE0, 0x01, 0x18, 0x80, 0x03, 0x0C, 0x1E, 0x03, 0x8E, 0x3F, 0x06, 0xC6, 0x70, 0x06, 0x66, 0x60, 0x06, 0x66, 0x30, 0x06, 0xC6, 0x3F, 0x03, 0x0C, 0x60, 0x00, 0x0C, 0x60, 0x00, 0x38, 0x30, 0x00, 0xE0, 0x1F, // 64
  0x00, 0x7C, 0x00, 0x80, 0x7F, 0x00, 0xF0, 0x0F, 0x00, 0xFE, 0x0C, 0x00, 0x0E, 0x0C, 0x00, 0x0E, 0x0C, 0x00, 0xFE, 0x0C, 0x00, 0xF0, 0x0F, 0x00, 0x80, 0x7F, 0x00, 0x00, 0x7C, // 65
  0xFE, 0x7F, 0x00, 0xFE, 0x7F, 0x00, 0x86, 0x61, 0x00, 0x86, 0x61, 0x00, 0x86, 0x61, 0x00, 0xCE, 0x73, 0x00, 0x7C, 0x3F, 0x00, 0x38, 0x1C, // 66
  0xF8, 0x1F, 0x00, 0xFC, 0x3F, 0x00, 0x0E, 0x70, 0x00, 0x06, 0x60, 0x00, 0x06, 0x60, 0x00, 0x0E, 0x70, 0x00, 0x3C, 0x3C, 0x00, 0x38, 0x1C, // 67
  0xFE, 0x7F, 0x00, 0xFE, 0x7F, 0x00, 0x06, 0x60, 0x00, 0x06, 0x60, 0x00, 0x06, 0x60, 0x00, 0x0E, 0x70, 0x00, 0xFC, 0x3F, 0x00, 0xF8, 0x1F, // 68
  0xFE, 0x7F, 0x00, 0xFE, 0x7F, 0x00, 0x86, 0x61, 0x00, 0x86, 0x61, 0x00, 0x86, 0x61, 0x00, 0x86, 0x61, 0x00, 0x06, 0x60, // 69
  0xFE, 0x7F, 0x00, 0xFE, 0x7F, 0x00, 0x86, 0x01, 0x00, 0x86, 0x01, 0x00, 0x86, 0x01, 0x00, 0x86, 0x01, 0x00, 0x06, // 70
  0xF8, 0x1F, 0x00, 0xFC, 0x3F, 0x00, 0x0E, 0x70, 0x00, 0x06, 0x60, 0x00, 0x06, 0x63, 0x00, 0x0E, 0x63, 0x00, 0x3C, 0x7F, 0x00, 0x38, 0x3F, // 71
  0xFE, 0x7F, 0x00, 0xFE, 0x7F, 0x00, 0x80, 0x01, 0x00, 0x80, 0x01, 0x00, 0x80, 0x01, 0x00, 0x80, 0x01, 0x00, 0xFE, 0x7F, 0x00, 0xFE, 0x7F, // 72
  0xFE, 0x7F, 0x00, 0xFE, 0x7F, // 73
  0x00, 0x30, 0x00, 0x00, 0x70, 0x00, 0x00, 0x60, 0x00, 0x00, 0x60, 0x00, 0xFE, 0x7F, 0x00, 0xFE, 0x3F, // 74
  0xFE, 0x7F, 0x00, 0xFE, 0x7F, 0x00, 0xC0, 0x01, 0x00, 0xE0, 0x03, 0x00, 0x70, 0x07, 0x00, 0x18, 0x1E, 0x00, 0x0E, 0x78, 0x00, 0x06, 0x60, // 75
  0xFE, 0x7F, 0x00, 0xFE, 0x7F, 0x00, 0x00, 0x60, 0x00, 0x00, 0x60, 0x00, 0x00, 0x60, 0x00, 0x00, 0x60, 0x00, 0x00, 0x60, // 76
  0xFE, 0x7F, 0x00, 0xFE, 0x7F, 0x00, 0xF8, 0x00, 0x00, 0xE0, 0x0F, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x78, 0x00, 0x00, 0x3F, 0x00, 0xE0, 0x0F, 0x00, 0xF8, 0x00, 0x00, 0xFE, 0x7F, 0x00, 0xFE, 0x7F, // 77
  0xFE, 0x7F, 0x00, 0xFE, 0x7F, 0x00, 0x7C, 0x00, 0x00, 0xF0, 0x01, 0x00, 0xC0, 0x07, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x3C, 0x00, 0xFE, 0x7F, 0x00, 0xFE, 0x7F, // 78
  0xF8, 0x1F, 0x00, 0xFC, 0x3F, 0x00, 0x0E, 0x70, 0x00, 0x06, 0x60, 0x00, 0x06, 0x60, 0x00, 0x0E, 0x70, 0x00, 0xFC, 0x3F, 0x00, 0xF8, 0x1F, // 79
  0xFE, 0x7F, 0x00, 0xFE, 0x7F, 0x00, 0x06, 0x03, 0x00, 0x06, 0x03, 0x00, 0x06, 0x03, 0x00, 0x8E, 0x03, 0x00, 0xFC, 0x01, 0x00, 0xF8, // 80
  0xF8, 0x1F, 0x00, 0xFC, 0x3F, 0x00, 0x0E, 0x70, 0x00, 0x06, 0x60, 0x00, 0x06, 0x60, 0x00, 0x0E, 0xF0, 0x00, 0xFC, 0xBF, 0x01, 0xF8, 0x9F, 0x01, // 81
  0xFE, 0x7F, 0x00, 0xFE, 0x7F, 0x00, 0x06, 0x03, 0x00, 0x06, 0x03, 0x00, 0x06, 0x07, 0x00, 0x8E, 0x1F, 0x00, 0xFC, 0x7D, 0x00, 0xF8, 0x70, // 82
  0x3C, 0x38, 0x00, 0x7E, 0x78, 0x00, 0xE6, 0x60, 0x00, 0xC6, 0x61, 0x00, 0x86, 0x63, 0x00, 0x06, 0x67, 0x00, 0x1E, 0x7E, 0x00, 0x1C, 0x3C, // 83
  0x06, 0x00, 0x00, 0x06, 0x00, 0x00, 0x06, 0x00, 0x00, 0xFE, 0x7F, 0x00, 0xFE, 0x7F, 0x00, 0x06, 0x00, 0x00, 0x06, 0x00, 0x00, 0x06, // 84
  0xFE, 0x1F, 0x00, 0xFE, 0x3F, 0x00, 0x00, 0x70, 0x00, 0x00, 0x60, 0x00, 0x00, 0x60, 0x00, 0x00, 0x70, 0x00, 0xFE, 0x3F, 0x00, 0xFE, 0x1F, // 85
  0x1E, 0x00, 0x00, 0xFE, 0x00, 0x00, 0xE0, 0x07, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x78, 0x00, 0x00, 0x3F, 0x00, 0xE0, 0x07, 0x00, 0xFE, 0x00, 0x00, 0x1E, // 86
  0x7E, 0x00, 0x00, 0xFE, 0x0F, 0x00, 0x80, 0x7F, 0x00, 0x00, 0x78, 0x00, 0xC0, 0x1F, 0x00, 0xF8, 0x07, 0x00, 0x3C, 0x00, 0x00, 0xF8, 0x07, 0x00, 0xC0, 0x1F, 0x00, 0x00, 0x7C, 0x00, 0x80, 0x7F, 0x00, 0xFE, 0x0F, 0x00, 0x7E, // 87
  0x0E, 0x70, 0x00, 0x3E, 0x7C, 0x00, 0xF0, 0x07, 0x00, 0x80, 0x01, 0x00, 0xF0, 0x07, 0x00, 0x3E, 0x7C, 0x00, 0x0E, 0x70, // 88
  0x1E, 0x00, 0x00, 0x7E, 0x00, 0x00, 0xF0, 0x01, 0x00, 0x80, 0x7F, 0x00, 0x80, 0x7F, 0x00, 0xF0, 0x01, 0x00, 0x7E, 0x00, 0x00, 0x1E, // 89
  0x06, 0x78, 0x00, 0x06, 0x7C, 0x00, 0x06, 0x6F, 0x00, 0x86, 0x63, 0x00, 0xE6, 0x61, 0x00, 0x76, 0x60, 0x00, 0x3E, 0x60, 0x00, 0x1E, 0x60, // 90
  0xFF, 0xFF, 0x07, 0xFF, 0xFF, 0x07, 0x03, 0x00, 0x06, 0x03, 0x00, 0x06, // 91
  0x0E, 0x00, 0x00, 0x7C, 0x00, 0x00, 0xE0, 0x03, 0x00, 0x00, 0x1F, 0x00, 0x00, 0xF8, 0x00, 0x00, 0xC0, 0x01, // 92
  0x03, 0x00, 0x06, 0x03, 0x00, 0x06, 0xFF, 0xFF, 0x07, 0xFF, 0xFF, 0x07, // 93
  0xC0, 0x00, 0x00, 0x70, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x06, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x70, 0x00, 0x00, 0xC0, // 94
  0x00, 0x80, 0x01, 0x00, 0x80, 0x01, 0x00, 0x80, 0x01, 0x00, 0x80, 0x01, 0x00, 0x80, 0x01, 0x00, 0x80, 0x01, 0x00, 0x80, 0x01, 0x00, 0x80, 0x01, // 95
  0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x03, 0x00, 0x00, 0x06, 0x00, 0x00, 0x04, // 96
  0x00, 0x3C, 0x00, 0x60, 0x7E, 0x00, 0x70, 0x67, 0x00, 0x30, 0x63, 0x00, 0x30, 0x23, 0x00, 0xF0, 0x7F, 0x00, 0xE0, 0x7F, // 97
  0xFF, 0x7F, 0x00, 0xFF, 0x7F, 0x00, 0x60, 0x30, 0x00, 0x30, 0x60, 0x00, 0x70, 0x70, 0x00, 0xE0, 0x3F, 0x00, 0xC0, 0x1F, // 98
  0xC0, 0x1F, 0x00, 0xE0, 0x3F, 0x00, 0x70, 0x70, 0x00, 0x30, 0x60, 0x00, 0x30, 0x60, 0x00, 0xF0, 0x78, 0x00, 0xE0, 0x38, // 99
  0xC0, 0x1F, 0x00, 0xE0, 0x3F, 0x00, 0x70, 0x70, 0x00, 0x30, 0x60, 0x00, 0x60, 0x30, 0x00, 0xFF, 0x7F, 0x00, 0xFF, 0x7F, // 100
  0xE0, 0x3F, 0x00, 0xF0, 0x7F, 0x00, 0x30, 0x63, 0x00, 0x30, 0x63, 0x00, 0x30, 0x63, 0x00, 0xF0, 0x73, 0x00, 0xE0, 0x33, // 101
  0x30, 0x00, 0x00, 0xFE, 0x7F, 0x00, 0xFF, 0x7F, 0x00, 0x33, 0x00, 0x00, 0x33, // 102
  0xE0, 0x3F, 0x06, 0xF0, 0x7F, 0x06, 0x70, 0x70, 0x06, 0x30, 0x60, 0x06, 0x60, 0x30, 0x07, 0xF0, 0xFF, 0x03, 0xF0, 0xFF, // 103
  0xFF, 0x7F, 0x00, 0xFF, 0x7F, 0x00, 0x60, 0x00, 0x00, 0x30, 0x00, 0x00, 0x30, 0x00, 0x00, 0xF0, 0x7F, 0x00, 0xE0, 0x7F, // 104
  0xF3, 0x7F, 0x00, 0xF3, 0x7F, // 105
  0x00, 0x00, 0x06, 0x10, 0x00, 0x06, 0xF3, 0xFF, 0x07, 0xF3, 0xFF, 0x03, // 106
  0xFF, 0x7F, 0x00, 0xFF, 0x7F, 0x00, 0x80, 0x07, 0x00, 0xC0, 0x07, 0x00, 0xE0, 0x1E, 0x00, 0x70, 0x78, 0x00, 0x30, 0x60, // 107
  0xFF, 0x7F, 0x00, 0xFF, 0x7F, // 108
  0xF0, 0x7F, 0x00, 0xF0, 0x7F, 0x00, 0x60, 0x00, 0x00, 0x30, 0x00, 0x00, 0x30, 0x00, 0x00, 0xF0, 0x7F, 0x00, 0xE0, 0x7F, 0x00, 0x60, 0x00, 0x00, 0x30, 0x00, 0x00, 0x30, 0x00, 0x00, 0xF0, 0x7F, 0x00, 0xE0, 0x7F, // 109
  0xF0, 0x7F, 0x00, 0xF0, 0x7F, 0x00, 0x60, 0x00, 0x00, 0x30, 0x00, 0x00, 0x30, 0x00, 0x00, 0xF0, 0x7F, 0x00, 0xE0, 0x7F, // 110
  0xC0, 0x1F, 0x00, 0xE0, 0x3F, 0x00, 0x30, 0x70, 0x00, 0x30, 0x60, 0x00, 0x70, 0x60, 0x00, 0xE0, 0x3F, 0x00, 0xC0, 0x1F, // 111
  0xF0, 0xFF, 0x07, 0xF0, 0xFF, 0x07, 0x60, 0x30, 0x00, 0x30, 0x60, 0x00, 0x70, 0x70, 0x00, 0xE0, 0x3F, 0x00, 0xC0, 0x1F, // 112
  0xC0, 0x1F, 0x00, 0xE0, 0x3F, 0x00, 0x70, 0x70, 0x00, 0x30, 0x60, 0x00, 0x60, 0x30, 0x00, 0xF0, 0xFF, 0x07, 0xF0, 0xFF, 0x07, // 113
  0xF0, 0x7F, 0x00, 0xF0, 0x7F, 0x00, 0x60, 0x00, 0x00, 0x30, 0x00, 0x00, 0x30, // 114
  0xE0, 0x30, 0x00, 0xF0, 0x71, 0x00, 0xB0, 0x63, 0x00, 0x30, 0x67, 0x00, 0x30, 0x6E, 0x00, 0x70, 0x7C, 0x00, 0x60, 0x38, // 115
  0x30, 0x00, 0x00, 0xFE, 0x3F, 0x00, 0xFE, 0x7F, 0x00, 0x30, 0x60, 0x00, 0x30, 0x60, // 116
  0xF0, 0x3F, 0x00, 0xF0, 0x7F, 0x00, 0x00, 0x60, 0x00, 0x00, 0x60, 0x00, 0x00, 0x30, 0x00, 0xF0, 0x7F, 0x00, 0xF0, 0x7F, // 117
  0x70, 0x00, 0x00, 0xF0, 0x07, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x70, 0x00, 0x00, 0x3F, 0x00, 0xF0, 0x07, 0x00, 0x70, // 118
  0xF0, 0x00, 0x00, 0xE0, 0x1F, 0x00, 0x00, 0x7C, 0x00, 0x00, 0x7E, 0x00, 0xE0, 0x07, 0x00, 0x70, 0x00, 0x00, 0xE0, 0x07, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x7C, 0x00, 0xE0, 0x0F, 0x00, 0xF0, // 119
  0x30, 0x60, 0x00, 0xF0, 0x78, 0x00, 0xC0, 0x1F, 0x00, 0x00, 0x07, 0x00, 0xC0, 0x1F, 0x00, 0xF0, 0x78, 0x00, 0x30, 0x60, // 120
  0xF0, 0x0F, 0x06, 0xF0, 0x1F, 0x06, 0x00, 0x38, 0x06, 0x00, 0x30, 0x06, 0x00, 0x30, 0x07, 0xF0, 0xFF, 0x03, 0xF0, 0xFF, 0x01, // 121
  0x30, 0x78, 0x00, 0x30, 0x7C, 0x00, 0x30, 0x6E, 0x00, 0x30, 0x67, 0x00, 0xB0, 0x63, 0x00, 0xF0, 0x61, 0x00, 0xF0, 0x60, // 122
  0x00, 0x06, 0x00, 0xF8, 0xFF, 0x01, 0xFE, 0xF9, 0x07, 0x03, 0x00, 0x0C, 0x01, 0x00, 0x08, // 123
  0xFC, 0xFF, 0x07, 0xFC, 0xFF, 0x07, // 124
  0x01, 0x00, 0x08, 0x03, 0x00, 0x0C, 0xFE, 0xF9, 0x07, 0xF8, 0xFF, 0x00, 0x00, 0x06, // 125
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC6, 0x00, 0x00, 0xE3, 0x00, 0x00, 0xB1, 0x00, 0x00, 0x99, 0x00, 0x00, 0x8F, 0x00, 0x00, 0x86, // 126
};

