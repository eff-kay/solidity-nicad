
import re
import pandas as pd
from numpy import source
from hashlib import sha256

def extract_function_id(source_code):
    id = ''
    p = r'function ([\s\S]*?)\{[\s\S]*\}'
    matches = re.findall(p, source_code, re.MULTILINE)
    id = matches[0]
    return id

def extract_contracts(path):
    xml = open(path).read()
    p = r'^<source file=([\s\S]*?) startline=([\s\S]*?) endline=([\s\S]*?)>$([\s\S]*?)^<\/source>$'
    matches = re.findall(p, xml, re.MULTILINE)
    # print([extract_function_id(m[3]) for m in matches])
    matches = [(m[0], m[1], m[2], extract_function_id(m[3]), sha256(m[3].encode()).hexdigest()) for m in matches]
    df = pd.DataFrame(matches)
    filename = path.split('.')[0]
    print('saving file', filename)
    df.columns = ['filename', 'startline', 'endline', 'function_id', 'hash']
    df.to_csv(open(filename + ".csv", 'w+'))


def create_dfs(paths):
    for path in paths:
        extract_contracts(path)


def comparison(result, corpus_contracts, openzeppelin_contracts):
    for res_path, cpath, oz_path in zip(result, corpus_contracts, openzeppelin_contracts):
        print(cpath, oz_path)
        corpus_df = pd.read_csv(open(cpath))
        oz_df = pd.read_csv(open(oz_path))
        corpus_df = corpus_df.merge(oz_df, on='hash', how='left')
        corpus_df.to_csv(open(f'{res_path}.csv', 'w+'))

        corpus_df.isnull()
if __name__=="__main__":
    # path = 'test_data/openzeppelin_contracts.xml'
    base_path = 'data'
    code_block = 'functions' #functions| contracts

    corpus_contracts = [f'corpus_{code_block}{x}.xml' for x in ('', '-consistent', '-blind')]
    openzeppelin_contracts = [f'openzeppelin_{code_block}{x}.xml' for x in ('', '-consistent', '-blind')]

    corpus_contracts = [f'{base_path}/{path}' for path in corpus_contracts]
    openzeppelin_contracts = [f'{base_path}/{path}' for path in  openzeppelin_contracts]
    paths = corpus_contracts[:1] + openzeppelin_contracts[:1]
    print(create_dfs(paths))

    corpus_contracts = [f'corpus_{code_block}{x}.csv' for x in ('', '-consistent', '-blind')]
    openzeppelin_contracts = [f'openzeppelin_{code_block}{x}.csv' for x in ('', '-consistent', '-blind')]

    corpus_contracts = [f'{base_path}/{path}' for path in corpus_contracts]
    openzeppelin_contracts = [f'{base_path}/{path}' for path in  openzeppelin_contracts]
    paths = corpus_contracts[:1] + openzeppelin_contracts[:1]
    result = [f'result_csv_1/{x}' for x in ('type-1', 'type-2c', 'type-2b')]
    result = result[:1]

    print(comparison(result, corpus_contracts, openzeppelin_contracts))

