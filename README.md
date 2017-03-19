A simple interactive interface over a serial connection to an ATmega328P.
Something I can hopefully share with my nephew back home :-)


    $ minicom -D /dev/ttyUSB0 -b 4800
    ...

    Type 'help' if you need usage instructions
    >>> help
    
    Executing command: 'help'
    
    Usage:
        led on      to light me up
        led off     to go to sleep...
    
    >>> 
    Type 'help' if you need usage instructions
    >>> led on
    
    Executing command: 'led on'
    
    Type 'help' if you need usage instructions
    >>> led off
    
    Executing command: 'led off'
    
    Type 'help' if you need usage instructions
    >>> asdfad
    
    Command 'asdfad' is not recognized...
    Available commands are:
    
        led on
        led off
        help
    
    Type 'help' if you need usage instructions
    >>> 
