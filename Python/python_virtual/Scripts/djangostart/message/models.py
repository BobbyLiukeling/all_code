from django.db import models

# Create your models here.
class UserMessage(models.Model):
     name = models.CharField(max_length=20,verbose_name=u"用户名")
     email = models.EmailField(verbose_name=u"邮箱")
     address = models.CharField(max_length=100,verbose_name=u"联系地址")
     message = models.CharField(max_length=500,verbose_name=u"留言信息")

     class Meta:
          verbose_name = u"留言信息"
          verbose_name_plural = verbose_name#不知道是干什么的
          # db_table = "user_message"#应该是指定数据库名称
          # ordering = "-object_id" #指定以object_id倒叙排序，假如object_id存在
