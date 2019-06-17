#!/bin/bash

JAGEX=$HOME/.jagex
RS_DIR=$JAGEX/runescape
RS_BIN=$RS_DIR/bin
RS_IMAGES=$RS_DIR/images

mkdir $HOME/.jagex_cache_32
mkdir $HOME/.jagex_cache_32/runescape
mkdir $JAGEX
mkdir $RS_DIR
mkdir $RS_BIN
mkdir $RS_IMAGES

wget https://github.com/MrHDR/RaspberryPi/raw/master/Rsinstall/jagexappletviewer.jar -P $RS_BIN

wget https://raw.githubusercontent.com/MrHDR/RaspberryPi/master/Rsinstall/jagexappletviewer.png -P $RS_IMAGES

wget https://raw.githubusercontent.com/MrHDR/RaspberryPi/master/Rsinstall/jagexappletvieweros.png -P $RS_IMAGES


