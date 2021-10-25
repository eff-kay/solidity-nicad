import os
import xml.etree.ElementTree as ET
import pandas as pd 
import pickle
from calculate_statistics import calculate_statistics

root_folder='' 

def convert_file_with_subelem(clone_type, xml_file, df_file):
    global root_folder

    xml_file = root_folder+xml_file
    df_file = root_folder+'subelem_'+df_file
    tree = ET.parse(xml_file)

    root = tree.getroot()

    elements = []
    for i, elem in enumerate(root[4:]):
        for source in elem[:]:
            d={}
            d['classid'] = elem.attrib['classid']
            d['nclones'] = int(len(elem[:]))
            d['nlines'] = int(elem.attrib['nlines'].replace('"',''))
            # d['nlines'] = 0
            # d['nlines'] += int(source.attrib['endline']) - int(source.attrib['startline'])
            d['similarity'] = elem.attrib['similarity']
            d['startline'] = source.attrib['startline']
            d['endline'] = source.attrib['endline']
            d['file'] = source.attrib['file']
            d['type'] = clone_type
            elements.append(d)
        
    df = pd.DataFrame(elements)
    pickle.dump(df, open(df_file, 'wb'))

def convert_file(xml_file, df_file):
    global root_folder

    xml_file = root_folder+xml_file
    df_file = root_folder+df_file
    tree = ET.parse(xml_file)

    root = tree.getroot()

    elements = []
    for i, elem in enumerate(root[4:]):
        d={}
        d['classid'] = elem.attrib['classid']
        d['nclones'] = int(len(elem[:]))
        d['nlines'] = 0
        # for source in elem[:]:
        #     d['nlines'] += int(source.attrib['endline']) - int(source.attrib['startline'])
        d['nlines']= int(elem.attrib['nlines'])* int(len(elem[:])) 
        d['similarity'] = elem.attrib['similarity']
        elements.append(d)
        
    df = pd.DataFrame(elements)
    pickle.dump(df, open(df_file, 'wb'))
    nclones = df['nclones'].astype(int).sum()
    nlines  = df['nlines'].astype(int).sum()
    print(df['nlines'])
    print(f'classes = {df.shape[0]}, \
        fragments={nclones}, \
        , lines = {nlines}')



def created_merged_df():
    global root_folder
    root_folder='duplicates/'
    type1 = 'final/type-1.xml'
    type1df = 'final/type-1.p'

    type2b = 'final/type-2.xml'
    type2bdf = 'final/type-2.p'

    type2c = 'final/type-2c.xml'
    type2cdf = 'final/type-2c.p'

    type3 = 'final/type-3-1.xml'
    type3df = 'final/type-3-1.p'
    
    type3b = 'final/type-3-2.xml'
    type3bdf = 'final/type-3-2.p'
    
    type3c= 'final/type-3-2c.xml'
    type3cdf = 'final/type-3-2c.p'

    os.makedirs('duplicates/subelem_final', exist_ok=True)
#    file_pairs = [(type1, type1df), (type2c, type2cdf), (type3, type3df), (type3b, type3bdf), (type3c, type3cdf)]
#    for x,y in file_pairs[:]:
#        print('starting', x,y)
#        convert_file(x,y)
#        print("done")

    file_pairs = [('type-1',type1, type1df), ('type-2', type2b, type2bdf), ('type-2c',type2c, type2cdf), ('type-3',type3, type3df), ('type-3-2', type3b, type3bdf), ('type-3-2c',type3c, type3cdf)]
    for ctype, x,y in file_pairs[:]:
        print('starting', ctype, x,y)
        convert_file_with_subelem(ctype, x,y)
        print("done")
    
    fs = os.listdir('duplicates/subelem_final')
    merged_df = pd.concat([pickle.load(open('duplicates/subelem_final/'+x, 'rb')) for x in fs])
    
    pickle.dump(merged_df, open('duplicates/merged_df.p', 'wb'))

if __name__ == "__main__":
    created_merged_df()