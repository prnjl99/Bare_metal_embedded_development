#!/bin/bash

ROOT_FOLDER=$(dirname ${BASH_SOURCE[0]})

# Compile target application
make APP=$1 ROOT_FOLDER=$ROOT_FOLDER clean