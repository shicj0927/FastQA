from tkinter import*
import tkinter.ttk as tt
def writeTable(result,t,questions):
	items=t.get_children()
	for i in items:
		t.delete(i)
	for i in result:
		tmp=[i[0],questions[i[0]],i[1],i[2]]
		t.insert("","end",values=tmp)
		print("[Debug]","insert",i)
def showResultMain(result,questions):
	rootShowR=Toplevel()
	rootShowR.geometry("800x400")
	t=tt.Treeview(rootShowR,columns=("c1","c2","c3","c4"),show="headings")
	t.pack(fill="both",expand="yes")
	t.heading("c1",text="序号")
	t.heading("c2",text="题目")
	t.heading("c3",text="用时")
	t.heading("c4",text="结果")
	writeTable(result,t,questions)
	rootShowR.mainloop()