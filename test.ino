#include "KT0937_D8.h"

#define SDA_PIN 4
#define SCL_PIN 5

uint8_t volume = 15;
uint32_t frequency = 90000;
KT0937_D8_Mode currentMode = KT0937_D8_Mode::FM;
bool isJapanese = true;

const char* const messages[][2] = {
    {"KT0937-D8 ラジオコントロール", "KT0937-D8 Radio Control"},
    {"初期化に失敗しました", "Initialization failed"},
    {"音量", "Volume"},
    {"周波数", "Frequency"},
    {"モード", "Mode"},
    {"現在の設定", "Current settings"},
    {"ステレオ", "Stereo"},
    {"はい", "Yes"},
    {"いいえ", "No"},
    {"コマンドメニュー", "Command Menu"},
    {"音量アップ", "Volume up"},
    {"音量ダウン", "Volume down"},
    {"周波数アップ", "Frequency up"},
    {"周波数ダウン", "Frequency down"},
    {"FMモード", "FM mode"},
    {"AMモード", "AM mode"},
    {"このメニューを表示", "Show this menu"},
    {"言語切替", "Switch language"},
    {"周波数設定 (kHz)", "Set frequency (kHz)"},
    {"無効な周波数です", "Invalid frequency"},
    {"設定に失敗しました", "Setting failed"}
};

const char* getMessage(int index) {
    return messages[index][isJapanese ? 0 : 1];
}

void printMessage(int index) {
    Serial.println(getMessage(index));
}

KT0937_D8_Error checkAndPrintError(KT0937_D8_Error err) {
    if (err != KT0937_D8_Error::OK) {
        Serial.print(getMessage(20));
        Serial.print(": ");
        Serial.println(kt0937_errorToString(err));
    }
    return err;
}

void setup() {
    Serial.begin(115200);
    while (!Serial);

    printMessage(0);

    KT0937_D8_Error err = kt0937_init(SDA_PIN, SCL_PIN);
    if (checkAndPrintError(err) != KT0937_D8_Error::OK) {
        return;
    }

    updateRadioSettings();
    printMenu();
}

void loop() {
    if (Serial.available()) {
        String input = Serial.readStringUntil('\n');
        input.trim();

        if (input.length() == 1) {
            handleSingleCharCommand(input[0]);
        } else if (input.startsWith("set ")) {
            handleFrequencyInput(input.substring(4));
        }
    }
}

void handleSingleCharCommand(char cmd) {
    switch (cmd) {
        case '+': changeVolume(1); break;
        case '-': changeVolume(-1); break;
        case 'u': changeFrequency(currentMode == KT0937_D8_Mode::FM ? 100 : 9); break;
        case 'd': changeFrequency(currentMode == KT0937_D8_Mode::FM ? -100 : -9); break;
        case 'f': switchMode(KT0937_D8_Mode::FM); break;
        case 'a': switchMode(KT0937_D8_Mode::MW); break;
        case 'm': printMenu(); break;
        case 'l': isJapanese = !isJapanese; printMenu(); break;
        default: printMessage(20); break;
    }
}

void handleFrequencyInput(String freqStr) {
    uint32_t newFreq = freqStr.toInt();
    if (currentMode == KT0937_D8_Mode::FM) {
        if (newFreq >= 76000 && newFreq <= 108000) {
            frequency = newFreq;
            KT0937_D8_Error err = kt0937_setFrequency(frequency);
            if (checkAndPrintError(err) == KT0937_D8_Error::OK) {
                Serial.println("Frequency set to " + String(frequency / 100.0, 1) + " MHz");
                verifyAndPrintSettings();
            }
        } else {
            printMessage(19);
        }
    } else {
        if (newFreq >= 522 && newFreq <= 1710) {
            frequency = newFreq;
            KT0937_D8_Error err = kt0937_setFrequency(frequency);
            if (checkAndPrintError(err) == KT0937_D8_Error::OK) {
                Serial.println("Frequency set to " + String(frequency) + " kHz");
                verifyAndPrintSettings();
            }
        } else {
            printMessage(19);
        }
    }
}

void changeVolume(int delta) {
    int newVolume = constrain(volume + delta, 0, 31);
    if (newVolume != volume) {
        volume = newVolume;
        if (checkAndPrintError(kt0937_setVolume(volume)) == KT0937_D8_Error::OK) {
            Serial.print(getMessage(2));
            Serial.print(": ");
            Serial.println(volume);
        }
    }
}

void changeFrequency(int delta) {
    uint32_t newFreq = frequency + delta;
    if ((currentMode == KT0937_D8_Mode::FM && newFreq >= 76000 && newFreq <= 108000) ||
        (currentMode == KT0937_D8_Mode::MW && newFreq >= 522 && newFreq <= 1710)) {
        frequency = newFreq;
        KT0937_D8_Error err = kt0937_setFrequency(frequency);
        if (checkAndPrintError(err) == KT0937_D8_Error::OK) {
            Serial.println("Frequency changed to " + String(frequency / (currentMode == KT0937_D8_Mode::FM ? 100.0 : 1.0), 1) + 
                           (currentMode == KT0937_D8_Mode::FM ? " MHz" : " kHz"));
            verifyAndPrintSettings();
        }
    } else {
        printMessage(19);
    }
}

void switchMode(KT0937_D8_Mode mode) {
    if (mode != currentMode) {
        currentMode = mode;
        frequency = (mode == KT0937_D8_Mode::FM) ? 90000 : 1000;
        KT0937_D8_Error err = kt0937_setMode(currentMode);
        if (checkAndPrintError(err) == KT0937_D8_Error::OK) {
            Serial.println(getMessage(currentMode == KT0937_D8_Mode::FM ? 14 : 15));
            updateRadioSettings();
        }
    }
}

void updateRadioSettings() {
    KT0937_D8_Error err;

    err = kt0937_setFrequency(frequency);
    if (checkAndPrintError(err) != KT0937_D8_Error::OK) return;

    err = kt0937_setVolume(volume);
    if (checkAndPrintError(err) != KT0937_D8_Error::OK) return;

    err = kt0937_setSoftMute(false);
    if (checkAndPrintError(err) != KT0937_D8_Error::OK) return;

    err = kt0937_setAFC(false);
    if (checkAndPrintError(err) != KT0937_D8_Error::OK) return;

    verifyAndPrintSettings();
}

void verifyAndPrintSettings() {
    uint32_t actualFreq;
    bool settingsCorrect = true;

    // モード確認
    uint8_t modeReg;
    if (kt0937_readRegister(REG_FMCHAN0, &modeReg) == KT0937_D8_Error::OK) {
        bool isFM = !(modeReg & 0x40);
        if ((currentMode == KT0937_D8_Mode::FM) != isFM) {
            settingsCorrect = false;
            Serial.println("Mode mismatch");
        }
    } else {
        settingsCorrect = false;
        Serial.println("Failed to read mode register");
    }

    // 周波数確認
    if (kt0937_getFrequency(&actualFreq) == KT0937_D8_Error::OK) {
        if (actualFreq != frequency) {
            settingsCorrect = false;
            Serial.println("Frequency mismatch: Actual = " + String(actualFreq) + ", Expected = " + String(frequency));
        }
    } else {
        settingsCorrect = false;
        Serial.println("Failed to read frequency");
    }

    // 音量確認
    uint8_t volumeReg;
    if (kt0937_readRegister(0x0F, &volumeReg) == KT0937_D8_Error::OK) {
        if ((volumeReg & 0x1F) != volume) {
            settingsCorrect = false;
            Serial.println("Volume mismatch");
        }
    } else {
        settingsCorrect = false;
        Serial.println("Failed to read volume register");
    }

    if (!settingsCorrect) {
        Serial.println(getMessage(20));
        return;
    }

    printMessage(5);
    Serial.print(getMessage(4));
    Serial.println(currentMode == KT0937_D8_Mode::FM ? " FM" : " AM");
    Serial.print(getMessage(3));
    Serial.print(": ");
    Serial.print(frequency / (currentMode == KT0937_D8_Mode::FM ? 100.0 : 1.0), 1);
    Serial.println(currentMode == KT0937_D8_Mode::FM ? " MHz" : " kHz");
    Serial.print(getMessage(2));
    Serial.print(": ");
    Serial.println(volume);

    int8_t rssi;
    kt0937_getRSSI(&rssi);
    Serial.print("RSSI: ");
    Serial.print(rssi);
    Serial.println(" dBm");

    uint8_t snr;
    kt0937_getSNR(&snr);
    Serial.print("SNR: ");
    Serial.println(snr);

    bool isStereo;
    kt0937_isStereo(&isStereo);
    Serial.print(getMessage(6));
    Serial.print(": ");
    Serial.println(isStereo ? getMessage(7) : getMessage(8));
}

void printMenu() {
    Serial.println("\n--- " + String(getMessage(9)) + " ---");
    Serial.println("+ : " + String(getMessage(10)));
    Serial.println("- : " + String(getMessage(11)));
    Serial.println("u : " + String(getMessage(12)));
    Serial.println("d : " + String(getMessage(13)));
    Serial.println("f : " + String(getMessage(14)));
    Serial.println("a : " + String(getMessage(15)));
    Serial.println("m : " + String(getMessage(16)));
    Serial.println("l : " + String(getMessage(17)));
    Serial.println("set [kHz] : " + String(getMessage(18)));
    Serial.println("---------------------");
}