import xadmin
from xadmin import views
from xadmin.plugins.auth import UserAdmin
from xadmin.layout import Fieldset, Main, Side, Row

from .models import EmailVerifyRecord,Banner,UserProfile


class BaseSetting(object):
    enable_themes = True#主题功能
    use_bootswatch = True


class GlobalSetting(object):
    site_title = "管理系统"#xadmin页头
    site_footer = "学网在线"#xadmin底部注释
    menu_style = "accordion"#收起页表


class EmailVerifyRecordAdmin(object):
    list_display = ["code","email","send_type","send_time"]
    search_fields = ["code","email","send_type"]
    list_filter = ["code","email","send_type","send_time"]


class BannerAdmin(object):
    list_display = ["title", "image", "url", "index","add_time"]
    search_fields = ["title", "image", "url", "index"]
    list_filter = ["title", "image", "url", "index","add_time"]


class UserProfileAdmin(UserAdmin):
    pass


xadmin.site.register(EmailVerifyRecord,EmailVerifyRecordAdmin)
xadmin.site.register(Banner,BannerAdmin)
xadmin.site.register(views.BaseAdminView,BaseSetting)
xadmin.site.register(views.CommAdminView,GlobalSetting)

'''
要先将UserProfile卸载否则会出现以下错误
xadmin.sites.AlreadyRegistered: The model UserProfile is already registered
'''
xadmin.site.unregister(UserProfile)#
xadmin.site.register(UserProfile,UserProfileAdmin)
