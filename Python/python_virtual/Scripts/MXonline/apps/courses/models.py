from datetime import datetime

from django.db import models
from DjangoUeditor.models import UEditorField

from organization.models import CourseOrg,Teacher


# Create your models here.
class Course(models.Model):#定义课程
    course_org = models.ForeignKey(CourseOrg,verbose_name="课程机构",null=True,on_delete=models.CASCADE)
    teacher = models.ForeignKey(Teacher,verbose_name='讲师',null=True,on_delete=models.CASCADE)
    name = models.CharField(max_length=50,verbose_name=u"课程")
    # (width=1200, height=600, imagePath="article/ueditor/",
    # filePath="article/ueditor/", verbose_name=u"文章内容")
    desc = UEditorField(verbose_name=u"课程描述",width=1200, height=600,)
    # desc = models.CharField(max_length=300, verbose_name=u"课程描述")
    detail = models.TextField(verbose_name=u"课程详情")
    degree = models.CharField(choices=(("cj",u"初级"),('zj',u"中级"),('gj',u"高级")),max_length=5)#课程难度
    learn_times = models.IntegerField(default=0,verbose_name=u"学习时长（分钟数）")
    student = models.IntegerField(default=0,verbose_name=u"学习人数")
    fav_nums= models.IntegerField(default=0,verbose_name=u"收藏人数")
    image = models.ImageField(upload_to="courses/%Y/%m",verbose_name=u"封面")
    click_nums = models.IntegerField(default=0,verbose_name=u"课程点击数")
    tag = models.CharField(default='',max_length=10,verbose_name='课程标签')
    add_time = models.DateTimeField(default=datetime.now,verbose_name=u"课程添加时间")

    class Meta:
        verbose_name = u"课程"
        verbose_name_plural = verbose_name

    def __str__(self):
        return self.name

    def get_lesson_count(self):
        lesson_count = self.lesson_set.all().count()#获取到这门课程的所有章节数，前提是course是lesson的外键,不在同一文件下也可以用
        return  lesson_count

    def get_lesson(self):
        lesson = self.lesson_set.all()#获取到这门课程的所有章节，前提是course是lesson的外键,不在同一文件下也可以用
        return lesson


class Lesson (models.Model):#章节信息
    #on_delete=models.CASCADE连锁删除，使用course的课course作为外键
    course = models.ForeignKey(Course,verbose_name=u"课程",on_delete=models.CASCADE)
    name = models.CharField(max_length=100,verbose_name=u"章节名")
    add_time = models.DateTimeField(default=datetime.now,verbose_name=u"添加时间")

    class Meta:
        verbose_name = u"章节"
        verbose_name_plural = verbose_name

    def get_lesson_video(self):
        video = self.video_set.all()
        return video


    # def __str__(self):
    #     return self.course

class Video(models.Model):#视屏信息
    lesson = models.ForeignKey(Lesson,verbose_name=u"章节",on_delete=models.CASCADE)
    name = models.CharField(max_length=100,verbose_name=u"视屏名")
    url = models.CharField(max_length=100,verbose_name='访问链接')
    add_time = models.DateTimeField(default=datetime.now,verbose_name=u"添加时间")

    class Meta:
        verbose_name = u"視屏"
        verbose_name_plural = verbose_name

    # def __str__(self):
    #     return self.lesson

class CourseResource(models.Model):#资源文件
    course = models.ForeignKey(Course,verbose_name=u"课程",on_delete=models.CASCADE)
    name = models.CharField(max_length=100, verbose_name=u"资源名称")
    download = models.FileField(upload_to="course/resource/%Y/%m",verbose_name=u"资源文件",max_length=100)
    add_time = models.DateTimeField(default=datetime.now, verbose_name=u"添加时间")

    class Meta:
        verbose_name = u"课程资源"
        verbose_name_plural = verbose_name

    def __str__(self):
        return self.name