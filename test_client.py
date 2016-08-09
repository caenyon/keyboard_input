# coding=utf-8

# noinspection PyUnresolvedReferences
import future
# noinspection PyCompatibility
from tkinter import *


def print_event(event):
    print('type={}, code={}, send_event={}, keysym={}'.format(event.type, event.keycode, event.send_event,
                                                              event.keysym))

if __name__ == '__main__':
    root = Tk()

    frame = Frame(root, width=200, height=100)
    frame.bind("<KeyPress>", print_event)
    frame.bind("<KeyRelease>", print_event)
    frame.pack()
    frame.focus_set()

    root.mainloop()
