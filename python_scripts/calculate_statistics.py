
import pickle
import pandas as pd

def calculate_statistics(file_path):
    m = pickle.load(open(file_path, 'rb'))

    d=[]

    file_pairs = ['type-1', 'type-2', 'type-2c', 'type-3', 'type-3-2', 'type-3-2c']
    for ctype in file_pairs:
        fr = m[m['type']==ctype].count()[0]
        cl = m[m['type']==ctype]['classid'].unique().size
        fi = m[m['type']==ctype]['file'].unique().size 
        loc = m[m['type']==ctype]['nlines'].sum() 
        per = (loc/74529)*100
        d.append([cl,fr,fi,loc,'{:.2f}'.format(per)])
        # print(cl,fr,fi,loc,'{:.2f}'.format(per))

    d_df = pd.DataFrame(d)
    d_df[4] = d_df[4].astype(float)
    total = d_df.sum()
    total.name = 6
    d_df = d_df.append(total)
    print(d_df.to_latex())

    return d_df


def combine_dfs():
    all_dfs = ['min1', 'min2', 'min3', 'min4', 'min5','min10']
    a = [calculate_statistics('merged_dfs/'+df+'.p').iloc[6] for df in all_dfs]
    a_df = pd.DataFrame(a)
    print(list(a_df[4]))




if __name__ == "__main__":
    # file_path = gg'duplicates/merged_df.p'
    # calculate_statistics(file_path)
    combine_dfs()