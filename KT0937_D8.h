#ifndef KT0937_D8_H
#define KT0937_D8_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// エラーコード
enum class KT0937_D8_Error {
    OK = 0,
    ERROR_I2C,
    ERROR_PARAM,
    ERROR_TIMEOUT,
    ERROR_DEVICE
};

// 受信モード
enum class KT0937_D8_Mode {
    FM = 0,
    MW,
    SW
};

// FM空間
enum class KT0937_D8_FMSpace {
    SPACE_100KHZ = 0,
    SPACE_200KHZ,
    SPACE_50KHZ
};

// AM空間
enum class KT0937_D8_AMSpace {
    SPACE_1KHZ = 0,
    SPACE_9KHZ,
    SPACE_10KHZ
};

// SW空間
enum class KT0937_D8_SWSpace {
    SPACE_1KHZ = 0,
    SPACE_5KHZ,
    SPACE_9KHZ,
    SPACE_10KHZ
};

// 関数プロトタイプ
KT0937_D8_Error kt0937_init(int sda_pin, int scl_pin);
KT0937_D8_Error kt0937_setMode(KT0937_D8_Mode mode);
KT0937_D8_Error kt0937_setFrequency(uint32_t frequency);
KT0937_D8_Error kt0937_setVolume(uint8_t volume);
KT0937_D8_Error kt0937_setMute(bool mute);
KT0937_D8_Error kt0937_getRSSI(int8_t *rssi);
KT0937_D8_Error kt0937_getSNR(uint8_t *snr);
KT0937_D8_Error kt0937_isStereo(bool *is_stereo);
KT0937_D8_Error kt0937_setAFC(bool enable);
KT0937_D8_Error kt0937_setSoftMute(bool enable);
KT0937_D8_Error kt0937_setBass(uint8_t bass_boost);
KT0937_D8_Error kt0937_setFMSpace(KT0937_D8_FMSpace space);
KT0937_D8_Error kt0937_setAMSpace(KT0937_D8_AMSpace space);
KT0937_D8_Error kt0937_setSWSpace(KT0937_D8_SWSpace space);
KT0937_D8_Error kt0937_isChannelValid(bool *is_valid);
KT0937_D8_Error kt0937_setFMStereoBlend(uint8_t start_level, uint8_t stop_level);
KT0937_D8_Error kt0937_setAMChannelFilter(uint8_t bandwidth);
KT0937_D8_Error kt0937_setStandby(bool enable);
KT0937_D8_Error kt0937_configureInterrupt(bool enable, bool active_high, bool edge_triggered);
KT0937_D8_Error kt0937_setKeyMode(void);
KT0937_D8_Error kt0937_setDialMode(void);
KT0937_D8_Error kt0937_setAudioGain(uint8_t gain);
KT0937_D8_Error kt0937_setCrystalFrequency(uint32_t frequency);
KT0937_D8_Error kt0937_setDeemphasis(bool is_75us);
KT0937_D8_Error kt0937_performAntennaTuning(void);
KT0937_D8_Error kt0937_getCarrierFrequencyOffset(int16_t *offset);
KT0937_D8_Error kt0937_configureSoftMute(uint8_t start_rssi, uint8_t slope_rssi, uint8_t start_snr, uint8_t slope_snr, uint8_t min_gain);
KT0937_D8_Error kt0937_startSeek(bool up, bool wrap);
KT0937_D8_Error kt0937_checkSeekStatus(bool *complete, bool *failed);
KT0937_D8_Error kt0937_setRDS(bool enable);
KT0937_D8_Error kt0937_readRDS(uint16_t *block_a, uint16_t *block_b, uint16_t *block_c, uint16_t *block_d);
KT0937_D8_Error kt0937_set3DSound(uint8_t level);
KT0937_D8_Error kt0937_setLowPowerMode(bool enable);
KT0937_D8_Error kt0937_getChipInfo(uint16_t *chip_id, uint8_t *version);

const char* kt0937_errorToString(KT0937_D8_Error error);
void kt0937_printDebugInfo(void (*print_func)(const char*));
void kt0937_printRegister(uint8_t reg, void (*print_func)(const char*));
void kt0937_dumpAllRegisters(void (*print_func)(const char*));

#ifdef __cplusplus
}
#endif

#endif // KT0937_D8_H