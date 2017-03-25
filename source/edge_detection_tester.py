import sys, os

exe_path = "C:\\Users\\stefan-1212\\Desktop\\vision2\\HU-Vision-1617-groep2\\source\\ExternalDLL\\Release\\ExternalDLL.exe"



amount = 10000
var_list = []
for i in range(amount):
    var_list.append(os.system(exe_path))
for i in var_list:
    print(i/1000)
print()
print("max =",max(var_list)/1000)
print("min =",min(var_list)/1000)
print("average =", (sum(var_list)/amount)/1000)
    
#print((sum/amount)/1000, "miliseconds")
