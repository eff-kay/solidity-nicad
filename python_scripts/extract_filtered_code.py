import  xml.etree.ElementTree as ET
import os, shutil

root_folder='duplicates/'

def filter_code_clones(xml_path, classids, filtered_path):
    global root_folder
    print(root_folder, 'root_folder')
    xml_path= root_folder+xml_path
    filtered_path = root_folder+filtered_path

    tree_1 = ET.parse(xml_path)
    root = tree_1.getroot()
    
    #create a list of sources
    
    #iterate through every dirty element and check if it exists in the type1 thing, remove it
    for i, elem in enumerate(tree_1[4:],4):
        head=4
        if elem.attrib['classid'] in classids:
            tree_1.remove(tree_1[head])
        else:
            head+=1

    tree_1.write(filtered_path)

if __name__=='__main__':
    original_path = 'originals/'
    type_2c_classids = ['1', '5', '7', '9', '11', '17', '19', '24', '30', '32', '35', '42', '49', '61', '62', '87', '90', '93', '94']
    type_2c = '2c.xml'
    filtered_path = 'code-filtered/'  

    filter_code_clones(original_path+type_2c, type_2c_classids, filtered_path+type_2c)
    print('done')