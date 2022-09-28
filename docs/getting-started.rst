.. _arduino-getting-started:

Getting Started
================

Overview
--------

This getting started guide helps you to properly connect DC Motor Control Shield with BTN9970LV and BTN9970LV with the right platform and teaches you how to install the required software to use the Infineon 
BTN99x0 chips

.. _`DC-SHIELD_BTN9970LV`: https://www.infineon.com/cms/en/product/evaluation-boards/dc-shield_btn9970lv/

Required Hardware
-----------------

Microcontroller
"""""""""""""""
Any Arduino compatible board with Arduino Uno form-factor, like XMC1100 Boot Kit 

.. image:: img/XMC1100.jpg
    :height: 200

DC-SHIELD_BTN9970LV
"""""""""""""""""""""""""""""""""""

.. image:: img/btn99x0_shield.png
    :height: 300

Required Software
-----------------

* `Arduino IDE`_
* This library installed in the Arduino IDE, the instructions can be found `here <https://www.arduino.cc/en/guide/libraries>`__
* When using an Arduino compatible XMC board, please find installation instructions `here <https://github.com/Infineon/XMC-for-Arduino#installation-instructions>`_.

.. _`Arduino IDE`: https://www.arduino.cc/en/software

Tutorial
--------

Software Installation
""""""""""""""""""""""

1. **Install the Arduino IDE**. If you are new to Arduino, please `download <https://www.arduino.cc/en/Main/Software>`__ the program and install it first.

2. **Include the XMC boards in the IDE (if a XMC is used)**. The official Arduino boards are already available in the Arduino IDE, but other third party boards as the Infineon XMC MCU based ones need to be explicitly included. Follow the instructions in the `link <https://github.com/Infineon/XMC-for-Arduino#installation-instructions>`__ to add the XMC board family to the Arduino IDE.

3. **Install the library**. In the Arduino IDE, go to the menu *Sketch > Include library > Library Manager*. Type *Arduino-BTN99x0** and install the library.

Hardware Setup
""""""""""""""

The shield can be used with all platforms that support the Arduino form factor. But please be aware that all these platforms have to have the same pin functionalities as the Arduino. Otherwise the full functionality of the shield can not be assured.

To connect the shield you just have to assure that the notch of the Arduino Uno and the shield are above each other. Then you can plug the shield on top of the Arduino.

.. image:: img/arduino-marked.png
    :height: 200

.. image:: img/btn99x0_shield.png
    :height: 250

The pin headers can also be used to figure out the right orientation. There is only one way to properly connect them.

As soon as the shield is connected to the Arduino you can connect a USB cable to the Arduino to power up the microcontroller. Make sure that no code or the example code of this repository is flashed to the microcontroller. Otherwise it can happen that the board is already activating one of the switches.

.. image:: img/arduino-btn99x0-stack.PNG
    :height: 200

Now you can attach the power supply to the X1 connector.Now you have to attach your load to the desired output channel in the X2 conncetor.The DC brush motor need to be connected between the outputs OUT1 and OUT2 of both half bridges of BTN9970 and BTN9990.

Ready To Go!
""""""""""""

Now you can upload the provided example code to your Arduino compatible board. For this, navigate in your Arduino IDE to *File* -> *Examples* -> *Arduino-BTN99x0* -> **.

For a specific description and overview of all examples please refer to :ref:`Arduino examples <arduino-examples>`.