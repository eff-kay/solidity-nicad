import pandas as pd
import xml.etree.ElementTree as ET
import re
import pickle
def extract_total_functions(path):

    tree = ET.parse(path)

    root = tree.getroot()

    elements =[]
    for i, elem in enumerate(root):
        d={}
        d['startline'] = elem.attrib['startline']
        d['endline'] = elem.attrib['endline']

        d['lines'] = d['endline']-d['startline']
        elements.append(d)

    df = pd.DataFrame(elements)

    print(df.size)

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
    p = r'^<source[\s\S]*?>$([\s\S]*?)^<\/source>$'
    source_bodies = re.findall(p, xml, re.MULTILINE)  

    line_count = []
    for s in source_bodies:
        p = r'^[\s\S]*?\n$'
        flines = re.findall(p, s, re.MULTILINE)
        line_count.append(len(flines))

    print(line_count) 
    df = pd.DataFrame(line_count)

    df.columns = ['total_lines']
    pickle.dump(df, open('all_functions_line_counted.p', 'wb'))

    return len(line_count)
    # for s in sources:
    # print(source_bodies[:2])
    # df = pd.DataFrame(sources)
    # df.columns = ['startline', 'endline']
    # pickle.dump(df, open('all_functions.p', 'wb'))
    # return len(sources)

if __name__=="__main__":

    path = "data/smart_contracts_functions.xml"
    # path = "data/min1/type-1.xml"
    print(extract_lines_occupied(path))