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
    if(count == 172):
        break
    data = []
    for title, cell in zip(headers, row):

        data.append(cell.value)
        
        if(title == "Musteri"):
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

#sql = "INSERT INTO müsteri (`İsim`,`Cihaz Seri No`) VALUES (%s, %s)"
#countError = 0
countName = 0
temp = ""
for i in range(len(all_rows)):
    print(all_rows[i][1] + "  ++")
    print("1")
    if(all_rows[i][1] == 'LAB'):
        print("1_1")
        continue
    else:
        print("1_2")
        sql = f"SELECT COUNT(*) FROM `müsteri` WHERE `İsim` = '{all_rows[i][1]}';"
        cursor.execute(sql)

        for x in cursor:
            countName = x[0]
            break
        print("Count of name : "+str(countName))
        if(countName == 1):
            print("1_2_1")
            sql = "SELECT `Cihaz Seri No` FROM `müsteri` WHERE İsim = '" + all_rows[i][1] + "';"
            cursor.execute(sql)

            for cihaz in cursor:
                temp = str(cihaz[0])
                break
            print("Mevcut cihaz seri no : " + temp)
            temp += "\n" + str(all_rows[i][0])

            sql = "UPDATE `müsteri` SET `Cihaz Seri No` = '" + temp + "' WHERE İsim = '" + all_rows[i][1] + "';"
            cursor.execute(sql)
        else:
            print("1_2_2")
            sql = "SELECT `Cihaz Seri No` FROM `müsteri`"
            cursor.execute(sql)
            list = []
            
            for item in cursor:
                list.append(item)
            
            if str(all_rows[i][0]) in list:
                print("1_2_2_1")
                print("Bir cihaz seri no birden çok müşteriye ait olamaz" + str(all_rows[i][0]))
            else:
                print("1_2_2_2")
                sql = "INSERT INTO müsteri(`İsim`,`Cihaz Seri No`) VALUES('" + str(all_rows[i][1]) + "','" + str(all_rows[i][0]) + "')"
                cursor.execute(sql)
    conn.commit()

conn.commit()
conn.close()

