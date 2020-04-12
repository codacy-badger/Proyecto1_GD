from tkinter import*
root = Tk()

e = Entry(root, width = 50, bg="blue", fg="white", borderwidth =5)
e.pack()
e.insert(0,"Enter Your Name:")

def myClick():
    hello = "Hello " + e.get()
    myLabel = Label(root, text= hello)
    myLabel.pack()
#Creating a label Widget
myButton = Button(root, text="Entrer your name", padx = 50, pady = 10, command = myClick, fg="blue",bg ="#0f0")
myButton.pack()

root.mainloop()