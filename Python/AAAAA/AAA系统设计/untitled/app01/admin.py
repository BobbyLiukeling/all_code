from django.contrib import admin
from app01 import models
# Register your models here.
admin.site.register(models.App01Apartment)
admin.site.register(models.App01Student)
admin.site.register(models.App01Area)
admin.site.register(models.App01Teacher)

'''后台注册'''