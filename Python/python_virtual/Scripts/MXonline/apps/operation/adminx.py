import xadmin

from .models import UserAsr,CourseComment,UserFavorate,UserMessage,UserCourse

class UserAsrAdmin(object):#用户咨询
    list_display= ["name","mobile","course_name","add_time"]
    list_filter = ["name","mobile","course_name","add_time"]
    search_fields = ["name","mobile","course_name"]


class CourseCommentAdmin(object):#课程评论
    list_display = ["user", "course", "comment", "add_time"]
    list_filter =["comment", "add_time"]
    search_fields =["user", "course", "comment"]


class UserFavorateAdmin(object):#用户收藏
    list_display = ["user", "fav_id", "fav_type", "add_time"]
    list_filter =["fav_id", "fav_type", "add_time"]
    search_fields =["user", "fav_id", "fav_type"]


class UserMessageAdmin(object):#用户消息
    list_display = ["user", "message", "has_read", "add_time"]
    list_filter =["message", "has_read", "add_time"]
    search_fields =["user", "message", "has_read"]


class UserCourseAdmin(object):
    list_display = ["user", "course", "add_time"]
    search_fields =["user", "course"]


xadmin.site.register(UserAsr,UserAsrAdmin)
xadmin.site.register(CourseComment,CourseCommentAdmin)
xadmin.site.register(UserFavorate,UserFavorateAdmin)
xadmin.site.register(UserMessage,UserMessageAdmin)
xadmin.site.register(UserCourse,UserCourseAdmin)
