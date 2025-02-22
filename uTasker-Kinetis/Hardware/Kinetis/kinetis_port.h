/***********************************************************************
    Mark Butcher    Bsc (Hons) MPhil MIET

    M.J.Butcher Consulting
    Birchstrasse 20f,    CH-5406, R�tihof
    Switzerland

    www.uTasker.com    Skype: M_J_Butcher

    ---------------------------------------------------------------------
    File:      kinetis_port.h (k60)
    Project:   Single Chip Embedded Internet
    ---------------------------------------------------------------------
    Copyright (C) M.J.Butcher Consulting 2004..2016
    *********************************************************************
    27.10.2012 Reworked with new style and dedicated port strings, 121 pin completed
    21.04.2012 Added new K60 pin functions                               {1}

*/

#if PIN_COUNT == PIN_COUNT_100_PIN                                       // 100 LQFP
    #define _PIN_COUNT              0
#elif PIN_COUNT == PIN_COUNT_121_PIN                                     // 121 MAPBGA
    #define _PIN_COUNT              1
#elif PIN_COUNT == PIN_COUNT_144_PIN
    #if PACKAGE_TYPE != PACKAGE_MAPBGA
        #define _PIN_COUNT          2                                    // 144 LQFP
    #else
        #define _PIN_COUNT          3                                    // 144 MAPBGA
    #endif
#else
    #error "Package not clearly defined!!"
#endif

#define ALTERNATIVE_FUNCTIONS   7                                        // GPIO plus 5 possible peripheral/extra/system functions

static const char *cPinNumber[PORTS_AVAILABLE + 1][PORT_WIDTH][4] = {
    {
        //  100LQFP   MAPBGA121  144LQFP   MAPBGA144                     GPIO A
        {  "34",      "J6",      "50",     "J5", },                      // PA0
        {  "35",      "H8",      "51",     "J6", },                      // PA1
        {  "36",      "J7",      "52",     "K6", },                      // PA2
        {  "37",      "H9",      "53",     "K7", },                      // PA3
    #if defined KINETIS_K64
        {  "38",      "J8",      "54",     "L7", },                      // PA4
        {  "39",      "K7",      "55",     "M8", },                      // PA5
    #else
        {  "-",       "J8",      "54",     "L7", },                      // PA4
        {  "-",       "K7",      "55",     "M8", },                      // PA5
    #endif
        {  "-",       "-",       "58",     "J7", },                      // PA6
        {  "-",       "-",       "59",     "J8", },                      // PA7
        {  "-",       "-",       "60",     "K8", },                      // PA8
        {  "-",       "-",       "61",     "L8", },                      // PA9
        {  "-",       "J9",      "62",     "M9", },                      // PA10
        {  "-",       "J4",      "63",     "L9", },                      // PA11
        {  "42",      "K8",      "64",     "K9", },                      // PA12
        {  "43",      "L8",      "65",     "J9", },                      // PA13
        {  "44",      "K9",      "66",     "L10",},                      // PA14
        {  "45",      "L9",      "67",     "L11",},                      // PA15
        {  "46",      "J10",     "68",     "K10",},                      // PA16
        {  "47",      "H10",     "69",     "K11",},                      // PA17
        {  "50",      "L11",     "72",     "M12",},                      // PA18
        {  "51",      "K11",     "73",     "M11",},                      // PA19
        {  "-",       "-",       "-",      "-",  },                      // PA20
        {  "-",       "-",       "-",      "-",  },                      // PA21
        {  "-",       "-",       "-",      "-",  },                      // PA22
        {  "-",       "-",       "-",      "-",  },                      // PA23
        {  "-",       "-",       "75",     "K12",},                      // PA24
        {  "-",       "-",       "76",     "J12",},                      // PA25
        {  "-",       "-",       "77",     "J11",},                      // PA26
        {  "-",       "-",       "78",     "J10",},                      // PA27
        {  "-",       "-",       "79",     "H12",},                      // PA28
        {  "-",       "H11",     "80",     "H11",},                      // PA29
        {  "-",       "-",       "-",      "-",  },                      // PA30
        {  "-",       "-",       "-",      "-",  },                      // PA31
    },
    {
        //  100LQFP   MAPBGA121  144LQFP   MAPBGA144                     GPIO B
        {  "53",      "G11",     "81",     "H10",},                      // PB0
        {  "54",      "G10",     "82",     "H9", },                      // PB1
        {  "55",      "G9",      "83",     "G12",},                      // PB2
        {  "56",      "G8",      "84",     "G11",},                      // PB3
        {  "-",       "-",       "85",     "G10",},                      // PB4
        {  "-",       "-",       "86",     "G9", },                      // PB5
        {  "-",       "F11",     "87",     "F12",},                      // PB6
        {  "-",       "E11",     "88",     "F11",},                      // PB7
        {  "-",       "D11",     "89",     "F10",},                      // PB8
        {  "57",      "E10",     "90",     "F9", },                      // PB9
        {  "58",      "D10",     "91",     "E12",},                      // PB10
        {  "59",      "C10",     "92",     "E11",},                      // PB11
    #if defined KINETIS_K64
        {  "-",       "B11",     "-",      "-",  },                      // PB12
        {  "-",       "C11",     "-",      "-",  },                      // PB13
    #else
        {  "-",       "-",       "-",      "-",  },                      // PB12
        {  "-",       "-",       "-",      "-",  },                      // PB13
    #endif
        {  "-",       "-",       "-",      "-",  },                      // PB14
        {  "-",       "-",       "-",      "-",  },                      // PB15
        {  "62",      "B10",     "95",     "E10",},                      // PB16
        {  "63",      "E9",      "96",     "E9", },                      // PB17
        {  "64",      "D9",      "97",     "D12",},                      // PB18
        {  "65",      "C9",      "98",     "D11",},                      // PB19
        {  "66",      "F10",     "99",     "D10",},                      // PB20
        {  "67",      "F9",      "100",    "D9", },                      // PB21
        {  "68",      "F8",      "101",    "C12",},                      // PB22
        {  "69",      "E8",      "102",    "C11",},                      // PB23
        {  "-",       "-",       "-",      "-",  },                      // PB24
        {  "-",       "-",       "-",      "-",  },                      // PB25
        {  "-",       "-",       "-",      "-",  },                      // PB26
        {  "-",       "-",       "-",      "-",  },                      // PB27
        {  "-",       "-",       "-",      "-",  },                      // PB28
        {  "-",       "-",       "-",      "-",  },                      // PB29
        {  "-",       "-",       "-",      "-",  },                      // PB30
        {  "-",       "-",       "-",      "-",  },                      // PB31
    },
    {
        //  100LQFP   MAPBGA121  144LQFP   MAPBGA144                     GPIO C
        {  "70",      "B9",      "103",    "B12",},                      // PC0
        {  "71",      "D8",      "104",    "B11",},                      // PC1
        {  "72",      "C8",      "105",    "A12",},                      // PC2
        {  "73",      "B8",      "106",    "A11",},                      // PC3
        {  "76",      "A8",      "109",    "A9", },                      // PC4
        {  "77",      "D7",      "110",    "D8", },                      // PC5
        {  "78",      "C7",      "111",    "C8", },                      // PC6
        {  "79",      "B7",      "112",    "B8", },                      // PC7
        {  "80",      "A7",      "113",    "A8", },                      // PC8
        {  "81",      "D6",      "114",    "D7", },                      // PC9
        {  "82",      "C6",      "115",    "C7", },                      // PC10
        {  "83",      "C5",      "116",    "B7", },                      // PC11
        {  "84",      "B6",      "117",    "A7", },                      // PC12
        {  "85",      "A6",      "118",    "D6", },                      // PC13
        {  "86",      "A5",      "119",    "C6", },                      // PC14
        {  "87",      "B5",      "120",    "B6", },                      // PC15
        {  "90",      "D5",      "123",    "A6", },                      // PC16
        {  "91",      "C4",      "124",    "D5", },                      // PC17
        {  "92",      "B4",      "125",    "C5", },                      // PC18
        {  "-",       "A4",      "126",    "B5", },                      // PC19
        {  "-",       "-",       "-",      "-",  },                      // PC20
        {  "-",       "-",       "-",      "-",  },                      // PC21
        {  "-",       "-",       "-",      "-",  },                      // PC22
        {  "-",       "-",       "-",      "-",  },                      // PC23
        {  "-",       "-",       "-",      "-",  },                      // PC24
        {  "-",       "-",       "-",      "-",  },                      // PC25
        {  "-",       "-",       "-",      "-",  },                      // PC26
        {  "-",       "-",       "-",      "-",  },                      // PC27
        {  "-",       "-",       "-",      "-",  },                      // PC28
        {  "-",       "-",       "-",      "-",  },                      // PC29
        {  "-",       "-",       "-",      "-",  },                      // PC30
        {  "-",       "-",       "-",      "-",  },                      // PC31
    },
    {
        //  100LQFP   MAPBGA121  144LQFP   MAPBGA144                     GPIO D
        {  "93",      "D4",      "127",    "A5", },                      // PD0
        {  "94",      "D3",      "128",    "D4", },                      // PD1
        {  "95",      "C3",      "129",    "C4", },                      // PD2
        {  "96",      "B3",      "130",    "B4", },                      // PD3
        {  "97",      "A3",      "131",    "A4", },                      // PD4
        {  "98",      "A2",      "132",    "A3", },                      // PD5
        {  "99",      "B2",      "133",    "A2", },                      // PD6
        {  "100",     "A1",      "136",    "A1", },                      // PD7
        {  "-",       "A10",     "137",    "C9", },                      // PD8
        {  "-",       "A9",      "138",    "B9", },                      // PD9
        {  "-",       "B1",      "139",    "B3", },                      // PD10
        {  "-",       "C2",      "140",    "B2", },                      // PD11
        {  "-",       "C1",      "141",    "B1", },                      // PD12
        {  "-",       "D2",      "142",    "C3", },                      // PD13
        {  "-",       "D1",      "143",    "C2", },                      // PD14
        {  "-",       "E1",      "144",    "C1", },                      // PD15
        {  "-",       "-",       "-",      "-",  },                      // PD16
        {  "-",       "-",       "-",      "-",  },                      // PD17
        {  "-",       "-",       "-",      "-",  },                      // PD18
        {  "-",       "-",       "-",      "-",  },                      // PD19
        {  "-",       "-",       "-",      "-",  },                      // PD20
        {  "-",       "-",       "-",      "-",  },                      // PD21
        {  "-",       "-",       "-",      "-",  },                      // PD22
        {  "-",       "-",       "-",      "-",  },                      // PD23
        {  "-",       "-",       "-",      "-",  },                      // PD24
        {  "-",       "-",       "-",      "-",  },                      // PD25
        {  "-",       "-",       "-",      "-",  },                      // PD26
        {  "-",       "-",       "-",      "-",  },                      // PD27
        {  "-",       "-",       "-",      "-",  },                      // PD28
        {  "-",       "-",       "-",      "-",  },                      // PD29
        {  "-",       "-",       "-",      "-",  },                      // PD30
        {  "-",       "-",       "-",      "-",  },                      // PD31
    },
    {
        //  100LQFP   MAPBGA121  144LQFP   MAPBGA144                     GPIO E
        {  "1",       "E4",      "1",      "D3", },                      // PE0
        {  "2",       "E3",      "2",      "D2", },                      // PE1
        {  "3",       "E2",      "3",      "D1", },                      // PE2
        {  "4",       "F4",      "4",      "E4", },                      // PE3
        {  "5",       "H7",      "7",      "E3", },                      // PE4
        {  "6",       "G4",      "8",      "E2", },                      // PE5
        {  "7",       "F3",      "9",      "E1", },                      // PE6
        {  "-",       "-",       "10",     "F4", },                      // PE7
        {  "-",       "-",       "11",     "F3", },                      // PE8
        {  "-",       "-",       "12",     "F2", },                      // PE9
        {  "-",       "-",       "13",     "F1", },                      // PE10
        {  "-",       "-",       "14",     "G4", },                      // PE11
        {  "-",       "-",       "15",     "G3", },                      // PE12
        {  "-",       "-",       "-",      "-",  },                      // PE13
        {  "-",       "-",       "-",      "-",  },                      // PE14
        {  "-",       "-",       "-",      "-",  },                      // PE15
        {  "-",       "-",       "-",      "-",  },                      // PE16
        {  "-",       "-",       "-",      "-",  },                      // PE17
        {  "-",       "-",       "-",      "-",  },                      // PE18
        {  "-",       "-",       "-",      "-",  },                      // PE19
        {  "-",       "-",       "-",      "-",  },                      // PE20
        {  "-",       "-",       "-",      "-",  },                      // PE21
        {  "-",       "-",       "-",      "-",  },                      // PE22
        {  "-",       "-",       "-",      "-",  },                      // PE23
        {  "31",      "H5",      "45",     "M4", },                      // PE24
        {  "32",      "J5",      "46",     "K5", },                      // PE25
        {  "33",      "H6",      "47",     "K4", },                      // PE26
        {  "-",       "-",       "48",     "J4", },                      // PE27
        {  "-",       "-",       "49",     "H4", },                      // PE28
        {  "-",       "-",       "-",      "-",  },                      // PE29
        {  "-",       "-",       "-",      "-",  },                      // PE30
        {  "-",       "-",       "-",      "-",  },                      // PE31
    },
    { 
        //  100LQFP   MAPBGA121  144LQFP   MAPBGA144                     dedicated ADC pins
#if defined KINETIS_K64
        {  "-",       "L7",      "-",      "L5", },                      // RTC_WAKEUP_B
        {  "10",      "F1",      "19",     "H1", },                      // USB0_DP
        {  "11",      "F2",      "20",     "H2", },                      // USB0_DM
        {  "12",      "G1",      "21",     "G1", },                      // VOUT33
        {  "13",      "G2",      "22",     "G2", },                      // VREGIN
        {  "14",      "H1",      "23",     "J1", },                      // ADC0_DP1
        {  "15",      "H2",      "24",     "J2", },                      // ADC0_DM1
        {  "16",      "J1",      "25",     "K1", },                      // ADC1_DP1
        {  "17",      "J2",      "26",     "K2", },                      // ADC1_DM1
        {  "18",      "K1",      "27",     "L1", },                      // ADC0_DP0/ADC1_DP3
        {  "19",      "K2",      "28",     "L2", },                      // ADC0_DM0/ADC1_DM3
        {  "20",      "L1",      "29",     "M1", },                      // ADC1_DP0/ADC0_DP3
        {  "21",      "L2",      "30",     "M2", },                      // ADC1_DM0/ADC0_DM3
        {  "22",      "F5",      "31",     "H5", },                      // VDAA
        {  "23",      "G5",      "32",     "G5", },                      // VREFH
        {  "24",      "G6",      "33",     "G6", },                      // VREFL
        {  "25",      "F6",      "34",     "H6", },                      // VSSA
        {  "-",       "J3",      "35",     "K3", },                      // ADC1_SE16/CMP2_IN2/ADC0_SE22
        {  "-",       "H3",      "36",     "J3", },                      // ADC0_SE16/CMP1_IN2/ADC0_SE21
        {  "26",      "L3",      "37",     "M3", },                      // VREF_OUT/CMP1_IN5/CMP0_IN5/ADC1_SE18
        {  "27",      "K5",      "38",     "L3", },                      // DAC0_OUT/CMP1_IN3/ADC0_SE23
        {  "-",       "K4",      "39",     "L4", },                      // DAC1_OUT/CMP0_IN4/CMP2_IN3/ADC1_SE23
        {  "28",      "L4",      "40",     "M7", },                      // XTAL32
        {  "92",      "L5",      "41",     "M6", },                      // EXTAL32
        {  "30",      "K6",      "42",     "L6", },                      // VBAT
        {  "-",       "-",       "-",      "-",  },
        {  "-",       "-",       "-",      "-",  },
        {  "-",       "-",       "-",      "-",  },
        {  "-",       "-",       "-",      "-",  },
        {  "-",       "-",       "-",      "-",  },
        {  "-",       "-",       "-",      "-",  },
        {  "-",       "-",       "-",      "-",  },
#else
        {  "14",      "H1",      "23",     "J1", },                      // ADC0_DP1
        {  "15",      "H2",      "24",     "J2", },                      // ADC0_DM1
        {  "16",      "J1",      "25",     "K1", },                      // ADC1_DP1
        {  "17",      "J2",      "26",     "K2", },                      // ADC1_DM1
        {  "18",      "K1",      "27",     "L1", },                      // PGA0_DP / ADC0_SP0 / ADC1_DP3
        {  "19",      "K2",      "28",     "L2", },                      // PGA0_DM / ADC0_DM0 / ADC1_DM3
        {  "20",      "L1",      "29",     "M1", },                      // PGA1_DP / ADC1_DP0 / ADC0_DP3
        {  "21",      "L2",      "30",     "M2", },                      // PGA1_DM / ADC1_DM0 / ADC0_DM3
        {  "-",       "J3",      "35",     "K3", },                      // ADC1_SE16 / CMP2_IN2 / ADC0_SE22
        {  "-",       "H3",      "36",     "J3", },                      // ADC0_SE16 / CMP1_IN2 / ADC0_SE21
        {  "26",      "L3",      "37",     "M3", },                      // VREF_OUT / CMP1_IN5 / CMP0_IN5 / ADC1_SE18
        {  "27",      "K5",      "38",     "L3", },                      // DAC0_OUT / CMP1_IN3 / ADC0_SE23
        {  "-",       "K4",      "39",     "L4", },                      // DAC1_OUT / CMP2_IN3 / ADC1_SE23
        {  "28",      "L4",      "40",     "M7", },                      // XTAL32
        {  "92",      "L5",      "41",     "M6", },                      // EXTAL32
        {  "10",      "F1",      "19",     "H1", },                      // USB0_DP
        {  "11",      "F2",      "20",     "H2", },                      // USB0_DM
        {  "12",      "G1",      "21",     "G1", },                      // VOUT33
        {  "13",      "G2",      "22",     "G2", },                      // VREGIN
        {  "-",       "-",       "-",      "-",  },
        {  "-",       "-",       "-",      "-",  },
        {  "-",       "-",       "-",      "-",  },
        {  "-",       "-",       "-",      "-",  },
        {  "-",       "-",       "-",      "-",  },
        {  "-",       "-",       "-",      "-",  },
        {  "-",       "-",       "-",      "-",  },
        {  "-",       "-",       "-",      "-",  },
        {  "-",       "-",       "-",      "-",  },
        {  "-",       "-",       "-",      "-",  },
        {  "-",       "-",       "-",      "-",  },
        {  "-",       "-",       "-",      "-",  },
        {  "-",       "-",       "-",      "-",  },
#endif
    }
};

#define _DEDICATED_PINS
static CHAR *cDedicated[PORT_WIDTH] = {                                  // dedicated pin functions
#if defined KINETIS_K64
    "RTC_WAKEUP_B",
    "USB0_DP",
    "USB0_DM",
    "VOUT33",
    "VREGIN",
    "ADC0_DP1",
    "ADC0_DM1",
    "ADC1_DP1",
    "ADC1_DM1"
    "ADC0_DP0/ADC1_DP3",
    "ADC0_DM0/ADC1_DM3",
    "ADC1_DP0/ADC0_DP3",
    "ADC1_DM0/ADC0_DM3",
    "VDAA",
    "VREFH",
    "VREFL",
    "VSSA",
    "ADC1_SE16/CMP2_IN2/ADC0_SE22",
    "ADC0_SE16/CMP1_IN2/ADC0_SE21",
    "VREF_OUT/CMP1_IN5/CMP0_IN5/ADC1_SE18",
    "DAC0_OUT/CMP1_IN3/ADC0_SE23",
    "DAC1_OUT/CMP0_IN4/CMP2_IN3/ADC1_SE23",
    "XTAL32",
    "EXTAL32",
    "VBAT",
#else
    "ADC0_DP1",
    "ADC0_DM1",
    "ADC1_DP1",
    "ADC1_DM1",
    "PGA0_DP/ADC0_SP0/ADC1_DP3",
    "PGA0_DM/ADC0_DM0/ADC1_DM3",
    "PGA1_DP/ADC1_DP0/ADC0_DP3",
    "PGA1_DM/ADC1_DM0/ADC0_DM3",
    "ADC1_SE16/CMP2_IN2/ADC0_SE22",
    "ADC0_SE16/CMP1_IN2/ADC0_SE21",
    "VREF_OUT/CMP1_IN5/CMP0_IN5/ADC1_SE18",
    "DAC0_OUT/CMP1_IN3/ADC0_SE23",
    "DAC1_OUT/CMP2_IN3/ADC1_SE23",
    "XTAL32",
    "EXTAL32",
    "USB0_DP",
    "USB0_DM",
    "VOUT33",
    "VREGIN"
#endif
};

// Table not yet complete
//
static int ADC_DEDICATED_CHANNEL[PORT_WIDTH] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, ADC_SE16_SINGLE, 0, 0, 0, 0, ADC_DM1_SINGLE, ADC_DP1_SINGLE, ADC_DM1_SINGLE, ADC_DP1_SINGLE};
static int ADC_DEDICATED_MODULE[PORT_WIDTH]  = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 2, 2, 1, 1}; // ADC0 is named 1, ADC1 is named 2 etc.
static int ADC_MUX_CHANNEL[PORTS_AVAILABLE][PORT_WIDTH] = {0};           // not yet controlled


#if _PIN_COUNT == 0
static const char *cPer[PORTS_AVAILABLE][PORT_WIDTH][8] = {              // 100 pin LQFP
    {
        // ALT 0           ALT 1    ALT2         ALT 3         ALT 4          ALT 5        ALT 6       ALT 7
    #if defined KINETIS_K64
        {  "-",            "PTA0",  "UART0_CTS_b/UART0_COL_b","FTM0_CH5","-", "-",         "-",        "JTAG_TCLK/SWD_CLK" }, // PORT A
        {  "-",            "PTA1",  "UART0_RX",  "FTM0_CH6",   "-",           "-",         "-",        "JTAG_TDI"          },
        {  "-",            "PTA2",  "UART0_TX",  "FTM0_CH7",   "-",           "-",         "-",        "JTAG_TDO/TRACE_SWO"},
        {  "-",            "PTA3",  "UART0_RTS", "FTM0_CH0",   "-",           "-",         "-",        "JTAG_TMS/SWD_DIO"  },
        {  "-",            "PTA4/LLWU_P3","-",   "FTM0_CH1",   "-",           "-",         "-",        "NMIb"              },
        {  "-",            "PTA5",  "USB_CLKIN", "FTM0_CH2",   "MII_RXER",    "CMP2_OUT",  "I2S0_TX_BCLK","JTAG_TRST_b"    },
    #else
        {  "TSI0_CH1",     "PTA0",  "UART0_CTS", "FTM0_CH5",   "-",           "-",         "-",        "JTAG_TCLK/SWD_CLK" }, // PORT A
        {  "TSI0_CH2",     "PTA1",  "UART0_RX",  "FTM0_CH6",   "-",           "-",         "-",        "JTAG_TDI"          },
        {  "TSI0_CH3",     "PTA2",  "UART0_TX",  "FTM0_CH7",   "-",           "-",         "-",        "JTAG_TDO/TRACE_SWO"},
        {  "TSI0_CH4",     "PTA3",  "UART0_RTS", "FTM0_CH0",   "-",           "-",         "-",        "JTAG_TMS/SWD_DIO"  },
        {  "TSI0_CH5",     "PTA4/LLWU_P3","-",   "FTM0_CH1",   "-",           "-",         "-",        "NMIb"              },
        {  "-",            "PTA5",  "USB_CLKIN", "FTM0_CH2",   "MII_RXER",    "CMP2_OUT",  "I2S0_TX_BCLK","JTAG_TRST"      },
    #endif
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
    #if defined KINETIS_K64
        {  "CMP2_IN0",     "PTA12", "CAN0_TX",   "FTM1_CH0",   "MII_RXD1",    "I2C2_SCL",  "I2S0_TXD", "FTM1_QD_PHA"       },
        {  "CMP2_IN1",     "PTA13/LLWU_P4","CAN0_RX","FTM1_CH1","MII_RXD0",   "I2C2_SDA",  "I2S0_TX_FS","FTM1_QD_PHB"      },
        {  "-",            "PTA14", "SPI0_PCS0", "UART0_TX",   "MII_CRS_DV",  "I2C2_SCL",  "I2S0_RX_BCLK","I2S0_TXD1"      },
        {  "-",            "PTA15", "SPI0_SCK",  "UART0_RX",   "MII_TXEN",    "-",         "I2S0_RXD", "-"                 },
        {  "-",            "PTA16", "SPI0_SOUT", "UART0_CTS_b","MII_TXD0",    "-",         "I2S0_RX_FS","I2S0_RXD1"        },
        {  "ADC1_SE17",    "PTA17", "SPI0_SIN",  "UART0_RTS_b","MII_TXD1",    "-",         "I2S0_MCLK","-"                 },
        {  "EXTAL0",       "PTA18", "-",         "FTM0_FLT2",  "FTM_CLKIN0",  "-",         "-",        "-"                 },
        {  "XTAL0",        "PTA19", "-",         "FTM1_FLT0",  "FTM_CLKIN1",  "-",         "LPTMR0_ALT1","-"               },
    #else
        {  "CMP2_IN0",     "PTA12", "CAN0_TX",   "FTM1_CH0",   "MII_RXD1",    "-",         "I2S0_TXD", "FTM1_QD_PHA"       },
        {  "CMP2_IN1",     "PTA13/LLWU_P4","CAN0_RX","FTM1_CH1","MII_RXD0",   "-",         "I2S0_TX_FS","FTM1_QD_PHB"      }, // {1}
        {  "-",            "PTA14", "SPI0_PCS0", "UART0_TX",   "MII_CRS_DV",  "-",         "I2S0_RX_BCLK","-"              },
        {  "-",            "PTA15", "SPI0_SCK",  "UART0_RX",   "MII_TXEN",    "-",         "I2S0_RXD", "-"                 },
        {  "-",            "PTA16", "SPI0_SOUT", "UART0_CTS",  "MII_TXD0",    "-",         "I2S0_RX_FS","I2S0_RXD1"        }, // {1}
        {  "ADC1_SE17",    "PTA17", "SPI0_SIN",  "UART0_RTS",  "MII_TXD1",    "-",         "I2S0_MCLK","-"                 }, // {1}
        {  "EXTAL",        "PTA18", "-",         "FTM0_FLT2",  "FTM_CLKIN0",  "-",         "-",        "-"                 },
        {  "XTAL",         "PTA19", "-",         "FTM1_FLT0",  "FTM_CLKIN1",  "-",         "LPT0_ALT1","-"                 },
    #endif
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 }
    },
    {
        // ALT 0           ALT 1    ALT2         ALT 3         ALT 4          ALT 5        ALT 6       ALT 7
    #if defined KINETIS_K64
        {  "ADC0_SE8/ADC1_SE8","PTB0/LLWU_P5","I2C0_SCL","FTM1_CH0","MII_MDIO","-",        "FTM1_QD_PHA", "-"              }, // PORT B
        {  "ADC0_SE9/ADC1_SE9","PTB1","I2C0_SDA","FTM1_CH1",   "MII_MCD",     "-",         "FTM1_QD_PHB", "-"              },
        {  "ADC0_SE12",   "PTB2","I2C0_SCL","UART0_RTS_b","ENET_1588_TMR0",   "-",         "FTM0_FLT3","-"                 },
        {  "ADC0_SE13",   "PTB3","I2C0_SDA","UART0_CTS_b/UART0_COL_b","ENET_1588_TMR1","-","FTM0_FLT0","-"                 },
    #else
        {  "ADC0_SE8/TSI0_CH1","PTB0/LLWU_P5","I2C0_SCL","FTM1_CH0","MII_MDIO","-",        "FTM1_QD_PHA", "-"              }, // PORT B {1}
        {  "ADC0_SE9/TSI0_CH6","PTB1","I2C0_SDA","FTM1_CH1",   "MII_MCD",     "-",         "FTM1_QD_PHB", "-"              },
        {  "ADC0_SE12/TSI0_CH7","PTB2","I2C0_SCL","UART0_RTS", "ENET_1588_TMR0","-",       "FTM0_FLT3","-"                 },
        {  "ADC0_SE13/TSI0_CH8","PTB3","I2C0_SDA","UART0_CTS", "ENET_1588_TMR1","-",       "FTM0_FLT0","-"                 },
    #endif
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "PTB9",  "SPI1_PCS1", "UART3_CTS_b","-",           "FB_AD20",   "-",        "-"                 },
        {  "ADC1_SE14",    "PTB10", "SPI1_PCS0", "UART3_RX",   "-",           "FB_AD19",   "FTM0_FLT1","-"                 },
        {  "ADC1_SE15",    "PTB11", "SPI1_SCK",  "UART3_TX",   "-",           "FB_AD18",   "FTM0_FLT2","-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
    #if defined KINETIS_K64
        {  "-",            "PTB16", "SPI1_SOUT", "UART0_RX",   "FTM_CLKIN0",  "FB_AD17",   "EWM_IN",   "-"                 },
        {  "-",            "PTB17", "SPI1_SIN",  "UART0_TX",   "FTM_CLKIN1",  "FB_AD16",   "EWM_OUT_b","-"                 },
        {  "-",            "PTB18", "CAN0_TX",   "FTM2_CH0",   "I2S0_TX_BCLK","FB_AD15",   "FTM2_QD_PHA","-"               },
        {  "-",            "PTB19", "CAN0_RX",   "FTM2_CH1",   "I2S0_TX_FS",  "FB_OE",     "FTM2_QD_PHB","-"               },
    #else
        {  "TSI0_CH9",     "PTB16", "SPI1_SOUT", "UART0_RX",   "-",           "FB_AD17",   "EWM_IN",   "-"                 },
        {  "TSI0_CH10",    "PTB17", "SPI1_SIN",  "UART0_TX",   "-",           "FB_AD16",   "EWM_OUT",  "-"                 },
        {  "TSI0_CH11",    "PTB18", "CAN0_TX",   "FTM2_CH0",   "I2S0_TX_BCLK","FB_AD15",   "FTM2_QD_PHA","-"               },
        {  "TSI0_CH12",    "PTB19", "CAN0_RX",   "FTM2_CH1",   "I2S0_TX_FS",  "FB_OE",     "FTM2_QD_PHB","-"               },
    #endif
        {  "-",            "PTB20", "SPI2_PCS0", "-",          "-",           "FB_AD31",   "CMP0_OUT", "-"                 },
        {  "-",            "PTB21", "SPI2_SCK",  "-",          "-",           "FB_AD30",   "CMP1_OUT", "-"                 },
        {  "-",            "PTB22", "SPI2_SOUT", "-",          "-",           "FB_AD29",   "CMP2_OUT", "-"                 },
        {  "-",            "PTB23", "SPI2_SIN",  "SPI0_PCS5",  "-",           "FB_AD28",   "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 }
    },
    {
        // ALT 0           ALT 1    ALT2         ALT 3         ALT 4          ALT 5        ALT 6       ALT 7
    #if defined KINETIS_K64
        {  "ADC0_SE14",    "PTC0",  "SPI0_PCS4","PDB0_EXTRG",  "USB_SOF_OUT", "FB_AD14",   "I2S0_TXD1","-"                 }, // PORT C
        {  "ADC0_SE15",    "PTC1/LLWU_P6","SPI0_PCS3","UART1_RTS_b","FTM0_CH0","FB_AD13",  "I2S0_TXD0","-"                 },
        {  "ADC0_SE4/CMP1_IN0","PTC2","SPI0_PCS2","UART1_CTS_b","FTM0_CH1",   "FB_AD12",   "I2S0_TX_FS","-"                },
        {  "CMP1_IN1",     "PTC3/LLWU_P7","SPI0_PCS1","UART1_RX","FTM0_CH2",  "CLKOUT",    "I2S0_TX_BCLK","-"              },
        {  "-",            "PTC4/LLWU_P8","SPI0_PCS0","UART1_TX","FTM0_CH3",  "FB_AD11",   "CMP1_OUT", "-"                 },
        {  "-",            "PTC5/LLWU_P9","SPI0_SCK","LPTMR0_ALT2","I2S0_RXD0","FB_AD10",  "CMP0_OUT", "FTM0_CH2"          },
        {  "CMP0_IN0",     "PTC6/LLWU_P10","SPI0_SOUT","PDB0_EXTRG","I2S0_RX_BCLK","FB_AD9","I2S0_MCLK","-"                },
        {  "CMP0_IN1",     "PTC7",  "SPI0_SIN",  "USB_SOF_OUT","I2S0_RX_FS",  "FB_AD8",    "-",        "-"                 },
        {  "ADC1_SE4b/CMP0_IN2","PTC8","-",      "FTM3_CH4",   "I2S0_MCLK",   "FB_AD7",    "-",        "-"                 },
        {  "ADC1_SE5b/CMP0_IN3","PTC9","-",      "FTM3_CH5",   "I2S0_RX_BCLK","FB_AD6",    "FTM2_FLT0","-"                 },
        {  "ADC1_SE6b",    "PTC10", "I2C1_SCL",  "FTM3_CH6",   "I2S0_RX_FS",  "FB_AD5",    "-",        "-"                 },
        {  "ADC1_SE7b",    "PTC11/LLWU_P11","I2C1_SDA","FTM3_CH7","I2S0_RXD1","FB_RW_b",   "-",        "-"                 },
        {  "-",            "PTC12", "-",         "UART4_RTS_b","-",           "FB_AD27",   "FTM3_FLT0","-"                 },
        {  "-",            "PTC13", "-",         "UART4_CTS_b","-",           "FB_AD26",   "-",        "-"                 },
        {  "-",            "PTC14", "-",         "UART4_RX",   "-",           "FB_AD25",   "-",        "-"                 },
        {  "-",            "PTC15", "-",         "UART4_TX",   "-",           "FB_AD24",   "-",        "-"                 },
        {  "-",            "PTC16", "-",         "UART3_RX",   "ENET_1588_TMR0","FB_CS5/FB_TSIZ1/FB_BE23_16_BLS15_8","-","-"},
        {  "-",            "PTC17", "-",         "UART3_TX",   "ENET_1588_TMR1","FB_CS4/FB_TSIZ0/FB_BE31_24_BLS7_0","-","-"},
        {  "-",            "PTC18", "-",         "UART3_RTS",  "ENET_1588_TMR2","FB_TBST/FB_CS2/FB_BE15_8_BLS23_16","-","-"},
    #else
        {  "ADC0_SE14/TSI0_CH13","PTC0","SPI0_PCS4","PDB0_EXTRG","-",         "FB_AD14",   "I2S0_TXD1","-"                 }, // PORT C {1}
        {  "ADC0_SE15/TSI0_CH14","PTC1/LLWU_P6","SPI0_PCS3","UART1_RTS_b","FTM0_CH0","FB_AD13","I2S0_TXD0","-"             }, // {1}
        {  "ADC0_SE4/CMP1_IN0/TSI0_CH15","PTC2","SPI0_PCS2","UART1_CTS_b","FTM0_CH1","FB_AD12","I2S0_TX_FS","-"            }, // {1}
        {  "CMP1_IN1",     "PTC3/LLWU_P7","SPI0_PCS1","UART1_RX","FTM0_CH2",  "FB_CLKOUT", "I2S0_TX_BCLK","-"              }, // {1}
        {  "-",            "PTC4/LLWU_P8","SPI0_PCS0","UART1_TX","FTM0_CH3",  "FB_AD11",   "CMP1_OUT", "-"                 }, // {1}
        {  "-",            "PTC5/LLWU_P9","SPI0_SCK","LPTMR0_ALT2","I2S0_RXD0","FB_AD10",  "CMP0_OUT", "-"                 }, // {1}
        {  "CMP0_IN0",     "PTC6/LLWU_P10","SPI0_SOUT","PDB0_EXTRG","I2S0_RX_BCLK","FB_AD9","I2S0_MCLK","-"                }, // {1}
        {  "CMP0_IN1",     "PTC7",  "SPI0_SIN",  "USB_SOF_OUT","I2S0_RX_FS",  "FB_AD8",    "-",        "-"                 }, // {1}
        {  "ADC1_SE4/CMP0_IN2","PTC8","-",       "-",          "I2S0_MCLK",   "FB_AD7",    "-",        "-"                 }, // {1}
        {  "ADC1_SE5/CMP0_IN3","PTC9","-",       "-",          "I2S0_RX_BCLK","FB_AD6",    "FTM2_FLT0","-"                 },
        {  "ADC1_SE6/CMP0_IN4","PTC10","I2C1_SCL","-",         "I2S0_RX_FS",  "FB_AD5",    "-",        "-"                 },
        {  "ADC1_SE7",     "PTC11/LLWU_P11","I2C1_SDA","-",    "I2S0_RXD",    "FB_RW",     "-",        "-"                 }, // {1}
        {  "-",            "PTC12", "-",         "UART4_RTS_b","-",           "FB_AD27",   "-",        "-"                 }, // {1}
        {  "-",            "PTC13", "-",         "UART4_CTS_b","-",           "FB_AD26",   "-",        "-"                 }, // {1}
        {  "-",            "PTC14", "-",         "UART4_RX",   "-",           "FB_AD25",   "-",        "-"                 }, // {1}
        {  "-",            "PTC15", "-",         "UART4_TX",   "-",           "FB_AD24",   "-",        "-"                 }, // {1}
        {  "-",            "PTC16", "CAN1_RX",   "UART3_RX",   "ENET_1588_TMR0","FB_CS5/FB_TSIZ1/FB_BE23_16_BLS15_8","-","-"},
        {  "-",            "PTC17", "CAN1_TX",   "UART3_TX",   "ENET_1588_TMR1","FB_CS4/FB_TSIZ0/FB_BE31_24_BLS7_0","-","-"},
        {  "-",            "PTC18", "-",         "UART3_RTS",  "ENET_1588_TMR2","FB_TBST/FB_CS2/FB_BE15_8_BLS23_16","-","-"},
    #endif
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 }
    },
    {
        // ALT 0           ALT 1    ALT2         ALT 3         ALT 4          ALT 5        ALT 6       ALT 7
    #if defined KINETIS_K64
        {  "-",            "PTD0/LLWU_P12","SPI0_PCS0","UART2_RTS_b","FTM3_CH0","FB_ALE/FB_CS1_b/FB_TS_b","-","-"          }, // PORT D
        {  "ADC0_SE5b",    "PTD1",  "SPI0_SCK",  "UART2_CTS_b","FTM3_CH1",    "FB_CS0_b",  "-",        "-"                 },
        {  "-",            "PTD2/LLWU_P13","SPI0_SOUT","UART2_RX","FTM3_CH2", "FB_AD4",    "-",        "I2C0_SCL"          },
        {  "-",            "PTD3",  "SPI0_SIN",  "UART2_TX",   "FTM3_CH3",    "FB_AD3",    "-",        "I2C0_SDA"          },
        {  "-",            "PTD4/LLWU_P14","SPI0_PCS1","UART0_RTS_b","FTM0_CH4","FB_AD2",  "EWM_IN",   "SPI1_PCS0"         },
        {  "ADC0_SE6b",    "PTD5",  "SPI0_PCS2", "UART0_CTS_b/UART0_COL_b","FTM0_CH5","FB_AD1","EWM_OUT_b","SPI1_SCK"      },
        {  "ADC0_SE7b",    "PTD6/LLWU_P15","SPI0_PCS3","UART0_RX","FTM0_CH6", "FB_AD0",    "FTM0_FLT0","SPI1_SOUT"         },
        {  "-",            "PTD7",  "CMT_IRO",   "UART0_TX",   "FTM0_CH7",    "-",         "FTM0_FLT1","SPI1_SIN"          },
    #else
        {  "-",            "PTD0/LLWU_P12","SPI0_PCS0", "UART2_RTS", "-",     "FB_ALE/FB_CS1/FB_TS","-","-"                }, // PORT D {1}
        {  "ADC0_SE5",     "PTD1",  "SPI0_SCK",  "UART2_CTS",  "-",           "FB_CS0",    "-",        "-"                 },
        {  "-",            "PTD2/LLWU_P13","SPI0_SOUT","UART2_RX","-",        "FB_AD4",    "-",        "-"                 }, // {1}
        {  "-",            "PTD3",  "SPI0_SIN",  "UART2_TX",   "-",           "FB_AD3",    "-",        "-"                 },
        {  "-",            "PTD4/LLWU_P14","SPI0_PCS1","UART0_RTS","FTM0_CH4","FB_AD2",    "EWM_IN",   "-"                 }, // {1}
        {  "ADC0_SE6",     "PTD5",  "SPI0_PCS2", "UART0_CTS",  "FTM0_CH5",    "FB_AD1",    "EWM_OUT",  "-"                 },
        {  "ADC0_SE7",     "PTD6/LLWU_P15","SPI0_PCS3","UART0_RX","FTM0_CH6", "FB_AD0",    "FTM0_FLT0","-"                 }, // {1}
        {  "-",            "PTD7",  "CMT_IRO",   "UART0_TX",   "FTM0_CH7",    "-",         "FTM0_FLT1","-"                 },
    #endif
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 }
    },
    {
        // ALT 0           ALT 1    ALT2         ALT 3         ALT 4          ALT 5        ALT 6       ALT 7
    #if defined KINETIS_K64
        {  "ADC1_SE4a",    "PTE0",  "SPI1_PCS1", "UART1_TX",   "SDHC0_D1",    "TRACE_CLKOUT","I2C1_SDA","RTC_CLKOUT"       }, // PORT E
        {  "ADC1_SE5a",    "PTE1/LLWU_P0","SPI1_SOUT","UART1_RX","SDHC0_D0",  "TRACE_D3",  "I2C1_SCL", "SPI1_SIN"          },
        {  "ADC0_DM2/ADC1_SE6a","PTE2/LLWU_P1","SPI1_SCK","UART1_CTS_b","SDHC0_DCLK","TRACE_D2","-",   "-"                 },
        {  "ADC0_DM2/ADC1_SE7a","PTE3","SPI1_SIN","UART1_RTS_b","SDHC0_CMD",  "TRACE_D1",  "-",        "SPI1_SOUT"         },
        {  "-",            "PTE4/LLWU_P2","SPI1_PCS0","UART3_TX","SDHC0_D3",  "TRACE_D0",  "-",        "-"                 },
        {  "-",            "PTE5",  "SPI1_PCS2", "UART3_RX",   "SDHC0_D2",    "-",         "FTM3_CH0", "-"                 },
        {  "-",            "PTE6",  "SPI1_PCS3", "UART3_CTS_b","I2S0_MCLK",   "-",         "FTM3_CH1", "USB_SOF_OUT"       },
    #else
        {  "ADC1_SE4",     "PTE0",  "SPI1_PCS1", "UART1_TX",   "SDHC0_D1",    "-",         "I2C1_SDA", "RTC_CLKOUT"        }, // PORT E {1}
        {  "ADC1_SE5",     "PTE1/LLWU_P0","SPI1_SOUT","UART1_RX","SDHC0_D0",  "-",         "I2C1_SCL", "SPI1_SIN"          }, // {1}
        {  "ADC1_SE6",     "PTE2/LLWU_P1","SPI1_SCK","UART1_CTS","SDHC0_DCLK","-",         "-",        "-"                 }, // {1}
        {  "ADC1_SE7",     "PTE3",  "SPI1_SIN",  "UART1_RTS",  "SDHC0_CMD",   "-",         "-",        "SPI1_SOUT"         }, // {1}
        {  "-",            "PTE4/LLWU_P2","SPI1_PCS0","UART3_TX","SDHC0_D3",  "-",         "-",        "-"                 }, // {1}
        {  "-",            "PTE5",  "SPI1_PCS2", "UART3_RX",   "SDHC0_D2",    "-",         "-",        "-"                 },
        {  "-",            "PTE6",  "SPI1_PCS3", "UART3_CTS",  "I2S0_MCLK",   "-",         "-",        "USB_SOF_OUT"       }, // {1}
    #endif
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
    #if defined KINETIS_K64
        {  "ADC0_SE17",    "PTE24", "-",         "UART4_TX",   "-",           "I2C0_SCL",  "EWM_OUT_b","-"                 },
        {  "ADC0_SE18",    "PTE25", "-",         "UART4_RX",   "-",           "I2C_SDA",   "EWM_IN",   "-"                 },

    #else
        {  "ADC0_SE17",    "PTE24", "CAN1_TX",   "UART4_TX",   "-",           "-",         "EWM_OUT_b","-"                 }, // {1}
        {  "ADC0_SE18",    "PTE25", "CAN1_RX",   "UART4_RX",   "-",           "-",         "EWM_IN",   "-"                 },
    #endif
        {  "-",            "PTE26", "ENET_1588_CLKIN", "UART4_CTS_b","-",     "-",         "RTC_CLKOUT","USB_CLKIN"        },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 }
    }
};
#elif _PIN_COUNT == 1 
static const char *cPer[PORTS_AVAILABLE][PORT_WIDTH][8] = {              // 121 pin
    {
        // ALT 0           ALT 1    ALT2         ALT 3         ALT 4          ALT 5        ALT 6       ALT 7
        {  "TSI0_CH1",     "PTA0",  "UART0_CTS_b","FTM0_CH5",  "-",           "-",         "-",        "JTAG_TCLK/SWD_CLK" }, // PORT A
        {  "TSI0_CH2",     "PTA1",  "UART0_RX",  "FTM0_CH6",   "-",           "-",         "-",        "JTAG_TDI"          },
        {  "TSI0_CH3",     "PTA2",  "UART0_TX",  "FTM0_CH7",   "-",           "-",         "-",        "JTAG_TDI/TRACE_SWO"},
        {  "TSI0_CH4",     "PTA3",  "UART0_RTS_b","FTM0_CH0",  "-",           "-",         "-",        "JTAG_TMS/SWD_DIO"  },
        {  "TSI0_CH5",     "PTA4",  "-",         "FTM0_CH1",   "-",           "-",         "-",        "NMI_b"             },
        {  "-",            "PTA5",  "-",         "FTM0_CH2",   "MII_RXER",    "CMP2_OUT",  "I2S0_RX_BCLK","JTAG_TRST"      },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "PTA10", "-",         "FTM2_CH0",   "MII_RXD2",    "-",         "FTM2_QD_PHA","TRACE_D0"        },
        {  "-",            "PTA11", "-",         "FTM2_CH1",   "MII_RXCLK",   "-",         "FTM2_QD_PHB","-"               },
        {  "CMP2_IN0",     "PTA12", "CAN0_TX",   "FTM1_CH0",   "MII_RXD1",    "-",         "I2S0_TXD", "FTM1_QD_PHA"       },
        {  "CMP2_IN1",     "PTA13/LLWU_P4","CAN0_RX","FTM1_CH1","MII_RXD0",   "-",         "I2S0_TX_FS","FTM1_QD_PHB"      }, // {1}
        {  "-",            "PTA14", "SPI0_PCS0", "UART0_TX",   "MII_CRS_DV",  "-",         "I2S0_RX_BCLK","-"              },
        {  "-",            "PTA15", "SPI0_SCK",  "UART0_RX",   "MII_TXEN",    "-",         "I2S0_RXD", "-"                 },
        {  "-",            "PTA16", "SPI0_SOUT", "UART0_CTS",  "MII_TXD0",    "-",         "I2S0_RX_FS","I2S0_RXD1"        }, // {1}
        {  "ADC1_SE17",    "PTA17", "SPI0_SIN",  "UART0_RTS",  "MII_TXD1",    "-",         "I2S0_MCLK","-"                 }, // {1}
        {  "EXTAL",        "PTA18", "-",         "FTM0_FLT2",  "FTM_CLKIN0",  "-",         "-",        "-"                 },
        {  "XTAL",         "PTA19", "-",         "FTM1_FLT0",  "FTM_CLKIN1",  "-",         "LPT0_ALT1","-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },                
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "PTA29", "-",         "-",          "MII_COL",     "-",         "FB_A24",   "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 }
    },
    {
        // ALT 0           ALT 1    ALT2         ALT 3         ALT 4          ALT 5        ALT 6       ALT 7
        {  "ADC0_SE8/TSI0_CH1","PTB0/LLWU_P5","I2C0_SCL","FTM1_CH0","MII_MDIO","-",        "FTM1_QD_PHA", "-"              }, // PORT B {1}
        {  "ADC0_SE9/TSI0_CH6","PTB1","I2C0_SDA","FTM1_CH1",   "MII_MCD",     "-",         "FTM1_QD_PHB", "-"              },
        {  "ADC0_SE12/TSI0_CH7","PTB2","I2C0_SCL","UART0_RTS_b","ENET_1588_TMR0","-",      "FTM0_FLT3","-"                 },
        {  "ADC0_SE13/TSI0_CH8","PTB3","I2C0_SDA","UART0_CTS_b","ENET_1588_TMR1","-",      "FTM0_FLT0","-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "ADC1_SE12",    "PTB6",  "-",         "-",          "-",           "FB_AD23",   "-",        "-"                 },
        {  "ADC1_SE13",    "PTB7",  "-",         "-",          "-",           "FB_AD22",   "-",        "-"                 },
        {  "-",            "PTB8",  "-",         "UART3_RTS_b","-",           "FB_AD21",   "-",        "-"                 },
        {  "-",            "PTB9",  "SPI1_PCS1", "UART3_CTS_b","-",           "FB_AD20",   "-",        "-"                 },
        {  "ADC1_SE14",    "PTB10", "SPI1_PCS0", "UART3_RX",   "-",           "FB_AD19",   "FTM0_FLT1","-"                 },
        {  "ADC1_SE15",    "PTB11", "SPI1_SCK",  "UART3_TX",   "-",           "FB_AD18",   "FTM0_FLT2","-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "TSI0_CH9",     "PTB16", "SPI1_SOUT", "UART0_RX",   "-",           "FB_AD17",   "EWM_IN",   "-"                 },
        {  "TSI0_CH10",    "PTB17", "SPI1_SIN",  "UART0_TX",   "-",           "FB_AD16",   "EWM_OUT_b","-"                 },
        {  "TSI0_CH11",    "PTB18", "CAN0_TX",   "FTM2_CH0",   "I2S0_TX_BCLK","FB_AD15",   "FTM2_QD_PHA","-"               },
        {  "TSI0_CH12",    "PTB19", "CAN0_RX",   "FTM2_CH1",   "I2S0_TX_FS",  "FB_OE",     "FTM2_QD_PHB","-"               },
        {  "-",            "PTB20", "SPI2_PCS0", "-",          "-",           "FB_AD31",   "CMP0_OUT", "-"                 },
        {  "-",            "PTB21", "SPI2_SCK",  "-",          "-",           "FB_AD30",   "CMP1_OUT", "-"                 },
        {  "-",            "PTB22", "SPI2_SOUT", "-",          "-",           "FB_AD29",   "CMP2_OUT", "-"                 },
        {  "-",            "PTB23", "SPI2_SIN",  "SPI0_PCS5",  "-",           "FB_AD28",   "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 }
    },
    {
        // ALT 0           ALT 1    ALT2         ALT 3         ALT 4          ALT 5        ALT 6       ALT 7
        {  "ADC0_SE14/TSI0_CH13","PTC0","SPI0_PCS4","PDB0_EXTRG","-",         "FB_AD14",   "I2S0_TXD1", "-"                }, // PORT C {1}
        {  "ADC0_SE15/TSI0_CH14","PTC1/LLWU_P6","SPI0_PCS3","UART1_RTS_b","FTM0_CH0","FB_AD13","I2S0_TXD0","-"             }, // {1}
        {  "ADC0_SE4/CMP1_IN0/TSI0_CH15","PTC2","SPI0_PCS2","UART1_CTS_b","FTM0_CH1","FB_AD12","I2S0_TX_FS","-"            }, // {1}
        {  "CMP1_IN1",     "PTC3/LLWU_P7","SPI0_PCS1","UART1_RX","FTM0_CH2",  "FB_CLKOUT", "I2S0_TX_BCLK","-"              }, // {1}
        {  "-",            "PTC4/LLWU_P8","SPI0_PCS0","UART1_TX","FTM0_CH3",  "FB_AD11",   "CMP1_OUT", "-"                 }, // {1}
        {  "-",            "PTC5/LLWU_P9","SPI0_SCK","LPTMR0_ALT2","I2S0_RXD0","FB_AD10",  "CMP0_OUT", "-"                 }, // {1}
        {  "CMP0_IN0",     "PTC6/LLWU_P10","SPI0_SOUT","PDB0_EXTRG","I2S0_RX_BCLK","FB_AD9","I2S0_MCLK","-"                }, // {1}
        {  "CMP0_IN1",     "PTC7",  "SPI0_SIN",  "USB_SOF_OUT","I2S0_RX_FS",   "FB_AD8",    "-",        "-"                 }, // {1}
        {  "ADC1_SE4/CMP0_IN2","PTC8","-",       "-",          "I2S0_MCLK",   "FB_AD7",    "-",        "-"                 }, // {1}
        {  "ADC1_SE5/CMP0_IN3","PTC9","-",       "-",          "I2S0_RX_BCLK","FB_AD6",    "FTM2_FLT0","-"                 },
        {  "ADC1_SE6/CMP0_IN4","PTC10","I2C1_SCL","-",         "I2S0_RX_FS",  "FB_AD5",    "-",        "-"                 },
        {  "ADC1_SE7",     "PTC11/LLWU_P11","I2C1_SDA","-",    "I2S0_RXD",    "FB_RW",     "-",        "-"                 }, // {1}
        {  "-",            "PTC12", "-",         "UART4_RTS_b","-",           "FB_AD27",   "-",        "-"                 }, // {1}
        {  "-",            "PTC13", "-",         "UART4_CTS_b","-",           "FB_AD26",   "-",        "-"                 }, // {1}
        {  "-",            "PTC14", "-",         "UART4_RX",   "-",           "FB_AD25",   "-",        "-"                 }, // {1}
        {  "-",            "PTC15", "-",         "UART4_TX",   "-",           "FB_AD24",   "-",        "-"                 }, // {1}
        {  "-",            "PTC16", "CAN1_RX",   "UART3_RX",   "ENET_1588_TMR0","FB_CS5/FB_TSIZ1/FB_BE23_16_BLS15_8","-","-"},
        {  "-",            "PTC17", "CAN1_TX",   "UART3_TX",   "ENET_1588_TMR1","FB_CS4/FB_TSIZ0/FB_BE31_24_BLS7_0","-","-"},
        {  "-",            "PTC18", "-",         "UART3_RTS_b","ENET_1588_TMR2","FB_TBST/FB_CS2/FB_BE15_8_BLS23_16","-","-"},
        {  "-",            "PTC19", "-",         "UART3_CTS_b","ENET_1588_TMR3","FB_CS3/FB_BE7_0_BLS31_24","FB_TA","-"     },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 }
    },
    {
        // ALT 0           ALT 1    ALT2         ALT 3         ALT 4          ALT 5        ALT 6       ALT 7
        {  "-",            "PTD0/LLWU_P12","SPI0_PCS0", "UART2_RTS", "-",     "FB_ALE/FB_CS1/FB_TS","-","-"                }, // PORT D {1}
        {  "ADC0_SE5",     "PTD1",  "SPI0_SCK",  "UART2_CTS",  "-",           "FB_CS0",    "-",        "-"                 },
        {  "-",            "PTD2/LLWU_P13","SPI0_SOUT","UART2_RX","-",        "FB_AD4",    "-",        "-"                 }, // {1}
        {  "-",            "PTD3",  "SPI0_SIN",  "UART2_TX",   "-",           "FB_AD3",    "-",        "-"                 },
        {  "-",            "PTD4/LLWU_P14","SPI0_PCS1","UART0_RTS","FTM0_CH4","FB_AD2",    "EWM_IN",   "-"                 }, // {1}
        {  "ADC0_SE6",     "PTD5",  "SPI0_PCS2", "UART0_CTS",  "FTM0_CH5",    "FB_AD1",    "EWM_OUT",  "-"                 },
        {  "ADC0_SE7",     "PTD6/LLWU_P15","SPI0_PCS3","UART0_RX","FTM0_CH6", "FB_AD0",    "FTM0_FLT0","-"                 }, // {1}
        {  "-",            "PTD7",  "CMT_IRO",   "UART0_TX",   "FTM0_CH7",    "-",         "FTM0_FLT1","-"                 },
        {  "-",            "PTD8",  "I2C0_SCL",  "UART5_RX",   "-",           "-",         "FB_A16",   "-"                 },
        {  "-",            "PTD9",  "I2C0_SDA",  "UART5_TX",   "-",           "-",         "FB_A17",   "-"                 },
        {  "-",            "PTD10", "-",         "UART5_RTS",  "-",           "-",         "FB_A18",   "-"                 },
        {  "-",            "PTD11", "SPI2_PCS0", "UART5_CTS",  "SDHC0_CLKIN", "-",         "FB_A19",   "-"                 },
        {  "-",            "PTD12", "SPI2_SCK",  "-",          "SDHC0_D4",    "-",         "FB_A20",   "-"                 },
        {  "-",            "PTD13", "SPI2_SOUT", "-",          "SDHC0_D5",    "-",         "FB_A21",   "-"                 },
        {  "-",            "PTD14", "SPI2_SIN",  "-",          "SDHC0_D6",    "-",         "FB_A22",   "-"                 },
        {  "-",            "PTD15", "SPI2_PCS1", "-",          "SDHC0_D7",    "-",         "FB_A23",   "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 }
    },
    {
        // ALT 0           ALT 1    ALT2         ALT 3         ALT 4          ALT 5        ALT 6       ALT 7
        {  "ADC1_SE4",     "PTE0",  "SPI1_PCS1", "UART1_TX",   "SDHC0_D1",    "-",         "I2C1_SDA", "RTC_CLKOUT"        }, // PORT E {1}
        {  "ADC1_SE5",     "PTE1/LLWU_P0","SPI1_SOUT","UART1_RX","SDHC0_D0",  "-",         "I2C1_SCL", "SPI1_SIN"          }, // {1}
        {  "ADC1_SE6",     "PTE2/LLWU_P1","SPI1_SCK","UART1_CTS","SDHC0_DCLK","-",         "-",        "-"                 }, // {1}
        {  "ADC1_SE7",     "PTE3",  "SPI1_SIN",  "UART1_RTS",  "SDHC0_CMD",   "-",         "-",        "SPI1_SOUT"         }, // {1}
        {  "-",            "PTE4/LLWU_P2","SPI1_PCS0","UART3_TX","SDHC0_D3",  "-",         "-",        "-"                 }, // {1}
        {  "-",            "PTE5",  "SPI1_PCS2", "UART3_RX",   "SDHC0_D2",    "-",         "-",        "-"                 },
        {  "-",            "PTE6",  "SPI1_PCS3", "UART3_CTS",  "I2S0_MCLK",   "-",         "-",        "USB_SOF_OUT"       }, // {1}
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "ADC0_SE17",    "PTE24", "CAN1_TX",   "UART4_TX",   "-",           "-",         "EWM_OUT_b","-"                 }, // {1}
        {  "ADC0_SE18",    "PTE25", "CAN1_RX",   "UART4_RX",   "-",           "-",         "EWM_IN",   "-"                 },
        {  "-",            "PTE26", "ENET_1588_CLKIN", "UART4_CTS_b","-",     "-",         "RTC_CLKOUT","USB_CLKIN"        }, // {1}
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 }
    }
};
#else
static const char *cPer[PORTS_AVAILABLE][PORT_WIDTH][8] = {              // 144 pin LQFP/MAPBGA
    {
        // ALT 0           ALT 1    ALT2         ALT 3         ALT 4          ALT 5        ALT 6       ALT 7
    #if defined KINETIS_K64
        {  "-",            "PTA0",  "UART0_CTS_b/UART0_COL_b", "FTM0_CH5","-","-",         "-",        "JTAG_TCLK/SWD_CLK" }, // PORT A
        {  "-",            "PTA1",  "UART0_RX",  "FTM0_CH6",   "-",           "-",         "-",        "JTAG_TDI"          },
        {  "-",            "PTA2",  "UART0_TX",  "FTM0_CH7",   "-",           "-",         "-",        "JTAG_TDI/TRACE_SWO"},
        {  "-",            "PTA3",  "UART0_RTS_b","FTM0_CH0",  "-",           "-",         "-",        "JTAG_TMS/SWD_DIO"  },
        {  "-",            "PTA4/LLWU_P3", "-",  "FTM0_CH1",   "-",           "-",         "-",        "NMI_b"             },
        {  "-",            "PTA5",  "USB_CLKIN", "FTM0_CH2",   "MII_RXER",    "CMP2_OUT",  "I2S0_RX_BCLK","JTAG_TRST"      },
        {  "-",            "PTA6",  "-",         "FTM0_CH3",   "-",           "CLKOUT",    "-",        "TRACE_CLKOUT"      },
        {  "ADC0_SE10",    "PTA7",  "-",         "FTM0_CH4",   "-",           "-",         "-",        "TRACE_D3"          },
        {  "ADC0_SE11",    "PTA8",  "-",         "FTM1_CH0",   "-",           "-",         "FTM1_QD_PHA","TRACE_D2"        },
        {  "-",            "PTA9",  "-",         "FTM1_CH1",   "MII_RXD3",    "-",         "FTM1_QD_PHB","TRACE_D1"        },
        {  "-",            "PTA10", "-",         "FTM2_CH0",   "MII_RXD2",    "-",         "FTM2_QD_PHA","TRACE_D0"        },
        {  "-",            "PTA11", "-",         "FTM2_CH1",   "MII_RXCLK",   "I2C2_SDA",  "FTM2_QD_PHB","-"               },
        {  "CMP2_IN0",     "PTA12", "CAN0_TX",   "FTM1_CH0",   "MII_RXD1",    "I2C2_SCL",  "I2S0_TXD", "FTM1_QD_PHA"       },
        {  "CMP2_IN1",     "PTA13/LLWU_P4","CAN0_RX","FTM1_CH1","MII_RXD0",   "I2C_SDA",   "I2S0_TX_FS","FTM1_QD_PHB"      },
        {  "-",            "PTA14", "SPI0_PCS0", "UART0_TX",   "MII_CRS_DV",  "I2C2_SCL",  "I2S0_RX_BCLK","-"              },
        {  "-",            "PTA15", "SPI0_SCK",  "UART0_RX",   "MII_TXEN",    "-",         "I2S0_RXD0","-"                 },
        {  "-",            "PTA16", "SPI0_SOUT", "UART0_CTS_b/UART0_COL_b","MII_TXD0","-", "I2S0_RX_FS","I2S0_RXD1"        },
        {  "ADC1_SE17",    "PTA17", "SPI0_SIN",  "UART0_RTS_b","MII_TXD1",    "-",         "I2S0_MCLK","-"                 },
        {  "EXTAL0",       "PTA18", "-",         "FTM0_FLT2",  "FTM_CLKIN0",  "-",         "-",        "-"                 },
        {  "XTAL0",        "PTA19", "-",         "FTM1_FLT0",  "FTM_CLKIN1",  "-",         "LPT0_ALT1","-"                 },
    #else
        {  "TSI0_CH1",     "PTA0",  "UART0_CTS", "FTM0_CH5",   "-",           "-",         "-",        "JTAG_TCLK/SWD_CLK" }, // PORT A
        {  "TSI0_CH2",     "PTA1",  "UART0_RX",  "FTM0_CH6",   "-",           "-",         "-",        "JTAG_TDI"          },
        {  "TSI0_CH3",     "PTA2",  "UART0_TX",  "FTM0_CH7",   "-",           "-",         "-",        "JTAG_TDI/TRACE_SWO"},
        {  "TSI0_CH4",     "PTA3",  "UART0_RTS", "FTM0_CH0",   "-",           "-",         "-",        "JTAG_TMS/SWD_DIO"  },
        {  "TSI0_CH5",     "PTA4",  "-",         "FTM0_CH1",   "-",           "-",         "-",        "NMI"               },
        {  "-",            "PTA5",  "-",         "FTM0_CH2",   "MII_RXER",    "CMP2_OUT",  "I2S0_RX_BCLK","JTAG_TRST"      },
        {  "-",            "PTA6",  "-",         "FTM0_CH3",   "-",           "-",         "-",        "TRACE_CLKOUT"      },
        {  "ADC0_SE10",    "PTA7",  "-",         "FTM0_CH4",   "-",           "-",         "-",        "TRACE_D3"          },
        {  "ADC0_SE11",    "PTA8",  "-",         "FTM1_CH0",   "-",           "-",         "FTM1_QD_PHA","TRACE_D2"        },
        {  "-",            "PTA9",  "-",         "FTM1_CH1",   "MII_RXD3",    "-",         "FTM1_QD_PHB","TRACE_D1"        },
        {  "-",            "PTA10", "-",         "FTM2_CH0",   "MII_RXD2",    "-",         "FTM2_QD_PHA","TRACE_D0"        },
        {  "-",            "PTA11", "-",         "FTM2_CH1",   "MII_RXCLK",   "-",         "FTM2_QD_PHB","-"               },
        {  "CMP2_IN0",     "PTA12", "CAN0_TX",   "FTM1_CH0",   "MII_RXD1",    "-",         "I2S0_TXD", "FTM1_QD_PHA"       },
        {  "CMP2_IN1",     "PTA13/LLWU_P4","CAN0_RX","FTM1_CH1","MII_RXD0",   "-",         "I2S0_TX_FS","FTM1_QD_PHB"      }, // {1}
        {  "-",            "PTA14", "SPI0_PCS0", "UART0_TX",   "MII_CRS_DV",  "-",         "I2S0_RX_BCLK","-"              },
        {  "-",            "PTA15", "SPI0_SCK",  "UART0_RX",   "MII_TXEN",    "-",         "I2S0_RXD", "-"                 },
        {  "-",            "PTA16", "SPI0_SOUT", "UART0_CTS",  "MII_TXD0",    "-",         "I2S0_RX_FS","I2S0_RXD1"        }, // {1}
        {  "ADC1_SE17",    "PTA17", "SPI0_SIN",  "UART0_RTS",  "MII_TXD1",    "-",         "I2S0_MCLK","-"                 }, // {1}
        {  "EXTAL",        "PTA18", "-",         "FTM0_FLT2",  "FTM_CLKIN0",  "-",         "-",        "-"                 },
        {  "XTAL",         "PTA19", "-",         "FTM1_FLT0",  "FTM_CLKIN1",  "-",         "LPT0_ALT1","-"                 },
    #endif
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "PTA24", "-",         "-",          "MII_TXD2",    "-",         "FB_A29",   "-"                 },
        {  "-",            "PTA25", "-",         "-",          "MII_TXCLK",   "-",         "FB_A28",   "-"                 },
        {  "-",            "PTA26", "-",         "-",          "MII_TXD3",    "-",         "FB_A27",   "-"                 },                
        {  "-",            "PTA27", "-",         "-",          "MII_CRS",     "-",         "FB_A26",   "-"                 },
        {  "-",            "PTA28", "-",         "-",          "MII_TXER",    "-",         "FB_A25",   "-"                 },
        {  "-",            "PTA29", "-",         "-",          "MII_COL",     "-",         "FB_A24",   "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 }
    },
    {
        // ALT 0           ALT 1    ALT2         ALT 3         ALT 4          ALT 5        ALT 6       ALT 7
    #if defined KINETIS_K64
        {  "ADC0_SE8/ADC1_SE8","PTB0/LLWU_P5","I2C0_SCL","FTM1_CH0","MII_MDIO","-",        "FTM1_QD_PHA", "-"              }, // PORT B {1}
        {  "ADC0_SE9/ADC1_SE9","PTB1","I2C0_SDA","FTM1_CH1",   "MII_MCD",     "-",         "FTM1_QD_PHB", "-"              },
        {  "ADC0_SE12",    "PTB2","I2C0_SCL","UART0_RTS_b",    "ENET_1588_TMR0","-",       "FTM0_FLT3","-"                 },
        {  "ADC0_SE13",    "PTB3","I2C0_SDA","UART0_CTS_b/UART0_COL_b","ENET_1588_TMR1","-","FTM0_FLT0","-"                },
        {  "ADC1_SE10",    "PTB4",  "-",         "-",          "ENET_1588_TMR2","-",       "FTM1_FLT0","-"                 },
        {  "ADC1_SE11",    "PTB5",  "-",         "-",          "ENET_1588_TMR3","-",       "FTM2_FLT0","-"                 },
        {  "ADC1_SE12",    "PTB6",  "-",         "-",          "-",           "FB_AD23",   "-",        "-"                 },
        {  "ADC1_SE13",    "PTB7",  "-",         "-",          "-",           "FB_AD22",   "-",        "-"                 },
        {  "-",            "PTB8",  "-",         "UART3_RTS_b","-",           "FB_AD21",   "-",        "-"                 },
        {  "-",            "PTB9",  "SPI1_PCS1", "UART3_CTS_b","-",           "FB_AD20",   "-",        "-"                 },
        {  "ADC1_SE14",    "PTB10", "SPI1_PCS0", "UART3_RX",   "-",           "FB_AD19",   "FTM0_FLT1","-"                 },
        {  "ADC1_SE15",    "PTB11", "SPI1_SCK",  "UART3_TX",   "-",           "FB_AD18",   "FTM0_FLT2","-"                 },
        {  "-",            "PTB12", "UART3_RTS_b","FTM1_CH0",  "FTM0_CH4",    "-",         "FTM1_QD_PHA","-"               },
        {  "-",            "PTB13", "UART3_CTS_b","FTM1_CH1",  "FTM0_CH5",    "-",         "FTM1_QD_PHB","-"               },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "PTB16", "SPI1_SOUT", "UART0_RX",   "FTM_CLKIN0",  "FB_AD17",   "EWM_IN",   "-"                 },
        {  "-",            "PTB17", "SPI1_SIN",  "UART0_TX",   "FTM_CLKIN1",  "FB_AD16",   "EWM_OUT_b","-"                 },
        {  "-",            "PTB18", "CAN0_TX",   "FTM2_CH0",   "I2S0_TX_BCLK","FB_AD15",   "FTM2_QD_PHA","-"               },
        {  "-",            "PTB19", "CAN0_RX",   "FTM2_CH1",   "I2S0_TX_FS",  "FB_OE_b",   "FTM2_QD_PHB","-"               },
        {  "-",            "PTB20", "SPI2_PCS0", "-",          "-",           "FB_AD31",   "CMP0_OUT", "-"                 },
        {  "-",            "PTB21", "SPI2_SCK",  "-",          "-",           "FB_AD30",   "CMP1_OUT", "-"                 },
        {  "-",            "PTB22", "SPI2_SOUT", "-",          "-",           "FB_AD29",   "CMP2_OUT", "-"                 },
        {  "-",            "PTB23", "SPI2_SIN",  "SPI0_PCS5",  "-",           "FB_AD28",   "-",        "-"                 },
    #else
        {  "ADC0_SE8/TSI0_CH1","PTB0/LLWU_P5","I2C0_SCL","FTM1_CH0","MII_MDIO","-",        "FTM1_QD_PHA", "-"              }, // PORT B {1}
        {  "ADC0_SE9/TSI0_CH6","PTB1","I2C0_SDA","FTM1_CH1",   "MII_MCD",     "-",         "FTM1_QD_PHB", "-"              },
        {  "ADC0_SE12/TSI0_CH7","PTB2","I2C0_SCL","UART0_RTS", "ENET_1588_TMR0","-",       "FTM0_FLT3","-"                 },
        {  "ADC0_SE13/TSI0_CH8","PTB3","I2C0_SDA","UART0_CTS", "ENET_1588_TMR1","-",       "FTM0_FLT0","-"                 },
        {  "ADC1_SE10",    "PTB4",  "-",         "-",          "ENET_1588_TMR2","-",       "FTM1_FLT0","-"                 },
        {  "ADC1_SE11",    "PTB5",  "-",         "-",          "ENET_1588_TMR3","-",       "FTM2_FLT0","-"                 },
        {  "ADC1_SE12",    "PTB6",  "-",         "-",          "-",           "FB_AD23",   "-",        "-"                 },
        {  "ADC1_SE13",    "PTB7",  "-",         "-",          "-",           "FB_AD22",   "-",        "-"                 },
        {  "-",            "PTB8",  "-",         "UART3_RTS",  "-",           "FB_AD21",   "-",        "-"                 },
        {  "-",            "PTB9",  "SPI1_PCS1", "UART3_CTS",  "-",           "FB_AD20",   "-",        "-"                 },
        {  "ADC1_SE14",    "PTB10", "SPI1_PCS0", "UART3_RX",   "-",           "FB_AD19",   "FTM0_FLT1","-"                 },
        {  "ADC1_SE15",    "PTB11", "SPI1_SCK",  "UART3_TX",   "-",           "FB_AD18",   "FTM0_FLT2","-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "TSI0_CH9",     "PTB16", "SPI1_SOUT", "UART0_RX",   "-",           "FB_AD17",   "EWM_IN",   "-"                 },
        {  "TSI0_CH10",    "PTB17", "SPI1_SIN",  "UART0_TX",   "-",           "FB_AD16",   "EWM_OUT",  "-"                 },
        {  "TSI0_CH11",    "PTB18", "CAN0_TX",   "FTM2_CH0",   "I2S0_TX_BCLK","FB_AD15",   "FTM2_QD_PHA","-"               },
        {  "TSI0_CH12",    "PTB19", "CAN0_RX",   "FTM2_CH1",   "I2S0_TX_FS",  "FB_OE",     "FTM2_QD_PHB","-"               },
        {  "-",            "PTB20", "SPI2_PCS0", "-",          "-",           "FB_AD31",   "CMP0_OUT", "-"                 },
        {  "-",            "PTB21", "SPI2_SCK",  "-",          "-",           "FB_AD30",   "CMP1_OUT", "-"                 },
        {  "-",            "PTB22", "SPI2_SOUT", "-",          "-",           "FB_AD29",   "CMP2_OUT", "-"                 },
        {  "-",            "PTB23", "SPI2_SIN",  "SPI0_PCS5",  "-",           "FB_AD28",   "-",        "-"                 },
    #endif
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 }
    },
    {
        // ALT 0           ALT 1    ALT2         ALT 3         ALT 4          ALT 5        ALT 6       ALT 7
    #if defined KINETIS_K64
        {  "ADC0_SE14",    "PTC0",  "SPI0_PCS4", "PDB0_EXTRG", "USB_SOF_OUT", "FB_AD14",   "I2S0_TXD1", "-"                }, // PORT C {1}
        {  "ADC0_SE15",    "PTC1/LLWU_P6","SPI0_PCS3","UART1_RTS_b","FTM0_CH0","FB_AD13",  "I2S0_TXD0", "-"                },
        {  "ADC0_SE4/CMP1_IN0","PTC2","SPI0_PCS2","UART1_CTS_b","FTM0_CH1",   "FB_AD12",   "I2S0_TX_FS","-"                },
        {  "CMP1_IN1",     "PTC3/LLWU_P7","SPI0_PCS1","UART1_RX","FTM0_CH2",  "CLKOUT",    "I2S0_TX_BCLK","-"              },
        {  "-",            "PTC4/LLWU_P8","SPI0_PCS0","UART1_TX","FTM0_CH3",  "FB_AD11",   "CMP1_OUT", "-"                 },
        {  "-",            "PTC5/LLWU_P9","SPI0_SCK","LPTMR0_ALT2","I2S0_RXD0","FB_AD10",  "CMP0_OUT", "FTM0_CH0"          },
        {  "CMP0_IN0",     "PTC6/LLWU_P10","SPI0_SOUT","PDB0_EXTRG","I2S0_RX_BCLK","FB_AD9","I2S0_MCLK","-"                },
        {  "CMP0_IN1",     "PTC7",  "SPI0_SIN",  "USB_SOF_OUT","I2S0_RX_FS",  "FB_AD8",    "-",        "-"                 },
        {  "ADC1_SE4b/CMP0_IN2","PTC8","-",      "FTM3_CH4",   "I2S0_MCLK",   "FB_AD7",    "-",        "-"                 },
        {  "ADC1_SE5b/CMP0_IN3","PTC9","-",      "FTM3_CH5",   "I2S0_RX_BCLK","FB_AD6",    "FTM2_FLT0","-"                 },
        {  "ADC1_SE6b/CMP0_IN4","PTC10","I2C1_SCL","FTM3_CH6", "I2S0_RX_FS",  "FB_AD5",    "-",        "-"                 },
        {  "ADC1_SE7b",    "PTC11/LLWU_P11","I2C1_SDA","-",    "I2S0_RXD",    "FB_RW_b",   "-",        "-"                 },
        {  "-",            "PTC12", "-",         "UART4_RTS_b","-",           "FB_AD27",   "FTM3_FLT3","-"                 },
        {  "-",            "PTC13", "-",         "UART4_CTS_b","-",           "FB_AD26",   "-",        "-"                 },
        {  "-",            "PTC14", "-",         "UART4_RX",   "-",           "FB_AD25",   "-",        "-"                 },
        {  "-",            "PTC15", "-",         "UART4_TX",   "-",           "FB_AD24",   "-",        "-"                 },
        {  "-",            "PTC16", "-",         "UART3_RX",   "ENET_1588_TMR0","FB_CS5/FB_TSIZ1/FB_BE23_16_BLS15_8","-","-"},
        {  "-",            "PTC17", "-",         "UART3_TX",   "ENET_1588_TMR1","FB_CS4/FB_TSIZ0/FB_BE31_24_BLS7_0","-","-"},
        {  "-",            "PTC18", "-",         "UART3_RTS_b","ENET_1588_TMR2","FB_TBST/FB_CS2/FB_BE15_8_BLS23_16","-","-"},
        {  "-",            "PTC19", "-",         "UART3_CTS_b","ENET_1588_TMR3","FB_CS3/FB_BE7_0_BLS31_24","FB_TA","-"     },
    #else
        {  "ADC0_SE14/TSI0_CH13","PTC0","SPI0_PCS4","PDB0_EXTRG","-",         "FB_AD14",   "I2S0_TXD1", "-"                }, // PORT C {1}
        {  "ADC0_SE15/TSI0_CH14","PTC1/LLWU_P6","SPI0_PCS3","UART1_RTS_b","FTM0_CH0","FB_AD13","I2S0_TXD0","-"             }, // {1}
        {  "ADC0_SE4/CMP1_IN0/TSI0_CH15","PTC2","SPI0_PCS2","UART1_CTS_b","FTM0_CH1","FB_AD12","I2S0_TX_FS","-"            }, // {1}
        {  "CMP1_IN1",     "PTC3/LLWU_P7","SPI0_PCS1","UART1_RX","FTM0_CH2",  "FB_CLKOUT", "I2S0_TX_BCLK","-"              }, // {1}
        {  "-",            "PTC4/LLWU_P8","SPI0_PCS0","UART1_TX","FTM0_CH3",  "FB_AD11",   "CMP1_OUT", "-"                 }, // {1}
        {  "-",            "PTC5/LLWU_P9","SPI0_SCK","LPTMR0_ALT2","I2S0_RXD0","FB_AD10",  "CMP0_OUT", "-"                 }, // {1}
        {  "CMP0_IN0",     "PTC6/LLWU_P10","SPI0_SOUT","PDB0_EXTRG","I2S0_RX_BCLK","FB_AD9","I2S0_MCLK","-"                }, // {1}
        {  "CMP0_IN1",     "PTC7",  "SPI0_SIN",  "USB_SOF_OUT","I2S0_RX_FS",  "FB_AD8",    "-",        "-"                 }, // {1}
        {  "ADC1_SE4/CMP0_IN2","PTC8","-",       "-",          "I2S0_MCLK",   "FB_AD7",    "-",        "-"                 }, // {1}
        {  "ADC1_SE5/CMP0_IN3","PTC9","-",       "-",          "I2S0_RX_BCLK","FB_AD6",    "FTM2_FLT0","-"                 },
        {  "ADC1_SE6/CMP0_IN4","PTC10","I2C1_SCL","-",         "I2S0_RX_FS",  "FB_AD5",    "-",        "-"                 },
        {  "ADC1_SE7",     "PTC11/LLWU_P11","I2C1_SDA","-",    "I2S0_RXD",    "FB_RW",     "-",        "-"                 }, // {1}
        {  "-",            "PTC12", "-",         "UART4_RTS_b","-",           "FB_AD27",   "-",        "-"                 }, // {1}
        {  "-",            "PTC13", "-",         "UART4_CTS_b","-",           "FB_AD26",   "-",        "-"                 }, // {1}
        {  "-",            "PTC14", "-",         "UART4_RX",   "-",           "FB_AD25",   "-",        "-"                 }, // {1}
        {  "-",            "PTC15", "-",         "UART4_TX",   "-",           "FB_AD24",   "-",        "-"                 }, // {1}
        {  "-",            "PTC16", "CAN1_RX",   "UART3_RX",   "ENET_1588_TMR0","FB_CS5/FB_TSIZ1/FB_BE23_16_BLS15_8","-","-"},
        {  "-",            "PTC17", "CAN1_TX",   "UART3_TX",   "ENET_1588_TMR1","FB_CS4/FB_TSIZ0/FB_BE31_24_BLS7_0","-","-"},
        {  "-",            "PTC18", "-",         "UART3_RTS",  "ENET_1588_TMR2","FB_TBST/FB_CS2/FB_BE15_8_BLS23_16","-","-"},
        {  "-",            "PTC19", "-",         "UART3_CTS",  "ENET_1588_TMR3","FB_CS3/FB_BE7_0_BLS31_24","FB_TA","-"     },
    #endif
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 }
    },
    {
        // ALT 0           ALT 1    ALT2         ALT 3         ALT 4          ALT 5        ALT 6       ALT 7
    #if defined KINETIS_K64
        {  "-",            "PTD0/LLWU_P12","SPI0_PCS0", "UART2_RTS_b","FTM3_CH0","FB_ALE/FB_CS1/FB_TS","-","-"             }, // PORT D {1}
        {  "ADC0_SE5b",    "PTD1",  "SPI0_SCK",  "UART2_CTS_b", "FTM3_CH1",   "FB_CS0_b",  "-",        "-"                 },
        {  "-",            "PTD2/LLWU_P13","SPI0_SOUT","UART2_RX","FTM3_CH2", "FB_AD4",    "-",        "I2C0_SCL"          },
        {  "-",            "PTD3",  "SPI0_SIN",  "UART2_TX",   "FTM3_CH3",    "FB_AD3",    "-",        "I2C0_SDA"          },
        {  "-",            "PTD4/LLWU_P14","SPI0_PCS1","UART0_RTS_b","FTM0_CH4","FB_AD2",  "EWM_IN",   "SPI1_PCS0"         },
        {  "ADC0_SE6b",    "PTD5",  "SPI0_PCS2", "UART0_CTS_b/UART0_COL_b","FTM0_CH5","FB_AD1","EWM_OUT_b","-"             },
        {  "ADC0_SE7b",    "PTD6/LLWU_P15","SPI0_PCS3","UART0_RX","FTM0_CH6", "FB_AD0",    "FTM0_FLT0","SPI1_SOUT"         },
        {  "-",            "PTD7",  "CMT_IRO",   "UART0_TX",   "FTM0_CH7",    "-",         "FTM0_FLT1","SPI1_IN"           },
        {  "-",            "PTD8",  "I2C0_SCL",  "UART5_RX",   "-",           "-",         "FB_A16",   "-"                 },
        {  "-",            "PTD9",  "I2C0_SDA",  "UART5_TX",   "-",           "-",         "FB_A17",   "-"                 },
        {  "-",            "PTD10", "-",         "UART5_RTS_b","-",           "-",         "FB_A18",   "-"                 },
        {  "-",            "PTD11", "SPI2_PCS0", "UART5_CTS_b","SDHC0_CLKIN", "-",         "FB_A19",   "-"                 },
        {  "-",            "PTD12", "SPI2_SCK",  "FTM3_FLT0",  "SDHC0_D4",    "-",         "FB_A20",   "-"                 },
        {  "-",            "PTD13", "SPI2_SOUT", "-",          "SDHC0_D5",    "-",         "FB_A21",   "-"                 },
        {  "-",            "PTD14", "SPI2_SIN",  "-",          "SDHC0_D6",    "-",         "FB_A22",   "-"                 },
        {  "-",            "PTD15", "SPI2_PCS1", "-",          "SDHC0_D7",    "-",         "FB_A23",   "-"                 },
    #else
        {  "-",            "PTD0/LLWU_P12","SPI0_PCS0", "UART2_RTS", "-",     "FB_ALE/FB_CS1/FB_TS","-","-"                }, // PORT D {1}
        {  "ADC0_SE5",     "PTD1",  "SPI0_SCK",  "UART2_CTS",  "-",           "FB_CS0",    "-",        "-"                 },
        {  "-",            "PTD2/LLWU_P13","SPI0_SOUT","UART2_RX","-",        "FB_AD4",    "-",        "-"                 }, // {1}
        {  "-",            "PTD3",  "SPI0_SIN",  "UART2_TX",   "-",           "FB_AD3",    "-",        "-"                 },
        {  "-",            "PTD4/LLWU_P14","SPI0_PCS1","UART0_RTS","FTM0_CH4","FB_AD2",    "EWM_IN",   "-"                 }, // {1}
        {  "ADC0_SE6",     "PTD5",  "SPI0_PCS2", "UART0_CTS",  "FTM0_CH5",    "FB_AD1",    "EWM_OUT",  "-"                 },
        {  "ADC0_SE7",     "PTD6/LLWU_P15","SPI0_PCS3","UART0_RX","FTM0_CH6", "FB_AD0",    "FTM0_FLT0","-"                 }, // {1}
        {  "-",            "PTD7",  "CMT_IRO",   "UART0_TX",   "FTM0_CH7",    "-",         "FTM0_FLT1","-"                 },
        {  "-",            "PTD8",  "I2C0_SCL",  "UART5_RX",   "-",           "-",         "FB_A16",   "-"                 },
        {  "-",            "PTD9",  "I2C0_SDA",  "UART5_TX",   "-",           "-",         "FB_A17",   "-"                 },
        {  "-",            "PTD10", "-",         "UART5_RTS",  "-",           "-",         "FB_A18",   "-"                 },
        {  "-",            "PTD11", "SPI2_PCS0", "UART5_CTS",  "SDHC0_CLKIN", "-",         "FB_A19",   "-"                 },
        {  "-",            "PTD12", "SPI2_SCK",  "-",          "SDHC0_D4",    "-",         "FB_A20",   "-"                 },
        {  "-",            "PTD13", "SPI2_SOUT", "-",          "SDHC0_D5",    "-",         "FB_A21",   "-"                 },
        {  "-",            "PTD14", "SPI2_SIN",  "-",          "SDHC0_D6",    "-",         "FB_A22",   "-"                 },
        {  "-",            "PTD15", "SPI2_PCS1", "-",          "SDHC0_D7",    "-",         "FB_A23",   "-"                 },
    #endif
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 }
    },
    {
        // ALT 0           ALT 1    ALT2         ALT 3         ALT 4          ALT 5        ALT 6       ALT 7
    #if defined KINETIS_K64
        {  "ADC1_SE4a",     "PTE0",  "SPI1_PCS1", "UART1_TX",   "SDHC0_D1",   "TRACE_CLKOUT","I2C1_SDA","RTC_CLKOUT"       }, // PORT E
        {  "ADC1_SE5a",     "PTE1/LLWU_P0","SPI1_SOUT","UART1_RX","SDHC0_D0", "TRACE_D3",  "I2C1_SCL", "SPI1_SIN"          }, 
        {  "ADC0_DP2/ADC1_SE6a","PTE2/LLWU_P1","SPI1_SCK","UART1_CTS_b","SDHC0_DCLK","TRACE_D2","-",   "-"                 },
        {  "ADC0_DM2/ADC1_SE7a","PTE3","SPI1_SIN","UART1_RTS_b","SDHC0_CMD",  "TRACE_D1",  "-",        "SPI1_SOUT"         },
        {  "-",            "PTE4/LLWU_P2","SPI1_PCS0","UART3_TX","SDHC0_D3",  "TRACE_D0",  "-",        "-"                 },
        {  "-",            "PTE5",  "SPI1_PCS2", "UART3_RX",   "SDHC0_D2",    "-",         "FTM3_CH0", "-"                 },
        {  "-",            "PTE6",  "SPI1_PCS3", "UART3_CTS_b","I2S0_MCLK",   "-",         "FTM3_CH1", "USB_SOF_OUT"       },
        {  "-",            "PTE7",  "-",         "UART3_RTS_b","I2S0_RXD",    "-",         "FTM3_CH2", "-"                 },
        {  "-",            "PTE8",  "I2S0_RXD1", "UART5_TX",   "I2S0_RX_FS",  "-",         "FTM3_CH3", "-"                 },
        {  "-",            "PTE9",  "I2S0_RXD1", "UART5_RX",   "I2S0_RX_BCLK","-",         "FTM3_CH4", "-"                 },
        {  "-",            "PTE10", "-",         "UART5_CTS_b","I2S0_TXD0",   "-",         "FTM3_CH5", "-"                 },
        {  "-",            "PTE11", "-",         "UART5_RTS_b","I2S0_TX_FS",  "-",         "FTM3_CH6", "-"                 },
        {  "-",            "PTE12", "-",         "-",          "I2S0_TX_BCLK","-",         "FTM3_CH7", "-"                 },
    #else
        {  "ADC1_SE4",     "PTE0",  "SPI1_PCS1", "UART1_TX",   "SDHC0_D1",    "-",         "I2C1_SDA", "RTC_CLKOUT"        }, // PORT E {1}
        {  "ADC1_SE5",     "PTE1/LLWU_P0","SPI1_SOUT","UART1_RX","SDHC0_D0",  "-",         "I2C1_SCL", "SPI1_SIN"          }, // {1}
        {  "ADC1_SE6",     "PTE2/LLWU_P1","SPI1_SCK","UART1_CTS","SDHC0_DCLK","-",         "-",        "-"                 }, // {1}
        {  "ADC1_SE7",     "PTE3",  "SPI1_SIN",  "UART1_RTS",  "SDHC0_CMD",   "-",         "-",        "SPI1_SOUT"         }, // {1}
        {  "-",            "PTE4/LLWU_P2","SPI1_PCS0","UART3_TX","SDHC0_D3",  "-",         "-",        "-"                 }, // {1}
        {  "-",            "PTE5",  "SPI1_PCS2", "UART3_RX",   "SDHC0_D2",    "-",         "-",        "-"                 },
        {  "-",            "PTE6",  "SPI1_PCS3", "UART3_CTS",  "I2S0_MCLK",   "-",         "-",        "USB_SOF_OUT"       }, // {1}
        {  "-",            "PTE7",  "-",         "UART3_RTS",  "I2S0_RXD",    "-",         "-",        "-"                 },
        {  "-",            "PTE8",  "-",         "UART5_TX",   "I2S0_RX_FS",  "-",         "-",        "-"                 },
        {  "-",            "PTE9",  "-",         "UART5_RX",   "I2S0_RX_BCLK","-",         "-",        "-"                 },
        {  "-",            "PTE10", "-",         "UART5_CTS",  "I2S0_TXD",    "-",         "-",        "-"                 },
        {  "-",            "PTE11", "-",         "UART5_RTS",  "I2S0_TX_FS",  "-",         "-",        "-"                 },
        {  "-",            "PTE12", "-",         "-",          "I2S0_TX_BCLK","-",         "-",        "-"                 },
    #endif
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
    #if defined KINETIS_K64
        {  "ADC0_SE17",    "PTE24", "-",         "UART4_TX",   "-",           "I2C0_SCL",  "EWM_OUT_b","-"                 },
        {  "ADC0_SE18",    "PTE25", "-",         "UART4_RX",   "-",           "I2C0_SDA",  "EWM_IN",   "-"                 },
        {  "-",            "PTE26", "ENET_1588_CLKIN", "UART4_CTS_b","-",     "-",         "RTC_CLKOUT","USB_CLKIN"        },
        {  "-",            "PTE27", "-",         "UART4_RTS_b","-",           "-",         "-",        "-"                 },
        {  "-",            "PTE28", "-",         "-",          "-",           "-",         "-",        "-"                 },
    #else
        {  "ADC0_SE17",    "PTE24", "CAN1_TX",   "UART4_TX",   "-",           "-",         "EWM_OUT_b","-"                 }, // {1}
        {  "ADC0_SE18",    "PTE25", "CAN1_RX",   "UART4_RX",   "-",           "-",         "EWM_IN",   "-"                 },
        {  "-",            "PTE26", "ENET_1588_CLKIN", "UART4_CTS_b","-",     "-",         "RTC_CLKOUT","USB_CLKIN"        }, // {1}
        {  "-",            "PTE27", "-",         "UART4_RTS",  "-",           "-",         "-",        "-"                 },
        {  "-",            "PTE28", "-",         "-",          "-",           "-",         "-",        "-"                 },
    #endif
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 },
        {  "-",            "-",     "-",         "-",          "-",           "-",         "-",        "-"                 }
    }
};
#endif
