#!/usr/bin/env python3

import os
from pathlib import Path
import argparse
import sys

import ninja_syntax
from get_platform import get_platform


DEFAULT_WIBO_PATH = "./wibo"


parser = argparse.ArgumentParser(description="Generates build.ninja")
parser.add_argument('-w', type=str, default=DEFAULT_WIBO_PATH, dest="wine", required=False, help="Path to Wine/Wibo (linux only)")
parser.add_argument("--compiler", type=Path, required=False, help="Path to pre-installed compiler root directory")
parser.add_argument("--no-extract", action="store_true", help="Skip extract step")
parser.add_argument("--dsd", type=Path, required=False, help="Path to pre-installed dsd CLI")
parser.add_argument('version', choices=["usa", "jpn", "eur"], help='Game version')
args = parser.parse_args()


# Config
GAME = "dqix"
DSD_VERSION = 'v0.10.2'
WIBO_VERSION = '0.6.16'
OBJDIFF_VERSION = 'v2.7.1'
MWCC_VERSION = "2.0/sp2p2" # minimum version required to match fixed point s64 arithmetic around 0x02030f30 (not sdk code). might need p3 or p4?
MWCC_VERSIONS = { # Files compiled with another version than MWCC_VERSION
    # Nintendo's libraries were compiled with 2.0/sp2 or older: from 2.0/sp2p2, multiplying a 32-bit value by a 64-bit
    # one skips the multiplications by the high words that are 0, e.g. in OS_Sleep (SleepCurrentContext)
    "src/Graphics/NSBXX/JAC.cpp": "2.0/sp2", # NitroSystem
    "src/Sound/SoundArchiveStream.cpp": "2.0/sp2", # NitroSystem
    "src/System/ProcessorContext.cpp": "2.0/sp2", # NitroSDK
    # OSi_ReloadRomData assigns its registers like 2.0/sp1p5 and older, not like 2.0/sp1p7 and newer
    "src/System/itcm/ResetITCM.cpp": "2.0/sp1p5", # NitroSDK
    "src/System/RealTimeClockConvert.cpp": "2.0/sp2", # NitroSDK
    "src/System/Trigonometry.cpp": "2.0/sp2", # NitroSDK
    "src/Autopilot/ov003/0215ee44.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/02160b2c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/0216a85c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/0217f194.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/0215ca68.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/02173bb0.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/0216d7ec.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/0216ff90.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/0217e5b0.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/0215e498.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/021749c0.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/02158a50.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/02160b50.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/0216720c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/02167548.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/0216d818.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/02172570.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/0217451c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/02174890.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/02175898.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/0217e300.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/0217e67c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/02174988.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/0215dd00.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/0215e85c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/0217585c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/02159250.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/0215cab0.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/0215e750.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/02166f40.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/02169554.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/02158140.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/02175f90.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/02155f40.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/0215b328.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/0215dcb8.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/0215efb8.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/02161438.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/02168560.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/0216950c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/0215b370.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/0215ca1c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/0216d5f0.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/0217063c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/02171cac.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/02173490.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/02174408.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/0217e36c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/0217e630.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/0215be20.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/0216adbc.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/02170d38.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/021694b8.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/0217dc40.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/0215c510.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/021702e4.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/02173788.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/0217a220.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/0217f1b8.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/02170280.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/02177208.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/0215376c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/0215f5e8.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/021705d4.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/02159100.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/021716f8.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/02179da8.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/0216664c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/0215f56c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/02160240.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/02171cf8.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/0217f118.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/0217bcb8.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/0217480c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/02159078.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/02160e34.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/02154eec.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/0217daf0.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/021669f0.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/0216e200.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/0215c464.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/0215ddc0.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov003/0215de6c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov001/02158008.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov001/02158018.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov001/02158028.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov001/02158338.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov001/0215941c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov001/021598e0.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov001/0215aaa8.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov001/0215aab8.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov001/0215ef44.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov001/02156858.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov001/02157acc.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov001/0215b5b4.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov001/0215b5c8.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov001/02159044.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov001/021590c4.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov001/0215a3c0.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov001/0215a5d8.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov001/0215a5f0.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov001/021622f0.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov001/02162308.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov001/02162320.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov001/021637d4.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov001/02163848.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov001/02163994.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov001/02157570.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov001/02159804.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov001/0215a6fc.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov001/0215a718.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov001/0215a734.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov001/0215b058.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov001/0215b598.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov001/0215b5dc.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov001/0215b5f8.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov001/0215b614.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov001/0215b630.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov001/02156534.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov001/0215647c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov001/02153994.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov001/02154da0.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov001/02153948.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov000/02170078.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov000/0216b204.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov000/0216c384.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov000/02176498.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov000/02178cbc.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov000/02179128.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov000/021795e0.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov000/0216ad0c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov000/02179c6c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov000/0216b394.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov000/0216fd80.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov000/0216ac90.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov000/0216b180.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov000/0216fe9c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov000/02175b54.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov000/0216d2d0.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov000/0217f480.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov000/0216abc4.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov000/0217de64.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov000/0216c144.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov000/021635e4.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov000/021818e0.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov000/0216a364.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov000/0217c094.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov000/02177bf0.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov000/0217bfbc.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov000/0217e46c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov000/02166880.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/0218b5a0_ov017.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/0218b5b0.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021a7998.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021a85d4.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021a9248.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021a99c8.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021ac294.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021aca00.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021adb08.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021adc30.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021adc44.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021afae8.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021afafc.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021b1fc0.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021b1fd4.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021b1fe8.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021b1ffc.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021b2010.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021b2024.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021b2038.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021b204c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021b2060.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021b354c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021b8c70.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021c1a10.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021c30f8.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021d2428.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021d35f8.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021d4a24.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021d4a64.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021d6134.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021d6148.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/02191b40.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/02191b58.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/02195748.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/0219a370.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021a11f4.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021a1924.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021a4e70.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021a6b84.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021a72dc.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021a7a5c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021a85bc.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021a9314.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021a9998.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021a99b0.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021acce4.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021b1454.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021b1d24.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021b2bdc.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021b2bf4.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021b2c0c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021b2f4c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021b6b44.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021b6b5c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021b6b74.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021b83f0.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021b8408.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021b8420.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021b8438.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021b8450.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021b86e0.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021b8b54.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021babc8.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021babe0.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021bae80.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021bae98.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021bb8d8.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021beb8c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021befcc.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021bf5dc.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021c031c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021c0520.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021c0538.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021c0550.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021c0568.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021c11f0.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021c1208.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021c1220.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021c19e0.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021c19f8.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/0218d4d0.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/0218d5ac.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/0218d7fc.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/02195760.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/02199480.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/02199998.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021999e0.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021ab67c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021b1ca8.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021b2074.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021b65bc.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021b8b94.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021c168c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021c9b04.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021c9b58.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021c9b74.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021cdae4.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/0218d75c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021923e0.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021a5934.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021a5954.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021a5a28.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021a5a48.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021a5a68.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021a5ab0.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021afa9c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021b04c0.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021b1cc4.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021b1ce4.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021b1d04.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021b2328.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021b2348.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021b2368.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021b2f0c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021b2f2c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021b8b34.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021b994c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021be3ec.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021c162c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021c164c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021c166c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021d4a78.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021d4a98.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021d4ab8.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021d4ad8.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/0218b664.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/02193428.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021a185c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021a1880.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021a18a4.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021acd00.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021b9904.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021b9928.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021be0a0.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021c16a8.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021c1acc.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021c2688.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/0219cd98.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021a942c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021aa3f4.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021b11b0.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021b2c24.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021c316c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021c9cb0.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/0218d618.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021972cc.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021972f8.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021999b4.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021afa70.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021afabc.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021b6b8c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021ba8e0.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021babf8.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov017/021baeb0.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02231df8.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02232004.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02232380.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/022324e8.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02233700.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02234770.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/022348ac.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02234b2c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02234dc4.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02235eac.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02235ecc.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02235eec.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/0223689c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/022368e0.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02236f68.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/022393e4.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02239e48.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/0223a040.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/0223da38.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02241318.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/022436c0.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02245528.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/022071b4.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/022072ac.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02207380.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/022093d0.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02212598.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02212c18.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/022134cc.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02214334.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/022157c4.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02227ba4.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02228980.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/0222a848.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/0222a86c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/0222abe8.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/0222b52c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02231a78.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/0223232c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02233154.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02233cbc.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02233f1c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02234408.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02235f0c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02236878.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/022368bc.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02239a00.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02239b10.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/0223ac14.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/0223c054.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/0223c7c4.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/0223cedc.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/0223cf4c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/0223ea60.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/0220510c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02205620.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02207d60.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02211820.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/0221e2bc.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02221e84.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/022274e4.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02227520.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/0222821c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/022286f4.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02228a84.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02228ae4.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02228ef4.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02228f54.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02229350.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/022298a8.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02229ad4.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02229b34.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02229cf4.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02229d54.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02229f70.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/0222bb1c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/0222cbb8.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/0222e868.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/0222e8c8.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02231058.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/0223125c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02231674.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02231d48.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/022321c4.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/022334e8.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02233c94.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/022346a8.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02234a68.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02236e38.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/022399d8.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02239b98.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/0223a288.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/0223d830.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/0223e8ac.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/0223fa34.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/022403b0.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/022407f8.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02240df4.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/022436e0.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02207204.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02207620.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/022098ac.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/0221032c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02210ef8.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/022112e4.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/022115a4.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02212248.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02213204.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/0221544c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/0221add4.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/0221aff8.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/0221b258.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/0221cfdc.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/0221d384.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02222e54.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02227688.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02228a58.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02229aa8.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02229f44.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/0222abbc.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/0222ac5c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/0222b388.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/0222cb8c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/0222d6b0.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/0222e378.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02231230.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/022312e0.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/022314ec.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/0220321c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02204168.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02204b50.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02200754.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02202810.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/022033e8.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/0220376c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02204dbc.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/022006f0.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02203b8c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02204df8.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/02203398.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/022031bc.c": "2.0/sp2", # Autopilot
    "src/Autopilot/main/0201156c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/main/02011580.c": "2.0/sp2", # Autopilot
    "src/Autopilot/main/02011800.c": "2.0/sp2", # Autopilot
    "src/Autopilot/main/02011814.c": "2.0/sp2", # Autopilot
    "src/Autopilot/main/02011b4c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/main/02012de0.c": "2.0/sp2", # Autopilot
    "src/Autopilot/main/02017d78.c": "2.0/sp2", # Autopilot
    "src/Autopilot/main/02017d8c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/main/0201bf80.c": "2.0/sp2", # Autopilot
    "src/Autopilot/main/0201bf94.c": "2.0/sp2", # Autopilot
    "src/Autopilot/main/0201bfd0.c": "2.0/sp2", # Autopilot
    "src/Autopilot/main/0201e258.c": "2.0/sp2", # Autopilot
    "src/Autopilot/main/0201e888.c": "2.0/sp2", # Autopilot
    "src/Autopilot/main/0202140c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/main/020263d8.c": "2.0/sp2", # Autopilot
    "src/Autopilot/main/020269e0.c": "2.0/sp2", # Autopilot
    "src/Autopilot/main/02026bd8.c": "2.0/sp2", # Autopilot
    "src/Autopilot/main/0202e6a4.c": "2.0/sp2", # Autopilot
    "src/Autopilot/main/0202e958.c": "2.0/sp2", # Autopilot
    "src/Autopilot/main/02033ed8.c": "2.0/sp2", # Autopilot
    "src/Autopilot/main/020397bc.c": "2.0/sp2", # Autopilot
    "src/Autopilot/main/0203984c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/main/02039d78.c": "2.0/sp2", # Autopilot
    "src/Autopilot/main/0203b4c0.c": "2.0/sp2", # Autopilot
    "src/Autopilot/main/0203b4f8.c": "2.0/sp2", # Autopilot
    "src/Autopilot/main/0203b530.c": "2.0/sp2", # Autopilot
    "src/Autopilot/main/0203be74.c": "2.0/sp2", # Autopilot
    "src/Autopilot/main/0203be88.c": "2.0/sp2", # Autopilot
    "src/Autopilot/main/0203ce10.c": "2.0/sp2", # Autopilot
    "src/Autopilot/main/020404bc.c": "2.0/sp2", # Autopilot
    "src/Autopilot/main/02040aec.c": "2.0/sp2", # Autopilot
    "src/Autopilot/main/020415c0.c": "2.0/sp2", # Autopilot
    "src/Autopilot/main/020415d4.c": "2.0/sp2", # Autopilot
    "src/Autopilot/main/020416dc.c": "2.0/sp2", # Autopilot
    "src/Autopilot/main/020421c0.c": "2.0/sp2", # Autopilot
    "src/Autopilot/main/0200efb8.c": "2.0/sp2", # Autopilot
    "src/Autopilot/main/0200fd68.c": "2.0/sp2", # Autopilot
    "src/Autopilot/main/02010098.c": "2.0/sp2", # Autopilot
    "src/Autopilot/main/020108e8.c": "2.0/sp2", # Autopilot
    "src/Autopilot/main/02011554.c": "2.0/sp2", # Autopilot
    "src/Autopilot/main/020115a0.c": "2.0/sp2", # Autopilot
    "src/Autopilot/main/020115e0.c": "2.0/sp2", # Autopilot
    "src/Autopilot/main/02011620.c": "2.0/sp2", # Autopilot
    "src/Autopilot/main/0203ef70.c": "2.0/sp2", # Autopilot
    "src/Autopilot/main/0203f1d8.c": "2.0/sp2", # Autopilot
    "src/Autopilot/main/0203f364.c": "2.0/sp2", # Autopilot
    "src/Autopilot/main/0203fc94.c": "2.0/sp2", # Autopilot
    "src/Autopilot/main/0200efd0.c": "2.0/sp2", # Autopilot
    "src/Autopilot/main/02011528.c": "2.0/sp2", # Autopilot
    "src/Autopilot/main/0203bb2c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/main/0203c74c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/main/0203b58c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/main/0203c0dc.c": "2.0/sp2", # Autopilot
    "src/Autopilot/main/0203bd98.c": "2.0/sp2", # Autopilot
    "src/Autopilot/main/0203db0c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/main/0201138c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/main/02011478.c": "2.0/sp2", # Autopilot
    "src/Autopilot/main/020114a4.c": "2.0/sp2", # Autopilot
    "src/Autopilot/main/020114d0.c": "2.0/sp2", # Autopilot
    "src/Autopilot/main/020114fc.c": "2.0/sp2", # Autopilot
    "src/Autopilot/main/0201bf48.c": "2.0/sp2", # Autopilot
    "src/Autopilot/main/0201134c.c": "2.0/sp2", # Autopilot
    "src/Autopilot/main/0201bb88.c": "2.0/sp2", # Autopilot
    "src/Autopilot/main/0201ba78.c": "2.0/sp2", # Autopilot
    "src/Autopilot/ov031/0220a444.c": "2.0/sp2", # Autopilot
}
DECOMP_ME_COMPILER = "mwcc_30_137"
CC_FLAGS = " ".join([
    "-O2",                  # Optimize maximally, omit p: it optimizes out things that the game doesn't normally
    "-enum int",            # Use int-sized enums
    "-char signed",         # Char type is signed
    "-str noreuse",         # Equivalent strings are different objects
    "-proc arm946e",        # Target processor
    "-gccext,on",           # Enable GCC extensions
    "-fp soft",             # Compute float operations in software
    "-inline noauto",       # Inline only functions marked with 'inline'
    "-lang=c++",            # Set language to C++
    "-Cpp_exceptions off",  # Disable C++ exceptions
    "-RTTI off",            # Disable runtime type information
    "-interworking",        # Enable ARM/Thumb interworking
    "-w off",               # Disable warnings
    "-sym on",              # Debug info, including line numbers
    "-gccinc",              # Interpret #include "..." and #include <...> equally
    "-nolink",              # Do not link
    "-msgstyle gcc",        # Use GCC-like messages (some IDEs will make file names clickable)
    "-str pool,reuse"       # Pool and reuse strings within translation units
])
REGION_DEFINES = { # Preprocessor macros that each version is compiled with
    "usa": ["usa"],
    "jpn": ["jpn"],
    "eur": ["usa", "eur"], # EUR is built from the same code as USA
}
MWCC_DEFINES = " ".join(f"-d {define}" for define in REGION_DEFINES[args.version])
M2CTX_DEFINES = " ".join(f"-D {define}" for define in REGION_DEFINES[args.version])
FORCE_ACTIVE = { # Overlay functions that -dead would strip because nothing references them
    "usa": "func_ov030_021d8a40",
    "jpn": "func_ov029_021d9300,func_ov030_021d9300",
    # Main calls overlay 34's loader through the symbol of overlay 33's, which is at the same address. The constants of
    # the NitroSDK's SHA-1 are before its function, which loads them relative to its address (see SHA1Block.cpp).
    # Main calls overlay 21's Initialize() and Finish(), overlay 19's and 20's Initialize() and overlay 30's functions
    # through the symbols of the overlays at the same address too, and overlays 2 and 23 call overlay 13's
    # SkillPointMenu::Update() and overlay 11's MenuScript::GetUnk1b2() through overlay 9's. Overlay 6's
    # AlchemyMenu::Draw3D() is called through overlay 1's function at the same address.
    "eur": "_Z19CreateGameResourcesP14AllocatorUnionPP17GameResourcesData,"
           "_Z20DestroyGameResourcesP13GameResourcesP14AllocatorUnionPP17GameResourcesData,"
           "_Z28PopulateOv34BackgroundLoaderPvji,sha1Constants,"
           "_ZN22CharacterCreationScene10InitializeEv,_ZN22CharacterCreationScene6FinishEv,"
           "_ZN15SaveErrorScreen10InitializeEv,_ZN12StartupScene10InitializeEv,"
           "_ZN14SkillPointMenu6UpdateEi,_ZN10MenuScript9GetUnk1b2Ev,_ZN11AlchemyMenu6Draw3DEv",
}
LOCAL_SYMBOLS = { # Weak symbols that a file has its own copy of, see tools/localize_symbols.py
    # Overlays 33 and 34 are at the same address, and both have a copy of BackgroundLoader's vtable
    "src/Filesystem/Overlay_34/Ov34BackgroundLoader.cpp": ["_ZTV16BackgroundLoader"],
    # Overlays 9 and 12 each have a copy of the checker of the forbidden words
    "src/Scene/Overlay_9/CharacterCreation.cpp": [
        "_ZN20ForbiddenWordChecker10InitializeEv", "_ZN20ForbiddenWordChecker7ToUpperEPKcPc",
        "_ZN20ForbiddenWordChecker8FindTextEPKcS1_ii", "_ZN20ForbiddenWordChecker5MatchEPKcS1_ii",
        "_ZN20ForbiddenWordChecker8ContainsEPKhih",
    ],
}
LD_FLAGS = " ".join([
    "-proc arm946e",        # Target processor
    "-nostdlib",            # No C/C++ standard library
    "-interworking",        # Enable ARM/Thumb interworking
    "-m Entry",             # Set entry function
    "-map closure,unused",  # Generate map file
    "-msgstyle gcc",        # Use GCC-like messages (some IDEs will make file names clickable)
    "-dead",                # Don't allow dead code (FORCE_ACTIVE, in the linker script, keeps the functions that
                            # nothing references by their own symbols)
])
DSD_OBJDIFF_ARGS = " ".join([
    "--scratch",                        # Metadata for creating decomp.me scratches
    f"--compiler {DECOMP_ME_COMPILER}", # decomp.me compiler name
    f'--c-flags "{CC_FLAGS} -lang=c++ {MWCC_DEFINES}"', # decomp.me compiler flags
    "--custom-make ninja",              # Command for rebuilding files
])


# Paths
current_path     = Path(__name__)
root_path        = current_path.parent
build_ninja_path = root_path / "build.ninja"
arm7_bios_path   = root_path / "arm7_bios.bin"
config_path      = root_path / "config"
build_path       = root_path / "build"
src_path         = root_path / "src"
libs_path        = root_path / "libs"
extract_path     = root_path / "extract"
tools_path       = root_path / "tools"
mwcc_root        = args.compiler or tools_path / "mwccarm"
mwcc_path        = mwcc_root / MWCC_VERSION


# Includes
includes = [
    str(root_path / "include")
]
for root, dirs, _ in os.walk(libs_path):
    for dir in dirs:
        if dir == "include":
            includes.append(Path(root) / dir)
CC_INCLUDES = " ".join(f"-i {include}" for include in includes)


# Platform info
platform = get_platform()
if platform is None:
    exit(1)
EXE = platform.exe
WINE = args.wine if platform.system != "windows" else ""
DSD = str(args.dsd or os.path.join('.', str(root_path / f"dsd{EXE}")))
OBJDIFF = os.path.join('.', str(root_path / f"objdiff-cli{EXE}"))
CC = os.path.join('.', str(mwcc_path / "mwccarm.exe"))
CC_VERSIONS = {source: os.path.join('.', str(mwcc_root / version / "mwccarm.exe")) for source, version in MWCC_VERSIONS.items()}
LD = os.path.join('.', str(mwcc_path / "mwldarm.exe"))
PYTHON = sys.executable


class Project:
    def __init__(self, game_version: str):
        self.game_version = game_version
        '''Version of the game'''
        self.game_config = config_path / game_version
        '''Root directory for dsd configs'''

        self.game_build = build_path / game_version
        '''Path to build directory'''
        self.game_extract = extract_path / game_version
        '''Path to extract directory'''

        self.delinks_files = get_config_files(self.game_config, "delinks.txt")
        '''Paths to every delinks.txt file'''
        self.relocs_files = get_config_files(self.game_config, "relocs.txt")
        '''Paths to every relocs.txt file'''
        self.symbols_files = get_config_files(self.game_config, "symbols.txt")
        '''Paths to every symbols.txt file'''

    def dsd_configs(self) -> list[str]:
        return self.delinks_files + self.relocs_files + self.symbols_files

    def arm9_config_yaml(self) -> Path:
        return self.game_config / "arm9" / "config.yaml"

    def is_initialized(self) -> bool:
        '''Whether the dsd configs for this version exist yet'''
        return self.arm9_config_yaml().is_file()

    def baserom(self) -> Path:
        return extract_path / f'baserom_{GAME}_{self.game_version}.nds'

    def build_rom(self) -> str:
        return f"{GAME}_{self.game_version}.nds"

    def baserom_config(self) -> Path:
        return self.game_extract / 'config.yaml'

    def build_rom_config(self) -> Path:
        return self.game_build / "build" / "rom_config.yaml"

    def source_object_files(self) -> list[str]:
        return [
            str(self.game_build / source_file.with_suffix(".o"))
            for source_file in get_c_cpp_files([src_path, libs_path])
        ]

    def arm9_lcf(self) -> Path:
        return self.game_build / "arm9.lcf"

    def arm9_sdk_lcf(self) -> Path:
        return self.game_build / "arm9_sdk.lcf"

    def arm9_objects_txt(self) -> Path:
        return self.game_build / "objects.txt"

    def arm9_delink_yaml(self) -> Path:
        return self.game_build / "delinks" / "delink.yaml"

    def arm9_o(self) -> Path:
        return self.game_build / "arm9.o"

    def arm9_delinks(self) -> Path:
        return self.game_build / "delinks"

    def objdiff_report(self) -> Path:
        return self.game_build / "report.json"


def main():
    project = Project(args.version)

    with build_ninja_path.open("w") as file:
        n = ninja_syntax.Writer(file)

        n.rule(
            name="download_tool",
            command=f'{PYTHON} tools/download_tool.py $tool $tag --path $path'
        )
        n.newline()

        if arm7_bios_path.is_file():
            n.variable("arm7_bios_flag", f"--arm7-bios {arm7_bios_path.relative_to(root_path)}")
        else:
            n.variable("arm7_bios_flag", "")
        n.newline()

        n.rule(
            name="extract",
            command=f"{DSD} rom extract --rom $in --output-path $output_path $arm7_bios_flag"
        )
        n.newline()

        n.rule(
            name="delink",
            command=f"{DSD} delink --config-path $config_path"
        )
        n.newline()

        # -MMD excludes all includes instead of just system includes for some reason, so use -MD instead.
        # The compiler is a variable, since some files are compiled with another version (see MWCC_VERSIONS)
        n.variable("mwcc", CC)
        mwcc_cmd = f'{WINE} "$mwcc" {CC_FLAGS} {CC_INCLUDES} $cc_flags {MWCC_DEFINES} -MD -c $in -o $basedir'
        mwcc_implicit = [CC]
        if platform.system != "windows":
            transform_dep = "tools/transform_dep.py"
            mwcc_cmd += f" && $python {transform_dep} $basefile.d $basefile.d"
            mwcc_implicit.append(transform_dep)
        n.rule(
            name="mwcc",
            command=mwcc_cmd,
            depfile="$basefile.d",
        )
        n.newline()

        n.rule(
            name="localize_symbols",
            command=f"{PYTHON} tools/localize_symbols.py $in $out $symbols"
        )
        n.newline()

        n.rule(
            name="lcf",
           # command=f"{DSD} lcf -c $config_path --lcf-file $lcf_file --objects-file $objects_file"
            command=f"{DSD} lcf --config-path $config_path"
        )
        n.newline()

        n.rule(
            name="add_linker_symbols",
            command=f"{PYTHON} tools/add_linker_symbols.py $in $out --force-active {FORCE_ACTIVE[args.version]}"
        )
        n.newline()

        n.rule(
            name="mwld",
            command=f'{WINE} "{LD}" {LD_FLAGS} @$objects_file $lcf_file -o $out'
        )
        n.newline()

        n.rule(
            name="rom_config",
            command=f"{DSD} rom config --elf $in --config $config_path"
        )
        n.newline()

        n.rule(
            name="rom_build",
            command=f"{DSD} rom build --config $in --rom $out $arm7_bios_flag"
        )
        n.newline()

        n.rule(
            name="objdiff",
            command=f"{DSD} objdiff --config-path $config_path {DSD_OBJDIFF_ARGS}"
        )
        n.newline()

        n.rule(
            name="objdiff_report",
            command=f"{OBJDIFF} report generate -o $out"
        )
        n.newline()

        n.rule(
            name="m2ctx",
            command=f"{PYTHON} tools/m2ctx.py -f $out {M2CTX_DEFINES} $in"
        )
        n.newline()

        n.rule(
            name="check_modules",
            command=f"{DSD} check modules --config-path $config_path --fail"
        )
        n.newline()

        n.rule(
            name="check_symbols",
            command=f"{DSD} check symbols --config-path $config_path --elf-path $elf_path --fail"
        )
        n.newline()

        n.rule(
            name="sha1",
            command=f"{PYTHON} tools/sha1.py $in -c $sha1_file"
        )
        n.newline()

        add_download_tool_builds(n)
        add_extract_build(n, project)
        if not project.is_initialized():
            # New version without dsd configs yet, so there is nothing to delink or build
            if not args.no_extract:
                n.default("extract")
            print(f"{project.arm9_config_yaml()} not found, so only the extract step was generated.")
            return
        add_delink_and_lcf_builds(n, project)
        add_mwcc_builds(n, project, mwcc_implicit)
        add_mwld_and_rom_builds(n, project)
        add_check_builds(n, project)
        add_objdiff_builds(n, project)

        # Provide barebones alternative `ninja min` to avoid building a
        # decomp.me context for every source file, which makes GCC a
        # prerequisite for producing the ROM. Also skips the sha1 step
        n.build(
            inputs=["rom", "check"],
            rule="phony",
            outputs="min",
        )
        n.newline()


def add_download_tool_builds(n: ninja_syntax.Writer):
    if args.dsd is None:
        n.build(
            rule="download_tool",
            outputs=DSD,
            variables={
                "tool": "dsd",
                "tag": DSD_VERSION,
                "path": DSD,
            },
        )
        n.newline()

    n.build(
        rule="download_tool",
        outputs=OBJDIFF,
        variables={
            "tool": "objdiff",
            "tag": OBJDIFF_VERSION,
            "path": OBJDIFF,
        }
    )
    n.newline()

    if args.compiler is None:
        n.build(
            rule="download_tool",
            outputs=[CC, LD, *sorted(set(CC_VERSIONS.values()) - {CC})],
            variables={
                "tool": "mwccarm",
                "tag": "latest",
                "path": tools_path,
            },
        )
        n.newline()

    if platform.system != "windows" and WINE == DEFAULT_WIBO_PATH:
        n.build(
            rule="download_tool",
            outputs=WINE,
            variables={
                "tool": "wibo",
                "tag": WIBO_VERSION,
                "path": WINE,
            },
        )
        n.newline()


def add_extract_build(n: ninja_syntax.Writer, project: Project):
    if not args.no_extract:
        n.build(
            inputs=str(project.baserom()),
            implicit=DSD,
            rule="extract",
            outputs=str(project.baserom_config()),
            variables={
                "output_path": str(project.game_extract)
            }
        )
        n.newline()

        n.build(
            inputs=str(project.baserom_config()),
            rule="phony",
            outputs="extract",
        )
        n.newline()


def add_mwld_and_rom_builds(n: ninja_syntax.Writer, project: Project):
    # dsd's linker script, with the symbols that the NitroSDK's linker script defines
    lcf_file = str(project.arm9_sdk_lcf())
    add_linker_symbols = "tools/add_linker_symbols.py"
    n.build(
        inputs=str(project.arm9_lcf()),
        implicit=add_linker_symbols,
        rule="add_linker_symbols",
        outputs=lcf_file,
    )
    n.newline()

    objects_file = str(project.arm9_objects_txt())
    delink_file = str(project.arm9_delink_yaml())
    elf_file = str(project.arm9_o())
    n.build(
        inputs=project.source_object_files() + [lcf_file, objects_file, delink_file],
        implicit=LD,
        rule="mwld",
        outputs=elf_file,
        variables={
            "target_dir": project.game_build,
            "objects_file": objects_file,
            "lcf_file": lcf_file,
        }
    )
    n.newline()

    n.build(
        inputs=elf_file,
        rule="phony",
        outputs="arm9",
    )
    n.newline()

    rom_config_file = str(project.build_rom_config())
    n.build(
        inputs=elf_file,
        implicit=DSD,
        rule="rom_config",
        outputs=rom_config_file,
        variables={
            "config_path": project.arm9_config_yaml(),
        }
    )
    n.newline()

    rom_file = project.build_rom()
    n.build(
        inputs=rom_config_file,
        implicit=DSD,
        rule="rom_build",
        outputs=rom_file,
    )
    n.newline()

    n.build(
        inputs=rom_file,
        rule="phony",
        outputs="rom",
    )
    n.newline()

    n.build(
        inputs=rom_file,
        rule="sha1",
        variables={
            "sha1_file": str(Path(rom_file).with_suffix(".sha1"))
        },
        outputs="sha1",
    )
    n.newline()


def add_mwcc_builds(n: ninja_syntax.Writer, project: Project, mwcc_implicit: list[Path]):
    for source_file in get_c_cpp_files([src_path, libs_path]):
        src_obj_path = project.game_build / source_file
        local_symbols = LOCAL_SYMBOLS.get(source_file.as_posix())
        # With symbols to make local, the compiler's object goes to a subdirectory first
        mwcc_obj_path = src_obj_path.parent / "weak" / src_obj_path.name if local_symbols else src_obj_path
        cc_flags = []
        if is_cpp(source_file): cc_flags.append("-lang=c++")
        elif is_c(source_file): cc_flags.append("-lang=c")
        variables = {
            "cc_flags": " ".join(cc_flags),
            "basedir": os.path.dirname(mwcc_obj_path),
            "basefile": str(mwcc_obj_path.with_suffix("")),
        }
        implicit = mwcc_implicit
        compiler = CC_VERSIONS.get(source_file.as_posix())
        if compiler is not None:
            variables["mwcc"] = compiler
            implicit = [compiler if dependency == CC else dependency for dependency in mwcc_implicit]
        n.build(
            inputs=str(source_file),
            implicit=implicit,
            rule="mwcc",
            outputs=str(mwcc_obj_path.with_suffix(".o")),
            variables=variables,
        )
        n.newline()

        if local_symbols:
            n.build(
                inputs=str(mwcc_obj_path.with_suffix(".o")),
                implicit="tools/localize_symbols.py",
                rule="localize_symbols",
                outputs=str(src_obj_path.with_suffix(".o")),
                variables={"symbols": " ".join(local_symbols)},
            )
            n.newline()

        extension = source_file.suffix
        ctx_file = str(project.game_build / source_file.with_suffix(f".ctx{extension}"))
        n.build(
            inputs=str(source_file),
            rule="m2ctx",
            outputs=ctx_file,
        )
        n.newline()


def get_c_cpp_files(dirs: list[Path]):
    for dir in dirs:
        for root, _, files in os.walk(dir):
            root = Path(root)
            for file in files:
                if is_cpp(file) or is_c(file):
                    yield root / file


def is_cpp(name: str):
    return Path(name).suffix in [".cpp"]


def is_c(name: str):
    return Path(name).suffix in [".c"]


def add_delink_and_lcf_builds(n: ninja_syntax.Writer, project: Project):
    n.comment("Delink ELF binaries when any delinks.txt file is modified")
    rom_config = str(project.baserom_config())
    delinks_path = project.arm9_delinks()
    n.build(
        inputs=project.dsd_configs() + [rom_config],
        implicit=DSD,
        rule="delink",
        outputs=str(delinks_path / "delink.yaml"),
        variables={
            "config_path": project.arm9_config_yaml(),
        }
    )
    n.newline()

    n.build(
        inputs=str(delinks_path / "delink.yaml"),
        rule="phony",
        outputs="delink"
    )
    n.newline()

    lcf_file = project.arm9_lcf()
    objects_file = project.arm9_objects_txt()
    n.build(
        inputs=project.delinks_files + [str(rom_config)],
        implicit=DSD,
        rule="lcf",
        outputs=[str(lcf_file), str(objects_file)],
        variables={
            "config_path": project.arm9_config_yaml(),
            "lcf_file": lcf_file,
            "objects_file": objects_file,
        }
    )
    n.newline()


def add_check_builds(n: ninja_syntax.Writer, project: Project):
    n.build(
        inputs=str(project.arm9_o()),
        rule="check_modules",
        outputs="check_modules",
        variables={
            "config_path": project.arm9_config_yaml(),
        },
    )
    n.newline()

    n.build(
        inputs=str(project.arm9_o()),
        rule="check_symbols",
        outputs="check_symbols",
        variables={
            "config_path": project.arm9_config_yaml(),
            "elf_path": project.arm9_o(),
        },
    )
    n.newline()

    n.build(
        inputs=["check_modules", "check_symbols"],
        rule="phony",
        outputs="check",
    )
    n.newline()


def add_objdiff_builds(n: ninja_syntax.Writer, project: Project):
    n.build(
        inputs=project.dsd_configs(),
        implicit=DSD,
        rule="objdiff",
        outputs="objdiff.json",
        variables={
            "config_path": project.arm9_config_yaml(),
        }
    )
    n.newline()

    n.build(
        inputs="objdiff.json",
        rule="phony",
        outputs="objdiff",
    )
    n.newline()

    n.build(
        inputs=["objdiff.json"],
        implicit=[OBJDIFF] + project.source_object_files(),
        rule="objdiff_report",
        outputs=str(project.objdiff_report()),
    )
    n.newline()

    n.build(
        inputs=str(project.objdiff_report()),
        rule="phony",
        outputs="report",
    )
    n.newline()


def get_config_files(game_config: Path, name: str) -> list[str]:
    return [
        f"{root}/{file}"
        for root, _, files in os.walk(game_config)
        for file in files
        if file == name
    ]


if __name__ == "__main__": main()
