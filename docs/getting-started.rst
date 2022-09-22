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

.. image:: ../../img/XMC1100.jpg
    :height: 200

DC-SHIELD_BTN9970LV
"""""""""""""""""""""""""""""""""""

.. image:: ../../img/BTN9970_shield.jpg
    :height: 200

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

3. **Install the library**. In the Arduino IDE, go to the menu *Sketch > Include library > Library Manager*. Type **high-side-switch-ino** and install the library.

Hardware Setup
""""""""""""""

The shield can be used with all platforms that support the Arduino form factor. But please be aware that all these platforms have to have the same pin functionalities as the Arduino. Otherwise the full functionality of the shield can not be assured