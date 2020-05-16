
import os,pdb
def file_name(file_dir):
    for root, dirs, files in os.walk(file_dir):

        # print('*******root_dir:',  root)  # 当前目录路径
        # print('*******la:', files)  # 当前目录路径
        # print('*******aaa:', dirs)  # 当前目录路径
        #
        for i in dirs[1:]:
            s = root+'\\'+i
            renamedir(s)

def renamedir(file_dir):
    for root, dirs,files in os.walk(file_dir):
        for i in files:
            print(i)
            os.rename(root+"\\"+i, root+"\\"+i.lower())














file_name('F:\GitHubCode\Code\Csjjg\严蔚敏《数据结构》的全部代码实现（C语言）')