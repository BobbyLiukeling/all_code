from django.db import models

# Create your models here.
#定义字段
class Ariticle(models.Model):
    title = models.CharField(max_length=20,default="title")
    content = models.TextField(null=True)
    pub_time = models.DateTimeField(null = True) #当前时间
    def __str__(self):
        return self.title