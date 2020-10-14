import re
import pickle
import os
import pandas as pd
from collections import defaultdict

def extract_function_defs(functions, file_path, classids, save_path:str):
    f  = open(file_path).read()
    
    save_list = defaultdict(list)
    for i in map(str, classids):
        p = r'^(<class classid="{}"[\s\S]*?<\/class>)$'.format(i)
        cs = re.findall(p, f, re.MULTILINE)
        pre_cs = cs
        p = r'^<source[\s\S]*?function[ ]?([\s\S]*?)\([\s\S]*<\/source>$'
        all_fs = re.findall(p, cs[0], re.MULTILINE)
        if len(all_fs)==0:
            p = r'^<source[\s\S]*?>([\s\S]*?)<\/source>$'
            cs = re.findall(p, cs[0], re.MULTILINE)
            p = r'[\s\S]*?function[ ]?([\s\S]*?)\([\s\S]*?$'
            all_fs = re.findall(p, cs[0], re.MULTILINE)
            if len(all_fs)==0:
                print('still not caught', cs[0])

        if len(all_fs)>=1:
            # print(all_fs[0])
            if all_fs[0] in functions:
                p = r'^<source[\s\S]*?function (%s\([\s\S]*?\{[\s\S]*?\})[\s\S]*?<\/source>$'%(all_fs[0])
                func_def = re.findall(p, pre_cs[0], re.MULTILINE)
                save_list[all_fs[0]] += func_def
        else:
            # print(all_fs)
            if all_fs=="'symbol'":
                p = r'^<source[\s\S]*?function[ ]?symbol\([\s\S]*?(\{[\s\S]*?\})<\/source>$'
                func_def = re.findall(p, pre_cs, re.MULTILINE)
                # print(func_def)
        # print(f'class id {i} done')
    os.makedirs(f'{save_path}/function-defs/', exist_ok=True) 
    for k,v in save_list.items():
        save_path_ob = open(f'{save_path}/function-defs/{k}.txt', 'a+')
        [save_path_ob.write(w+'\n') for w in v]

def extrac_code(file_path, classids, save_path):
    f  = open(file_path).read()
    
    save_list = []
    for i in map(str, classids):
        p = r'^(<class classid="{}"[\s\S]*?<\/class>)$'.format(i)
        cs = re.findall(p, f, re.MULTILINE)
        pre_cs = cs
        p = r'^<source[\s\S]*?function[ ]?([\s\S]*?)\([\s\S]*<\/source>$'
        all_fs = re.findall(p, cs[0], re.MULTILINE)
        if len(all_fs)==0:
            p = r'^<source[\s\S]*?>([\s\S]*?)<\/source>$'
            cs = re.findall(p, cs[0], re.MULTILINE)
            p = r'[\s\S]*?function[ ]?([\s\S]*?)\([\s\S]*?$'
            all_fs = re.findall(p, cs[0], re.MULTILINE)
            if len(all_fs)==0:
                print('still not caught', cs[0])

        save_list.append(all_fs)
        print(f'class id {i} done')
    pickle.dump(save_list, open(save_path, 'wb'))

def get_classids(file_path)->int:
    a = open(file_path).read()
    b = re.findall('.*?classid="(\d+)".*', a)

    return b

def extract_functions_ids(config):
    original_paths = ['type-1', 'type-2', 'type-2c', 'type-3-1', 'type-3-2', 'type-3-2c']
    print('extr')
    os.makedirs('duplicates/code-filtered', exist_ok=True)
    os.makedirs('duplicates/function-ids', exist_ok=True)
    for filepath in original_paths:
        print(f'starting {filepath}')
        classids = get_classids('duplicates/final/'+filepath+".xml")
        print(f'classsids {len(classids)}')
        complete_file_path = 'data/{}/withsource/{}'.format(config, filepath+'.xml')
        save_path_pickle = 'duplicates/function-ids/{}'.format(filepath+'.p')
        extrac_code(complete_file_path, classids, save_path_pickle)
       
        save_path_txt = open('duplicates/function-ids/{}'.format(filepath+'.txt'), 'w')
        functions = pickle.load(open(save_path_pickle, 'rb'))

        for f in functions:
            save_path_txt.write(f[0]+'\n') 

        print(len(classids), len(functions))

def convert_to_combined_csv():
    original_paths = ['type-1', 'type-2', 'type-2c', 'type-3-1', 'type-3-2', 'type-3-2c']

    res =[]
    for type in original_paths:
        file_path = 'duplicates/function-ids/{}'.format(type+'.p')

        a = pickle.load(open(file_path, 'rb'))
        res.append(a)

    b = pd.DataFrame(res)
    open('duplicates/function-ids/combined_functions.csv', 'w+').write(b.to_csv())


def extract_function_bodies(functions, config):
    original_paths = ['type-1', 'type-2', 'type-2c', 'type-3-1', 'type-3-2', 'type-3-2c']
    os.makedirs('duplicates/code-filtered', exist_ok=True)
    os.makedirs('duplicates/function-ids', exist_ok=True)
    for filepath in original_paths:
        print(f'starting {filepath}')
        classids = get_classids('duplicates/final/'+filepath+".xml")
        print(f'classsids {len(classids)} ')
        complete_file_path = 'data/{}/withsource/{}'.format(config, filepath+'.xml')
        save_path = 'duplicates/function-ids'
        extract_function_defs(functions, complete_file_path, classids, save_path)

def get_top_function_ids(path):
    original_paths = ['type-1', 'type-2', 'type-2c', 'type-3-1', 'type-3-2', 'type-3-2c']

    save_path = open(f'{path}/function-ids/all-ids.txt', 'w')
    for file in original_paths:
        # ids = file.read().split('\n')
        file_data = open(f'{path}/function-ids/{file}.txt').read()
        # print(f'{file}', file_data)
        save_path.write(file_data)
    save_path.flush()

    top20_functions = pd.Series(open(f'{path}/function-ids/all-ids.txt', 'r').read().split('\n')[:-1]).value_counts()[:20]

    print(top20_functions.to_latex())
    top20_path = open(f'{path}/function-ids/top20.txt', 'w')
    
    [top20_path.write(f'{x}\n') for x in top20_functions.index]
    return top20_functions

if __name__ == "__main__":
    #get_top_function_ids('macro-duplicates')
    top20_fids = open(f'duplicates/function-ids/top20.txt', 'r').read()
    fids:list = [l for l in top20_fids.split('\n')]
    extract_function_bodies(fids, 'macro')
    # # extract_functions_ids('min4')
    # convert_to_combined_csv()
    # print('done')
