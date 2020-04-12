import serial
import time
import tkinter as tk

window = tk.Tk()
window.configure(background="dark orange")
window.title("BASIC GUI")

megaBoard = serial.Serial('COM21', 9600)

def motor_control():
    print(">>> XBEE + MOTOR CTRL - PROGRAM <<<\n")
    def forward():
        print("CTRL -> FORWARD + GREEN LED -> ON")
        megaBoard.write(b'g')

    def reverse():
        print("CTRL -> REVERSE + RED LED -> ON")
        megaBoard.write(b'r')

    def quit():
        print("\n** END OF PROGRAM **")
        megaBoard.write(b'q')
        megaBoard.close()
        window.destroy()

    b1 = tk.Button(window, text="FORWARD", command=forward, bg="lime green", fg="gray7", font=("Comic Sans MS", 20))

    b2 = tk.Button(window, text="REVERSE", command=reverse, bg="firebrick2", fg="ghost white", font=("Comic Sans MS", 20))

    b3 = tk.Button(window, text="EXIT", command=quit, bg="gold", fg="gray7", font=("Comic Sans MS", 20))

    l = tk.Label(window, text="XBEE + MOTOR CTRL - PYTHON", bg="SlateBlue1", font=("Comic Sans MS", 15))

    b1.grid(row=1, column=1, padx=5, pady=10)
    b2.grid(row=2, column=1, padx=5, pady=10)
    b3.grid(row=3, column=1, padx=5, pady=10)
    l.grid(row=4, column=1, padx=5, pady=10)

    window.mainloop()

time.sleep(2)
motor_control()
