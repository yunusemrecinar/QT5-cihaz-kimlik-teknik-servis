import xlrd
wb = xlrd.open_workbook("C:\\Users\emrecinar\Desktop\modeo.xlsx")

ws = wb.sheet_by_index(0)

print(ws.cell_value(3,13),end="\t")

#for i in range(2):
#    for j in range(ws.ncols):
#        print(ws.cell_value(i,j),end="\t")
#    print('')
