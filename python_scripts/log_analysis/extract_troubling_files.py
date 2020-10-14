import re
import os

def extract_file_names(src):

    log = open(src).read()
    pat = r'^\[systems/smart_contracts/(0x[\w]+.sol),.*?'
    result = re.findall(pat, log, re.MULTILINE)
    return result



if __name__=='__main__':
    src = 'function_extraction_error.log'
    res = extract_file_names(src)
    dst = 'extracted_files.txt'

    with open(dst, 'w') as w:
        for f in res:
            w.write(f'{f}\n')
    print(len(res), len(set(res)))
