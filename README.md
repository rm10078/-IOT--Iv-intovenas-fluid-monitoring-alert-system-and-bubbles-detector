
# IOT Iv intovenas fluid monitoring alert system and bubbles detector

Our college is organizing a tech program(AICTE SPICES & HIT). I made this project for this program. Our device measures the saline fluid level and sends an alert when the level is so low.
The device has a bubble detector for detecting the air bubble in the fluid line. And we are the winner.


# Feature
* Mass flow rate 
* Liquid weight
* Alert through internet (Telegram)
* Air bubble detector
* Internal battery status
* Rechargeable battery 
# Device photo
![App Screenshot](https://github.com/rm10078/-IOT--Iv-intovenas-fluid-monitoring-alert-system-and-bubbles-detector/blob/main/image/dev_photo.jpeg?raw=true)
![App Screenshot](https://github.com/rm10078/-IOT--Iv-intovenas-fluid-monitoring-alert-system-and-bubbles-detector/blob/main/image/inside_box.jpg?raw=true)
# Working process

I use esp32 for this project. The esp32 acts as a web server and sends data to the Thingspeak cloud.
You can monitor the data online on Thingspeak and offline on a local web page. The air
bubbles detector work on simple opamp comparator circuit with ldr and a green led.

## Air bubbles detector
![App Screenshot](https://github.com/rm10078/-IOT--Iv-intovenas-fluid-monitoring-alert-system-and-bubbles-detector/blob/main/image/air_bubble.jpeg?raw=true)
<br> <br>

The device has three mod.
1.Configuration <br>
2.Set fluid <br>
3.Normal mode <br>

## 1. Configuration mode

Hold the config button. next-> Turn on the device. <br>

Now the device acts like a web server. You just connect the device wifi and the password is hit@1234. Next go to the link and enter all the information. 

![App Screenshot](https://github.com/rm10078/-IOT--Iv-intovenas-fluid-monitoring-alert-system-and-bubbles-detector/blob/main/image/config.png?raw=true)

After submit Reset the device.

## 2. Set fluid

Hold the back button. Next-> Turn on the device. <br>

Now you can set the fluid weight and aler point. For increase use up button and decrease use down button.
press ok for save the data.

![App Screenshot](https://github.com/rm10078/-IOT--Iv-intovenas-fluid-monitoring-alert-system-and-bubbles-detector/blob/main/image/alert%20point.png?raw=true)
![App Screenshot](https://github.com/rm10078/-IOT--Iv-intovenas-fluid-monitoring-alert-system-and-bubbles-detector/blob/main/image/fluid_weight_w.png?raw=true)

## 3. Normal mode

Restart the device.

![App Screenshot](https://github.com/rm10078/-IOT--Iv-intovenas-fluid-monitoring-alert-system-and-bubbles-detector/blob/main/image/display_view.png?raw=true)

# Web page

## Offline page
### Mobile
![App Screenshot](https://github.com/rm10078/-IOT--Iv-intovenas-fluid-monitoring-alert-system-and-bubbles-detector/blob/main/image/mobile_page1.png?raw=true)
![App Screenshot](https://github.com/rm10078/-IOT--Iv-intovenas-fluid-monitoring-alert-system-and-bubbles-detector/blob/main/image/mobile_page2.png?raw=true)
### Desktop
![App Screenshot](https://github.com/rm10078/-IOT--Iv-intovenas-fluid-monitoring-alert-system-and-bubbles-detector/blob/main/image/desktop_page.png?raw=true)

## online page
![App Screenshot](https://github.com/rm10078/-IOT--Iv-intovenas-fluid-monitoring-alert-system-and-bubbles-detector/blob/main/image/online.png?raw=true)
## Alert Screenshot
![App Screenshot](https://github.com/rm10078/-IOT--Iv-intovenas-fluid-monitoring-alert-system-and-bubbles-detector/blob/main/image/alert_ss.png?raw=true)

## For more information watch this video.
- [@video](https://youtu.be/ULRAC_1f-9c)

# About me
I am a diploma engineer. Currently i am pursuing Bachelor in technology. I am a 3nd year Applied Electronics and Instrumentation engineering student.
## 🔗 Links
Gmail-  rm10078@gmail.com
[![linkedin](https://img.shields.io/badge/linkedin-0A66C2?style=for-the-badge&logo=linkedin&logoColor=white)](https://www.linkedin.com/in/rajib-manna-41155a228/)


