/**********************************************************************
    Mark Butcher    Bsc (Hons) MPhil MIET

    M.J.Butcher Consulting
    Birchstrasse 20f,    CH-5406, R�tihof
    Switzerland

    www.uTasker.com    Skype: M_J_Butcher

    ---------------------------------------------------------------------
    File:      app_user_files.h
    Project:   Single Chip Embedded Internet
    ---------------------------------------------------------------------
    Copyright (C) M.J.Butcher Consulting 2004..2016
    *********************************************************************
    06.08.2009 Add OLED graphical demo                                   {1}
    28.02.2010 Control LCD web interface with define LCD_WEB_INTERFACE   {2}
    
    The file is otherwise not specifically linked in to the project since it
    is included by application.c when needed.

*/        

//#define FAVICON_UTASKER                                                // use the uTasker favicon rather than chip manufacturer's


#ifdef FAVICON_UTASKER
        #define _favicon uTaskerfavicon
static const unsigned char uTaskerfavicon[] = {
    0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x10, 0x10,   0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x28, 0x01,
    0x00, 0x00, 0x16, 0x00, 0x00, 0x00, 0x28, 0x00,   0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x20, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00,   0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80,   0x00, 0x00, 0x00, 0x80, 0x80, 0x00, 0x80, 0x00,
    0x00, 0x00, 0x80, 0x00, 0x80, 0x00, 0x80, 0x80,   0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0xc0, 0xc0,
    0xc0, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0xff,   0x00, 0x00, 0x00, 0xff, 0xff, 0x00, 0xff, 0x00,
    0x00, 0x00, 0xff, 0x00, 0xff, 0x00, 0xff, 0xff,   0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0xf9, 0x99,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf9, 0x99,   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf9, 0x99,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf9, 0x99,   0x89, 0x98, 0x99, 0x9f, 0xff, 0xff, 0xf9, 0x99,
    0x99, 0x99, 0x99, 0x9f, 0xff, 0xff, 0xf9, 0x99,   0xdf, 0xf9, 0x99, 0x9f, 0xff, 0xff, 0xf9, 0x99,
    0xff, 0xf8, 0x99, 0x9f, 0xff, 0xff, 0xf9, 0x99,   0xff, 0xff, 0x99, 0x9f, 0xff, 0xff, 0xf9, 0x99,
    0xff, 0xff, 0x99, 0x9f, 0xff, 0xff, 0xf9, 0x99,   0xff, 0xff, 0x99, 0x9f, 0xff, 0xff, 0xf9, 0x99,
    0xff, 0xff, 0x99, 0x9f, 0xff, 0xff, 0xf9, 0x99,   0xff, 0xff, 0x99, 0x9f, 0xff, 0xff, 0xf9, 0x99,
    0xff, 0xff, 0x99, 0x9f, 0xff, 0xff, 0xf9, 0x99,   0xff, 0xff, 0x99, 0x9f, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
#else
    #if defined _HW_AVR32                                                // ATMEL favicon
        #define _favicon favicon_avr32
static const unsigned char favicon_avr32[] = {
0xff,0xd8,0xff,0xe0,0x00,0x10,0x4a,0x46,0x49,0x46,0x00,0x01,0x01,0x01,0x00,0x60,0x00,0x60,0x00,0x00,0xff,0xdb,0x00,0x43,0x00,0x08,0x06,0x06,0x07,0x06,0x05,0x08,
0x07,0x07,0x07,0x09,0x09,0x08,0x0a,0x0c,0x14,0x0d,0x0c,0x0b,0x0b,0x0c,0x19,0x12,0x13,0x0f,0x14,0x1d,0x1a,0x1f,0x1e,0x1d,0x1a,0x1c,0x1c,0x20,0x24,0x2e,0x27,0x20,
0x22,0x2c,0x23,0x1c,0x1c,0x28,0x37,0x29,0x2c,0x30,0x31,0x34,0x34,0x34,0x1f,0x27,0x39,0x3d,0x38,0x32,0x3c,0x2e,0x33,0x34,0x32,0xff,0xdb,0x00,0x43,0x01,0x09,0x09,
0x09,0x0c,0x0b,0x0c,0x18,0x0d,0x0d,0x18,0x32,0x21,0x1c,0x21,0x32,0x32,0x32,0x32,0x32,0x32,0x32,0x32,0x32,0x32,0x32,0x32,0x32,0x32,0x32,0x32,0x32,0x32,0x32,0x32,
0x32,0x32,0x32,0x32,0x32,0x32,0x32,0x32,0x32,0x32,0x32,0x32,0x32,0x32,0x32,0x32,0x32,0x32,0x32,0x32,0x32,0x32,0x32,0x32,0x32,0x32,0x32,0x32,0x32,0x32,0xff,0xc0,
0x00,0x11,0x08,0x00,0x21,0x00,0x1a,0x03,0x01,0x22,0x00,0x02,0x11,0x01,0x03,0x11,0x01,0xff,0xc4,0x00,0x1f,0x00,0x00,0x01,0x05,0x01,0x01,0x01,0x01,0x01,0x01,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0xff,0xc4,0x00,0xb5,0x10,0x00,0x02,0x01,0x03,0x03,0x02,0x04,0x03,0x05,
0x05,0x04,0x04,0x00,0x00,0x01,0x7d,0x01,0x02,0x03,0x00,0x04,0x11,0x05,0x12,0x21,0x31,0x41,0x06,0x13,0x51,0x61,0x07,0x22,0x71,0x14,0x32,0x81,0x91,0xa1,0x08,0x23,
0x42,0xb1,0xc1,0x15,0x52,0xd1,0xf0,0x24,0x33,0x62,0x72,0x82,0x09,0x0a,0x16,0x17,0x18,0x19,0x1a,0x25,0x26,0x27,0x28,0x29,0x2a,0x34,0x35,0x36,0x37,0x38,0x39,0x3a,
0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4a,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5a,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6a,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7a,
0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9a,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xb2,0xb3,0xb4,0xb5,0xb6,0xb7,
0xb8,0xb9,0xba,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xd2,0xd3,0xd4,0xd5,0xd6,0xd7,0xd8,0xd9,0xda,0xe1,0xe2,0xe3,0xe4,0xe5,0xe6,0xe7,0xe8,0xe9,0xea,0xf1,
0xf2,0xf3,0xf4,0xf5,0xf6,0xf7,0xf8,0xf9,0xfa,0xff,0xc4,0x00,0x1f,0x01,0x00,0x03,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x01,
0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0xff,0xc4,0x00,0xb5,0x11,0x00,0x02,0x01,0x02,0x04,0x04,0x03,0x04,0x07,0x05,0x04,0x04,0x00,0x01,0x02,0x77,0x00,
0x01,0x02,0x03,0x11,0x04,0x05,0x21,0x31,0x06,0x12,0x41,0x51,0x07,0x61,0x71,0x13,0x22,0x32,0x81,0x08,0x14,0x42,0x91,0xa1,0xb1,0xc1,0x09,0x23,0x33,0x52,0xf0,0x15,
0x62,0x72,0xd1,0x0a,0x16,0x24,0x34,0xe1,0x25,0xf1,0x17,0x18,0x19,0x1a,0x26,0x27,0x28,0x29,0x2a,0x35,0x36,0x37,0x38,0x39,0x3a,0x43,0x44,0x45,0x46,0x47,0x48,0x49,
0x4a,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5a,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6a,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7a,0x82,0x83,0x84,0x85,0x86,0x87,0x88,
0x89,0x8a,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9a,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xb2,0xb3,0xb4,0xb5,0xb6,0xb7,0xb8,0xb9,0xba,0xc2,0xc3,0xc4,
0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xd2,0xd3,0xd4,0xd5,0xd6,0xd7,0xd8,0xd9,0xda,0xe2,0xe3,0xe4,0xe5,0xe6,0xe7,0xe8,0xe9,0xea,0xf2,0xf3,0xf4,0xf5,0xf6,0xf7,0xf8,0xf9,
0xfa,0xff,0xda,0x00,0x0c,0x03,0x01,0x00,0x02,0x11,0x03,0x11,0x00,0x3f,0x00,0xf6,0xba,0xc9,0xf1,0x26,0xb7,0x17,0x87,0xb4,0x1b,0x9d,0x46,0x40,0x19,0x91,0x76,0xc4,
0x84,0xfd,0xf9,0x0f,0x0a,0xbf,0x9f,0x5f,0x6c,0x9a,0xd6,0xaf,0x15,0xf8,0x97,0xe2,0x13,0xaa,0xeb,0xdf,0xd9,0xb0,0x3e,0x6d,0x2c,0x09,0x53,0x83,0xc3,0x4d,0xfc,0x47,
0xfe,0x03,0xf7,0x7e,0xbb,0xab,0xa7,0x0b,0x43,0xdb,0x54,0x4b,0xa7,0x53,0x9f,0x13,0x5b,0xd9,0x53,0x72,0xea,0x73,0xcf,0xe2,0xaf,0x11,0x15,0x76,0x3a,0xe5,0xfe,0xe3,
0x92,0x71,0x31,0x03,0x3e,0xc3,0xb5,0x7b,0xf6,0x8e,0xef,0x2e,0x89,0x61,0x24,0x8e,0xce,0xed,0x6d,0x1b,0x33,0x31,0xc9,0x62,0x54,0x64,0x9a,0xf9,0xa9,0xfe,0xe3,0x7d,
0x0d,0x7d,0x29,0xa2,0x7f,0xc8,0x07,0x4e,0xff,0x00,0xaf,0x58,0xbf,0xf4,0x11,0x5d,0xd9,0x94,0x23,0x18,0xc6,0xca,0xc7,0x16,0x5d,0x39,0x4a,0x52,0xbb,0x33,0x3c,0x69,
0xe2,0x11,0xe1,0xcf,0x0e,0xcd,0x73,0x1b,0x0f,0xb5,0xcb,0xfb,0x9b,0x60,0x7f,0xbe,0x47,0x5f,0xc0,0x64,0xfe,0x18,0xef,0x5e,0x21,0xa1,0xe9,0x13,0xeb,0xba,0xcd,0xb6,
0x9b,0x6e,0xd8,0x79,0x98,0xee,0x91,0x86,0x76,0x28,0xe5,0x98,0xff,0x00,0x9e,0x49,0x1e,0xb5,0xd3,0xf8,0xf1,0xf5,0x9f,0x10,0xf8,0x89,0xcc,0x3a,0x46,0xa6,0xd6,0x56,
0x80,0xc3,0x06,0x2d,0x24,0xc3,0x73,0xf3,0x38,0xe3,0xb9,0x03,0x1e,0xc0,0x56,0x87,0xc3,0x1b,0x7b,0xed,0x3b,0x5e,0x9e,0x1b,0xad,0x0e,0xea,0x2f,0x3e,0x23,0xfe,0x97,
0x3c,0x2e,0x9e,0x58,0x5c,0x7c,0x83,0x2b,0x8e,0x49,0xcf,0x5e,0xc3,0xd2,0xae,0x8a,0xfa,0xbe,0x1d,0xc9,0x7c,0x4f,0x5f,0xeb,0xd0,0x55,0xaf,0x5f,0x10,0xa2,0xfe,0x14,
0x79,0xc4,0xc0,0x29,0x95,0x54,0x92,0xaa,0x58,0x02,0x46,0x32,0x05,0x7d,0x25,0xa2,0x7f,0xc8,0x07,0x4e,0xff,0x00,0xaf,0x58,0xbf,0xf4,0x11,0x5f,0x3e,0x4b,0xa0,0xeb,
0x44,0xca,0x46,0x8b,0xa9,0x9c,0x96,0xc7,0xfa,0x1c,0x9e,0xa7,0xfd,0x9a,0xfa,0x13,0x46,0x56,0x4d,0x0f,0x4f,0x57,0x56,0x46,0x16,0xd1,0x82,0xac,0x08,0x20,0xed,0x1c,
0x10,0x7a,0x1a,0x8c,0xce,0x49,0xc6,0x36,0x63,0xcb,0xe2,0xd4,0xa5,0x74,0x5d,0xa2,0x8a,0x2b,0xc8,0x3d,0x50,0xa4,0xa2,0x8a,0x00,0xff,0xd9,
};
    #elif defined _HW_SAM7X                                              // AT91 favicon
        #define _favicon AT91_favicon
static const unsigned char AT91_favicon[] = {
0x00,0x00,0x01,0x00,0x01,0x00,0x10,0x10,0x00,0x00,0x01,0x00,0x20,0x00,0x68,0x04,0x00,0x00,0x16,0x00,0x00,0x00,0x28,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x20,0x00,
0x00,0x00,0x01,0x00,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x13,0x0b,0x00,0x00,0x13,0x0b,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xbe,0xff,
0xff,0x08,0xbe,0xff,0xff,0x13,0xbe,0xff,0xff,0x21,0xab,0xe5,0xe5,0x37,0x8b,0xba,0xba,0x52,0x7b,0xa5,0xa5,0x66,0x82,0xae,0xae,0x64,0x94,0xc7,0xc7,0x52,0xad,0xe8,
0xe8,0x3e,0xac,0xe7,0xe7,0x3b,0x80,0xab,0xab,0x48,0x61,0x82,0x82,0x46,0x6c,0x91,0x91,0x2e,0xa4,0xdc,0xdc,0x14,0xbe,0xff,0xff,0x08,0xbe,0xff,0xff,0x01,0xbe,0xff,
0xff,0x0f,0xbe,0xff,0xff,0x20,0xbe,0xff,0xff,0x38,0xb0,0xd2,0xc1,0x67,0x9c,0xad,0x96,0x97,0x7c,0xa6,0xa6,0xaa,0x7a,0xa3,0xa3,0xb4,0x83,0xb1,0xb1,0x9e,0x9d,0xd2,
0xd2,0x75,0xa9,0xcb,0xbb,0x71,0x88,0x91,0x79,0x93,0x53,0x6f,0x6f,0x8a,0x5b,0x7b,0x7b,0x5a,0x90,0xc2,0xc2,0x25,0xbe,0xff,0xff,0x0d,0xbe,0xff,0xff,0x02,0xbe,0xff,
0xff,0x17,0xbe,0xff,0xff,0x30,0xbe,0xff,0xff,0x55,0xbf,0x9a,0x59,0xbd,0xc5,0x67,0x00,0xff,0xc3,0x6c,0x0b,0xfc,0xb0,0x91,0x57,0xf1,0x93,0xc5,0xc5,0xd8,0x9e,0xd4,
0xd4,0xb4,0xb9,0x9a,0x5d,0xca,0xc5,0x67,0x00,0xff,0x85,0x7b,0x57,0xc4,0x67,0x8a,0x8a,0x77,0x96,0xc9,0xc9,0x34,0xbe,0xff,0xff,0x13,0xbe,0xff,0xff,0x03,0xbe,0xff,
0xff,0x1d,0xbe,0xff,0xff,0x3d,0xbe,0xff,0xff,0x6a,0xb4,0xe2,0xd8,0xae,0xb6,0xae,0x80,0xe8,0xc0,0x7f,0x2b,0xfb,0xc5,0x67,0x00,0xff,0xb5,0xbb,0x97,0xf6,0xa9,0xe3,
0xe3,0xdd,0xbb,0xa5,0x6e,0xdf,0xc5,0x67,0x00,0xff,0x91,0x8d,0x6b,0xce,0x77,0x9f,0x9f,0x84,0x9f,0xd5,0xd5,0x3e,0xbe,0xff,0xff,0x18,0xbe,0xff,0xff,0x04,0xbe,0xff,
0xff,0x22,0xbe,0xff,0xff,0x46,0xbe,0xff,0xff,0x7a,0xbf,0x94,0x50,0xe6,0xc5,0x67,0x00,0xff,0xc5,0x67,0x00,0xff,0xc5,0x67,0x00,0xff,0xc2,0x99,0x54,0xff,0xb4,0xf1,
0xf1,0xf0,0xbb,0xaa,0x77,0xed,0xc5,0x67,0x00,0xff,0x97,0x96,0x75,0xd6,0x7e,0xa9,0xa9,0x8b,0xa2,0xd9,0xd9,0x44,0xbe,0xff,0xff,0x1a,0xbe,0xff,0xff,0x05,0xbe,0xff,
0xff,0x26,0xbe,0xff,0xff,0x4c,0xbe,0xff,0xff,0x82,0xc5,0x67,0x00,0xff,0xc3,0x7a,0x20,0xfe,0xbe,0xf5,0xee,0xff,0xc5,0x67,0x00,0xff,0xc3,0x90,0x44,0xff,0xbc,0xf1,
0xea,0xf9,0xbd,0xaf,0x7d,0xf5,0xc5,0x67,0x00,0xff,0x98,0x99,0x79,0xdc,0x82,0xaf,0xaf,0x8f,0xa3,0xdb,0xdb,0x47,0xbe,0xff,0xff,0x1b,0xbe,0xff,0xff,0x05,0xbe,0xff,
0xff,0x27,0xbe,0xff,0xff,0x4e,0xbe,0xff,0xff,0x84,0xc4,0x77,0x1b,0xf8,0xc4,0x70,0x10,0xfe,0xc1,0xc2,0x99,0xff,0xc5,0x67,0x00,0xff,0xc2,0xae,0x77,0xff,0xc2,0xa4,
0x66,0xff,0xc4,0x70,0x10,0xfe,0xc5,0x67,0x00,0xff,0xa0,0xa3,0x82,0xd4,0x8e,0xbf,0xbf,0x85,0xa9,0xe3,0xe3,0x44,0xbe,0xff,0xff,0x1a,0xbe,0xff,0xff,0x04,0xbe,0xff,
0xff,0x26,0xbe,0xff,0xff,0x4b,0xbe,0xff,0xff,0x7f,0xbe,0xca,0xa9,0xd2,0xc4,0x79,0x1f,0xfd,0xc5,0x67,0x00,0xff,0xc3,0x90,0x44,0xff,0xbe,0xf5,0xee,0xff,0xc0,0xd6,
0xba,0xfe,0xc3,0x82,0x2f,0xfb,0xc5,0x67,0x00,0xff,0xa9,0xaa,0x86,0xc3,0xa0,0xd6,0xd6,0x6f,0xb6,0xf5,0xf5,0x3a,0xbe,0xff,0xff,0x16,0xbe,0xff,0xff,0x03,0xbe,0xff,
0xff,0x25,0xbe,0xff,0xff,0x48,0xbe,0xff,0xff,0x7b,0xb9,0xdc,0xcb,0xc8,0xb7,0xea,0xe3,0xee,0xbe,0xff,0xff,0xff,0xbe,0xf5,0xee,0xff,0xbf,0xeb,0xdd,0xff,0xbb,0xfb,
0xfb,0xf9,0xb7,0xdf,0xd0,0xec,0xa7,0xd3,0xcb,0xda,0x8d,0xbe,0xbe,0xaf,0x9d,0xd2,0xd2,0x66,0xbe,0xff,0xff,0x32,0xbe,0xff,0xff,0x13,0xbe,0xff,0xff,0x02,0xbe,0xff,
0xff,0x24,0xbe,0xff,0xff,0x48,0xbe,0xff,0xff,0x7d,0xc4,0x76,0x1a,0xf7,0xc4,0x70,0x0f,0xfe,0xbf,0xeb,0xdd,0xff,0xc3,0x9a,0x55,0xff,0xc5,0x67,0x00,0xff,0xc0,0xd6,
0xbb,0xff,0xc5,0x67,0x00,0xff,0xbc,0x83,0x35,0xf7,0x85,0xb2,0xb2,0xbd,0x95,0xc8,0xc8,0x6c,0xbe,0xff,0xff,0x32,0xbe,0xff,0xff,0x12,0xbe,0xff,0xff,0x02,0xbe,0xff,
0xff,0x21,0xbe,0xff,0xff,0x47,0xbe,0xff,0xff,0x7d,0xc1,0x99,0x54,0xe7,0xc5,0x67,0x00,0xff,0xc5,0x67,0x00,0xff,0xc5,0x67,0x00,0xff,0xc5,0x71,0x11,0xff,0xbe,0xff,
0xff,0xff,0xc5,0x67,0x00,0xff,0xbe,0x85,0x38,0xf8,0x8a,0xba,0xba,0xc2,0x99,0xcd,0xcd,0x72,0xbe,0xff,0xff,0x36,0xbe,0xff,0xff,0x14,0xbe,0xff,0xff,0x03,0xbe,0xff,
0xff,0x1c,0xbe,0xff,0xff,0x41,0xbe,0xff,0xff,0x76,0xc0,0xbf,0x95,0xcf,0xc5,0x67,0x00,0xff,0xc3,0x9a,0x55,0xff,0xc5,0x67,0x00,0xff,0xc3,0x9a,0x55,0xff,0xbe,0xff,
0xff,0xff,0xc5,0x67,0x00,0xff,0xbe,0x85,0x38,0xf9,0x8a,0xba,0xba,0xc7,0x92,0xc3,0xc3,0x7d,0xad,0xe8,0xe8,0x3e,0xb6,0xf5,0xf5,0x17,0xbe,0xff,0xff,0x04,0xbe,0xff,
0xff,0x18,0xbe,0xff,0xff,0x39,0xbe,0xff,0xff,0x6b,0xbe,0xef,0xe5,0xac,0xc5,0x67,0x00,0xff,0xc5,0x71,0x11,0xff,0xc5,0x67,0x00,0xff,0xc1,0xc2,0x99,0xff,0xbe,0xff,
0xff,0xff,0xc5,0x67,0x00,0xff,0xbd,0x84,0x37,0xfa,0x84,0xb0,0xb0,0xd3,0x7b,0xa4,0xa4,0x99,0x88,0xb6,0xb6,0x53,0xa6,0xde,0xde,0x1c,0xbe,0xff,0xff,0x05,0xbe,0xff,
0xff,0x12,0xbe,0xff,0xff,0x2f,0xbe,0xff,0xff,0x5a,0xbe,0xff,0xff,0x8e,0xc2,0x87,0x37,0xf0,0xc5,0x67,0x00,0xff,0xc5,0x67,0x00,0xff,0xbf,0xe1,0xcc,0xff,0xc0,0xc0,
0x97,0xfd,0xc5,0x67,0x00,0xff,0xc1,0x75,0x1a,0xfb,0xa3,0x92,0x62,0xdf,0x7e,0x98,0x8e,0xa6,0x7b,0xa5,0xa5,0x5d,0x98,0xcd,0xcd,0x20,0xbe,0xff,0xff,0x07,0xbe,0xff,
0xff,0x0c,0xbe,0xff,0xff,0x21,0xbe,0xff,0xff,0x43,0xbe,0xff,0xff,0x69,0xc1,0xa2,0x64,0xc6,0xc5,0x67,0x00,0xff,0xc3,0x80,0x2a,0xf7,0xbf,0xaf,0x7b,0xeb,0xc5,0x67,
0x00,0xff,0xc5,0x67,0x00,0xff,0xc5,0x67,0x00,0xff,0xc5,0x67,0x00,0xff,0xaa,0x9c,0x6d,0x98,0x97,0xca,0xca,0x44,0xac,0xe7,0xe7,0x1c,0xbe,0xff,0xff,0x08,0xbe,0xff,
0xff,0x06,0xbe,0xff,0xff,0x14,0xbe,0xff,0xff,0x2a,0xbe,0xff,0xff,0x42,0xbe,0xff,0xff,0x5e,0xbe,0xff,0xff,0x77,0xbe,0xff,0xff,0x87,0xbe,0xff,0xff,0x8d,0xbe,0xff,
0xff,0x8d,0xbe,0xff,0xff,0x85,0xbe,0xff,0xff,0x73,0xbe,0xff,0xff,0x5a,0xbe,0xff,0xff,0x40,0xbe,0xff,0xff,0x27,0xbe,0xff,0xff,0x13,0xbe,0xff,0xff,0x06,0xff,0xff,
0x00,0x00,0xf0,0xcf,0x00,0x00,0xe0,0x0f,0x00,0x00,0xe0,0x07,0x00,0x00,0xe0,0x07,0x00,0x00,0xc0,0x07,0x00,0x00,0xc0,0x07,0x00,0x00,0xe0,0x0f,0x00,0x00,0xe0,0x0f,
0x00,0x00,0xe0,0x0f,0x00,0x00,0xe0,0x0f,0x00,0x00,0xe0,0x0f,0x00,0x00,0xe0,0x07,0x00,0x00,0xe0,0x07,0xff,0xff,0xf0,0x07,0xff,0xff,0xfc,0x3f,0xff,0xff,
};
    #elif defined _M5223X || defined _FLEXIS32 || defined _KINETIS       // freescale favicon
        #define _favicon Freescale_favicon
static const unsigned char Freescale_favicon[] = {
0x00,0x00,0x01,0x00,0x01,0x00,0x10,0x10,0x00,0x00,0x01,0x00,0x20,0x00,0x68,0x04,0x00,0x00,0x16,0x00,0x00,0x00,0x28,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x20,0x00,
0x00,0x00,0x01,0x00,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x21,0x65,
0xf2,0x5f,0x20,0x65,0xf1,0xef,0x20,0x65,0xf2,0xef,0x21,0x65,0xf2,0x2f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x65,
0xf2,0xcf,0x20,0x65,0xf1,0xff,0x21,0x65,0xf2,0xff,0x20,0x65,0xf2,0xff,0x20,0x65,0xf1,0xaf,0x21,0x66,0xf2,0x0f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x21,0x65,0xf2,0x4f,0x20,0x65,0xf2,0xef,0x20,0x65,0xf1,0xff,0x20,0x65,0xf2,0xcf,0x21,0x66,0xf2,0x0f,0x0c,0xc1,0xff,0x3f,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x21,0x65,0xf2,0x0f,0x20,0x65,0xf2,0x2f,0x0c,0xc2,0xff,0x4f,0x0b,0xc1,0xff,0xef,0x0b,0xc1,0xff,0xff,0x0c,0xc1,0xff,0xef,0x0b,0xc1,
0xff,0x2f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x65,0xf1,0x5f,0x20,0x65,0xf1,0xdf,0x16,0x93,0xf8,0x5f,0x0b,0xc1,0xff,0xcf,0x0b,0xc1,0xff,0xff,0x0b,0xc1,0xff,0xff,0x0b,0xc1,
0xff,0xff,0x0b,0xc1,0xff,0x9f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x21,0x65,0xf2,0x9f,0x20,0x65,0xf1,0xff,0x20,0x65,0xf1,0xff,0x20,0x65,0xf1,0xff,0x21,0x65,0xf2,0xaf,0x0f,0xb2,0xfc,0x5f,0x0b,0xc1,0xff,0xef,0x0b,0xc1,
0xff,0xcf,0x11,0xaa,0xfb,0x3f,0x21,0x65,0xf2,0x9f,0x20,0x65,0xf2,0x5f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x21,0x65,0xf2,0x4f,0x21,0x65,0xf2,0xef,0x20,0x65,0xf1,0xff,0x20,0x65,0xf1,0xff,0x20,0x65,0xf1,0xcf,0x00,0x00,0x00,0x00,0x21,0x65,
0xf2,0x1f,0x20,0x65,0xf2,0xff,0x20,0x65,0xf1,0xff,0x20,0x65,0xf1,0xff,0x20,0x65,0xf1,0xcf,0x21,0x65,0xf2,0x2f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x21,0x65,0xf2,0x9f,0x21,0x66,0xf2,0x2f,0x0c,0xc2,0xff,0x5f,0x0b,0xc1,0xff,0xef,0x0b,0xc1,
0xff,0xef,0x16,0x93,0xf8,0x5f,0x21,0x65,0xf2,0xcf,0x20,0x65,0xf1,0xff,0x20,0x65,0xf2,0xff,0x20,0x65,0xf1,0xff,0x20,0x65,0xf2,0x2f,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0b,0xc1,0xff,0x0f,0x0b,0xc1,0xff,0xcf,0x0b,0xc1,0xff,0xff,0x0b,0xc1,
0xff,0xff,0x0c,0xc1,0xff,0xff,0x0c,0xc1,0xff,0xaf,0x1d,0x72,0xf3,0x6f,0x21,0x65,0xf2,0x9f,0x21,0x65,0xf2,0x0f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0c,0xc1,0xff,0x4f,0x0c,0xc1,
0xff,0xef,0x0b,0xc1,0xff,0xff,0x0b,0xc1,0xff,0xcf,0x16,0x93,0xf8,0x1f,0x20,0x65,0xf2,0x3f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0c,0xc1,
0xff,0x0f,0x0c,0xc1,0xff,0x2f,0x20,0x65,0xf2,0x8f,0x21,0x65,0xf2,0xff,0x20,0x65,0xf1,0xff,0x21,0x65,0xf2,0xef,0x20,0x65,0xf1,0x2f,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0b,0xc1,
0xff,0x5f,0x0b,0xc1,0xff,0xef,0x16,0x93,0xf8,0x5f,0x20,0x65,0xf1,0xcf,0x20,0x65,0xf1,0xff,0x20,0x65,0xf2,0xff,0x20,0x65,0xf1,0xff,0x20,0x65,0xf1,0xcf,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x65,0xf2,0x3f,0x0c,0xc2,0xff,0x9f,0x0b,0xc1,
0xff,0xff,0x0b,0xc1,0xff,0xff,0x0b,0xc1,0xff,0xff,0x0b,0xc1,0xff,0xaf,0x1d,0x74,0xf4,0x5f,0x21,0x65,0xf2,0xef,0x21,0x65,0xf2,0x9f,0x21,0x65,0xf2,0x0f,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x65,0xf1,0x4f,0x21,0x65,0xf2,0xef,0x20,0x65,0xf2,0xff,0x20,0x65,0xf1,0xcf,0x0f,0xb1,
0xfc,0x5f,0x0b,0xc1,0xff,0xef,0x0b,0xc1,0xff,0xff,0x0b,0xc1,0xff,0xff,0x0b,0xc1,0xff,0x9f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x65,0xf1,0x2f,0x20,0x65,0xf1,0xef,0x20,0x65,0xf1,0xff,0x20,0x65,0xf1,0xff,0x20,0x65,
0xf1,0xff,0x21,0x65,0xf2,0x9f,0x0c,0xc1,0xff,0x9f,0x0c,0xc2,0xff,0x2f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x21,0x65,0xf2,0x5f,0x20,0x65,0xf1,0xff,0x21,0x65,
0xf2,0xcf,0x21,0x65,0xf2,0x2f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0f,0xff,
0x00,0x00,0x03,0xff,0x00,0x00,0x81,0xff,0x00,0x00,0xc0,0x7f,0x00,0x00,0xc0,0x3f,0x00,0x00,0x80,0x0f,0x00,0x00,0xc1,0x03,0x00,0x00,0xf0,0x01,0x00,0x00,0xf8,0x03,
0x00,0x00,0xfe,0x07,0x00,0x00,0xff,0x01,0x00,0x00,0xff,0x00,0x00,0x00,0xfc,0x00,0x00,0x00,0xf0,0x07,0x00,0x00,0xf0,0x0f,0x00,0x00,0xfc,0x3f,0x00,0x00,
};
    #elif defined _LPC23XX || defined _LPC17XX                           // NXP favicon
        #define _favicon nxp_favicon
static const unsigned char nxp_favicon[] = {
0x00,0x00,0x01,0x00,0x01,0x00,0x10,0x10,0x00,0x00,0x01,0x00,0x20,0x00,0x68,0x04,0x00,0x00,0x16,0x00,0x00,0x00,0x28,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x20,0x00,
0x00,0x00,0x01,0x00,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x13,0x0b,0x00,0x00,0x13,0x0b,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xb5,
0xf9,0xff,0x00,0xb5,0xf9,0xff,0x00,0xb5,0xf9,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,
0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0x00,0xd2,0xc9,0xff,0x00,0xd2,0xc9,0xff,0x00,0xd2,0xc9,0xff,0x00,0xd2,0xc9,0xff,0x00,0xb5,
0xf9,0xff,0x00,0xb5,0xf9,0xff,0x00,0xb5,0xf9,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,
0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0x00,0xd2,0xc9,0xff,0x00,0xd2,0xc9,0xff,0x00,0xd2,0xc9,0xff,0x00,0xd2,0xc9,0xff,0x00,0xb5,
0xf9,0xff,0x00,0xb5,0xf9,0xff,0x00,0xb5,0xf9,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,
0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0x00,0xd2,0xc9,0xff,0x00,0xd2,0xc9,0xff,0x00,0xd2,0xc9,0xff,0x00,0xd2,0xc9,0xff,0x00,0xb5,
0xf9,0xff,0x00,0xb5,0xf9,0xff,0x00,0xb5,0xf9,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,
0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0x00,0xd2,0xc9,0xff,0x00,0xd2,0xc9,0xff,0x00,0xd2,0xc9,0xff,0x00,0xd2,0xc9,0xff,0x00,0xb5,
0xf9,0xff,0x00,0xb5,0xf9,0xff,0x00,0xb5,0xf9,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,
0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0x00,0xd2,0xc9,0xff,0x00,0xd2,0xc9,0xff,0x00,0xd2,0xc9,0xff,0x00,0xd2,0xc9,0xff,0x00,0xb5,
0xf9,0xff,0x00,0xb5,0xf9,0xff,0x00,0xb5,0xf9,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,
0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0x00,0xd2,0xc9,0xff,0x00,0xd2,0xc9,0xff,0x00,0xd2,0xc9,0xff,0x00,0xd2,0xc9,0xff,0x00,0xb5,
0xf9,0xff,0x00,0xb5,0xf9,0xff,0x00,0xb5,0xf9,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,
0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0x00,0xd2,0xc9,0xff,0x00,0xd2,0xc9,0xff,0x00,0xd2,0xc9,0xff,0x00,0xd2,0xc9,0xff,0x00,0xb5,
0xf9,0xff,0x00,0xb5,0xf9,0xff,0x00,0xb5,0xf9,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,
0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0x00,0xd2,0xc9,0xff,0x00,0xd2,0xc9,0xff,0x00,0xd2,0xc9,0xff,0x00,0xd2,0xc9,0xff,0x00,0xb5,
0xf9,0xff,0x00,0xb5,0xf9,0xff,0x00,0xb5,0xf9,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,
0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0x00,0xd2,0xc9,0xff,0x00,0xd2,0xc9,0xff,0x00,0xd2,0xc9,0xff,0x00,0xd2,0xc9,0xff,0x00,0xb5,
0xf9,0xff,0x00,0xb5,0xf9,0xff,0x00,0xb5,0xf9,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,
0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0x00,0xd2,0xc9,0xff,0x00,0xd2,0xc9,0xff,0x00,0xd2,0xc9,0xff,0x00,0xd2,0xc9,0xff,0x00,0xb5,
0xf9,0xff,0x00,0xb5,0xf9,0xff,0x00,0xb5,0xf9,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,
0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0x00,0xd2,0xc9,0xff,0x00,0xd2,0xc9,0xff,0x00,0xd2,0xc9,0xff,0x00,0xd2,0xc9,0xff,0x00,0xb5,
0xf9,0xff,0x00,0xb5,0xf9,0xff,0x00,0xb5,0xf9,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,
0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0x00,0xd2,0xc9,0xff,0x00,0xd2,0xc9,0xff,0x00,0xd2,0xc9,0xff,0x00,0xd2,0xc9,0xff,0x00,0xb5,
0xf9,0xff,0x00,0xb5,0xf9,0xff,0x00,0xb5,0xf9,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,
0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0x00,0xd2,0xc9,0xff,0x00,0xd2,0xc9,0xff,0x00,0xd2,0xc9,0xff,0x00,0xd2,0xc9,0xff,0x00,0xb5,
0xf9,0xff,0x00,0xb5,0xf9,0xff,0x00,0xb5,0xf9,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,
0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0x00,0xd2,0xc9,0xff,0x00,0xd2,0xc9,0xff,0x00,0xd2,0xc9,0xff,0x00,0xd2,0xc9,0xff,0x00,0xb5,
0xf9,0xff,0x00,0xb5,0xf9,0xff,0x00,0xb5,0xf9,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,
0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0x00,0xd2,0xc9,0xff,0x00,0xd2,0xc9,0xff,0x00,0xd2,0xc9,0xff,0x00,0xd2,0xc9,0xff,0x00,0xb5,
0xf9,0xff,0x00,0xb5,0xf9,0xff,0x00,0xb5,0xf9,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,
0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0xdb,0xb1,0x7b,0xff,0x00,0xd2,0xc9,0xff,0x00,0xd2,0xc9,0xff,0x00,0xd2,0xc9,0xff,0x00,0xd2,0xc9,0xff,0x00,0x00,
0x3a,0x00,0x00,0x00,0x3a,0x00,0x00,0x00,0x49,0xf1,0x00,0x00,0xe9,0xeb,0x00,0x00,0xdb,0x3c,0x00,0x00,0x3e,0x99,0x00,0x00,0x0d,0x1c,0x00,0x00,0x47,0xde,0x00,0x00,
0x4d,0xc8,0x00,0x00,0x8b,0xa6,0x00,0x00,0x5a,0x7d,0x00,0x00,0x25,0x1f,0x00,0x00,0xcb,0xfc,0x00,0x00,0x45,0x3b,0x00,0x00,0x89,0x0a,0x00,0x00,0xae,0x32,
};
    #elif defined _LM3SXXXX                                              // Luminary Mico favicon
        #define _favicon Luminary_favicon
static const unsigned char Luminary_favicon[] = {
0x00,0x00,0x01,0x00,0x01,0x00,0x10,0x10,0x00,0x00,0x01,0x00,0x20,0x00,0x68,0x04,0x00,0x00,0x16,0x00,0x00,0x00,0x28,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x20,0x00,
0x00,0x00,0x01,0x00,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x13,0x0b,0x00,0x00,0x13,0x0b,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xd7,0xdb,0xdd,0xff,0x91,0x9c,0xa2,0xff,0x5f,0x6f,0x77,0xff,0x5f,0x6f,0x77,0xff,0x5f,0x6f,
0x77,0xff,0x5f,0x6f,0x77,0xff,0x5f,0x6f,0x77,0xff,0x5f,0x6f,0x77,0xff,0x5f,0x6f,0x77,0xff,0x5f,0x6f,0x77,0xff,0x91,0x9c,0xa2,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xa5,0xae,0xb3,0xff,0x5f,0x6f,0x77,0xff,0x5f,0x6f,0x77,0xff,0x5f,0x6f,0x77,0xff,0x5f,0x6f,0x77,0xff,0x5f,0x6f,
0x77,0xff,0x5f,0x6f,0x77,0xff,0x5f,0x6f,0x77,0xff,0x5f,0x6f,0x77,0xff,0x5f,0x6f,0x77,0xff,0x5f,0x6f,0x77,0xff,0x5f,0x6f,0x77,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xa5,0xae,0xb3,0xff,0x5f,0x6f,0x77,0xff,0x5f,0x6f,0x77,0xff,0x87,0x93,0x99,0xff,0xd7,0xdb,0xdd,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x5f,0x6f,0x77,0xff,0x5f,0x6f,0x77,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xd7,0xdb,0xdd,0xff,0x5f,0x6f,0x77,0xff,0x5f,0x6f,0x77,0xff,0xaf,0xb7,0xbb,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xeb,0xed,
0xee,0xff,0xaf,0xb7,0xbb,0xff,0xc3,0xc9,0xcc,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x5f,0x6f,0x77,0xff,0x5f,0x6f,0x77,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0x91,0x9c,0xa2,0xff,0x5f,0x6f,0x77,0xff,0x87,0x93,0x99,0xff,0xff,0xff,0xff,0xff,0xe1,0xe4,0xe5,0xff,0x91,0x9c,0xa2,0xff,0xff,0xff,0xff,0xff,0xd7,0xdb,
0xdd,0xff,0x5f,0x6f,0x77,0xff,0x87,0x93,0x99,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x5f,0x6f,0x77,0xff,0x5f,0x6f,0x77,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0x5f,0x6f,0x77,0xff,0x5f,0x6f,0x77,0xff,0xd7,0xdb,0xdd,0xff,0xff,0xff,0xff,0xff,0x7d,0x8a,0x91,0xff,0x87,0x93,0x99,0xff,0xff,0xff,0xff,0xff,0xd7,0xdb,
0xdd,0xff,0x5f,0x6f,0x77,0xff,0x87,0x93,0x99,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x5f,0x6f,0x77,0xff,0x5f,0x6f,0x77,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0x5f,0x6f,0x77,0xff,0x5f,0x6f,0x77,0xff,0xff,0xff,0xff,0xff,0xe1,0xe4,0xe5,0xff,0x5f,0x6f,0x77,0xff,0x87,0x93,0x99,0xff,0xff,0xff,0xff,0xff,0xd7,0xdb,
0xdd,0xff,0x5f,0x6f,0x77,0xff,0x87,0x93,0x99,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x5f,0x6f,0x77,0xff,0x5f,0x6f,0x77,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0x5f,0x6f,0x77,0xff,0x5f,0x6f,0x77,0xff,0xff,0xff,0xff,0xff,0xd7,0xdb,0xdd,0xff,0x5f,0x6f,0x77,0xff,0x87,0x93,0x99,0xff,0xff,0xff,0xff,0xff,0xd7,0xdb,
0xdd,0xff,0x5f,0x6f,0x77,0xff,0x87,0x93,0x99,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x5f,0x6f,0x77,0xff,0x5f,0x6f,0x77,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0x5f,0x6f,0x77,0xff,0x5f,0x6f,0x77,0xff,0xff,0xff,0xff,0xff,0xd7,0xdb,0xdd,0xff,0x5f,0x6f,0x77,0xff,0x87,0x93,0x99,0xff,0xff,0xff,0xff,0xff,0xd7,0xdb,
0xdd,0xff,0x5f,0x6f,0x77,0xff,0x87,0x93,0x99,0xff,0xff,0xff,0xff,0xff,0xcd,0xd2,0xd4,0xff,0x5f,0x6f,0x77,0xff,0x5f,0x6f,0x77,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0x5f,0x6f,0x77,0xff,0x5f,0x6f,0x77,0xff,0xff,0xff,0xff,0xff,0xd7,0xdb,0xdd,0xff,0x5f,0x6f,0x77,0xff,0x87,0x93,0x99,0xff,0xff,0xff,0xff,0xff,0xd7,0xdb,
0xdd,0xff,0x5f,0x6f,0x77,0xff,0x87,0x93,0x99,0xff,0xff,0xff,0xff,0xff,0x87,0x93,0x99,0xff,0x5f,0x6f,0x77,0xff,0x91,0x9c,0xa2,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0x5f,0x6f,0x77,0xff,0x5f,0x6f,0x77,0xff,0xff,0xff,0xff,0xff,0xd7,0xdb,0xdd,0xff,0x5f,0x6f,0x77,0xff,0x87,0x93,0x99,0xff,0xff,0xff,0xff,0xff,0xd7,0xdb,
0xdd,0xff,0x5f,0x6f,0x77,0xff,0x87,0x93,0x99,0xff,0x9b,0xa5,0xaa,0xff,0x5f,0x6f,0x77,0xff,0x5f,0x6f,0x77,0xff,0xd7,0xdb,0xdd,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0x5f,0x6f,0x77,0xff,0x5f,0x6f,0x77,0xff,0xff,0xff,0xff,0xff,0xd7,0xdb,0xdd,0xff,0x5f,0x6f,0x77,0xff,0x87,0x93,0x99,0xff,0xff,0xff,0xff,0xff,0xd7,0xdb,
0xdd,0xff,0x5f,0x6f,0x77,0xff,0x87,0x93,0x99,0xff,0x5f,0x6f,0x77,0xff,0x5f,0x6f,0x77,0xff,0xaf,0xb7,0xbb,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0x5f,0x6f,0x77,0xff,0x5f,0x6f,0x77,0xff,0xff,0xff,0xff,0xff,0xd7,0xdb,0xdd,0xff,0x5f,0x6f,0x77,0xff,0x5f,0x6f,0x77,0xff,0x5f,0x6f,0x77,0xff,0x5f,0x6f,
0x77,0xff,0x5f,0x6f,0x77,0xff,0x5f,0x6f,0x77,0xff,0x5f,0x6f,0x77,0xff,0xaf,0xb7,0xbb,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0x5f,0x6f,0x77,0xff,0x5f,0x6f,0x77,0xff,0xff,0xff,0xff,0xff,0xd7,0xdb,0xdd,0xff,0x91,0x9c,0xa2,0xff,0x5f,0x6f,0x77,0xff,0x5f,0x6f,0x77,0xff,0x5f,0x6f,
0x77,0xff,0x69,0x78,0x80,0xff,0x9b,0xa5,0xaa,0xff,0xe1,0xe4,0xe5,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};
    #elif defined _STR91XF || defined _STM32                             // ST Micro favicon
        #define _favicon ST_favicon
static const unsigned char ST_favicon[] = {
0x00,0x00,0x01,0x00,0x01,0x00,0x10,0x10,0x10,0x00,0x00,0x00,0x00,0x00,0x28,0x01,0x00,0x00,0x16,0x00,0x00,0x00,0x28,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x20,0x00,
0x00,0x00,0x01,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xff,0xff,
0xff,0x00,0xff,0xff,0xff,0x00,0xff,0xef,0xe7,0x00,0xff,0xde,0xc6,0x00,0xff,0xd6,0xb5,0x00,0xff,0xce,0xa5,0x00,0xff,0xc6,0x8c,0x00,0xff,0xbd,0x84,0x00,0xff,0xb5,
0x73,0x00,0xff,0xb5,0x6b,0x00,0xff,0xad,0x63,0x00,0xff,0x9c,0x42,0x00,0xff,0x94,0x31,0x00,0xff,0x8c,0x21,0x00,0xff,0x7b,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x43,0x06,0x60,0x00,0x00,0x00,0x00,
0x00,0x07,0x06,0xea,0x00,0x00,0x0c,0xdd,0xdb,0x04,0x20,0xde,0x00,0x00,0x04,0xed,0xd4,0x08,0x90,0xae,0x60,0x00,0x00,0xcd,0x40,0x3d,0xd0,0x3d,0xd0,0x00,0x00,0x58,
0x05,0xde,0xe5,0x0c,0xd4,0x00,0x00,0x04,0x05,0x87,0x75,0x03,0x84,0x00,0x00,0x05,0x50,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0xee,0xed,0xde,0xee,0xdd,0x80,0x00,0x00,
0x5e,0xee,0xee,0xee,0xee,0xe5,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
};
    #endif
#endif

#if defined SPECIAL_LCD_DEMO || defined SUPPORT_GLCD || defined SUPPORT_OLED// {2}
    #define LCD_WEB_INTERFACE                                            // allow posting an image to the display and displaying the image in the LCD on a web page
#endif

//static const CHAR ajax1[]      = "<Dummy>�vX4</Dummy>";                // example of file used for ajax interpetation
//static const CHAR link_page[]  = "This is another embedded page - <a href=""0.htm"">Go to main start page</a>";
//static const CHAR start_page[] = "<html><head><title>uTasker Test</title></head><body>This is a start test page embedded in the code<br><a href=""0.htm"">Go to main start page</a><br><a href=""link.htm"">Test another embedded page</a></body></html>";
static const CHAR gen_binary[]   = "�H10";                               // command generation of large binary content
#if defined LCD_WEB_INTERFACE                                            // {1}{2}
    static const CHAR gen_bmp[]  = "�H20";                               // command to generate a BMP from the present LCD display content
#endif

static const USER_FILE user_files[] = {
  //{"link.htm", (unsigned char *)link_page, (sizeof(link_page) - 1), MIME_HTML, FILE_VISIBLE},
  //{"0HTTP", (unsigned char *)start_page, (sizeof(start_page) - 1), MIME_HTML, (FILE_VISIBLE | FILE_ADD_EXT)}, // define start on web server contact
  //{"XML?Dummy", (unsigned char *)ajax1, (sizeof(ajax1) - 1), MIME_HTML, FILE_INVISIBLE},

    {"flash.bin", (unsigned char *)(FLASH_START_ADDRESS + 1), (SIZE_OF_FLASH - 1), MIME_BINARY, (FILE_VISIBLE | FILE_NOT_CODE)},
#if defined SPI_SW_UPLOAD || defined SPI_FLASH_FAT || (defined SPI_FILE_SYSTEM && defined FLASH_FILE_SYSTEM)
    {"spi_flash.bin", (unsigned char *)(FLASH_START_ADDRESS + SIZE_OF_FLASH), (SPI_DATA_FLASH_SIZE), MIME_BINARY, (FILE_VISIBLE | FILE_NOT_CODE)},
#endif
    {"ram.bin",   (unsigned char *)RAM_START_ADDRESS, (SIZE_OF_RAM), MIME_BINARY, (FILE_VISIBLE | FILE_NOT_CODE)},

    {"favicon.ico", (unsigned char *)_favicon, sizeof(_favicon), MIME_ICON, FILE_VISIBLE},
    {"9Generate.bin", (unsigned char *)gen_binary, (sizeof(gen_binary) - 1), MIME_HTML, FILE_INVISIBLE},
#if defined LCD_WEB_INTERFACE                                            // {1}{2}
    {"LCD.BMP", (unsigned char *)gen_bmp, sizeof(gen_bmp), MIME_HTML, FILE_INVISIBLE},
#endif
    {0}                                                                  // end of list
};

