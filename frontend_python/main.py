import tkinter as tk
from frontend_python.app import LoginWindow

if __name__ == "__main__":
    root = tk.Tk()
    app = LoginWindow(root)
    root.mainloop()