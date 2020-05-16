import xadmin

from .models import UserProfile,VerifyCodede


class UserProfileAdmin(object):
    list_display = ['birthday','name','gender','mobile']
    list_filter = ['birthday','name','gender','mobile']
    search_filter = ['birthday','name','gender','mobile']


class VerifyCodedeAdmin(object):
    list_display = ['code','mobile','add_time']
    list_filter = ['code','mobile','add_time']
    search_filter = ['code','mobile']


# xadmin.site.register(UserProfile,UserProfileAdmin)
xadmin.site.register(VerifyCodede,VerifyCodedeAdmin)