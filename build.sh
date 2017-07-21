#!/bin/bash
cc -o xcr $(pkg-config --cflags --libs cairo xcb xcb-icccm) xcr.c -lcairo -lxcb -lxcb-icccm
