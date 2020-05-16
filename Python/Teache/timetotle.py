
from pymediainfo import MediaInfo
# media_info = MediaInfo.parse("F:/BaiduYunDownload/基础班/高数/001—20考研数学基础课程高等数学第一章极限与连续（1）【公众号：给力考研资料】免费分享.mp4")
import os,pdb


def file_name(file_dir):
    min = 0
    sec = 0
    for files in os.walk(file_dir):
        F = files[0]
        a = 1
        for f in files[2]:
            # print(files)
            # pdb.set_trace()
            if(f.split(".")[-1] == 'mp4'):
                media_info = MediaInfo.parse(F+"\\"+f)
                # print(F+"\\"+f)
                data = media_info.to_json()
                # pdb.set_trace()
                time = eval(data)["tracks"][0]['other_duration'][4]

                hour = int(time.split(":")[0])*60 #加上前面的小时
                print(int(time.split(":")[1])+hour)
                min = min+int(time.split(":")[1])+hour
                print(str(a)+" totle---"+str(min/60))
                a = a+1
                # print(min)
                # pdb.set_trace()
                sec = sec+int(time.split(":")[2][0:2])
                # print(min / 60 + sec / 3600)
    print(min/60 + sec/3600)
    # print(min/60)


file_name('E:\\BaiduDownload\\0000A')   #程序入口
