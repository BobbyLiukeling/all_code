from datetime import datetime

from django.db import models
# from operation.models import UserAsr

# Create your models here.

class CityDict(models.Model):#城市
    name = models.CharField(max_length=20,verbose_name=u"城市")
    desc = models.CharField(max_length=200,verbose_name=u"描述")
    add_time = models.DateTimeField(default=datetime.now)

    class Meta:
        verbose_name = u"城市"
        verbose_name_plural = verbose_name

    def __str__(self):
        return self.name

class CourseOrg(models.Model):#课程机构
    name = models.CharField(max_length=50,verbose_name=u"机构名称")
    desc = models.TextField(verbose_name=u"机构描述")
    category =  models.CharField(verbose_name="机构类别",max_length=20, choices=(('pxjg','培训机构'),('gr','个人'),('gx','高校')),default='pxjg')
    click_nums = models.IntegerField(verbose_name=u"点击数",default=0)
    fav_nums = models.IntegerField(verbose_name=u"收藏数",default=0)
    img = models.ImageField(verbose_name=u"封面",upload_to="org/%Y/%m")
    address = models.CharField(max_length=150,verbose_name=u"机构地址")
    city = models.ForeignKey(CityDict,verbose_name=u"所在城市",on_delete=models.CASCADE)
    students = models.IntegerField(default=0,verbose_name="学习人数")
    course_nums = models.IntegerField(default=0,verbose_name='课程数')
    add_time = models.DateTimeField(default=datetime.now)

    class Meta:
        verbose_name = u"课程机构"
        verbose_name_plural = verbose_name

    def __str__(self):
        return self.name

    def get_teacher_num(self):
        teacher_num = self.teacher_set.all().count()
        return teacher_num


class Teacher(models.Model):#教师信息
    org = models.ForeignKey(CourseOrg,verbose_name=u"所属机构",on_delete=models.CASCADE)
    name= models.CharField(max_length=50, verbose_name=u"教师名称")
    work_years = models.IntegerField(verbose_name=u"工作年限", default=0)
    work_company = models.CharField(max_length=50, verbose_name=u"就职公司")
    work_position = models.CharField(max_length=50, verbose_name=u"公司职位")
    points = models.CharField(max_length=50, verbose_name=u"教学特点")
    click_nums = models.IntegerField(verbose_name=u"点击数", default=0)
    fav_nums = models.IntegerField(verbose_name=u"收藏数", default=0)
    img = models.ImageField(verbose_name=u"教师封面", upload_to="teacher/%Y/%m",default='')
    add_time = models.DateTimeField(default=datetime.now)

    class Meta:
        verbose_name = u"教师"
        verbose_name_plural = verbose_name

    def __str__(self):
        return self.name

    def get_courses_nums(self):
        return self.course_set.all().count()


class ZeroTeacher(Teacher):
    class Meta:
        verbose_name = "没有被点击过的老师"
        verbose_name_plural = verbose_name
        proxy = True #当值为True时，后台不会为它重新生成一张数据表，默认为false，但是在后台管理时又会多出一个管理菜单

