import pandas as pd
import xml.etree.ElementTree as ET
import re
import pickle
# THiS DOES NOT WORK
# def extract_total_functions(path):
#     tree = ET.parse(path)
#     root = tree.getroot()
#     elements =[]
#     for i, elem in enumerate(root):
#         d={}
#         d['startline'] = elem.attrib['startline']
#         d['endline'] = elem.attrib['endline']
#         d['lines'] = d['endline']-d['startline']
#         elements.append(d)
#     df = pd.DataFrame(elements)
#     print(df.size)

def extract_total_functions_using_regex(path):
    xml = open(path).read()
    p = r'^<source file=[\s\S]*? startline=([\s\S]*?) endline=([\s\S]*?)\>[\s\S]*?<\/source>'
    sources = re.findall(p, xml, re.MULTILINE)

    df = pd.DataFrame(sources)
    df.columns = ['startline', 'endline']
    pickle.dump(df, open('all_functions.p', 'wb'))
    return len(sources)

def extract_lines_occupied(path):
    xml = open(path).read()
    p = r'^<source file=([\s\S]*?) [\s\S]*?>$([\s\S]*?)^<\/source>$'
    source_bodies = re.findall(p, xml, re.MULTILINE)  

    line_count = []
    for f, s in source_bodies:
        p = r'^[\s\S]*?\n$'
        flines = re.findall(p, s, re.MULTILINE)
        # print(flines, list(map(lambda x: x.split('\n'), flines)))
        line_count.append([f.replace('"','').split('/')[-1], len(flines[0].split('\n')[1:-1])])

    df = pd.DataFrame(line_count)

    df.columns = ['file', 'total_lines']
    pickle.dump(df, open('all_functions_line_counted.p', 'wb'))

    return df['total_lines'].sum()
    # for s in sources:
    # print(source_bodies[:2])
    # df = pd.DataFrame(sources)
    # df.columns = ['startline', 'endline']
    # pickle.dump(df, open('all_functions.p', 'wb'))
    # return len(sources)


def count_lines(df_path):
    df = pickle.load(open(df_path, 'rb'))
    return df['total_lines'].sum()

if __name__=="__main__":
    path = "systems/source-code_functions.xml"
    # path = "data/min1/type-1.xml"
    # print(extract_lines_occupied(path))
    df_path = 'all_functions_line_counted.p'
    print(count_lines(df_path))

    print('done')