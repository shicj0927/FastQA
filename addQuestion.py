from tkinter import*
import tkinter.ttk as tt
import csv
questions=[]
def loadCsv():
	global questions
	questions=[]
	with open("./data/questions.csv",encoding="utf8") as f:
		reader=csv.reader(f)
		for idx,v in enumerate(reader):
			questions.append(list(v))
	print("[Debug]","load questions OK")
	print("[Debug]","data:",questions)
def writeCsv():
	global questions
	with open("./data/questions.csv","w",newline="",encoding="utf8") as f:
		writer=csv.writer(f)
		for i in questions:
			writer.writerow(i)
	print("[Debug]","write questions OK")
	print("[Debug]","data:",questions)
def writeTable(t):
	items=t.get_children()
	for i in items:
		t.delete(i)
	for i in questions:
		t.insert("","end",values=i)
		print("[Debug]","insert",i)
def addQuestion(t):
	rootAddQ=Toplevel()
	rootAddQ.title("快问快答-加入问题")
	rootAddQ.resizable(False,False)
	Label(rootAddQ,text="问题",font=("黑体",15)).grid(row=1,column=1)
	e1=Entry(rootAddQ,width=45,font=("黑体",15))
	e1.grid(row=1,column=2)
	Label(rootAddQ,text="提示",font=("黑体",15)).grid(row=2,column=1)
	e2=Entry(rootAddQ,width=45,font=("黑体",15))
	e2.grid(row=2,column=2)
	Label(rootAddQ,text="答案",font=("黑体",15)).grid(row=3,column=1)
	e3=Entry(rootAddQ,width=45,font=("黑体",15))
	e3.grid(row=3,column=2)
	def enter():
		print("[Debug]",e1.get())
		tmp=[str(e1.get()),str(e2.get()),str(e3.get())]
		questions.append(tmp)
		print("[Debug]","add data",tmp)
		writeCsv()
		writeTable(t)
		rootAddQ.destroy()
	def quitWin():
		rootAddQ.destroy()
	Button(rootAddQ,text="完成",width=50,font=("黑体",15),command=enter).grid(row=4,column=1,columnspan=2)
	Button(rootAddQ,text="取消",width=50,font=("黑体",15),command=quitWin).grid(row=5,column=1,columnspan=2)
	rootAddQ.mainloop()
def addQuestionMain():
	root=Toplevel()
	root.title("快问快答-问题设置")
	root.geometry("600x400")
	root.resizable(False,False)
	loadCsv()
	t=tt.Treeview(root,columns=("c1","c2","c3"),show="headings")
	t.pack(fill="both",expand="yes")
	t.heading("c1",text="问题")
	t.heading("c2",text="提示")
	t.heading("c3",text="答案")
	writeTable(t)
	def click():
		addQuestion(t)
	Button(root,text="新建问题",padx=10,pady=10,font=("黑体",15),command=click).pack(fill="both",expand="yes")
	root.mainloop()