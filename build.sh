#!/bin/sh
cd arduino_starter_kit_projects/p1_led_blink; make
cd ../p2_spaceship_interface; make
cd ../../can_isotp_fd/canfd/; make
cd ../canisotp/; make
cd ../../logger/; make