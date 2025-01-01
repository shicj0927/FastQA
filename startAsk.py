from tkinter import*
import csv
import showResult
from tkinter import messagebox
questions=[]
result=[]
def loadCsv():
	global questions
	questions=[]
	with open("./data/questions.csv",encoding="utf8") as f:
		reader=csv.reader(f)
		for idx,v in enumerate(reader):
			questions.append(list(v))
	print("[Debug]","load questions OK")
	print("[Debug]","data:",questions)
def writeResult(result):
	with open("./data/result.csv","w",newline="",encoding="utf-8-sig") as f:
		writer=csv.writer(f)
		writer.writerow(["编号","问题","提示","答案","用时","结果"])
		for i in range(len(result)):
			tmpq=questions[result[i][0]]
			tmp=[result[i][0],tmpq[0],tmpq[1],tmpq[2],result[i][1],result[i][2]]
			writer.writerow(tmp)
	print("[Debug]","write result OK")
	print("[Debug]","data:",result)
running=False
nowQid=0
timerRunning=False
timer=0
def startAskMain():
	result=[]
	rootStart=Toplevel()
	rootStart.title("快问快答")
	rootStart.iconbitmap("icon.ico")
	rootStart.resizable(False,False)
	loadCsv()
	bT=StringVar()
	sT=StringVar()
	sCN=StringVar()
	sC=StringVar()
	sQ=StringVar()
	sH=StringVar()
	sA=StringVar()
	bT.set("开始")
	sT.set("0s")
	sCN.set("?/?")
	sC.set("1")
	sQ.set("[未开始]")
	sH.set("[未开始]")
	def loadNext():
		# global questions
		# print("[]",questions)
		global nowQid
		nowQid+=1
		if nowQid>=len(questions):
			nowQid-=1
			return False
		sQ.set(questions[nowQid][0])
		sH.set(questions[nowQid][1])
		sCN.set(str(nowQid+1)+"/"+str(len(questions)))
		print("[Debug]","nowQue",sQ.get())
		return True
	def updateTime():
		global timerRunning,timer
		if timerRunning:
			timer+=1
			sT.set(str(timer)+"s")
			rootStart.after(1000,updateTime)
	def judge():
		global nowQid
		if sA.get()==questions[nowQid][2]:
			result.append([nowQid,timer,1])
			print("[Info]",nowQid,"正确")
			writeResult(result)
			sA.set("")
		else:
			result.append([nowQid,timer,0])
			questions.append(questions[nowQid])
			messagebox.showerror('提示','答案错误\n应为：'+questions[nowQid][2],parent=rootStart)
			#showWarn()
			print("[Info]",nowQid,"错误")
			writeResult(result)
			sA.set("")
	def startEnd():
		global running,nowQid,timer,timerRunning
		if running==False:
			running=True
			nowQid=-1
			loadNext()
			timerRunning=True
			timer=0
			updateTime()
			bT.set("结束")
		else:
			running=False
			timerRunning=False
			timer=0
			sT.set("0s")
			sCN.set("?/?")
			sC.set("1")
			sQ.set("[未开始]")
			sH.set("[未开始]")
			print("[Info]","result",result)
			showResult.showResultMain(result,questions)
			bT.set("开始")
		print(bT.get())
	def submit():
		global nowQid,timer,result
		judge()
		timer=0
		loadNext()
	bSE=Button(rootStart,textvariable=bT,font=("黑体",15),command=startEnd).pack(anchor="n",fill="x")
	f1=Frame(rootStart)
	l2=Label(f1,textvariable=sT,font=("黑体",15)).pack(side="left",anchor="n",expand="yes")
	l3=Label(f1,textvariable=sCN,font=("黑体",15)).pack(side="left",anchor="n",expand="yes")
	l4=Label(f1,textvariable=sC,font=("黑体",15)).pack(side="left",anchor="n",expand="yes")
	f1.pack(anchor="n",fill="x")
	f2=Frame(rootStart)
	l5=Label(f2,text="问题: ",font=("楷体",20)).pack(side="left",anchor="n")
	l6=Label(f2,textvariable=sQ,anchor='w',font=("楷体",20)).pack(side="left",anchor="n",expand="yes")
	f2.pack(anchor="n",fill="x")
	f3=Frame(rootStart)
	l7=Label(f3,text="提示: ",font=("楷体",20)).pack(side="left",anchor="n")
	l8=Label(f3,textvariable=sH,anchor='w',font=("楷体",20)).pack(side="left",anchor="n",expand="yes")
	f3.pack(anchor="n",fill="x")
	f4=Frame(rootStart)
	l9=Label(f4,text="答案: ",font=("楷体",20)).pack(side="left",anchor="n")
	e1=Entry(f4,textvariable=sA,font=("楷体",20),width=30).pack(side="left",anchor="n",fill="x",expand="yes")
	f4.pack(anchor="n",fill="x")
	f5=Frame(rootStart)
	bS=Button(f5,text="提交",font=("黑体",15),command=submit).pack(anchor="n",fill="x")
	f5.pack(anchor="n",fill="x")
	rootStart.mainloop()