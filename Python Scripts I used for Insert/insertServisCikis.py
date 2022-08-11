from asyncio.windows_events import NULL
from tkinter import Y
import pymysql
from openpyxl import load_workbook
import pandas
from datetime import datetime 

sheet = load_workbook('C:\\Users\emrecinar\Desktop\modeo_servis_tamir.xlsx').active

rows = sheet.rows
count = 0

headers = [cell.value for cell in next(rows)]
all_rows = []

for row in rows :
    if(count == 248):
        break
    data = []
    for title, cell in zip(headers, row):

        if(title == 'Tamir Bitiş Tarihi'):
            if(cell.value == None or cell.value == ""):
                temp = "10.10.1010 10:10"
                data.append(temp)
                print(data)
            else:
                temp = cell.value.strftime("%d.%m.%Y") + " 12:00"
                data.append(temp)
                print(data)
        else:
            data.append(cell.value)
            print(data)

        if(title == "Tamir Bitiş Tarihi"):
            break
    print(data)    
    all_rows.append(data) 
    count += 1

conn = pymysql.connect(
    host = "192.168.1.40",
    user = "modeo",
    password = "Modeo123123*",
    database = "modeo"
)
cursor = conn.cursor()

sql = "INSERT INTO teknikservis (`Cihaz Seri No`,`Yapılan İşlem`,`Tarih`) VALUES (%s, %s, %s)"

for i in range(len(all_rows)):
        cursor.execute(sql,all_rows[i])
    
conn.commit()
conn.close()
