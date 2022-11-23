import os

def main(startpath):
    for root, dirs, files in os.walk(startpath):
        level = root.replace(startpath, '').count(os.sep)
        indent = ' ' * 4 * (level)
        print('{}{}/'.format(indent, os.path.basename(root)))
        subindent = ' ' * 4 * (level + 1)
        for f in files:
            print('{}{}'.format(subindent, f))



if __name__ == '__main__':


    path_project_base = os.getcwd()
    
    path_file = os.path.dirname(__file__)

    os.chdir(path_file)

    main(path_file)
    os.chdir(path_project_base)

