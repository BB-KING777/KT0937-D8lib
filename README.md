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
