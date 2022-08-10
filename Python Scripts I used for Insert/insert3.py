from tkinter import Y
import pymysql
from openpyxl import load_workbook
import pandas
import datetime 

sheet = load_workbook('C:\\Users\emrecinar\Desktop\modeo_musteri.xlsx').active

rows = sheet.rows
count = 0

headers = [cell.value for cell in next(rows)]
all_rows = []

for row in rows :
    if(count == 173):
        break
    data = []
    for title, cell in zip(headers, row):

        data.append(cell.value)
        
        if(title == "Musteri"):
            break
    all_rows.append(data)
    count += 1

conn = pymysql.connect(
    host = "localhost",
    user = "root",
    password = "",
    database = "modeo"
)
cursor = conn.cursor()

sql = "INSERT INTO müsteri (`Cihaz Seri No`,`İsim`) VALUES (%s, %s)"
countError = 0
for i in range(len(all_rows)):
    try:
        cursor.execute(sql,all_rows[i])
    except:
        count = 0
    


conn.commit()
conn.close()
