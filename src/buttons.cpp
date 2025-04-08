#include "buttons.h"
#include "mosfet.h"
#include "mqtt.h"
#include "main.h"

Button2 btnCh0Up, btnCh1Up, btnCh2Up, btnCh3Up, btnCh0Down, btnCh1Down, btnCh2Down, btnCh3Down;

void buttonClickHandler(Button2 &btn)
{
    if (btn == btnCh0Up)
        if (appSettings.flipButtons)
            DecreaseLEDGamma(0);
        else
            IncreaseLEDGamma(0);

    if (btn == btnCh0Down)
        if (appSettings.flipButtons)
            IncreaseLEDGamma(0);
        else
            DecreaseLEDGamma(0);

    if (btn == btnCh1Up)
        if (appSettings.flipButtons)
            DecreaseLEDGamma(1);
        else
            IncreaseLEDGamma(1);

    if (btn == btnCh1Down)
        if (appSettings.flipButtons)
            IncreaseLEDGamma(1);
        else
            DecreaseLEDGamma(1);

    if (btn == btnCh2Up)
        if (appSettings.flipButtons)
            DecreaseLEDGamma(2);
        else
            IncreaseLEDGamma(2);

    if (btn == btnCh2Down)
        if (appSettings.flipButtons)
            IncreaseLEDGamma(2);
        else
            DecreaseLEDGamma(2);

    if (btn == btnCh3Up)
        if (appSettings.flipButtons)
            DecreaseLEDGamma(3);
        else
            IncreaseLEDGamma(3);

    if (btn == btnCh3Down)
        if (appSettings.flipButtons)
            IncreaseLEDGamma(3);
        else
            DecreaseLEDGamma(3);
}

void buttonDoubleClickHandler(Button2 &btn)
{
}

void buttonTripleClickHandler(Button2 &btn)
{
    if (btn == btnCh0Up)
        if (appSettings.flipButtons)
            MinLEDGamma(0);
        else
            MaxLEDGamma(0);

    if (btn == btnCh0Down)
        if (appSettings.flipButtons)
            MaxLEDGamma(0);
        else
            MinLEDGamma(0);
    if (btn == btnCh1Up)
        if (appSettings.flipButtons)
            MinLEDGamma(1);
        else
            MaxLEDGamma(1);
    if (btn == btnCh1Down)
        if (appSettings.flipButtons)
            MaxLEDGamma(1);
        else
            MinLEDGamma(1);
    if (btn == btnCh2Up)
        if (appSettings.flipButtons)
            MinLEDGamma(2);
        else
            MaxLEDGamma(2);
    if (btn == btnCh2Down)
        if (appSettings.flipButtons)
            MaxLEDGamma(2);
        else
            MinLEDGamma(2);
    if (btn == btnCh3Up)
        if (appSettings.flipButtons)
            MinLEDGamma(3);
        else
            MaxLEDGamma(3);
    if (btn == btnCh3Down)
        if (appSettings.flipButtons)
            MaxLEDGamma(3);
        else
            MinLEDGamma(3);
}

void buttonLongClickHandler(Button2 &btn)
{
    if ((btn == btnCh0Up) || (btn == btnCh1Up) || (btn == btnCh2Up) || (btn == btnCh3Up))
    {
        for (size_t i = 0; i < NUMBER_OF_CHANNELS; i++)
            if (appSettings.flipButtons)
                MinLEDGamma(i);
            else
                MaxLEDGamma(i);
    }
    if ((btn == btnCh0Down) || (btn == btnCh1Down) || (btn == btnCh2Down) || (btn == btnCh3Down))
    {
        for (size_t i = 0; i < NUMBER_OF_CHANNELS; i++)
            if (appSettings.flipButtons)
                MaxLEDGamma(i);
            else
                MinLEDGamma(i);
    }
}

void setupButtons()
{
    btnCh0Up.begin(BUTTON1_GPIO);
    btnCh1Up.begin(BUTTON3_GPIO);
    btnCh2Up.begin(BUTTON5_GPIO);
    btnCh3Up.begin(BUTTON7_GPIO);

    btnCh0Down.begin(BUTTON0_GPIO);
    btnCh1Down.begin(BUTTON2_GPIO);
    btnCh2Down.begin(BUTTON4_GPIO);
    btnCh3Down.begin(BUTTON6_GPIO);

    btnCh0Up.setClickHandler(buttonClickHandler);
    btnCh1Up.setClickHandler(buttonClickHandler);
    btnCh2Up.setClickHandler(buttonClickHandler);
    btnCh3Up.setClickHandler(buttonClickHandler);

    btnCh0Down.setClickHandler(buttonClickHandler);
    btnCh1Down.setClickHandler(buttonClickHandler);
    btnCh2Down.setClickHandler(buttonClickHandler);
    btnCh3Down.setClickHandler(buttonClickHandler);

    btnCh0Up.setDoubleClickHandler(buttonDoubleClickHandler);
    btnCh1Up.setDoubleClickHandler(buttonDoubleClickHandler);
    btnCh2Up.setDoubleClickHandler(buttonDoubleClickHandler);
    btnCh3Up.setDoubleClickHandler(buttonDoubleClickHandler);

    btnCh0Down.setDoubleClickHandler(buttonDoubleClickHandler);
    btnCh1Down.setDoubleClickHandler(buttonDoubleClickHandler);
    btnCh2Down.setDoubleClickHandler(buttonDoubleClickHandler);
    btnCh3Down.setDoubleClickHandler(buttonDoubleClickHandler);

    btnCh0Up.setLongClickDetectedHandler(buttonLongClickHandler);
    btnCh1Up.setLongClickDetectedHandler(buttonLongClickHandler);
    btnCh2Up.setLongClickDetectedHandler(buttonLongClickHandler);
    btnCh3Up.setLongClickDetectedHandler(buttonLongClickHandler);

    btnCh0Down.setLongClickDetectedHandler(buttonLongClickHandler);
    btnCh1Down.setLongClickDetectedHandler(buttonLongClickHandler);
    btnCh2Down.setLongClickDetectedHandler(buttonLongClickHandler);
    btnCh3Down.setLongClickDetectedHandler(buttonLongClickHandler);

    btnCh0Up.setTripleClickHandler(buttonTripleClickHandler);
    btnCh1Up.setTripleClickHandler(buttonTripleClickHandler);
    btnCh2Up.setTripleClickHandler(buttonTripleClickHandler);
    btnCh3Up.setTripleClickHandler(buttonTripleClickHandler);

    btnCh0Down.setTripleClickHandler(buttonTripleClickHandler);
    btnCh1Down.setTripleClickHandler(buttonTripleClickHandler);
    btnCh2Down.setTripleClickHandler(buttonTripleClickHandler);
    btnCh3Down.setTripleClickHandler(buttonTripleClickHandler);
}

void loopButtons()
{
    btnCh0Up.loop();
    btnCh1Up.loop();
    btnCh2Up.loop();
    btnCh3Up.loop();

    btnCh0Down.loop();
    btnCh1Down.loop();
    btnCh2Down.loop();
    btnCh3Down.loop();
}