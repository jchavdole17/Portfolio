# Goal
The purpose of this project was to create an automated musical instrument for a design methodology class. This project was finished in a span of 2.5 months. The requirements were for the final prototype to play 3 songs without any manual input.

# Approach
My group's approach was to actuate mallets with a solenoid to play xylophone keys. In regards to automation, we decided to not code each solenoid directly to play a song. We felt that we could make our project more versatile by connecting a digital audio workstation (DAW) to our microcontroller and playing any song within our octave that way. This required communication with MIDI protocol between the DAW and the Arduino, but we found an open-source library that facilitated this. I was in charge of creating this program and tethering it to our solenoids. There is a video in this folder that shows the final result.
