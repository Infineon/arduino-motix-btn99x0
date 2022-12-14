.. _api-ref:

API Reference
=============

The Arduino library API is implemented via 3 different classes:

* **HalfBridge**. This class provides the primary API to operate and configure the half-bridge devices. → Use with arbitary board or custom hardware design with BTN99x0 half-bridge.
* **DCShield**. This class is a convenience class resolving the hardware configuration of the DC Motor Control Shield with BTN9970LV and BTN9990LV half-bridge switches. → Use with the DC Motor control Shield when driving arbitary loads.
* **MotorControl**. This class provides motor controlling functionality using the DC Motor Control Shield and abstracting the half-bridge API. → Use with the DC Motor control Shield when driving DC motors.

.. image:: img/btn99x0_class_overview.png
    :width: 500

HalfBridge API
---------------------------

.. doxygenclass:: btn99x0::HalfBridge
   :members:

DCShield API
---------------------------

.. doxygenclass:: btn99x0::DCShield
   :members:

MotorControl API
---------------------------

.. doxygenclass:: btn99x0::MotorControl
   :members:

BTN99x0 Types
-------------

.. doxygenstruct:: btn99x0::io_pins_t

.. doxygenstruct:: btn99x0::ic_experimental_const_t

.. doxygenstruct:: btn99x0::hw_conf_t

.. doxygenenum:: btn99x0::ic_variant_t

.. doxygenenum:: btn99x0::slew_rate_level_t

.. doxygenenum:: btn99x0::error_t 