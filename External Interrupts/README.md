# ATmega48-IO-ports
<p style="text-align:center;">LEDs are connected to port B. Buttons are connected to port D. After pressing any button, a PCINT2 interrupt request is generated. After pressing the buttons SW1 - SW7, their numbers are remembered. Each even pressing of the SW0 button turns on the LEDs with the numbers of the previously pressed buttons, and each odd one turns off the LEDs, and the numbers of the pressed buttons are not stored after that.</p>

# Proteus simulation
![image](https://user-images.githubusercontent.com/65315002/226192488-29220008-24d8-4ae1-9c4e-41e0491b356e.png)



# Algorithm
![image](https://user-images.githubusercontent.com/65315002/226192459-3e45e46a-970b-428d-a143-add55c8e372d.png)
