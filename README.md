# ESP32 老式电视红外遥控器

用 ESP32-S3 + 红外收发模块控制老式（非智能）电视：开关、换台、音量等。
支持学习原装遥控器的红外编码并回放，手机连本地网页即可遥控。

姊妹项目：[ac-remote](https://github.com/samlaying/ac-remote)（同架构的 ESP32 空调遥控器），本项目沿用其
PlatformIO + IRremoteESP8266 + 本地网页的架构，接线、配网、API 设计保持一致。

## 功能规划

- [ ] 手机本地网页遥控（开关、换台、音量、菜单）
- [ ] 学习原装遥控器红外编码并存储
- [ ] 已知协议电视直接按协议发送（NEC / Sony / RC5 / RC6 等 80+）
- [ ] JSON API，可对接定时任务或语音助手

## 技术选型（来自调研）

| 项目 | 平台 | 适合场景 | 结论 |
|------|------|---------|------|
| [IRremoteESP8266](https://github.com/crankyoldgit/IRremoteESP8266) | ESP8266/ESP32 | 全功能电视遥控，80+ 协议 | **已采用**，生态最成熟 |
| [ESPIR](https://github.com/pjpeter/ESPIR) | ESP32 + Android App | BLE + 录制回放 | 参考"录制 + 回放"的思路 |
| [RemoteESP32](https://github.com/YujioNako/RemoteESP32) | ESP32 | 万能遥控器 | 备选参考 |
| ESPHome `remote_transmitter`/`remote_receiver` | ESP32 | 接入 Home Assistant | 后期可选，兼容现有生态 |
| TVBGone | Arduino | 一键关电视 | 不适合全功能控制，仅灵感来源 |

选型逻辑：老式电视协议多数未被 IRremoteESP8266 内置支持，因此核心路径是
**红外学习（接收原始码 → 存储）→ 回放（原始码发射）**；已知协议设备走协议直发。

## 接线（沿用 ac-remote）

- 接收器：OUT -> GPIO4，VCC -> 3V3，GND -> GND
- 发射器：DAT/OUT -> GPIO5，VCC -> 5Vin，GND -> GND

## 本地命令

```sh
pio run                # 编译
pio run --target upload
pio device monitor
```

## API（规划，与 ac-remote 对齐）

- `GET /api/state`：读取当前状态（频道、音量、电源）
- `POST /api/control`：发送控制指令
- `POST /api/learn`：进入学习模式，录制一个按键的红外码
- `GET /api/codes`：列出已学习的编码
