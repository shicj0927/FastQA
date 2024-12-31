import addQuestion
import startAsk
from tkinter import*
root=Tk()
root.title("快问快答")
root.geometry("600x400")
root.resizable(False,False)
Label(root,text="快问快答 V1.1",font=("黑体",20)).pack()
Button(root,text="开始问答",padx=10,pady=10,font=("黑体",15),command=startAsk.startAskMain).pack(fill="both",expand="yes")
Button(root,text="问题设置",padx=10,pady=10,font=("黑体",15),command=addQuestion.addQuestionMain).pack(fill="both",expand="yes")
root.mainloop()