import addQuestion
import startAsk
from tkinter import*
#import ttkbootstrap as ttk
import ttkbootstrap as ttk
root=ttk.Window()
root.title("快问快答")
root.iconbitmap("icon.ico")
root.geometry("600x200")
root.resizable(False,False)
Label(root,text="快问快答 V1.2",font=("黑体",20)).pack()
Button(root,text="开始问答",padx=10,pady=10,font=("黑体",20),command=startAsk.startAskMain).pack(fill="x",expand="yes")
Button(root,text="问题设置",padx=10,pady=10,font=("黑体",20),command=addQuestion.addQuestionMain).pack(fill="x",expand="yes")
root.mainloop()