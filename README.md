> [!IMPORTANT]
> このライブラリは現在試験段階及び、個人利用目的です。このライブラリの使用による機器の破損、製品のバグなどに関しては一切責任を負うことはできません。
> This library is currently in the testing phase and is for personal use only. We are not responsible for any damage to equipment or bugs in the product that may result from the use of this library.

# KT0937-D8lib
This library for SDR radio chip "KT0937-D8"

# KT0937-D8 ラジオチップライブラリ

## 概要

このライブラリは、KT Micro社のKT0937-D8 FM/MW/SW受信機チップを制御するためのArduino互換ライブラリです。KT0937-D8は、高性能なシングルチップラジオ受信機ICで、FMおよびAM（MW/SW）バンドをサポートしています。

## 特徴

- FM、MW、SWバンドのサポート
- 簡単な周波数設定
- ボリューム制御
- ミュート機能
- RSSI（受信信号強度）とSNR（信号対雑音比）の読み取り
- AFCとソフトミュート機能
- RDS（Radio Data System）のサポート
- 低消費電力モード
- 詳細な設定オプション

## インストール

1. このリポジトリをZIPファイルとしてダウンロードします。
2. Arduinoの「スケッチ(inoファイル)」のあるディレクトリに直接この2つファイルを入れてください。

## 使用方法

```cpp
#include "KT0937_D8.h"

void setup() {
  Serial.begin(115200);
  
  // KT0937-D8の初期化（I2CピンはArduinoボードに応じて変更してください）
  if (kt0937_init(SDA, SCL) != KT0937_D8_Error::OK) {
    Serial.println("KT0937-D8の初期化に失敗しました");
    while (1);
  }
  
  // FMモードに設定
  kt0937_setMode(KT0937_D8_Mode::FM);
  
  // 周波数を設定（例：90.0MHz）
  kt0937_setFrequency(90000);
  
  // ボリュームを設定（0-31）
  kt0937_setVolume(20);
}

void loop() {
  // RSSIを読み取る
  uint8_t rssi;
  if (kt0937_getRSSI(&rssi) == KT0937_D8_Error::OK) {
    Serial.print("RSSI: ");
    Serial.println(rssi);
  }
  
  delay(1000);
}
```
## ドキュメント
~~より詳細な使用方法や関数のリファレンスについては、Wikiを参照してください。~~
## ライセンス
このライブラリはMITライセンスの下で公開されています。
## 貢献
バグ報告や機能リクエストは、GitHubのIssueページにお願いします。プルリクエストも歓迎します。このライブラリおよびモジュールを作成するにあたり、知恵袋のユーザーであるogu******さんに感謝申し上げます。

## PCBファイル(基盤データ)に関して
KT0937-D8のデータシートのApprication Circuitを再現した、PCBファイルを作成しました。発注する場合、「g」から始まるデータと、「.drl」ファイルをすべてzipファイルに入れてください。使用する部品は以下の通りです。

| Reference | Value | Datasheet | Footprint | Qty | DNP |
|-----------|--------|-----------|------------|-----|-----|
| C1 | 100pF | ~ | Capacitor_THT:C_Radial_D5.0mm_H5.0mm_P2.00mm | 1 | |
| C2,C4 | 0.1uF | ~ | Capacitor_THT:C_Radial_D5.0mm_H5.0mm_P2.00mm | 2 | |
| C3 | 47nF | ~ | Capacitor_THT:C_Radial_D5.0mm_H5.0mm_P2.00mm | 1 | |
| C5,C6 | 24pF | ~ | Capacitor_THT:C_Radial_D5.0mm_H5.0mm_P2.00mm | 2 | |
| C7,C8 | 125uF | ~ | Capacitor_THT:CP_Radial_D8.0mm_P3.50mm | 2 | |
| C9,C10,C11 | 10uF | ~ | -- ミックスされた値 -- | 3 | |
| C12,C13,C14 | 4.7uF | ~ | Capacitor_THT:C_Radial_D5.0mm_H5.0mm_P2.00mm | 3 | |
| D1,D2 | D | ~ | Diode_THT:D_DO-35_SOD27_P7.62mm_Horizontal | 2 | |
| J1 | Conn_01x04_Pin | ~ | Connector_PinHeader_2.54mm:PinHeader_1x04_P2.54mm_Horizontal | 1 | |
| J2,J3 | AudioJack3 | ~ | Connector_Audio:Jack_3.5mm_CUI_SJ-3523-SMT_Horizontal | 2 | |
| J4 | Conn_01x02_Pin | ~ | Connector_PinHeader_2.54mm:PinHeader_1x02_P2.54mm_Horizontal | 1 | |
| KT1 | ~ | | Package_SO:SSOP-16_3.9x4.9mm_P0.635mm | 1 | |
| L1 | 2.2uH | ~ | Inductor_THT:L_Axial_L5.3mm_D2.2mm_P7.62mm_Horizontal_Vishay_IM-1 | 1 | |
| Q1 | 2N3904 | https://www.onsemi.com/pub/Collateral/2N3903-D.PDF | Package_TO_SOT_THT:TO-92_Inline | 1 | |
| R1 | 4.7KΩ | ~ | Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal | 1 | |
| R2 | 4.7kΩ | ~ | Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal | 1 | |
| R3,R4,R5,R6,R7,R8 | 10kΩ | ~ | Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal | 6 | |
| R9,R10 | 100kΩ | ~ | Resistor_THT:R_Axial_DIN0207_L6.3mm_D2.5mm_P7.62mm_Horizontal | 2 | |
| SW1,SW2 | SW_Wuerth_450301014042 | https://www.we-online.com/components/products/datasheet/450301014042.pdf | Button_Switch_THT:SW_Slide-03_Wuerth-WS-SLTV_10x2.5x6.4_P2.54mm | 2 | |
| Y1 | Crystal | ~ | Crystal:Crystal_AT310_D3.0mm_L10.0mm_Horizontal | 1 | |


# KT0937-D8 Radio Chip Library
## Overview
This library is an Arduino-compatible library for controlling the KT Micro KT0937-D8 FM/MW/SW receiver chip. The KT0937-D8 is a high-performance single-chip radio receiver IC that supports FM and AM (MW/SW) bands.
Features

- Support for FM, MW, and SW bands
- Easy frequency setting
- Volume control
- Mute function
- RSSI (Received Signal Strength Indicator) and SNR (Signal-to-Noise Ratio) reading
- AFC and soft mute functions
- RDS (Radio Data System) support
- Low power mode
- Detailed configuration options

## Installation

1. Download this repository as a ZIP file.
2. Put these two files directly into the directory where the Arduino “sketch (ino file)” is located.

Usage
```cpp
#include "KT0937_D8.h"

void setup() {
  Serial.begin(115200);
  
  // Initialize KT0937-D8 (change I2C pins according to your Arduino board)
  if (kt0937_init(SDA, SCL) != KT0937_D8_Error::OK) {
    Serial.println("Failed to initialize KT0937-D8");
    while (1);
  }
  
  // Set to FM mode
  kt0937_setMode(KT0937_D8_Mode::FM);
  
  // Set frequency (e.g., 90.0MHz)
  kt0937_setFrequency(90000);
  
  // Set volume (0-31)
  kt0937_setVolume(20);
}

void loop() {
  // Read RSSI
  uint8_t rssi;
  if (kt0937_getRSSI(&rssi) == KT0937_D8_Error::OK) {
    Serial.print("RSSI: ");
    Serial.println(rssi);
  }
  
  delay(1000);
}
```

## Documentation
~~For more detailed usage instructions and function references, please refer to the Wiki.~~
## License
This library is released under the MIT License.
## Contributing
Please report bugs or feature requests on the GitHub Issues page. Pull requests are also welcome. We would like to thank ogu******, a user of *Yahoo Chiebukuro*, for his help in creating this library and module.
