import  xml.etree.ElementTree as ET
import os, shutil
from convert_xml_to_df import created_merged_df

root_folder = ''
def remove_type1(type1_path, dirty_path, new_path):
    global root_folder
    print(root_folder, 'root_folder')
    type1_path= root_folder+type1_path
    dirty_path = root_folder+dirty_path
    new_path = root_folder+new_path

    type1f = open(type1_path)
    f = open(dirty_path)
    #newf = open(new_path)

    tree_1 = ET.parse(type1f)
    root = tree_1.getroot()
    
    dirty_tree = ET.parse(f)
    dirty_root = dirty_tree.getroot()
 
    #create a list of sources
    sources = []
    for elem in root[4:]:
        sources.extend(elem[:])
    
    sources = [(x.attrib['file'],x.attrib['startline'], x.attrib['endline']) for x in sources[:]]
     
    #iterate through every dirty element and check if it exists in the type1 thing, remove it
    for i, elem in enumerate(dirty_root[4:],4):
        head=0
        for j, source in enumerate(elem[:]):
                if (source.attrib['file'], source.attrib['startline'], source.attrib['endline']) in sources:
                        dirty_root[i].remove(dirty_root[i][head])
                else:
                    head+=1
    
    head=4 
    for i, elem in enumerate(dirty_root[4:], 4):
        if len(elem[:])==0:
            # print(i,head, dirty_root[head].attrib['classid'])
            dirty_root.remove(dirty_root[head])
        else:
            head+=1
    
    dirty_tree.write(new_path)


def remove_all_duplicates(config):
    global root_folder
    type1_path = 'data/{}/withoutsource/type-1.xml'.format(config)
    type2b_path = 'data/{}/withoutsource/type-2.xml'.format(config)
    type2c_path = 'data/{}/withoutsource/type-2c.xml'.format(config)
    type3_path = 'data/{}/withoutsource/type-3-1.xml'.format(config)
    type3b_path = 'data/{}/withoutsource/type-3-2.xml'.format(config)
    type3c_path = 'data/{}/withoutsource/type-3-2c.xml'.format(config)

    os.makedirs('duplicates/final', exist_ok=True)
    parent_folder = 'duplicates/'
    #remote type1 from the rest
    type2b_filtered_type1 = 'type2b_filtered_type1.xml'
    type2c_filtered_type1 = 'type2c_filtered_type1.xml'
    type3_filtered_type1 = 'type3_filtered_type1.xml'
    type3b_filtered_type1 = 'type3b_filtered_type1.xml'
    type3c_filtered_type1 = 'type3c_filtered_type1.xml'
    
    remove_type1(type1_path, type2b_path, parent_folder+type2b_filtered_type1)
    remove_type1(type1_path, type2c_path,  parent_folder+type2c_filtered_type1)
    remove_type1(type1_path, type3_path,  parent_folder+type3_filtered_type1)
    remove_type1(type1_path, type3b_path,  parent_folder+type3b_filtered_type1)
    remove_type1(type1_path, type3c_path,  parent_folder+type3c_filtered_type1)

    root_folder = 'duplicates/' 
    print('done')
    
    #remove type2c from all type3
    type3_filtered_type2c = 'type3_filtered_type2c.xml'
    type3b_filtered_type2c = 'type3b_filtered_type2c.xml'
    type3c_filtered_type2c = 'type3c_filtered_type2c.xml'

    remove_type1(type2c_filtered_type1, type3_filtered_type1, type3_filtered_type2c)
    remove_type1(type2c_filtered_type1, type3b_filtered_type1, type3b_filtered_type2c)
    remove_type1(type2c_filtered_type1, type3c_filtered_type1, type3c_filtered_type2c)

    print('done')
    
    #remove type2b from all type3
    type3_filtered_type2b = 'type3_filtered_type2b.xml'
    type3b_filtered_type2b = 'type3b_filtered_type2b.xml'
    type3c_filtered_type2b = 'type3c_filtered_type2b.xml'
    
    remove_type1(type2b_filtered_type1, type3_filtered_type2c, type3_filtered_type2b)
    remove_type1(type2b_filtered_type1, type3b_filtered_type2c, type3b_filtered_type2b)
    remove_type1(type2b_filtered_type1, type3c_filtered_type2c, type3c_filtered_type2b)
    print('done')

    # remove type2c from type2b 
    type2b_filtered_type1_type2c = 'type2b_filtered_type1_type2c.xml'
    remove_type1(type2c_filtered_type1, type2b_filtered_type1, type2b_filtered_type1_type2c)
    print('done')

    #remove type3 from type3b and type3c
    type3b_filtered_type2b_type3 = 'type3b_filtered_type2b_type3.xml'
    remove_type1(type3_filtered_type2b, type3b_filtered_type2b, type3b_filtered_type2b_type3)

    type3c_filtered_type2b_type3 = 'type3c_filtered_type2b_type3.xml'
    remove_type1(type3_filtered_type2b, type3c_filtered_type2b, type3c_filtered_type2b_type3)
    print('done')
   
    #remove type3c from type3b
    type3b_filtered_type2b_type3_type3c = 'type3b_filtered_type2b_type3_type3c.xml'
    remove_type1(type3c_filtered_type2b_type3, type3b_filtered_type2b_type3, type3b_filtered_type2b_type3_type3c)
    print('done')


    os.makedirs('duplicates/final', exist_ok=True)
    shutil.copy(type1_path, 'duplicates/final/type-1.xml')
    shutil.move('duplicates/'+type2c_filtered_type1, 'duplicates/final/type-2c.xml')
    shutil.move('duplicates/'+type2b_filtered_type1_type2c, 'duplicates/final/type-2.xml')
    shutil.move('duplicates/'+type3_filtered_type2b, 'duplicates/final/type-3-1.xml')
    shutil.move('duplicates/'+type3c_filtered_type2b_type3, 'duplicates/final/type-3-2c.xml')
    shutil.move('duplicates/'+type3b_filtered_type2b_type3_type3c, 'duplicates/final/type-3-2.xml')
    
    # TODO: enable this when we want to do the correlation calculation from scratch
    #created_merged_df()

if __name__=="__main__":
    remove_all_duplicates('baseline')
