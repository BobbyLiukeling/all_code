from datetime import datetime

from django.db import models
from django.contrib.auth.models import AbstractUser
# Create your models here.


class UserProfile(AbstractUser):#扩展用户信息数据库
    birthday = models.DateTimeField(verbose_name=u"生日", null=True, blank=True, default=None)
    name = models.CharField(max_length=30, verbose_name=u"昵称", null=True, blank=True)
    gender = models.CharField(choices=(("male",u"男"),("female",u"女")),default="",max_length=6)
    # address = models.CharField(max_length=100,default=u"")
    mobile = models.CharField(max_length=11,verbose_name='电话号码',null=True,blank=True)
    # image = models.ImageField(upload_to="image/%Y/%m",default=u"image/default.img",max_length=100)#用户头像和默认头像

    class Meta:
        verbose_name = u"用户信息"
        verbose_name_plural = verbose_name

    def __str__(self):#admin 管理时返回的题目标题
        return self.username

    # def unread_message(self):
    #     '''
    #     获取当前用户未读的信息的条数
    #     在当前方法内部 引入外部模块，防止循环引用
    #     '''
    #     from operation.models import UserMessage
    #     message = UserMessage.objects.filter(user = self.id,has_read = False)
    #     return message.count()


class VerifyCodede(models.Model):
    code = models.CharField(max_length=6,verbose_name='验证码')
    mobile = models.CharField(max_length=11,verbose_name='电话号码')
    add_time = models.DateTimeField(default=datetime.now, verbose_name=u"添加时间")

    class Meta:
        verbose_name = u"短信验证码"
        verbose_name_plural = verbose_name

    def __str__(self):#admin 管理时返回的题目标题
        return self.code