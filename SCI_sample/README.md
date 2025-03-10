Renesas RX24T, RX64M, RX71M, RX65N, RX66T, RX72T, RX72N SCI (UART) sample
=========

[Japanese](READMEja.md)

## Overview
SCI (UART) sample program using RX microcontroller
   
## Project list
 - main.cpp
 - RX24T/Makefile
 - RX64M/Makefile
 - RX71M/Makefile
 - RX65N/Makefile
 - RX66T/Makefile
 - RX72T/Makefile
 - RX72N/Makefile
   
## Hardware preparation (general)
 - If the base crystal is different, change the typedef parameter.
 - Makefile declares the set frequency for each module.
 - RX24T:  80MHz (10MHz)
 - RX64M: 120MHz (12MHz)
 - RX71M: 240MHz (12MHz)
 - RX65N: 120MHz (12MHz)
 - RX66T: 160MHz (10MHz)
 - RX72T: 192MHz (16MHz)
 - RX72N: 240MHz (16MHz)
 - Connect the indicator LED to the specified port.
 - Connect the USB serial and SCI ports.
 - Refer to RX600/port_map.hpp for the RX64M/RX71M SCI standard port.
 - Refer to RX24T/port_map.hpp for the RX24T SCI standard port.
 - Refer to RX65x/port_map.hpp for the RX65x SCI standard port.
 - Refer to RX72N/port_map.hpp for the RX72N SCI standard port.
 
```
#if defined(SIG_RX64M)
	typedef device::system_io<12'000'000> SYSTEM_IO;
	typedef device::PORT<device::PORT0, device::bitpos::B7> LED;
	typedef device::SCI1 SCI_CH;
	static const char* system_str_ = { "RX64M" };
#elif defined(SIG_RX71M)
	typedef device::system_io<12'000'000> SYSTEM_IO;
	typedef device::PORT<device::PORT0, device::bitpos::B7> LED;
	typedef device::SCI1 SCI_CH;
	static const char* system_str_ = { "RX71M" };
#elif defined(SIG_RX65N)
	typedef device::system_io<12'000'000> SYSTEM_IO;
	typedef device::PORT<device::PORT7, device::bitpos::B0> LED;
	typedef device::SCI9 SCI_CH;
	static const char* system_str_ = { "RX65N" };
#elif defined(SIG_RX24T)
	typedef device::system_io<10'000'000> SYSTEM_IO;
	typedef device::PORT<device::PORT0, device::bitpos::B0> LED;
	typedef device::SCI1 SCI_CH;
	static const char* system_str_ = { "RX24T" };
#elif defined(SIG_RX66T)
	typedef device::system_io<10'000'000> SYSTEM_IO;
	typedef device::PORT<device::PORT0, device::bitpos::B0> LED;
	typedef device::SCI1 SCI_CH;
	static const char* system_str_ = { "RX66T" };
#elif defined(SIG_RX72N)
	typedef device::system_io<16'000'000> SYSTEM_IO;
	typedef device::PORT<device::PORT4, device::bitpos::B0> LED;
	typedef device::SCI2 SCI_CH;
	static const char* system_str_ = { "RX72N" };
#elif defined(SIG_RX72T)
	typedef device::system_io<16'000'000, 192'000'000> SYSTEM_IO;
	typedef device::PORT<device::PORT0, device::bitpos::B1> LED;
	typedef device::SCI1 SCI_CH;
	static const char* system_str_ = { "RX72T" };
#endif
```

 - The standard crystal value is 10MHz for the RX24T and RX66T, and 12MHz for other CPUs.
 - RX72N Envision kit is a "16MHz" crystal
 - RX72T is a "16MHz" crystal
 - For the Envision kit RX65N, the indicator LED uses the blue color on the board.
 - For the Envision kit RX72N, the indicator LED uses the blue color on the board.
   
## Prepare your hardware resources.
 - Connect a converter, such as USB serial, to the port specified in SCI.
 - Connect the RXD terminal on the microcontroller side to the TXD of USB serial.
 - Connect the TXD terminal on the microcontroller side to the RXD of USB serial.
 - The RX72N Envision kit connects a PC to the CN8 micro USB on board.
   
## Build method
 - Go to each platform directory and make it.
 - Write the sci_sample.mot file.
   
## 動作
 - LED が 0.25 秒間隔で点滅する。
 - SCI に指定されたポートで、TX（送信）、RX（受信）を行う。
 - TeraTerm などで確認。
 - TeraTerm のシリアル設定：１１５２００ボー、８ビットデータ、１ストップ、パリティ無し。
 - main.cpp の中、SCI の初期化でボーレートは自由に設定できる。
 - ボーレート設定出来ない「値」の場合、初期化が失敗する。（極端に遅い、速い）
 - utils::command クラスにより、１行入力機能をサービス。
 - 受け取った文字をパースして表示。
    
## 備考
 - FIFO バッファは、受信側 256 バイト、送信側 512 バイトとなっている。
 - ボーレート、受信頻度、送信頻度などを考慮して、適切な値に調整する。
 - 最小は 16 バイト程度。
 - FIFO バッファより大きい文字列を送る場合、バッファが空くまで待機する事になる。
 - 受信時、バッファからの取り出し速度が、受信速度を下回ると、オーバーフローして、文字を紛失する。
 - SCI のチャネルを変更する場合「main.cpp」で「typedef」してある定義を変更する。
 - SCIx とポート接続の関係性は、RXxxx/port_map.hpp を参照する。
 - port_map クラスは、169 ピンデバイスのポートを基準にしたアサインになっている。
 - ピン番号以外は、144ピン、100ピン、デバイスでも同じように機能する。
 - 第二候補を選択する場合は、sci_io の typedef で、「device::port_map::option::SECOND」を追加する。
 - 別プログラムによって、雑多な設定を自動化してソースコードを生成する試みを行っているアプリケーションがありますが、それは、基本的に間違った方法だと思えます、設定の修正が必要な場合、必ず生成プログラムに戻って、生成からやり直す必要があります。
 - C++ テンプレートは、チャネルの違いや、ポートの違い、デバイスの違いをうまく吸収して、柔軟で、判りやすい方法で実装できます。
   
## 標準出力の対応
 - main.cpp には、標準出力（printf）に対応する事が出来る「枝」を出してあります。
 - 「sci_putch」などですが、これらの関数は、POSIX 関数、write などから、特定のディスクリプタ（stdout）で呼ばれるような仕組みが実装されています。（common/syscalls.c）
 - なので、printf 関数は普通に使えるのですが、C++ では推奨しません。（使う理由が無い）
 - printf は、引数が可変引数になっていて、スタック経由なので、format 文と引数に反故がある場合、クラッシュする事もあります、コンパイラのチェックでは完全に「反故」を見つける事は困難です、従って、どんなに便利でも使ってはいけません。
 - 代わりに、utils::format クラスを利用して下さい、printf とほぼ同じように使えて、間違った引数でもクラッシュする事はありません。
 - C++ の標準出力機能「std::cout」は、メモリを大量に消費し、実質的に利用出来ない為非推奨としています。
   
-----
   
License
----

MIT
