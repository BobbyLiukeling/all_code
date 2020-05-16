import xadmin

from .models import Course,Lesson,Video,CourseResource


class LessonInline(object):
    model = Lesson
    extra = 0


class CourseResourceInline(object):
    model = CourseResource
    extra = 0


class CourseAdmin(object):
    list_display = ['name','desc','detail','degree','learn_times','student','fav_nums','image','click_nums','add_time']
    list_filter = ['name','desc','detail','degree','learn_times','student','fav_nums','image','click_nums','add_time']
    search_fields = ['name','desc','detail','degree','student','fav_nums','image','click_nums']
    ordering = ['-click_nums']#后台显示时，按照点击数进行倒序排列
    readonly_fields = ['click_nums']#设置click_nums为只读后台不可更改
    style_fields = {"detail": "ueditor"}
    '''
    当前数据表作为其他数据表外键时，可以将其他数据表注册到当前数据表的inlines中
    这样在后台管理xadmin中就可以在配置当前数据表时就一起配置其他将当前数据表作为外键的数据表
    注意：
        1、这样的配置不可层叠多个，只能有上下两层
        2、一个数据表可以同时将多个将其作为外键的数据表一起配置
    '''
    inlines = [LessonInline,CourseResourceInline]




class LessonAdmin (object):#章节信息
    list_display = ["course","name","add_time"]
    list_filter = ["course__name","name","add_time"]
    search_fields = ["course","name"]


class VideoAdmin(object):#视屏信息
    list_display = ["lesson","name","add_time",'url']
    list_filter = ["lesson__name","name","add_time",'url']
    search_fields = ["lesson","name"]


class CourseResourceAdmin(object):#资源文件
    list_display = ["course","name","download","add_time"]
    list_filter = ["course__name","name","download","add_time"]
    search_fields = ["course","name","download"]


xadmin.site.register(Course,CourseAdmin)
xadmin.site.register(Lesson,LessonAdmin)
xadmin.site.register(Video,VideoAdmin)
xadmin.site.register(CourseResource,CourseResourceAdmin)
