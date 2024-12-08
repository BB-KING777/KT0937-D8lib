#ifndef KT0937_D8_H
#define KT0937_D8_H

#include <stdint.h>

#define KT0937_D8_ADDR 0x35

// レジスタアドレス
#define REG_DEVICEID0 0x00
#define REG_DSPCFG5 0x002F
#define REG_RXCFG0 0x0E
#define REG_RXCFG1 0x0F
#define REG_BANDCFG0 0x16
#define REG_BANDCFG2 0x18
#define REG_BANDCFG3 0x19
#define REG_MUTECFG0 0x1A
#define REG_SOFTMUTE2 0x1F
#define REG_SOFTMUTE5 0x22
#define REG_SOUNDCFG 0x28
#define REG_DSPCFG0 0x2A
#define REG_DSPCFG1 0x2B
#define REG_DSPCFG2 0x2C
#define REG_AFC2 0x3E
#define REG_ANACFG 0x4E
#define REG_GPIOCFG2 0x51
#define REG_AMDSP0 0x62
#define REG_FMCHAN0 0x88
#define REG_FMCHAN1 0x89
#define REG_STATUS0 0xDE
#define REG_STATUS4 0xE2
#define REG_STATUS8 0xE6
#define REG_AFC_STATUS1 0xE9

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

// チャンネルスペース設定の詳細オプション
enum class KT0937_D8_FMSpaceDetail {
    SPACE_200KHZ = 0, // USA, Europe
    SPACE_100KHZ = 1, // Europe, Japan 
    SPACE_50KHZ = 2
};

enum class KT0937_D8_AMSpaceDetail {
    SPACE_1KHZ = 0,
    SPACE_9KHZ = 1, // Europe, Asia
    SPACE_10KHZ = 2 // USA
};

enum class KT0937_D8_SWSpaceDetail {
    SPACE_1KHZ = 0,
    SPACE_5KHZ = 1,
    SPACE_9KHZ = 2,
    SPACE_10KHZ = 3
};

// オーディオ品質設定構造体
struct AudioQualityConfig {
    uint8_t stereoBlendStart;
    uint8_t stereoBlendStop;
    uint8_t softmuteStartRSSI;
    uint8_t softmuteStartSNR;
    uint8_t softmuteSlopeRSSI;
    uint8_t softmuteSlopeSNR;
    uint8_t bassBoost;
    uint8_t audioGain;
};

// 保護状態構造体
struct ProtectionStatus {
    bool voltageLow;
    bool temperatureHigh;
    bool antennaError;
    int8_t temperature;
    uint16_t voltage;
};

// 自動チューニング設定構造体
struct AutoTuneConfig {
    uint8_t minRSSI;
    uint8_t minSNR;
    uint8_t channelSpacing;
    uint32_t startFreq;
    uint32_t endFreq;
    bool seekUp;
    bool wrapAround;
};

// 自動チューニング結果構造体
struct AutoTuneResult {
    uint32_t frequency;
    int8_t rssi;
    uint8_t snr;
    bool isValid;
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
KT0937_D8_Error kt0937_readRegister(uint8_t reg, uint8_t *value);
KT0937_D8_Error kt0937_writeRegister(uint8_t reg, uint8_t value);
KT0937_D8_Error kt0937_getFrequency(uint32_t *frequency);
KT0937_D8_Error kt0937_setDetailedSpacing(KT0937_D8_Mode mode, uint8_t spacing);
KT0937_D8_Error kt0937_setAudioQuality(const AudioQualityConfig& config);
KT0937_D8_Error kt0937_getProtectionStatus(ProtectionStatus* status);
KT0937_D8_Error kt0937_autoTune(const AutoTuneConfig& config, AutoTuneResult* results, uint8_t maxResults, uint8_t* numFound);

const char* kt0937_errorToString(KT0937_D8_Error error);
void kt0937_printDebugInfo(void (*print_func)(const char*));
void kt0937_printRegister(uint8_t reg, void (*print_func)(const char*));
void kt0937_dumpAllRegisters(void (*print_func)(const char*));

#ifdef __cplusplus
}
#endif

#endif // KT0937_D8_H