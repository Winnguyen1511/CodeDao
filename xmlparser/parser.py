import xml.etree.ElementTree as et

root = et.parse('00501.xml').getroot()

print(root)
lstObj = []
# for obj in root.iter('object'):
#     lstObj.extend(obj)
# print(len(lstObj))
# for item in lstObj:
#     print(item.tag)

for element in root:
    if element.tag == 'object':
        print(type(element))
        lstObj.append(element)
print(len(lstObj))

# for element in root:
#     print(element.tag)
for element in lstObj:
    print(element.tag)