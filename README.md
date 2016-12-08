# incu8ator
*** incu8ator *** 
----------------- 
An egg incubator termostat implementation using Raspberry Pi.

(OLED12864 means an OLED type display having SSD1306 display driver.)

Usage

nc8tr [OPTIONS]  
<p>--sensortype &lt;type&gt;, -s &lt;type&gt;								The type of the temperature sensor connected. Currently available types are 'emulator' or 'dht22'. Emulator simply generates random temperature and humidity values.</p>
<p>--displaytype &lt;type&gt;, -d &lt;type&gt;               The type of the display connected. Enter 'stdout' to see the messages in your console or write 'OLED12864' if you have this kind of OLED display connected.</p>
<p>--sensorgpiopin &lt;GPIO PIN#&gt;, -p &lt;GPIO PIN#&gt;   The BCM GPIO pin number (input) where the sensor connects. Default is GPIO04, that means the P1-07 physical connection.</p>
<p>--heatgpiopin &lt;GPIO PIN#&gt;, -w &lt;GPIO PIN#&gt;     The BCM GPIO pin number (output) where the heating device connects. Default is GPIO27, that means the P1-13 physical connection.</p>
<p>--qinterval &lt;number&gt;, -q &lt;number&gt;             Delay between two sensor query in seconds. The default value is 10 seconds and maximum is also 10 seconds.</p>
<p>--readalgorythm &lt;number&gt;, -a &lt;number&gt;         Method of query the sensor(DHT22). Currently there are two kind of options. Enter 1 to use the solution implemented by the Adafruit team(https://github.com/adafruit/Adafruit_Python_DHT). Or enter 2 to use a custom method gathered from the web from different sources. The first one is the best one.</p>
<p>--maxtemp &lt;number&gt;, -m &lt;number&gt;               Turn off the heating device when reaching the given temperature. Set it to a big number e.g. 9999 to avoid checking this limit(not recommended). For emergency purposes. Default value is 40.0°C.</p>
<p>--maxsensorerror &lt;number&gt;, -e &lt;number&gt;        The maximum number of the consecutive sensor errors. The default value is 5. Assuming 10seconds as query interval this means that the heating device will be turned on not more than 50 seconds. An insulated box which is ca. 0.6m3 with a ceramic heating wire supplied with 240V causes ca. 1°C/15seconds temperature increase assuming 38°C as a starting temperature. Aboves mean that the final temperature will be ca. 42-43°C after the 5 consecutive sensor errors. Calculate this value based on your own box! Over 42°C eggs will die. Over 60°C there is a good chance to cause fire within the box!</p>
<p>--report                                      Creates a CSV formatted file in /etc/incu8ator/report.csv. The will store each measuring steps as well as the errors.</p>
<p>--debug                                       Write verbose log information into the syslog file. Use it only in case of error or first time check.</p>
<p>--verbose                                     Same as --debug.</p>
<p>--help, -h                                    Show this message.</p>
<p>--version, -v                                 Show version information.</p>

Thanks to:
  - DHT22 driver - Adafruit tutorials on DHT22 and DHT11.
	
  - OLED driver - http://github.com/hallard/ArduiPi_OLED
	
  - BCM2835 C library - airspayce.com/mikem/bcm2835
	

!!!!********************* SAFETY FIRST *********************!!!!

PLEASE BE SURE YOU ARE ABSOLUTELY KNOW WHAT YOU DO:

  a.) ENTERING WRONG OR INAPPROPRIATE COMMAND LINE PARAMETER VALUES MAY CAUSE FIRE IN YOUR INCUBATOR BOX!

  b.) YOU MUST RUN MORE TESTS BEFORE LEAVING THE INCUBATOR BOX WORKING ALONE!

  c.) TAKE INTO ACCOUNT THAT THE HEATING DEVICES AND THE SENSORS USED MAY VARY!

  d.) PAPERS AND SEVERAL PLASTICS CAN FIRE UP FROM 80°C!

  e.) COMMON EGGS DIE OVER 42°C!

  f.) THE SUPPLY VOLTAGE (240V, 150V) OF AN INCUBATOR BOX IS VERY DANGEROUS!
  
  g.) INSERT AN INDEPENDENT MECHANICAL THERMOSTAT INTO THE HEATING SYSTEM AND SET IT'S MAXIMUM TEMPERATURE TO 42°C! THIS WILL BREAK THE HEATING CIRCUIT EVEN IF THE SOFTWARE AND/OR THE RASPBERRY PI HAS CRASHED.

YOU ARE USING THIS SOFTWARE WITH ABSOLUTELY NO WARRANTY.
I, THE OWNER OF THE SOURCE CODE, AM NOT RESPONSIBLE FOR ANY KIND OF ISSUES OR ACCIDENTS CAUSED BY THE SOFTWARE ITSELF - USE IT FOR YOUR OWN RISK!

!!!!********************* SAFETY FIRST *********************!!!!

Istvan Vig &copy; 2016. 
