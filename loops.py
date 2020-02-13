val = 11
lst = [11,11, 56, 14, 11, 756, 34, 90, 11, 11, 65,0, 11, 35]
start = 0; end = len(lst)
# count = lst.count(val)

# tmp = lst.index(val)

# start = tmp + 1
# index_lst = [tmp]
# #print(tmp)
# while start < end and count != 1:
#     tmp = lst.index(val,start)
#     start = tmp + 1
#     index_lst += [tmp]
#     count-=1
# print(index_lst)
# end = int(len(index_lst))
# for i in range(0, end):
#     lst.pop(int(index_lst[end - i -1]) )
# print(lst)
# lst.sort()

# for i in range(0, end):
#     lst.insert(int(index_lst[i]), val)

print(lst)
min = 0
i_min = 0;
gap = 1;
for i in range(0, end):
    if lst[i] != val:
        min = lst[i]
        i_min = i
        break
for i in range(i_min + 1, end):
    
    if(lst[i] == val):
        i+=1
        gap += 1
        continue
    for j in range(i , end):
        if lst[j] == val:
            j+=1
            continue
        if min > lst[j]:
            min = lst[j]
            i_min = j
    lst[i_min] = lst[i-gap]
    i_min = i
    lst[i-gap] = min 
    min = lst[i]
    gap = 1
print(lst)

lst = ["Khoa", "Hien", "Linh"]
gen = enumerate(lst, 12)
lst = list(gen)
print(lst)