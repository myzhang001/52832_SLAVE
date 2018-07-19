@echo off

:菜单
echo =======================
echo      批处理菜单
echo =======================

echo ====================================================
echo    1.擦除 erase_all     
echo    2.生成bootloader_setting
echo    3.生成private.pem 和 public_key.c
echo    4.烧录softdevice+settings+bootloader
echo    5.烧录纯应用代码
echo    6.打包application.zip
echo    7.合并所有
echo    8.发布工厂生成文件
echo    9.发布升级文件
echo    10.清理文件



echo ====================================================
echo ====================================================

echo    15.擦除UICR
echo    16.擦除NRF52 Flash
echo    17.复位
echo    18.烧协议栈
echo    19.烧应用层
echo    20.烧录所有
echo =======================

set /p 选择=请进入命令：

if %选择%==1 (goto  :16擦除NRF52 Flash)
if %选择%==2 (goto :1生成bootloader_setting)
if %选择%==3 (goto :2生成private.pem 和 public_key.c) 
if %选择%==4 (goto :19烧应用层) 
if %选择%==5 (goto  :21烧纯app)
if %选择%==6 (goto :5打包application) 
if %选择%==7 (goto :9合并所有) 
if %选择%==8 (goto :23发布工厂文件) 
if %选择%==9 (goto :24发布升级文件) 
if %选择%==10 (goto :25 清理文件) 




if %选择%==15 (goto :15擦除UICR)
if %选择%==16 (goto :16擦除NRF52 Flash)
if %选择%==17 (goto  :17复位)
if %选择%==18 (goto  :18烧协议栈)
if %选择%==19 (goto  :19 bootloader +setting 文件)

::else (goto : 菜单) 

:1生成bootloader_setting
:: 拷贝bootloader  hex
copy .\boot_loader\nRF5_SDK_14.2.0_17b948a\examples\dfu\bootloader_secure_ble\pca10040\arm5_no_packs\_build\smart_demo_bootloader.hex .\    
:: 拷贝app hex
copy .\nRF5_SDK_14.2.0_17b948a\examples\ble_peripheral\ble_app_uart\pca10040\s132\arm5_no_packs\_build\smart_demo_app.hex  .\

::拷贝协议栈
copy .\nRF5_SDK_14.2.0_17b948a\components\softdevice\s132\hex\s132_nrf52_5.0.0_softdevice.hex .\


::生成bootloader setting 文件 ，文件是通过app,hex 文件生成的
nrfutil.exe settings generate --family NRF52 --application smart_demo_app.hex --application-version 3 --bootloader-version 2 --bl-settings-version 1 bootloader_settings.hex
echo 已生成bootloader_setting...
:pause>nul
goto 菜单


:2生成private.pem 和 public_key.c
nrfutil.exe keys generate private.pem
nrfutil keys display --key pk --format code private.pem --out_file public_key.c
::nrfutil.exe keys generate private.pem Generated private key and stored in :key.pem
echo 生成private
:pause>nul
goto 菜单

:::3生成public_key.c
::nrfutil keys display --key pk --format code private.pem --out_file public_key.c
::nrfjprog -f NRF52 --reset
::echo 生成public_key.c
:::pause>nul
::goto 菜单

:::4合并bootloader和bootloader_setting
:://mergehex -m nrf52832.hex  bootloader_settings.hex  –o final.hex
::mergehex.exe  --merge  nrf52832_xxaa_bootloader.hex   bootloader_settings.hex    --output bootloade_final.hex 
::echo ......
:::pause>nul
::goto 菜单

:5打包application

::打包前先把最新的固件更新到文件路劲下面  app .hex
copy .\nRF5_SDK_14.2.0_17b948a\examples\ble_peripheral\ble_app_uart\pca10040\s132\arm5_no_packs\_build\smart_demo_app.hex  .\

nrfutil pkg generate --hw-version 52 --sd-req 0x9d --application-version 0xff --application smart_demo_app.hex --key-file private.pem smart_demo_app.zip
echo ......
:pause>nul
goto 菜单



:8打包SOFTDEVICE与bootloader
nrfutil pkg generate --hw-version 52 --sd-req 0x9d --softdevice   s132_nrf52_5.0.0_softdevice.hex --bootloader-version 0x11 --bootloader nrf52832_xxaa_bootloader.hex --key-file private.pem sd_boot.zip
:pause>nul
goto 菜单

:9合并所有


nrfutil.exe settings generate --family NRF52 --application smart_demo_app.hex --application-version 3 --bootloader-version 2 --bl-settings-version 1 bootloader_settings.hex

mergehex.exe  --merge  smart_demo_bootloader.hex   s132_nrf52_5.0.0_softdevice.hex     --output production_final1.hex 
mergehex.exe  --merge  production_final1.hex   smart_demo_app.hex   --output production_final2.hex 
mergehex.exe  --merge  production_final2.hex   bootloader_settings.hex  --output smart_demo(soft_device_settings_bootloader_app).hex 
del production_final1.hex
del production_final2.hex

:pause>nul
goto 菜单

:10打开app工程
start ..\nRF5_SDK_14.0.0_3bcc1f7\examples\ble_peripheral\ble_app_buttonless_dfu\pca10040\s132\arm5_no_packs\ble_app_buttonless_dfu_pca10040_s132.uvprojx
echo. & pause
goto 菜单

:11打开boot工程
start ..\nRF5_SDK_14.0.0_3bcc1f7\examples\dfu\bootloader_secure_ble\pca10040\arm5_no_packs\secure_dfu_ble_s132_pca10040.uvprojx
echo. & pause
goto 菜单

:12打开release目录
start release
echo. & pause
goto 菜单

:::13复制boot.hex到release目录
::copy ..\nRF5_SDK_14.0.0_3bcc1f7\examples\dfu\bootloader_secure_ble\pca10040\arm5_no_packs\_build\nrf52832_xxaa_bootloader.hex  release
::echo. & pause
::goto 菜单


:::14复制app.hex到release目录
::copy ..\nRF5_SDK_14.0.0_3bcc1f7\examples\ble_peripheral\ble_app_buttonless_dfu\pca10040\s132\arm5_no_packs\_build\nrf52832_xxaa_app.hex  release
::echo. & pause
::goto 菜单

:13复制boot.hex、app.hex到release目录
copy ..\nRF5_SDK_14.0.0_3bcc1f7\examples\dfu\bootloader_secure_ble\pca10040\arm5_no_packs\_build\nrf52832_xxaa_bootloader.hex  .\
copy ..\nRF5_SDK_14.0.0_3bcc1f7\examples\ble_peripheral\ble_app_buttonless_dfu\pca10040\s132\arm5_no_packs\_build\nrf52832_xxaa_app.hex  .\

echo. & pause
goto 菜单

:15擦除UICR
nrfjprog --family NRF52 --recovers 
echo. & pause 
goto 菜单


:16擦除NRF52 Flash
nrfjprog -f NRF52 --eraseall
echo 擦除完毕...
:pause>nul
goto 菜单


:17复位
nrfjprog -f NRF52 --reset
echo ......
:pause>nul
goto 菜单

:18烧协议栈
copy .\nRF5_SDK_14.2.0_17b948a\components\softdevice\s132\hex\s132_nrf52_5.0.0_softdevice.hex .\

nrfjprog.exe  -f NRF52  --program "s132_nrf52_5.0.0_softdevice.hex" --verify
::nrfjprog -f NRF52 --reset
echo ......
:pause>nul
goto 菜单

:19烧应用层
nrfjprog.exe  -f NRF52  --program "s132_nrf52_5.0.0_softdevice.hex" --verify
nrfjprog.exe  -f NRF52  --program "bootloader_settings.hex" --verify
nrfjprog.exe  -f NRF52  --program "smart_demo_bootloader.hex" --verify

::nrfjprog.exe  -f NRF52  --program "rm661_final.hex" --verify
::nrfjprog -f NRF52 --reset
echo ......
:pause>nul
goto 菜单

:21烧纯app

:: 拷贝app hex
copy .\nRF5_SDK_14.2.0_17b948a\examples\ble_peripheral\ble_app_uart\pca10040\s132\arm5_no_packs\_build\smart_demo_app.hex  .\

nrfjprog.exe  -f NRF52  --program "smart_demo_app.hex" --verify


::nrfjprog.exe  -f NRF52  --program "rm661_final.hex" --verify
::nrfjprog -f NRF52 --reset
echo ......
:pause>nul
goto 菜单



:23发布工厂文件

md  softdevice_setting_boot_app_zip



copy   smart_demo(soft_device_settings_bootloader_app).hex               .\softdevice_setting_boot_app_zip

del    smart_demo(soft_device_settings_bootloader_app).hex 


echo ......
:pause>nul
goto 菜单

:24发布升级文件 

md  update_zip

::打包前先把最新的固件更新到文件路劲下面  app .hex
copy .\nRF5_SDK_14.2.0_17b948a\examples\ble_peripheral\ble_app_uart\pca10040\s132\arm5_no_packs\_build\smart_demo_app.hex  .\

nrfutil pkg generate --hw-version 52 --sd-req 0x9d --application-version 0xff --application smart_demo_app.hex --key-file private.pem smart_demo_app.zip

copy .\smart_demo_app.zip  .\update_zip

del .\smart_demo_app.zip

echo ......
:pause>nul
goto 菜单


:25 清理文件

del  *.hex

echo ......
:pause>nul
goto 菜单





:20烧录所有
::nrfjprog.exe  -f NRF52  --program "nrf52832_661.hex" --verify
::nrfjprog.exe  -f NRF52  --program "nrf52832_xxaa_bootloader.hex" --verify
::nrfjprog.exe  -f NRF52  --program "bootloader_settings.hex" --verify
cls
nrfjprog -f NRF52 --eraseall
::nrfjprog --family NRF52 --recovers 

nrfjprog.exe  -f NRF52  --program  "rm661_final.hex" --verify
nrfjprog -f NRF52 --reset
echo ......
:pause>nul
goto 菜单


:无效命令
echo 无效的指令 指令范围（1-20）重新选择
goto 菜单

