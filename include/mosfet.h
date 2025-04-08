#ifndef MOSFET_H
#define MOSFET_H

#define NUMBER_OF_CHANNELS 4

#define MOSFET0_GPIO 19
#define MOSFET1_GPIO 21
#define MOSFET2_GPIO 22
#define MOSFET3_GPIO 23

// #define LEDC_FREQ 5600
#define LEDC_FREQ 3072
#define LEDC_RESOLUTION 8

void MaxLEDGamma(size_t chan);
void MinLEDGamma(size_t chan);
void IncreaseLEDGamma(size_t chan);
void DecreaseLEDGamma(size_t chan);
void SetLEDGamma(size_t chan, uint8_t value);

void setupMOSFET();
void loopMOSFET();

// Gamma brightness lookup table <https://victornpb.github.io/gamma-table-generator>

// gamma = 2.50 steps = 10 range = 0-255
const uint8_t LEDGamma_lut[10] = {
    0,
    1,
    6,
    16,
    34,
    59,
    93,
    136,
    190,
    255};

#endif
