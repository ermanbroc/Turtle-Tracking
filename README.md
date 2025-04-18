# Turtle Tracking

## Embedded code for tracking Eastern Box Turtles

### Description

Arduino/C++ code to operate Adafruit Feather 32u4 RFM95 LoRa Radios. Boards are split into transmitters and receivers. Transmitters use an Adafruit Mini GPS PA1010D to locate position, then send the samples through the lora radio via a code standard. Receivers are equipped with a microsd card breakout board to log all samples the radio receives. Samples are seperated line by line, and the data within those samples is defined by the 28 byte standard outlined in the [pdf](Formatting.pdf).

### Purpose

The current technology for tracking small turtles is radiotelemetry. This technology requires someone to find the turtle through using an antenna to gauge whether they are getting closer or further from the transmitter, every time they want to record a single location sample. This new technology allows for a receiver to passively collect samples every few hours, without the need of a person. This will improve the amount of data researchers are able to collect when analyzing habits of various species.

### Product Requirements

* < 5m accurate turtle location coordinates
* < 15g weight for on turtle transceiver
* 20+ day transmitter battery life

### Transmitter Parts

| Part                                                                                  | Price  |
|---------------------------------------------------------------------------------------|--------|
| [LoRa Boards](https://www.adafruit.com/product/3078)                                  | $34.95 |
| [GPS Module](https://www.adafruit.com/product/4415)                                   | $29.95 |
| [LiPo Battery](https://www.adafruit.com/product/1317)                                 | $5.95  |
| [Dipole Antenna](https://www.digikey.com/en/products/detail/molex/1052620001/3918562?utm_adgroup=&utm_source=google&utm_medium=cpc&utm_campaign=PMax%20Shopping_Product_Medium%20ROAS%20Categories&utm_term=&utm_content=&utm_id=go_cmp-20223376311_adg-_ad-__dev-c_ext-_prd-3918562_sig-Cj0KCQjwr9m3BhDHARIsANut04YSBzpRy-2hhjNc40IiKBV0zNAmXBEovrMPh5oY-zLfD7GnWOpAwz8aAkT_EALw_wcB&gad_source=1&gclid=Cj0KCQjwr9m3BhDHARIsANut04YSBzpRy-2hhjNc40IiKBV0zNAmXBEovrMPh5oY-zLfD7GnWOpAwz8aAkT_EALw_wcB) | $1.98 |

### Receiver Parts

| Part                                                                                   | Price  |
|----------------------------------------------------------------------------------------|--------|
| [LoRa Boards](https://www.adafruit.com/product/3078)                                   | $34.95 |
| [MicroSD Breakout Board](https://www.adafruit.com/product/254)                         | $7.50  |
| [MicroSD Card](https://www.amazon.com/dp/B000H3E33A?ref=ppx_yo2ov_dt_b_fed_asin_title) | $9.99  |
| [Dipole Antenna](https://www.digikey.com/en/products/detail/molex/1052620001/3918562?utm_adgroup=&utm_source=google&utm_medium=cpc&utm_campaign=PMax%20Shopping_Product_Medium%20ROAS%20Categories&utm_term=&utm_content=&utm_id=go_cmp-20223376311_adg-_ad-__dev-c_ext-_prd-3918562_sig-Cj0KCQjwr9m3BhDHARIsANut04YSBzpRy-2hhjNc40IiKBV0zNAmXBEovrMPh5oY-zLfD7GnWOpAwz8aAkT_EALw_wcB&gad_source=1&gclid=Cj0KCQjwr9m3BhDHARIsANut04YSBzpRy-2hhjNc40IiKBV0zNAmXBEovrMPh5oY-zLfD7GnWOpAwz8aAkT_EALw_wcB) | $1.98 |

##### -Note about receiver power:

The receiver has no weight limit, and can be powered using a usb connected to a portable battery or extension cord

### Wiring
#### Transmitter: 

#### Receiver:

![LoRa Radio Board](https://github.com/ermanbroc/Turtle-Tracking/blob/main/Images/RadioBoard.png)
![MicroSD Card Reader](https://github.com/ermanbroc/Turtle-Tracking/blob/main/Images/SDReader.png)

##### Connections List:

| MicroSD Card Reader | LoRa Radio Board |
|---------------------|------------------|
| 5V                  | USB              |
| GND                 | GND              |
| CLK                 | SCK              |
| DO                  | MISO             |
| DI                  | MOSI             |
| CS                  | 10               |

##### -Note about LoRa Board:

In order to "connect" the LoRa Board to the radio network, you must also wire the dipole antenna to the ANT pin (check the bottom of the board).



