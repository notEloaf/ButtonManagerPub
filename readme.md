# Button Manager
The purpose of this code is to create an easy to use, versatile button manager. It supports multiple different kinds of button presses and allows for independent actions to be taken for each button interaction.

## Setup
Setup is intentionally simple to do, however it requires 2 main components: the config file and an interface.

The purpose of an interface is to link what a button down and button up is in hardware to the software. If none of the available interfaces are appropriate for your hardware then look at the example to create your own.

The config file is a simple txt document that defines the id of each button and the events associated with them (look at button events section for the config definitions). To create your own config simply create a file called config.txt. Write "ButtonIds:" followed by each id of your button (make sure each id is on a newline). Then write "Behaviors:" followed by an event defition (see Button Events section) **remember all definitions must have "START" before them and "buttonId:{id}** for any clarification look at the provided config.txt.

## Button Events
Button Down Event:
This event occurs when a button is pressed down.
```
type:buttonDown
op:{button Op}
```

Button Up Event:
This event occurs when a button is released.
```
type:buttonUp
op:{button Op}
```
Timed Click Event:
This event has two different interactions. Given a time "click duration" if the button is pressed down and released in less time than the "click duration" then it is a short press, otherwise it is a long press.
```
type:timedClick
shortOp:{short click op}
longOp:{long click op}
clickDuration:{time in ms}
```

Clicked Event:
This event occurs when a buttons is pressed and released. (functionally the same as the button up event, just included for ease of use)
```
type:clicked
op:{clicked op}
```

Held Event:
This event will only occur when a button has been held for more than x ms, once the event occurs no more events can occur.
```
type:held
op:{held op}
downDuration:{time in ms}
```

**Example event**
```
START
buttonId:sim0
type:held
op:HoldingOp
downDuration:1000
```

## Usage
