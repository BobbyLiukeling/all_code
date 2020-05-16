from django.contrib import admin

# Register your models here.
from . import models
class ArticleAdmin(admin.ModelAdmin):
    list_display=('id','pub_time', 'title','content',)#支持list和tuple
    list_filter = ('pub_time',)

admin.site.register(models.Ariticle, ArticleAdmin)