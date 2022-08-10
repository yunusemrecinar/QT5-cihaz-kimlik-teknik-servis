from tkinter import Y
import pymysql
from openpyxl import load_workbook
import pandas
import datetime 

sheet = load_workbook('C:\\Users\emrecinar\Desktop\modeo3_1.xlsx').active

rows = sheet.rows
count = 0

headers = [cell.value for cell in next(rows)]
all_rows = []

for row in rows :
    if(count == 179):
        break
    data = []
    for title, cell in zip(headers, row):

        if(title == "Uretim Tarihi"):
            if cell.value != None:
                data.append(cell.value.strftime("%d.%m.%Y"))
            else:
                data.append(cell.value)
        else:
            data.append(cell.value)

        if(title == "NOT"):
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

sql = "INSERT INTO cihazkimlik (`Model`, `Cihaz Seri No`, `Anakart No`, `UID No`, `Modem Kartı`, `Lcd Kartı`, `Şarj Kartı`, `Durumu`, `Modem Tipi`, `Müşteri Adı`, `Modem Seri Num 1`, `Modem Seri Num 2`, `Modem Seri Num 3`, `Modem Seri Num 4`, `Modem Seri Num 5`, `Modem Seri Num 6`, `Uretim Tarihi`, `Test Durumu`, `Notlar`) VALUES (%s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s)"

for i in range(len(all_rows)):
    cursor.execute(sql,all_rows[i])

conn.commit()
conn.close()
