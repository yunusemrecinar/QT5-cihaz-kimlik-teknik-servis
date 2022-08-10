from tkinter import Y
import pymysql
from openpyxl import load_workbook
import pandas
from datetime import datetime 

sheet = load_workbook('C:\\Users\emrecinar\Desktop\modeo_servis_1.xlsx').active

rows = sheet.rows
count = 0

headers = [cell.value for cell in next(rows)]
all_rows = []

for row in rows :
    if(count == 280):
        break
    data = []
    for title, cell in zip(headers, row):
        print("Check0 " + title)
        

        if(title == 'Geliş Tarihi'):
            print("Check1")
            temp = cell.value.strftime("%d.%m.%Y") + " 12:00"
            data.append(temp)
            print(data)
        else:
            print("Check2")
            data.append(cell.value)
            #print(data)
        
        if(title == "Arıza Tarifi"):
            break
        
    all_rows.append(data) 
    count += 1

conn = pymysql.connect(
    host = "192.168.1.40",
    user = "modeo",
    password = "Modeo123123*",
    database = "modeo"
)
cursor = conn.cursor()

sql = "INSERT INTO teknikservis (`Cihaz Seri No`,`Tarih`,`Olay`,`Yapılan İşlem`) VALUES (%s, %s, 'Geldi', %s)"
countError = 0
for i in range(len(all_rows)):
        cursor.execute(sql,all_rows[i])
    
conn.commit()
conn.close()
