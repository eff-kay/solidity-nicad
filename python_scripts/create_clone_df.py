
import subprocess as sp
import os
import shutil
# from extract_functions_from_corpus import extract_lines_occupied
# from convert_xml_to_df import created_merged_df
# from calculate_statistics import calculate_statistics
# from remove_duplicates import remove_all_duplicates
# from extract_function_ids import extract_functions_ids, get_top_function_ids
from pathlib import Path

REPORT_NAMES = ['type1-report', 'type2-report', 'type2c-report', 'type3-1-report', 'type3-2-report', 'type3-2c-report']
folder_names = ['smart_contracts_functions-clones', 'smart_contracts_functions-blind-clones', 'smart_contracts_functions-consistent-clones']
file_names = []
file_names_with_source = []

for n in folder_names:
    file_names.append(n+'/'+n+'-0.00-classes.xml')
    file_names_with_source.append(n+'/'+n+'-0.00-classes-withsource.xml')
    file_names.append(n+'/'+n+'-0.30-classes.xml')
    file_names_with_source.append(n+'/'+n+'-0.30-classes-withsource.xml')
clone_types = ['type-1', 'type-3-1', 'type-2', 'type-3-2', 'type-2c', 'type-3-2c']

def run_nicad(config_name):
    for i,name in enumerate(REPORT_NAMES):
        nicad_cmd = './nicad6 functions sol systems/source-code {}-{}'.format(name, config_name)
        sp.run(nicad_cmd.split(' '))
        print('{} done'.format(name))

def take_diff(from_path, to_path):
    for type in clone_types:
        print('taking diff of {}'.format(type))
        cmd = 'diff {}/{} {}/{}'.format(from_path, type+'.xml', to_path, type+'.xml')
        sp.run(cmd.split(' '))
    

def move_and_rename_files(config_name):
    os.makedirs('systems/{}'.format(config_name), exist_ok=True)
    REPORT_NAMES = ['type1-report', 'type2-report', 'type2c-report', 'type3-1-report', 'type3-2-report', 'type3-2c-report']
    folder_names = ['source-code_functions-clones', 'source-code_functions-blind-clones', 'source-code_functions-consistent-clones']
    file_names = []
    file_names_with_source = []

    for n in folder_names:
        file_names.append(n+'/'+n+'-0.00-classes.xml')
        file_names_with_source.append(n+'/'+n+'-0.00-classes-withsource.xml')
        file_names.append(n+'/'+n+'-0.30-classes.xml')
        file_names_with_source.append(n+'/'+n+'-0.30-classes-withsource.xml')
    clone_types = ['type-1', 'type-3-1', 'type-2', 'type-3-2', 'type-2c', 'type-3-2c']

    for i, (n_with_source, n, ctype) in enumerate(zip(file_names_with_source, file_names, clone_types)):
        os.makedirs('systems/{}/withoutsource'.format(config_name), exist_ok=True)
        os.makedirs('systems/{}/withsource'.format(config_name), exist_ok=True)
        shutil.move('systems/{}'.format(n), 'systems/{}/withoutsource/{}'.format(config_name, ctype+'.xml'))
        shutil.move('systems/{}'.format(n_with_source), 'systems/{}/withsource/{}'.format(config_name, ctype+'.xml'))


if __name__=='__main__':
    if not Path('systems').exists():
        # IF SYSTEMS IS NOT PROVIDED THEN USE THE EXAMPLES
        check = input('We didnt detect any systems folder. We will use the sample dataset to execute cloning on. Are you sure you want to continue')
        os.makedirs('systems/source-code')
        shutil.copytree('data/smart_contracts', 'systems/source-code', dirs_exist_ok=True)

    config = 'macro'
    run_nicad(config)
    move_and_rename_files(config)

    # TODO: move the rest of these outside of this file
    # print("EXTRACT TOTAL FUNCTION LINES: use this number in calculating statistics")
    # functions_path =  'systems/source-code_functions.xml'
    # total_lines = extract_lines_occupied(functions_path)
    # print('total_lines = ', total_lines)

    # create a data folder if it does not exists
    # os.makedirs(f'python_scripts/data', exist_ok=True)

    # delete the config folder if it exists
    # shutil.rmtree(f'python_scripts/data/{config}', ignore_errors=True)
    # shutil.move(f'systems/{config}', f'python_scripts/data/{config}')
    
    # now we are in the manipulation domain
    # print("CHANGING DIRs")
    # os.chdir('python_scripts')

    # print("REMOVING DUPLICATES")
    # creates final/type-1.xml, final/type-2b.xml, ... final/type-3.xml
    # remove_all_duplicates(config)

    # print("EXTRACTING FUNCTION IDS")
    # extract_functions_ids(config)
    # get_top_function_ids('duplicates')
    # take_diff('systems/baseline', 'systems/min5')

    # created_merged_df()
    # file_path = 'duplicates'
    # calculate_statistics('duplicates/merged_df.p', total_loc = total_lines)

    print('done')







