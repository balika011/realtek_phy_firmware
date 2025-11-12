#!/bin/bash
set -e
gcc rtl8261n_rtl8264b.c phy_patch.c -o phy_patch
./phy_patch