from datetime import datetime

from django.db import models
from django.contrib.auth.models import AbstractUser

# Create your models here.

class UserProfile(AbstractUser):#扩展用户信息数据库
    birthday = models.DateTimeField(verbose_name=u"生日", null=True, blank=True, default=None)
    nick_name = models.CharField(max_length=30, verbose_name=u"昵称", default=u"")
    #birthday = models.DateTimeField(verbose_name=u"生日",null=True,blank=True,default=u"")
    gender = models.CharField(choices=(("male",u"男"),("femal",u"女")),default=u"",max_length=6)
    address = models.CharField(max_length=100,default=u"")
    mobile = models.CharField(max_length=11,blank=True,null=True)
    image = models.ImageField(upload_to="image/%Y/%m",default=u"image/default.img",max_length=100)#用户头像和默认头像

    class Meta:
        verbose_name = u"用户信息"
        verbose_name_plural = verbose_name

    def __str__(self):#admin 管理时返回的题目标题
        return self.username

    def unread_message(self):
        '''
        获取当前用户未读的信息的条数
        在当前方法内部 引入外部模块，防止循环引用
        '''
        from operation.models import UserMessage
        message = UserMessage.objects.filter(user = self.id,has_read = False)
        return message.count()


class EmailVerifyRecord(models.Model):#邮箱验证码
    code = models.CharField(max_length=20,verbose_name=u"验证码")
    email = models.EmailField(max_length=50,verbose_name=u"邮箱")
    send_type = models.CharField(max_length=10,choices=(("register",u"注册"),("forget",u"找回密码"),('update','重置邮箱')))
    # default=datetime.now获取当时间（是程序运行时的时间），default=datetime.now（）将括号加上以后所获取的时间为程序编写的时间
    send_time = models.DateTimeField(default=datetime.now)

    class Meta:
        verbose_name = u"邮箱验证码"
        verbose_name_plural = verbose_name

    def __str__(self):
        return '{0}{1}{2}'.format(self.code," ",self.email)

class Banner(models.Model):#轮播图
    title = models.CharField(max_length=100,verbose_name=u"标题")
    image = models.ImageField(upload_to="banner/%Y/%m",verbose_name=u"轮播图")
    url = models.URLField(max_length=200,verbose_name=u"访问地址")
    index = models.IntegerField(default=100,verbose_name=u"顺序")#使用编号大小来控制轮播图的顺序
    add_time  = models.DateTimeField(default=datetime.now,verbose_name=u"添加时间")

    class Meta:
        verbose_name = u"轮播图"
        verbose_name_plural = verbose_name