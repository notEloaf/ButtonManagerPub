# Button Manager
The purpose of this code is to create an easy to use, versatile button manager. It supports multiple different kinds of button presses and allows for independent actions to be taken for each button interaction.

## Setup

## Button Events
Button Down Event:
This event occurs when a button is pressed down.

Button Up Event:
This event occurs when a button is released.

Timed Click Event:
This event has two different interactions. Given a time "click duration" if the button is pressed down and released in less time than the "click duration" then it is a short press, otherwise it is a long press.

Clicked Event:
This event occurs when a buttons is pressed and released. (functionally the same as the button up event, just included for ease of use)

Held Event:
This event will only occur when a button has been held for more than x ms, once the event occurs no more events can occur.

